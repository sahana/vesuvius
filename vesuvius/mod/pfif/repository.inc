<?php
/**
 * @name         Person Finder Interchange Format
 * @version      2
 * @package      pfif
 * @author       Carl H. Cornwell <ccornwell at aqulient dor com>
 * @author       Leif Neve <lneve@mail.nih.gov>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0223
 */


require_once($global['approot'].'inc/handler_db.inc');
require_once("harvest_person_log.inc");
require_once("harvest_note_log.inc");
require_once("export_log.inc");
require_once("util.inc");
class Pfif_Repository {
    public $id;
    public $name;
    public $incident_id;
    public $base_url;
    public $subdomain;
    public $auth_key;
    public $resource_type;
    public $role;
    public $granularity;
    public $deleted_record;
    public $sched_interval_minutes;
    public $log_granularity;
    public $first_entry;
    public $last_entry;
    public $total_persons;
    public $total_notes;

    protected $is_new = true;      // Record has not been saved
    protected $log = null;

    public function __construct()
    {
    }

    /**
     * is_ready_for_harvest determines whether a harvest can be initiated
     * for this repository. The conditions include a test for proper role, harvest
     * not already in progress and time since last harvest.
     *
     * @return @code(true) if harvest is permissible, otherwise @code(false)
     * @param dir  direction ('in' or 'out')
     * @param datetime  scheduled time (default = now)
     *
     */
    public function is_ready_for_harvest($dir, $time = null) {

        // Make sure role is correct (e.g. can't do a scheduled import to a sink)
        if (($dir == 'out' && $this->role != 'sink') || ($dir == 'in' && $this->role != 'source')) {
            return false;
        }
        // Is harvest interval 0? (scheduled harvest has been disabled)
        if ($this->sched_interval_minutes == 0) {
            return false;
        }

        // If nothing has been logged, repository is ready for initial harvest.
        $log_end = $this->log->end_time;
        //var_dump('log_end', $log_end, 'first_entry', $this->first_entry);
        if ($this->first_entry == NULL || empty($log_end)) {
            return true;
        }

        // Verify that a harvest is not already in progress
        if (!empty($this->log) && $this->log->status == 'started') {
            // Print something to standard out to get some idea of frequency.
            print ("\nRepository '".$this->name."' already started!");
            return false;
        }

        // Check whether sched time is greater than last log end_time
        $sched_time = empty($time) ? time() : $time;
        $delta = $this->sched_interval_minutes * 60;
        $comp_time = strtotime($log_end) + $delta - 60;  // allow 60 second window
        $ready = ($comp_time <= $sched_time);
        //var_dump('sched_time',$sched_time,'delta',$delta,'comp_time',$comp_time,'ready',$ready);
        return ($ready);
    }

    public function get_request_params() {
        $params = array();
        //var_dump("log contains", $this->log);
        if (empty($this->log) || empty($this->log->last_entry)) {
            $params['min_entry_date'] = '2010-01-01T00:00:01Z';
        } else if ($this->log->last_entry == "0000-00-00 00:00:00") {
            $params['min_entry_date'] = utc_date($this->log->first_entry); // start at time of first entry logged
        } else {
            $params['min_entry_date'] = utc_date($this->log->last_entry); // start at time of last entry date logged
        }
        $params['skip'] = $this->log->last_count;
        return $params;
    }

    /**
     * start_harvest validates that the import/export is permissible and updates
     * log to indicate that a harvest is in progress.
     *
     * @throws RuntimeException if repository is not ready for harvest
     * @return @void
     * @param String  mode 'scheduled', 'manual' or 'test'
     * @param String  direction 'in', 'update' or 'out'
     */
    private function is_logrecord_done($start_time) {
        // ($start_time - $log_start_time) > $this->log_granularity)
        $log_start  = strtotime($this->log->start_time);
        $gran = date_parse($this->log_granularity);
        $gran_secs = 3600*$gran['hour']+60*$gran['minute']+$gran['second'];
        $done = ($start_time - $log_start >= $gran_secs);
        //var_dump($done, $start_time, $log_start, $gran_secs);
        return $done;
    }

    public function start_harvest($mode, $direction) {
        $start_time = time();
        if ($this->is_ready_for_harvest($direction, $start_time)) {
            $log = $this->log;
            if ($log->status == 'paused' && $this->is_logrecord_done($start_time)) {
                $log->status = 'completed';
                $log->update();
                //print "start_harvest: closed log record with start time ".$log->start_time."\n";
            }
            $this->log->start($this->id, $start_time, $mode, $direction);
        } else {
            throw new RuntimeException("Invalid start request: repository not ready.");
        }
    }

    /**
     * end_harvest performs any necessary post-processing on
     * completion of a harvest operation and updates the log accordingly.
     *
     * @throws RuntimeException if repository is not ready for harvest
     * @return @void
     * @param boolean  @code(true) if completed successfully, otherwise @code(false)
     * @param array() request params
     * @param array() harvest statistics (@see pfif.php and pfif_cron_import.php)
     *
     * @todo update repos last_entry and counts
     */
    public function end_harvest($success,$req_params,$info_array=array()) {
        // Verify that harvest is in progress
        if ($this->log->status != 'started') {
            throw new RuntimeException('Invalid end request: no harvest in progress.');
        }

        // If request was not successful, log 'error' otherwise
        // check log_granularity and if reached log 'completed' otherwise 'paused'
        $log_start  = strtotime($this->log->start_time);
        $end_time = time();
        $end_status = '';
        $gran = date_parse($this->log_granularity);
        $gran_secs = 3600*$gran['hour']+60*$gran['minute']+$gran['second'];
        //var_dump('log_start',$log_start,'end_time',$end_time,'log_granularity',$gran_secs);
        if ($end_time - $log_start <= $gran_secs) {
            $end_status = 'paused';
        } else {
            $end_status = 'completed';
        }
        //var_dump('end status',$end_status);
        if ($success == 'error') {
           // revert to original last_entry
           $info_array['last_entry'] = '';
           //$info_array['last_entry'] = $req_params['min_entry_date'];
        }
        $this->log->stop($end_time,$info_array,$req_params,$end_status);
        if ($success != 'error') {
           $this->update_summary($info_array);
        }
    }

    private function update_summary($info_array) {
        //var_dump('update_summary: info_array',$info_array);
        if (empty($this->first_entry)) {
            $this->first_entry = $info_array['first_entry'];
        }
        $this->last_entry = $info_array['last_entry'];
        $this->total_persons += $info_array['pfif_person_count'];
        $this->total_notes += $info_array['pfif_note_count'];
        $this->save(); // TODO: can this return a status that needs to be reported to caller?
    }

    /**
    * Create a Pfif_Repository from provided attributes and store in database.
    *
    * @return Pfif_Repository  returned even if validation failed and not stored in database
    */
    public static function create($attributes = array()) {
        $pr = new Pfif_Repository();
        foreach ($attributes as $prop_name => $prop_value) {
            if (property_exists('Pfif_Repository',$prop_name)) {
                $pr->$prop_name = $prop_value;
            } else {
                throw new InvalidArgumentException($prop_name.' is not a valid property');
            }
        }
        unset($prop_value);

        // Attempt save(). Set is_new if successful.
        if ($pr->save()) {
            // print "create.save successful\n";
            $pr->is_new = false;
        };

        $log = null;
        if (isset($pr->role) && $pr->role == 'source') {
            if ($pr->resource_type == 'person') {
               $pr->log = new Pfif_Harvest_Person_Log();
            } else {
               $pr->log = new Pfif_Harvest_Note_Log();
            }
        } else if (isset($pr->role) && $pr->role == 'sink') {
            $pr->log = new Pfif_Export_Log();
        }

        // Return instance regardless of save status.
        return $pr;
    }

    /**
    * Return true if this instance has been saved in the database.
    */
    public function is_new() {
        return $this->is_new;
    }

    public function get_log() {
        return $this->log;
    }

    public static function find($where_clause = '1') {
    global $global;
        $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
        $sql = "SELECT * from `pfif_repository` WHERE $where_clause";
        $rs = $global['db']->GetAssoc($sql);

        $r_list = false;
        if (!$rs) {
            pfif_error_log("ERROR: find ".$where_clause." failed! ".$global['db']->_errorMsg."\n");
        } else {
            foreach ($rs as $id => $row) {
                //var_dump($id,$row);
                $pr = self::parse_resultset($id, $row, true /* include log */);
                //var_dump('Parsed Object',$pr);
                $r_list[$id] = $pr;
            }
            unset($row);
        }

        return $r_list;
    }

    public static function find_by_id($id) {
        $r_list = false;
        if (isset($id) && !empty($id)) {
            $where_clause = " `id`='$id' ";
            $r_list = self::find($where_clause);
        }
        return $r_list;
    }

    public static function find_source($type, $name = 'all') {
        $where_clause = "`role`='source' ";
        $where_clause .= "AND `resource_type`='" .$type."' ";
        $where_clause .= ($name == 'all')
                                ? '' :
                                "AND `name` = '".addslashes($name)."'";
        $r_list = self::find($where_clause);
        return $r_list;
    }

    public static function find_sink($name = 'all') {
        $where_clause = "`role`='sink' ";
        $where_clause .= ($name == 'all')
                                ? '' :
                                "AND `name` = '".addslashes($name)."'";
        $r_list = self::find($where_clause);
        return $r_list;
    }

    // TODO: Doesn't this return the same result as find() and find_<role>('all') ?;
    public static function find_all($source_or_sink = 'all') {
        $where_clause = "`role`";
        $where_clause .= $source_or_sink == 'all' ? " in ('source','sink') " :
        "= '".$source_or_sink."' ";
        $r_list = find($where_clause);
        return $r_list;
    }

    // TODO: What is the distiction between find_all and list_all ?
    /* public static function list_all($source_or_sink = 'all') {
        $r_list = array();
        return $r;
    }
    */

    public function save() {
        global $global,$conf;
        if (!$this->is_new) {
            return $this->update();
        }

        if (!$this->validate()) {
            return false;
        }

        $status = false;
        if ($this->log_index != NULL) {
            $status = $this->update($log_table);
        } else {
            $insert_array = $this->copy_vars_to_array();
            try {
                shn_db_insert($insert_array,'pfif_repository',false);
                $msg = $global['db']->ErrorMsg();
                if (!empty($msg)) {
                    throw new RuntimeException();
                }

                // Get the key for the record we just inserted
                $key = $global['db']->Insert_ID('pfif_repository','id');
                if ($key) {
                    $this->id = $key;
                    $status = true;
                } else {
                    pfif_error_log("Pfif_Repository.save: failed to retrieve log_index :".$global['db']->ErrorMsg());
                }
            } catch (Exception $e) {
                pfif_error_log("shn_db_insert error:".$e->getMessage().":".$global['db']->ErrorMsg());
            }
        }
        return $status;

    }

    public function update() {
    global $global,$conf;
        $status = false;
        if (!($this->id == null) && $this->validate()) {
            $key = "WHERE `id` = '$this->id'";
            $insert_array = $this->copy_vars_to_array(false);
            // var_dump('pfif_repository.update: insert_array',$insert_array);
            try {
                shn_db_update($insert_array,'pfif_repository',$key);
                $status = true;
            } catch (Exception $e) {
                pfif_error_log("shn_db_insert error:".$e->getMessage().":".$global['db']->ErrorMsg());
            }
        }
        return $status;
    }

    /**
    *
    * Parse resultset row into repository instance
    *
    * @param  mixed   single resultset row from repository query
    * @param  boolean if @code(true) include associated log
    * @return array() indexed by column attribute name
    */
    protected static function parse_resultset($id, $row, $include_log = true) {
        $pr = new Pfif_Repository();
        $pr->id = $id;
        $pr->is_new = false;
        foreach ($row as $prop_name => $prop_value) {
            $pr->$prop_name = $prop_value;
        }
        unset($prop_value);

        $direction = ($pr->role == 'source')? 'in' : 'out';
        if (isset($pr->role) && $pr->role == 'source') {
            if ($pr->resource_type == 'note') {
               $log = Pfif_Harvest_Note_Log::get_last($id, $direction);
            } else {
               $log = Pfif_Harvest_Person_Log::get_last($id, $direction);
            }
            //var_dump("parse_resultset: log =",$log);
            if (empty($log)) {
                if ($pr->resource_type == 'person') {
                   $log = new Pfif_Harvest_Person_Log();
                } else {
                   $log = new Pfif_Harvest_Note_Log();
                }
                $log->direction = $direction;
                $log->repository_id = $id;
            }
            $pr->log = $log;
            //var_dump("parse_resultset: log =",$log);
        } else if (isset($pr->role) && $pr->role == 'sink') {
            $log = Pfif_Export_Log::get_last($id, $direction);
            //var_dump("parse_resultset: log =",$log);
            if (empty($log)) {
                $log = new Pfif_Export_Log();
                $log->direction = $direction;
                $log->repository_id = $id;
            }
            $pr->log = $log;
        }

        return $pr;
    }

    /**
    *
    * Copy instance variables to array for DB insert/update
    *
    * @param  boolean include key attribute
    * @return array() indexed by column attribute name
    */
    protected function copy_vars_to_array($include_key = true) {
        $array = array();
        $props = get_object_vars($this);
        //print "copy_vars...: props =\n";
        //print_r($props);
        if (!$include_key) {
            unset($props['id']);
        }
        // Unset non-db attributes
        unset($props['is_new']);
        unset($props['log']);
        foreach ($props as $prop_name => $prop_value) {
            if ($prop_value != NULL) {
                $name = trim($prop_name);
                $array[$name]=$prop_value;
            }
        }
        return $array;
    }
    /**
    * Validate instance attributes. Ensure that only a single instance exists in DB for given name, base url and role.
    * TODO: This may be relaxed to allow additional entries with different config.[export|import].url.
    *
    * @return @code(true) if validation passes, otherwise @code(false)
    */
    public function validate() {
        // check for required attributes
        if (!isset($this->name) ||
            !isset($this->base_url) ||
            !isset($this->role) )
        {
            return false;
        }
        // check role value
        if (!($this->role == 'source' || $this->role == 'sink')) {
            return false;
        }
        // check existence constraints
        // find where name == $this->name, if count > 0 return false;
        return true;
    }

}


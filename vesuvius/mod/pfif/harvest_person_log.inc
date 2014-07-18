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


require_once("log.inc");

class Pfif_Harvest_Person_Log extends Pfif_Log {
    const MY_LOG_TABLE = "pfif_harvest_person_log";
    public $images_in = 0;
    public $images_retried = 0;
    public $images_failed = 0;


    public function __construct() {}

    public function start($repos_id, $start_time, $mode, $dir) {
        $this->direction = $dir; // TODO: will parent copy vars pick this up?
        if ($this->status == null || $this->status == 'completed' || $this->status == 'error') {
            $this->reset_harvest_counts(); // Reset harvest counts counts when starting a new entry
        }
        return parent::start($repos_id, $start_time, $mode, self::MY_LOG_TABLE);
    }
    /**
    *   stop - overrides parent stop method in order to log harvest sp[ecific counts
    *
    */
    public function stop($end_time,$log_info,$req_params,$log_status='completed') {
      try {
        // var_dump('harvest_log.stop: before update',$this);
        $status = parent::stop($end_time,$log_info,$req_params,$log_status);
        if ($status) {
            // var_dump('harvest_log.stop: after parent update',$this);
            $this->update_harvest_counts($log_info);
            $status = $this->update();
            // var_dump('harvest_log.stop: after update',$this);
        }
        return $status;
      } catch (Exception $e) {
          error_log("pfif_harvest_person_log. : "+$e.getMessage());
          return false;
      }
    }

    //TODO: Is this being used?
    public function pause($end_time,$log_info) {
        return $this->stop($end_time,$log_info,'paused');
    }

    // TODO: can we overload base class' reset and update methods?
    public function reset_harvest_counts() {
//        parent::reset_counts(); // update common counts
        $this->images_in = 0;
        $this->images_retried = 0;
        $this->images_failed = 0;
    }

    public function update_harvest_counts($log_info) {
//        parent::update_counts($counts); // update common counts
        // var_dump('update_harvest_counts: info',$log_info);
        $this->images_in += $log_info['images_in'];
        $this->images_retried += $log_info['images_retried'];
        $this->images_failed += $log_info['images_failed'];
    }

    /*
     * DB layer methods
     */
    public function save() {
        return parent::save(self::MY_LOG_TABLE);
    }

    public function update() {
        // var_dump("pfif_harvest_person_log.update:",$this);

        return parent::update(self::MY_LOG_TABLE);
    }

    public static function find_by($columns,
                                   $conditions = null) {
        $rs = parent::find_by('pfif_harvest_repository',
                              $columns, $conditions);
        return $rs;
    }

    public static function get_last($repository_id,
                                    $direction) {
        global $global;

        $log = null;

        $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
        $where_clause = "`repository_id`='".$repository_id."' ";
        $where_clause .= "AND `direction` = '".$direction."' ";
        $where_clause .= "AND `start_mode` IN ('scheduled','test')";
        // $where_clause .= "AND NOT `status` = 'completed' ";

        $sql = "SELECT * from `pfif_harvest_person_log` WHERE $where_clause ".
               "ORDER BY start_time DESC LIMIT 1"; // TODO: first_entry and last_entry are already in UTC format, it would be
                                           //       nice if DATE_FORMAT(`xxx_entry`,"%Y-%m-%dT%TZ") could be used in the
                                           //       SELECT, but for now must be sure to reformat when used in Google APIs.
        // print "Log QUERY: $sql";
        $rs = $global['db']->GetAssoc($sql);
        // var_dump("Log resultset",$rs);
        if ($rs) {
            /* DEBUGGING ....
            foreach ($rs as $id => $row) {
                var_dump($id,$row);
            }
            unset($row);
            */ // ... DEBUGGING

            /* We only want to keep the first row */
            // var_dump("\nthe log records",$rs,"\n");
            $log_keys = array_keys($rs); // FIXME: what if no keys?
            $log_index = $log_keys[0];
            $row = array_shift($rs);
            $log = self::fetch_object($row,$log_index);
            //var_dump("using log record",$log,"\n");
            // die;
        // TODO: If there were multiple results, the earlier instances should be updated with status='error'
        } else {
            // print "No log records found for query\n$sql\n";
        }

        return $log;
    }

    private static function fetch_object($rs_row,$key = null) {
        // var_dump("Log row:",$rs_row,"key:",$key);
        $log = new Pfif_Harvest_Person_Log();
        if (empty($rs_row)) {
            return $log;
        }
        foreach ($rs_row as $prop_name => $prop_value) {
            $log->$prop_name = $prop_value;
        }
        unset($prop_value);
        $log->log_index = $key;
        return $log;
    }
}

<?php
/**
* @package     pfif
* @version      1.1
* @author       Nilushan Silva <>
* @author       Carl H. Cornwell <ccornwell@mail.nih.gov>
* LastModified: 2010:0304:2003
* License:      LGPL
* @link         TBD
*/
require_once("../../inc/handler_db.inc");
require_once("pfif_harvest_log.inc");
require_once("pfif_export_log.inc");
class Pfif_Repository {
    public $id;
    public $name;
    public $base_url;
    public $role;
    public $granularity;
    public $deleted_record;
    public $params;
    public $sched_interval_minutes;
    public $log_granularity;
    public $first_entry;
    public $last_entry;
    public $total_persons;
    public $total_notes;

    protected $is_new = true;
    protected $harvest_log = null; // FIXME: chc 4/27/10 : why are separate logs needed, isn't it
                                   //         true that only one or the other is possible based on $role?
    protected $export_log  = null;
    
    public function __construct()
    {
    }
    
    public function is_ready_for_import($import_time = null) {
        $sched_time = empty($import_time) ? time() : $import_time;
        // No log records exist, so ready for initial import.
        $log_end = $this->harvest_log->end_time;
        if ($this->first_entry == NULL || empty($log_end)) {
            return true;
        }
        
        // Check whether sched interval has elapsed since last log end_time 
        $delta = $this->sched_interval_minutes * 60;
        return ((strtotime($log_end) + $delta) >= $import_time);
    }
    
    public function start_import($mode,$direction) {
        $start_time = time();
        $this->harvest_log->start($this->id,$start_time,$mode,$direction);
    }
    
    public function end_import($status,$info_array=array()) {
    }
    
    public function is_ready_for_export() {
    }
    
    /**
            * Create a Pfif_Repository from provided attributes and store in database. 
            *
            * @return Pfif_Repository  returned even if validation failed and not stored in database
            */
    public static function create($attributes = array()) {
        $pr = new Pfif_Repository();
        foreach ($attributes as $prop_name => $prop_value) {
            $pr->$prop_name = $prop_value;
        }
        unset($prop_value);

        // Attempt save(). Set is_new if successful. 
        if ($pr->save()) {
            $pr->is_new = false;
        };

        $log = null;
        if (isset($pr->role) && $pr->role == 'source') {
            $pr->harvest_log = new Pfif_Harvest_Log();
        } else if (isset($pr->role) && $pr->role == 'sink') {
            $pr->export_log = new Pfif_Export_Log();
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
    
    public static function find($id) {
        $r_list = array();
        return $r_list;
    }

    public static function find_source($name = 'all') {
    global $global;
        $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
        $where_clause = "`role`='source' ";
        $where_clause .= ($name == 'all') 
                                ? '' :
                                "AND `name` = '".addslashes($name)."'";
        $sql = "SELECT * from `pfif_repository` WHERE $where_clause";
        $rs = $global['db']->GetAssoc($sql);

        $r_list = false;
        if (!$rs) {
            error_log("ERROR: find_source failed! ".$global['db']->_errorMsg."\n");
        } else {
            foreach ($rs as $id => $row) {
//                var_dump($id,$row);
                $pr = new Pfif_Repository();
                $pr->id = $id;
                $pr->is_new = false;
                foreach ($row as $prop_name => $prop_value) {
                    $pr->$prop_name = $prop_value;
                }
                unset($prop_value);

                $log = Pfif_Harvest_Log::get_last($id,'in');
                $pr->harvest_log = $log;
                $r_list[$id] = $pr;
            }
            unset($row);
        }
           
        return $r_list;
    }

    public static function find_sink($name = 'all') {
        $r_list = array();
        return $r_list;
    }

    public static function find_all($source_or_sink = 'all') {
        $r_list = array();
        return $r_list;
    }

    // TODO: What is the distiction between find_all and list_all ?
    public static function list_all($source_or_sink = 'all') {
        $r_list = array();
        return $r;
    }
    
    public function save() {
        if ($this->is_new) {
            return $this->update();
        }

        if ($this->validate()) {
            return true; // Be sure to set is_new to false if successful
        } else {
            return false;
        }
    }
    
    public function update() {
        if ($this->validate()) {
            return true;
        } else {
            return false;
        }
    }
    
    /**
            * Validate instance attributes. Ensure that only a single instance exists in DB for given name, base url and role.
            * TODO: This may be relaxed to allow additional entries with different config.[export|import].url.
            *
            * @return @code(true) if validation passes, otherwise @code(false)
            */
    public function validate() {
        // check for required attributes
        // check existence constraints
        return true;
    }
    
}


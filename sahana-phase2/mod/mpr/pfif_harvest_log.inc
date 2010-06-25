<?php
require_once("pfif_log.inc");

class Pfif_Harvest_Log extends Pfif_Log {
    const MY_LOG_TABLE = "pfif_harvest_log";
    public $images_in = 0;
    public $images_retried = 0;
    public $images_failed = 0;
    

    public function __construct() {}
    
    public function start($repos_id, $start_time, $mode, $dir) {
        $this->direction = $dir; // TODO: will parent copy vars pick this up?
        $this->reset_harvest_counts();
        return parent::start($repos_id, $start_time, $mode, self::MY_LOG_TABLE);
    }
    /**
            *   stop - overrides parent stop method in order to log harvest sp[ecific counts
            *
            */
    public function stop($end_time,$log_info,$log_status='completed') {
        $status = parent::stop($end_time,$log_info,$log_status);
        if ($status) {
            $this->update_harvest_counts($log_info);
            $status = $this->update();
        }
        return $status;
    }
    
    public function pause($end_time,$log_info) {
        return $this->stop($end_time,$log_info,'started');
    }
    
    // TODO: can we overload base class' reset and update methods?
    public function reset_harvest_counts() {
//        parent::reset_counts(); // update common counts
        $this->person_updates = 0;
        $this->images_in = 0;
        $this->images_retried = 0;
        $this->images_failed = 0;
    }

    public function update_harvest_counts($log_info) {
//        parent::update_counts($counts); // update common counts
        $this->person_updates += $log_info['person_updates'];
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
        $where_clause .= "AND `start_mode` = 'scheduled' ";
        // $where_clause .= "AND NOT `status` = 'completed' ";

        $sql = "SELECT * from `pfif_harvest_log` WHERE $where_clause ".
               "ORDER BY start_time DESC";
        $rs = $global['db']->GetAssoc($sql);
        
        if ($rs) {
            // DEBUGGING ....
            foreach ($rs as $id => $row) {
                var_dump($id,$row);
            }
            unset($row);
            // ... DEBUGGING

            /* We only want to keep the first row */
            $log = self::fetch_object($rs[0]);
        // TODO: If there were multiple results, the earlier instances should be updated with status='error'
        } else {
            print "No log records found for query\n$sql\n";
        }
        
        return $log;
    }
    
    private static function fetch_object($rs_row) {
        $log = new Pfif_Harvest_Log();
        foreach ($rs_row as $prop_name => $prop_value) {
            $log->$prop_name = $prop_value;
        }
        unset($prop_value);
        return $log;
    }
}
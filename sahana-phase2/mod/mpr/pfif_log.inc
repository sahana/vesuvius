<?php
// TODO: Need to add validate() method to be called by save() and update()

require_once("../../inc/handler_db.inc");
define("LOG_DATE_FORMAT","Y-m-d H:i:s");
abstract class Pfif_Log {
    public $log_index = null;
    public $repository_id = null;
    public $status = null;
    public $start_mode = '';
    public $start_time = null;
    public $end_time = null;
    public $first_entry = null;
    public $last_entry  = null;
    public $last_count  = 0;
    public $person_count = 0;
    public $note_count = 0;
    
    public function __construct() {}

    public function start($repos_id, $start_time, $mode, $log_table) {
        if ($this->status != 'started') { // This is a new entry
            $this->log_index = null;
            $this->first_entry = null;
            $this->last_entry = null;
            $this->reset_counts();
            $this->repository_id = $repos_id;
            $this->status='started';
            $this->start_time = date(LOG_DATE_FORMAT,$start_time);
            $this->start_mode = $mode;
            $status = $this->save($log_table);
        } else {
            // Nothing to do
            $status = false;
        }
        return $status;
    }
    /**
            *  Record the result of a harvest operation.
            *
            *   @return @code(true) = result recorded or @code(false) otherwise
            *   @param datetime  timetag of operation
            *   @param array() String UTC time of first (optional) and
            *                               String last entries from harvested repository, and 
            *                               int count of person and 
            *                               int note records harvested.
            *   @param String  The operation status may be one of:
            *       - started : the log's cumulative counts are being updated for a continuing operation
            *       - completed : the log's cumulative counts are being updated and the log record should be flushed
            *       - error : the last operation failed. TBD shat information is available
            *
            */
    public function stop($end_time,$log_info,$log_status='completed') {
        if ($this->status != 'completed') {
            $this->status=$log_status;
            $this->end_time =  date(LOG_DATE_FORMAT,$end_time);
            if (empty($this->first_entry)) {
                $this->first_entry = $log_info['first_entry'];
            }
            $last_entry = $log_info['last_entry'];
            if (!empty($last_entry) && $last_entry > $this->last_entry) {
                $this->last_entry = $last_entry;
                $this->last_count = $log_info['last_count'];
            }
            $this->update_counts($log_info);
        } else {
            /*  Calling stop when $this->status = 'completed' is a design error, as record should
                                 *  have been flushed. Throw runtime exception reporting error. */
            throw new RuntimeException("DESIGN ERROR: log->stop called in completed state");
        }
        return true;
    }

    // TODO: to make general, would need to extract keys from counters array (see below)
    protected function reset_counts() {
        $this->person_count = 0;
        $this->note_count = 0;
        $this->last_count = 0;
    }

    // TODO: could make this general y having it copy and counts it finds. Would have to put counts in a separate container within log_info.
    protected function update_counts($counts = array()) {
        $this->person_count += $counts['person_count'];
        $this->note_count += $counts['note_count'];
    }
    
    /*
            * DB layer methods 
            */
    public function save($log_table) {
    global $global,$conf;
        // $debug = $conf['debug'];
        // $conf['debug']=true;
        $status = false;
        if ($this->log_index != NULL) {
            $status = $this->update($log_table);
        } else {
            $insert_array = $this->copy_vars_to_array();
            try {
                shn_db_insert($insert_array,$log_table,false);
                $msg = $global['db']->ErrorMsg();
                if (!empty($msg)) {
                    throw new RuntimeException();
                }
                
                // Get the key for the record we just inserted
                $key = $global['db']->Insert_ID($log_table,'log_index');
                if ($key) {
                    $this->log_index = $key;
                    $status = true;
                } else {
                    error_log("Pfif_Log.save: failed to retrieve log_index :".$global['db']->ErrorMsg());
                }
            } catch (Exception $e) {
                error_log("shn_db_insert error:".$e->getMessage().":".$global['db']->ErrorMsg());
            }
        }
        // $conf['debug']=$debug;
        return $status;
    }

    public function update($log_table) {
    global $global;
        //$debug = $conf['debug'];
        //$conf['debug']=true;
        if ($this->log_index == null) {
            return false; // Can't update if key is null
        }
        $key = "WHERE `log_index` = '$this->log_index'";
        $insert_array = $this->copy_vars_to_array(false);
        //print "pfif_log.update:\n";
        //print_r($insert_array);
        try {
            shn_db_update($insert_array,$log_table,$key);
        } catch (Exception $e) {
            error_log("shn_db_insert error:".$e->getMessage().":".$global['db']->ErrorMsg());
            $conf['debug']=$debug;
            return false;
        }
        //$conf['debug']=$debug;
        return true;
    }
    
    public static function find_by($log_table, $columns, 
                                   $conditions = null) {
    global $global;
    
        $global['db']->SetFetchMode(ADODB_FETCH_ASSOC);
        $cols = is_array($columns) ? implode("`,`",$columns) : $columns;
        $cond = !empty($conditions) ? "$conditions" : '';
        $sql = "SELECT `$cols` FROM `$log_table` $cond";
        $rs = $global['db']->GetAssoc($sql);
        return $rs;
    }

    protected function copy_vars_to_array($include_key = true) {
        $array = array();
        $props = get_object_vars($this);
        //print "copy_vars...: props =\n";
        //print_r($props);
        if (!$include_key) {
            unset($props['log_index']);
        }
        foreach ($props as $prop_name => $prop_value) {
            if ($prop_value != NULL) {
                $name = trim($prop_name);
                $array[$name]=$prop_value;
            }
        }
        return $array;
    }    
}
?>
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

class Pfif_Export_Log extends Pfif_Log {
    const MY_LOG_TABLE = "pfif_export_log";

    public function __construct() {}

    public function start_harvest($repos_id, $start_time, $mode, $dir) {
        $this->direction = $dir;
        if ($this->status == null || $this->status == 'completed' || $this->status == 'error') {
            $this->reset_harvest_counts(); // Reset harvest counts counts when starting a new entry
        }
        return parent::start($repos_id, $start_time, $mode, self::MY_LOG_TABLE);
    }
    /**
    *   stop - overrides parent stop method in order to potentially log export-specific counts
    */
    public function stop($end_time,$log_info,$req_params,$log_status='completed') {
      try {
        // var_dump('export_log.stop: before update',$this);
        $status = parent::stop($end_time,$log_info,$req_params,$log_status);
        if ($status) {
            // var_dump('export_log.stop: after parent update',$this);
            $status = $this->update();
            // var_dump('export_log.stop: after update',$this);
        }
        return $status;
      } catch (Exception $e) {
          error_log("pfif_export_log. : "+$e.getMessage());
          return false;
      }
    }

    //TODO: Is this being used?
    public function pause($end_time,$log_info) {
        return $this->stop($end_time,$log_info,'paused');
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

    // TODO: Is this being used?
    public static function find_by($columns,
                                   $conditions = null) {
        $rs = parent::find_by('pfif_export_repository',
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

        $sql = "SELECT * from `pfif_export_log` WHERE $where_clause ".
               "ORDER BY start_time DESC LIMIT 1";
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
        $log = new Pfif_Export_Log();
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

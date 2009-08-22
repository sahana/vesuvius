<?php
/**
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

class report{

    private $tables;
    private $all=array();
    private $duplicate=array();
    private $update=array();
    private $insert=array();

    function set_tables($t=array()){
        $this->tables=$t;
    }

    function set_all_number(){
        global $global;
        foreach($this->tables as $table){
            $sql="SELECT count(*) FROM tmp_".$table;
            if (($rs=$global['db']->GetOne($sql)) === false) {
            print '36 error deleting: '.$global['db']->ErrorNo().$global['db']->ErrorMsg()."\n";
            }
            $this->all[$table]=$rs;
        }
    }

    function set_delete_number($table,$num){
        $this->duplicate[$table]=$num;
    }

    function set_update_number($table,$num){
        $this->update[$table]=$num;
    }

    function set_insert_number($table,$num){
        $this->insert[$table]=$num;
    }

    function print_report(){
        $report="<div id ='result'><table><thead><td>"._t('Table Name')."</td><td>"._t('Records Imported')."</td><td>"._t('Duplicate Records')."</td><td>"._t('Updated Records')."</td><td>"._t('Inserted Records')."</td></thead>";
        foreach($this->tables as $table){
            $report.="<tr>";
            $report.="<td>".$table."</td><td>".
                        $this->all[$table]."</td><td>".
                        $this->duplicate[$table]."</td><td>".
                        $this->update[$table]."</td><td>".
                        $this->insert[$table]."</td>";
            $report.="</tr>";
        }
        
        $report.="</div>";
        return $report;
    }
}


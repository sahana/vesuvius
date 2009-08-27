<?php
/**
 * DSM
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author      Nuwan Waidyanatha, LIRNEasia
 * @copyright   Lanka Software Foundation - http://www.opensource.lk
 * @package     bsm
 * @subpackage  bsm_db_io
 * @license     http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 * @TODO convert this to a class
 * @TODO enable multi mode IO for XML, txt file, SMS
 * @TODO enhance to accommodate multible databases
 * @TODO eliminate redundant code and include exisiting sahana libs such as handler_db.inc
 *
 */
//class bsm_sql_io
//{
function _shn_bsm_run_sql($sql)
{
    global $global;
    $db=$global["db"];
    //$results[] = array(); problems when passing results=false;
    //$link = mysql_connect("localhost", "root", "") or die ("Could not connect");
    $conn = mysql_connect("localhost", "root", "") or die("Error No ".mysql_errno($conn).": Conection error - ".mysql_error($conn));
    if (!$conn || !mysql_select_db("rtbp",$conn)){$results=false;}
    else
    {
        $rsql = mysql_query($sql);
        if (substr($sql, 0, 3)=="SEL" || substr($sql, 0, 3)=="SHO")
        {
            if ($rsql==FALSE){$results = FALSE;}
            elseif (empty($rsql) || mysql_num_rows($rsql)==0){$results=null;}
            else {while ($row = mysql_fetch_assoc($rsql)) {$results[] = $row;} mysql_free_result($rsql);}
        }
        elseif ($rsql==FALSE){$results=FALSE;} 
        elseif (substr($sql, 0, 3)=="INS") {$results = mysql_insert_id();}
        else {$results = TRUE;}
    }    
    mysql_close($conn);
    return $results;
}
//@table = disease, symptom, sign,
function _shn_bsm_get_tbl_recs($table,$pkname=null,$pkvalues=null,$fatts=null)
{
    $rsql[] = array();
    if (!empty($fatts))
    {
        $sql = "SELECT ";
        $arrfatts = explode(' ',$fatts);
        foreach ($arrfatts as $rf => $fvalue)
        {
            $sql .= $fvalue.", ";
        }
        $sql = substr($sql,0,-2);
    }
    else {$sql = $sql."SELECT * ";}
    $sql .= " FROM $table WHERE deactivate_dt IS NULL ";
    if (!empty($pkvalues)&&!empty($pkname))
    {
        $arrpkvals = explode(' ',$pkvalues);
        foreach ($arrpkvals as $rpk => $pvalue)
        {
            $pksql .= "'$pvalue', ";
        }
        $pksql = substr($pksql,0,-2);
        $pksql = "AND $pkname in ($pksql)";
    }
    else {$pksql="";}
    $sql .= $pksql;
    $rsql[] = _shn_bsm_run_sql($sql);
    //print_r(array_values($rsql));
    return $rsql;
}
//@tables: dis_symp, dis_sign
function _shn_bsm_get_join_recs($sqljoin, $pk1name=null, $pk2name=null, $pk1val=null, $pk2val=null, $fatts=null)
{
    $rsql[] = array();
    //$arrstruct = _shn_bsm_run_sql("SHOW COLUMNS FROM $table");
    if (!empty($fatts))
    {
        $sql = "SELECT ";
        $arrfatts = explode(' ',$fatts);
        foreach ($arrfatts as $rf => $fvalue)
        {
            $sql .= "$fvalue, ";
        }
        $sql = substr($sql,0,-2);
    }
    else {$sql .= "SELECT *";}
    $sql = $sql.$sqljoin;
    if (!empty($pk1name)&&!empty($pk1val))
    {
        $arrpkvals = explode(' ',$pk1val);
        foreach ($arrpkvals as $rpk => $pvalue)
        {
            $pksql .= "'$pvalue', ";
        }
        $pksql = substr($pksql,0,-2);
        $pksql = "AND ".trim($pk1name)." in (".$pksql.")";
    }
    else {$pksql="";}
    $sql .= $pksql;
    if (!empty($pk2name)&&!empty($pk2val))
    {
        $pksql="";
        $arrpkvals = explode(' ',$pk2val);
        foreach ($arrpkvals as $rpk => $pvalue)
        {
            $pksql .= "'$pvalue', ";
        }
        $pksql = substr($pksql,0,-2);
        $pksql = "AND ".trim($pk2name)." in ($pksql)";
    }
    else {$pksql="";}
    $sql .= $pksql;
    $rsql = _shn_bsm_run_sql($sql);
    return $rsql;
}
//@table: all stand alone tables
function _shn_bsm_set_tbl_recs ($table, $pknames=null, $pkvalues=null, $fatts=null, $fvals=null)
{
    if (!empty($pknames)&&!empty($pkvalues))
    {
        $rfn = _shn_bsm_get_tbl_recs($table,$pknames,$pkvalues,null);
        if($rfn[1]!=null || $rfn[1]!=false){$action = "update";} else {$action = "insert";}
    }
    else {$action = "insert";}
    $arrstruct = _shn_bsm_run_sql("SHOW COLUMNS FROM $table");
    $arrfatts = explode(' ',$fatts);
    $arrfvals = explode(' ',$fvals);
    switch ($action)
    {
        case "update":
            $sql = "UPDATE ".$table." SET ";
            foreach ($arrfatts as $rf => $fv)
            {
                reset($arrstruct);
                for ($i=0; $i<count($arrstruct);$i++)
                {
                    if ($fv == current($arrstruct[$i]))
                    {
                        foreach ($arrstruct[$i] as $arr => $arrval)
                        {
                            if ($arr == 'Type')
                            {
                                if (substr($arrval,0,3) == 'int' || substr($arrval,0,3) == 'dec' || substr($arrval,0,4) == 'bool')
                                {$sql .= "$fv = $arrfvals[$rf], ";}
                                else {$sql .= "$fv = '$arrfvals[$rf]', ";}
                             }
                        }

                    }
                }
            }
            $sql = substr($sql, 0, -2);
            $sql .= " WHERE deactivate_dt IS NULL ";
            $arrpk = explode(' ',$pknames);
            $arrpv = explode(' ',$pkvalues);
            foreach ($arrpk as $rf => $fv)
            {
                $sql .= "AND ".$fv." = '".$arrpv[$rf]."' ";
            }
            $result = _shn_bsm_run_sql($sql);
            break;

        case "insert":          
            foreach ($arrfatts as $rf => $fv)
            {
                reset($arrstruct);
                for ($i=0; $i<count($arrstruct);$i++)
                {
                    if ($fv == current($arrstruct[$i]))
                    {
                        foreach ($arrstruct[$i] as $arr => $arrval)
                        {
                            if ($arr == 'Type')
                            {
                                if (substr($arrval,0,3) == 'int' || substr($arrval,0,3) == 'dec' || substr($arrval,0,4) == 'bool')
                                {$vsql .= "$arrfvals[$rf], ";}
                                else {$vsql .= "'$arrfvals[$rf]', ";}
                            }
                        }
                    }
                }
            }
            $fatts = str_replace(" ",", ",$fatts);
            $vsql = substr($vsql, 0, -2);
            $sql = "INSERT INTO $table ($fatts) VALUES ($vsql)";
            $result = _shn_bsm_run_sql($sql);
            break;
        default:
            break;
    }
    return $result;
}

//$sql_io = new bsm_sql_io;
$action = trim (!empty($_POST['action']) ? $_POST['action'] : $_GET['action']);
$table = trim (!empty($_POST['table']) ? $_POST['table'] : $_GET['table']);
$pk1name = trim (!empty($_POST['pk1name']) ? $_POST['pk1name'] : $_GET['pk1name']);
$pk1val = trim (!empty($_POST['pk1val']) ? $_POST['pk1val'] : $_GET['pk1val']);
$pk2name = trim (!empty($_POST['pk2name']) ? $_POST['pk2name'] : $_GET['pk2name']);
$pk2val = trim (!empty($_POST['pk2val']) ? $_POST['pk2val'] : $_GET['pk2val']);
$fatts = trim (!empty($_POST['fatts']) ? $_POST['fatts'] : $_GET['fatts']);
$fvals = trim (!empty($_POST['fvals']) ? $_POST['fvals'] : $_GET['fvals']);

if ($action!=null && $table!=null)
{
    $rfn[] = array();
    //$action = get, set1, &setm
    //to minimize the input string length from table names the standard prefix is attached
    //but can be removed if you are using a none bsm module sahana table
    $table = substr($table,0,4)!="bsm_" ? $table .= "bsm_" : $table;
    switch ($action)
    {
        //GET
        case get:
            switch ($table)
            {
                case ("dis_symp"):
                    $sqljoin = $sqljoin." FROM dis_symp ds INNER JOIN disease d ON d.disease = ds.disease ";
                    $sqljoin = $sqljoin."INNER JOIN symptom s ON s.symptom = ds.symptom WHERE ds.deactivate_dt IS NULL ";
                    $fatts = "d.disease s.symptom";
                    $pk1name = "d.".$pk1name; $pk2name = "s.".$pk2name;
                    $rfn = _shn_bsm_get_join_recs($sqljoin, $pk1name, $pk2name, $pk1val, $pk2val, $fatts);
                    break;
                case ("dis_sign"):
                    $sqljoin = $sqljoin." FROM dis_sign ds INNER JOIN disease d ON d.disease = ds.disease ";
                    $sqljoin = $sqljoin."INNER JOIN sign s ON s.sign = ds.sign WHERE ds.deactivate_dt IS NULL ";
                    $fatts = "d.disease s.sign";
                    $pk1name = "d.".$pk1name; $pk2name = "s.".$pk2name;
                    $rfn = _shn_bsm_get_join_recs($sqljoin, $pk1name, $pk2name, $pk1val, $pk2val, $fatts);
                    break;
                case ("dis_caus_fact"):
                    $sqljoin = $sqljoin." FROM dis_caus_fact dcf INNER JOIN disease d ON d.disease = dcf.disease ";
                    $sqljoin = $sqljoin."INNER JOIN caus_fact cf ON cf.caus_fact = dcf.caus_fact WHERE dcf.deactivate_dt IS NULL ";
                    $fatts = "d.disease cf.caus_fact";
                    $pk1name = "d.".$pk1name; $pk2name = "cf.".$pk2name;
                    $rfn = _shn_bsm_get_join_recs($sqljoin, $pk1name, $pk2name, $pk1val, $pk2val, $fatts);
                    break;
                case ("case_sign"):
                    $sqljoin = $sqljoin." FROM case_sign cs INNER JOIN cases ca ON ca.case_id = cs.case_id ";
                    $sqljoin = $sqljoin."INNER JOIN sign s ON s.sign = cs.sign WHERE cs.deactivate_dt IS NULL ";
                    $fatts = "ca.case_id ca.disease s.sign s.sign_desc";                    
                    if (!empty($pk1name)){$pk1name = "ca.".$pk1name;}else{$pk1name=null;}
                    if (!empty($pk2name)){$pk2name = "s.".$pk2name;}else{$pk2name=null;}
                    $rfn = _shn_bsm_get_join_recs($sqljoin, $pk1name, $pk2name, $pk1val, $pk2val, $fatts);
                    break;
                case ("case_symp"):
                    $sqljoin = $sqljoin." FROM case_symp cs INNER JOIN cases ca ON ca.case_id = cs.case_id ";
                    $sqljoin = $sqljoin."INNER JOIN symptom s ON s.symptom = cs.symptom WHERE cs.deactivate_dt IS NULL ";
                    $fatts = "ca.case_id ca.disease s.symptom s.symp_desc";
                    if (!empty($pk1name)){$pk1name = "ca.".$pk1name;}else{$pk1name=null;}
                    if (!empty($pk2name)){$pk2name = "s.".$pk2name;}else{$pk2name=null;}
                    $rfn = _shn_bsm_get_join_recs($sqljoin, $pk1name, $pk2name, $pk1val, $pk2val, $fatts);
                    break;
                default:
                    $rfn = _shn_bsm_get_tbl_recs($table,$pk1name,$pk1val,$fatts);
                    break;
            }
            break;
        //SET1 - write a single record with none or one primary key and multiple fields of a record
        case set1:
            $arrfatts = explode(' ', $fatts); $arrfvals = explode(' ', $fvals);
            if (empty($fatts) || empty($fvals) )
                {
                    print("Improperly defined parameters! fatts = ".count($arrfatts)." fvals = ".count($arrfvals));
                    $rfn = false;
                }
            else
            {
                switch ($table)
                {
                    //@TODO add in rules for insert and update based on referential integrity
                    case "location":
                        $rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $fatts, $fvals); break;
                    case "person":
                        $rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $fatts, $fvals); break;
                    case "cases":                   
                        $rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $fatts, $fvals); break;
                    case "case_symp":
                        $rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $fatts, $fvals); break;
                    case "case_sign":
                        $rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $fatts, $fvals); break;
                    default: break;
                }
            }
            break;
        //SETM - write a multiple records with none, one or two primary keys and a single field of a record
        case setm:
            $arrfvals = explode(' ',$fvals);
            foreach ($arrfvals as $rv => $rf)
            {
                switch ($table)
                {
                    case "case_symp":
                        $rfn = _shn_bsm_run_sql("SELECT * FROM $table WHERE deactivate_dt IS NULL AND $pk1name = '$pk1val' AND $fatts = '$rf'");
                        if($rfn[1]==null || $rfn[1]==false)
                        {$rfn = _shn_bsm_set_tbl_recs($table, null, null, $pk1name." ".$fatts, $pk1val." ".$rf);}
                        else {$rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $pk1name." ".$fatts, $pk1val." ".$rf);}
                        break;
                    case "case_sign":
                        $rfn = _shn_bsm_run_sql("SELECT * FROM $table WHERE deactivate_dt IS NULL AND $pk1name = '$pk1val' AND $fatts = '$rf'");
                        if($rfn[1]==null || $rfn[1]==false)
                        {$rfn = _shn_bsm_set_tbl_recs($table, null, null, $pk1name." ".$fatts, $pk1val." ".$rf);}
                        else {$rfn = _shn_bsm_set_tbl_recs($table, $pk1name, $pk1val, $pk1name." ".$fatts, $pk1val." ".$rf);}
                        break;
                    default: break;
                }
            }
            break;
        default:
            break;
    }
    if (is_array($rfn)){print_r(array_values($rfn));}
    else {print $rfn;}
}
else
{
    print ("Invalid parameters!");
}
?>

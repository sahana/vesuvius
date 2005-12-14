<?php
/* $Id: audit.inc,v 1.1 2005-12-14 12:55:22 janakawicks Exp $ */

/** Audit page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

function shn_audit_show($x_uuid)
{
    global $global;

    $sql = "SELECT a.updated, b.full_name, a.change_table, a.change_field, " . 
    "a.change_type, a.prev_val, a.new_val FROM audit a LEFT OUTER JOIN " .
    "person_uuid b ON b.p_uuid = a.u_uuid WHERE a.x_uuid = '$x_uuid' ";
    $arr_result = $global['db']->GetAll($sql);
    
    echo ' <a title="Download"'.
        'href="index.php?mod='.$global['module'].'&act=auditmp&id='.
        $_GET['id'].'" >'.'Download CSV'. '</a>';

    echo '&nbsp;&nbsp;&nbsp;<a title="Download"'.
        'href="index.php?mod='.$global['module'].'&act=auditmp&id='.
        $_GET['id'].'" >'.'Download PDF'. '</a>';

    echo '&nbsp;&nbsp;&nbsp;<a title="Download"'.
        'href="index.php?mod='.$global['module'].'&act=auditmp&id='.
        $_GET['id'].'" >'.'Download Ugly Excel'. '</a>';
//TODO PUT INTO A LIB
?>
<DIV ID="result">
<TABLE>
<THEAD>
    <TD>Date/Time</TD>
    <TD>User Making Changes</TD>
    <TD>Table Affected</TD>
    <TD>Field Affected</TD>
    <TD>Type of change</TD>
    <TD>Previous Value</TD>
    <TD>New Value</TD>
</THEAD>
<?php
    foreach($arr_result as $arr){
        if ($arr['change_type'] == 'ins' )
            $arr['change_type'] = 'Inserted'; 
?>
    <TR>
    <TD><?= $arr['updated']; ?></TD>
    <TD><?= $arr['full_name']; ?></TD>
    <TD><?= $arr['change_table']; ?></TD>
    <TD><?= $arr['change_field']; ?></TD>
    <TD><?= $arr['change_type']; ?></TD>
    <TD><?= $arr['prev_val']; ?></TD>
    <TD><?= $arr['new_val']; ?></TD>
    </TR>
<?php
    }
?>    
</TABLE>
</DIV>
<?
}
?>

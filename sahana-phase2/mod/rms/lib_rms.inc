<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/ 

require_once('lib_request.inc');


function _shn_rms_show_headder($sub='')
{
?>
<h2><?=_("Sahana Request Management System")?></h2>
<?php
if ($sub != '')
    print "<h3>" . _("$sub") . "</h3>";
}

/**
 * Some Simple Error Handling
 */
function _shn_rms_adderror($err_msg)
{
    $_SESSION['rms_errors'][] = $err_msg;
}

function _shn_rms_showerrors()
{
    if (!isset($_SESSION['rms_errors']))
        return false;
    $errors = $_SESSION['rms_errors'];
?>
<div id="errors">
    <p><em>Oops... the following errors were encountered:</em></p>
    <ul>
<?php
    foreach ( $errors as $err )
    {
?>
    <li><?=$err?></li>
<?php
    }
?>
    </ul>
</div>    
<?php
    $_SESSION['rms_errors'] = null;
}

function _shn_rms_errorcount()
{
    return count($_SESSION['rms_errors']);
}


/**
 * Categoty list
 */
 
function _shn_rms_get_catlist()
{
    global $global;
    
    $sql = "SELECT id,category FROM rms_item_cat";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $recs = $recordSet_cat->getArray(); 
    $list = array();
    foreach ($recs as $rec)
    {
        $list[$rec[0]] = $rec[1];
    }
    return $list;
}

function _shn_rms_get_prylist()
{
    global $global;
    
    $sql = "SELECT id,priority FROM rms_item_pry";    
    $recordSet_cat = $global['db']->Execute($sql);
    
    $recs = $recordSet_cat->getArray(); 
    $list = array();
    foreach ($recs as $rec)
    {
        $list[$rec[0]] = $rec[1];
    }
    return $list;
}

function _shn_rms_get_catname($cat_id)
{
    global $global;
    
    $sql = "SELECT category FROM rms_item_cat WHERE id='$cat_id'";    
    $rs = $global['db']->Execute($sql);
    
    
    if ($rs == null)
    {
        _shn_rms_adderror("Incorrect category id");
        return false;
    }
    
    if (1>$rs->RecordCount())
    {
        _shn_rms_adderror("Category doesn't exist'");
        return false;
    }
    
    $arr = $rs->GetArray();
    $cat = $arr[0];
    return $cat['category'];
}

function _shn_rms_get_pryname($pry_id)
{
    global $global;
    
    $sql = "SELECT priority FROM rms_item_pry WHERE id='$pry_id'";    
    $rs = $global['db']->Execute($sql);
    
    if ($rs == null)
    {
        _shn_rms_adderror("Incorrect Priority id");
        return false;
    }
    
    if (1>$rs->RecordCount())
    {
        _shn_rms_adderror("Priority doesn't exist'");
        return false;
    }
    
    $arr = $rs->GetArray();
    $pry = $arr[0];
    return $pry['priority'];
}

/**
 * @TODO
 * Stopping accidental resubmiting on refresh or backbutton
 */

?>
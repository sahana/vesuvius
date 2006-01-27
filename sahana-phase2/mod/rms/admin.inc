<?php
/**
* Sahana Request Management System configuration file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package
* @subpackage
* @tutorial
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
require_once 'lib_rms.inc';

function shn_rms_adm_default()
{
?>

<h2>Welcome to The RMS Administration Page</h2>
<br/><hr/><br/>
<div id="home">
<div id="result">
<div id="home_resent"><?php print _("Items Category Settings")?></div><hr/>
<?php print '<a href="index.php?mod=rms&act=adm_add_category">' . _("Add Category") . '</a>'?><br/>
<?php print '<a href="index.php?mod=rms&act=adm_remove_category">' . _("Remove Category") . '</a>'?><br/>
</div>
</div>
<br/><hr/><br/>
<div id="result">
<div id="home_resent"><?php print _("Items Priority Settings")?></div><hr/>
<?php print '<a href="index.php?mod=rms&act=adm_add_priority">' . _("Add Priority Type") . '</a>'?><br/>
<?php print '<a href="index.php?mod=rms&act=adm_remove_priority">' . _("Remove Priority Type") . '</a>'?><br/>
</div>
</div>
</div>

<?php
}


function check_frgn_key($table,$field,$value)
{
    global $global;

    $sql = "SELECT $field FROM $table WHERE $field='$value'";
    $rs = $global['db']->Execute($sql);

    if (1 > $rs->RecordCount())
    {
        return false;
    }

    return true;
}


/**
 * Add/Remove Item Category types
 */



function show_rms_categories_adm()
{
    global $global;

    $sql = "SELECT * FROM rms_req_category";
    $recordSet_cat = $global['db']->Execute($sql);

    $rs = $recordSet_cat->getArray();
?>
<div id ="result">
    <table>
    <thead>
        <td><?php print _("CatID") ?></td>
        <td width="150"><?php print _("Category") ?></td>
        <td width=""><?php print _("Description") ?></td>
    </thead>
    <tbody>
    <?php
        foreach($rs as $r)
        {
    ?>
    <tr>
        <td><?php print  $r['cat_id'] ?></td>
        <td><?php print  $r['category'] ?></td>
        <td><?php print  $r['description'] ?></td>
    </tr>
    <?php
        }
    ?>
    </table>
</div>
<?php
}

function shn_rms_adm_add_category()
{

    shn_form_fopen("adm_add_cat",null);

    shn_form_fsopen('Add Categories');

    //shn_form_select(get_rms_catlist(),"category","category");
    shn_form_text('Category','cat_name','size="30"');
    shn_form_textarea('Description','cat_desc');

    shn_form_fsclose();
    shn_form_submit('Add');
    shn_form_fclose();
    show_rms_categories_adm();

}

function shn_rms_adm_add_cat()
{

    global $global;
    $name = $_POST["cat_name"];
    $desc = $_POST["cat_desc"];
    $error = false;

    $sql = "SELECT category FROM rms_req_category WHERE category='$name'";
    $rs = $global['db']->Execute($sql);

    if(trim($_POST["cat_name"])=='' || !isset($_POST["cat_name"]))
    {
    	_shn_rms_adderror("The Category cannot be blank please enter a " .
    			"valid Category");
    	$error = true;
    }

    if(trim($_POST["cat_desc"])=='' || !isset($_POST["cat_desc"]))
    {
    	_shn_rms_adderror("The Category description cannot be blank please enter a " .
    			"valid Category description");
    	$error = true;
    }

    if($error)
    {
    	_shn_rms_showerrors();
    }
    elseif (1 > $rs->RecordCount())
    {
        $sql = "INSERT INTO rms_req_category (category,description) VALUES('$name','$desc')";
        $global['db']->Execute($sql);
        print _("category added successfully");
    }
    else
    {
        print _("The category already exists");
    }

    shn_rms_adm_add_category();

}


function shn_rms_adm_remove_category()
{

    shn_form_fopen("adm_remove_cat",null);

    shn_form_fsopen('Remove Categories');

    shn_form_select(get_rms_catlist(),"Category","cat_id");

    shn_form_fsclose();
    shn_form_submit('Remove');
    shn_form_fclose();
    show_rms_categories_adm();

}

function shn_rms_adm_remove_cat()
{
    global $global;
    $cat_id = $_POST["cat_id"];

    if (!check_frgn_key("rms_req_item","cat_id",$cat_id))
    {
        $sql = "DELETE FROM rms_req_category WHERE cat_id='$cat_id'";
        $rs = $global['db']->Execute($sql);
        print _("Category removed successfully");
    }
    else
    {
        print _("This category cannot be removed, because it is in use atm");
    }

    shn_rms_adm_remove_category();
}

/**
 * Add/Remove Item Priority types
 */
function get_rms_priolist()
{
    global $global;

    $sql = "SELECT priority_id,priority FROM rms_req_priority";
    $recordSet_prio = $global['db']->Execute($sql);

    $recs = $recordSet_prio->getArray();
    $list = array();
    foreach ($recs as $rec)
    {
        $list[$rec[0]] = $rec[1];
    }
    return $list;
}

function show_rms_priorities()
{
    global $global;

    $sql = "SELECT * FROM rms_req_priority";
    $recordSet_prio = $global['db']->Execute($sql);

    $rs = $recordSet_prio->getArray();
?>
<div id ="result">
    <table>
    <thead>
        <td><?php print _("Priority_ID") ?></td>
        <td width="150"><?php print _("Priority") ?></td>
        <td width=""><?php print _("Description") ?></td>
    </thead>
    <tbody>
    <?php
        foreach($rs as $r)
        {
    ?>
    <tr>
        <td><?php print  $r['priority_id'] ?></td>
        <td><?php print  $r['priority'] ?></td>
        <td><?php print  $r['description'] ?></td>
    </tr>
    <?php
        }
    ?>
    </table>
</div>
<?php
}

function shn_rms_adm_add_priority()
{

    shn_form_fopen("adm_add_prio",null);

    shn_form_fsopen('Add Priority Type');

    shn_form_text('Priority','priority','size="30"');
    shn_form_textarea('Description','prio_desc');

    shn_form_fsclose();
    shn_form_submit('Add');
    shn_form_fclose();
    show_rms_priorities();

}

function shn_rms_adm_add_prio()
{

    global $global;
    $prio = $_POST["priority"];
    //print $name;
    $desc = $_POST["prio_desc"];
    $error = false;

    global $global;
    $sql = "SELECT priority FROM rms_req_priority WHERE priority='$prio'";
    $rs = $global['db']->Execute($sql);

    if(trim($_POST["priority"])=='' || !isset($_POST["priority"]))
    {
    	_shn_rms_adderror("The priority cannot be blank please enter a " .
    			"valid priority");
    	$error = true;
    }

    if(trim($_POST["prio_desc"])=='' || !isset($_POST["prio_desc"]))
    {
    	_shn_rms_adderror("The priority description cannot be blank please enter a " .
    			"valid priority description");
    	$error = true;
    }

    if($error)
    {
    	_shn_rms_showerrors();
    }
    elseif (1 > $rs->RecordCount())
    {
        $sql = "INSERT INTO rms_req_priority (priority,description) VALUES('$prio','$desc')";
        $global['db']->Execute($sql);
        print _("Priority type added successfully");
    }
    else
    {
        print _("The Priority type already exists");
    }

    shn_rms_adm_add_priority();

}


function shn_rms_adm_remove_priority()
{

    shn_form_fopen("adm_remove_prio",null);

    shn_form_fsopen('Remove Priority Type');

    shn_form_select(get_rms_priolist(),"Priority","priority");

    shn_form_fsclose();
    shn_form_submit('Remove');
    shn_form_fclose();
    show_rms_priorities();

}

function shn_rms_adm_remove_prio()
{
    global $global;
    $prio = $_POST["priority"];

    if (!check_frgn_key("rms_req_item","priority_id",$prio))
    {
        $sql = "DELETE FROM rms_req_priority WHERE priority_id='$prio'";
        $rs = $global['db']->Execute($sql);
        print _("Priority Type removed successfully");
    }
    else
    {
        print _("This Priority type cannot be removed, because it is in use at the moment");
    }

    shn_rms_adm_remove_priority();
}
?>
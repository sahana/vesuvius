<?php
/**
 * View & Edit  
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


/**
 * This function shows a form to select the category.Submit the result to shn_cs_edit_form_submit() in main.inc.
 * @access public
 * @return void
 */
function shn_cs_edit_form()
{
    $option_array=array('none' => '-----Select -----','Item' => 'Item/Catalogue','Unit' => 'Unit','Unit_types'=>'Unit Types');
    $form_opts['name']="select_edit_type_form";
    shn_form_fopen('edit_form_submit',null,$form_opts);
    shn_form_fsopen(_('Select Category'));
    $select_opts='onChange="select_edit_type_form_submit()"';
    shn_form_select($option_array,'','edit_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();

    shn_cs_select_edit_type_form_submit_js();
}


/**
 * This function shows the Catalogue/Item table. Submit the result to shn_cs_edit_cat_select_submit() in main.inc.
 * @access private
 * @return void
 */
function show_item_cat_table()
{
    global $global;
    $db=$global["db"];


    //------new development
    $query1="select ct_uuid,name from ct_catalogue where parentid = '0' ";
    $res1=$db->Execute($query1);

    $main_cat_arr = array('all' => 'All');
    while(!$res1==NULL && !$res1->EOF)
    {
    $main_cat_arr[$res1->fields["ct_uuid"]]=$res1->fields["name"];
    $res1->MoveNext();
    }

    $cat_item_level_arr = array('all' => 'All','l1' =>'Level 1','l2' =>'Level 2','l3' =>'Level 3','l4' =>'Level 4');
    $num_of_rec = array('all'=>'All','10'=>'10','20'=>'20','30'=>'30');
    $cat_item_arr = array('all'=>'All','cat' => 'Catalogs', 'item' => 'Items');

	print "<br><br>";
    	shn_form_fopen(null,null,$form_opts);
   	?>
    <div id="result">
    <table>

	<tr>
        <td><?php print "Filter by : Main catalogue"; ?></td>
        <td><?php print "Filter by : Cataolg/Item"; ?></td>
        <td><?php print "Filter by : Level"; ?></td>
	<td><?php print "Filter by : Number of Records"; ?></td>
	<td><?php print ""; ?></td>
	</tr>

	<tr>
        <td><?php shn_form_select($main_cat_arr,'','edit_type',$select_opts,null); ?></td>
        <td><?php shn_form_select($cat_item_arr,'','edit_type',$select_opts,null); ?></td>
        <td><?php shn_form_select($cat_item_level_arr,'','edit_type',$select_opts,null); ?></td>
	<td><?php shn_form_select($num_of_rec,'','edit_type',$select_opts,null); ?></td>
	<td><?php shn_form_submit(_("Filters"));; ?></td>
	</tr>
	</table>
	</div>	
		<?php
	shn_form_fclose();
//-----------------------------------------------------------------------------------------------------------------------

?>
<br>
<div id="result">
<table>
    <thead>
        <td><strong><?=_("Name")?></strong></td>

        <td><strong><?=_("Item/Catalogue")?></strong></td>
	<td><strong><?=_("Keyword")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $query="select * from ct_catalogue";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $name=$res->fields["name"];
    $description=$res->fields["description"];
    $cat_id=$res->fields["ct_uuid"];
    $final_flag=$res->fields["final_flag"];
    $keyword=$res->fields["keyword"];
    $parent_ID=$res->fields["parentid"];

    ?>
    <tr>
        <td><?php _shn_cs_add_spaces_to_table($cat_id); ?><a href="index.php?mod=cs&act=edit_cat_select_submit&id=<?php echo $cat_id ?>"><?php print $name ;?></a></td>
        <?php if($final_flag=='0' && $parent_ID == '0') { ?>
            <td><?php print "Main catalogue" ; ?></td>
        <?php } elseif($final_flag=='0' && $parent_ID != '0') { ?>
	    <td>&nbsp;&nbsp;<?php print "Sub catalogue" ; ?></td>
        <?php } else { ?>
            <td>&nbsp;&nbsp;&nbsp;&nbsp;<?php print "Item" ; ?></td>
        <?php } ?>
           <td>&nbsp;&nbsp;&nbsp;&nbsp;<?php print $keyword ;?></td>
    </tr>
    <?php  
    $res->MoveNext();
    }//end of while loop
    ?>
    </TBODY>    
</table>
</div>
<?php
}

/**
 * This function adds spaces to the item catalogue table according to the level it exists
 * @access private
 * @return void
 */
function _shn_cs_add_spaces_to_table($cat_id)
{
    require_once('lib_cs.inc');
    $level = shn_cs_get_level_count($cat_id);
	for($i=0;$i<$level;$i++)
	{
	$space_string .= '&nbsp;&nbsp;&nbsp;&nbsp;';
	}
    print $space_string;
}

/**
 * This function shows the edit form for Catalogue/ Item. Submit the result to shn_cs_edit_cat_form_submit() in main.inc.
 * Called by shn_cs_edit_cat_select_submit() in main.inc
 * process POST data submited by show_item_cat_table() in edit.inc
 * @access private
 * @return void
 */

function _shn_cs_edit_cat_select_submit_result()
{
    ?>
    <p><?= _('<b>Using Delete, you will lose all the records of the particular catalogues, Items, Unit or Unit Types.</b> By deleting a catalogue You will lose all the entries under the particular catalogue'); ?></p>
    <?php
    global $global;
    $db=$global["db"];

    $id = trim($_REQUEST['id']);

    $query="select name,description from ct_catalogue where ct_uuid='$id' ";
    $res=$db->Execute($query);

    $name=$res->fields["name"];
    $description=$res->fields["description"];

    $form_opts['name']="edit_form";
    $extra_opts['req']=true;
    shn_form_fopen('edit_cat_form_submit',null,$form_opts);
    shn_form_fsopen(_('Details Of the catalogue/Item'));
    $extra_opts['value']=$name;
    shn_form_text(_("Catalogue / Item Name   : "),'item_cat_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    $extra_opts['value']=$description;
    shn_form_text(_("Description   : "),'description','size="50"',$extra_opts);
    shn_form_fsclose();

    shn_form_hidden(array('id' => $id));

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    
    shn_form_button(_("Close"),"onClick='shn_cs_edit_cat_select_submit_result_js(\"close\")'",$extra_opts);
    shn_form_button(_("Save"),"onClick='shn_cs_edit_cat_select_submit_result_js(\"edit\")'",$extra_opts);
    shn_form_button(_("Delete"),"onClick='shn_cs_edit_cat_select_submit_result_js(\"del\")'",$extra_opts);

    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php
    shn_form_fclose();

    shn_cs_edit_cat_select_submit_result_js();
}


/**
 * This function does the action specified by the button.
 * Called by shn_cs_edit_cat_form_submit() in main.inc
 * process POST data submited by _shn_cs_edit_cat_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
function _shn_cs_edit_cat_form_submit_result()
{
    global $global;
    $db=$global["db"];

    $action=trim($_POST['action']);

    if($action=='close')
    {
        echo "<h1>Edit closed</h1>";
        shn_cs_edit_form();
    }//end of if

    else if($action=='edit')
    {
        $name = trim($_POST['item_cat_name']);
            $description = trim($_POST['description']);
        $id = trim($_POST['id']);
    
        $query="update ct_catalogue set name='$name' , description='$description' where ct_uuid='$id' ";
        $res=$db->Execute($query);    

        ?>
        <div id="result_msg">
        <?php echo $name." was succesfully Saved.";?>
        </div>
        <?php
        shn_cs_edit_form();
    }//end of else if

    else if($action=='del')
    {

    $id = trim($_POST['id']);
    $inuse_flag_return=item_cat_inuse($id);
        if($inuse_flag_return==true)
        {
        echo "You can not Delete this Catalogue/ Item. Because there sub catalogues/Items under this catalogue OR it has been used by the INVENTORY MANAGEMENT SYSTEM";
        }
        else
        {
        $query="delete from ct_catalogue where ct_uuid='$id' ";
        $res=$db->Execute($query);
        echo "Item/Catalogue was Deleted";
        shn_cs_edit_form();
        }

    }//end of else if

}

function item_cat_inuse($item_cat_id)
{    
    global $global;
    $db=$global["db"];
    $inuse_flag=false;
    
        $query="select * from ct_catalogue where parentid='$item_cat_id' ";
        $res=$db->Execute($query);
        if(!$res==NULL && !$res->EOF)
        {
        $inuse_flag=true;
        }
        if(_shn_ims_find_catalogid($item_cat_id))
        {
        $inuse_flag=true;
        }
return $inuse_flag;
}



/**
 * This function shows the Unit table. Submit the result to shn_cs_edit_cat_select_submit() in main.inc.
 * @access private
 * @return void
 */
function show_unit_table()
{
    global $global;
    $db=$global["db"];

?>
<br>
<div id="result">
<table>
    <thead>
        <td><strong><?=_("Name")?></strong></td>
        <td><strong><?=_("Multiplier")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $query="select * from ct_unit";
    $res=$db->Execute($query);


    while(!$res==NULL && !$res->EOF)
    {
    $name=$res->fields["name"];
    $multiplier=$res->fields["multiplier"];
    $unit_id=$res->fields["unit_uuid"];
    ?>
    <tr>
        <td><a href="index.php?mod=cs&act=edit_unit_select_submit&id=<?php echo $unit_id ?>"><?php print $name ;?></a></td>
        <td><?php print $multiplier ;?></td>
    </tr>
    <?php  
    $res->MoveNext();
    }//end of while loop
    ?>

    </TBODY>
    
</table>
</div>
<?php
}

function _shn_cs_edit_unit_select_submit_result()
{
    global $global;
    $db=$global["db"];

    $id = trim($_REQUEST['id']);

    $query="select * from ct_unit where unit_uuid='$id' ";
    $res=$db->Execute($query);

    $name=$res->fields["name"];
    $multiplier=$res->fields["multiplier"];
    $base_flag=$res->fields["base_flag"];

    $form_opts['name']="edit_form";
    $extra_opts['req']=true;
    shn_form_fopen('edit_unit_form_submit',null,$form_opts);
    shn_form_fsopen(_('Details Of the Unit'));
    $extra_opts['value']=$name;
    shn_form_text(_("Unit Name   : "),'unit_name','size="50"',$extra_opts);
    //$extra_opts['value']=$multiplier;
    if($base_flag=='1')
    {
        shn_form_text(_("Multiplier   : "),'multiplier','size="50" readonly=true',array('req'=>'true','value'=>$multiplier,'help'=>_('Specify the multiplier of the particular unit to the base unit of the unit type')));
    }
    else
    {
        shn_form_text(_("Multiplier   : "),'multiplier','size="50"',array('req'=>'true','value'=>$multiplier,'help'=>_('Specify the multiplier of the particular unit to the base unit of the unit type')));
    }
    shn_form_fsclose();
    
    $parent_id_array=array('id' => $id);
    shn_form_hidden($parent_id_array);

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;

    shn_form_button(_("Close"),"onClick='change_action(\"close\")'",$extra_opts);
    shn_form_button(_("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_button(_("Delete"),"onClick='change_action(\"del\")'",$extra_opts);

    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php

    shn_form_fclose();
}

function _shn_cs_edit_unit_form_submit_result()
{
    global $global;
    $db=$global["db"];

    $action=trim($_POST['action']);

    if($action=='close')
    {
        echo "<h1>Edit closed</h1>";
        shn_cs_edit_form();
    }//end of if

    else if($action=='edit')
    {
        echo "<h1>Unit Saved</h1>";
        $name = trim($_POST['unit_name']);
            $multiplier = trim($_POST['multiplier']);
        $id = trim($_POST['id']);
    
        $query="update ct_unit set name='$name' , multiplier=$multiplier where unit_uuid='$id' ";
        $res=$db->Execute($query);    

        ?>
        <div id="result_msg">
        <?php echo $name." was succesfully Saved.";?>
        </div>
        <?php
    }//end of else if

    else if($action=='del')
    {
        $id = trim($_POST['id']);
    $inuse_flag_return=unit_inuse($id);
        if($inuse_flag_return==true)
        {
        echo "You can not Delete this Unit. Because it has been used in INVENTORY MANAGEMENT SYSTEM.";
        }
        else
        {
        $query="delete from ct_unit where unit_uuid='$id' ";
        $res=$db->Execute($query);
        echo "Item/Catalogue was Deleted";
        }
    }//end of else if
}

function unit_inuse($unit_id_input)
{
    $inuse_flag=false;
        if(_shn_ims_find_unitid($unit_id_input))
        {
        $inuse_flag=true;
        }
return $inuse_flag;
}

function show_unit_type_table()
{
    global $global;
    $db=$global["db"];

?>
<br>
<div id="result">
<table>
    <thead>
        <td><strong><?=_("Name")?></strong></td>
        <td><strong><?=_("Description")?></strong></td>
    </thead>
    <TBODY>
    <?php

    $query="select * from ct_unit_type";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $name=$res->fields["name"];
    $description=$res->fields["description"];
    $unit_type_id=$res->fields["unit_type_uuid"];
    ?>
    <tr>
        <td><a href="index.php?mod=cs&act=edit_unittype_select_submit&id=<?php echo $unit_type_id ?>"><?php print $name ;?></a></td>
        <td><?php print $description ;?></td>
    </tr>
    <?php  
    $res->MoveNext();
    }//end of while loop
    ?>

    </TBODY>
    
</table>
</div>
<?php
}


function _shn_cs_edit_unittype_select_submit_result()
{
    global $global;
    $db=$global["db"];

    $id = trim($_REQUEST['id']);

    $query="select name,description from ct_unit_type where unit_type_uuid='$id' ";
    $res=$db->Execute($query);

    $name=$res->fields["name"];
    $description=$res->fields["description"];

    $form_opts['name']="edit_form";
    $extra_opts['req']=true;
    shn_form_fopen('edit_unit_type_form_submit',null,$form_opts);
    shn_form_fsopen(_('Details Of the Unit Type'));
    $extra_opts['value']=$name;
    shn_form_text(_("Unit Type Name   : "),'unit_type_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    $extra_opts['value']=$description;
    shn_form_text(_("Description   : "),'description','size="50"',$extra_opts);
    shn_form_fsclose();
    
    $parent_id_array=array('id' => $id);
    shn_form_hidden($parent_id_array);

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_("Close"),"onClick='change_action(\"close\")'",$extra_opts);
    shn_form_button(_("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    //shn_form_button(_("Delete"),"onClick='change_action(\"del\")'");

    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php

    shn_form_fclose();

}

function _shn_cs_edit_unit_type_form_submit_result()
{
    global $global;
    $db=$global["db"];

    $action=trim($_POST['action']);

    if($action=='close')
    {
        echo "<h1>Edit closed</h1>";
        shn_cs_edit_form();
    }//end of if

    else if($action=='edit')
    {
        echo "<h1>Unit Type Saved</h1>";
        $name = trim($_POST['unit_type_name']);
            $description = trim($_POST['description']);
        $id = trim($_POST['id']);
    
        $query="update ct_unit_type set name='$name' , description='$description' where unit_type_uuid='$id' ";
        $res=$db->Execute($query);    

        ?>
        <div id="result_msg">
        <?php echo $name." was succesfully Saved.";?>
        </div>
        <?php
    }//end of else if

    else if($action=='del')
    {
    echo "<h1>Delete Unit Type Under Construction</h1>";
    }//end of else if

}
?>

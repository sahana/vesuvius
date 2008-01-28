
<?php
/**
 * Edit  
 * PHP version 4 and 5
 * @author      thinesh Thusinthaka
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage service
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function _shn_service_edit_cat_select_submit_result()
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

/**
 * This function does the action specified by the button.
 * Called by shn_service_edit_cat_form_submit() in main.inc
 * process POST data submited by _shn_service_edit_cat_select_submit_result() in edit.inc
 * @access private
 * @return void
 */
 
function _shn_service_edit_cat_form_submit_result()
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
    
    //    $query="update ct_catalogue set name='$name' , description='$description' where ct_uuid='$id' ";
         $query="update config_altered set confkey='$name' , value='$description' where value='$_POST[id]' and confkey='$_POST[confkey]' IN (update config values confkey='$name' , value='$description') ";
     
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

        $query2="delete from ct_cat_unit where ct_uuid='$id' ";
        $res2=$db->Execute($query2);
	?>
	<div id="result_msg">
        <?php print "Item/Catalogue was Deleted";?>
	</div>
	<br>
	<?php
        shn_cs_edit_form();
        }

    }//end of else if
}


function item_cat_inuse($item_cat_id)
{    
    global $global;
    $db=$global["db"];
    $inuse_flag=false;
    
        $query="select * from config where confkey='$item_cat_id' ";
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
 * This function shows the Unit table. Submit the result to shn_service_edit_cat_select_submit() in main.inc.
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
    $query="select * from config_altered";
    $res=$db->Execute($query);


    while(!$res==NULL && !$res->EOF)
    {
    $name=$res->fields["module_id"];
    $multiplier=$res->fields["confkey"];
    $unit_id=$res->fields["value"];
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

        ?>
        <div id="result_msg">
        <?php echo "The unit was Deleted";?>
        </div>
        <?php
        
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
<script type="text/javascript">
    function changeform()
    {
    var x=document.select_edit_type_form.edit_type.options[document.select_edit_type_form.edit_type.selectedIndex].value;
    if(x!='none')
        {
        document.select_edit_type_form.submit();
        }
    }
</script>
<?php

?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.edit_form.submit();
         return;
    }
</script>

<?php

?>



<?php   
function _shn_service_edit_cat_select_submit_result()
{
    global $global;
    $db=$global["db"];

    	$action=trim($_POST['action']);

    if($action=='close')
    {
        echo "<h1>Save Feed</h1>";
        shn_service_edit_form();
    }//end of if

    else if($action=='edit')
    {
        $name = trim($_POST['item_cat_name']);
            $description = trim($_POST['description']);
        $id = trim($_POST['description']);
    
    echo "testing id".$id;
	//echo "testing id  $_POST['item_cat_name']";

//$query="update config_altered_altered set confkey";    
     $query="update config_altered set confkey='$name' , value='$description' where value='$_POST[id]' and confkey='$_POST[confkey]'";
        $res=$db->Execute($query);    
        ?>
        <div id="result_msg">
        <?php echo $name." was succesfully Saved.";?>
        </div>
        <?php
        shn_service_edit_form();
    }//end of else if
}


function shn_service_edit_form()
{
    $option_array=array('none' => '-----Select -----','Item' => 'WMS_Feed','Unit' => 'GeoRSS feed','Unit_types'=>'WFS feed');
    $form_opts['name']="select_edit_type_form";
    shn_form_fopen('edit_form_submit',null,$form_opts);
    shn_form_fsopen(_t('Select Category'));
    $select_opts='onChange="changeform()"';
    shn_form_select($option_array,'','edit_type',$select_opts,null);
    shn_form_fsclose();
    shn_form_fclose();
}     


function show_item_cat_table()
{  
 global $global;
 $db=$global["db"];
?>
<br>
<div id="result">
<table>
    <thead>
        <td><strong><?=_t("Feed Confkey")?></strong></td>
        <!--<td><strong><?=_t("Description")?></strong></td> -->
        <td><strong><?=_t("modulename")?></strong></td>
	<td><strong><?=_t("Value")?></strong></td>
    </thead>
    <TBODY>
    
    <?php    
//config table altered from the field_options
    $query="select * from config_altered";
    $res=$db->Execute($query);

    while(!$res==NULL && !$res->EOF)
    {
    $name=$res->fields["confkey"];
//  $description=$res->fields["value"];
    $cat_id=$res->fields["value"];
    $final_flag=$res->fields["module_id"];
    $visiblity=$res->fields["visibility"];
    ?>
    <tr>
    
  <?php
  
  
if (true) //when the user is the admin
{ 
	$visiblity==1;
//  when the user click on the record and moves to the next page,
// there you get the button to set visibility.	
}  
  
    
    	if($visiblity) /*change this with session variables and $visibiilty*/ 	{
    		?>
        <td><a href="index.php?mod=service&act=edit_cat_select_submit&id=<?php echo $cat_id ?>&confkey=<?php echo $name?>&module_id=<?php echo $final_flag ?>"><?php echo $name?></a></td>
        <? } else { 
        	echo "<td> $name</td>";
        }?>
        <?php if($final_flag=='0') { ?>
            <td><?php print "$name" ; ?></td>
        <?php } else { ?>
            <td><?php print "$final_flag" ; ?></td>
        <?php } ?>
           <td><?php print "$cat_id" ;?></td>
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


function _shn_service_show_cat()
{
    ?>
    <p><?= _t('<b>Using Delete, you will lose all the records of the particular catalogues, Items, Unit or Unit Types.</b> By deleting a catalogue You will lose all the entries under the particular catalogue'); ?></p>
    <?php
    global $global;
    $db=$global["db"];

    $id = trim($_REQUEST['id']);

    $query="select * from config_altered where value='$id' ";
   	  

   	         
    $res=$db->Execute($query);

    $name=$res->fields["confkey"];
    $description=$res->fields["value"];
    $visiblity=$res->fields["visibility"];


    $form_opts['name']="edit_form";
    $extra_opts['req']=true;
    shn_form_fopen('edit_cat_form_submit',null,$form_opts);
    shn_form_fsopen(_t('Details Of the catalogue/Item'));
    $extra_opts['value']=$name;
    shn_form_text(_t("Catalogue / Item Name   : "),'item_cat_name','size="50"',$extra_opts);
    $extra_opts['req']=false;
    $extra_opts['value']=$description;
    shn_form_text(_t("Description   : "),'description','size="50"',$extra_opts);
    shn_form_fsclose();


//hidden field set of id transfering
    shn_form_hidden(array('id' => $id));
    //hidden field also set for confkey
    shn_form_hidden(array('confkey'=>$name))

    ?>
    <br />
    <center>
    <?php
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    
    shn_form_button(_t("Close"),"onClick='change_action(\"close\")'",$extra_opts);
    shn_form_button(_t("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='change_action(\"del\")'",$extra_opts);
    
//shn_form_button(_t("New Feeds"),"onClick='change_action(\"NewFeed\")'",$extra_opts);
	$shn_session_admin=0;
//get the sesions details from login 4 admin and alter the shn_session_details to ->1 	
//    if($shn_session_admin==1)
//    {
    	
    if($visiblity==0)
	shn_form_button(_t("Set Visibility"),"onClick='change_action(\"visible\")'",$extra_opts);
	else		
	shn_form_button(_t("Non Visible"),"onClick='change_action(\"visible\")'",$extra_opts);
//visibility factor of admin is set with $visibility variable set here as given     
//}
	
    shn_form_hidden(array('action'=>'0'));
    ?>
    </center>
    <br />
    <?php

    shn_form_fclose();	
}



//function repeated 2 update database entries which are existing
function _shn_cs_edit_cat_select_submit_result()
{
    global $global;
    $db=$global["db"];

    	$action=trim($_POST['action']);

    if($action=='close')
    {
        echo "<h1>Edit closed</h1>";
        shn_service_edit_form();
    }//end of if

    else if($action=='edit')
    {
        $name = trim($_POST['item_cat_name']);
            $description = trim($_POST['description']);
        $id = trim($_POST['description']);
    
    //echo "testing id".$id;
	//echo "testing id  $_POST['item_cat_name']";

    
    $query="update config_altered set confkey='$name' , value='$description' where value='$_POST[id]' and confkey='$_POST[confkey]' IN (update config values confkey='$name' , value='$description') ";
    
        $res=$db->Execute($query);    
        ?>
        <div id="result_msg">
        <?php echo $name." was succesfully Saved.";?>
        </div>
        <?php
        shn_service_edit_form();
    }//end of else if

    else if($action=='del')
    {//'id' here has 2 be changed to d	escription
    
    $id = trim($_POST['id']);
  echo " id paased here $id";
  
  
    $inuse_flag_return=item_cat_inuse($id);
        if($inuse_flag_return==true)
        {
        echo "You can not Delete this Catalogue/Feed.There are data under this is";
        }
        else
        {
        $query="delete from config_altered where value='$_POST[id]' and confkey='$_POST[confkey]'";
        echo $query;
        
        $res=$db->Execute($query);

	echo "The selection for delete=+ 'id'   ";	  
	?>  
	
	<div id="result_msg">
        <?php print "FeedKey was Deleted";?>
	</div>
	<br>
	<?php
        shn_service_edit_form();
        }
    }//end of else if

/*
//THIS IS for new Feed addition function altered for acess
elseif ($action=='NewFeed') {
	$name = trim($_POST['item_cat_name']);
    $description = trim($_POST['description']);
	
	$query="INSERT INTO `sahana`.`config_altered` (
`module_id` ,
`confkey` ,
`value` ,
`confkeyID` ,
`visibility`
)
VALUES ('$_POST[]','$_POST[]','$_POST[]','$_POST[]','$_POST[]'";	
};

*/


    else if($action=="visible")	{
    	$query="select * from config_altered";
    	$res=$db->Execute($query);
    	$visiblity=$res->fields["visibility"];
    	echo "The visibility ".$visiblity;
    	if($visiblity==1)
    		{
    			$query="update config_altered set visibility=0 where value='$_POST[id]' and confkey='$_POST[confkey]'";
       			$res=$db->Execute($query);
       			echo $query;
    		}
    	else
    		{
    		$query="update config_altered set visibility=1 where value='$_POST[id]' and confkey='$_POST[confkey]'";
       		$res=$db->Execute($query);
       		echo "$query";			  
    		}
    	shn_service_edit_form();
    }
}


//similar to function edit.inc
function item_cat_inuse($item_cat_id)
{    
    global $global;
    $db=$global["db"];
    $inuse_flag=false;
    
        $query="select * from config_altered where confkey='$item_cat_id' ";
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


//for mod_sevice deletion of feed selected
function _shn_ims_find_catalogid($catalog_id)
{
    global $global;
    $db=$global["db"];
    $catalog_found=false;
    $sql1="SELECT item_id FROM ims_item_records WHERE catalog_id='$catalog_id';";
    $ims1=$db->Execute($sql1);
    $item_id=$ims1->fields['item_id'];
        
                    
    $sql2="SELECT inv_id FROM ims_reorder_level WHERE catalog_id='$catalog_id';";
    $ims2=$db->Execute($sql2);
    $inv_id=$ims2->fields['inv_id'];

    if($item_id!=null || $inv_id!=null)
    {
        $catalog_found=true;
    }
    else
    {
        $catalog_found=false;
    }

    return $catalog_found;
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

<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.edit_form.submit();
         return;
    }
</script>


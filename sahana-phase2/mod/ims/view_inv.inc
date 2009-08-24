<?php
/** View ,Edit forms for Inventories of the Inventory Management System 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
	      Mahesh Kaluarachchi <mahesh@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage ims
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_errors.inc";
require_once $global['approot']."/inc/lib_location.inc";

include_once "lib_ims.inc";

function _shn_ims_viewform_allorg($no=NULL,$page_number=NULL,$Limit=NULL)
{
	$form_opts['name']="view_inv";
	shn_form_fopen("reg_inv_actions",null,$form_opts);
	shn_form_fsopen(_t("Register a New Inventory"));
	$extra_opts['br']=false;
        $extra_opts['req']=false;
	shn_form_button(_t("Add Inventory"),"onClick='change_action(\"addinventory\")'",$extra_opts);
	//shn_form_submit(_t("Add Inventory"));
	shn_form_fsclose();

    global $global;
    $db=$global['db'];

    //$Limit=20;
    print '<b>';
    shn_form_text(_t("Records Per Page : "),'records','onChange="submit(this);"',array('value'=>$Limit));
    print '</b>';
    shn_form_hidden(array('action'=>'0'));
	
    if($page_number!=0)
    {
	$page_number=($page_number-1)*$Limit;
    }
    else 
    {
	$page_number=0;
    }

    $sql="SELECT * FROM ims_inventory_records ORDER BY inventory_name;";

    $SearchResult=mysql_query($sql) or die(mysql_error()); 
	$NumberOfResults=mysql_num_rows($SearchResult); 
	
	$NumberOfPages=ceil($NumberOfResults/$Limit); 
	 print '<b>';
	print(_t("Go to Page : "));
	
	for($i=1;$i<$NumberOfPages+1;$i++)
	{
		
	    ?><a href="index.php?mod=ims&act=inventory_paging&$i=<?php echo $i;?>&$Limit=<?php echo $Limit;?>"><?php print ($i." ");?></a><?php
	    print "\n";
	}
	 print '</b>';
?>
<div id ="result">
	<table>
        <thead>
            <td><?=_t("Inventory Name")?></td>
            <td><?=_t("Country of Origin/GIS")?></td> 
            <td><?=_t("Address")?></td>
            <td><?=_t("Contact Numbers")?></td>
            <td><?=_t("Man Power")?></td>
            <td><?=_t("Equipment")?></td>
            <td><?=_t("Other <br /> Facilities")?></td>
	    <td><?=_t("Inventory Space")?></td>
	    <td><?=_t("Actions")?></td>
        </thead>
        <tbody>
<?php
    if($no==NULL){
        $q = "SELECT inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space FROM  ims_inventory_records WHERE parent_id=0 ORDER BY inventory_name LIMIT $page_number,$Limit";
        $res_org=$db->Execute($q);
    }else {
        $q = "SELECT inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space FROM  ims_inventory_records WHERE parent_id=0 ORDER BY inv_uuid desc";
        $res_org=$db->SelectLimit($q,$no);
    }

    while(!$res_org==NULL && !$res_org->EOF){
        $org_id=$res_org->fields[0];
        if($org_id!=NULL){
        _shn_display_org($flag=true,$org_id);
        $q = "SELECT inv_uuid FROM  ims_inventory_records WHERE parent_id='{$org_id}' ORDER BY name";
        $res_operation=$db->Execute($q);
        while(!$res_operation==NULL && !$res_operation->EOF){
            $operation_id=$res_operation->fields[0];
            _shn_display_org($flag=true,$operation_id);
            $res_operation->MoveNext();
        }
        }
        $res_org->MoveNext();
    }
?>
   </tbody>
  </table>
</div>
<?php
	shn_form_fclose();
}

function _shn_display_org($flag,$org_id,$indent=true,$edit=false)
{
    global $global;
    
    $db=$global["db"];
    $q = "SELECT inv_uuid,parent_id,inventory_name,man_power,equipment,resources,space FROM  ims_inventory_records WHERE inv_uuid='{$org_id}'";
    $res_org=$db->Execute($q);

    $org_id=$res_org->fields[0];
    
    if($org_id==NULL)
    {
	;
    }
    else
    {
            
    $q = "SELECT address FROM location_details WHERE poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $q="SELECT search_id FROM location_details,location WHERE poc_uuid='{$org_id}' AND location_details.location_id=location.location_id";
    //$res_temp=$db->Execute($q);
	//print $q;
    $loc=$res_temp->fields[0][0];
    $q="SELECT name FROM location WHERE location_id='{$loc}'";
    //$res_bsd_country=$db->Execute($q);
	
    $q = "SELECT option_description FROM field_options,ims_inventory_records WHERE o_uuid='{$org_id}' AND
field_options.option_code=ims_inventory_records.inventory_type AND field_options.field_name='inventory_type'";
    //$res_type=$db->Execute($q); 
    //$org_type=$res_type->fields[0];
    $q = "SELECT option_description FROM field_options,sector WHERE pgoc_uuid='{$org_id}' AND
field_options.option_code=sector.opt_sector AND field_options.field_name='opt_sector_type'";
    //$res_sector=$db->Execute($q);    
?>
<tr>
    <td>
     <?php
$inv_id=$res_org->fields[0];
    $parent=$res_org->fields[1];
    if($parent>0 && $indent){
        echo "<div id='parent'>";
	
    }
    ?>
    <a href="index.php?mod=ims&act=view_inv&id=<?php echo $res_org->fields[0] ?>"><?php echo $res_org->fields[2]?></a> 
    <?php
    if($parent>0 && $indent){
        echo "</div>";
    }
    ?>
    </td>
<?php
	$location_display=_shn_ims_get_location($inv_id);
?>
    <td><?php print $location_display;?><br><a href="index.php?mod=ims&act=gis_inv&id=<?php echo $res_org->fields[0] ?>"><?php echo "GIS Map";?></a> </td>
   
   <!-- <td><?php echo $res_bsd_country->fields[0]?></td> -->
    <td><?php echo $res_addr->fields[0]?><br /></td>
    <td><?php echo $res_phone->fields[1]?><br /><?php echo $res_mobile->fields[0]?><br/><a href="mailto:<?php echo $res_email->fields[0]?>"/><?php echo $res_email->fields[0]?></a></td>
    <td><?php echo $res_org->fields[3]?></td>
    <td><?php echo $res_org->fields[4]?></td>
    <td><?php echo $res_org->fields[5]?>
    <td><?php echo $res_org->fields[6]?></td>
<?php
    if($flag==true)
    {
?>
    <td><a href="index.php?mod=ims&act=add_item_main_page&inv_id=<?php echo $inv_id?>"><?php print ("Add Item"); ?></a><?php print "   ,"; ?><a href="index.php?mod=ims&act=view_inv&id=<?php echo $res_org->fields[0] ?>"><?php print ("Edit Inventory");?></a></td>
<?php
    }
    else
    {
	;
    }
?>



</tr>
<?php
}
}

function _shn_ims_viewform_org($org_id,$error=false)
{
    include_once "lib_ims.inc";
    global $global;
    $db=$global['db'];
    $q = "SELECT inv_uuid,parent_id,inventory_name,reg_no,man_power,resources,space FROM  ims_inventory_records WHERE inv_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        $parent=($res_org->fields[1]=='0')?true:false;    
        $org_name=$res_org->fields[2];
        
    $q = "SELECT location_id FROM location_details WHERE poc_uuid='{$org_id}'";
    $res_loc=$db->Execute($q);
    $bsd_village=$res_loc->fields[0];
   
    }
    
    $sql = "SELECT * FROM ims_inventory_relation WHERE inv_uuid='{$org_id}'";
    $res=$db->Execute($sql);
    $shel_org = $res->fields['shel_org_flag'];
    $shel_org_id = $res->fields['shel_org_id'];
?>
<h2><?php printf(_t("Inventory Registration Information of <em>%s</em>"),$org_name)?></h2>
<?php
 if($error==true)
        display_errors();
?>
<div id="formcontainer">
<?php
    $form_opts['name']='view';
    $form_opts['req_message']=false;
    shn_form_fopen("view_inv_submit",null,$form_opts);
    shn_form_fsopen(_t('Primary Details'));
    $extra_opts['req']=true;
    $extra_opts['value']=$org_name;
    shn_form_text(_t("Inventory Name : "),'org_name','size="50"', $extra_opts); 
    
    /*************************************************************
    *********************Set Inventory Ownership ******************
    **************************************************************/
    
    //******************
    echo "<br />";
    $destination_array=array('shelter'=>'Shelter','org'=>'Organization');
    shn_form_radio($destination_array,_t('Inventory Ownership : '),'destination','onClick="change_action_des(this.value)"',null);
  
    $opt = _shn_admin_set_option1_javascript();
    
    echo "<br />";
	


//********************* Destination Shelter Display Begin ***********

	echo "<div class='hide' id='des_shelter'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
    	
    shn_form_select(_shn_ims_get_shelter_name(),_t("Owner Shelter : "),'shelter_to','size="1"',array('req'=>true,'help'=>_t('Select the Owner Shelter '), 'value'=>$shel_org_id));
    $destination_type='shelter';
    	//$option_type=array('availability'=>'Availability','confirmation'=>'Confirmation');
    	//shn_form_radio($option_type,_t('Status : '),'file_type',$select_opts,$extra_opts);
    	echo "<br />";
	echo "</div>";
//********************* Destination Shelter display End *************
//********************* Destination Organization Display Begin ******

	echo "<div class='hide' id='des_organization'>";    	
    	$extra_opts['req']  = true;
    	$extra_opts['br']  = true;
    	$select_opts = '';
    	
    shn_form_select(_shn_ims_get_organization_name(),_t("Owner Organization : "),'organization_to','size="1"',array('req'=>true,'help'=>_t('Select the owner Organization Inventory'),'value'=>$shel_org_id));
    
    	echo "<br />";
	echo "</div>";

//********************* Destination Organization Display End ********
    
    /*************************************************************
     *********************Set Inventory Ownership end ************
     *************************************************************/

    //$range=array("start"=>1,"end"=>5);
    
    //shn_location($range,$bsd_village,null);
    shn_form_fsopen(_t("Base Location"));
    //shn_location_form(1,5,$bsd_village);
    shn_location($range,$value=$bsd_village,$parent=null,$extra_opts=null);
    shn_form_fsclose();

    shn_form_fsopen(_t("Contact Information"));
    _shn_ims_display_contact_person($error,true,$org_id);
    shn_form_fsclose();
    shn_form_fsopen(_t("Facilities Available"));
    _shn_ims_display_org_facilities($error,$org_id);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
    $extra_opts['br']=false;
    $extra_opts['req']=false;
    shn_form_button(_t("Close"),"onClick='change_action(\"close\")'",$extra_opts);
	shn_form_button(_t("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_button(_t("Delete"),"onClick='change_action(\"del\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
     shn_form_hidden(array('org_id'=>$org_id));
    shn_form_hidden(array('bsd_village'=>$bsd_village));
    _shn_ims_action_change_javascript("action");
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose();
?>				     
</div>
<?php
} 

function _shn_ims_reg_inv_actions($action)
{
    if($action=='addinventory')
    {
	shn_ims_reg_inv();
    }
    if($action=='0')
    {
	$Limit=trim($_POST['records']);
	if(!is_numeric($Limit))
	{
	    add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
	    display_errors();
	    shn_ims_inventory_paging($Limit=20);
	}
	else if($Limit=='0' || $Limit<0)
	{
	    add_error(SHN_ERR_IMS_AMOUNT_NUMERIC);
	    display_errors();
	    shn_ims_inventory_paging($Limit=20);
	}
	else
	{
	    shn_ims_inventory_paging($Limit);
	}	
    }
}


function _shn_admin_set_option1_javascript()
{
?>
<script type="text/javascript">
    
	
	var url = "index.php?"; 
    var start = 1;
 var http;
    function getHTTPObject() 
    {
        var xmlhttp;
        
        

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();

            } catch (e) {
            xmlhttp = false;
            }
        }

    return xmlhttp;
    }



function handleHttpResponse(){
        if (http.readyState == 4) 
    { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
		
                if (results[0]!="null")
            	{ 
                var x=document.getElementsByName('victim_to');
		
                    for (i=0; i<=x[0].options.length+1; i++)
                    {
                            x[0].options[0]=null;
				
                            }
 		

                j=0;
                for (i=1; i<results.length-1; i=i+2, j++)
                    {
                    
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                            }
                    }
        } 
    }


    function change_action_des(value){
        alert
	
         if(value=='shelter'){         	
         	document.getElementById("des_shelter").style.display='block';  
		//document.getElementById("des_inventory").style.display='none';
		//document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';   	
         }
	 else if(value=='org'){         	
         	document.getElementById("des_organization").style.display='block'; 
		//document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		//document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';    	
         }
	  
         else
	{
             //document.getElementById("des_inventory").style.display='none';
		document.getElementById("des_shelter").style.display='none';
		document.getElementById("des_organization").style.display='none';
		//document.getElementById("des_victim").style.display='none';
	}	
         }

	function add_evacuees(){
		
        	var y=document.getElementsByName("head_name");
		
       		http = getHTTPObject();
        	var url2=url + "act=victims&mod=xst&stream=text&head_name="+y[0].value;
        	//var url2=url + "act=sub_cat&cat=" + selection+"&flag="+item_flag;
        	http.open("GET", url2, true); 
//        	http.onreadystatechange = null; 
        	http.onreadystatechange = function(){}; 
        	http.onreadystatechange = handleHttpResponse; 
        	http.send(null);
        }
</script>

		
<?php
}
?>

<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName('action');
         x[0].value=action;
         document.view_inv.submit();
         return;
    }
</script>

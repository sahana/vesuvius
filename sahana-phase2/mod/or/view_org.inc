<?php
/** View ,Edit forms for Organizations of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_location.inc";

function _shn_or_display_page_links(){
	/*
	$left=$total%5;
	$pages=($total-$left)/5;
	if($left>0){
		$pages=$pages+1;
	}*/
	$pages=$_SESSION["org"]["total_pages"];
	
   	for($i=1;$i<=$pages;$i++){
   			
   	    ?>
    <a href="index.php?mod=or&act=view_page&page=<?php echo $i?>"><?php echo $i?></a> 
    <?php
   }
}

function _shn_or_display_page($page){
	?><h2> Organization Registry</h2><?
	_shn_or_display_page_links();
	?>
    <div id="note">
	<?=_("Your are viewing page no $page ");?>
	</div>
	<?
	_shn_or_display_header();
	/*
	global $global;
	$db=$global["db"];
	$no=$end-($page-1)*5;
	$offset=($page-1)*5;
	$incident=$_SESSION["incidents"];
	$inci=shn_or_create_database_IN_array($incident);
	$q = "select distinct o_uuid,parent_id,name,man_power,equipment,resources from org_main,resource_to_incident where privacy=false and resource_to_incident.x_uuid=org_main.o_uuid and parent_id is NULL and incident_id IN $inci order by o_uuid";
    $res_org=$db->SelectLimit($q,$no,$offset);
    $orgs=array();
    while(!$res_org==NULL && !$res_org->EOF){
    		array_push(
    			$orgs,
    			$res_org->fields["o_uuid"]
    		);
        $res_org->MoveNext();
    }
    */
   $orgs=$_SESSION["org"]["pages"][$page];
    _shn_display_orgs($orgs,true);
    ?>
   </tbody>
  </table>
</div>
<?
}

function _shn_or_display_header()
{
		 ?>
	<br /><br />
    <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Incidents")?></td>
            <td><?=_("Services Provided")?></td>
            <td><?=_("Organization Type")?></td>
          	<td><?=_("Location")?></td>
            <td><?=_("Address")?></td>
            <td><?=_("Contact Numbers")?></td>
        </thead>
        <tbody>
        <?php
}
function _shn_display_orgs($orgs,$root=false)
{
	 global $global;
	 $db=$global['db'];
	 if(empty($orgs)){
	 	?><h2> No Records </h2><?
	 	return;
	 }
	 foreach($orgs as $org_id){
	 	
	 	$sub_orgs=array();
	 	if($root==true){
	  		$org_no=split(",",$org_id);
	 		$org_id=$org_no[1];
	 		_shn_display_org($org_id,$org_no[0]);
	 		
	 	}else{
	    		_shn_display_org($org_id);
	 	}
        $q = "select o_uuid from org_main where parent_id='{$org_id}' order by name";
		$res_org=$db->Execute($q);
		if(!$res_org==NULL && !$res_org->EOF){
			while(!$res_org==NULL && !$res_org->EOF){
    			array_push(
    				$sub_orgs,
    				$res_org->fields["o_uuid"]
    			);
        		$res_org->MoveNext();
    			}
    		_shn_display_orgs($sub_orgs);
		}
	 }
	 $_SESSION["or_rec_no"]=$count;
	  
}
function _shn_or_page_generator($org_list)
{
	
	$total=count($org_list);
	$left=$total%5;
	$pages=($total-$left)/5;
	if($left>0){
		$pages=$pages+1;
	}
	
	$start=0;
   	for($i=1;$i<=$pages;$i++){
   		if((5*$i)<$total){
   			$end=5*$i;
   		}else{
   			$end=$total;
   		}
   		$list=array();
   		for($j=$start;$j<$end;$j++){
   			$list[$j-$start]=($j+1).",".$org_list[$j];
   		}
   		
   	//	array_copy($org_list,$list,$start,$end);
   		$start=$end;
   		$_SESSION["org"]["pages"][$i]=$list;	
    }
    $_SESSION["org"]["total_pages"]=$i-1;

}

function _shn_or_viewform_allorg($org_list)
{
    global $global;
    $db=$global['db'];
	_shn_or_page_generator($org_list);
	_shn_or_display_page(1);

}

function _shn_display_org($org_id,$no=null)
{
    
    global $global;
    $db=$global["db"];
    $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where o_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    $q="select loc_uuid from location,location_details where poc_uuid='{$org_id}' and location_details.location_id=location.loc_uuid";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields["loc_uuid"];
    $q = "select address from location_details where poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);

 	$parent=_shn_or_is_root($org_id);
        if($parent==false){
    //if($no==null){
    		$type="opt_org_sub_type";
    }else{
		$type="opt_org_type";
    }
    $q = "select option_description from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='".$type."'";
    $res_type=$db->Execute($q); 
    $org_type=$res_type->fields['option_description'];
    $q = "select option_description from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
    $res_sector=$db->Execute($q);
    $location=_shn_org_location_string($loc);    
?>
<tr>
	<td><?if ($no!=null){echo $no;}?></td>
    <td>
     <?php
     /*
    $parent=$res_org->fields[1];
    if($parent>0 && $indent){
        echo "<div id='parent'>";
    }*/
    ?>
    <a href="index.php?mod=or&act=edit_org&org_id=<?php echo $org_id ?>"><?php echo $res_org->fields['name']?></a> 
    <?php
    /*
    if($parent>0 && $indent){
        echo "</div>";
    }*/
    ?>
    </td>
     <td>    
    <?php 
    		$incidents=_shn_org_get_incidents($org_id); 
        foreach ($incidents as $i){
        		echo $i[1]."<br />";
        }
    ?>
    <a href="index.php?mod=admin&act=ims_assign&id=<?php echo $res_org->fields["o_uuid"] ?>">Assign to More Incidents</a>
    </td>
    <td>
<?php
    while(!$res_sector->EOF){
        echo $res_sector->fields[0]."<br />";
        $res_sector->MoveNext();
    }
?>
    </td>

    
    <td><?php echo $org_type?></td>
  	<td><?php echo $location?></td>
    <td><?php echo $res_addr->fields[0]?><br /><a href="mailto:<?php echo $res_email->fields[0]?>"/><?php echo $res_email->fields[0]?></a></td>
    <td><?php echo $res_phone->fields[0]?><br /><?php echo $res_mobile->fields[0]?></td>

</tr>
<?php
}

function _shn_or_viewform_org($org_id,$error=false)
{
    include_once "lib_or.inc";
    global $global;
    $db=$global['db'];
    $q = "select o_uuid,parent_id,name,reg_no,man_power,resources from org_main where o_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    if(!$res_org==NULL && !$res_org->EOF){
        $parent=_shn_or_is_root($org_id);    
        $org_name=$res_org->fields["name"];
        $reg_no=$res_org->fields["reg_no"]; 
	
	if($parent==true){
        		$type="opt_org_type";	
        }else{
        		$type="opt_org_sub_type";	
        }
        $q = "select option_code from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='$type'";
	$res_type=$db->Execute($q); 
        $org_type=$res_type->fields["option_code"];
        $q = "select option_code from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
        $res_sector=$db->Execute($q);    
        
        $or_sector_arr=array();
        while(!$res_sector->EOF){
            array_push(
                $or_sector_arr,
                $res_sector->fields[0]
            );       
            $res_sector->MoveNext();
        }
        
        if($parent){
        $q = "select i.incident_id,name from incident as i,resource_to_incident as r where i.incident_id=r.incident_id and r.x_uuid='{$org_id}'";
        $res_incident=$db->Execute($q);    
        $or_incident_arr=array();
        
        while(!$res_incident->EOF){
            array_push(
                $or_incident_arr,
                $res_incident->fields["incident_id"]
            );       
            $res_incident->MoveNext();
        }  
        }
        
    $q = "select location_id from location_details where poc_uuid='{$org_id}'";
    
    $res_loc=$db->Execute($q);
    if(!$res_loc==NULL && !$res_loc->EOF){
    		$loc=$res_loc->fields["location_id"];
    }else{
    		$loc=-1;
    }

    }
?>
<h2><?=_("Organization Registration Information of <em>").$org_name?></em></h2>
<?php
 if($error==true)
        display_errors();
?>
<?php
    $form_opts['name']='view';
    $form_opts['req_message']=false;
    shn_form_fopen("view_org_submit",null,$form_opts);
    shn_form_fsopen(_('Primary Details'));
    $extra_opts['req']=true;
    $extra_opts['value']=$org_name;
    shn_form_text(_("Organization Name : "),'org_name','size="50"', $extra_opts); 
    if($parent){
        shn_form_text(_("Registration Number : "),'reg_no','size="50"',array('value'=>$reg_no)); 
    }
    shn_form_fsclose();
    
     if($parent){
     	shn_form_fsopen(_("Incidents related to the Organization"));
    		_shn_or_display_incident($error,true,$or_incident_arr);
    		shn_form_fsclose();
     }
     
    shn_form_fsopen(_("Organization Type"));
    if($parent){
    	_shn_or_display_org_type($error,false,$org_type);
    }else{
    	_shn_or_display_org_sub_type($error,false,$org_type);
	}    
    shn_form_fsclose();
    shn_form_fsopen(_("Organization Sector"));
    _shn_or_display_sector($error,$or_sector_arr);
    shn_form_fsclose();
    shn_form_fsopen("Base Location");
    $range= shn_or_get_loc_range();
    if($loc==-1){
    			shn_location($range,null,null,true);
    }else{
    			shn_location($range,$loc,null,true);	
    }
     
    shn_form_fsclose();
    shn_form_fsopen(_("Contact Information"));
    _shn_or_display_contact_person($error,false,$org_id);
    shn_form_fsclose();
    shn_form_fsopen(_("Facilities Avaliable"));
    _shn_or_display_org_facilities($error,false,$org_id);
    shn_form_fsclose();
?>
<br />
<center>
<?php
//create the submit button
	$extra_opts['br']=false;
	$extra_opts['req']=false;
    shn_form_button(_("Close"),"onClick='change_action(\"close\")'",$extra_opts);
	shn_form_button(_("Save"),"onClick='change_action(\"edit\")'",$extra_opts);
    shn_form_button(_("Delete"),"onClick='change_action(\"del\")'",$extra_opts);
    shn_form_hidden(array('action'=>'0'));
     shn_form_hidden(array('org_id'=>$org_id));
    _shn_or_action_change_javascript("action","edit");
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose(false);
?>				     

<?php
} 

function _shn_or_viewform_latest_orgs($no=NULL)
{
    global $global;
    $db=$global['db'];
?>
<div id ="result">
	<table>
        <thead>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Incidents")?></td>
            <td><?=_("Services Provided")?></td>
            <td><?=_("Organization Type")?></td>
            <td><?=_("Location")?></td>
            <td><?=_("Address")?></td>
            <td><?=_("Contact Numbers")?></td>
        </thead>
        <tbody>
<?php
    if($no==NULL){
        $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where parent_id is NULL order by name";
        $res_org=$db->Execute($q);
    }else {
        $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where parent_id is NULL order by o_uuid desc";
        $res_org=$db->SelectLimit($q,$no);
    }
   
    while(!$res_org==NULL && !$res_org->EOF){
        $org_id=$res_org->fields["o_uuid"];
        if($org_id!='0'){
        		_shn_display_latest_orgs($org_id);
        		$q = "select o_uuid from org_main where parent_id='{$org_id}' order by name";
        		$res_operation=$db->Execute($q);
        		while(!$res_operation==NULL && !$res_operation->EOF){
            		$operation_id=$res_operation->fields["o_uuid"];
            		_shn_display_latest_orgs($operation_id,true);
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
}

function _shn_display_latest_orgs($org_id,$indent=false,$edit=false)
{
    global $global;
    $db=$global["db"];
    $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where o_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    $org_id=$res_org->fields["o_uuid"];
    $q = "select address from location_details where poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    $q="select loc_uuid from location,location_details where poc_uuid='{$org_id}' and location_details.location_id=location.loc_uuid";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields["loc_uuid"];
    $q = "select option_description from field_options,org_main where o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='opt_org_type'";
    $res_type=$db->Execute($q); 
    $org_type=$res_type->fields[0];
    $q = "select option_description from field_options,sector where pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
    $res_sector=$db->Execute($q);    
?>
<tr>
    <td>
     <?php
    $parent=$res_org->fields["name"];
    if($indent==true){
    	?>
 <a href="index.php?mod=or&act=edit_org&org_id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo "--->".$res_org->fields["name"]?></a>
<?
    }else{
    ?>
    <a href="index.php?mod=or&act=edit_org&org_id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo $res_org->fields["name"]?></a> 
    <?php
    }
    ?>
    </td>
    <td>
    
    <?php 
    		$incidents=_shn_org_get_incidents($org_id); 
        foreach ($incidents as $i){
        		echo $i[1]."<br />";
        }
    ?>
    <a href="index.php?mod=admin&act=ims_assign&id=<?php echo $res_org->fields["o_uuid"] ?>">Assign to More Incidents</a>
    </td>
    <td>
<?php
    while(!$res_sector->EOF){
        echo $res_sector->fields[0]."<br />";
        $res_sector->MoveNext();
    }
    $location=_shn_org_location_string($loc);
?>
    </td>
    <td><?php echo $org_type?></td>
    <td><?php echo $location?></td>
    <td><?php echo $res_addr->fields[0]?><br /><a href="mailto:<?php echo $res_email->fields[0]?>"/><?php echo $res_email->fields[0]?></a></td>
    <td><?php echo $res_phone->fields[0]?><br /><?php echo $res_mobile->fields[0]?></td>

</tr>
<?php
}

?>

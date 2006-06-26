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

function _shn_or_display_page_links($total){
	
	$left=$total%5;
	$pages=($total-$left)/5;
	if($left>0){
		$pages=$pages+1;
	}
	
	;
   	for($i=1;$i<=$pages;$i++){
   		if((5*$i)<$total){
   			$end=5*$i;
   		}else{
   			$end=$total;
   		}
   		
   	    ?>
    <a href="index.php?mod=or&act=view_page&page=<?php echo $i?>&end=<?php echo $end?>"><?php echo $i?></a> 
    <?php
   }
}

function _shn_or_display_page($page,$end){

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
   
    _shn_display_orgs($orgs,true);
}

function _shn_display_orgs($orgs,$root=false)
{
	 global $global;
	 $db=$global['db'];
	
	 foreach($orgs as $org_id){
	 	$sub_orgs=array();
	 	if($root==true){
	 		$no=_shn_org_position($org_id,$_SESSION["incidents"],true);
	 		_shn_display_org($org_id,$no);
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
	  
}

function _shn_or_viewform_allorg($page=1,$end=NULL)
{
    global $global;
    $db=$global['db'];
    ?>
    <div id="note">
	<?=_("Your are viewing page no $page ");?>
	</div>
	<?
	
	$total=shn_or_org_count($_SESSION["incidents"]);
	if($page==1){
		if($total<5){
			$end=$total;
		}else{
			$end=5;
		}
	}
	 _shn_or_display_page_links($total);
	 ?>
	<br /><br />
    <div id ="result">
	<table>
        <thead>
        		<td></td>
            <td><?=_("Organization Name")?></td>
            <td><?=_("Services Provided")?></td>
            <td><?=_("Organization Type")?></td>
          <!--  <td><?//=_("Country of Origin")?></td>-->
            <td><?=_("Address")?></td>
            <td><?=_("Contact Numbers")?></td>
            <td><?=_("Man Power")?></td>
            <td><?=_("Equipment")?></td>
            <td><?=_("Other <br /> Facilities")?></td>
        </thead>
        <tbody>
<?php
	
	_shn_or_display_page($page,$end);
?>
   </tbody>
  </table>
</div>
<?
}

function _shn_display_org($org_id,$no=null)
{
    global $global;
    $db=$global["db"];
    $q = "select o_uuid,parent_id,name,man_power,equipment,resources from org_main where o_uuid='{$org_id}'";
    $res_org=$db->Execute($q);
    
    $q = "select address from location_details where poc_uuid='{$org_id}'";
    $res_addr=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
    $res_phone=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
    $res_mobile=$db->Execute($q);
    $q = "select contact_value from contact where pgoc_uuid='{$org_id}' and opt_contact_type='email'";
    $res_email=$db->Execute($q);
    /*
    $q="select search_id from location_details,location where poc_uuid='{$org_id}' and location_details.location_id=location.location_id";
    $res_temp=$db->Execute($q);
    $loc=$res_temp->fields[0][0];
    $q="select name from location where location_id='{$loc}'";
    $res_bsd_country=$db->Execute($q);
    */
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
    while(!$res_sector->EOF){
        echo $res_sector->fields[0]."<br />";
        $res_sector->MoveNext();
    }
?>
    </td>
    <td><?php echo $org_type?></td>
  <!-- <td><?php// echo $res_bsd_country->fields[0]?></td>-->
    <td><?php echo $res_addr->fields[0]?><br /><a href="mailto:<?php echo $res_email->fields[0]?>"/><?php echo $res_email->fields[0]?></a></td>
    <td><?php echo $res_phone->fields[0]?><br /><?php echo $res_mobile->fields[0]?></td>
    <td><?php echo $res_org->fields[3]?></td>
    <td><?php echo $res_org->fields[4]?></td>
    <td><?php echo $res_org->fields[5]?></td>
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
	var_dump($parent);
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
    _shn_or_display_contact_person($error,true,$org_id);
    shn_form_fsclose();
    shn_form_fsopen(_("Facilities Avaliable"));
    _shn_or_display_org_facilities($error,$org_id);
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
    _shn_or_action_change_javascript("action");
?>
</center>
<br />
<?php
        //close the form
    shn_form_fclose(false);
?>				     

<?php
} 
?>

<?php

/** View ,Edit forms for Organizations of the Organization Registry
 *
 * PHP version 5
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
include_once $global['approot'] . "/inc/lib_form.inc";
include_once $global['approot'] . "/inc/lib_location.inc";

function _shn_or_display_page_links()
{
	/*
	 $left=$total%5;
	 $pages=($total-$left)/5;
	 if($left>0){
		$pages=$pages+1;
		}*/
	$pages = $_SESSION["org"]["total_pages"];
	if ($pages > 1){
		for ($i = 1; $i <= $pages; $i++) {

			?>
<a href="index.php?mod=or&act=view_page&page=<?php echo $i?>"><?php echo $i?></a>
			<?php
}
}
}

function _shn_or_display_page($page)
{
	?>
<h2><?php echo _t('Organization Registry'); ?></h2>
<div><?php 
shn_report_download("shn_or_all_orgs_pdf",_t("Download report as a PDF"));
?></div>
<?php
if (($_SESSION["org"]["total_pages"])<1) {
	?>
<div id="note"><?php echo _t("No organizations have yet been registered.");?></div>
	<?php
	return;
}else{
	_shn_or_display_page_links();
}

?>
<div id="note"><?php echo _t("Your are viewing page number").' '.$page;?></div>
<?php 
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
$orgs = $_SESSION["org"]["pages"][$page];
_shn_display_orgs($orgs,true);
?>
</tbody>
</table>
</div>
<?php
}

function _shn_or_display_header()
{
	?>
<br />
<br />
<div id="result">
<table>
	<thead>
		<td></td>
		<td><?php echo _t("Organization Name")?></td>
		<td><?php echo _t("Incidents")?></td>
		<td><?php echo _t("Services Provided")?></td>
		<td><?php echo _t("Organization Type")?></td>
		<td><?php echo _t("Location")?></td>
		<td><?php echo _t("Address")?></td>
		<td><?php echo _t("Contact Numbers")?></td>
	</thead>
	<tbody>
	<?php
}
function _shn_display_orgs($orgs,$root=false)
{
	global $global;
	$db = $global['db'];
	if (empty($orgs)) {
		echo "<h2>"._t("No Records")."</h2>";
		return;
	}
	foreach ($orgs as $org_id) {

		$sub_orgs = array();
		if ($root == true){
			$org_no = split(",",$org_id);
			$org_id = $org_no[1];
			_shn_display_org($org_id,$org_no[0]);

		}else{
			_shn_display_org($org_id);
		}
		/*
		 $q = "SELECT o_uuid FROM org_main WHERE parent_id='{$org_id}' ORDER BY name";
		 $res_org = $db->Execute($q);
		 if (!$res_org == NULL && !$res_org->EOF) {
		 while (!$res_org==NULL && !$res_org->EOF) {
		 array_push($sub_orgs, $res_org->fields["o_uuid"]);
		 $res_org->MoveNext();
		 }
		 _shn_display_orgs($sub_orgs);
		 }
		 */
	}
	$_SESSION["or_rec_no"] = $count;

}
function _shn_or_page_generator($org_list)
{

	$total = count($org_list);
	$left = $total%5;
	$pages = ($total-$left)/5;
	if ($left > 0) {
		$pages = $pages+1;
	}

	$start = 0;
	for ($i = 1; $i <= $pages; $i++) {
		if ((5*$i) < $total) {
			$end = 5*$i;
		}else{
			$end = $total;
		}
		$list = array();
		for ($j = $start; $j < $end; $j++) {
			$list[$j-$start] = ($j+1).",".$org_list[$j];
		}
			
		//	array_copy($org_list,$list,$start,$end);
		$start = $end;
		$_SESSION["org"]["pages"][$i] = $list;
	}
	$_SESSION["org"]["total_pages"] = $i-1;

}

function _shn_or_viewform_allorg($org_list)
{
	global $global;
	$db=$global['db'];
	_shn_or_page_generator($org_list);
	_shn_or_display_page(1);

}

function _shn_display_org($org_id, $no=null)
{

	global $global;
	$db=$global["db"];
	$q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main WHERE o_uuid='{$org_id}'";
	$res_org=$db->Execute($q);
	$q="SELECT loc_uuid FROM location,location_details WHERE poc_uuid='{$org_id}' AND location_details.location_id=location.loc_uuid";
	$res_temp=$db->Execute($q);
	$loc=$res_temp->fields["loc_uuid"];
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='loc_txt'";
	$res=$db->Execute($q);
	$loc_txt=$res->fields["contact_value"];
	$q = "SELECT address FROM location_details WHERE poc_uuid='{$org_id}'";
	$res_addr=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='curr'";
	$res_phone=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='pmob'";
	$res_mobile=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='email'";
	$res_email=$db->Execute($q);

	$parent = _shn_or_is_root($org_id);
	if ($parent == false) {
		//if($no==null){
		$type = "opt_org_sub_type";
		$parent_node=_shn_or_get_parent($org_id);
		$parent_data_arr=split(":",$parent_node);
		$parent_data=" of <a href='index.php?mod=or&act=edit_org&org_id=".$parent_data_arr[0]."'>".$parent_data_arr[1]."</a>";
	}else{
		$type = "opt_org_type";
	}
	$q = "SELECT option_description FROM field_options,org_main WHERE o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='".$type."'";
	$res_type = $db->Execute($q);
	$org_type = $res_type->fields['option_description'];
	$q = "SELECT option_description FROM field_options,sector WHERE pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
	$res_sector = $db->Execute($q);
	$location = _shn_org_location_string($loc);
	//$location .= "<br />".$loc_txt;
	?>
		<tr>
			<td><?if ($no != null){echo $no;}?></td>
			<td><?php
			/*
			 $parent=$res_org->fields[1];
			 if($parent>0 && $indent){
			 echo "<div id='parent'>";
			 }*/
			?> <a
				href="index.php?mod=or&act=edit_org&org_id=<?php echo $org_id ?>"><?php echo $res_org->fields['name']?></a>
				<?php
				/*
				 if($parent>0 && $indent){
				 echo "</div>";
				 }*/
				?></td>
			<td><?php 
			$incidents = _shn_org_get_incidents($org_id);
			foreach ($incidents as $i) {
				echo $i[1]."<br />";
			}
			?> <a
				href="index.php?mod=admin&act=ims_assign&id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo _t("Assign to more incidents")?></a></td>
			<td><?php
			while (!$res_sector->EOF) {
				echo $res_sector->fields["option_description"]."<br />";
				$res_sector->MoveNext();
			}
			?></td>


			<td><?php echo $org_type.$parent_data; ?></td>
			<td><?php echo $location;?></td>
			<td><?php echo $loc_txt;?><br />
			
			
			<td><a href="mailto:<?php echo $res_email->fields["contact_value"]?>" /><?php echo $res_email->fields["contact_value"]?></a><br />
			<?php echo $res_phone->fields["contact_value"]?><br />
			<?php echo $res_mobile->fields["contact_value"]?></td>


		</tr>
		<?php
}

function _shn_confirm_delete_org($org_id){
	global $global;
	$db = $global['db'];
	$q = "SELECT o_uuid,parent_id,name,reg_no,man_power,resources FROM org_main WHERE o_uuid='{$org_id}'";
	$res_org=$db->Execute($q);
	if(!$res_org==NULL && !$res_org->EOF){
		$parent=_shn_or_is_root($org_id);
		$org_name=$res_org->fields["name"];
		$reg_no=$res_org->fields["reg_no"];
		echo "<h2>"._t("Confirm delete")."</h2>";
		echo "<div class=\"message information\">";
		shn_form_fopen("view_org_submit",null,array('name'=>'confirm_del_form','req_message'=>false));	
		shn_form_hidden(array('action'=>'0'));
		shn_form_hidden(array('org_id'=>$org_id));	
		echo "<p>";
		printf(_t('Are you sure you need to delete the organization %1$s with registration number %2$d'),$org_name,$reg_no);
		echo "</p><br/><center>";
		shn_form_submit(_t("No"),"onClick='change_action(\"exit\")'");
		shn_form_submit(_t("Yes"),"onClick='change_action(\"del\")'");
		echo "</center>";
		_shn_or_action_change_javascript("confirm_del_form","action");
		shn_form_fclose();
		echo "</div>";
	}
}

function _shn_get_org_data($org_id,$no=null)
{

	global $global;
	$db=$global["db"];
	$q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main WHERE o_uuid='{$org_id}'";
	$res_org=$db->Execute($q);
	$q = "SELECT loc_uuid FROM location,location_details WHERE poc_uuid='{$org_id}' and location_details.location_id=location.loc_uuid";
	$res_temp=$db->Execute($q);
	$loc = $res_temp->fields["loc_uuid"];
	//$q = "SELECT address FROM location_details WHERE poc_uuid='{$org_id}'";
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' and opt_contact_type='loc_txt'";
	$res_addr=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' and opt_contact_type='curr'";
	$res_phone=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' and opt_contact_type='pmob'";
	$res_mobile=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' and opt_contact_type='email'";
	$res_email = $db->Execute($q);

	$parent = _shn_or_is_root($org_id);
	if ($parent == false) {
		//if($no==null){
		$type = "opt_org_sub_type";
	}else{
		$type = "opt_org_type";
	}
	$q = "SELECT option_description FROM field_options,org_main WHERE o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type and field_options.field_name='".$type."'";
	$res_type = $db->Execute($q);
	$org_type = $res_type->fields['option_description'];
	$q = "SELECT option_description FROM field_options,sector WHERE pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector and field_options.field_name='opt_sector_type'";
	$res_sector = $db->Execute($q);
	$location = _shn_org_location_string($loc);

	$org_data=array();

	$incidents = _shn_org_get_incidents($org_id);
	foreach ($incidents as $i) {
		$org_data["incidents"] = $org_data["incidents"].",".$i[1];
	}
	$count = 0;
	while (!$res_sector->EOF) {
		//  echo $res_sector->fields[0]."<br />";
		if ($count = 0) {
			$sector=$res_sector->fields[0];
		}else{
			$sector=$sector.",".$res_sector->fields[0];
		}
		$res_sector->MoveNext();
	}
	$org_data["type"]= $org_type;
	$org_data["sector"]= $sector;
	$org_data["location"]=$location;
	$org_data["address"]= $res_addr->fields["contact_value"];
	$org_data["phone"]= $res_phone->fields["contact_value"];
	return $org_data;
}

function _shn_or_viewform_org($org_id, $error=false)
{
	include_once "lib_or.inc";
	global $conf;
	global $global;
	$db = $global['db'];
	$q = "SELECT o_uuid,parent_id,name,reg_no,man_power,resources FROM org_main WHERE o_uuid='{$org_id}'";
	$res_org=$db->Execute($q);
	if(!$res_org==NULL && !$res_org->EOF){
		$parent=_shn_or_is_root($org_id);
		$org_name=$res_org->fields["name"];
		$reg_no=$res_org->fields["reg_no"];
		
		if ($parent == true) {
			$type = "opt_org_type";
		}else{
			$type = "opt_org_sub_type";
		}
		$q = "SELECT option_code FROM field_options,org_main WHERE o_uuid='{$org_id}' and
field_options.option_code=org_main.opt_org_type AND field_options.field_name='$type'";
		$res_type = $db->Execute($q);
		$org_type = $res_type->fields["option_code"];
		$q = "SELECT option_code FROM field_options,sector WHERE pgoc_uuid='{$org_id}' and
field_options.option_code=sector.opt_sector AND field_options.field_name='opt_sector_type'";
		$res_sector=$db->Execute($q);

		$or_sector_arr=array();
		while (!$res_sector->EOF) {
			array_push(
			$or_sector_arr,
			$res_sector->fields[0]
			);
			$res_sector->MoveNext();
		}

		if($parent){
			$q = "SELECT i.incident_id,name FROM incident AS i,resource_to_incident AS r WHERE i.incident_id=r.incident_id AND r.x_uuid='{$org_id}'";
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

		$q = "SELECT location_id FROM location_details WHERE poc_uuid='{$org_id}'";

		$res_loc=$db->Execute($q);
		if(!$res_loc==NULL && !$res_loc->EOF){
			$loc=$res_loc->fields["location_id"];
		}else{
			$loc=-1;
		}
		$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='loc_txt'";
		$res=$db->Execute($q);
		$loc_txt=$res->fields["contact_value"];
        // declare key to return.
        if ($conf['gis']) {
            require_once $global['approot'] . "/inc/lib_gis/gis_fns.inc";
            $keys = array('f_coords' => 1);
            // get keys of features that contain module ref $org_id.
            $gis_result = shn_gis_get_features_item_ref($org_id, $keys);
            // decode from wkt string into array of point(s).
            $coords = shn_gis_coord_decode($gis_result[0]['f_coords']);
            // use centroid point.
            $lat = $coords[0][0];
            $lon = $coords[0][1];
        }
	}
	?>
		<h2><?php echo  _t("Organization Registration Information of ") ?><em><?php echo  $org_name ?></em></h2>
		<?php
		if($error==true)
		display_errors();
		?>
		<?php
		$org_id = isset($org_id)?$org_id:$_SESSION['org']['org_id'];
		
		$form_opts['name']='view';
		$form_opts['req_message']=false;
		shn_form_fopen("view_org_submit",null,$form_opts);
		shn_form_fsopen(_t('Primary Details'));
		?>
		<div class="info"><?php echo  _t("These are the basic details of an organization. Organization name is required ,but registration  no is optional");?></div>
		<br />
		<?php
		$extra_opts['req']=true;
		$extra_opts['value']=isset($org_name)?$org_name:$_SESSION['org']['name'];
		$parent = isset($parent)?$parent:_shn_or_is_root($_SESSION['org']['org_id']);
		shn_form_text(_t("Organization Name : "),'org_name','size="40"', $extra_opts);
		if($parent){
			shn_form_text(_t("Registration Number : "),'reg_no','size="40"',array('value'=>isset($reg_no)?$reg_no:$_SESSION['org']['reg_no']));
		}
		shn_form_fsclose();
		/*
		 if($parent){
		 shn_form_fsopen(_t("Incidents related to the Organization"));
		 _shn_or_display_incident($error,true,$or_incident_arr);
		 shn_form_fsclose();
		 }
		 */
		shn_form_fsopen(_t("Organization Type"));
		if($parent){
			_shn_or_display_org_type($error,false,isset($org_type)?$org_type:$_SESSION['org']['type']);
		}else{
			_shn_or_display_org_sub_type($error,false,isset($org_type)?$org_type:$_SESSION['org']['type']);
		}
		shn_form_fsclose();
		shn_form_fsopen(_t("Organization Sector"));
		_shn_or_display_sector($error,isset($or_sector_arr)?$or_sector_arr:$_SESSION['org']['sector']);
		shn_form_fsclose();
		//$extra_opts["camps"]=true;
		//$extra_opts["org"]=true;
		$extra_opts['req']=false;
		shn_form_fsopen(_t("Base Location"));
		$range= shn_or_get_loc_range();
		
		$loc = isset($loc)?$loc:$_SESSION['org']['loc'];
		
		if($loc==-1){
			shn_location($range,null,null,$extra_opts);
		}else{
			shn_location($range,$loc,null,$extra_opts);
			$extra_opts['value']=isset($loc_txt)?$loc_txt:$_SESSION['org']['loc_txt'];
			shn_form_text(_t("Address"),'loc_txt','size="40"', $extra_opts);
		}
		shn_form_fsclose();


		// Contact infomatio
		shn_form_fsopen(_t("Map Location"));
		$extra_opts['req']=false;
		$lat = isset($lat)?$lat:$_SESSION['org']['lat_edited'];
		$extra_opts['value']= $lat;
		shn_form_text(_t("Latitude : "),'lat_edited','size="40"', $extra_opts);
		$lon = isset($lon)?$lon:$_SESSION['org']['lon_edited'];
		$extra_opts['value'] = $lon;
		shn_form_text(_t("Longitude : "),'lon_edited','size="40"', $extra_opts);
		$extra_opts['br']=false;

		shn_form_button(_t("GIS Map"),"onClick='change_action(\"gis\")'",$extra_opts);
		shn_form_hidden(array('lat'=>$lat));
		shn_form_hidden(array('lon'=>$lon));
		shn_form_fsclose();
		shn_form_fsopen(_t("Contact Information"));
		_shn_or_display_contact_person($error,false,$org_id);
		shn_form_fsclose();
		shn_form_fsopen(_t("Facilities Avaliable"));
		_shn_or_display_org_facilities($error,false,$org_id);
		shn_form_fsclose();
		?>
		<br />
		<center><?php
		//create the submit button
		$extra_opts['br']=false;
		$extra_opts['req']=false;
		shn_form_button(_t("Close"),"onClick='change_action(\"exit\")'",$extra_opts);
		shn_form_button(_t("Edit"),"onClick='change_action(\"confirm_edit\")'",$extra_opts);
		shn_form_button(_t("Delete"),"onClick='change_action(\"confirm_del\")'",$extra_opts);
		shn_form_hidden(array('action'=>'0'));
		shn_form_hidden(array('org_id'=>$org_id));
		// shn_form_hidden(array('org_name'=>$org_name));
		_shn_or_action_change_javascript("view","action");
		?></center>
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

	if($no==NULL){
		$q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main WHERE parent_id is NULL AND privacy=false ORDER BY created desc";
		$res_org=$db->Execute($q);
	}else {
		$q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main WHERE parent_id is NULL AND privacy=false ORDER BY created desc";
		$res_org=$db->SelectLimit($q,$no);
	}
	if(!$res_org==NULL && !$res_org->EOF){
		// dont show the table if there are no records.
		?>
		<div id="result">
		<table>
			<thead>
				<td><?php echo _t("Organization Name")?></td>
				<td><?php echo _t("Incidents")?></td>
				<td><?php echo _t("Services Provided")?></td>
				<td><?php echo _t("Organization Type")?></td>
				<td><?php echo _t("Location")?></td>
				<td><?php echo _t("Address")?></td>
				<td><?php echo _t("Contact Numbers")?></td>
			</thead>
			<tbody>
			<?php
			while(!$res_org==NULL && !$res_org->EOF){
				$org_id=$res_org->fields["o_uuid"];
				if($org_id!='0'){
					_shn_display_latest_orgs($org_id);
					$q = "SELECT o_uuid FROM org_main WHERE parent_id='{$org_id}' ORDER BY name";
					$res_operation=$db->Execute($q);
					while(!$res_operation==NULL && !$res_operation->EOF){
						$operation_id=$res_operation->fields["o_uuid"];
						_shn_display_latest_orgs($operation_id, true, false, $org_id);
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
}

function _shn_display_latest_orgs($org_id, $indent=false, $edit=false, $parent = null)
{
	global $global;
	$db=$global["db"];
	$q = "SELECT o_uuid,parent_id,name,man_power,equipment,resources FROM org_main WHERE o_uuid='{$org_id}'";
	$res_org=$db->Execute($q);
	$org_id=$res_org->fields["o_uuid"];
	$q = "SELECT address FROM location_details WHERE poc_uuid='{$org_id}'";
	$res_addr=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='curr'";
	$res_phone=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='pmob'";
	$res_mobile=$db->Execute($q);
	$q = "SELECT contact_value FROM contact WHERE pgoc_uuid='{$org_id}' AND opt_contact_type='email'";
	$res_email=$db->Execute($q);
	$q="SELECT loc_uuid FROM location,location_details WHERE poc_uuid='{$org_id}' AND location_details.location_id=location.loc_uuid";
	$res_temp=$db->Execute($q);
	$loc=$res_temp->fields["loc_uuid"];
	$q = "SELECT option_description FROM field_options,org_main WHERE o_uuid='{$org_id}' AND
field_options.option_code=org_main.opt_org_type AND field_options.field_name='opt_org_type'";
	$res_type=$db->Execute($q);
	$org_type=$res_type->fields[0];
	$q = "SELECT option_description FROM field_options,sector WHERE pgoc_uuid='{$org_id}' AND
field_options.option_code=sector.opt_sector AND field_options.field_name='opt_sector_type'";
	$res_sector=$db->Execute($q);
	?>
		<tr>
			<td><?php
			if($indent==true){
					$q = "SELECT name FROM org_main WHERE o_uuid='{$parent}'";
					$res_parent =  $db->Execute($q);
					$parent_name = $res_parent->fields["name"];
					$name = $res_org->fields["name"]." Of ". $parent_name;
				?> <a
				href="index.php?mod=or&act=edit_org&org_id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo $name;?></a>
				<?php
			}else{
	?> <a
				href="index.php?mod=or&act=edit_org&org_id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo $res_org->fields["name"]?></a>
				<?php
}
?></td>
			<td><?php 
			$incidents=_shn_org_get_incidents($org_id);
			foreach ($incidents as $i){
				echo $i[1]."<br />";
			}
			?> <a
				href="index.php?mod=admin&act=ims_assign&id=<?php echo $res_org->fields["o_uuid"] ?>"><?php echo _t("Assign to more incidents")?></a></td>
			<td><?php
			while(!$res_sector->EOF){
				echo $res_sector->fields[0]."<br />";
				$res_sector->MoveNext();
			}
			$location=_shn_org_location_string($loc);
			?></td>
			<td><?php echo $org_type?></td>
			<td><?php echo $location?></td>
			<td><?php echo $res_addr->fields[0]?><br />
			<a href="mailto:<?php echo $res_email->fields[0]?>" /><?php echo $res_email->fields[0]?></a></td>
			<td><?php echo $res_phone->fields[0]?><br />
			<?php echo $res_mobile->fields[0]?></td>

		</tr>
		<?php
}
function _shn_or_view_map_form_org()
{
	global $global;
	include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_form_fopen("view_org_submit");
	shn_form_hidden(array("action"=>'edit'));
	?>
	<center><?php
	//create the submit button
	shn_form_submit(_t("Back"));
	?></center><?php
	$map_arr=array();
	$url="mod=or&act=edit_org&org_id=".isset($_POST["org_id"])?$_POST["org_id"]:$_SESSION['org']['org_id'];
	array_push($map_arr,array('lat'=>isset($_POST["lat_edited"])?$_POST["lat_edited"]:$_SESSION['org']['lat_edited'],
							  'lon'=>isset($_POST["lon_edited"])?$_POST["lon_edited"]:$_SESSION['org']['lon_edited'],
							  		'name'=>isset($_POST["org_name"])?$_POST["org_name"]:$_SESSION['org']['name'],
							  		'id'=>isset($_POST["org_id"])?$_POST["org_id"]:$_SESSION['org']['org_id'],
							  		'url'=>$url));
	shn_gis_map_with_markers($map_arr);
	?>
		<br />
		<center><?php
		//create the submit button
		shn_form_submit(_t("Back"));
		?></center>
		<br />
		<?php
		//close the form
		shn_form_fclose();
}



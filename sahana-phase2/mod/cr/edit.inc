<?php
/**Update functions for  CR
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana - http://sahana.sourceforge.net
 * @subpackage cr
 * @author   Chathra Hendehewa <chathra@opensource.lk>
 * @author   Mifan Careem <mifan@opensource.lk>
 * @edited by Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 */

include_once($global['approot'].'/inc/lib_form.inc');
include_once($global['approot'].'/inc/lib_validate.inc');
include_once($global['approot'].'/inc/lib_errors.inc');
include_once $global['approot']."/inc/lib_location.inc";

global $editid;
function _shn_cr_cedt_start($errors=false){
	if($errors)
	display_errors();
	global $global;
	$db = $global['db'];
	?>
<h2><?php echo _t("Update Existing Shelter")?></h2>
	<?php
	/*$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields['c_uuid'];*/
	$editid=$_REQUEST['cmp_id'];
	$_SESSION['editid']=$editid;

	_shn_cr_get_session($editid);
	shn_form_fopen(ecmp);
	shn_form_fsopen(_t("General Details"));
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_hidden(array('cmp_id'=>$_SESSION['editid']));
	shn_form_text(_t("Shelter Name"),"camp_name",'size="50"',array('req'=>true,'value'=>$_SESSION['camp_name']));
	shn_form_opt_select("opt_camp_type",_t("Shelter Type"),null,array('value'=>$_SESSION['opt_camp_type']));
	shn_form_textarea(_t("Address"),"camp_address",null,array('value'=>$_SESSION['camp_address']));
	shn_form_fsclose();
	?>

	<?php

	global $global;
	global $range;
	shn_form_fsopen(_t("Location Details"));
	shn_location($range,$_SESSION['opt_location_type']);
	shn_form_fsclose();

	//-----------------------------------------
	shn_form_fsopen(_t("Contact Person Details"));
	shn_form_text(_t("Full Name"),"camp_contact_name",'size="60"',array('value'=>$_SESSION['camp_contact_name']));
	shn_form_text(_t("Phone Number"),"camp_contact_number",'size="60"',array('value'=>$_SESSION['camp_contact_number']));
	shn_form_text(_t("Mobile Number"),"contact_mob",'size="60"',array('value'=>$_SESSION['camp_contact_mob']));
	shn_form_text(_t("Occupation"),"occupation",'size="60"',array('value'=>$_SESSION['camp_occupation']));
	shn_form_fsclose();
	shn_form_fsopen(_t("Shelter Population"));
	shn_form_text(_t("Capacity"),"capacity",'size="10"',array('value'=>$_SESSION['camp_capacity']));

	shn_form_text(_t("Men"),"men",'size="10"',array('value'=>$_SESSION['camp_men']));
	shn_form_text(_t("Women"),"women",'size="10"',array('value'=>$_SESSION['camp_women']));
	shn_form_text(_t("Children"),"children",'size="10"',array('value'=>$_SESSION['camp_children']));
	shn_form_text(_t("Infected Count"),"family",'size="10"',array('value'=>$_SESSION['camp_family']));
	shn_form_text(_t("Total Count"),"total",'size="10"',array('value'=>$_SESSION['camp_total']));

	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();
}


function shn_cr_all_view(){

	?>
<script type="text/javascript">
	function editThis(){
		var x=window.confirm('<?php echo _t("Do You Really Want to Delete?")?>');
		if (x){
			return true;
		}else{
			return false;
		}
	}
</script>
	<?php
	global $global;
	$db = $global['db'];
	?>
<h2><?php echo _t("Shelter Details")?></h2>
	<?php
	/*$query="select c_uuid from camp_general where name='{$_REQUEST['cmp_id']}'";
	$res=$db->Execute($query);
	$editid=$res->fields[0];*/
	$editid=$_REQUEST['cmp_id'];
	$_SESSION['editid']=$editid;

	_shn_cr_get_session($editid);
	shn_form_fopen(crch);
	shn_form_fsopen(_t("General Details"));
	shn_form_hidden(array('seq'=>'show'));
	$sql = "SELECT option_description FROM field_options WHERE field_name = 'opt_camp_type' AND option_code = '{$_SESSION['opt_camp_type']}'";
	$res = $global['db']->Execute($sql);
	$_SESSION['camp_type'] = '';
	if($res->RecordCount() > 0){
		$_SESSION['camp_type'] = $res->fields['option_description'];
	}
	shn_form_hidden(array('opt_camp_type'=>$_SESSION['opt_camp_type']));

	shn_form_label(_t("Shelter Name"),$_SESSION['camp_name'],array('br'=>'true'));
	shn_form_label(_t("Shelter Type"),$_SESSION['camp_type'],array('br'=>'true'));
	?>
<!--
<label>Division</label>
<select name="opt_location_type" >-->
	<?php
	// Display selected Division type only
	/*
	$q="select value from config where confkey='division_type' && module_id='cr'";
	//$q ="select option_description from field_options where field_name='cr_pref_div'";
	$ref = $db->Execute($q);
	$val=$ref->fields[0];
	$q ="select location_id,name from location where opt_location_type=$val";
	$ref = $db->Execute($q);
	while(!$ref->EOF){
	$val=$ref->fields[0];
	$name=$ref->fields[1];
	?>
	<option value='<?php echo $val?>'><?php echo $name?></option>
	<?php
	$ref->MoveNext();
	}
	*/
	?>
<!--</select><br>-->
	<?php

	global $global;
	include $global['approot']."/mod/or/lib_or.inc";

	//-----------------------------------------
	shn_form_label(_t("Address"),$_SESSION['camp_address']);


	//Starts
	$i = 1  - 1;
	while( $i < 5 ) {
		$i++;
		$sql = " SELECT location.name , field_options.option_description FROM location ".
				           " INNER JOIN field_options ON field_options.option_code = location.opt_location_type " .
				           " WHERE location.opt_location_type = '$i' AND " .
				           " location.loc_uuid = '{$_SESSION['opt_location_type']}' ";
		$result = $global['db']->GetRow($sql);
		shn_form_label($result['option_description'] , $result['name']);

	}
	//Ends


	shn_form_fsclose();
	//shn_location_form_view(1,4,$_SESSION['opt_location_type']);
	shn_form_fsopen(_t("Contact Person Details"));
	shn_form_label(_t("Full Name"),$_SESSION['camp_contact_name']);
	shn_form_label(_t("Phone Number"),$_SESSION['camp_contact_number']);
	shn_form_label(_t("Mobile Number"),$_SESSION['camp_contact_mob']);
	shn_form_label(_t("Occupation"),$_SESSION['camp_occupation']);
	shn_form_fsclose();
	shn_form_fsopen(_t("Shelter Population"));
	shn_form_label(_t("Capacity"),$_SESSION['camp_capacity']);

	shn_form_label(_t("Men"),$_SESSION['camp_men']);
	shn_form_label(_t("Women"),$_SESSION['camp_women']);
	shn_form_label(_t("Children"),$_SESSION['camp_children']);
	shn_form_label(_t("Infected Count"),$_SESSION['camp_family']);
	shn_form_label(_t("Total Count"),$_SESSION['camp_total']);

	shn_form_fsclose();
	$sql = "SELECT option_description FROM field_options WHERE option_code IN (SELECT opt_camp_service FROM camp_services WHERE c_uuid = '{$_SESSION['editid']}') AND field_name = 'opt_camp_service'";
	$res = $global['db']->Execute($sql);
	if($res->RecordCount() > 0){ 
		shn_form_fsopen(_('Available services'));
		for($i = 0; $i < $res->RecordCount(); $i++){
			shn_form_label('', $res->fields['option_description']);
			$res->MoveNext();
		}
		shn_form_fsclose();
	}
	shn_form_submit(_t("Close"));
	?>
<input type="button" onClick="location.replace('index.php?mod=cr&act=ecmp&seq=disp&cmp_id=<?php echo $_REQUEST['cmp_id']?>');" value=<?php echo _t("Edit")?> />
<input type="button" onClick="if(editThis()) location.replace('index.php?mod=cr&act=ecmp&seq=del&cmp_id=<?php echo $_SESSION['editid']?>');" value=<?php echo _t("Delete")?> />
	<?php
	shn_form_fclose();
}





function _shn_cr_cedt_chk($errors=false){
	if($errors)
	display_errors;

	global $global;
	include_once $global['approot']."/inc/lib_location.inc";
	$_SESSION['cr']['loc']=shn_location_get_form_submit_loc();
	$_SESSION['camp_name']=$_POST['camp_name'];
	$_SESSION['opt_camp_type']=$_POST['opt_camp_type'];
	$_SESSION['opt_location_type']=$_POST['opt_location_type'];
	$_SESSION['camp_address']=$_POST['camp_address'];
	$_SESSION['camp_contact_name']=$_POST['camp_contact_name'];
	$_SESSION['camp_contact_number']=$_POST['camp_contact_number'];
	$_SESSION['camp_contact_mob']=$_POST['contact_mob'];
	$_SESSION['camp_occupation']=$_POST['occupation'];
	$_SESSION['camp_family']=$_POST['family'];

	$_SESSION['camp_capacity']=$_POST['capacity'];

	$_SESSION['camp_men']=$_POST['men'];
	$_SESSION['camp_women']=$_POST['women'];
	$_SESSION['camp_children']=$_POST['children'];
	$_SESSION['camp_total']=$_POST['total'];
        $_SESSION['cr_loc']=shn_location_get_form_submit_loc();

	//var_dump($_SESSION);
	?>
<h2><?php echo ("Shelter Checklist")?></h2>
	<?php
	shn_form_fopen("ecmp",'',array('req_message'=>false));
	shn_form_fsopen(_t("Services / Facilities Available"));
	shn_form_hidden(array('seq'=>'confir'));

	$db = $global['db'];
	$query = "select opt_camp_service from camp_services where c_uuid='{$_SESSION['editid']}'";
	$res = $db->Execute($query);
	$select=array();
	while(!$res->EOF){
		array_push($select,$res->fields['opt_camp_service']);
		$res->MoveNext();

	}

	shn_form_opt_checkbox("opt_camp_service",array('selected'=>$select));
// 	shn_form_textarea(_t("Other Facilities"),"comments");
	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();

}

function _shn_cr_del_camp($id)
{
    global $global;
    $db=$global['db'];
    $q="delete from camp_general where c_uuid='{$id}'";
    $r="delete from camp_reg where c_uuid='{$id}'";
    $s="delete from camp_services where c_uuid='{$id}'";
    $db->Execute($q);
    $db->Execute($r);
    $db->Execute($s);
    // Delete GIS Entry
    if($conf['gis']){
        require_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        shn_gis_remove_feature_module_item($id);
    }
    add_confirmation(_t("Deleted Shelter Succesfully"));
    //shn_cr_crch
}

function _shn_cr_cadd_commit()
{
	global $global;
	//write to database
	$_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
	$_SESSION['camp_comments']=$_POST['comments'];
	foreach($_SESSION['opt_camp_service'] as $a=>$b){
		//echo "value is $b";
	}
	//echo microtime(true);
	//var_dump($_SESSION);
	_shn_cr_cadd_commit_db();
}

function _shn_cr_create_cid(){
	//create unique camp id
	//db->GenID();
	$id=time();
	return $id;

}

function _shn_cr_search_edt_frm(){
	?><h2 align="center">Edit Existing Shelter</h2><?php
	shn_form_fopen("ecmp");
	shn_form_fsopen(_t("Edit Shelter"));
	shn_form_hidden(array('seq'=>'disp'));
	shn_form_text(_t("Name of Shelter to edit"),'cmp_id','size="20"');
	shn_form_fsclose();
	shn_form_submit(_t("Edit"));
	shn_form_fclose();

}
function shn_cr_edt_srch(){
	global $global;
	include($global['approot'].'/mod/cr/search.inc');
	_shn_cr_srch(true);

}


function _shn_cr_validate_error(){
	clean_errors();
	$error_flag=false;


	if(null == ($_POST['camp_name'])){
		add_error(_t("Please enter the shelter  name"));
		$error_flag=true;
	}

	if(!(null == ($_POST['family']))){
		if(!is_numeric(trim($_POST['family']))){
			add_error(_t("The infected count is not a valid number"));
			$error_flag=true;
		}
		else if(!positive_number($_POST['family'])){
                		add_error(_t("The infected count cannot be negative"));
                        $error_flag=true;
       }
	}

	if(!(null == ($_POST['capacity']))){
                if(!is_numeric(trim($_POST['capacity']))){
                        add_error(_t("The capacity is not a valid number"));
                        $error_flag=true;
                }
                else if(!positive_number($_POST['capacity'])){
                		add_error(_t("The capacity cannot be negative"));
                        $error_flag=true;
                }
        }

	if(!(null == ($_POST['total']))){
		if(!is_numeric(trim($_POST['total']))){
			add_error(_t("The total count is not a valid number"));
			$error_flag=true;
		}
		else if(!positive_number($_POST['total'])){
                		add_error(_t("The total count cannot be negative"));
                        $error_flag=true;
       }
	}
	if(!(null == ($_POST['men']))){
		if(!is_numeric(trim($_POST['men']))){
			add_error(_t("The men count is not a valid number"));
			$error_flag=true;
		}
		else if(!positive_number($_POST['men'])){
                		add_error(_t("The men count cannot be negative"));
                        $error_flag=true;
       }
	}
	if(!(null == ($_POST['women']))){
		if(!is_numeric(trim($_POST['women']))){
			add_error(_t("The women count is not a valid number"));
			$error_flag=true;
		}
		else if(!positive_number($_POST['women'])){
                		add_error(_t("The women count cannot be negative"));
                        $error_flag=true;
       }
	}
	if(!(null == ($_POST['children']))){
		if(!is_numeric(trim($_POST['children']))){
			add_error(_t("The children count is not a valid number"));
			$error_flag=true;
		}
		else if(!positive_number($_POST['children'])){
                		add_error(_t("The children count cannot be negative"));
                        $error_flag=true;
       }
	}



	return $error_flag;
}

function positive_number($nr) {
if(ereg("^[0-9]+$", $nr) && $nr > -1){
  return true;
  } else {
  return false;
 }
}


/**
 * populate session variables from database
 * @param camp_id	the retrieved camp id
 */
function _shn_cr_get_session($camp_id){
	global $global;
	$db = $global['db'];

	$query="select a.name,a.location_id,a.opt_camp_type,a.address,admin_name,admin_no,family,total,men,women,children,capacity from camp_general a left outer join camp_reg b on a.c_uuid=b.c_uuid where a.c_uuid='{$camp_id}'";

	$res = $db->Execute($query);

	$_SESSION['camp_name']=$res->fields['name'];
	$_SESSION['opt_camp_type']=$res->fields['opt_camp_type'];
	$_SESSION['opt_location_type']=$res->fields['location_id'];
	$_SESSION['camp_address']=$res->fields['address'];
	$_SESSION['camp_contact_name']=$res->fields['admin_name'];
	$_SESSION['camp_contact_number']=$res->fields['admin_no'];
	$_SESSION['camp_family']=$res->fields['family'];
	$_SESSION['camp_men']=$res->fields['men'];
	$_SESSION['camp_women']=$res->fields['women'];
	$_SESSION['camp_children']=$res->fields['children'];
	$_SESSION['camp_total']=$res->fields['total'];
	$_SESSION['camp_capacity']=$res->fields['capacity'];

	$query="select * from contact where pgoc_uuid=(select contact_puuid from camp_admin where c_uuid='{$camp_id}')";
	$res = $db->Execute($query);
	$_SESSION['camp_contact_mob']=$res->fields['contact_value'];

	$query = "select occupation from person_details where p_uuid=(select contact_puuid from camp_admin where c_uuid='{$camp_id}');";
	$res = $db->Execute($query);
	$_SESSION['camp_occupation']=$res->fields['occupation'];

}
function _shn_cr_get_locid()
{
	if($_SESSION['cr_5']!=null)
        return $_SESSION['cr_5'];
	else if($_SESSION['cr_4']!=null)
        return $_SESSION['cr_4'];
	else if($_SESSION['cr_3']!=null)
        return $_SESSION['cr_3'];
	else if($_SESSION['cr_2']!=null)
        return $_SESSION['cr_2'];
	else
        return $_SESSION['cr_1'];
}

function _shn_cr_cedt_commit()
{
	if(isset($_POST['finish'])){
	//insert to database;
	global $conf;
    global $global;
	global $editid;
	$db = $global['db'];

	$admin = "SELECT * from camp_admin  where c_uuid='{$_SESSION['editid']}'";
	$res_admin = $db->Execute($admin);
	$pid = $res_admin->fields['contact_puuid'];

	$loc_id=$_SESSION['cr_loc'];

	//call unique camp id
	//$uid=_shn_cr_create_cid();
	//enter into camp table
	$q="update camp_general set name='{$_SESSION['camp_name']}',location_id='{$loc_id}',opt_camp_type='{$_SESSION['opt_camp_type']}',address='{$_SESSION['camp_address']}',capacity={$_SESSION['camp_capacity']} where c_uuid='{$_SESSION['editid']}'";
	$res = $db->Execute($q);

	//enter into camp_reg table
	$q="update camp_reg set admin_name='{$_SESSION['camp_contact_name']}',admin_no='{$_SESSION['camp_contact_number']}',men='{$_SESSION['camp_men']}',women='{$_SESSION['camp_women']}',family={$_SESSION['camp_family']},children='{$_SESSION['camp_children']}',total={$_SESSION['camp_total']} where c_uuid='{$_SESSION['editid']}'";
	$res = $db->Execute($q);

	$qb = "UPDATE person_details set occupation='{$_SESSION['camp_occupation']}' where p_uuid='$pid'";
	$resb = $db->Execute($qb);

	// insert into admin contact
	$qc = "UPDATE contact SET contact_value='{$_SESSION['camp_contact_mob']}' WHERE pgoc_uuid='{$pid}' AND opt_contact_type='cmob'";
	$resc = $db->Execute($qc);

	/*insert services into camp_services table
	 //currently add checked values
	 foreach($_SESSION['opt_camp_service'] as $a => $b){
	 //currently add checked values.
		//$q = "update camp_services(c_uuid,opt_camp_service,value) values($editid,'{$b}',1)";
		$res = $db->Execute($q);
		}
		*/

    // Update GIS
    if($conf['gis']){
        include_once ($global['approot'].'/inc/lib_gis/gis_fns.inc');
        $class = 'cr_camp';
        if($_SESSION['opt_camp_type'] == 'gov' || $_SESSION['opt_camp_type'] == 'tmp' || $_SESSION['opt_camp_type'] == 'ngo'){
            $class = $class . '_' . $_SESSION['opt_camp_type'];
        }
        $keys = array(  
            'f_class'         => $class,
            'f_name'          => $_SESSION['camp_name'],
            'f_address'       => $_SESSION['camp_address']
        );
        shn_gis_modify_feature_module_item($_SESSION['editid'], $keys);
    }
        
	$uid = $_SESSION['editid'];

	if(isset($_SESSION['opt_camp_service'])){
		//Delete previous values and override with current ones:
		$del="DELETE FROM camp_services WHERE c_uuid='{$uid}'";
		$res=$db->Execute($del);

		foreach($_SESSION['opt_camp_service'] as $a => $b){
			//currently add checked values.
			$q = "insert into camp_services(c_uuid,opt_camp_service,value) values('{$uid}','{$b}',1)";
			$res = $db->Execute($q);
		}
	}
	?>

<?php add_confirmation(_t("You have succesfully edited shelter ").$_SESSION['camp_name']);?>
<br />
<h3><?php echo _t("The availability of Services & Facilities of the shelter are as follows")?></h3>

	<!--To have the results shown in table format-->
<div id="result">
	<table>
		<thead>
                    <tr>
			<td><?php echo _t("Service Type")?></td>
			<td><?php echo _t("Availability")?></td>
                    </tr>
		</thead>

		<tbody>
			<tr>

			<?php
			$a="select option_code,option_description from field_options where field_name='opt_camp_service'";
			$ref=$db->Execute($a);
			while(!$ref->EOF){
				$val=$ref->fields[0];
				$name=$ref->fields[1];
				$flag=false;
				if(isset($_SESSION['opt_camp_service'])){
					foreach($_SESSION['opt_camp_service'] as $a => $b){
						if($val==$b){
							echo "<td>$name</td>";
							echo "<td>". _t("Available"). "</td>";
							$flag = true;
						}
					}
				}
				if(!$flag){
					echo "<td>$name</td>";
					echo "<td>"._t("NOT AVAILABLE")."</td>";

// 					echo "<br>";

				}
				?>
			</tr>
			<?php
			$ref->MoveNext();
}

?>

		</tbody>
	</table>
</div>
<br/>
<br/>
<p><?php echo _t("Use the Navigation Menu to Continue")?></p>
<?php
	}
	elseif(isset($_POST['edit'])){
		_shn_cr_cedit_second();
	}
}
//added to confirm edit
function _shn_cr_cedit_confir(){
	if($errors)
	display_errors;
	global $global;
	global $conf;
	$db=$global['db'];
    ?>
    <h2><?php echo  _t('Confirm Registration Details of ').$_SESSION['camp_name'] ?></h2>
    <?php
    shn_form_fopen("ecmp",null,array('req_message'=>false,'name'=>""));
    shn_form_fsopen(_t('General Details'));
    shn_form_label(_t("Shelter Name")." : ",$_SESSION['camp_name']);
    $q="select option_description from field_options where field_name='opt_camp_type' and option_code='".$_SESSION['opt_camp_type']."'";
	$ref=$db->Execute($q);
    shn_form_label(_t("Shelter Type")." : ",$ref->fields[0]);
    shn_form_label(_t("Address")." : ",$_SESSION['camp_address']);
    shn_form_fsclose();
    shn_form_fsopen(_t('Location Details'));
    $location=_shn_cr_location_string($_SESSION['cr']['loc']);
    shn_form_label(_t("Location")." : ",$location);
    shn_form_fsclose();
    shn_form_fsopen(_t('Contact Person Details'));
    shn_form_label(_t("Full Name")." : ",$_SESSION['camp_contact_name']);
    shn_form_label(_t("Phone Number")." : ",$_SESSION['camp_contact_number']);
    shn_form_label(_t("Mobile Number")." : ",$_SESSION['camp_contact_mob']);
    shn_form_label(_t("Occupation")." : ",$_SESSION['camp_occupation']);


    shn_form_fsclose();
    shn_form_fsopen(_t('Shelter Population'));
    shn_form_label(_t("Capacity")." : ",$_SESSION['camp_capacity']);
    shn_form_label(_t("Men")." : ",$_SESSION['camp_men']);
    shn_form_label(_t("Women")." : ",$_SESSION['camp_women']);
    shn_form_label(_t("Children")." : ",$_SESSION['camp_children']);
    shn_form_label(_t("Infected Count")." : ",$_SESSION['camp_family']);
    shn_form_label(_t("Total Count")." : ",$_SESSION['camp_total']);

    shn_form_hidden(array('seq'=>'commit'));
    shn_form_fsclose();
    /*shn_form_fsopen(_t('GPS Coordinates'));
    shn_form_label(_t("Latitude : "),$_SESSION['gis_loc_y']);
    shn_form_label(_t("Longitude : "),$_SESSION['gis_loc_x']);

    shn_form_fsclose();*/
    shn_form_fsopen(_t('Services / Facilities Available'));
    if(!isset($_SESSION['hospital'])){
	    $_SESSION['opt_camp_service']=$_POST['opt_camp_service'];
	    $_SESSION['camp_comments']=$_POST['comments'];
    }
    $a="select option_code,option_description from field_options where field_name='opt_camp_service'";
	$ref=$db->Execute($a);
	while(!$ref->EOF){
		$val=$ref->fields[0];
		$name=$ref->fields[1];
		$flag=false;
		if(isset($_SESSION['opt_camp_service'])){
		 foreach($_SESSION['opt_camp_service'] as $a => $b){
			if($val==$b){
				shn_form_label(_lc($name)." : ",_t('Available'));

	    		$flag=true;
			}
		 }
		}
		if(!$flag){
			shn_form_label(_lc($name)." : ",_t('Not Available'));

		}
		?>
		
		<?php
		$ref->MoveNext();
}


    shn_form_fsclose();
    echo '<center>';
    shn_form_submit(_t("Finish"),'name="finish"');
    shn_form_submit(_t("Edit"),'name="edit"');
    echo '</center>';
    shn_form_fclose();

}
function _shn_cr_cedit_second(){
	shn_form_fopen(ecmp);
	shn_form_fsopen(_t("General Details"));
	shn_form_hidden(array('seq'=>'chk'));
	shn_form_hidden(array('cmp_id'=>$_SESSION['editid']));	
	shn_form_text(_t("Shelter Name"),"camp_name",'size="50"',array('req'=>true,'value'=>$_SESSION['camp_name']));
	shn_form_opt_select("opt_camp_type",_t("Shelter Type"),null,array('value'=>$_SESSION['opt_camp_type']));
	shn_form_textarea(_t("Address"),"camp_address",null,array('value'=>$_SESSION['camp_address']));
	shn_form_fsclose();
	?>

	<?php

	global $global;
	include_once $global['approot']."/inc/lib_location.inc";
	global $range;
	shn_form_fsopen(_t("Location Details"));
	shn_location($range,$_SESSION['cr']['loc']);
	shn_form_fsclose();

	//-----------------------------------------
	shn_form_fsopen(_t("Contact Person Details"));
	shn_form_text(_t("Full Name"),"camp_contact_name",'size="60"',array('value'=>$_SESSION['camp_contact_name']));
	shn_form_text(_t("Phone Number"),"camp_contact_number",'size="60"',array('value'=>$_SESSION['camp_contact_number']));
	shn_form_text(_t("Mobile Number"),"contact_mob",'size="60"',array('value'=>$_SESSION['camp_contact_mob']));
	shn_form_text(_t("Occupation"),"occupation",'size="60"',array('value'=>$_SESSION['camp_occupation']));
	shn_form_fsclose();
	shn_form_fsopen(_t("Shelter Population"));
	shn_form_text(_t("Capacity"),"capacity",'size="10"',array('value'=>$_SESSION['camp_capacity']));

	shn_form_text(_t("Men"),"men",'size="10"',array('value'=>$_SESSION['camp_men']));
	shn_form_text(_t("Women"),"women",'size="10"',array('value'=>$_SESSION['camp_women']));
	shn_form_text(_t("Children"),"children",'size="10"',array('value'=>$_SESSION['camp_children']));
	shn_form_text(_t("Infected Count"),"family",'size="10"',array('value'=>$_SESSION['camp_family']));
	shn_form_text(_t("Total Count"),"total",'size="10"',array('value'=>$_SESSION['camp_total']));

	shn_form_fsclose();
	shn_form_submit(_t("Next"));
	shn_form_fclose();

}
//this is redundant function
function _shn_cr_location_string($loc)
{
	global $global;
	$db=$global["db"];
	$loc_arr=array();
   	shn_get_parents($loc,&$loc_arr);
   	if($loc_arr[0]=='unknown'){
   		//shn_form_label(_t("Organization Location"),"Unknown");
   	}else{

   		$max=count($loc_arr)-1;
   		array_pop($loc_arr);
   		for($count=0;$count<$max;$count++){
   			$x=array_pop($loc_arr);
   			$q="select name from location where loc_uuid='{$x}'";
    			$res=$db->Execute($q);
    			if($count==0 ){
    				$location=$location.$res->Fields("name");
    			}else{
   				$location=$location." -->".$res->Fields("name");
    			}

   		}
   	}
   	return $location;
}

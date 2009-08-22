<?php

include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_uuid.inc';
include_once $global['approot'].'/inc/lib_table.inc';
include_once $global['approot'].'/inc/lib_paging.inc';
include_once $global['approot'].'/inc/lib_location.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_ajax.inc';

include_once 'lib_pre.inc';
include_once 'gis_map.inc';
include_once 'lib_pre_frm.inc';

/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */
function shn_pre_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    // Create the module menu
    shn_mod_menuopen(_('Disaster Preparedness'));
    shn_mod_menuitem('default',_('Home'));
    shn_sub_mod_menuopen(_('Disaster identification'));
    shn_mod_menuitem('add_disaster', _('Add a disaster'));
    shn_mod_menuitem('list_disaster', _('List disasters'));
    shn_mod_menuitem('list_disaster&seq=sch_dis_frm', 'Search/Edit Disaster');
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Areas Under threat');
    shn_mod_menuitem('add_threat_area', 'Add area');
    shn_mod_menuitem('list_threat_area', 'List areas');
    shn_mod_menuitem('list_threat_area&seq=sch_frm', 'Search/Edit');
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Areas for shelters');
    shn_mod_menuitem('add_shelter_area', 'Add area');
    shn_mod_menuitem('list_shelter_area', 'List areas');
    shn_mod_menuitem('list_shelter_area&seq=sch_frm', 'Search/Edit');
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Evacuations');
    shn_mod_menuitem('evacuation', 'Evacuation planning');
    shn_mod_menuitem('list_evac', 'List Evacuation planning');
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Recovery Planning');
    shn_mod_menuitem('rec_plan', 'Plan');
    shn_mod_menuitem('list_rec_plan', 'List Recovery Plan');
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Reporting System');
    shn_mod_menuitem('dis_report', 'Public Education');
    shn_mod_menuitem('list_disaster&seq=history', 'Disaster History');
    shn_mod_menuitem('gis_report', 'GIS Report');
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';

} 

/** 
 * Other sections you can override
 */
// function shn_skel_header() {}
// function shn_skel_footer() {}
// function shn_skel_html_head() {}

/**
 * This function displays the default page of the module when it is selected
 * This function has to exist! 
 *
 * @access public
 * @return void
 */
function shn_pre_default()
{

    global $global;

?>
<div id="home">
<h2><?php echo  _('Disaster Preparedness Module'); ?></h2>
<p><?php echo  _('Most disasters and there effects can be identify before it occurs. Identifying and tracking those information will helps to do a efficient and effective planing for recover or minimize the damage and public education. From that effort for relief waorks and rehabilitation can be minimized. Sahana disaster preparedness system is addressing requirements of pre disaster deployments. Sahana disaster preparedness system is addressing four basic functionalities in disaster preparedness.')?>

<?php echo  _('Features include:');?></p>
<ul>
    <li><?php echo _('Assessing Vulnerabilities')?></li>
    <li><?php echo _('Planning')?></li>
    <li><?php echo _('Reporting')?></li>
    <li><?php echo _('Warning')?></li>
</ul>
</div>

<?php
}

function shn_pre_add_disaster(){
	include_once 'handler_disaster.inc';
}

function shn_pre_list_disaster(){
	include_once 'list_disaster.inc';
}

function shn_pre_add_threat_area(){
	global $global;
	global $conf;
	$sql = "SELECT disaster_uuid, disaster FROM pre_disaster";
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() > 0){
		include_once 'handler_area.inc';
		switch($_REQUEST['seq']){
			case '':
				_shn_pre_add_threat_area_general($res);
				break;
			case 'gis':
				if(!_shn_pre_validate_threat_area_general()){
					_shn_pre_add_threat_area_general($res);
				}
				else{
					_shn_pre_add_threat_area_session();
					if($conf['gis'] == true){
						_shn_pre_add_threat_area_map();
					}
					else{
						//_shn_pre_add_threat_area_db();
						_shn_pre_set_area_threat_level();
					}
				}
				break;
			case 'threat':
				if($conf['gis'] == true){
					if(!_shn_pre_validate_gis()){
						_shn_pre_add_threat_area_map();
					}
					else{
						_shn_pre_gis_session();
						_shn_pre_set_area_threat_level();
						//_shn_pre_add_threat_area_confirm();
					}
				}
				else{
					if(!_shn_pre_validate_threat_area_general()){
						_shn_pre_add_threat_area_general($res);
					}
					else{
						_shn_pre_add_threat_area_session();
					}
				}
				break;
			case 'confirm':
				_shn_pre_set_area_threat_session();
				_shn_pre_add_threat_area_confirm();
				break;
			case 'db':
				if(isset($_POST['save'])){
					_shn_pre_add_threat_area_db();
				}
				else{
					_shn_pre_edit_threat_area($res);
				}
				break;
			case 'edit':
				$area_uuid = $_REQUEST['area'];
				_shn_pre_edit_threat_area_form($area_uuid);
				break;
			case 'edit_threat':
				if(_shn_pre_validate_threat_area_general()){
					_shn_pre_add_threat_area_session(false);
					$_SESSION['area_uuid'] = $_POST['area_uuid'];
					$_SESSION['new_p'] = $_POST['new'];
					_shn_pre_set_area_threat_level(false);
				}
				else{
					$area_uuid = $_REQUEST['area_uuid'];
					_shn_pre_edit_threat_area_form($area_uuid);
				}
				break;
			case 'edit_db':
				_shn_pre_set_area_threat_session();
				_shn_pre_edit_threat_area_db();
				break;
			case 'del':
				$area_uuid = $_POST['area_uuid'];
				_shn_pre_delete_threat_area($area_uuid);
				break;
			default:
				break;
		}
	}
	else{
		_shn_pre_print_alert('No disaster has been identified');
	}
}

function shn_pre_list_threat_area(){
	include_once 'list_area.inc';
	switch($_REQUEST['seq']){
		case '':
			_shn_pre_print_header('List Areas Under Threat');
			_shn_pre_list_threat_area();
			break;
		case 'list':
			$id = $_REQUEST['area'];
			_shn_pre_get_threat_area($id);
			break;
		case 'gis':
			$area_uuid = $_REQUEST['area'];
			_shn_pre_show_area($area_uuid);
			break;
		case 'sch_frm':
			_shn_pre_print_header('Search a area under threat');
			_shn_pre_search_threat_area_form();
			break;
		case 'search':
			_shn_pre_print_header('Result of searching');
			_shn_pre_search_threat_area();
			echo '<br><a href="index.php?mod=pre&act=list_threat_area&seq=sch_frm">Back</a>';
			break;
		case 'sch_frm_d':
			_shn_pre_seach_disaster_area_form();
			break;
		case 'sch_d':
			_shn_pre_disaster_threat_area($_POST['disaster']);
			break;
		default:
			break;
	}
	
}

function shn_pre_add_shelter_area(){
	global $global;
	global $conf;
	$sql = "SELECT disaster_uuid, disaster FROM pre_disaster";
	$res = $global['db']->Execute($sql);
	if ($res->RecordCount() > 0){
		include_once 'handler_shelter.inc';
		switch($_REQUEST['seq']){
			case '':
				_shn_pre_add_shelter_area_general($res);
				break;
			case 'gis':
				if(_shn_pre_validate_shelter_area_general()){
					_shn_pre_add_shelter_area_general($res);
				}
				else{
					_shn_pre_add_shelter_general_session();
					_shn_pre_add_shelter_area_map();
				}
				break;
			case 'confirm':
				if($conf['gis']){
					if(!_shn_pre_validate_gis()){
						_shn_pre_add_threat_area_map();
					}
					else{
						_shn_pre_gis_session();
						_shn_pre_add_shelter_confirmation();
					}
				}
				else{
					if(_shn_pre_validate_shelter_area_general()){
						_shn_pre_add_shelter_area_general($res);
					}
					else{
						_shn_pre_add_shelter_confirmation();
					}
				}
				break;
			case 'db':
				if(isset($_POST['save'])){
					_shn_pre_add_shelter_area_db();
				}
				break;
			case 'edit':
				$area_uuid = $_REQUEST['area'];
				_shn_pre_edit_shelter_area_form($area_uuid);
				break;
			case 'edit_db':
				$area_uuid = $_POST['area_uuid'];
				if(_shn_pre_validate_shelter_area_general()){
					_shn_pre_edit_shelter_area_form($area_uuid);
				}
				else{
					_shn_pre_edit_shelter_area_db();
				}
				break;
			case 'del':
				$area_uuid = $_POST['area_uuid'];
				_shn_pre_delete_shelter_area($area_uuid);
				break;
			default:
				break;
		}
	}
	else{
		_shn_pre_print_alert("No disaster has been identified yet");
	}
}

function shn_pre_list_shelter_area(){
	include_once 'list_area.inc';
	switch($_REQUEST['seq']){
		case '':
			_shn_pre_list_shelter_area();
			break;
		case 'list':
			$id = $_REQUEST['area'];
			_shn_pre_get_shelter_area($id);
			break;
		case 'gis':
			$area_uuid = $_REQUEST['area'];
			_shn_pre_show__shelter_area($area_uuid);
			break;
		case 'sch_frm':
			_shn_pre_search_shelter_area_form();
			break;
		case 'search':
			_shn_pre_search_shelter_area();
			break;
		default:
			break;
	}
	
}

function shn_pre_evacuation(){
	include_once 'list_area.inc';
	include_once 'handler_evacuation.inc';
	switch($_REQUEST['seq']){
		case '':
			_shn_pre_print_header('Select a disaster for evacuation');
			_shn_pre_seach_disaster_area_form();
			break;
		case 'show_shlt':
			$_SESSION['area_uuid'] = $_REQUEST['area_id'];
			$_SESSION['disaster'] = $_REQUEST['dis_id'];
			_shn_pre_print_header('Select suitable shelter for evacuations in '._shn_pre_get_threat_area_name($_SESSION['area_uuid']));
			_shn_pre_get_best_shelters($_SESSION['area_uuid'], $_SESSION['disaster']);
			_shn_pre_get_other_shelters($_SESSION['area_uuid'], $_SESSION['disaster']);
			break;
		case 'alct_frm':
			$_SESSION['shelter_uuid'] = $_REQUEST['sht_id'];
			_shn_pre_print_header('Allocate people to shelter '._shn_pre_get_shelter_area_name($_SESSION['shelter_id']));
			_shn_pre_add_allocate_form();
			break;
		case 'alct_add':
			if($_REQUEST['allocate'] > $_REQUEST['population']){
				_shn_pre_print_alert('Allocated quantity to shelter should be less than the population');
				_shn_pre_add_allocate_form();
			}
			else{
				$_SESSION['allocate'] = $_REQUEST['allocate'];
				if($_REQUEST['allocate'] > $_REQUEST['capacity']){
					_shn_pre_print_alert('Allocated population is larger than the capacity');
					_shn_pre_add_it_allocate();
				}
				else{
					_shn_pre_add_allocate_db();
				}
			}
			break;
		case 'alct_add_it':
			_shn_pre_add_allocate_db();
			break;
		case 'show_area':
			$_SESSION['shelter_uuid'] = $_REQUEST['shlt_id'];
			$_SESSION['disaster'] = $_REQUEST['dis_id'];
			break;
		case 'list':
			_shn_pre_print_header('List planed evacuation');
			_shn_pre_seach_disaster_area_form();
			break;
		default:
			break;
	}
}

function shn_pre_list_evac(){
	include 'list_evacuation.inc';
}

function shn_pre_add_warning(){
	include 'handler_warning.inc';
}

function shn_pre_rec_plan(){
	include 'handler_rec_plan.inc';
}

function shn_pre_list_rec_plan(){
	include 'list_rec_plan.inc';
}

function shn_pre_dis_report(){
	include_once 'handler_dis_report.inc';
}

function shn_pre_gis_report(){
	switch($_REQUEST['seq']){
	case '':
		_shn_pre_print_header('GIS Report');
		_shn_pre_list_disaster_selection('gis_report', 'show_all');
		break;
	case 'show_all':
		$_SESSION['disaster'] = $_REQUEST['disaster'];
		_shn_pre_print_header('Area Under Threat and Safe Areas for '._shn_pre_get_disaster_name($_SESSION['disaster']));
		_shn_pre_gis_disaster_report($_SESSION['disaster']);
	default :
		break;
}
}

function shn_ajax_send_contact_person(){
	$id=null;
	$name=null;
	$data=_shn_ajax_get_contact_person();
	
    for($j=0;$j<count($data);$j++){
    	list($id,$name)=split(';',$data[$j]);
    	$id_array[$j]=$id;
    	$name_array[$j]=$name;
    }
   
    $input=$_GET["input"];
    $print=$_GET["print"];
    $event=$_GET["eve"];
    $input_ele=$_GET["input_ele"];
if (strlen($input) > 0)
{
  $hint="";
  for($i=0; $i<count($data); $i++)
  {
  if (strtolower($input)==strtolower(substr($name_array[$i],0,strlen($input))))
    {
    if ($hint=="")
      {
      $hint=':'.$data[$i];
      }
    else
      {
      $hint=$hint.':'.$data[$i];
      }
    }
  }
}
    $hint=$print.':'.$event.':'.$input_ele.':'.substr($hint,strpos($hint,':')+1,strlen($hint));

    if ($hint == "")
    {
    //$response="no suggestion";
    }
    else
    {
        $response=$hint;
    }


    echo $response;
    return $response;
}

function _shn_ajax_get_contact_person(){
	global $global;
	global $conf;
	$db = $global['db'];
	$head_names= array ();
	$count=0;

	$sql="";
	
	//$sql="select pd.apt_no as apt_no,g.g_uuid as gid,p.full_name as first_name,p.family_name as last_name,co.contact_value as address from person_uuid p,group_details g,person_details pd,contact co,resource_to_shelter rdnyc where rdnyc.transfer_status='N' and rdnyc.x_uuid=g.g_uuid and g.head_uuid=p.p_uuid and pd.p_uuid=g.head_uuid and pd.p_uuid=p.p_uuid and co.pgoc_uuid=p.p_uuid and co.pgoc_uuid=g.head_uuid and co.pgoc_uuid=pd.p_uuid and co.opt_contact_type='address'";
		
	$text = $_REQUEST['text'];
	$res = _shn_pre_get_existing_person($text);
	while(!$res->EOF)
	{
	//$head_names[$res->fields['groupid']]=$res->fields['full_name'];
	
	$head_names[$count]=$res->fields['person_uuid'].';'.$res->fields['full_name'];
	$count++;
	
	$res->MoveNext();
	}
	//$head_names[0] = "sssssssss;asasdada";
	return $head_names;
	
}

function shn_text_pre_get_contact_person(){
	
	global $global;
	shn_ajax_send_contact_person();
}


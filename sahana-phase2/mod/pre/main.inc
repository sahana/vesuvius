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
    shn_sub_mod_menuclose();
    shn_sub_mod_menuopen('Areas of shelters');
    shn_mod_menuitem('add_shelter_area', 'Add area');
    shn_mod_menuitem('list_shelter_area', 'List areas');
    shn_sub_mod_menuclose();
    shn_mod_menuitem('evacuation', 'Evacuation planning');
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
<h2><?= _('Disaster Preparedness Module'); ?></h2>
<p><?= _('This is a description of the module that we typically
give on the first page with it\' features listed below')?>
<?= _('Features include:');?></p>
<ul>
    <li><?=_('Give a description of the features')?></li>
    <li><?=_('Feature 2')?></li>
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
			case 'del':
				$area_uuid = $_POST['area_uuid'];
				_shn_pre_delete_threat_area($area_uuid);
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
		case 'sch_frm_d':
			_shn_pre_seach_disaster_area_form();
			break;
		case 'sch_d':
			echo $_POST['disaster'].'sssssssssssss';
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
		default:
			break;
	}
	
}

function shn_pre_evacuation(){
	include_once 'list_area.inc';
	switch($_REQUEST['seq']){
		case '':
		_shn_pre_print_header('Select a disaster for evacuation');
		_shn_pre_seach_disaster_area_form();
		break;
	default:
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

?>
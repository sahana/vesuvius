<?php
/** 
* $id$
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * Show GIS Map with Wiki info
 * reference function
 */
function show_wiki_map($category="all",$date=0)
{
	
	global $global;
	include $global['approot']."/mod/gis/gis_fns.inc";
	include_once $global['approot']."/inc/lib_form.inc";
	
	//$type_help="Help Me";
	
	shn_form_fopen(swik,null,array('req'=>false));
	shn_form_fsopen("Filter Options");
	shn_form_opt_select("opt_wikimap_type",_("Situation Type"),null,array('all'=>true));
	shn_form_fsclose();
	shn_form_submit(_("Filter"));
	shn_form_fclose();
	
	$db = $global['db'];
	$query="select a.name,a.description,a.url,a.event_date,a.author,b.map_northing,b.map_easting from gis_wiki as a, gis_location as b where a.wiki_uuid=b.poc_uuid ";
	$res = $db->Execute($query);
	
	//create array
	$map_array=array();
	
	//populate aray
	while(!$res->EOF){
			array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
				"desc"=>$res->fields['description'],"url"=>$res->fields['url']));
			$res->MoveNext();	
	}
	
	shn_gis_map_with_wiki_markers($map_array);
	
	
	/*
	shn_gis_init_plugin("GIS Maps of Camps");
	global $conf;
	load_map($conf['mod_gis_center_x'],$conf['mod_gis_center_y']);
		//put values into array: even better, process directly ;)
	$db = $global['db'];
	$query="select a.name,a.description,a.url,a.event_date,a.author,b.map_northing,b.map_easting from gis_wiki as a, gis_location as b where a.wiki_uuid=b.poc_uuid";
	$res = $db->Execute($query);
		while(!$res->EOF){
			add_wiki_marker_db($res->fields['map_northing'],$res->fields['map_easting'],$res->fields['name']);
			$res->MoveNext();
		}
	end_page();
	*/
}

/**
 * Show GIS Map with Wiki info
 */
function show_wiki_add_map()
{
	$_SESSION['wiki_name'] = $_POST['wiki_name'];
	$_SESSION['opt_wikimap_type'] = $_POST['opt_wikimap_type'];
	$_SESSION['wiki_text'] = $_POST['wiki_text'];
	$_SESSION['wiki_url'] = $_POST['wiki_url'];
	$_SESSION['wiki_evnt_date'] = $_POST['wiki_evnt_date'];
	$_SESSION['wiki_author'] = $_POST['wiki_author'];
	$_SESSION['edit_public'] = $_POST['edit_public'];
	$_SESSION['view_public'] = $_POST['view_public'];
	
	
	global $global;
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_form_fopen(awik);
	shn_form_hidden(array('seq'=>'com'));
	shn_gis_add_marker_map_form();
	shn_form_submit(_("Next"));
}

function add_wiki_detail()
{
	
}

function show_wiki_add_detail($errors=false)
{
	if($errors){
		echo "Errors";
	}
	global $global;
	include_once $global['approot']."/inc/lib_form.inc";
?>
	<h2><?=_("Add Situation Detail")?></h2>
<?php
	$type_help="yo";
	$url_help="type url";
	$date_help="type date";
	
	shn_form_fopen(awik);
	shn_form_fsopen(_("Main Details"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_("Name of Detail"),"wiki_name",'size="50"',array('req'=>true,'help'=>$type_help));
	shn_form_opt_select("opt_wikimap_type",_("Wiki Type"),null,array('help'=>$type_help));
	shn_form_textarea(_("Detail Summary"),"wiki_text",'size="50"');
	shn_form_fsclose();
	shn_form_fsopen(_("Extra Details"));
	shn_form_text(_("URL"),"wiki_url",'size="50"',array('help'=>$url_help));
	shn_form_text(_("Date of Event"),"wiki_evnt_date",'size="50"',array('help'=>$date_help));
	shn_form_fsclose();
	shn_form_fsopen(_("Wikimap Options"));
	shn_form_text(_("Author"),"wiki_author",'size="50"',array('help'=>$type_help));
	shn_form_checkbox(_("Publicly Editable"),"edit_public");
	shn_form_checkbox(_("Publicly Viewable"),"view_public");
	shn_form_fsclose();
	shn_form_submit(_("Add Detail"));
	shn_form_fclose();
}

function shn_wiki_map_commit()
{
	global $global;
	include_once($global['approot'].'/inc/lib_uuid.inc');
	$id = shn_create_uuid();
	$_SESSION['loc_x']=$_POST['loc_x'];
	$_SESSION['loc_y']=$_POST['loc_y'];

	$db = $global['db'];
	$wiki_id=shn_create_uuid('wm');
	//$gis_id=shn_create_uuid('g');
	$gis_id=0;
	
	$query = " insert into gis_wiki (wiki_uuid,gis_uuid,name,description,opt_category,url,event_date,editable,author,approved) " .
			 " values ('{$wiki_id}','{$gis_id}','{$_SESSION['wiki_name']}','{$_SESSION['wiki_text']}','{$_SESSION['opt_wikimap_type']}', " .
			 "'{$_SESSION['wiki_url']}','{$_SESSION['wiki_evnt_date']}','{$_SESSION['edit_public']}','{$_SESSION['wiki_author']}','{$_SESSION['view_public']}')";
			 
	$res=$db->Execute($query);
	
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_dbinsert($wiki_id,0,null,$_SESSION['loc_x'],$_SESSION['loc_y'],NULL);
	echo "DONE";
	
	
}
?>

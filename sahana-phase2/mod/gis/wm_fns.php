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
	if(!isset($category))
		$category="all";
	
	//$type_help="Help Me";
	
	shn_form_fopen(swik,null,array('req'=>false));
	shn_form_fsopen("Filter Options");
	shn_form_opt_select("opt_wikimap_type",_("Situation Type"),null,array('all'=>true));
	shn_form_fsclose();
	shn_form_submit(_("Filter"));
	shn_form_fclose();
	
	$db = $global['db'];
	$query="select a.wiki_uuid,a.name,a.description,a.url,a.placement_date,a.author,a.editable,b.map_northing,b.map_easting from gis_wiki as a, gis_location as b where a.wiki_uuid=b.poc_uuid ".
		(($category=='all')?" ":" and opt_category='{$category}'");
	$res = $db->Execute($query);
	
	//create array
	$map_array=array();
	
	
	
	//populate aray
	while(!$res->EOF){
			
			$editable=$res->fields['editable'];
			if($editable==1){
				$edit_url= "<a href="."index.php?mod=gis&act=wm_edit&seq=ewmp&wmid=".$res->fields['wiki_uuid']."> Edit</a>";
			}
			else
				$edit_url="";
			
			array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
				"desc"=>$res->fields['description'],"url"=>$res->fields['url'],"author"=>$res->fields['author'],"edit"=>$edit_url,"date"=>$res->fields['placement_date'],"wiki_id"=>$res->fields['wiki_uuid']));
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
	shn_form_fopen(awik,null,array('req'=>false));
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
	shn_form_checkbox(_("Publicly Editable"),"edit_public",null,array('value'=>'edit'));
	shn_form_checkbox(_("Publicly Viewable"),"view_public","view");
	shn_form_fsclose();
	shn_form_submit(_("Add Detail"));
	shn_form_fclose();
}

function shn_wiki_edit($id)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$query="select wiki_uuid,description from gis_wiki where wiki_uuid='{$id}'";
	$res=$db->Execute($query);
	$desc=$res->fields['description'];
	
	include_once $global['approot']."/inc/lib_form.inc";
	shn_form_fopen(ewik);
	shn_form_fsopen(_("Update Detail"));
	shn_form_textarea(_("Detail Summary"),"wiki_text",'size="50"',array('value'=>$desc));
?>
	<input type="hidden" name="wiki_id" value="<?=$res->fields['wiki_uuid']?>">
<?php
	shn_form_fsclose();
	shn_form_submit(_("Commit Detail"));
	shn_form_fclose();
}

function shn_wiki_edit_com($id)
{
	global $global;
	global $conf;
	$db = $global['db'];
	//echo $id;
	//echo "{$_REQUEST['wiki_text']}";
	$query="update gis_wiki set description='{$_REQUEST['wiki_text']}' where wiki_uuid='{$id}'";
	$res=$db->Execute($query);
?>
<div id="note">
	<p><?=_('Succesfully Updated Description')?></p>
</div>
<?php
}

function shn_wiki_map_commit()
{
	global $global;
	include_once($global['approot'].'/inc/lib_uuid.inc');
	include_once $global['approot']."/inc/lib_form.inc";
	//$id = shn_create_uuid();
	$_SESSION['loc_x']=$_POST['loc_x'];
	$_SESSION['loc_y']=$_POST['loc_y'];

	$db = $global['db'];
	$wiki_id=shn_create_uuid('wm');
	//$gis_id=shn_create_uuid('g');
	$gis_id=0;
	
	$edit=($_SESSION['edit_public']=='edit')?1:0;
	
	$query = " insert into gis_wiki (wiki_uuid,gis_uuid,name,description,opt_category,url,event_date,editable,author,approved) " .
			 " values ('{$wiki_id}','{$gis_id}','{$_SESSION['wiki_name']}','{$_SESSION['wiki_text']}','{$_SESSION['opt_wikimap_type']}', " .
			 "'{$_SESSION['wiki_url']}','{$_SESSION['wiki_evnt_date']}','{$edit}','{$_SESSION['wiki_author']}','{$_SESSION['view_public']}')";
			 
	$res=$db->Execute($query);
	
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_dbinsert($wiki_id,0,null,$_SESSION['loc_x'],$_SESSION['loc_y'],NULL);
	
	shn_form_fopen(null,null,array('req'=>false));
	shn_form_fsopen(_(" Added Wiki Item"));
?>
	<div class="error">
		<?=shn_form_label(_("Succesfully added wiki item :"),_("{$_SESSION['wiki_name']}"));?>
	</div>
<?php
	//echo $_SESSION['edit_public'];
	shn_form_fsclose();
	shn_form_fclose();
	
	
}
?>

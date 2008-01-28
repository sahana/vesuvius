<?php
/* $id$ */
/** 
 * Wikimaps functionality for GIS module
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * 
 * @author   Mifan Careem <mifan@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage gis
 */

/**
 * Show GIS Map with Wiki information as markers
 * @param string $category filter subtype
 * @param date $date
 * @access public
 * @return void
 * @TODO filter by date
 */
function show_wiki_map($category="all",$date=0)
{
	
	global $global;
	global $conf;
	include $global['approot']."/mod/gis/gis_fns.inc";
	include_once $global['approot']."/inc/lib_form.inc";
	
	//default to all categories
	//set to something else if load problems occur, especially online
	print ("<h2>"._("View Situation Map")."</h2>");
	
	if(!isset($category))
		$category="all";
	shn_form_fopen(swik,null,array('req'=>false));
	shn_form_fsopen(_("Filter Options"));
	shn_form_opt_select("opt_wikimap_type",_("Situation Type"),null,array('all'=>true));
	shn_form_fsclose();
	shn_form_submit(_("Filter"));
	shn_form_fclose();
	
	$db = $global['db'];
	$query="SELECT a.wiki_uuid,a.name,a.description,a.url,date(a.event_date) as event_date,a.author,a.editable,b.map_northing,b.map_easting FROM gis_wiki as a, gis_location as b WHERE a.wiki_uuid=b.poc_uuid ".
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
			
			//handle images
			//@todo: image type
			$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpeg';
			$image_path="tmp/".$image_name;
			$image_file=$global['approot'].$conf['mod_gis_image_folder'].$image_name;
			
			//no image available and other format support
			if(!file_exists($image_file)){
				//check jpg
				$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpg';
				$image_path="tmp/".$image_name;
				$image_file=$global['approot'].$conf['mod_gis_image_folder'].$image_name;
				if(!file_exists($image_file)){
					//check png
					$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.png';
					$image_path="tmp/".$image_name;
					$image_file=$global['approot'].$conf['mod_gis_image_folder'].$image_name;
					if(!file_exists($image_file)){
						$image_path=null;
					}
				}
			}
			
			array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
				"desc"=>$res->fields['description'],"url"=>$res->fields['url'],"author"=>$res->fields['author'],"edit"=>$edit_url,"date"=>$res->fields['event_date'],"wiki_id"=>$res->fields['wiki_uuid'],"image"=>$image_path,"img_w"=>100,"img_h"=>100));
			$res->MoveNext();	
	}
	
	//call gis api
	shn_gis_map_with_wiki_markers($map_array);
	
	
}

/**
 * Image Upload Form as part of adding situations
 * @access public
 * @return void
 */
function show_wiki_add_image()
{
	
	//var_dump($_POST);
	if(isset($_POST['loc_x']) && $_POST['loc_y']!=''){
		$_SESSION['loc_x']=$_POST['loc_x'];
		$_SESSION['loc_y']=$_POST['loc_y'];
	}
	if(isset($_POST['gps_x']) && $_POST['gps_y']!=''){
        $_SESSION['loc_x']=$_POST['gps_x'];
        $_SESSION['loc_y']=$_POST['gps_y'];
    }
	
	
	global $global;
	include_once ($global['approot'].'/inc/lib_form.inc');
	shn_form_fopen(awik,null,array('enctype'=>'enctype="multipart/form-data"'));
	shn_form_hidden(array('seq'=>'com'));
	shn_form_fsopen(_("Situation Image"));
	shn_form_upload(_("Upload Image"),'image');
	shn_form_fsclose();
	shn_form_submit(_('Next'));
	shn_form_fclose();
	
}
/**
 * Show GIS Map with Wiki addition event listener
 * Part of add situation sequence
 * @access public
 * @return void 
 * patch by Fran Boon
 */
function show_wiki_add_map($errors=false)
{
	global $global;
		
	if($errors){
       display_errors();
    }
    else{
		$_SESSION['wiki_name'] = $_POST['wiki_name'];
		$_SESSION['opt_wikimap_type'] = $_POST['opt_wikimap_type'];
		$_SESSION['wiki_text'] = $_POST['wiki_text'];
		$_SESSION['wiki_url'] = $_POST['wiki_url'];
		$_SESSION['wiki_evnt_date'] = $_POST['wiki_evnt_date'];
		$_SESSION['wiki_author'] = $_POST['wiki_author'];
		$_SESSION['edit_public'] = $_POST['edit_public'];
		$_SESSION['view_public'] = $_POST['view_public'];
    }
    
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_form_fopen(awik,null,array('req'=>false));
	shn_form_hidden(array('seq'=>'img'));
	//call gis api
	shn_gis_add_marker_map_form();
	shn_form_submit(_("Next"));
	shn_form_fclose();
}

function add_wiki_detail()
{
	
}

/**
 * Situation add form
 * start of sequence with error checking
 * @param boolean $errors true if errors exist,false otherwise
 * @access public
 * @return void
 * @TODO: add javascript calender for date input
 */


//-----------------------------
//replaces Mifan's shn_gis_show
function map_client($errors=false)
{
	global $global;
	include_once $global['approot'] . "/inc/lib_errors.inc";
	
	//if($errors){
	//	add_error(_("Detail Name Cannot be empty"));
	//}
	global $global;
	global $conf;
	include_once $global['approot']."/inc/lib_form.inc";
  	include_once $global['approot']."/mod/gis/gis_fns.inc";
  
  
	
	
?>
	<h2><?=_("Mapping Client")?></h2>
	<p></p>
<?php

	//mapping comes here
	$options=array();
  	if((isset($_POST['mapa_x'])) && isset($_POST['mapa_y'])){
  		//echo $_POST['mapa_x'];
  	}
  		//var_dump($_POST);
  	shn_gis_map();	


}


//-----------------------------

function show_wiki_add_detail($errors=false)
{
	global $global;
	include_once $global['approot'] . "/inc/lib_errors.inc";
	
	if($errors){
		add_error(_("'Name of situation detail' field cannot be empty"));
	}
	global $global;
	global $conf;
	include_once $global['approot']."/inc/lib_form.inc";
?>
	<h2><?=_("Add Situation Detail")?></h2>
<?php
	
	shn_form_fopen(awik);
	shn_form_fsopen(_("Main Details"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_("Name of situation detail"),"wiki_name",'size="50"',array('req'=>true,'help'=>_($conf['mod_gis_situation_name_help'])));
	shn_form_opt_select("opt_wikimap_type",_("Wiki Type"),null,array('help'=>_($conf['mod_gis_situation_type_help'])));
	shn_form_textarea(_("Detail Summary"),"wiki_text",'size="50"');
	shn_form_fsclose();
	shn_form_fsopen(_("Extra Details"));
	shn_form_text(_("URL"),"wiki_url",'size="50"',array('help'=>_($conf['mod_gis_situation_url_help'])));
	//shn_form_text(_("Date of //Event"),"wiki_evnt_date",'size="50"',array('help'=>_($conf['mod_gis_situation_date_help'])));
	shn_form_date(_("Date of Event"),"wiki_evnt_date",array('req'=>true,'value'=>date('Y-m-d'),'help'=>_($conf['mod_gis_situation_date_help'])));
	shn_form_fsclose();
	shn_form_fsopen(_("Wikimap Options"));
	shn_form_text(_("Author"),"wiki_author",'size="50"',array('help'=>_($conf['mod_gis_situation_author_help'])));
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
	$query="SELECT wiki_uuid,description FROM gis_wiki WHERE wiki_uuid='{$id}'";
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
	$query="update gis_wiki set description='{$_REQUEST['wiki_text']}' WHERE wiki_uuid='{$id}'";
	$res=$db->Execute($query);
	add_confirmation(_('Succesfully updated description'));
}

function shn_wiki_map_commit()
{
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_uuid.inc');
	include_once $global['approot']."/inc/lib_form.inc";
	include_once $global['approot']."/inc/lib_image.inc";
	include_once $global['approot'] . "/inc/lib_errors.inc";
	//$id = shn_create_uuid();

	$db = $global['db'];
	$wiki_id=shn_create_uuid('wm');
	//$gis_id=shn_create_uuid('g');
	$gis_id=0;
	
	$edit=($_SESSION['edit_public']=='edit')?1:0;
	
	$query = " insert into gis_wiki (wiki_uuid,gis_uuid,name,description,opt_category,url,event_date,editable,author,approved) " .
			 " values ('{$wiki_id}','{$gis_id}','{$_SESSION['wiki_name']}','{$_SESSION['wiki_text']}','{$_SESSION['opt_wikimap_type']}', " .
			 "'{$_SESSION['wiki_url']}','{$_SESSION['wiki_evnt_date']}','{$edit}','{$_SESSION['wiki_author']}','{$_SESSION['view_public']}')";
			 
	$res=$db->Execute($query);
	//var_dump($_SESSION);
	include $global['approot']."/mod/gis/gis_fns.inc";
	shn_gis_dbinsert($wiki_id,0,null,$_SESSION['loc_x'],$_SESSION['loc_y'],NULL);
	
	shn_gis_dbinsert_feature($wiki_id,$_SESSION['loc_y'],$_SESSION['loc_x']);
	
	if(!($_FILES['image']['error']==UPLOAD_ERR_NO_FILE))
	{
	
		//handle image upload from previous page
		$info = getimagesize($_FILES['image']['tmp_name']);
		//if($info){
	    	//valid image
	    	list($ignore,$ext) = split("\/",$info['mime']);
	    //}
	    $ext = '.'.$ext;
		$upload_dir = $global['approot'].'www/tmp/';
		
		$uploadfile = $upload_dir .'wiki_'.$wiki_id.$ext;
		
	    if(move_uploaded_file($_FILES['image']['tmp_name'], $uploadfile))
	    {
	    	//success
	    }
	    else
	    {
			//false;
	    }
	    $thumb_path = $upload_dir .'wiki_thumb_'.$wiki_id.$ext;
	    //create thumbnail
	    shn_image_resize($uploadfile,$thumb_path,100,100);
	}
	
	//shn_form_fopen(null,null,array('req'=>false));
// 	shn_form_fsopen(_(" Added Wiki Item"));
	add_confirmation(_("Succesfully added wiki item ").$_SESSION['wiki_name']);
	//echo $_SESSION['edit_public'];
	//shn_form_fsclose();
	//shn_form_fclose();
	
	
	
	
	
}
?>

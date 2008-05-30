<?php

/** 
 * Wikimaps functionality for Sitaution Awareness module
 * PHP version 5
 *
 * @author   	Mifan Careem <mifan@opensource.lk>
 * @author   	Fran Boon <flavour@partyvibe.com>
 * @copyright  	Lanka Software Foundation - http://www.opensource.lk
 * @module      sm
 * @version     $id$;
 * @copyright  	Lanka Software Foundation - http://www.opensource.lk
 * @license    	http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * Show GIS Map with Wiki information as markers
 * @param string $category filter subtype
 * @param date $date
 * @access public
 * @return void
 * @TODO filter by date
 */
function shn_sm_show_wiki_map($category="all",$date=0)
{
	global $global;
	global $conf;
	include_once $global['approot']."/inc/lib_form.inc";
	
	//default to all categories
	//set to something else if load problems occur, especially online
	print ("<h2>"._t("View Situation Map")."</h2>");
	
	if(!isset($category))
		$category="all";
	shn_form_fopen(swik,null,array('req'=>false));
	shn_form_fsopen(_t("Filter Options"));
	shn_form_opt_select("opt_wikimap_type",_t("Situation Type"),null,array('all'=>true));
	shn_form_fsclose();
	shn_form_submit(_t("Filter"));
	shn_form_fclose();
	
	$db = $global['db'];
	$query="SELECT a.wiki_uuid,a.name,a.description,a.url,date(a.event_date) as event_date,a.author,a.editable,b.map_northing,b.map_easting FROM gis_wiki as a, gis_location as b WHERE a.wiki_uuid=b.poc_uuid ".
		(($category=='all')?" ":" and opt_category='{$category}'");
	$res = $db->Execute($query);
	
	//create array
	$map_array=array();

	//populate array
	while(!$res->EOF){
			$editable=$res->fields['editable'];
			if($editable==1){
				$edit_url= "index.php?mod=sm&act=wm_edit&seq=ewmp&wmid=".$res->fields['wiki_uuid'];
			}
			else
				$edit_url="";
			
			//handle images
			//@todo: image type
			$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpeg';
			$image_path="tmp/".$image_name;
			$image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
			
			//no image available and other format support
			if(!file_exists($image_file)){
				//check jpg
				$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.jpg';
				$image_path="tmp/".$image_name;
				$image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
				if(!file_exists($image_file)){
					//check png
					$image_name='wiki_thumb_'.$res->fields['wiki_uuid'].'.png';
					$image_path="tmp/".$image_name;
					$image_file=$global['approot'].$conf['mod_sm_image_folder'].$image_name;
					if(!file_exists($image_file)){
						$image_path=null;
					}
				}
			}
			
			array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
				"desc"=>$res->fields['description'],"url"=>$res->fields['url'],"author"=>$res->fields['author'],"edit"=>$edit_url,"date"=>$res->fields['event_date'],"wiki_id"=>$res->fields['wiki_uuid'],"image"=>$image_path,"img_w"=>100,"img_h"=>100));
			$res->MoveNext();	
	}

    // Shortcuts to GIS Catalogue
    if ($conf['gis_dflt'] == "openlayers") {
        include_once $global['approot']."/inc/lib_gis/admin_acts.inc";
        print "<table><tr><td style=\"border: 0px;\">";
        print _t("GIS Administration:");
        print "</td><td style=\"border: 0px;\">";
        shn_form_fopen(gis_files,admin,array('req'=>false));
	    shn_form_submit(_t("Files"));
        shn_form_fclose();
        print "</td><td style=\"border: 0px;\">";
        shn_form_fopen(gis_layers,admin,array('req'=>false));
	    shn_form_submit(_t("Layers"));
        shn_form_fclose();
        print "</td><td style=\"border: 0px;\">";
        shn_form_fopen(gis_markers,admin,array('req'=>false));
	    shn_form_submit(_t("Markers"));
        shn_form_fclose();
        print "</td><td style=\"border: 0px;\">";
        shn_form_fopen(gis_projections,admin,array('req'=>false));
	    shn_form_submit(_t("Projections"));
        shn_form_fclose();
        print "</td></tr></table>";
    }
	
	// call GIS API
	include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_gis_map_with_wiki_markers($map_array);
}

/**
 * Image Upload Form as part of adding situations
 * @access public
 * @return void
 */
function shn_sm_show_wiki_add_image()
{
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
	shn_form_fsopen(_t("Situation Image"));
	shn_form_upload(_t("Upload Image"),'image');
	shn_form_fsclose();
	shn_form_submit(_t('Next'));
	shn_form_fclose();
}

/**
 * Show GIS Map with Wiki addition event listener
 * Part of add situation sequence
 * @access public
 * @return void 
 */
function shn_sm_show_wiki_add_map($errors=false)
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
    
	include $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_form_fopen(awik,null,array('req'=>false));
	shn_form_hidden(array('seq'=>'img'));
	//call GIS API
	shn_gis_add_marker_map_form();
	shn_form_submit(_t("Next"));
	shn_form_fclose();
}


//-----------------------------
//replaces Mifan's shn_gis_show
function map_client($errors=false)
{
	global $global;
	include_once $global['approot'] . "/inc/lib_errors.inc";
	
	//if($errors){
	//	add_error(_t("Detail Name Cannot be empty"));
	//}
	global $global;
	global $conf;
	include_once $global['approot']."/inc/lib_form.inc";
  	include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
	
?>
	<h2><?=_t("Mapping Client")?></h2>
	<p></p>
<?php

	// Mapping comes here
	$options=array();
  	if((isset($_POST['mapa_x'])) && isset($_POST['mapa_y'])){
  	}
  	shn_gis_map();	
}

/**
 * Situation add form
 * start of sequence with error checking
 * @param boolean $errors true if errors exist,false otherwise
 * @access public
 * @return void
 * @TODO: add javascript calendar for date input
 */
function shn_sm_show_wiki_add_detail($errors=false)
{
	global $global;
	global $conf;
	include_once $global['approot'] . "/inc/lib_errors.inc";
	
	if($errors){
		add_error(_t("'Name of situation detail' field cannot be empty"));
	}

	include_once $global['approot']."/inc/lib_form.inc";
?>
	<h2><?=_t("Add Situation Detail")?></h2>
<?php
	
	shn_form_fopen(awik);
	shn_form_fsopen(_t("Main Details"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_t("Name of situation detail"),"wiki_name",'size="50"',array('req'=>true,'help'=>_t($conf['mod_sm_situation_name_help'])));
	shn_form_opt_select("opt_wikimap_type",_t("Wiki Type"),null,array('help'=>_t($conf['mod_sm_situation_type_help'])));
	shn_form_textarea(_t("Detail Summary"),"wiki_text",'size="50"');
	shn_form_fsclose();
	shn_form_fsopen(_t("Extra Details"));
	shn_form_text(_t("URL"),"wiki_url",'size="50"',array('help'=>_t($conf['mod_sm_situation_url_help'])));
	//shn_form_text(_t("Date of //Event"),"wiki_evnt_date",'size="50"',array('help'=>_t($conf['mod_sm_situation_date_help'])));
	shn_form_date(_t("Date of Event"),"wiki_evnt_date",array('req'=>true,'value'=>date('Y-m-d'),'help'=>_t($conf['mod_sm_situation_date_help'])));
	shn_form_fsclose();
	shn_form_fsopen(_t("Wikimap Options"));
	shn_form_text(_t("Author"),"wiki_author",'size="50"',array('help'=>_t($conf['mod_sm_situation_author_help'])));
	shn_form_checkbox(_t("Publicly Editable"),"edit_public",null,array('value'=>'edit'));
	shn_form_checkbox(_t("Publicly Viewable"),"view_public",null,array('value'=>'view'));
	shn_form_fsclose();
	shn_form_submit(_t("Add Detail"));
	shn_form_fclose();
}

function shn_sm_wiki_edit($id)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$query="SELECT wiki_uuid,description FROM gis_wiki WHERE wiki_uuid='{$id}'";
	$res=$db->Execute($query);
	$desc=$res->fields['description'];
	
	include_once $global['approot']."/inc/lib_form.inc";
	shn_form_fopen(ewik);
	shn_form_fsopen(_t("Update Detail"));
	shn_form_textarea(_t("Detail Summary"),"wiki_text",'size="50"',array('value'=>$desc));
?>
	<input type="hidden" name="wiki_id" value="<?=$res->fields['wiki_uuid']?>">
<?php
	shn_form_fsclose();
	shn_form_submit(_t("Commit Detail"));
	shn_form_fclose();
}

function shn_sm_wiki_edit_com($id)
{
	global $global;
	global $conf;
	$db = $global['db'];
	$query="update gis_wiki set description='{$_REQUEST['wiki_text']}' WHERE wiki_uuid='{$id}'";
	$res=$db->Execute($query);
	add_confirmation(_t('Succesfully updated description'));
}

/**
 * Commit to database
 * @todo handle OGC/non-OGC DBs.
 * @todo Confirm with list on action to take
 */
function shn_sm_wiki_map_commit()
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
	$view_public=($_SESSION['view_public']=='view')?1:0;
	$query = " insert into gis_wiki (wiki_uuid,gis_uuid,name,description,opt_category,url,event_date,editable,author,approved) " .
			 " values ('{$wiki_id}','{$gis_id}','{$_SESSION['wiki_name']}','{$_SESSION['wiki_text']}','{$_SESSION['opt_wikimap_type']}', " .
			 "'{$_SESSION['wiki_url']}','{$_SESSION['wiki_evnt_date']}','{$edit}','{$_SESSION['wiki_author']}','{$view_public}')";
			 
	$res=$db->Execute($query);
	//var_dump($_SESSION);
	include $global['approot']."/inc/lib_gis/gis_fns.inc";
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
		
	    if(move_uploaded_file($_FILES['image']['tmp_name'], $uploadfile)){
	    	//success
	    }
	    else{
			//false;
	    }
	    $thumb_path = $upload_dir .'wiki_thumb_'.$wiki_id.$ext;
	    //create thumbnail
	    shn_image_resize($uploadfile,$thumb_path,100,100);
	}

	add_confirmation(_t("Succesfully added wiki item ").$_SESSION['wiki_name']);
}

/**
 * Report on Situations within a Radius of a Position
 */
function shn_sm_analysis_radius_form()
{
    shn_form_fopen('radius_analyse',null,array('req_message'=>true));
    shn_form_fsopen(_t('Situation Analysis'));
    shn_form_fsopen(_t('Radius'));
    echo '<p>'._t("Report on which situations are located within a specified radius of a selected location").'.</p>';
    shn_form_fsclose();
    $lat_help=_t("Latitude is North-South (Up-Down). Latitude is zero on the equator and positive in the northern hemisphere and negative in the southern hemisphere");
	$lon_help=_t("Longitude is West - East (sideways). Longitude is zero on the prime meridian (Greenwich Mean Time) and is positive to the east, across Europe and Asia.  Longitude is negative to the west, across the Atlantic and the Americas.");
	$radius_help=_t("Distance from the selected location to the search circle's edge - measured in kilometers.");
	shn_form_text(_t('Latitude: '),"sm_radius_lat",'size=40',array('req'=>true,"help"=>$lat_help));
	shn_form_text(_t('Longitude: '),"sm_radius_lon",'size=40',array('req'=>true,"help"=>$lon_help));
	shn_form_text(_t('Radius (km): '),"sm_radius_distance",'size=40',array('req'=>true,"help"=>$radius_help));
	shn_form_fsclose();
    shn_form_submit(_t('Analyse'));
    shn_form_fclose();
}

/**
 * Report on Situations within a Radius of a Position
 */
function shn_sm_radius_analyse_process()
{
    global $global;
    global $conf;
    if(!null==$_POST['sm_radius_lat'] && !null==$_POST['sm_radius_lon'] && !null==$_POST['sm_radius_distance']){
        // ToDo: http://wiki.sahana.lk/doku.php?id=dev:form_validation
        $lat = floatval($_POST['sm_radius_lat']);
        $lon = floatval($_POST['sm_radius_lon']);
        $radius = $_POST['sm_radius_distance'];
        
        // call GIS API
        include_once $global['approot']."/inc/lib_gis/gis_fns.inc";
        $array = shn_gis_features_in_radius($lat,$lon,$radius);
        
        if(!0==sizeof($array)){
            print '<h2>'._t("Radius Report").'</h2>';
            if ($lat > 0) {
                $northing = "N";
            } else {
                $northing = "S";
                $lat = ltrim($lat,"-");
            }
            if ($lon > 0) {
                $easting = "E";
            } else {
                $easting = "W";
                $lon = ltrim($lon,"-");
            }
            print '<p>'._t("These are the Situations within a")." $radius km "._t("radius of")." $lat $northing, $lon $easting:</p>";
            print '<table><thead><td>'._t("Situation").'</td><td>'._t("Distance").'</td><td>Lat</td><td>Lon</td></thead><tbody>';
            for($i=0;$i< sizeof($array);$i++){
				$poc_uuid=$array[$i]["poc_uuid"];
                // ToDo: Filter for only Situations
                $lat=$array[$i]["lat"];
				$lon=$array[$i]["lon"];
				$distance=$array[$i]["distance"];
                // ToDo: Make entries into clickable links
                print "<tr><td>$poc_uuid</td><td>$distance</td><td>$lat</td><td>$lon</td></tr>";
            }
            print "</tbody></table>";
        } else {
            add_confirmation(_t('No Situations found within this Radius'));
            shn_sm_analysis_radius_form();
        }
    } else {
        add_warning(_t('Not all fields have data. Not possible to run analysis'));
        shn_sm_analysis_radius_form();
    }
  
}
?>

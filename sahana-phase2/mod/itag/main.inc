<?php
/**Main Controller of the Light GIS 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><http://r4vi.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
//
global $global;
include_once $global['approot']."/inc/lib_errors.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/reporting/lib_chart.inc";
include_once $global['approot']."/inc/reporting/lib_reporting.inc";
include_once $global['approot']."/inc/lib_paging.inc";
require_once "lib_itag.inc";

function shn_itag_mainmenu() 
{
    global $global;
    global $conf;
    $module = $global['module'];
  //  $loc=_shn_or_get_start_loc();
    shn_mod_menuopen(_lc($conf['mod_itag_name']));
    shn_mod_menuitem("default",_t("Home"),$module);
    shn_mod_menuitem("upload",_t("Upload JPEG Image"),$module);
    shn_mod_menuitem("view",_t("View Maps"),$module);
 	shn_mod_menuitem("plot_select",_t("Plot points"),$module);
//    shn_mod_menuitem("display",_t("Display points"),$module);
    shn_sub_mod_menuclose();
    shn_mod_menuclose();
    
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

function shn_itag_upload(){
    shn_form_fopen('upload_submit',null,array('enctype'=>'enctype="multipart/form-data"'));
   	shn_form_fsopen(_('Map Details'));
   	shn_form_text(_("Name  : "),'name','size="50"',null);
   	shn_form_text(_("Description  : "),'desc','size="50"',null);
   	shn_form_fsclose();
    shn_form_fsopen(_('Upload a JPEG Map'));
    shn_form_upload(_('Image'),"map");
    shn_form_fsclose();
    shn_form_submit(_("Save"));
    shn_form_fclose();
	
}

function shn_itag_upload_submit(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");
    $db=$global["db"];
    $map_id	=shn_create_uuid('map');
    $info = getimagesize($_FILES["map"]['tmp_name']);
	$width_orig = $info[0];
	$height_orig = $info[1];
    $sql="insert into maps(map_uuid,name,description,width,height)values('{$map_id}','{$_POST["name"]}','{$_POST["desc"]}',{$width_orig},{$height_orig})";
    $res=$db->Execute($sql);
    if($_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
		shn_image_save_to_file("map","res/img/itag","jpeg_maps",$map_id);
    } 
    add_confirmation(_(" Map was succesfully saved"));
	
}
function shn_itag_plot_select(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");
	$maps=_shn_itag_get_all_maps();
	foreach($maps as $id=>$details){
		?>

		<a href="index.php?mod=itag&amp;act=plot_map&amp;map_id=<?php echo $id;?>"><?php echo $details["name"];?></a><br />
		<?php
		
	}
}
function shn_itag_plot_map(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");
	$id=$_GET["map_id"];
	$details=_shn_itag_get_map_details($id);

	
		?>
		<div>
		Name:<?php echo $details["name"];?><br />
		Description:<?php echo $details["desc"];?><br />
		</div>

<?php
	shn_form_fopen('plot_point_submit',null);
?>
<input name="itag_map" type="image" id="itag_map" src="index.php?stream=image&amp;mod=itag&amp;act=display_map_with_points&amp;media_id=<?php echo $details["media_id"];?>&amp;map_id=<?php echo $id;?>" width="<?php echo $details["width"];?>" height="<?php echo $details["height"];?>" border="0">
<br />
<?php 
	shn_form_fsopen();
	shn_form_text(_("Name  : "),'name','size="50"',null);
	shn_form_text(_("Description  : "),'desc','size="50"',null);
	shn_form_fsclose();
	shn_form_hidden(array("map_id"=>$id));
	shn_form_fclose();
	
}
function shn_itag_view(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");
	$maps=_shn_itag_get_all_maps();
	foreach($maps as $id=>$details){
		?>
		Name:<?php echo $details["name"];?><br />
		Description:<?php echo $details["desc"];?><br />
		<img src="index.php?stream=image&amp;mod=itag&amp;act=display_map&amp;media_id=<?php echo $details["media_id"];?>" /><br />
	<!--	<input name="map" type="image" src="index.php?stream=image&amp;mod=itag&amp;act=display_map&amp;media_id=<?php echo $details["media_id"];?>" />-->
		<?php
		
	}
}
function shn_image_itag_display_map(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	_shn_image_media_get($_GET["media_id"]);
}
function shn_image_itag_display_map_with_points(){
	global $global;
	
	//include_once($global['approot']."/inc/lib_image.inc");
	_shn_itag_display_marked_map($_GET["map_id"]);
}

function shn_itag_plot_point_submit(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");
	//var_dump($_POST);
    $db=$global["db"];
    $point_uuid	=shn_create_uuid('point');
    $map_id=$_POST["map_id"];
    $lat=$_POST["itag_map_y"];
    $long=$_POST["itag_map_x"];
    $name=$_POST["name"];
    $desc=$_POST["desc"];
    $type="sample";
    $sql="insert into map_points(point_uuid,map_uuid,type,name,description,latitude,longitude) values('{$point_uuid}','{$map_id}','{$type}','{$name}','{$desc}',{$lat},{$long})";

    $res=$db->Execute($sql);
	shn_itag_plot_select();
}
function shn_itag_default(){
	
}

function shn_itag_display(){
	
}


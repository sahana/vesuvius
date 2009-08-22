<?php

/**
* Waypoint Handling for GPS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;

include_once ($global['approot'].'/inc/lib_form.inc');
include_once $global['approot']."/mod/gps/conf_help.inc";
include_once $global['approot']."/mod/gps/main.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";

function shn_marker_add_detail($errors=false)
{
  global $global;
  global $conf;
	include_once $global['approot'] . "/inc/lib_errors.inc";
	
	if($errors){
		add_error(_("Name of Marker Cannot be empty"));
	}
?>
	<h2><?php echo _("Add Marker Detail")?></h2>
<?php
	
	shn_form_fopen(marker);
	shn_form_fsopen(_("Main Details"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_("Name of Waypoint"),"marker_name",'size="50"',array('req'=>true,'help'=>_($conf['mod_gps_marker_name_help'])));
	shn_form_opt_select("opt_wpt_type",_("Waypoint Type"),null,array('help'=>_($conf['mod_gps_marker_type_help'])));
	shn_form_textarea(_("Waypoint Description"),"marker_text",'size="50"');
        shn_form_fsclose();
	shn_form_submit(_("Add Detail"));
	shn_form_fclose();
}

function shn_marker_add_map($errors=false)
{
    global $global;
    if($errors){
        display_errors();
    }
    else{
	$_SESSION['marker_name'] = $_POST['marker_name'];
	$_SESSION['opt_wpt_type'] = $_POST['opt_wpt_type'];
	$_SESSION['marker_text'] = $_POST['marker_text'];
	$_SESSION['marker_author'] = $_POST['marker_author'];

    }
    
	include $global['approot']."/inc/lib_gis/gis_fns.inc";
	shn_form_fopen(marker,null,array('req'=>false));
	shn_form_hidden(array('seq'=>'img'));
	// call GIS API
	shn_gis_add_marker_map_form();
	shn_form_submit(_("Next"));

}

function shn_marker_add_file()
{
	if(isset($_POST['loc_x']) && $_POST['loc_y']!=''){
		$_SESSION['loc_x']=$_POST['loc_x'];
		$_SESSION['loc_y']=$_POST['loc_y'];
	}
	$form_opts['name']="add_waypoints";
	$marker_type=find_marker_type($_SESSION['opt_wpt_type']);
	$form_opts['name']="add_waypoints";
	shn_form_fopen("add",null,$form_opts);
	shn_form_hidden(array('seq'=>'com'));
	?><h2><?php echo _("Confirm Details of Marker ").$_SESSION['marker_name']?></h2><div id="formcontainer">
<?php
		
	shn_form_fsopen(_("Marker Details"));
	shn_form_label(_("Marker Name"),$_SESSION['marker_name']);
	shn_form_label(_("Marker Type"),$marker_type);
	shn_form_label(_("Marker Description"),$_SESSION['marker_text']);
	shn_form_label(_("Marker Latitude"),$_SESSION['loc_x']);
	shn_form_label(_("Marker Longitude"),$_SESSION['loc_y']);

	
	shn_form_fsclose();
?><br /><center>
<?php
//create the submit button
	$extra_opts['br'] = false;
	shn_form_submit(_("Add to File"),"name=\"button1\"");
	shn_form_submit(_("Cancel"),"name=\"button1\"");
	        	
?>
</center><br />

<?php	
	shn_form_fclose();
?>				     
</div>
<?php	
}
function shn_marker_add_download()
{
	add_confirmation($_SESSION['marker_name']._(" was successfully added to a downloadable marker file"));

//////////////	
?>
  <center>  <div id="result_msg">
    <?php
    $form_opts['name']='choose';
    $form_opts['req_message']=false;
    shn_form_fopen("add",null,$form_opts);
    	$extra_opts['br']=false;
	$extra_opts['req']=false;
	shn_form_fsopen('Add Markers');
	shn_form_hidden(array('seq'=>'trip'));
	$msg=_("Now you can add more Markers to this file By clicking the Add More Markers Button");
    ?><div class="info"><?php echo $msg?></div><br /><?php
    shn_form_submit(_("Add More Markers"),"name=\"button1\"");
	shn_form_fsclose();
	
	shn_form_fsopen('Download File');
	$msg=_("Instead if you have added necessary markers to marker file, click the button below to download it.")."<br />";
     ?><div class="info"><?php echo $msg?></div><br /><?php
	shn_form_submit(_("Download File"),"name=\"button1\"");
	shn_form_fsclose();
?>
</center>
<br />
<?php
////////////
}
function shn_add_marker_to_file($addmarker=false)
{
	global $conf;

	$marker_type=find_marker_type($_SESSION['opt_wpt_type']);
	$x_cord=$_SESSION['loc_x'];
	$y_cord=$_SESSION['loc_y'];

	$data="\n<wpt lat=\"$x_cord\" lon=\"$y_cord\">"."\n"."<name>".$_SESSION['marker_name']."</name>"."\n"."<desc>".$_SESSION['marker_text']."</desc>"."\n"."</wpt>";

	if(file_exists($conf['output']))
	{
		unlink($conf['output']);
	}

	if(file_exists($conf['input']))
	{
	 $fh = fopen($conf['input'], "a");
	}
	else
	$fh = fopen($conf['input'], "w");
        $success = fwrite($fh, $data);
        fclose($fh);
	
}

function find_marker_type($type)
{
	global $global;
	$db = $global['db'];

	$search="SELECT option_description FROM field_options WHERE field_name='opt_wpt_type' AND option_code='{$type}'";
	$res = $global['db']->Execute($search);
	
	return $res->fields['option_description'];
}

function shn_gps_add()
{
	switch($_POST['button1']){
	case "Add to File":
	shn_marker_add_download();
	shn_add_marker_to_file(true);
	break;	
	case "Cancel":
	shn_marker_add_detail();
	break;
	case "Add More Markers":
	shn_marker_add_detail();
	break;
	case "Download File":
	shn_gps_add_author();
	}

}

function shn_gps_add_author()
{

	global $conf;
	$form_opts['name']='choose';
        $form_opts['req_message']=false;
	shn_form_fopen("add_download&stream=text",null,$form_opts);
	shn_form_fsopen('File Author');
	shn_form_text(_("Name of Author"),"author_name",'size="50"',array('help'=>_($conf['mod_gps_marker_author_help'])));
	shn_form_submit(_("Download File"),"name=\"button1\"");
	shn_form_fsclose();
	shn_form_fclose();
}

function shn_text_gps_add_download()
{
	global $conf;

	if(trim($_POST['author_name'])=="")
	$author="anonymous";
	else
	$author = trim($_POST['author_name']);
	$gpx="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gpx version=\"1.0\" creator=\"Sahana - $author\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n xmlns=\"http://www.topografix.com/GPX/1/0\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">";

	$file_name="Sahana-Markers.gpx";
  	header("Content-type: text/gpx");
    	header("Content-Disposition: attachment; filename=".$file_name);
     	header("Cache-Control: no-cache, must-revalidate");

	$handle2 = fopen($conf['output'], "a");
	if(file_exists($conf['input']))
	{
	$handle1 = fopen($conf['input'], "r");
	$contents = fread($handle1, filesize($conf['input']));
	fwrite($handle2,$contents);
	fclose($handle1);
	unlink($conf['input']);
	fclose($handle2);
	}

	$handlex = fopen($conf['output'], "r");
	$data = fread($handlex, filesize($conf['output']));
	fclose($handlex);
	
    	print $gpx.$data."\n</gpx>";
}


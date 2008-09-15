<?php

/**
* Marker Handling Page of GPS Module
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Sriganeshan <sri@opensource.lk>
* @author     Fran Boon <flavour@partyvibe.com>
* @author     Richard Smith <s0459387@sms.ed.ac.uk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
global $conf;
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/mod/gps/main.inc";
include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_validate.inc";

function shn_gps_find_waypoint()
{
?>
<h2><?=_("Download Waypoints")?></h2>
<?php
	shn_form_fopen("waypoint",null,null,array('req'=>false));
	shn_form_fsopen(_("Waypoint Details"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_opt_select("opt_wpt_type","Waypoint Types");
	shn_form_text(_("Name of Author"),"author_name",'size="20"',array('req'=>false));
	shn_form_date(_("Date of Event"),"wiki_evnt_date",array('req'=>false,'help'=>_($conf['mod_gps_marker_date_help'])));
	shn_form_text(_("Name of Waypoint"),"marker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();
	shn_form_submit(_("Search"));
	shn_form_fclose();
    shn_form_fopen(marker,null,array('req'=>false));
    shn_form_submit(_t("Add Marker(s) to Download"));
    shn_form_fclose();
}

function _shn_gps_select_waypoint($type,$author_name,$date,$marker_name)
{
    global $global;
    $db = $global['db'];
    if($author_name==null & $date==null & $marker_name==null) {
        $search= "Select * from gpx_file where opt_category='{$type}'";
    } else if($author_name!=null & $date==null & $marker_name==null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND author_name LIKE '%{$author_name}%'"; 
    } else if($author_name==null & $date!=null & $marker_name==null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND event_date='{$date}'";
    } else if($author_name==null & $date==null & $marker_name!=null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND point_name LIKE'%{$marker_name}%'";
    } else if($author_name!=null & $date!=null & $marker_name==null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND author_name LIKE '%{$author_name}%' AND event_date='{$date}'"; 
    } else if($author_name!=null & $date==null & $marker_name!=null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND author_name LIKE '%{$author_name}%' AND point_name LIKE'%{$marker_name}%'"; 
    } else if($author_name==null & $date!=null & $marker_name!=null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND point_name LIKE'%{$marker_name}%' AND event_date='{$date}'"; 
    } else if($author_name!=null & $date==null & $marker_name!=null) {
        $search= "Select * from gpx_file where opt_category='{$type}' AND author_name LIKE '%{$author_name}%' AND point_name LIKE'%{$marker_name}%' AND event_date='{$date}'"; 
    }
    $results = $db->Execute($search);
    return $results;
}

function shn_gps_display_points()
{
	$type = $_POST['opt_wpt_type'];
	$author_name = trim($_POST['author_name']);
	$date = trim($_POST['wiki_evnt_date']);
	$marker_name = trim($_POST['marker_name']);
	$results=_shn_gps_select_waypoint($type,$author_name,$date,$marker_name);
	if(file_exists("tmp/tmp.txt")) {
        unlink("tmp/tmp.txt");
	}	
?>
<h2><?=_("Search Results")?></h2>
<?php
	shn_form_fopen("waypoint",null,null,array('req'=>false));
	shn_form_fsopen(_("Select Markers"));
	shn_form_hidden(array('seq'=>'add'));
	$count=0;
?>
	<br />
    <div id ="result">
	<table>
    <thead>
     <td><?=_("Marker Name")?></td>
     <td><?=_("Marker Description")?></td>
     <td><?=_("Marker Author")?></td>
     <td><?=_("Event Date")?></td>
     <td><?=_("Marker Type")?></td>
     <td><?=_("Select")?></td>
    </thead>
<?php
    while( !$results==NULL && !$results->EOF ) {
        ++$count;
        $id=$results->fields['point_uuid'];
?>
        <tr>
         <td><?= $results->fields['point_name']?></td>
         <td><?= $results->fields['description']?>
         <td><?= $results->fields['author_name']?></td>
         <td><?= $results->fields['event_date']?></td>
         <td><?= $results->fields['opt_category']?></td>
         <td><?=shn_form_checkbox($count,$count,null,array('value'=>$id))?></td>
        </tr>
<?php
        $results->MoveNext();
    }
?>
    </table>
    </div>
	<br />
    <center>
<?php
    shn_form_hidden(array('count'=>$count));
    shn_form_submit(_("Download Markers"),"name=\"button1\"");
    shn_form_submit(_("New Search"),"name=\"button1\"");
?>
    </center> 
    <br />
<?
    shn_form_fsclose();
    shn_form_fclose();
}

function shn_text_gps_create_file()
{
	$temp="tmp/tmp.txt";
	if(trim($_POST['author_name'])=="") {
        $author="anonymous";
    } else {
        $author = trim($_POST['author_name']);
    }
	$handle1=fopen($temp,"r");
	if(filesize($temp)!=0)
	$contents = fread($handle1,filesize($temp));
	fclose($handle1);
    //$limit=$_REQUEST['count'];
	$point_store="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gpx version=\"1.0\" creator=\"Sahana - $author\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n xmlns=\"http://www.topografix.com/GPX/1/0\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">\n";
	$file_name="Sahana-Marker.gpx";
  	header("Content-type: text/gpx");
    header("Content-Disposition: attachment; filename=".$file_name);
    header("Cache-Control: no-cache, must-revalidate");
	print $point_store.$contents."</gpx>";
}

function shn_gps_add_creator()
{
	$limit=$_REQUEST['count'];
    global $global;
    $db = $global['db'];
	//echo $limit;
	$create_point="";
	for($counter=1;$counter<$limit+1;++$counter) (
		if(isset($_POST[$counter])) {
			$_SESSION[$counter]=$_POST[$counter];
			$id=$_SESSION[$counter];
			//echo $id;
			$search="SELECT gpx_file.point_name, gpx_file.description,gis_location.map_northing, gis_location.map_easting
			FROM gpx_file,gis_location
			WHERE gpx_file.point_uuid=gis_location.poc_uuid AND gpx_file.point_uuid='{$id}'";
			$results = $db->Execute($search);
			$latitude=$results->fields['map_northing'];
			$longitude=$results->fields['map_easting'];
			$point_name=$results->fields['point_name'];
			$description=$results->fields['description'];
			$create_point=$create_point."<wpt lat=\"".$latitude."\" lon=\"".$longitude."\">\n<name>".$point_name."</name>\n<desc>".$description."</desc>\n</wpt>\n";
        }
	}
	$temp="tmp/tmp.txt";
	$handle1=fopen($temp,"a");
	fwrite($handle1,$create_point);
	fclose($handle1);
	global $conf;
	$form_opts['name']='choose';
    $form_opts['req_message']=false;
	shn_form_fopen("create_file&stream=text",null,$form_opts);
	shn_form_fsopen('File Author');
	shn_form_text(_("Name of Author"),"author_name",'size="50"',array('help'=>_($conf['mod_gps_marker_author_help'])));
	shn_form_submit(_("Download File"));
	shn_form_fsclose();
	shn_form_fclose();
}

?>

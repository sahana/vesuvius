<?php
/**
* Marker Handling Page of GPS Module
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Sriganeshan <sri@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
global $global;
global $conf;
//global $doc;
include_once($global['approot'].'/inc/lib_location.inc');
include_once $global['approot']."/mod/gps/conf.inc";

function shn_gps_point_sort_start(){
	if(isset($_SESSION['gps']['file']))
	{

	$current_file = $_SESSION['gps']['file'];
	$handle1 = fopen($current_file, "r");
	$contents = fread($handle1, filesize($current_file));
	fclose($handle1);
	$handle2 = fopen("../www/tmp/dom.txt", "w+");
	fwrite($handle2,$contents);
	fclose($handle2);

	shn_gps_point_sort();

	}
		
}
function shn_gps_point_sort()
{
global $global;
global $range;
	print '<center><h2>' . _("Uploaded Waypoints") . '</h2></center>';
	shn_form_fopen("classify",null,null);
	shn_form_fsopen(_("Select Waypoint Type")." <span class='req'>   *req </span>");
	shn_form_opt_select("opt_wpt_type","Waypoint/Marker Types");	
	shn_form_fsclose();
	shn_form_fsopen('File Author');
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_("Name of Author"),"author_name",'size="20"',array('help'=>_($conf['mod_gps_file_author_help']),'req'=>true));
	shn_form_fsclose();
	shn_form_fsopen(_("Select Waypoints"));
?>
	<enter ="result">
    <center>
    <table>
        <thead>
        <td><?=_("Point Name");?></td>
        <td><?=_("Point Description");?></td>
        <td><?=_("Point Latitude");?></td>
	<td><?=_("Point Lontitude");?></td>
	<td><?=_("Sequence No");?></td>
	<td><?=_("Check");?></td>
        </thead>
    <tbody>
<?php

	$doc1 = new DOMDocument;
	$doc1->load("../www/tmp/dom.txt");
	$_SESSION['file']['time']=$doc1->getElementsByTagName('time')->item(0)->nodeValue;
	$items = $doc1->getElementsByTagName('wpt');
	$_SESSION['point']['count']=$items->length;
	
	for ($i = 0; $i < $items->length; $i++) {
	$point_name=$items->item($i)->getElementsByTagName('name')->item(0)->nodeValue;

	if(trim($point_name)=='')
		$point_name="Unknown";	
	$point_description=$items->item($i)->getElementsByTagName('desc')->item(0)->nodeValue;
	$point_latitude=$items->item($i)->getAttribute('lat');
	$point_longitude=$items->item($i)->getAttribute('lon');
?>	
	<tr>
	<td><center><?php print $point_name;?></center></td>
	<td><center><?php print $point_description;?></center></td>
	<td><center><?php print $point_latitude;?></center></td>
	<td><center><?php print $point_longitude;?></center></td>
	<td><center><?php print $i;?></center></td>
	<td><center><?php shn_form_checkbox($i,$i,null,array('value'=>$i));?></center></td>
	</tr>
<?php
	$doc1->save("../www/tmp/dom.txt");
	
    }
?>
	</tbody>
	</table>
        </center>
<?php
	shn_form_fsclose();
?>
<center>
<?php	if(($items->length)!=0)
	shn_form_submit(_("Save Waypoints"),$items->length,null,null);
	else
	echo "<p><em><strong>"._('message: ')."</strong></em>"._('your file contains no waypoints')."</p>";

?>
</center>
<?
	shn_form_fclose();
}

function shn_gps_save_points()
{
	
	$checked=false;
	$author="";
	$chapter=null;	
	$author=trim($_POST['author_name']);
	$date=current(explode('T',$_SESSION['file']['time']));
	for($x=0; $x < $_SESSION['point']['count']; ++$x)
	{			
		if(isset($_POST[$x]))
		{
		$checked=true;
		}
	}


if(!$checked){
		add_error('You have not selected any waypoints. Please select waypoint(s)');
		shn_gps_point_sort();
	}
    else if($author==""){
	add_error(_('File author name is required. Please enter author name'));
	shn_gps_point_sort();
	}
	else{

		$doc2 = new DOMDocument;
	$doc2->load("../www/tmp/dom.txt");
    		$_SESSION['wpt']['loc']=$loc;
		$_SESSION['opt_wpt_type'] = $_POST['opt_wpt_type'];
	
		$tester=false;
		$items = $doc2->getElementsByTagName('wpt');
		$count = $items->length;
		$k=0;
		$a=0;
		for($x=0; $x < $count; ++$x)
		{		
				
			if(isset($_POST[$x]))
			{
				$handler=$doc2->documentElement;
				if($tester){
					++$a;
					$k=$x-$a;
					$chapter = $handler->getElementsByTagName('wpt')->item($k);
					$oldchapter = $handler->removeChild($chapter);
					$doc2->save("../www/tmp/dom.txt");
				}
				else{
					$k=$x;
					$chapter = $handler->getElementsByTagName('wpt')->item($k);
			
					$oldchapter = $handler->removeChild($chapter);
					$doc2->save("../www/tmp/dom.txt");
					$tester=true;
			
				}
				$name=$chapter->getElementsByTagName('name')->item(0)->nodeValue;
				$description=$chapter->getElementsByTagName('desc')->item(0)->nodeValue;
				$latitude=$chapter->getAttribute('lat');
				$longitude=$chapter->getAttribute('lon');
				if(trim($name)==null)
					$name="unknown";
				shn_gps_point_save($author,$date,$_SESSION['opt_wpt_type'],$name,$description,$latitude,$longitude);
			
			}
		
		}
				
	

		if(!($point_count=$items->length)>0)
		{  
			add_confirmation(_('All your waypoints were saved successfully...'));
			shn_gps_upload();
		}
		else
		{
			add_confirmation(_('Selected waypoints were saved successfully...'));
			shn_gps_point_sort();
		}
    	}

}



function shn_gps_point_save($author,$date,$type,$name,$description,$latitude,$longitude)
{//echo "amma";
	global $global;
	$db = $global['db'];
	include_once($global['approot'].'/inc/lib_uuid.inc');	
	$point_id=shn_create_uuid('gps');
	
	$no=0;
	$route_name="waypoint";
	$route_no=$no;
	$gis_id=shn_create_uuid('g');
	$query="INSERT INTO gis_location ( poc_uuid , location_id , opt_gis_mod , map_northing , map_easting , map_projection , opt_gis_marker , gis_uid) VALUES ( '{$point_id}', NULL , NULL , '{$latitude}' , '{$longitude}' , NULL , NULL , '{$gis_id}')";

	$res = $db->Execute($query);

	$query = "INSERT INTO gpx_file ( point_uuid , author_name , event_date , route_name , route_no , opt_category , sequence_no , point_name , description )
	VALUES ( '{$point_id}' , '{$author}' , '{$date}', '{$route_name}' , '{$route_no}' , '{$type}' , '{$no}' , '{$name}' , '{$description}')";
	
	$res = $db->Execute($query);

	
}

?>
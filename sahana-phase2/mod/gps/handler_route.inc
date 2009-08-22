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
include_once ($global['approot'].'/inc/lib_form.inc');
//include_once $global['approot']."/inc/lib_modules.inc";
//include_once $global['approot']."/inc/lib_menu.inc";
//include_once $global['approot']."/inc/lib_validate.inc";

function shn_gps_find_route()
{

?>
<h2><?php echo _("Download Route")?></h2>
<?php

	
	shn_form_fopen("route_download",null,null,array('req'=>false));
	shn_form_fsopen(_("Origin Point Detail"));
	shn_form_hidden(array('seq'=>'map'));
	shn_form_text(_("Name of Marker"),"orignmarker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();

	shn_form_fsopen(_("Destination Point Detail"));
	shn_form_text(_("Name of Marker"),"destmarker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();

	shn_form_fsopen(_("Point immediately next to Origin"));
	shn_form_text(_("Name of Marker"),"imm_nxt_org_marker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();

	shn_form_fsopen(_("Point before destination"));
	shn_form_text(_("Name of Marker"),"imm_befor_dest_maker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();

	shn_form_fsopen(_("Mid Point on Route"));
	shn_form_text(_("Name of Marker"),"midmarker_name",'size="20"',array('req'=>false));
	shn_form_fsclose();

	shn_form_submit(_("Search"));
	shn_form_fclose();


}

function shn_gps_display_routes()
{
	
$results=shn_gps_view_all();
?>
<h2><?php echo _("Search Results")?></h2>
<?php
	shn_form_fopen("route_creator",null,null,array('req'=>false));
	shn_form_fsopen(_("Create Route"));
	shn_form_hidden(array('seq'=>'add'));
	$count=0;	

	echo "<p><em><strong>"._('information: ')."</strong></em>"._('You may dynamically create your route by selecting route points.')."</p>";
	if(file_exists("../www/tmp/route.txt"))
	{
		unlink("../www/tmp/route.txt");
	}
?>
<br />
    <div id ="result">
	<table>
        <thead>
            <td><?php echo _("Author Name")?></td>
            <td><?php echo _("Event Date")?></td>
            <td><?php echo _("Route Name")?></td>
            <td><?php echo _("Point Name")?></td>
            <td><?php echo _("Point Description")?></td>
            <td><?php echo _("Select")?></td>

          </thead>
        <?php
        while( !$results==NULL && !$results->EOF )
        {
		++$count;
		$id=$results->fields['point_uuid'];
		
        ?>
        <tr>
 
        <td><?php echo  $results->fields['author_name']?></td>
        <td><?php echo  $results->fields['event_date']?></td>
        <td><?php echo  $results->fields['route_name']?></td>
        <td><?php echo  $results->fields['point_name']?></td>
        <td><?php echo  $results->fields['description']?></td>
        <td><?php echo shn_form_checkbox($count,$count,null,array('value'=>$id))?></td>
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
	shn_form_submit(_("Download Route"),"name=\"button1\"");
	//shn_form_submit(_("New Search"),"name=\"button1\"");
?>
	</center>
<br />
<?php
	shn_form_fsclose();
	shn_form_fclose();
}

function shn_gps_sort_input($org_type,$org_author,$org_date,$org_name,$dest_name,$next_org_name,$befor_dest_name,$mid_point_name)
{

		global $global;
		$db = $global['db'];

		//$query_main="SELECT  point_uuid,author_name,event_date, opt_category,point_name, route_name,description from gpx_file where (route_name != 'waypoint' ) ";
		//$query_main=" select distinct route_name, from gpx_file where route_name!='waypoint' AND route_name!='-'";

		$query_main="SELECT  point_uuid,author_name,event_date, opt_category,point_name, route_name,description from gpx_file where (route_name != 'waypoint' AND route_name='Borella-Nugegoda')";
		if($org_name!=null || $dest_name!=null ||$next_org_name!=null ||$befor_dest_name!=null ||$mid_point_name){
		$query_main=$query_main." AND (";
		if($org_name!=null)
		{
		$query_main=$query_main."  point_name='{$org_name}'";
		}
		if($dest_name!=null)
		{
		$query_main=$query_main." OR point_name='{$dest_name}'";
		}
		if($next_org_name!=null)
		{
		$query_main=$query_main." OR point_name='{$next_org_name}'";
		}
		if($befor_dest_name!=null)
		{
		$query_main=$query_main." OR point_name='{$befor_dest_name}'";
		}
		if($mid_point_name!=null)
		{
		$query_main=$query_main." OR point_name='{$befor_dest_name}'";		
		}
		$query_main=$query_main." )";
		
		}				

	$results = $db->Execute($query_main);

	return $results;
	


}

function shn_gps_view_all()
{
	global $global;
	$db = $global['db'];

	$query_main="SELECT  point_uuid,author_name,event_date, opt_category,point_name, route_name,description from gpx_file where (route_name != 'waypoint' ) ";

	$results = $db->Execute($query_main);

	return $results;

}
function shn_gps_view_exist_route()
{
	global $global;
	$db = $global['db'];

	$query_main="SELECT distinct route_name from gpx_file where route_name!='waypoint' AND route_name!='-'";

	$results = $db->Execute($query_main);

	return $results;



}





function shn_gps_route_creator()
{
$limit=$_REQUEST['count'];
			global $global;
		$db = $global['db'];
	//echo $limit;
	$create_point="";
	for($counter=1;$counter<$limit+1;++$counter)
	{
		if(isset($_POST[$counter]))
			{
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
			$create_point=$create_point."<rtept lat=\"".$latitude."\" lon=\"".$longitude."\">\n<name>".$point_name."</name>\n<desc>".$description."</desc>\n</rtept>\n";
			
			}

	}
	$temp="../www/tmp/route.txt";
	$handle1=fopen($temp,"a");
	fwrite($handle1,$create_point);
	fclose($handle1);
	global $conf;
	$form_opts['name']='choose';
        $form_opts['req_message']=false;
	shn_form_fopen("create_route&stream=text",null,$form_opts);
	shn_form_fsopen('File Author');
	shn_form_text(_("Name of Author"),"author_name",'size="50"',array('help'=>_($conf['mod_gps_marker_author_help'])));
	shn_form_text(_("Name of Route"),"route_name",'size="50"',null);
	shn_form_submit(_("Download File"));
	shn_form_fsclose();
	shn_form_fclose();


}

function shn_text_gps_create_route()
{


	$temp="../www/tmp/route.txt";
	if(trim($_POST['author_name'])=="")
	$author="anonymous";
	else
	$author = trim($_POST['author_name']);

	if(trim($_POST['route_name'])=="")
	$route="not mentioned";
	else
	$route = trim($_POST['route_name']);

	$handle1=fopen($temp,"r");
	$contents = fread($handle1,filesize($temp));
	fclose($handle1);

	//$limit=$_REQUEST['count'];
	$point_store="<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<gpx version=\"1.0\" creator=\"Sahana - $author\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n xmlns=\"http://www.topografix.com/GPX/1/0\" xsi:schemaLocation=\"http://www.topografix.com/GPX/1/0 http://www.topografix.com/GPX/1/0/gpx.xsd\">\n<rte>\n<name>".$route."</name>";
	

	
	$file_name="Sahana-Marker.gpx";
  	header("Content-type: text/gpx");
    	header("Content-Disposition: attachment; filename=".$file_name);
     	header("Cache-Control: no-cache, must-revalidate");
	print $point_store.$contents."</rte>\n</gpx>";


}


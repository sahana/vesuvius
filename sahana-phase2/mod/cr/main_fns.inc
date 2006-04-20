<?php
/* $Id: main_fns.inc,v 1.33 2006-04-20 06:04:49 mifanc Exp $ */

/**
* Default functions of CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


function shn_cr_default(){
?>
<div id="home">
<h2><?php echo _("Camps Registry");?></h2>
<p> <?php echo _("This sub application of Sahana keeps track of the location of all the camps in the
region and the some basic data on the facilities they might have and the number of
people in them. It also provides a GIS view to plot the location of the camps in the
affected area.
Current features include:")?></p>
<ul>
    <li><?php echo _("Tracking of basic meta-data on the location, facilities and size of the camp")?></li>
    <li><?php echo _("Integration of google maps to provide a GIS view of the affected region")?></li>
    <li><?php echo _("Ability to customize the list of important facilities needed at a camp")?></li>
    <li><?php echo _("Basic reports on the camps and drill-down by region")?></li>
</ul>
<!--<p>The Camps Registry is the central Registry to manage Camps and individual Camp Management Systems<br>
	This Registry can be used to add camps, edit camps, view information on camps based on different categories and to search for camps.  </p><br/>
	-->
</div>
    <div id="home_recent">		
	<h1><?php echo _("Most Populated Camps");?></h1>
	<?php shn_cr_home_pop(); 
	?>	
	
	<h1><?php echo _("Newest Camps");?></h1>
	<?php shn_cr_home_newcmp(); 
	?>
    </div>
	<?php
	}

function shn_cr_home_pop(){
	global $global;
	$db=$global['db'];
	$query="select c.name,a.total from camp_general as c,camp_reg as a where c.c_uuid=a.c_uuid  order by total desc";
	$res=$db->Execute($query);
	$count=0;
?>
<div id="result">
<table>
<thead>
	<td><?=_("Camp Name")?></td>
	<td><?=_("Population")?></td>
</thead>

<?php
	while((!$res->EOF) && $count<=3){
		echo "<tr>";
		echo "<td>{$res->fields['name']}</td>";
		echo "<td>{$res->fields['total']}</td>";
		echo "</tr>";
		$count++;
		$res->MoveNext();
	}
?>
</table>
</div>
<?php
}

function shn_cr_home_newcmp(){
	global $global;
	$db=$global['db'];
	$query="select c.name,b.name from camp_reg a left outer join camp_general c using(c_uuid) left outer join location b on c.location_id=b.location_id order by a.c_uuid desc";
	$res =$db->Execute($query);
	$count=0;
?>
<div id="result">
<table>
<thead>
	<td><?=_("Camp Name")?></td>
	<td><?=_("Location")?></td>
</thead>

<?php
	while((!$res->EOF) && ($count<=3)){
		echo "<tr>";
		echo "<td>{$res->fields[0]}</td>";
		echo "<td>{$res->fields[1]}</td>";
		echo "</tr>";
		$count++;
		$res->MoveNext();
	}
?>

</table>
</div>
<?php
}



function shn_cr_stat(){
}

function shn_cr_srch(){

  global $global;
  include($global['approot'].'/mod/cr/search.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
  switch($_REQUEST['seq']){
		case 'next'		:
		            	echo _("Search Results");
		           	 	break;
		case 'commit'	:
									_shn_cr_srch_rst($_POST['cmp_id'],$_POST['opt_camp_type']);
									break;
		default :
		            _shn_cr_srch();
		            break;
		}
  
}

function shn_cr_acmp(){
	global $global;
  include($global['approot'].'/mod/cr/camp.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									include($global['approot'].'/conf/config.inc');
									if($conf['gis']=='false'){
										if(_shn_cr_validate_error())
											_shn_cr_cadd_start(true);
									}
										_shn_cr_cadd_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cadd_commit();
		            	break;
		case 'gis'		:
									if(_shn_cr_validate_error())
									  _shn_cr_cadd_start(true);
									else								
										_shn_cr_sel_map();
									break;
		default 			:
		            	_shn_cr_cadd_start();
		            	break;
		}
																																																						
}

function shn_cr_gis_show(){
	global $global;
	global $conf;
  include($global['approot'].'/conf/config.inc');
	if($conf['gis']){
		global $global;
		include($global['approot'].'/mod/gis/conf.inc');	
		//include($global['approot'].'/mod/gis/plugins/'.$conf["mod_gis"].'/'.'handler_'.$conf['mod_gis'].'.inc');
		$db = $global['db'];
		//echo _("GIS Map of Camps");
		$q="select map_northing,map_easting,name from gis_location as a, camp_general as b where a.poc_uuid=b.c_uuid";
		$res = $db->Execute($q);
		include_once ($global['approot'].'/mod/gis/gis_fns.inc');			
		/*if($conf['mod_gis']=='google_maps'){
			$a="select value from config where module_id='gis' and confkey='google_key'";
			$ares=$db->Execute($a);
			$key=$ares->fields[0];			
			shn_gis_init_plugin("GIS Map of Camps");
		}
		*/
		shn_gis_init_plugin("GIS Map of Camps");
		add_footer();
		load_map($conf['mod_gis_center_x'],$conf['mod_gis_center_y']);
		//put values into array: even better, process directly ;)
		while(!$res->EOF){
			add_marker_db($res->fields[0],$res->fields[1],$res->fields[2]);
			//add_marker($res->fields[2]);
			$res->MoveNext();	
		}
		end_page();
		
	}
	
}


function shn_cr_ecmp(){
	global $global;
  include($global['approot'].'/mod/cr/edit.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									//if(_shn_cr_validate_error())
										//_shn_cr_edt_start(true);
									//else
									_shn_cr_cedt_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cedt_commit();
		            	break;
		case 'disp'		:
										_shn_cr_cedt_start();
									break;	
		case 'view'		:
									shn_cr_all_view();
									break;
		case 'del'	  :
									_shn_cr_del_camp($_REQUEST['cmp_id']);
									break;
		default 			:	
		            	shn_cr_edt_srch();
		            	break;
		}
																																																						
}


function shn_cr_rpt(){
 global $global;
 include($global['approot'].'/mod/cr/reports.inc');
 require_once($global['approot'].'/inc/handler_form.inc');

 // check action sequence
 switch($_REQUEST['seq']){
 case 'viewall'    :
					      echo "Reports";
								break;
 case 'commit' :
                _shn_cr_rpt_rst();
                break;
 case 'viewloc' :
 								echo "loc";
                _shn_cr_rpt_rst();
                break;
 default       :
 								echo "default";
								_shn_cr_rpt();
								break;
																																																									     }
																																																										 
}

function shn_cr_arpt(){
	global $global;
	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_all(); 
}

function shn_cr_contact(){
	global $global;
	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_contact(); 
}

function shn_cr_lrpt(){
	global $global;
 	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_drill_location();
	//_shn_cr_rpt_loc();
}

function shn_cr_ldrpt(){
	global $global;
 	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_loc($_REQUEST['seq']);
}

function shn_cr_srpt(){
	global $global;
 	include($global['approot'].'/mod/cr/reports.inc');
	_shn_cr_rpt_summary();
}

function shn_cr_acma(){
}

function shn_cr_view(){
}
s
?>

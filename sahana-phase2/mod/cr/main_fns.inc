<?php
/* $Id: main_fns.inc,v 1.50 2007-02-12 09:37:29 mifanc Exp $ */

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
	global $conf;
?>
	<div id="home">
	<h2><?php echo _($conf['mod_cr_name'])?></h2>
	<p> <?php echo _("This sub application of Sahana keeps track of the location of all the {$conf['mod_cr_alt']}s in the
	region and some basic data on the facilities they might have, the number of
	people in them etc. It also provides a GIS view to plot the location of the {$conf['mod_cr_alt']}s in the
	affected area.
	Current features include:")?></p>
	<ul>
	    <li><?php echo _("Tracking of basic meta-data on the location, facilities and size of the {$conf['mod_cr_alt']}s")?></li>
	    <li><?php echo _("Integration of google maps to provide a GIS view of the affected region")?></li>
	    <li><?php echo _("Ability to customize the list of important facilities needed at a {$conf['mod_cr_alt']}")?></li>
	    <li><?php echo _("Basic reports on the {$conf['mod_cr_alt']} and drill-down by region")?></li>
	</ul>
	</div>
	    <div id="home_recent">		
		<h2><?php echo _("Most Populated Shelters");?></h2>
		<?php shn_cr_home_pop(); 
		?>	
		
		<h2><?php echo _("Newest Shelters");?></h2>
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
	<td><?=_("Shelter Name")?></td>
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
	$query="select c.name,b.name from camp_reg a left outer join camp_general c using(c_uuid) left outer join location b on c.location_id=b.loc_uuid order by a.c_uuid desc";
	$res =$db->Execute($query);
	$count=0;
?>
<div id="result">
<table>
<thead>
	<td><?=_("Shelter Name")?></td>
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
									
		case 'show' :
									_shn_cr_srch_rst($_POST['cmp_id'],'all');
									break;	
		default :
		            _shn_cr_srch();
		            break;
		}
  
}

function shn_cr_srch_address(){

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
									
		case 'show' :
									_shn_cr_srch_rst($_POST['cmp_id'],'all');
									break;	
		default :
		            _shn_cr_srch_address();
		            break;
		}
  
}

function shn_cr_acmp(){
	global $global;
	global $conf;
  	include($global['approot'].'/mod/cr/camp.inc');
	require_once($global['approot'].'/inc/handler_form.inc');

	// check action sequence
	switch($_REQUEST['seq']){
		case 'chk'		:
									if(!$conf['gis']){
										if(_shn_cr_validate_error())
											_shn_cr_cadd_start(true);
									}
										_shn_cr_cadd_chk();
									break;
		case 'commit'	:
		            	_shn_cr_cadd_commit();
		            	break;
		
		case 'hos'  :
                        _shn_cr_hos_bed();
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
	if($conf['gis']){
		$db = $global['db'];
		$q="select map_northing,map_easting,name,c_uuid from gis_location as a, camp_general as b where a.poc_uuid=b.c_uuid";
		$res = $db->Execute($q);
		include_once ($global['approot'].'/mod/gis/gis_fns.inc');
		
		//create array
		$map_array=array();
		
		//populate aray
		while(!$res->EOF){
				$camp_url='mod=cr&act=ecmp&seq=view&cmp_id='.$res->fields['name'];
				array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
					"id"=>$res->fields['c_uuid'],"url"=>$camp_url));
				$res->MoveNext();	
		}	
		//global $conf;		
		shn_gis_map_with_markers($map_array);
		
	}
	
}

/**
 * Spatial report by number of infections
 * infected / total
 */
function shn_cr_gis_infect(){
	global $global;
	global $conf;
	if($conf['gis']){
		$db = $global['db'];
		$q="select map_northing,map_easting,name,b.c_uuid,total,family,capacity from gis_location as a," .
				" camp_general as b, camp_reg as c where a.poc_uuid=b.c_uuid and b.c_uuid=c.c_uuid";
		$res = $db->Execute($q);
		include_once ($global['approot'].'/mod/gis/gis_fns.inc');
		
		//create array
		$map_array=array();
		
		//populate aray
		while(!$res->EOF){
				$infected=$res->fields['family']; //points to infected values
				$capacity=$res->fields['total'];
				if($capacity!=0){
					$perc = $infected / $capacity;
				}
				else
					$perc=0;
				$desc = $perc * 100;
				$desc = $desc."% "._("Infected");
				
				$marker_n="marker";
				if($perc <= $conf['mod_cr_perc_0']){
					$marker_n=$conf['mod_cr_perc_0_mk'];
				}
				else if($perc > $conf['mod_cr_perc_0'] && $perc <= $conf['mod_cr_perc_1']){
					$marker_n=$conf['mod_cr_perc_1_mk'];
				}
				else if($perc > $conf['mod_cr_perc_1'] && $perc <= $conf['mod_cr_perc_2']){
					$marker_n=$conf['mod_cr_perc_2_mk'];
				}
				else if($perc > $conf['mod_cr_perc_2'] && $perc <= $conf['mod_cr_perc_3']){
					$marker_n=$conf['mod_cr_perc_3_mk'];
				}
				else{
					$marker_n=$conf['mod_cr_perc_f_mk'];
				}
				
				array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
					"id"=>$res->fields['c_uuid'],"desc"=>$desc,"marker"=>$marker_n));
				$res->MoveNext();	
		}			
?>
	<h1><?=_("Map of Shelters by Infected Population")?></h1>
<?php
		shn_gis_density_map($map_array);
	?>
<br>
<h3><?=_("Legend")?></h3>

<div id="result">
<table>

 <tbody>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_0_mk'].'.png'?>" /></td>
 	<td><?="Less than ".($conf['mod_cr_perc_0']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_1_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_0']*100)."%"." and ".($conf['mod_cr_perc_1']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_2_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_1']*100)."%"." and ".($conf['mod_cr_perc_2']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_3_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_2']*100)."%"." and ".($conf['mod_cr_perc_3']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_f_mk'].'.png'?>" /></td>
 	<td><?="More than ".($conf['mod_cr_perc_3']*100)."%"?></td>
 </tbody>
</table>
</div>
<?php
	}
	
}

/**
 * Spatial report by population
 * total / capacity
 */
function shn_cr_gis_population(){
	global $global;
	global $conf;
	if($conf['gis']){
		$db = $global['db'];
		$q="select map_northing,map_easting,name,b.c_uuid,total,family,capacity from gis_location as a," .
				" camp_general as b, camp_reg as c where a.poc_uuid=b.c_uuid and b.c_uuid=c.c_uuid";
		$res = $db->Execute($q);
		include_once ($global['approot'].'/mod/gis/gis_fns.inc');
		
		//create array
		$map_array=array();
		
		//populate aray
		while(!$res->EOF){
				$infected=$res->fields['total'];
				$capacity=$res->fields['capacity'];
				if($capacity!=0){
					$perc = $infected / $capacity;
				}
				else
					$perc=0;
				$desc = $perc * 100;
				$desc = $desc."% "._("Filled");
				
				$marker_n="marker";
				if($perc <= $conf['mod_cr_perc_0']){
					$marker_n=$conf['mod_cr_perc_0_mk'];
				}
				else if($perc > $conf['mod_cr_perc_0'] && $perc <= $conf['mod_cr_perc_1']){
					$marker_n=$conf['mod_cr_perc_1_mk'];
				}
				else if($perc > $conf['mod_cr_perc_1'] && $perc <= $conf['mod_cr_perc_2']){
					$marker_n=$conf['mod_cr_perc_2_mk'];
				}
				else if($perc > $conf['mod_cr_perc_2'] && $perc <= $conf['mod_cr_perc_3']){
					$marker_n=$conf['mod_cr_perc_3_mk'];
				}
				else{
					$marker_n=$conf['mod_cr_perc_f_mk'];
				}
				
				array_push($map_array,array("lat"=>$res->fields['map_northing'],"lon"=>$res->fields['map_easting'],"name"=>$res->fields['name'],
					"id"=>$res->fields['c_uuid'],"desc"=>$desc,"marker"=>$marker_n));
				$res->MoveNext();	
		}			
		//show_map_with_custom_markers($map_array);
?>
	<h1><?=("Map of Shelters by Population / Capacity percentage")?></h1>
<?php
		shn_gis_density_map($map_array);
?>
<br>
<h3><?=_("Legend")?></h3>

<div id="result">
<table>

 <tbody>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_0_mk'].'.png'?>" /></td>
 	<td><?="Less than ".($conf['mod_cr_perc_0']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_1_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_0']*100)."%"." and ".($conf['mod_cr_perc_1']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_2_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_1']*100)."%"." and ".($conf['mod_cr_perc_2']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_3_mk'].'.png'?>" /></td>
 	<td><?="Between ".($conf['mod_cr_perc_2']*100)."%"." and ".($conf['mod_cr_perc_3']*100)."%"?></td>
 	<td><img src="<?=$conf['mod_gis_marker_folder'].$conf['mod_cr_perc_f_mk'].'.png'?>" /></td>
 	<td><?="More than ".($conf['mod_cr_perc_3']*100)."%"?></td>
 </tbody>
</table>
</div>
<?php		
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
		case 'eplcnt'        :
                                    _shn_cr_edt_ppl($_REQUEST['cmp_id']);
                                    break;
		default 			:	
		            	shn_cr_edt_srch();
		            	break;
		}
																																																						
}

function shn_cr_eppl()
{

        global $global;
  include($global['approot'].'/mod/cr/edit_ppl.inc');
        require_once($global['approot'].'/inc/handler_form.inc');

        // check action sequence
        switch($_REQUEST['seq']){
                case 'chk'      :
                                                                        if(_shn_cr_validate_error())
                                                                                _shn_cr_cedt_start(true);
                                                                        else
                                                                          {
                     //                                                    _shn_cr_cedt_commit();
                                                                            _shn_cr_cedt_chk();
_shn_cr_cedt_commit();
}
                                                                        break;

              
                case 'disp'             :
                                                                                _shn_cr_cedt_start();
                                                                        break;
                case 'view'             :
                                                                        shn_cr_all_view();
                                                                        break;
               

 case 'eplcnt'        :
                                                                        _shn_cr_edt_ppl($_REQUEST['cmp_id']);
                                                                        break;



default                         :
                                shn_cr_edt_srch();
                                break;
                }


}


//added by isuru
function shn_cr_ebed()
{

        global $global;
  include($global['approot'].'/mod/cr/edit_bed.inc');
        require_once($global['approot'].'/inc/handler_form.inc');

        // check action sequence
        switch($_REQUEST['seq']){
                case 'chk'      :
                                                                        if(_shn_cr_validate_error())
                                                                                _shn_cr_cedt_start(true);
                                                                        else
                                                                          {
                     //                                                    _shn_cr_cedt_commit();
                                                                            _shn_cr_cedt_chk();
_shn_cr_cedt_commit();
}
                                                                        break;


                case 'disp'             :
                                                                                _shn_cr_cedt_start();
                                                                        break;
                case 'view'             :
                                                                        shn_cr_all_view();
                                                                        break;


 case 'eplcnt'        :
                                                                        _shn_cr_edt_bed($_REQUEST['cmp_id']);
                                                                        break;



default                         :
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

<?php
/**Figure Update Functionality of the Press and Media Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravith Botejue, Miyuru Daminda, Reka Sandaruwan, Chamara Caldera, Nishantha Pradeep
* @copyright Respective Authors
* @package    sahana
* @subpackage pnm
* 
* Developed during Sahana 2009 as a tribute.
*/

//include_once '/inc/lib_table.inc';

    switch($_POST['seq']){
	    case '':
	        _shn_pnm_figure_update_data();
	        break;
	    default :
	        _shn_pnm_figure_update_data();
	        break;        
    }


function _shn_pnm_figure_update_data(){
    
    echo '<H3>Figure Updates</H3>';
    
    $th_items[] = array('Figure', 'Count');


    global $global;
    $sql1 = "SELECT COUNT(c_uuid) AS shelter FROM camp_general";
    $res1 = $global['db']->Execute($sql1);
    
    $sql2 = "SELECT COUNT(p_uuid) AS missing FROM person_uuid  WHERE p_uuid IN(SELECT p_uuid FROM person_missing)";
    $res2 = $global['db']->Execute($sql2);
    
    $sql3 = 'SELECT SUM(no_displaced) AS dis_placed, SUM(no_dead) AS dead FROM group_details';
    $res3 = $global['db']->Execute($sql3);
    
    
    echo $global['db']->ErrorMsg();   // $res1->MoveNext();
   //echo $res1->fields['shelter'];
   $displaced = ($res3->RecordCount() > 0)?$res3->fields['dis_placed'] : 'No Displaced Person Reported';
    $missing = ($res2->RecordCount() > 0)?$res2->fields['missing'] : 'No Missing Person Reported';
    $dead = ($res3->RecordCount() > 0)?$res3->fields['dead'] : 'No death Reported';
    $shelter = ($res1->RecordCount() > 0)?$res1->fields['shelter'] : 'No Shelter is established yet';
  
  $tb_items[] = array('Number of Displaced',  $displaced);
  $tb_items[] = array('Number of missing Persons', '<a href = "index.php?mod=mpr&act=list_missing">'.$missing.'</a>');
  $tb_items[] = array('Number of deaths', $dead);
  $tb_items[] = array('Number of Shelters',  '<a href = "index.php?mod=cr&act=arpt">'.$shelter.'</a>');

    //shn_html_table(
    shn_html_table($tb_items, $th_items, null, array('class'=>'wide'));
}


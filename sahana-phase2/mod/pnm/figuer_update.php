<?php

function shn_pnm_figure_update(){

    switch($_POST['seq']){
    case = '':
        _shn_pnm_figure_update_date();
        break;
    default :
        break;
        
    }
}

function _shn_pnm_figure_data(){
    global $global;
    $sql1 = "SELECT COUNT(c_uuid) AS shelter FROM camp_general";
    $res2 = $global['db']->Execute($sql1);
    
    $sql2 = "SELECT COUNT(p_uuid) AS person FROM missing  WHERE p_uuid IN(SELECT p_uuid FROM person_missing)";
    $res2 = $global['db']->Execute($sql2);
    
    //$sql3 = "SELECT FROM WHERE"
    
    $tb_items[] = array('Number of missing Persons' , $res1->fields['missing']);
    $tb_items[] = array('Number of Shelters', $res2->fields['shelters']);
    
    shn_html_table(null, $th_items, null, array('class'=>'wide'));
}

?>
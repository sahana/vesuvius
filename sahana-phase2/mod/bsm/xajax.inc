<?php
global $global;
array_push($global['xajax_functions'],'bsm_change_loc_types');
array_push($global['xajax_functions'],'bsm_change_person');
array_push($global['xajax_functions'],'bsm_change_service');
array_push($global['xajax_functions'],'bsm_change_facility');

function bsm_change_loc_types($loc_cate){
    global $global;
    //populte only those type values with respect to the selected category value
    $sql = "SELECT loc_type FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_cate='$loc_cate' ORDER BY loc_type ASC";
    //if (isset($_POST['category'])){$category = trim($_POST['category']); $sql .= "AND lt.loc_cate = '$category'";}
    $rsql = $global['db']->Execute($sql);
    $html .="<option value=''></option>";
    foreach ($rsql AS $req)
    {
        $html .= "<option value='{$req['loc_type']}'>{$req['loc_type']}</option>";
    }



    $global['xajax_res']->addAssign('loc_type','innerHTML',$html);   
    return $global['xajax_res']->getXML(); 
}


function bsm_change_person($prsn_role){
    global $global;

    $sql = "SELECT DISTINCT prsn_type  FROM bsm_prsn_type WHERE deactivate_dt IS NULL AND prsn_role = '$prsn_role'";
    $rsql = $global['db']->Execute($sql);
    $html1 .="<option value=''></option>";
    foreach ($rsql AS $req)
    {
        $html1 .= "<option value='{$req['prsn_type']}'>{$req['prsn_type']}</option>";
    }

    $sql = "SELECT DISTINCT prsn_state  FROM bsm_prsn_state WHERE deactivate_dt IS NULL AND prsn_role = '$prsn_role'";
    $rsql = $global['db']->Execute($sql);
    $html2 .="<option value=''></option>";
    foreach ($rsql AS $req)
    {
        $html2 .= "<option value='{$req['prsn_state']}'>{$req['prsn_state']}</option>";
    }

    $global['xajax_res']->addAssign('prsn_type','innerHTML',$html1);   
    $global['xajax_res']->addAssign('prsn_state','innerHTML',$html2);   
    return $global['xajax_res']->getXML(); 
}



function bsm_change_service($serv_cate){
    global $global;
    //populte only those type values with respect to the selected category value
    $sql = "SELECT DISTINCT serv_type AS service_type FROM bsm_serv_type WHERE deactivate_dt IS NULL AND serv_cate = '$serv_cate'";
    //if (isset($_POST['category'])){$category = trim($_POST['category']); $sql .= "AND lt.loc_cate = '$category'";}
    $rsql = $global['db']->Execute($sql);
    $html .="<option value=''></option>";
    foreach ($rsql AS $req)
    {
        $html .= "<option value='{$req['service_type']}'>{$req['service_type']}</option>";
    }



    $global['xajax_res']->addAssign('service_type','innerHTML',$html);   
    return $global['xajax_res']->getXML(); 
}


function bsm_change_facility($fclty_cate){
    global $global;
    //populte only those type values with respect to the selected category value
    $sql = "SELECT DISTINCT fclty_type AS type FROM bsm_fclty_type WHERE deactivate_dt IS NULL AND fclty_cate='$fclty_cate'";
    $rsql = $global['db']->Execute($sql);
    $html .="<option value=''></option>";
    foreach ($rsql AS $req)
    {
        $html .= "<option value='{$req['type']}'>{$req['type']}</option>";
    }



    $global['xajax_res']->addAssign('type','innerHTML',$html);   
    return $global['xajax_res']->getXML(); 
}

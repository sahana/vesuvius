<?php
    global $global;
    
    $sql = "SELECT loc_cate FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_type = '$loc_type' ORDER BY loc_type ASC";
    $loc_cate = $global['db']->GetOne($sql);
//print $sql;
    shn_xajax_registerFunction('bsm_change_loc_types');
    $sql = "SELECT * FROM bsm_loc_cate WHERE deactivate_dt IS NULL ORDER BY loc_cate ASC";
    $rsql = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($rsql AS $r => $rv)
    {
        $arropt[$rv['loc_cate']]=$rv['loc_cate'];
    }
    //print 'test';
    //print_r($loc_cate);
   // print $loc_cate;
    shn_form_select($arropt,_('Category'), 'loc_cate',' onchange="bsm_change_loc_types(this.value)"',array('value'=>$loc_cate, 'help' => _('Select a location category.'), 'req'=>true));
//var_dump($arropt);
    //populte only those type values with respect to the selected category value
    //$loc_cate = $_SESSION['bsm']['loc']['cat'];
    if($_POST['loc_cate']!='' || $_POST['loc_cate']!=null)
    {
    	$loc_cate = $_POST['loc_cate'];
    }
    
    $sql = "SELECT loc_type FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_cate = '$loc_cate' ORDER BY loc_type ASC";
    //if (isset($_POST['category'])){$category = trim($_POST['category']); $sql .= "AND lt.loc_cate = '$category'";}
    $rsql = $global['db']->Execute($sql);
    //print $sql;
    $arropt = array(''=>'');
    foreach ($rsql AS $r => $rv)
    {
        $arropt[$rv['loc_type']]=$rv['loc_type'];
    }
    //print $loc_type;
    //print $_POST['loc_type'];
    if($_POST['loc_type']!='' || $_POST['loc_type']!=null)
    {
    	$loc_type= $_POST['loc_type'];
    	//print $loc_type;
    }
    //var_dump($arropt);
    //var_dump($arropt);
    shn_form_select($arropt,_('Type'), 'loc_type',null,array('value'=>$loc_type, 'help' => _('Select a location type.'), 'req'=>true));
	//var_dump($arropt);
	//$arropt="";
    //$_SESSION['bsm']['loc']['cat'] = "";

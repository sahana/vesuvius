<?php
    global $global;
    
    $sql = "SELECT prsn_role FROM bsm_prsn_type WHERE deactivate_dt IS NULL AND prsn_type = '$prsn_type'";
    $prsn_role = $global['db']->GetOne($sql);

    shn_xajax_registerFunction('bsm_change_service');
    $sql = "SELECT serv_cate FROM bsm_serv_cate WHERE deactivate_dt IS NULL";
    $res = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($res as $req)
    {
        $arropt[$req['serv_cate']]=$req['serv_cate'];
    }
    shn_form_select($arropt,_('Service Category'), 'service_category','onchange="bsm_change_service(this.value)"',array('help' => _('Select a service category.'), 'req'=>false, 'value'=>$serv_cate));

    $sql = "SELECT DISTINCT serv_type AS service_type FROM bsm_serv_type WHERE deactivate_dt IS NULL AND serv_cate = '$serv_cate'";
    $res = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($res as $req)
    {
        $arropt[$req['serv_cate']]=$req['serv_cate'];
    }
    shn_form_select($arropt,_('Service Type'), 'service_type',null,array('help' => _('Select a service type.'), 'req'=>false));

    $sql = "SELECT DISTINCT serv_state FROM bsm_serv_state WHERE deactivate_dt IS NULL ORDER BY serv_state_seq ";
    $res = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($res as $req)
    {
        $arropt[$req['serv_state']]=$req['serv_state'];
    }
    shn_form_select($arropt,_('Service State'), 'service_state',null,array('help' => _('Select a state category.'), 'req'=>false));



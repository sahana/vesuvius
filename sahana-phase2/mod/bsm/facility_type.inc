<?php
    global $global;
    
    $sql = "SELECT fclty_cate FROM bsm_fclty_type WHERE deactivate_dt IS NULL AND fclty_type = '$fclty_type'";
    $fclty_cate = $global['db']->GetOne($sql);

    shn_xajax_registerFunction('bsm_change_facility');
    $sql = "SELECT DISTINCT fclty_cate AS category FROM bsm_fclty_cate WHERE deactivate_dt IS NULL";
    $res = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($res as $req)
    {
        $arropt[$req['category']]=$req['category'];
    }
    shn_form_select($arropt,_('Category'), 'category','onchange="bsm_change_facility(this.value)"',array('help' => _('Select a facility category.'), 'req'=>true,'value'=>$fclty_cate));

    $sql = "SELECT DISTINCT fclty_type AS type FROM bsm_fclty_type WHERE deactivate_dt IS NULL AND fclty_cate='$fclty_cate'";
    $res = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($res as $req)
    {
        $arropt[$req['type']]=$req['type'];
    }
    shn_form_select($arropt,_('Type'), 'type',null,array('help' => _('Select a facility type.'), 'req'=>true,'value'=>$fclty_type));


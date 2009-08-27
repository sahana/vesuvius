<?php
    global $global;
    
    $sql = "SELECT prsn_role FROM bsm_prsn_type WHERE deactivate_dt IS NULL AND prsn_type = '$prsn_type'";
    $prsn_role = $global['db']->GetOne($sql);

    shn_xajax_registerFunction('bsm_change_person');
    $sql = "SELECT prsn_role FROM bsm_prsn_role WHERE deactivate_dt IS NULL";
    $roles = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($roles as $role)
    {
        $arropt[$role['prsn_role']]=$role['prsn_role'];
    }
    shn_form_select($arropt,_('Person role'), 'prsn_role','onchange="bsm_change_person(this.value)"',array('help' => _('Select a person role.'), 'req'=>true, 'value'=>$prsn_role));

    $sql = "SELECT DISTINCT prsn_type  FROM bsm_prsn_type WHERE deactivate_dt IS NULL AND prsn_role = '$prsn_role'";
    $types = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($types as $type)
    {
        $arropt[$type['prsn_type']]=$type['prsn_type'];
    }
    shn_form_select($arropt,_('Person Type'), 'prsn_type',null,array('help' => _('Select a person type.'), 'req'=>true,'value'=>$prsn_type));

    $sql = "SELECT DISTINCT prsn_state  FROM bsm_prsn_state WHERE deactivate_dt IS NULL AND prsn_role = '$prsn_role'";
    $states = $global['db']->GetAll($sql);
    $arropt = array(''=>'');
    foreach ($states as $state)
    {
        $arropt[$type['prsn_state']]=$state['prsn_state'];
    }
    shn_form_select($arropt,_('Person State'), 'prsn_state',null,array('help' => _('Select the state of the person.'), 'req'=>true, 'value'=>$prsn_state ));

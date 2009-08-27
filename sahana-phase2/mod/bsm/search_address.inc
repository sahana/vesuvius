<?php
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Address'));
    shn_form_text(_('Address Type'),'addr_type','size="30"',array('help' => _('Enter Address Type.'), 'req'=>false));
    shn_form_text(_('Address Status'),'addr_status','size="30"',array('help' => _('Enter Address Ststus.'), 'req'=>false));
		shn_form_textarea(_('Address 1 '),'addr_1',null,array('help' => _('Enter Address One.'), 'req'=>false));
		shn_form_textarea(_('Address 2 '),'addr_2',null,array('help' => _('Enter Address Two.'), 'req'=>false));
    shn_form_fsclose();

		//shn_form_fsopen(_('Location Details'));
		
		//shn_form_fsclose();

    /*shn_form_fsopen(_('Service Recipient'));
    shn_form_text(_('Last Name'),'recipient_last_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_text(_('First Name'),'recipient_first_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_fsclose();*/

    shn_form_submit(_('Search'));
    shn_form_fsclose();

		shn_form_hidden(array('fclty_id'=>$_REQUEST['id']));

		//echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=address&seq=lukup&id='.
        //$_SESSION['bsm']['edit']['p_uuid'].'">'." Click to ADD a new Address".'</a><br>';
    
    if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));

    shn_form_fclose();
}

/**
 * Search Query Generation
 * 
 * @deprecated 
 * @access public
 * @return void
 */
function shn_bsm_search_result()
{   
    //@todo: rewrite
	$_SESSION['bsm']['add']['fclty_id'] = trim($_POST['fclty_id']);
		
    //$name = trim($_POST['name']);
    $addr_type = trim($_POST['addr_type']);
    $addr_status = trim($_POST['addr_status']);
		$addr_1 = trim($_POST['addr_1']);
		$addr_2 = trim($_POST['addr_2']);
    
    global $global;
    global $conf;

		$sql = "SELECT fa.fclty_uuid AS fclty_uuid, a.addr_uuid AS addr_uuid, a.addr_type AS addr_type, a.addr_status AS addr_status, a.line_1 AS addr_1, a.line_2 AS addr_2 FROM bsm_address a INNER JOIN bsm_fclty_addr fa ON a.addr_uuid=fa.addr_uuid WHERE a.deactivate_dt IS NULL";

		//$sql = "SELECt pc.p_uuid AS p_uuid, c.cont_uuid AS cont_uuid, c.cont_mode AS cont_mode, c.cont_val AS cont_val FROM bsm_contact c INNER JOIN bsm_prsn_cont pc ON c.cont_uuid=pc.cont_uuid WHERE c.deactivate_dt IS NULL";
		if($addr_type != null || $addr_type != "") {$sql .= "AND a.addr_type LIKE '%$addr_type%'";}
		if($addr_status != null || $addr_status != ""){$sql .= "AND a.addr_status LIKE '%$addr_status%'";}
		if($addr_1 != null || $addr_1 != ""){$sql .= "AND a.line_1 LIKE '%$addr_1%'";}
		if($addr_2 != null || $addr_2 != ""){$sql .= "AND a.line_2 LIKE '%$addr_2%'";}
		$sql .= " GROUP BY 1";

    //print $sql;

    return $sql;
}

/**
 * Search Result Display
 * 
 * @deprecated 
 * @param string $subquery 
 * @param mixed $limit 
 * @param mixed $offset 
 * @access public
 * @return void
 */
function shn_bsm_search_result_vw($subquery=null, $offset=-1, $return=false)
{
//print 'test';
    $_SESSION['bsm']['search']['subquery'] = $subquery;

    global $global;
    global $conf;

    $limit = $conf['mod_bsm_search_limit'];

    /*$sql = "SELECT case_uuid AS case_uuid, case_dt AS case_datetime, pat_full_name AS patient_full_name, ";
    $sql .= "gender AS patient_gender, age_grp AS patient_age_group, age AS patient_age, disease AS disease, ";
    $sql .= "fclty_name AS facility, loc_name AS location, hwork_full_name AS hwork_full_name ";
    $sql .= "FROM bsm_cases WHERE deactivate_dt IS NULL AND case_uuid IN ($subquery) ORDER BY disease";*/
    $rs = $global['db']->SelectLimit(shn_bsm_search_result(),$limit,$offset);
    $rs_count = $global['db']->Execute(shn_bsm_search_result());

    if($rs!=null){$arr = $rs->GetAll();}
    echo '<p align="left">'."If the desired result is not in the record set, ".'<a align="center" title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=address&seq=lukup&id='.$_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD new record.".'</a></p><br>';
    
    if($rs_count!=null){$_SESSION['bsm']['search']['record_count'] = $rs_count->RecordCount();}
    else {$_SESSION['bsm']['search']['record_count'] =  0;}
    if($return){return $arr;} else 
    {
        shn_bsm_search_nav();


?>
<DIV ID="result">
<?php
    shn_bsm_search_show_result($arr);
?>
</DIV>
<?php
        shn_bsm_search_nav();
    }
}

/**
 * Navigation Controll
 * 
 * @deprecated
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_bsm_search_navigation_top($rs)
{
    shn_bsm_search_nav_arrows($rs);
}


function shn_bsm_search_navigation_bottom($rs)
{
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records found').'</strong><br />';
    shn_bsm_search_nav_arrows($rs);
}

function shn_bsm_search_nav()
{
    global $global;
    global $conf;

    $limit = $conf['mod_bsm_search_limit'];
    $offset = $_GET['offset']; 
    $total = $_SESSION['bsm']['search']['record_count'];

    $delta = $total - $offset - $limit;

    echo '<br /><strong>'._('Total').' '.$total.' '._('Records found').'</strong><br />';    
?>  
<ul class="paging">
<?php   
    //Back Arrows
    if( $offset > 0 ){
        //Right Back
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&seq='.$_REQUEST['seq'].
            '&offset=0'.'">'.
            '|&lt;&lt;'._('First').' '.$limit.' '._('Records').' </a></li>';   
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset - $limit ) . '">'.
            '&lt;&lt;'._('Previous').' '.$limit.' '._('Records').' </a></li>';
    }
    //Forward Arrows
    if( $delta > 0 ){
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset + $limit ) . '">'.
            _('Next').' '.($delta < $limit ? $delta : $limit).' '._('Records').' &gt;&gt; </a></li>';
        //Right at Last
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&seq='.$_REQUEST['seq'].
            '&offset='.($total - $limit).'">'.
            _('Last').'  '. $limit.' '._('Records').' &gt;&gt;|</a></li>';
    }
?>
</ul>
<?php

}


/**
 * Display Results
 * 
 * @deprecated
 * @param mixed $details 
 * @access public
 * @return void
 */
function shn_bsm_search_show_result($details)
{
    //var_dump($details);
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('UUID');?></TD>
    <TD><?= _('Address Type');?></TD>
    <TD><?= _('Address Status');?></TD>
		<TD><?= _('Address 1');?></TD>
		<TD><?= _('Address 2');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>  
    <TD> <?php   echo $detail['addr_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=facility&rtnfrm=cases&rtnid='.$detail['addr_uuid'].'&seq=&do=addaddress&lukupid='.$_SESSION['bsm']['add']['fclty_id'].'">'.
                    $detail['addr_uuid'].'</a><br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['addr_type'] ? $detail['addr_type'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['addr_status'] ? $detail['addr_status'].'<br>' : ''; ?> </TD>
		<TD> <?php   echo $detail['addr_1'] ? $detail['addr_1'].'<br>' : ''; ?> </TD>
		<TD> <?php   echo $detail['addr_2'] ? $detail['addr_2'].'<br>' : ''; ?> </TD>
    
    </TR>
<?php
    }
}
?>
</TABLE>
<?php
}

function _shn_bsm_add_fclty_address($fclty_addr, $addr_uuid)
{
	global $global;
	$db = $global['db'];
	$sql = "INSERT INTO bsm_fclty_addr (fclty_uuid, addr_uuid) VALUES ('{$fclty_addr}', '{$addr_uuid}')";
	$res = $db->Execute($sql);
}
?>
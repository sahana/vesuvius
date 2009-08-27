<?php
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='Search'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    //include('service_type.inc');

    shn_form_fsopen(_('Contact Details'));
    shn_form_text(_('Contact Mode'),'contact_mode','size="30"',array('help' => _('Enter Contact Mode.'), 'req'=>false));
    shn_form_text(_('Contact Value'),'contact_value','size="30"',array('help' => _('Enter Contact Value.'), 'req'=>false));
    shn_form_fsclose();

    

    shn_form_submit(_('Search'));
    shn_form_fsclose();
		shn_form_hidden(array('facility_id'=>$_REQUEST['id']));

		//echo '<a title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=contact&seq=lukup&id='.
       // $_SESSION['bsm']['edit']['p_uuid'].'">'." Click to ADD a new Contact".'</a><br>';
    
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
		$_SESSION['bsm']['edit']['facility_id'] = trim($_POST['facility_id']);
		
    //$name = trim($_POST['name']);
    $contact_mode = trim($_POST['contact_mode']);
    $contact_value = trim($_POST['contact_value']);
    
    global $global;
    global $conf;

		$sql = "SELECt pc.p_uuid AS p_uuid, c.cont_uuid AS cont_uuid, c.cont_mode AS cont_mode, c.cont_val AS cont_val FROM bsm_contact c INNER JOIN bsm_prsn_cont pc ON c.cont_uuid=pc.cont_uuid WHERE c.deactivate_dt IS NULL";
		if($contact_mode != null || $contact_mode != "") {$sql .= "AND c.cont_mode LIKE '%$contact_mode%'";}
		if($contact_value != null || $contact_value != ""){$sql .= "AND c.cont_value LIKE '%$contact_value%'";}
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
    echo '<p align="left">'."If the desired result is not in the record set, ".'<a align="center" title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=contact&seq=lukup&id='.$_SESSION['bsm']['edit']['p_uuid'].'">'." click to ADD new record.".'</a></p><br>';
    
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
    <TD><?= _('Contact Mode');?></TD>
    <TD><?= _('Contact Value');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>  
    <TD> <?php   echo $detail['cont_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=facility&rtnfrm=cases&rtnid='.$detail['cont_uuid'].'&do=addcontact&seq=lukup&lukupid='.$_SESSION['bsm']['edit']['facility_id'].'">'.
                    $detail['cont_uuid'].'</a><br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['cont_mode'] ? $detail['cont_mode'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['cont_val'] ? $detail['cont_val'].'<br>' : ''; ?> </TD>
    
    </TR>
<?php
    }
}
?>
</TABLE>
<?php
}

function _shn_bsm_add_fclty_contact($lukupid,$rtn_id)
{
	global $global;
	$db = $global['db'];
	$sql = "INSERT INTO bsm_prsn_cont (p_uuid, cont_uuid) VALUES ('{$lukupid}', '{$rtn_id}')";
//print $sql;
	$res = $db->Execute($sql);
}
?>
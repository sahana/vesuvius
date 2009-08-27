<?php

/**
 * 
 * Search a person
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license that is available through the world-wide-web at the
 * following URI: http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    mod
 * @subpackage bsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
/**
 * @name    Search default form
 * @access public
 * @return void
 * @param   string $fopen_name
 * @example .../index.php?mod=bsm&act=search&entity=person...
 * @param   string $fsopen_name
 * @example By default first search then rest: edit, add, & delete (avoid duplication!)
 * @TODO    only show person types and status related to the selected category "onchange"
 */
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search'){
    
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));
    shn_form_fsopen(_('Names :'));
    shn_form_text(_('Last Name'),'last_name','size="30"',array('help' => _('Enter full or part of the last name also known as Surname or Family Name.'), 'req'=>false));
    shn_form_text(_('First Name'),'first_name','size="30"',array('help' => _('Enter full or part of the first name.'), 'req'=>false));
    shn_form_text(_('Middle Name'),'mi_name','size="30"',array('help' => _('Enter full or part of the middle name or second name.'), 'req'=>false));
    shn_form_text(_('Alias'),'alias','size="30"',array('help' => _('Enter full or part of the alias name or second name.'), 'req'=>false));
    shn_form_fsclose();
    shn_form_fsopen(_('Characteristics:'));
    include('person_type.inc');
    shn_form_fsclose();
    shn_form_fsopen(_('Identifications :'));
    shn_form_text(_('Passport'),'passport','size="30"',array('help' => _('Enter full or part of the passport number.'), 'req'=>false));
    shn_form_text(_('National Identification'),'natl_id','size="30"',array('help' => _('Enter full or part of the national identification number.'), 'req'=>false));
    shn_form_text(_('Driver License'),'dr_lic','size="30"',array('help' => _('Enter full or part of the drivers license number.'), 'req'=>false));
    shn_form_fsclose();
    shn_form_submit(_('Search'));

    shn_form_fsclose();
    if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));
	if($_GET['person']!=null) shn_form_hidden(array('person'=>$_GET['person']));
    shn_form_fclose();
}
/**
 * @name Search Query Generation
 * @access public
 * @return void
 */
function shn_bsm_search_result(){   
    $role = trim($_POST['prsn_role']);
    $type = trim($_POST['prsn_type']);
    $state = trim($_POST['prsn_state']);
    $passport = trim($_POST['passport']);
    $national_id = trim($_POST['natl_id']);
    $driver_license = trim($_POST['dr_lic']);
    $lname = trim($_POST['last_name']);
    $fname = trim($_POST['first_name']);
    $mname = trim($_POST['mi_name']);
    $alias = trim($_POST['alias']);
    //$type = trim($_POST['type']);

    global $global;
    global $conf;

    $sql = "SELECT p.* ,l.*,pt.prsn_role FROM bsm_person AS p INNER JOIN bsm_prsn_link_type AS l ON l.p_uuid = p.p_uuid INNER JOIN bsm_prsn_type AS pt ON l.prsn_type = pt.prsn_type";
		//$sql = "SELECT p.* ,l.* FROM bsm_person AS p INNER JOIN bsm_prsn_link_type AS l ON l.p_uuid = p.p_uuid";
    $sql .= " WHERE p.deactivate_dt IS NULL ";
    if(isset($role) && $role != '') {$sql .= "AND pt.prsn_role = '$role' ";}
    if(isset($type) && $type != '') {$sql .= "AND l.prsn_type = '$type' ";}
    if(isset($state) && $state != '') {$sql .= "AND l.prsn_state = '$state' ";}
    if($passport !=null || $passport !="") {$sql .= "AND p.passport LIKE '%$passport%' ";}
    if($national_id !=null || $national_id !="") {$sql .= "AND p.natl_id LIKE '%$national_id%' ";}
    if($driver_license !=null || $driver_license !="") {$sql .= "AND p.dr_lic LIKE '%$driver_license%' ";}
    if($lname!=null || $lname !="") {$sql .= "AND p.last_name LIKE '%$lname%' ";}
    if($fname!=null || $fname !="") {$sql .= "AND p.first_name LIKE '%$fname%' ";}
    if($mname!=null || $mname !="") {$sql .= "AND p.mi_name LIKE '%$mname%' ";}
    if($alias !=null || $alias !="") {$sql .= "AND p.alias LIKE '%$mname%' ";}
    $sql .= "GROUP BY 1";
//print $sql;

	if($conf['debug']) {
        echo "<hr>".$sql."<hr>";
    }
    return $sql;
}
/*
 * @name search parent form requested lookup results
 * @access public
 * @return string $sql
 * @param   string $location_uuid
 */
function shn_bsm_search_lukup_result($p_uuid=null){
    global $global;
    global $conf;

    if ($p_uuid !=null){

				$sql = "SELECT p.* FROM bsm_person p INNER JOIN bsm_prsn_link_type pt ON pt.p_uuid = p.p_uuid";
				$sql .= " INNER JOIN bsm_prsn_type pr ON pr.prsn_type = pt.prsn_type WHERE pr.deactivate_dt IS NULL ";
				$sql .= 'GROUP BY 1';
//print $sql;
        /*$sql = "SELECT p.p_uuid FROM bsm_person p INNER JOIN bsm_prsn_type pt ON pt.prsn_type = p.prsn_type ";
        $sql .= "INNER JOIN bsm_prsn_role pr ON pr.prsn_role = pt.prsn_role WHERE p.deactivate_dt IS NULL ";
        $sql .= 'GROUP BY 1';*/
    }
    else {$sql = shn_bsm_search_result();}
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
function shn_bsm_search_result_vw($subquery="SELECT loc_id FROM bsm_location", $offset=-1, $return=false){
    global $global;
    global $conf;
    $_SESSION['bsm']['search']['subquery'] = $subquery;
    $limit = $conf['mod_bsm_search_limit'];
    echo "<br />";
    echo '<a class="but" title="'._('Add').'" href="index.php?mod='.$global['module'].
            '&act=add&entity=person&rtnid='.$_REQUEST['rtnid'].'&person='.$_REQUEST['person'].'">'." click to ADD new record.".'</a><br>';
?>
<br />
<DIV ID="result">
<?php
    $rs = shn_paging_get_report($subquery,$rpp=20,$headers=NULL,array('return'=>true,'post'=>true));
    if($rs!=null){$arr = $rs->GetAll();}
    shn_bsm_search_show_result($arr);
?>
</DIV>
<?php
      //  shn_bsm_search_nav();
    $rs_count = $global['db']->Execute($subquery);
    if($rs_count!=null)
    $_SESSION['bsm']['search']['record_count'] =  $rs_count->RecordCount();
    else
    $_SESSION['bsm']['search']['record_count'] =  0;



}

/* {{{ Navigation Controll */
/**
 * Navigation Controll
 * 
 * @deprecated
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_bsm_search_navigation_top($rs){
    shn_bsm_search_nav_arrows($rs);
}
/**
 * shn_mpr_search_navigation_bottom NOT NEEDED
 * 
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_bsm_search_navigation_bottom($rs){
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records were found').'</strong><br />';
    shn_bsm_search_nav_arrows($rs);
}
function shn_bsm_search_nav(){
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
 * @name    Display Results
 * @param array $details
 * @access public
 * @return void
 */
function shn_bsm_search_show_result($details){
    
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('UUID');?></TD>
    <TD><?= _('Full Name (Alias)');?></TD>
    <TD><?= _('Alias');?></TD>
    <TD><?= _('Identification');?></TD>
    <TD><?= _('Sex/DOB/Age');?></TD>
    <TD><?= _('Role/Type/State');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>  
    <TD> <?php   echo $detail['p_uuid'] ? $detail['p_uuid'].'<br>' : ''; ?> </TD>
    <?php if($_REQUEST['seq']=='lukup'){
    ?><TD> <?php   echo $detail['last_name'] || $detail['first_name'] || $detail['mi_name'] || $detail['alias'] ?
                        '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].
                        '&act=search&entity=person&rtnfrm='.'cases'/*$_POST['rtnfrm']*/.'&rtnfk='.$_REQUEST['rtnfk'].'&rtnid='.
                        $_REQUEST['rtnid'].'&seq=lukup&lukupid='.$detail['p_uuid'].'">'.
                        $detail['last_name'].', '.$detail['first_name'].' '.$detail['mi_name'].'</a><br>' : ''; ?> </TD>
    <?php } else {
    ?><TD> <?php   echo $detail['last_name'] || $detail['first_name'] || $detail['mi_name'] ?
                        '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=edit&entity=person&rtnid='.$detail['p_uuid'].'">'.
                        $detail['last_name'].', '.$detail['first_name'].' '.$detail['mi_name'].'</a><br>' : ''; ?> </TD>
    <?php } ?>
    <TD> <?php   echo $detail['alias'] ? $detail['alias'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['passport'] || $detail['passport'] || $detail['passport'] ?
                    '<b>P : </b>'.$detail['passport'].'<br><b>N : </b>'.$detail['natl_id'].'<br><b>D : </b>'.$detail['dr_lic'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['dob'] || $detail['age'] || $detail['age_group'] || $detail['gender'] ?
                    '<b>Sex : </b>'.$detail['gender'].'<br><b>DOB : </b>'.$detail['dob'].'<br><b>Age : </b>'.$detail['age_grp'].' ('.$detail['age'].')<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['p_role'] || $detail['prsn_type'] || $detail['p_state'] ?
                    '<b>R : </b>'.$detail['prsn_role'].'<br><b>T : </b>'.$detail['prsn_type'].'<br><b>S : </b>'.$detail['prsn_state'].'<br>' : ''; ?> </TD>

    </TR>
<?php
    }
}
?>
</TABLE>
<?php
}
/* }}} */

/* {{{ Get Trackers */
/**
 * Get List of Trackers
 * 
 * @param mixed $p_uuid 
 * @access public
 * @return void
 */
function shn_bsm_search_get_trackers($p_uuid)
{
    global $global;
    $sql = "SELECT a.p_uuid, a.full_name, b.relation FROM person_uuid a, person_to_report
            b WHERE
            b.p_uuid = '$p_uuid' AND a.p_uuid = b.rep_uuid";
    $arr = $global['db']->GetAll($sql);
    return $arr;
}
/* }}} */

/* {{{ Search Select */
/**
 * Search result with select button
 * 
 * @param mixed $details 
 * @access public
 * @return void
 */
function shn_bsm_search_select($details)
{
    shn_bsm_search_nav();

    global $global;
?>
<DIV ID="result">
<TABLE>
<THEAD>
    <TD><?= _('Picture'); ?></TD>
    <TD><?= _('Name'); ?></TD>
    <TD><?= _('Status'); ?></TD>
    <TD><?= _('Select'); ?></TD>
</THEAD>
<?php
    foreach($details as $detail){
?>
    <TR>
        <TD>
<?php
    shn_show_thumb_url($detail['p_uuid'],'bsm','addmp_img');
?>
        </TD>
        <TD>
<?php
    echo '<a title="'._('View').'" href="index.php?mod='.$global['module'].'&act=viewmp&rtnid='.
            $detail['p_uuid'].'">'.
            $detail['full_name'].'</a>'.
        '<br>'.$detail['family_name'].'<br>'.$detail['l10n_name'];
?>
        </TD>
        <TD>
<?php
    echo shn_get_field_opt($detail['opt_status'],'opt_status');
    if($detail['opt_status'] == 'mis')
        echo '</br /><a title="'._('Change the status to Alive & Well').'" '.
            'href="index.php?mod='.$global['module'].'&act=status&rtnid='.$detail['p_uuid'].
            '"><br />('._('Click to change to found').')</a>';
?>
        </TD>
        <TD><a title="<?= _('Select'); ?>" href="index.php?<?=$_SERVER['QUERY_STRING'].
                '&tracker_id='.$detail['p_uuid'].
                '&seq=tracker_select';?>" ><?= _('Select'); ?></a>
        </TD>
    </TR>
<?php
    }
?>
</TABLE>
<a title="<?= _('Back'); ?>" href="index.php?<?=$_SERVER['QUERY_STRING']?>&seq=tracker_back"><?= _('Back'); ?></a>
</DIV>
<?php
    shn_bsm_search_nav();
}
/* }}} */

/* {{{ Search Query Class */
/**
 * SearchQuery Generates sqls for search
 * 
 * @package module
 * @subpackage mpr
 * @copyright Lanka Software Foundation - http://www.opensource.lk
 * @author Janaka Wickramasinghe <janaka@opensource.lk>
 * @license http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
class SearchQuery
{
/* {{{ Varibles */
    /* {{{ private variables */
    var $__locationID;
    var $__locationName;
    var $__locationCategory;
    var $__locationType;
    var $__parentID;
    
    var $__sql;

    var $__joins;
    var $__where;
    /* }}} */

    /* {{{ public variables */

//    var $isvictim;
//    var $missing_only;
//
//    var $incident_list;
//    var $incident_id;

    /* }}} */

/* }}} */

/* {{{ Functions */

    /* {{{ set name */
    /**
     * Sets the name field including soundex and metaphone
     * 
     * @param mixed $name 
     * @access public
     * @return void
     */
    function set_name($name)
    {
        $this->__locationName = $name;
        //split name
        $locations = preg_split("/\s+/",$this->__locationName);
        foreach($names as $name){
            $encode1 .= " phonetic_word.encode1 LIKE '".soundex($name)."' OR ";
            $encode2 .= " phonetic_word.encode2 LIKE '".metaphone($name)."%' OR ";
        }
        $encode1 = substr($encode1,0,strlen($encode1) - 3);
        $encode2 = substr($encode2,0,strlen($encode2) - 3);
           
        //TODO: Need to check this later
        $this->__joins[] = " LEFT OUTER JOIN phonetic_word ON " .
            " person_status.p_uuid = phonetic_word.pgl_uuid ";

        $this->__where[] = " ( ($encode1) OR ($encode2) ) ";
    }
    /* }}} */

    /* {{{ set address */
    /**
     * Sets the address
     * 
     * @param mixed $address 
     * @access public
     * @return void
     */
    function set_address($address)
    {
        //todo CLEAN
        $this->__address = $address;

        //set wild cards between
        $local_address = $this->__address;
        preg_replace("/\s+/","%",$local_address);

        $this->__joins[] = " LEFT OUTER JOIN location_details ON " .
            " person_status.p_uuid = location_details.poc_uuid ";

        $this->__where[] = " location_details.address LIKE '$local_address' ";
    }
    /* }}} */

    /* {{{ set serial */
    /**
     * Sets any serial numeber
     * 
     * @param mixed $serial_no 
     * @access public
     * @return void
     */
    function set_serial_no($serial_no)
    {
        $this->__serial_no = $serial_no;

        $this->__joins[] = " LEFT OUTER JOIN identity_to_person ON ".
                " person_status.p_uuid = identity_to_person.p_uuid ";
        $this->__where[] = " identity_to_person.serial LIKE '%{$this->__serial_no}%' ";
    }
    /* }}} */

    /* {{{ set phone */
    /**
     * Sets the phone number
     * 
     * @param mixed $phone 
     * @access public
     * @return void
     */
    function set_phone($phone)
    {
        $this->__phone = $phone;

        $this->__joins[] = " LEFT OUTER JOIN contact ON ".
            " person_status.p_uuid = contact.pgoc_uuid AND contact.opt_contact_type = 'curr'";
        $this->__where[] = " contact.contact_value LIKE '%{$this->__phone}%' "; 
    }
    /* }}} */

    /* {{{ get sql */
    /**
     * returns the generated sql
     * 
     * @access public
     * @return string
     */
    function get_sql()
    {
        $sql = "SELECT l.loc_id FROM bsm_location l " ;
        
        foreach ($this->__joins as $joins)
            $sql .= $joins ;
        
        //if incident_id is given join that
        //if(! empty ($this->incident_id) || ! empty ($this->incident_list) )
        //   $sql .= " INNER JOIN resource_to_incident ON resource_to_incident.x_uuid = person_status.p_uuid ";
        
        if($this->__where){
            $sql .= " WHERE (";
            foreach ($this->__where as $where)
                $sql .= $where . " OR ";

            $sql = substr($sql,0,strlen($sql) - 3);
            $sql .= " ) ";
            
            if(!  empty ($this->incident_id))
                $sql .= " AND resource_to_incident.incident_id = '{$this->incident_id}' ";
            elseif(!  empty ($this->incident_list))
                $sql .= " AND resource_to_incident.incident_id IN ({$this->incident_list}) ";
            if($this->isvictim)
                $sql .= " AND person_status.isvictim = TRUE ";
            if($this->missing_only)
                $sql .= " AND person_status.opt_status = 'mis' ";
            $sql .= " GROUP BY 1";
        }       
        return $sql;
    } 
    /* }}} */

/* }}} */

}
/* }}} */
?>
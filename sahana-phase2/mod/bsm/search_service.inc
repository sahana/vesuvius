<?php
/* $Id: search_service.inc,v 1.1 2009-08-27 22:26:49 pradeeper Exp $ */
/**
 * 
 * Search a service
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Nuwan Waidyanatha <waidyanatha@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage bsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @TODO    fix the service type drop down to display only the category related records and also the same for
 *  the state related to type "onchange"
 * @TODO    model a service as a poset (or tree) of tasks and each task as a process with items asinputs to a
 *          the process and items as outputs to the process with setup times and process time
 */
/**
 * @name Search default form
 * @access public
 * @return void
 * @param   string $fopen_name
 * @example .../index.php?mod=bsm&act=search&entity=service...
 * @param   string $fsopen_name
 * @example By default first search then rest: edit, add, & delete (avoid duplication!)
 */
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search'){
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    include('service_type.inc');

    shn_form_fsopen(_('Service Provider'));
    shn_form_text(_('Last Name'),'provider_last_name','size="30"',array('help' => _('Enter full or part of the service provider.'), 'req'=>false));
    shn_form_text(_('First Name'),'provider_first_name','size="30"',array('help' => _('Enter full or part of the service provider.'), 'req'=>false));
    shn_form_fsclose();

    shn_form_fsopen(_('Service Recipient'));
    shn_form_text(_('Last Name'),'recipient_last_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_text(_('First Name'),'recipient_first_name','size="30"',array('help' => _('Enter full or part of the service recipient name.'), 'req'=>false));
    shn_form_fsclose();

    shn_form_submit(_('Search'));
		shn_form_hidden(array('fclty_id'=>$_REQUEST['id']));
    shn_form_fsclose();
    
    if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));

    shn_form_fclose();
}
/**
 * @name    Search Query Generation
 * @access  public
 * @return  void
 * @param   string $fopen_name
 * @param   string $fsopen_name
 * @TODO    fix to search by provider name and recipient name as well
 */
function shn_bsm_search_result(){   
    
    global $global;
    global $conf;
		$_SESSION['bsm']['add']['fclty_id'] = trim($_POST['fclty_id']);
    $service_category = trim($_POST['service_category']);
    $service_type = trim($_POST['service_type']);
    $service_state = trim($_POST['service_state']);
    $provider_last_name = trim($_POST['provider_last_name']);
    $provider_first_name = trim($_POST['provider_first_name']);
    $recipient_last_name = trim($_POST['recipient_last_name']);
    $recipient_first_name = trim($_POST['recipient_first_name']);

    $sql = "SELECT fs.fclty_uuid AS fclty_uuid, st.serv_cate as category,s.serv_state as state,serv_state_dt as state_datetime,s.serv_notes as notes,  s.serv_uuid as service_uuid,s.serv_start_dt as start_datetime, serv_end_dt as end_datetime , s.serv_type as type FROM bsm_fclty_serv fs INNER JOIN bsm_service s ON fs.serv_uuid=s.serv_uuid INNER JOIN bsm_serv_type st ON st.serv_type = s.serv_type WHERE s.deactivate_dt IS NULL ";
    if($service_category && $service_category != '--ALL--')
        $sql .= "AND s.serv_cate = '$service_category' ";
    if($service_type && $service_type !='--ALL--')
        $sql .= "AND s.serv_type = '$service_type' ";
    if($service_state && $service_state !='--ALL--')
        $sql .= "AND s.serv_state = '$service_state' ";

    if ($provider_first_name!=null || $provider_last_name!=null){
        $ppsql = "SELECT p_uuid FROM bsm_person WHERE deactivate_dt IS NULL ";
        $ppsql .= ($provider_last_name!=null) ? "AND last_name like '%".$provider_last_name."%' " : '';
        $ppsql .= ($provider_first_name!=null) ? "AND first_name like '%".$provider_first_name."%' " : '';
        $sql .= "AND s.prov_p_uuid IN (".$ppsql.") ";
    }
    if ($recipient_first_name!=null || $recipient_last_name!=null){
        $rpsql = "SELECT p_uuid FROM bsm_person WHERE deactivate_dt IS NULL ";
        $rppsql .= ($recipient_last_name!=null) ? "AND last_name like '%".$recipient_last_name."%' " : '';
        $rppsql .= ($recipient_first_name!=null) ? "AND last_name like '%".$recipient_first_name."%' " : '';
        $sql .= "AND s.recp_p_uuid IN (".$rpsql.") ";
    }
    return $sql;
}

/*
?><TR>
    <TD> <?php   echo $detail['service_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=service&rtnid='.$detail['service_uuid'].'">'.$detail['service_uuid'].'</a><br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['start_datetime'] || $detail['end_datetime'] ? '<b>From: </b>'.$detail['start_datetime'].'<br><b>To: </b>'.$detail['end_datetime'] : ''; ?> </TD>
    <TD> <?php   echo $detail['category'] || $detail['type'] ? '<b>C: </b>'.$detail['category'].'<br>'.'<b>T: </b>'.$detail['type'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['state'] || $detail['state_datetime'] ? '<b>S:</b>'.$detail['state'].'<br>'.'<b>D:</b>'.$detail['state_datetime'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['provider_name'] || $detail['recipient_name'] ? '<b>P:</b>'.$detail['provider_name'].'<br>'.'<b>R:</b>'.$detail['recipient_name'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['notes'] ? $detail['notes'].'<br>' : ''; ?> </TD>

    </TR>
*/

/**
 * @name Search Result Display
 * @param string $subquery 
 * @param mixed $limit 
 * @param mixed $offset 
 * @access public
 * @return void
 */
function shn_bsm_search_result_vw($subquery="SELECT serv_id FROM bsm_service", $offset=-1, $return=false){
    global $global;
    global $conf;
		$id = $_SESSION['bsm']['edit']['fclty_uuid'];
    $_SESSION['bsm']['search']['subquery'] = $subquery;
    $limit = $conf['mod_bsm_search_limit'];
    echo "<br />";
    echo '<a class="but" title="'._('Add').'" href="index.php?mod='.$global['module'].
            '&act=add&entity=service&id='.$id.'">'." click to ADD new record.".'</a><br>';
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
}
/**
 * @name    Navigation Controll
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
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records found.  ').'</strong>'._('[Click on ID with hypertext link to edit record]').'<br />';
    shn_bsm_search_nav_arrows($rs);
}
function shn_bsm_search_nav(){
    global $global;
    global $conf;

    $limit = $conf['mod_bsm_search_limit'];
    $offset = $_GET['offset']; 
    $total = $_SESSION['bsm']['search']['record_count'];

    $delta = $total - $offset - $limit;

    echo '<br /><strong>'._('Total').' '.$total.' '._('Records found  ').'</strong>'._('[Click on ID with hypertext link to edit record]').'<br />';
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
    global $conf;

    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('ID');?></TD>
    <TD><?= _('Start/End Time');?></TD>
    <TD><?= _('Category/Type');?></TD>
    <TD><?= _('State/Date');?></TD>
    <TD><?= _('Provider/Recipient');?></TD>
    <TD><?= _('Notes');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>
    <TD> <?php   echo $detail['service_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=facility&do=addservice&rtnfrm=cases&rtnfk=&seq=lukup&rtnid='.$detail['service_uuid'].'&lukupid='.$_SESSION['bsm']['add']['fclty_id'].'">'.$detail['service_uuid'].'</a><br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['start_datetime'] || $detail['end_datetime'] ? '<b>From: </b>'.$detail['start_datetime'].'<br><b>To: </b>'.$detail['end_datetime'] : ''; ?> </TD>
    <TD> <?php   echo $detail['category'] || $detail['type'] ? '<b>C: </b>'.$detail['category'].'<br>'.'<b>T: </b>'.$detail['type'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['state'] || $detail['state_datetime'] ? '<b>S:</b>'.$detail['state'].'<br>'.'<b>D:</b>'.$detail['state_datetime'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['provider_name'] || $detail['recipient_name'] ? '<b>P:</b>'.$detail['provider_name'].'<br>'.'<b>R:</b>'.$detail['recipient_name'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['notes'] ? $detail['notes'].'<br>' : ''; ?> </TD>

    </TR>
<?php
    }
}
?>
</TABLE>
<?php
    
}

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
    function set_service_name($service_name)
    {
        $this->__locationName = $service_name;
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

        $this->__joins[] = " LEFT OUTER JOIN service_details ON " .
            " person_status.p_uuid = service_details.poc_uuid ";

        $this->__where[] = " service_details.address LIKE '$local_address' ";
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
        $sql = "SELECT l.serv_id FROM bsm_service l " ;
        
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

function _shn_bsm_add_fclty_service($lukupid,$rtn_id)
{
	global $global;
	$db = $global['db'];
	$sql = "INSERT INTO bsm_fclty_serv (fclty_uuid, serv_uuid) VALUES ('{$lukupid}', '{$rtn_id}')";
//print $sql;
	$res = $db->Execute($sql);
}
?>

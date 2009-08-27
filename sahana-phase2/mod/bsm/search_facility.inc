<?php

/**
 * 
 * Search a facility
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage bsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/* {{{ Search Form */
/**
 * Search default form
 * 
 * @access public
 * @return void
 */
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search')
{
    global $global;
    global $conf;

    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    shn_form_text(_('Name'),'name','size="30"',array('help' => _('Enter full or part of the facility name.'), 'req'=>false));
    include('facility_type.inc');
    shn_form_opt_select('opt_fac_status',_('Status'), null, array('help' => _('Select the status of the facility.'), 'req'=>false));

    
    shn_form_submit(_('Search'));

    shn_form_fsclose();
    /*shn_form_hidden(array('seq'=>$_REQUEST['seq']));
    shn_form_hidden(array('type'=>$_REQUEST['type']));*/
		if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));
    shn_form_fclose();
}
/* }}} */


/* {{{ Search Query Generation (OLD NOT NEEDED) */
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

    //$name = trim($_POST['name']);
    $category = trim($_POST['caegory']);
    $type = trim($_POST['type']);
    $status = trim($_POST['status']);
    $name = trim($_POST['name']);

    global $global;
    global $conf;

    $sql = "SELECT f.fclty_uuid AS facility_uuid , f.fclty_status as status , f.fclty_desc as name ,ft.fclty_cate as category, ft.fclty_type as type FROM bsm_facility AS f INNER JOIN bsm_fclty_type ft ON ft.fclty_type = f.fclty_type WHERE f.deactivate_dt IS NULL ";
    if($category && $category != '--ALL--') {$sql .= "AND f.fclty_cate = '$category' ";}
    if($type && $type !='--ALL--') {$sql .= "AND f.fclty_type = '$type' ";}
    if($status && $status !='--ALL--') {$sql .= "AND f.fclty_status = '$status' ";}
    if($name !=null || $name !="") {$sql .= "AND p.fclty_desc LIKE '%$name%' ";}
    $sql .= "GROUP BY 1";
    return $sql;
}


/* {{{ Search Result Display  (OLD) */
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
function shn_bsm_search_result_vw($subquery="SELECT loc_id FROM bsm_location", $offset=-1, $return=false)
{
    global $global;
    global $conf;
    $_SESSION['bsm']['search']['subquery'] = $subquery;
    $limit = $conf['mod_bsm_search_limit'];
    echo "<br />";
    echo '<a class="but" title="'._('Add').'" href="index.php?mod='.$global['module'].
            '&act=add&entity=facility&rtnid='.$_REQUEST['rtnid'].'">'." click to ADD new record.".'</a><br>';
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
//var_dump($arr);
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
function shn_bsm_search_navigation_bottom($rs)
{
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records were found').'</strong><br />';
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
/* }}} */

/* {{{ Display Results  (OLD) */
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
    
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('UUID');?></TD>
    <TD><?= _('Name');?></TD>
    <TD><?= _('Category');?></TD>
    <TD><?= _('Type');?></TD>
    <TD><?= _('Status');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
//print_r($_REQUEST['seq']);
?><TR>  
    <TD> <?php   echo $detail['facility_uuid'] ? $detail['facility_uuid'].'<br>' : ''; ?> </TD>
    <TD> <?php   if($_REQUEST['seq']=='lukup'){
										echo $detail['name'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=search&entity=facility&rtnfrm='.$_REQUEST['rtnfrm'].'&rtnid='.$_REQUEST['rtnid'].'&rtnfk='.$_REQUEST['rtnfk'].'&seq=lukup&lukupid='.$detail['facility_uuid'].'">'.
                    $detail['name'].'</a><br>' : ''; 
									}
									else {
										echo $detail['name'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=facility&rtnfrm='.$_REQUEST['rtnfrm'].'&rtnid='.$_REQUEST['rtnid'].'&rtnfk='.$_REQUEST['rtnfk'].'&seq=lukup&lukupid='.$detail['facility_uuid'].'">'.
                    $detail['name'].'</a><br>' : ''; 
									}?> </TD>
    <TD> <?php   echo $detail['category'] ? $detail['category'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['type'] ? $detail['type'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['status'] ? $detail['status'].'<br>' : ''; ?> </TD>
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

function _shn_bsm_search_lukup_result($location_uuid=null){
    global $global;
    global $conf;
print 'hello';
//    $name = trim($_POST['name']);
//    $category = trim($_POST['category']);
//    $type = trim($_POST['type']);
//    $iso_code = trim($_POST['iso_code']);
    if ($location_uuid !=null){
    $sql = "SELECT loc_type_prnt FROM bsm_loc_type WHERE deactivate_dt IS NULL AND loc_type = ";
    $sql .= "(SELECT loc_type FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = '".$location_uuid."')";
    $rsql = $global['db']->Execute($sql);
    if ($rsql->RecordCount() > 0){$location_p_type = $rsql->fields['loc_type_prnt'];}
    
    $sql = "SELECT l.loc_uuid FROM bsm_location l INNER JOIN bsm_loc_type lt ON lt.loc_type = l.loc_type ";
    $sql .= "INNER JOIN bsm_loc_cate lc ON lc.loc_cate = lt.loc_cate WHERE l.deactivate_dt IS NULL ";
    //$sql .= "AND l.loc_cate = (SELECT loc_cate FROM bsm_location WHERE deactivate_dt IS NULL AND loc_uuid = '".$location_uuid."') ";
    $sql .= "AND l.loc_type = '".$location_p_type."' ";
    $sql .= 'GROUP BY 1';
    }
    else {$sql = shn_bsm_search_result();}
    return $sql;
}
    /* }}} */

/* }}} */

}
/* }}} */
?>

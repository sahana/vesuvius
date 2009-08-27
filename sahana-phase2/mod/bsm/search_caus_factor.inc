<?php

/**
 * Search for disease signs
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Nuwan Waidyanatha <waidyanatha@lirne.net>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    mod
 * @subpackage bsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/** @name search default form symptom
 * @access public
 * @return void
 * @param   string $fopen_name
 * @example .../index.php?mod=bsm&act=search&entity=caus_fact...
 * @param   string $fsopen_name
 * @example By default first search then rest: edit, add, & delete (avoid duplication!)
 */
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search'){
    global $global;
    global $conf;
    
    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    shn_form_text(_('Causality Factor'),'caus_fact','size="30"',array('help' => _('Enter full or part of the Causality Factor name.'), 'req'=>false));
    $sql = "SELECT DISTINCT option_description AS priority FROM field_options WHERE field_name = 'opt_caus_fact_priority'";
    $rsql = $global['db']->Execute($sql);
    $arropt = array('--ALL--');
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Priority'), null,array('help' => _('Select a location type.'), 'req'=>false));

    shn_form_submit(_('Search'));

    shn_form_fsclose();

    if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));

    shn_form_fclose();
}
/**
 * @name generate search query
 * @access public
 * @return $sql
 * @name search location
 * @example location name = "Kuliyapitiya" and category = "governance" and type = "district"
 */
function shn_bsm_search_result(){   
    global $global;
    global $conf;

    $caus_fact = trim($_POST['caus_fact']);
    $priority = trim($_POST['priority']);

    $sql = "SELECT caus_fact FROM bsm_caus_fact WHERE deactivate_dt IS NULL ";
    if($priority && $priority != '--ALL--')
        $sql .= "AND caus_fact_priority = '$priority' ";
    if($caus_fact) {$sql .= "AND caus_fact LIKE '%$caus_fact%' ";}
    $sql .= 'GROUP BY 1';

    return $sql;
}
/**
 * @name search parent form requested lookup results
 * @access public
 * @return string $sql
 * @param   string $location_uuid
 */
function shn_bsm_search_lukup_result($caus_fact=null){
    global $global;
    global $conf;

    if ($caus_fact !=null){$sql = "SELECT caus_fact FROM bsm_caus_fact WHERE deactivate_dt IS NULL AND caus_fact = '".$caus_fact."' GROUP BY 1";}
    else {$sql = shn_bsm_search_result();}
    return $sql;
}
/**
 * @name search location results for display
 * @access public
 * @return array $arr
 * @param string $subquery
 * @param mixed $limit
 * @param mixed $offset
 */
function shn_bsm_search_result_vw($subquery="SELECT caus_fact FROM bsm_caus_fact", $offset=-1, $return=false){

    global $global;
    global $conf;
    $_SESSION['bsm']['search']['subquery'] = $subquery;
    $limit = $conf['mod_bsm_search_limit'];

    $sql =  "SELECT caus_fact AS caus_fact, caus_fact_desc AS description, caus_fact_code AS code, ";
    $sql .= "caus_fact_enum AS s_enum FROM bsm_caus_fact WHERE deactivate_dt IS NULL AND caus_fact IN ($subquery) GROUP BY 1";

    $rs = $global['db']->SelectLimit($sql,$limit,$offset);
    $rs_count = $global['db']->Execute($sql);
    $rtnid = $_GET['rtnid'];
    if($rs!=null){$arr = $rs->GetAll();}
    echo '<a align="center" title="'._('Add').'" href="index.php?mod='.$global['module'].
            '&act=add&entity=caus_factor&rtnid='.$rtnid.'">'." click to ADD new record.".'</a><br>';
    if($rs_count!=null)
    $_SESSION['bsm']['search']['record_count'] =  $rs_count->RecordCount();
    else
    $_SESSION['bsm']['search']['record_count'] =  0;
    if($return){return $arr;}
    else{shn_bsm_search_nav();
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
 * @name    Navigation Controll
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_bsm_search_navigation_top($rs){
    shn_bsm_search_nav_arrows($rs);
}
/**
 * @name    shn_mpr_search_navigation_bottom NOT NEEDED
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_bsm_search_navigation_bottom($rs){
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records found').'</strong><br />';
    shn_bsm_search_nav_arrows($rs);
}
/**
 *
 * @global <type> $global
 * @global <type> $conf
 */
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
            '&act='.$_GET['act'].'&entity='.$_GET['entity'].'&seq='.$_REQUEST['seq'].
            '&offset=0'.'">'.
            '|&lt;&lt;'._('First').' '.$limit.' '._('Records').' </a></li>';   
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity='.$_GET['entity'].'&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset - $limit ) . '">'.
            '&lt;&lt;'._('Previous').' '.$limit.' '._('Records').' </a></li>';
    }
    //Forward Arrows
    if( $delta > 0 ){
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity='.$_GET['entity'].'&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset + $limit ) . '">'.
            _('Next').' '.($delta < $limit ? $delta : $limit).' '._('Records').' &gt;&gt; </a></li>';
        //Right at Last
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity='.$_GET['entity'].'&seq='.$_REQUEST['seq'].
            '&offset='.($total - $limit).'">'.
            _('Last').'  '. $limit.' '._('Records').' &gt;&gt;|</a></li>';
    }
?>
</ul>
<?php

}
/* @name display location search results
 * @access public
 * @return void
 * @param array $details
 */
function shn_bsm_search_show_result($details){
    
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('Enum');?></TD>
    <TD><?= _('Caus Factor');?></TD>
    <TD><?= _('Code');?></TD>
    <TD><?= _('Description');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>  <TD> <?php   echo $detail['s_enum'] ? $detail['s_enum'].'<br>' : ''; ?> </TD>
    <?php if($_REQUEST['seq']=='lukup'){
    ?><TD> <?php   echo $detail['caus_fact'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=search&entity=caus_factor&rtnfrm='.$_REQUEST['rtnfrm'].'&rtnid='.$_REQUEST['rtnid'].
                    '&seq=lukup&lukupid='.$detail['caus_fact'].'">'.$detail['caus_fact'].'</a><br>' : ''; ?> </TD>
    <?php } else {
    ?><TD> <?php   echo $detail['caus_fact'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=caus_factor&rtnid='.$detail['caus_fact'].'">'.
                    $detail['caus_fact'].'</a><br>' : ''; ?> </TD>
    <?php } ?>
    <TD> <?php   echo $detail['code'] ? $detail['code'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['description'] ? $detail['description'].'<br>' : ''; ?> </TD>

    </TR>
<?php
    }
}
?>
</TABLE>
<?php
}

/* {{{ Get Trackers */
/**
 * Get List of Trackers
 * 
 * @param mixed $p_uuid 
 * @access public
 * @return void
 
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
    echo '<a title="'._('View').'" href="index.php?mod='.$global['module'].'&act=viewmp&id='.
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
            'href="index.php?mod='.$global['module'].'&act=status&id='.$detail['p_uuid'].
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
 
class SearchQuery
{
/* {{{ Varibles */
    /* {{{ private variables 
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
    */

/* }}} */


/* }}} */
?>

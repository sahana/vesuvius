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

    shn_form_text(_('Disease'),'disease','size="30"',array('help' => _('Enter full or part of the name.'), 'req'=>false));

    $sql = "SELECT DISTINCT dis_type AS d_type FROM bsm_dis_type WHERE deactivate_dt IS NULL ";
    $rsql = $global['db']->Execute($sql);
    $arropt = array('--ALL--');
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Type'), 'type',null,array('help' => _('Select a disease type or select --ALL-- if in doubt.'), 'req'=>false));

    $sql = "SELECT option_description AS priority FROM field_options WHERE field_name = 'opt_dis_priority'";
    $rsql = $global['db']->Execute($sql);
    $arropt = array('--ALL--');
    foreach ($rsql AS $r => $rv)
    {
        array_push($arropt,$rv[0]);
    }
    $arropt = array_combine($arropt,$arropt);
    shn_form_select($arropt,_('Priority'), null, array('help' => _('Select the disease priority or select --ALL-- if in doubt.'), 'req'=>false));
    shn_form_text(_('ICD 10 Code'),'icd_code','size="30"',array('help' => _('Enter full or part of the ICD 10 code.'), 'req'=>false));
    shn_form_text(_('ICD 10 descritpion'),'icd_desc','size="30"',array('help' => _('Enter full or part of the ICD 10 description.'), 'req'=>false));
    shn_form_submit(_('Search'));

    shn_form_fsclose();
    if (!isset($_REQUEST['seq']) || $_REQUEST['seq']==null){shn_form_hidden(array('seq'=>'fetch'));}
    else {shn_form_hidden(array('seq'=>$_REQUEST['seq']));}
    if($_GET['rtnid']!=null) shn_form_hidden(array('rtnid'=>$_GET['rtnid']));
    if($_GET['rtnfrm']!=null) shn_form_hidden(array('rtnfrm'=>$_GET['rtnfrm']));
    if($_GET['rtnfk']!=null) shn_form_hidden(array('rtnfk'=>$_GET['rtnfk']));
    shn_form_fclose();
    if($conf['debug']){
    	print"<hr>request =".$_REQUEST['seq'].", rtnid =".$_GET['rtnid'].", rtnfrm =".$_GET['rtnfrm'].", rtnfk =".$_GET['rtnfk']."<hr>";
    }
}
/**
 * @name    Search Query Generation
 * @access public
 * @return void
 */
function shn_bsm_search_result(){

    $disease = trim($_POST['disease']);
    $type = trim($_POST['type']);
    $priority = trim($_POST['priority']);
    $icd_code = trim($_POST['icd_code']);
    $icd_desc = trim($_POST['icd_desc']);

    global $global;
    global $conf;

    $sql = "SELECT disease AS disease FROM bsm_disease WHERE deactivate_dt IS NULL ";
    //$sql = "SELECT disease AS disease FROM bsm_disease WHERE deactivate_dt IS NULL or deactivate_dt = '0000-00-00 00:00:00';";
    
    if($conf['debug']=="true"){
    	print "<hr>".$sql."<hr>";
    }
    
    if($disease !=null || $disease !="") {$sql .= "AND disease LIKE '%$disease%' ";}
    if($type && $type !='--ALL--') {$sql .= "AND dis_type = '".$type."' ";}
    if($priority && $priority != '--ALL--') {$sql .= "AND dis_priority = '$priority' ";}
    if($icd_code && $icd_code !='--ALL--') {$sql .= "AND icd_code = '$icd_code' ";}
    if($icd_desc !=null || $icd_desc !="") {$sql .= "AND icd_desc LIKE '%$icd_desc%' ";}
    $sql .= "GROUP BY 1";
    
    return $sql;
}
/**
 * @name    Search Result Display
 * @param string $subquery 
 * @param mixed $limit 
 * @param mixed $offset 
 * @access public
 * @return void
 */
function shn_bsm_search_result_vw($subquery="SELECT disease FROM bsm_disease", $offset=-1, $return=false){

    $_SESSION['bsm']['search']['subquery'] = $subquery;

    global $global;
    global $conf;

    $limit = $conf['mod_bsm_search_limit'];

    $sql =  "SELECT disease AS disease, dis_enum AS d_enum, dis_type AS d_type, dis_priority AS d_priority, icd_code AS icd_code, ";
    $sql .=  "icd_desc AS icd_desc FROM bsm_disease WHERE deactivate_dt IS NULL AND disease IN ($subquery) ";
    $sql .=  "ORDER BY disease";
    //print $sql;
    $rs = $global['db']->SelectLimit($sql,$limit,$offset);
    $rs_count = $global['db']->Execute($sql);

    if($rs!=null){$arr = $rs->GetAll();}
    echo '<p align="left">'."If the desired result is not in the record set, ".'<a align="center" title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=disease&rtnid='.$_REQUEST['rtnid'].'">'." click to ADD new record.".'</a></p><br>';
    
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

function shn_bsm_search_lukup_result($disease=null){
    global $global;
    global $conf;

    if ($disease !=null){
    	$sql = "SELECT disease FROM bsm_disease WHERE deactivate_dt IS NULL AND disease = '".$disease."' GROUP BY 1";
    	//print "<br>".$sql;
    } else {
    	$sql = shn_bsm_search_result();
    }
    return $sql;
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
 * @param   mixed $details
 * @access  public
 * @return  void
 */
function shn_bsm_search_show_result($details){
    
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('Disease - {Enum}');?></TD>
    <TD><?= _('Type');?></TD>
    <TD><?= _('Priority');?></TD>
    <TD><?= _('ICD Code/ Description');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>
    <?php if($_REQUEST['seq']=='lukup'){
    ?><TD> <?php   echo $detail['disease'] ? '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].
                        '&act=search&entity=disease&rtnfrm='.$_REQUEST['rtnfrm'].'&rtnfk='.$_REQUEST['rtnfk'].'&rtnid='.
                        $_REQUEST['rtnid'].'&seq=lukup&lukupid='.$detail['disease'].'">'.$detail['disease'].'</a><br>' : ''; ?> </TD>
    <?php } else {
    ?><TD> <?php   echo $detail['disease'] ? '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].
                        '&act=edit&entity=disease&rtnid='.$detail['disease'].'">'.$detail['disease'].' - {'.$detail['d_enum'].'}</a><br>' : ''; ?> </TD>
    <?php } ?>
    <TD> <?php   echo $detail['d_type'] ? $detail['d_type'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['d_priority'] ? $detail['d_priority'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['icd_code'] || $detail['icd_desc'] ? $detail['icd_code'].' - '.$detail['icd_desc'].'<br>' : ''; ?> </TD>
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
    /* }}} */

/* }}} */

}
/* }}} */
?>

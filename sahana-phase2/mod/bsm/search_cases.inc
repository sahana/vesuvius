<?php

/**
 * 
 * Search health cases
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

    shn_form_fopen('add&entity=cases',null,array('req_message'=>false));
    shn_form_submit(_('Add New Case'));
    shn_form_fclose();
    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    shn_form_fsopen(_('Search by the disease name'));
    shn_form_text(_('Disease'),'disease','size="30"',array('help' => _('Enter full or part of the facility name.'), 'req'=>false));
    shn_form_fsclose();

    shn_form_fsopen(_('AND : Search by case date range'));
    shn_form_date(_('Begin date'),'case_begin_date');
    shn_form_date(_('End date'),'case_end_date');
    shn_form_fsclose();

    shn_form_fsopen(_('AND : Search case by patient details'));
    shn_form_text(_('Last Name'),'patient_full_name','size="30"',array('help' => _('Enter full or part of the patient last name.'), 'req'=>false));
    //shn_form_text(_('First_Name'),'patient_first_name','size="30"',array('help' => _('Enter full or part of the patient first name.'), 'req'=>false));
    shn_form_opt_select('opt_gender',_('Gender'), null, array('help' => _('Select the patient gender.'), 'req'=>false));
    shn_form_opt_select('opt_age_group',_('Age Group'), null, array('help' => _('Select the patient age group.'), 'req'=>false));
    shn_form_text(_('Age'),'age','size="5"',array('help' => _('Enter full or part of the facility name.'), 'req'=>false));
    shn_form_fsclose();

    shn_form_fsopen(_('AND : Search case by reporting health worker, facility, and location'));
    shn_form_text(_('Last Name'),'hworker_full_name','size="30"',array('help' => _('Enter full or part of the health care worker last name.'), 'req'=>false));
    //shn_form_text(_('First_Name'),'hworker_first_name','size="30"',array('help' => _('Enter full or part of the health care worker first name.'), 'req'=>false));
    shn_form_text(_('Facility Name'),'facility_name','size="30"',array('help' => _('Enter full or part of the facility name.'), 'req'=>false));
    shn_form_text(_('Location Name'),'location_name','size="30"',array('help' => _('Enter full or part of the facility name.'), 'req'=>false));
    shn_form_fsclose();

    shn_form_submit(_('Search'));
    //shn_form_submit(_('Add'));
    shn_form_fsclose();
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
    $disease = trim($_POST['disease']);
    //print $disease;
    $begin_date = trim($_POST['case_begin_date']);
    //print $begin_date;    
    $end_date = trim($_POST['case_end_date']);
    //print $end_date;
    $p_last_name = trim($_POST['patient_full_name']);
    //$p_first_name = trim($_POST['patient_first_name']);
    $p_gender = trim($_POST['opt_gender']);
    $p_age_group = trim($_POST['opt_age_group']);
    $age = trim($_POST['age']);
    $hw_last_name = trim($_POST['hworker_full_name']);
    //$hw_first_name = trim($_POST['hworker_first_name']);
    $facility = trim($_POST['facility_name']);
    $location = trim($_POST['location_name']);

    global $global;
    global $conf;

    $sql = "SELECT case_uuid AS case_uuid FROM bsm_cases WHERE deactivate_dt IS NULL ";
    if($disease !=null || $disease !="") {$sql .= "AND disease LIKE '%$disease%' ";}
    if(isset($begin_date) && $begin_date!=''/*$begin_date != null*/){$sql .= "AND DATEDIFF(case_dt,'".$begin_date."' )>= 0 ";}
    if($end_date != null){$sql .="AND DATEDIFF(case_dt, '".$end_date."' )<= 0 ";}
    if($p_last_name) {$sql .= "AND pat_full_name like '%$p_last_name%' ";}
    //if($p_first_name) {$sql .= "AND pat_first_name like '%$p_first_name%' ";}
    if($p_gender) {$sql .= "AND gender = '$p_gender' ";}
    if($p_age_group) {$sql .= "AND age_grp = '$p_age_group' ";}
    if($age) {$sql .= "AND age = '$age' ";}
    if($hw_last_name) {$sql .= "AND hwork_full_name like '%$hw_last_name%' ";}
    //if($hw_first_name) {$sql .= "AND hwork_first_name like '%$hw_first_name%' ";}
    if($location) {$sql .= "AND loc_name like '%$location%' ";}
    if($facility) {$sql .= "AND fclty_name like '%$facility%' ";}
    $sql .= "GROUP BY 1";
//print $sql;
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
function shn_bsm_search_result_vw($subquery="SELECT disease FROM bsm_disease", $offset=-1, $return=false)
{

    $_SESSION['bsm']['search']['subquery'] = $subquery;

    global $global;
    global $conf;
    $off_temp = trim($_REQUEST['offset']);
    if(isset($off_temp) && $off_temp!='')
    {
		$offset = $off_temp;
    }	
    $limit = $conf['mod_bsm_search_limit'];
    //print $limit;
    //print '<br>';
    //print $offset;

    $sql = "SELECT case_uuid AS case_uuid, case_dt AS case_datetime, pat_full_name AS patient_full_name, ";
    $sql .= "gender AS patient_gender, age_grp AS patient_age_group, age AS patient_age, disease AS disease, ";
    $sql .= "fclty_name AS facility, loc_name AS location, hwork_full_name AS hwork_full_name ";
    $sql .= "FROM bsm_cases WHERE deactivate_dt IS NULL AND case_uuid IN ($subquery) ORDER BY disease";
    $rs = $global['db']->SelectLimit($sql,$limit,$offset);
    $rs_count = $global['db']->Execute($sql);

    if($rs!=null){$arr = $rs->GetAll();}
    echo '<p align="left">'."If the desired result is not in the record set, ".'<a align="center" title="'._('Add').'" href="index.php?mod='.$global['module'].'&act=add&entity=cases'.'">'." click to ADD new record.".'</a></p><br>';
    
    if($rs_count!=null){$_SESSION['bsm']['search']['record_count'] = $rs_count->RecordCount();}
    else {$_SESSION['bsm']['search']['record_count'] =  0;}
    if($return){return $arr;} else 
    {
    	/*print 'test';
print $offset;
print '<br>';
print 'delta';
print $delta;*/
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
    
   /* print 'test';
print $offset;
print '<br>';
print 'delta';
print $delta;*/

    echo '<br /><strong>'._('Total').' '.$total.' '._('Records found').'</strong><br />';    
?>  
<ul class="paging">
<?php   
    //Back Arrows
    if( $offset > 0 ){
        //Right Back
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity=cases&seq='.$_REQUEST['seq'].
            '&offset=0'.'">'.
            '|&lt;&lt;'._('First').' '.$limit.' '._('Records').' </a></li>';   
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity=cases&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset - $limit ) . '">'.
            '&lt;&lt;'._('Previous').' '.$limit.' '._('Records').' </a></li>';
    }
    //Forward Arrows
    if( $delta > 0 ){
        //With Limit Jump
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity=cases&seq='.$_REQUEST['seq'].
            '&offset='. ( $offset + $limit ) . '">'.
            _('Next').' '.($delta < $limit ? $delta : $limit).' '._('Records').' &gt;&gt; </a></li>';
        //Right at Last
        echo '<li><a href="index.php?mod='.$global['module'].
            '&act='.$_GET['act'].'&entity=cases&seq='.$_REQUEST['seq'].
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
    //var_dump($details);
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('Case ID');?></TD>
    <TD><?= _('Case Date');?></TD>
    <TD><?= _('Disease');?></TD>
    <TD><?= _('Patient');?></TD>
    <TD><?= _('Gender');?></TD>
    <TD><?= _('Age Group (age)');?></TD>
    <TD><?= _('Health Worker');?></TD>
    <TD><?= _('Facility');?></TD>
    <TD><?= _('Location');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
?><TR>  
    <TD> <?php   echo $detail['case_uuid'] ? '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=cases&rtnid='.$detail['case_uuid'].'">'.
                    $detail['case_uuid'].'</a><br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['case_datetime'] ? $detail['case_datetime'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['disease'] ? $detail['disease'].'<br>' : ''; ?> </TD>
    <TD><?php echo $detail['patient_full_name'];?></TD>
    <!-- <TD> <?php   echo $detail['patient_last_name'] || $detail['patient_first_name'] || $detail['patient_middle_name']
                    ? $detail['patient_last_name'].', '.$detail['patient_first_name'].' '.$detail['patient_middle_name'] .'<br>' : ''; ?> </TD>-->
    <TD> <?php   echo $detail['patient_gender'] ? $detail['patient_gender'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['patient_age_group'] || $detail['patient_age']
                    ? $detail['patient_age_group'].' ('.$detail['patient_age'].')<br>' : ''; ?> </TD>
    <TD><?php echo $detail['hwork_full_name'];?></TD>
    <!-- <TD> <?php   echo $detail['hwork_last_name'] || $detail['hwork_first_name'] || $detail['hwork_middle_name']
                    ? $detail['hwork_last_name'].', '.$detail['hwork_first_name'].' '.$detail['hwork_middle_name'] .'<br>' : ''; ?> </TD>-->
    <TD> <?php   echo $detail['facility'] ? $detail['facility'].'<br>' : ''; ?> </TD>
    <TD> <?php   echo $detail['location'] ? $detail['location'].'<br>' : ''; ?> </TD>
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

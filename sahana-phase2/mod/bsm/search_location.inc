    <?php

/**
 * Search for locations
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Nuwan Waidyanatha <waidyanatha@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    mod
 * @subpackage dsm
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @TODO       At some point this location object or entity used in dsm module should be blended with the
 * original concept of locations used in main Sahana MPR, GIS, VR etc based on a common acceptable standard set
 * of onthologies and taxinmoies. I didn't want to alter the existing table to cause problems with other modules.
 * @TODO    if form values have changed check with user to save before navigating away from page. Required for
 * "lukup"sequence when navigating away to lookup the paprent location.
 * @TODO    align the parent location field with the rest of the fields
 * @TODO    fix the drop down "location type" to display those records related to the "category"
 *
 */

/** @name search default form location
 * @access public
 * @return void
 * @param   string $fopen_name
 * @example .../index.php?mod=bsm&act=search&entity=location...
 * @param   string $fsopen_name
 * @example By default first search then rest: edit, add, & delete (avoid duplication!)
 */
function shn_bsm_search_default($fopen_name = 'search',$fsopen_name='search'){
    global $global;
    global $conf;
    
    shn_form_fopen($fopen_name,null,array('req_message'=>false));
    shn_form_fsopen(_($fsopen_name));

    include_once('loc_type.inc');

    shn_form_text(_('Location Name'),'loc_name','size="30"',array('help' => _('Enter full or part of the location name.'), 'req'=>false));
    shn_form_text(_('ISO Code'),'loc_iso_code','size="30"',array('help' => _('Enter the location ISO Code.'), 'req'=>false));
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

    $name = trim($_POST['loc_name']);
    $category = trim($_POST['loc_cate']);
   // print $category;
   // print 'test';
    $_SESSION['bsm']['loc']['cat'] = $category;
    $type = trim($_POST['loc_type']);
    $iso_code = trim($_POST['loc_iso_code']);

    $sql = "SELECT l.*, lc.loc_cate FROM bsm_location as l INNER JOIN bsm_loc_type as lt ON lt.loc_type = l.loc_type ";
    $sql .= "INNER JOIN bsm_loc_cate as lc ON lc.loc_cate = lt.loc_cate WHERE l.deactivate_dt IS NULL ";
    if(isset($category) && $category !=''  )
        $sql .= "AND lc.loc_cate = '$category' ";
    if(isset($type) && $type !='')
        $sql .= "AND lt.loc_type = '$type' ";
    if($name) {$sql .= "AND l.loc_name LIKE '%$name%' ";}
    if($iso_code) {$sql .= "AND l.loc_iso_code LIKE '%$iso_code%' ";}

    return $sql;
}
/*
 * @name search parent form requested lookup results
 * @access public
 * @return string $sql
 * @param   string $location_uuid
 */
function shn_bsm_search_lukup_result($location_uuid=null){
    global $global;
    global $conf;

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
/* @name search location results for display
 * @access public
 * @return array $arr
 * @param string $subquery
 * @param mixed $limit
 * @param mixed $offset
 */
function shn_bsm_search_result_vw($subquery="SELECT loc_id FROM bsm_location", $offset=-1, $return=false){

    global $global;
    global $conf;
    $_SESSION['bsm']['search']['subquery'] = $subquery;
    $limit = $conf['mod_bsm_search_limit'];
    echo "<br />";
    echo '<a class="but" title="'._('Add').'" href="index.php?mod='.$global['module'].
            '&act=add&entity=location&rtnid='.$_REQUEST['rtnid'].'">'." click to ADD new record.".'</a><br>';

    //$sql =  "SELECT loc_uuid AS location_uuid, loc_name AS name, loc_cate AS category, loc_type AS type, ";
/*    $sql =  "SELECT loc_uuid AS location_uuid, loc_name AS name, loc_type AS type, ";
    $sql .= "loc_desc AS description, loc_iso_code AS iso_code FROM bsm_location ";
    //$sql .= "WHERE deactivate_dt IS NULL AND loc_uuid IN ($subquery) GROUP BY 1";
    $sql .= "WHERE deactivate_dt IS NULL GROUP BY 1";
*/ 
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
function shn_bsm_search_navigation_bottom($rs){
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records found').'</strong><br />';
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
    <TD><?= _('ID');?></TD>
    <TD><?= _('Name');?></TD>
    <TD><?= _('Category');?></TD>
    <TD><?= _('Type');?></TD>
    <TD><?= _('ISO Code');?></TD>
    <TD><?= _('Description');?></TD>
</THEAD>
<?php
if($details!=null)
{
    foreach($details as $detail)
    {
//print($_REQUEST['seq']);
?><TR>  
    <TD> <?php   echo $detail['loc_uuid'] ? $detail['loc_uuid'].'<br>' : ''; ?> </TD>
    
    <?php if($_REQUEST['flag']=='add'){
    ?><TD> <?php   echo  '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=add&entity=location&rtnfrm='.
                        $_REQUEST['rtnfrm'].'&rtnfk='.$_REQUEST['rtnfk'].'&rtnid='.$_REQUEST['rtnid'].'&seq=lukup&lukupid='.$detail['loc_uuid'].'">'.$detail['loc_name'].'</a><br>'; ?> </TD>
    <?php }
    	?>
    	<?php if($_REQUEST['seq']=='lukup' && $_REQUEST['flag']!='add'){
    ?><TD> <?php   echo  '<a title="'._('Edit').'" href="index.php?mod='.
                        $global['module'].'&act=search&entity=location&rtnfrm='.
                        $_REQUEST['rtnfrm'].'&rtnfk='.$_REQUEST['rtnfk'].'&rtnid='.$_REQUEST['rtnid'].'&seq=lukup&lukupid='.$detail['loc_uuid'].'">'.$detail['loc_name'].'</a><br>'; ?> </TD>
    <?php } if($_REQUEST['seq']!='lukup' && $_REQUEST['flag']!='add') {
    ?><TD> <?php   echo '<a title="'._('Edit').'" href="index.php?mod='.
                    $global['module'].'&act=edit&entity=location&rtnid='.$detail['loc_uuid'].'">'.$detail['loc_name'].'</a><br>' ; ?> </TD>
    <?php } ?>
    <TD> <?php   echo $detail['loc_cate'] .'<br>' ; ?> </TD>
    <TD> <?php   echo $detail['loc_type'] .'<br>' ; ?> </TD>
    <TD> <?php   echo $detail['loc_iso_code'] .'<br>' ; ?> </TD>
    <TD> <?php   echo $detail['loc_desc'] .'<br>' ; ?> </TD>

    </TR>
<?php
    }
}
?>
</TABLE>
<?php
}
?>

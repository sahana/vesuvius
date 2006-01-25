<?php
/* $Id: search.inc,v 1.10 2006-01-25 09:36:32 janakawicks Exp $ */
/**
 * 
 * Main Search Controller of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
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
function shn_mpr_search_default()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen(_('Basic Search'));
    shn_form_text(_('Any Card Number'),'idcard','size="30"');
    shn_form_text(_('Any Name'),'name','size="30"');
    shn_form_submit(_('Next'));
    #shn_form_label("<a href=\"index.php?mod=mpr&act=search_adv&type={$_GET['type']}\">[Advance Search]</a>","");
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'result'));
    shn_form_hidden(array('type'=>$_REQUEST['type']));
    shn_form_fclose();
}
/* }}} */

/* {{{ Search Advance Form */
/**
 * Search Advance form
 * 
 * @access public
 * @return void
 * @todo work on the advance search function
 */
function shn_mpr_search_advance()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen(_('Advance Search'));

    shn_form_fsopen(_('Identity'));
    shn_form_text(_('Identity'),'idcard','size="30"');
    shn_form_checkbox('Identity Card','idcard_chk');
    shn_form_checkbox('Passport Number','pass_chk');
    shn_form_checkbox('Driving License','drv_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Name'));
    shn_form_text(_('Name'),'name','size="30"');
    shn_form_checkbox('Full Name','fullname_chk');
    shn_form_checkbox('Family Name','familyname_chk');
    shn_form_checkbox('Local Name','localname_chk');
    shn_form_fsclose();

    shn_form_fsopen(_('Basic Details'));
    shn_form_fsclose();

    shn_form_submit(_('Next'));
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'result'));
    shn_form_hidden(array('type'=>$_GET['type']));

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
function shn_mpr_search_result()
{   
    //@todo: rewrite

    $name = trim($_POST['name']);
    $idcard = trim($_POST['idcard']);
    $post_type = trim($_POST['type']);

    if($post_type == 'missing')
        $type = " AND opt_status LIKE 'mis'";
    elseif($post_type == 'found')
        $type = " AND opt_status NOT LIKE 'mis'";
    else
        $type = '';

    global $global;
    //check the name with numbers get the p_uuid accroding to the rank

    if($name){
	    //split name
	    $names = preg_split("/\s+/",$_POST['name']);
	    foreach($names as $name){
	        $encode1 .= " encode1 LIKE '".soundex($name)."' OR ";
	        $encode2 .= " encode2 LIKE '".metaphone($name)."%' OR ";
	    }
	    $encode1 = substr($encode1,0,strlen($encode1) - 3);
	    $encode2 = substr($encode2,0,strlen($encode2) - 3);
        $sql = "SELECT pgl_uuid as p_uuid FROM phonetic_word, person_status WHERE pgl_uuid=p_uuid AND (($encode1) OR ($encode2)) $type GROUP BY 1";
    }
    if($idcard)
        $sql = "SELECT a.p_uuid FROM identity_to_person a INNER JOIN person_status b USING (p_uuid) WHERE a.serial LIKE '%$idcard%' $type GROUP BY 1";

    if($name && $idcard)
        $sql = "SELECT a.p_uuid FROM person_status a
                    LEFT OUTER JOIN identity_to_person b USING(p_uuid)
                    LEFT OUTER JOIN phonetic_word c ON c.pgl_uuid = a.p_uuid
                    WHERE ((b.serial LIKE '%$idcard%') OR (($encode1) OR ($encode2))) $type
                    GROUP BY 1";

    if(!($name || $idcard)){
	    if($post_type == 'missing')
	        $sub_sql = "SELECT p_uuid FROM person_status WHERE opt_status
LIKE 'mis' AND isvictim='TRUE'";
	    elseif($post_type == 'found')
	        $sub_sql = "SELECT p_uuid FROM person_status WHERE opt_status
NOT LIKE 'mis' AND isvictim='TRUE'";
	    else
	        $sub_sql = "SELECT p_uuid FROM person_status WHERE
isvictim='TRUE'";
        shn_mpr_search_result_vw($sub_sql );
    }else{
        shn_mpr_search_result_vw($sql);
    }
}
/* }}} */

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
function shn_mpr_search_result_vw($subquery="SELECT p_uuid FROM person_uuid", $offset=-1, $return=false)
{
    
    $_SESSION['mpr']['search']['subquery'] = $subquery;

    global $global;
    global $conf;

    $limit = $conf['mod_mpr']['search']['limit'];

    if($conf['mysql']){
        //Select into temp table todo put the locks to reading tables ;-)
        $sql1 = "CREATE TEMPORARY TABLE tmp_mpr_search( p_uuid BIGINT )";
        $sql2 = "INSERT INTO tmp_mpr_search $subquery";
        $sql3 =  "SELECT 
                    a.p_uuid AS p_uuid, a.full_name AS full_name, a.family_name as family_name,
                    a.l10n_name AS l10n_name, b.height AS height, 
                    b.weight AS weight, b.opt_eye_color AS opt_eye_color, 
                    b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
                    c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
                    c.comments AS comments , d.opt_status as opt_status
                FROM person_uuid a 
                LEFT OUTER JOIN person_physical b USING (p_uuid)
                LEFT OUTER JOIN person_missing c USING (p_uuid)
                LEFT OUTER JOIN person_status d USING (p_uuid)
                INNER JOIN tmp_mpr_search USING (p_uuid)";
        $sql4 = "DROP TABLE tmp_mpr_search";
        $global['db']->Execute($sql1);
        $global['db']->Execute($sql2);
        $rs = $global['db']->SelectLimit($sql3,$limit,$offset);
        $rs_count = $global['db']->Execute($sql3);
        $global['db']->Execute($sql4);
    }else{
        $sql = "SELECT 
            a.p_uuid AS p_uuid, a.full_name AS full_name, a.family_name as family_name,
            a.l10n_name AS l10n_name, b.height AS height, 
            b.weight AS weight, b.opt_eye_color AS opt_eye_color, 
            b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
            c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
            c.comments AS comments , d.opt_status as opt_status
        FROM person_uuid a 
        LEFT OUTER JOIN person_physical b USING (p_uuid) 
        LEFT OUTER JOIN person_missing c USING (p_uuid) 
        LEFT OUTER JOIN person_status d USING (p_uuid)
        WHERE a.p_uuid IN ($subquery)";
        $rs = $global['db']->SelectLimit($sql,$limit,$offset);
        $rs_count = $global['db']->Execute($sql);
    }
    $arr = $rs->GetAll();
    $_SESSION['mpr']['search']['record_count'] =  $rs_count->RecordCount();
    if($return){
        return $arr;
    }else{
        shn_mpr_search_nav();
?>
<DIV ID="result">
<?php
    shn_mpr_search_show_result($arr);
?>
</DIV>
<?php
        shn_mpr_search_nav();
    }
}
/* }}} */

/* {{{ Navigation Controll */
/**
 * Navigation Controll
 * 
 * @deprecated
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_mpr_search_navigation_top($rs)
{
    shn_mpr_search_nav_arrows($rs);    
}

/**
 * shn_mpr_search_navigation_bottom NOT NEEDED
 * 
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_mpr_search_navigation_bottom($rs)
{
    //NOTE: I know this looks really dumb, but 
    //Later we are going to populate some bottom stuff
    echo '<br /><strong>'._('Total').' '.$rs->RecordCount().' '._('Records were found').'</strong><br />';
    shn_mpr_search_nav_arrows($rs);
}

function shn_mpr_search_nav()
{
    global $global;
    global $conf;

    $limit = $conf['mod_mpr']['search']['limit'];
    $offset = $_GET['offset']; 
    $total = $_SESSION['mpr']['search']['record_count'];

    $delta = $total - $offset - $limit;

    echo '<br /><strong>'._('Total').' '.$total.' '._('Records were found').'</strong><br />';    
?>  
<DIV id="paging_nav">
<UL>
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
</UL>
</DIV>
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
function shn_mpr_search_show_result($details)
{
    
    global $global;
    if($_GET['act']!='search')
        $select = true;
?>
<TABLE>
<THEAD>
    <TD><?= _('Picture');?></TD>
    <TD><?= _('Name');?></TD>
    <TD><?= _('Appearance');?></TD>
    <TD><?= _('Missing Details');?></TD>
    <TD><?= _('Status');?></TD>
    <?=($select?'<TD>'._('Select').'</TD>':''); ?>
</THEAD>
<?php
    foreach($details as $detail){
?>
    <TR>
        <TD>
<?php
    shn_show_thumb($detail['p_uuid']); 
    echo '<hr><a title="'._('Audit').'" '.
            'href="index.php?mod='.$global['module'].'&act=auditmp&id='.
            $detail['p_uuid'].'">'._('Audit').'</a>';
?>
        </TD>
        <TD>
<?php
    echo '<a title="'._('Edit').'" href="index.php?mod='.$global['module'].'&act=editmp&id='.
            $detail['p_uuid'].'">'.
            $detail['full_name'].'</a>'.
        '<br>'.$detail['family_name'].'<br>'.$detail['l10n_name'];
    echo '<hr><b>'._('Tracked by').'</b><br />';
    $arr = shn_mpr_search_get_trackers($detail['p_uuid']);
    foreach($arr as $fullname)
        echo "&nbsp;".'<a title="'._('View').'"'.
            'href="index.php?mod='.$global['module'].'&act=viewmp&id='.
            $fullname['p_uuid'].'">'.
            $fullname['full_name'].'</a><br />';
    
    echo "<br />";
    echo '<a title="'._('Add Tracker').'"'.
        'href="index.php?mod='.$global['module'].'&act=add_tracker&id=' .
        $detail['p_uuid'].'&name='.$detail['full_name'].'">'.
        _("Add a tracker").'</a>';
?>
        </TD>
        <TD>
<?php
    echo ($detail['height']?_('Height').' : '.$detail['height'].'<br>':'').
        ($detail['weight']?_('Weight').' : '.$detail['weight'].'<br>':'').
        ($detail['opt_eye_color']?_('Eye Colour').' : '.shn_get_field_opt($detail['opt_eye_color'],'opt_eye_color').'<br>':'').
        ($detail['opt_skin_color']?_('Skin Colour').' : '.shn_get_field_opt($detail['opt_skin_color'],'opt_skin_color').'<br>':'').
        ($detail['opt_hair_color']?_('Hair Colour').' : '.shn_get_field_opt($detail['opt_hair_color'],'opt_hair_color').'<br>':'');
?>
        </TD>
        <TD>
<?php
    echo ($detail['last_seen']?_('Last Seen').' : '.$detail['last_seen'].'<br>':'').
            ($detail['last_clothing']?_('Last Clothing').' : '.$detail['last_clothing'].'<br>':'').
            ($detail['comments']?_('Comments').': '.$detail['comments']:'');    
?>
        </TD>
        <TD>
<?php
    echo shn_get_field_opt($detail['opt_status'],'opt_status');
    if($detail['opt_status'] == 'mis')
        echo '</br /><a title="'._('Change the status to Alive & Well').'"
href="index.php?mod='.$global['module'].'&act=status&id='.$detail['p_uuid'].'"><br
/>('._('Click to change to found').')</a>';
?>      </TD>
        <?=($select?'<TD><a title="'._('Select').'" href="index.php?'.
            $_SERVER['QUERY_STRING'].'&tracker_id='.$detail['p_uuid'].
            '&tracker_relation='.$_POST['rep_relation'].'&seq=tracker_select" > '._('Select').' </a>'.
            '</TD>':''); ?>
    </TR>
<?php
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
function shn_mpr_search_get_trackers($p_uuid)
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
function shn_mpr_search_select($details)
{
    shn_mpr_search_nav();

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
    shn_show_thumb($detail['p_uuid']);
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
    shn_mpr_search_nav();
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
    var $__name;
    var $__address;
    var $__phone;
    var $__email;
    var $__serial_no;
    
    var $__sql;

    var $__joins;
    var $__where;

    var $isvictim;
    var $missing_only;

    /**
     * Sets the name field including soundex and metaphone
     * 
     * @param mixed $name 
     * @access public
     * @return void
     */
    function set_name($name)
    {
        $this->__name = $name;
        //split name
        $names = preg_split("/\s+/",$this->__name);
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

    /**
     * returns the generated sql
     * 
     * @access public
     * @return string
     */
    function get_sql()
    {
        $sql = "SELECT person_status.p_uuid FROM person_status " ;
        
        foreach ($this->__joins as $joins)
            $sql .= $joins ;
        
        if($this->__where){
            $sql .= " WHERE (";
            foreach ($this->__where as $where)
                $sql .= $where . " OR ";

            $sql = substr($sql,0,strlen($sql) - 3);
            $sql .= " ) ";
            
            if($this->isvictim)
                $sql .= " AND person_status.isvictim = 'TRUE' ";
            if($this->missing_only)
                $sql .= " AND person_status.opt_status = 'mis' ";
            $sql .= " GROUP BY 1";
        }       
        return $sql;
    } 
}
/* }}} */
?>

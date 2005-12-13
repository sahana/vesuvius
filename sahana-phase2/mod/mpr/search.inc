<?php
/**
* Description for file
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


/**
 * shn_mpr_search_default 
 * 
 * @access public
 * @return void
 */
function shn_mpr_search_default()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen('Basic Search');
    shn_form_text('Any Card Number','idcard','size="30"');
    shn_form_text('Any Name','name','size="30"');
    shn_form_submit('Next');
    shn_form_label("<a href=\"index.php?mod=mpr&act=search_adv&type={$_GET['type']}\">[Advance Search]</a>","");
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'result'));
    shn_form_hidden(array('type'=>$_GET['type']));
    shn_form_fclose();
}


/**
 * shn_mpr_search_advance 
 * 
 * @access public
 * @return void
 */
function shn_mpr_search_advance()
{
    shn_form_fopen("search",null); 
    shn_form_fsopen('Advance Search');

    shn_form_fsopen('Identity');
    shn_form_text('Identity','idcard','size="30"');
    shn_form_checkbox('Identity Card','idcard_chk');
    shn_form_checkbox('Passport Number','pass_chk');
    shn_form_checkbox('Driving License','drv_chk');
    shn_form_fsclose();

    shn_form_fsopen('Name');
    shn_form_text('Name','name','size="30"');
    shn_form_checkbox('Full Name','fullname_chk');
    shn_form_checkbox('Family Name','familyname_chk');
    shn_form_checkbox('Local Name','localname_chk');
    shn_form_fsclose();

    shn_form_fsopen('Basic Details');
    shn_form_fsclose();

    shn_form_submit('Next');
    shn_form_fsclose();
    shn_form_hidden(array('seq'=>'result'));
    shn_form_hidden(array('type'=>$_GET['type']));

    shn_form_fclose();

}

/**
 * shn_mpr_search_result 
 * 
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
    }else
        shn_mpr_search_result_vw($sql);
        
}


/**
 * shn_mpr_search_result_vw 
 * 
 * @param string $subquery 
 * @param mixed $limit 
 * @param mixed $offset 
 * @access public
 * @return void
 */
function shn_mpr_search_result_vw($subquery="SELECT p_uuid FROM person_uuid", $limit=-1,$offset=-1)
{
    global $global;
    global $conf;
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
        $global['db']->Execute($sql4);
    }else{
        $rs = $global['db']->SelectLimit("
        SELECT 
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
        WHERE a.p_uuid IN ($subquery)",$limit,$offset);
    }
    $arr = $rs->GetAll();
    shn_mpr_search_navigation_top($rs);
?>
<DIV ID="result">
<?php
    shn_mpr_search_show_result($arr);
    shn_mpr_search_navigation_bottom($rs);
?>
</DIV>
<?php
}


/**
 * shn_mpr_search_navigation_top 
 * 
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_mpr_search_navigation_top($rs)
{
    echo '<b>'.$rs->RecordCount().' Records were found</b><br>';    
}

/**
 * shn_mpr_search_navigation_bottom 
 * 
 * @param mixed $rs 
 * @access public
 * @return void
 */
function shn_mpr_search_navigation_bottom($rs)
{
    echo '<b>'.$rs->RecordCount().' Records were found</b><br>';    
}


/**
 * shn_mpr_search_show_result 
 * 
 * @param mixed $details 
 * @access public
 * @return void
 */
function shn_mpr_search_show_result($details)
{
    global $global;
?>
<TABLE>
<THEAD>
    <TD>Picture</TD><TD>Name</TD><TD>Appearance</TD><TD>Missing Details</TD><TD>Status</TD>
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
    echo '<a title="Edit" href="index.php?mod='.$global['module'].'&act=editmp&id='.
            $detail['p_uuid'].'">'.
            $detail['full_name'].'</a>'.
        '<br>'.$detail['family_name'].'<br>'.$detail['l10n_name'];
    echo '<hr><b>Tracked by</b><br />';
    $arr = shn_mpr_search_get_trackers($detail['p_uuid']);
    foreach($arr as $fullname)
        echo "&nbsp;".'<a title="View"'.
            'href="index.php?mod='.$global['module'].'&act=viewmp&id='.
            $fullname['p_uuid'].'">'.
            $fullname['full_name'].'</a><br />';
    
    echo "<br /";
    echo '<a title="Add Tracker"'.
        'href="index.php?mod='.$global['module'].'&act=add_tracker&id=' .
        $detail['p_uuid'].'&name='.$detail['full_name'].'">'.
        "Add a tracker".'</a>';
?>
        </TD>
        <TD>
<?php
    echo ($detail['height']?'Height : '.$detail['height'].'<br>':'').
        ($detail['weight']?'Weight : '.$detail['weight'].'<br>':'').
        ($detail['opt_eye_color']?'Eye Colour : '.shn_get_field_opt($detail['opt_eye_color'],'opt_eye_color').'<br>':'').
        ($detail['opt_skin_color']?'Skin Colour : '.shn_get_field_opt($detail['opt_skin_color'],'opt_skin_color').'<br>':'').
        ($detail['opt_hair_color']?'Hair Colour : '.shn_get_field_opt($detail['opt_hair_color'],'opt_hair_color').'<br>':'');
?>
        </TD>
        <TD>
<?php
    echo ($detail['last_seen']?'Last Seen : '.$detail['last_seen'].'<br>':'').
            ($detail['last_clothing']?'Last Clothing : '.$detail['last_clothing'].'<br>':'').
            ($detail['comments']?'Comments : '.$detail['comments']:'');    
?>
        </TD>
        <TD>
<?php
    echo shn_get_field_opt($detail['opt_status'],'opt_status');
    if($detail['opt_status'] == 'mis')
        echo '</br /><a title="Change the status to Alive & Well"
href="index.php?mod='.$global['module'].'&act=status&id='.$detail['p_uuid'].'"><br
/>(Click to change to found)</a>';
?>      </TD>
    </TR>
<?php
    }
?>
</TABLE>
<?php
}


/**
 * shn_mpr_search_get_trackers 
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
?>

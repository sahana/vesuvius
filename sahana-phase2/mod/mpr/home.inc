<?php
/* $Id: home.inc,v 1.18 2007-05-22 11:29:56 isurunishan Exp $ */

/** 
 * Home Page of the Missing Person Registry 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?= _('Missing Person Registry'); ?></h2>
<?php
global $global;
if(file_exists($global['approot'].'/www/tmp/mprfound.png')){
?>
<img src="tmp/mprfound.png"/>
<img src="tmp/mprfound.png"/>
<?php
}
?>
<p>
<?= _('The Missing person registry is an online bulletin board of missing and found people.
It not only captures information about the people missing and found, but the
information of the person seeking them is also captured, which increases to the chances
of people finding each other. For example if two members of the a family unit is
looking for the head of the family, we can use this data at least to connect those two
family members.'); ?>
<?= _('Features include:');?></p>
<ul>
    <li><?= _('Meta data around the individual such identity numbers, visual
appearance, last seen location, status, etc'); ?></li>
    <li><?= _('Sounds-like name search (using metafore and soundex
algorithms)'); ?></li>
    <li><?= _('Uploading of a persons picture'); ?></li>
    <li><?= _('Grouping by family unit or other groups types'); ?></li>
</ul>
</div>
<?php
/*
 *  Recent Found People people Top 6
 */
 global $global;
	require ($global['approot'] . 'mod/mpr/mpr_lib.inc');
?>
<div id="home_recent">
<h1><?= _('Latest updates on Found People'); ?></h1>
<?php
$limit = 6;
$type = "found";
$rs=shn_mpr_home_show_mpr($type,$limit,0);
shn_mpr_search_show_verticle($_SESSION['result']);

?>
<?php


/*
 *  Recent Missing People Top 6
 */
?>
<h1><?= _('Latest updates on Missing People'); ?></h1>
<?php
$limit = 6;
$type = "missing";
shn_mpr_home_show_mpr($type,$limit,0);
shn_mpr_search_show_verticle($_SESSION['result']);
?>
</div>
<?php
/**
 * Shows the latest updates on missing and found perople
 * 
 * @param string $type 
 * @param int $limit 
 * @access public
 * @return void
 */
function shn_mpr_home_show_mpr1($type="missing",$limit=5)
{
    global $global; 

    #$incident_ids = shn_db_get_all_incidents($_SESSION['user_pref_ims_incident_id']);
    #$incident_sql = implode($incident_ids,"','");
    #$incident_sql = "'$incident_sql'";
    $incident_join = "INNER JOIN resource_to_incident e ON a.p_uuid = e.x_uuid ";
    $sql_missing = "
            SELECT
                a.p_uuid AS p_uuid, a.full_name AS full_name, 
                b.height AS height, b.weight AS weight, 
                b.opt_eye_color AS opt_eye_color, 
                b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
                c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
                c.comments AS comments 
            FROM person_uuid a 
            LEFT OUTER JOIN person_physical b USING (p_uuid) 
            INNER JOIN person_missing c USING (p_uuid)
            INNER JOIN person_status d USING (p_uuid) 
            $incident_join 
            WHERE d.opt_status = 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}' 
            ORDER BY d.updated DESC";

    $sql_found = "
            SELECT
                a.p_uuid AS p_uuid, a.full_name AS full_name, 
                b.height AS height, b.weight AS weight, 
                b.opt_eye_color AS opt_eye_color, 
                b.opt_skin_color AS opt_skin_color, b.opt_hair_color AS opt_hair_color, 
                c.last_seen AS last_seen, c.last_clothing AS last_clothing, 
                c.comments AS comments 
            FROM person_uuid a 
            LEFT OUTER JOIN person_physical b USING (p_uuid) 
            INNER JOIN person_missing c USING (p_uuid)
            INNER JOIN person_status d USING (p_uuid) 
            $incident_join
            WHERE d.opt_status != 'mis' AND e.incident_id = '{$_SESSION['user_pref_ims_incident_id']}'
            ORDER BY d.updated DESC";

    if($type=='missing')
        $rs = $global['db']->SelectLimit($sql_missing,$limit);
    elseif($type=='found')
        $rs = $global['db']->SelectLimit($sql_found,$limit);
    if($rs){
        $arr = $rs->GetAll();
        shn_mpr_search_show_verticle($arr);
    }
}

/**
 * Actual Presentaion of latest updates
 * 
 * @param mixed $details 
 * @access public
 * @return void
 */
function shn_mpr_search_show_verticle1($details)
{
    global $global;
    global $conf;
?>
<DIV ID="result">
<TABLE>
<?
    for($i=0; $i<count($details); $i+=2){
        if($details[$i]){
?>
    <TR>
        <TD>
<?php
	        if(shn_show_thumb_url($details[$i]['p_uuid'],$conf['mod_mpr_upload_pic_handler'],'mpr','addmp_img'))
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	        else{
	            echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	            echo ($details[$i]['height']?_('Height : ').$details[$i]['height'].'<br>':'');
	            echo ($details[$i]['weight']?_('Weight : ').$details[$i]['weight'].'<br>':'');
	            echo ($details[$i]['opt_eye_color']?_('Eye Colour : ').shn_get_field_opt($details[$i]['opt_eye_color'],'opt_eye_color').'<br>':'');
	            echo ($details[$i]['opt_skin_color']?_('Skin Colour : ').shn_get_field_opt($details[$i]['opt_skin_color'],'opt_skin_color').'<br>':'');
	            echo ($details[$i]['opt_hair_color']?_('Hair Colour : ').shn_get_field_opt($details[$i]['opt_hair_color'],'opt_hair_color').'<br>':'');
	            echo ($details[$i]['last_seen']?_('Last Seen : ').$details[$i]['last_seen'].'<br>':'');
	            echo ($details[$i]['last_clothing']?_('Last Clothing : ').$details[$i]['last_clothing'].'<br>':'');
	            echo ($details[$i]['comments']?_('Comments : ').$details[$i]['comments']:'');
	        } 
            echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
                if(shn_show_thumb_url($details[$i+1]['p_uuid'],$conf['mod_mpr_upload_pic_handler'],'mpr','addmp_img'))
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		        else{
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		            echo ($details[$i+1]['height']?_('Height : ').$details[$i+1]['height'].'<br>':'');
		            echo ($details[$i+1]['weight']?_('Weight : ').$details[$i+1]['weight'].'<br>':'');
	                echo ($details[$i+1]['opt_eye_color']?_('Eye Colour : ').shn_get_field_opt($details[$i+1]['opt_eye_color'],'opt_eye_color').'<br>':'');
	                echo ($details[$i+1]['opt_skin_color']?_('Skin Colour : ').shn_get_field_opt($details[$i+1]['opt_skin_color'],'opt_skin_color').'<br>':'');
	                echo ($details[$i+1]['opt_hair_color']?_('Hair Colour : ').shn_get_field_opt($details[$i+1]['opt_hair_color'],'opt_hair_color').'<br>':'');
	                echo ($details[$i+1]['last_seen']?_('Last Seen : ').$details[$i+1]['last_seen'].'<br>':'');
	                echo ($details[$i+1]['last_clothing']?_('Last Clothing : ').$details[$i+1]['last_clothing'].'<br>':'');
	                echo ($details[$i+1]['comments']?_('Comments : ').$details[$i+1]['comments']:'');
		        } 
                echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            }
?>
    </TR>
<?php
        }
    }
?>
</TABLE>
</DIV>
<?php
}
?>


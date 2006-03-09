<?php
/* $Id: home.inc,v 1.1 2006-03-09 09:17:32 janakawicks Exp $ */

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
<h2><?= _('Sahana to Sahana Synchonization Module'); ?></h2>
<!-- <img src="theme/default/img/mpr.png"/> -->
<p><?= _('This module helps you to synchonize data between sahana instances and work sahana in a larger network.'); ?>
<?= _('Features include:');?></p>
<ul>
    <li><?= _('Join to Discovery Servers'); ?></li>
    <li><?= _('Synchonize with different Sahana Instance and Keep a track of updates'); ?></li>
    <li><?= _('Broadcast data that is to be shared'); ?></li>
</ul>
</div>
<?php
/*
 *  Recent Found People people Top 6
 */
?>
<div id="home_recent">
<h1><?= _('Latest updates on Sahana Instances'); ?></h1>
<?php
$limit = 6;
$type = "found";
shn_mpr_home_show_mpr($type,$limit);
?>
<?php


/*
 *  Recent Missing People Top 6
 */
?>
<h1><?= _('Latest Synchronization With Other Sahana Instances'); ?></h1>
<?php
$limit = 6;
$type = "missing";
shn_mpr_home_show_mpr($type,$limit);
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
function shn_mpr_home_show_mpr($type="missing",$limit=5)
{
    global $global; 

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
            INNER JOIN person_status d USING (p_uuid) WHERE d.opt_status = 'mis'
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
            INNER JOIN person_status d USING (p_uuid) WHERE d.opt_status != 'mis'
            ORDER BY d.updated DESC";

    if($type=='missing')
        $rs = $global['db']->SelectLimit($sql_missing,$limit);
    elseif($type=='found')
        $rs = $global['db']->SelectLimit($sql_found,$limit);

    $arr = $rs->GetAll();
    shn_mpr_search_show_verticle($arr);
}

/**
 * Actual Presentaion of latest updates
 * 
 * @param mixed $details 
 * @access public
 * @return void
 */
function shn_mpr_search_show_verticle($details)
{
    global $global;
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
	        if(shn_show_thumb($details[$i]['p_uuid']))
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
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
		        if(shn_show_thumb($details[$i+1]['p_uuid']))
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


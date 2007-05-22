<?php
/* $Id $ */

/** 
 * Missing Person Registry Common Libraries 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *@author     Janaka wickramasinghe<janakaopensource.lk>
 * @author	   Isuru Samaraweera<isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage mpr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


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
	     
	        if(shn_show_thumb_url($details[$i]['p_uuid'],'database','mpr','addmp_img',false))
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
            echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
                if(shn_show_thumb_url($details[$i+1]['p_uuid'],'database','mpr','addmp_img'))
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
                echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'" class="hideprint">'._('Assign to more incidents').'</a>';
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




/**
 * Shows the latest updates on missing and found perople
 * 
 * @param string $type 
 * @param int $limit 
 * @access public
 * @return void
 */
function shn_mpr_home_show_mpr($type="missing",$limit=5,$offset)
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

$final_sql="";
    if($type=='missing')
    {
        $final_sql=$sql_missing;
        $rs = $global['db']->SelectLimit($sql_missing,$limit,$offset);
        
    }
    elseif($type=='found')
     {
     $final_sql=$sql_found;     
        $rs = $global['db']->SelectLimit($sql_found,$limit,$offset);
     }
    if($rs){
        $arr = $rs->GetAll();
      //  shn_mpr_search_show_verticle($arr);
    $_SESSION['result']=$arr;
    }
    

$rs1=$global['db']->Execute($final_sql);
//print 'missing'.$rs1;
$count=0;
while (!$rs1->EOF){
	$count++;
$rs1->MoveNext();
}

return $count;
}


?>
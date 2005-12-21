<?php
/**
 * Some Intro text 
 */
?>
<h1 align="center">Missing Person Registry</h1>
<div id="home">
<!-- <img src="theme/default/img/mpr.png"/> -->
<ul>
    <li>Missing Person Registry helps you to find people quickly in the chaos</li>
	<br>
    <li>Ensures every single person is being accounted for and tracked</li>
	<br>
    <li>Helps prioritize releif response to the critically affected</li>
</ul>
</div>
<?php
/**
 *  Recent Found People people Top 5
 */
?>
<DIV ID="left">
<DIV id="heading">Latest updates on Found People
<?php
$limit = 5;
$type = "found";
shn_mpr_home_show_mpr($type,$limit);
?>
</DIV>
</DIV>
<?php


/**
 *  Recent Missing People Top 5
 */
?>
<DIV ID="right">
<DIV id="heading">Latest updates on Missing People
<?php
$limit = 5;
$type = "missing";
shn_mpr_home_show_mpr($type,$limit);
?>
</DIV>
</DIV>
<?php
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
	            echo ($details[$i]['height']?'Height : '.$details[$i]['height'].'<br>':'');
	            echo ($details[$i]['weight']?'Weight : '.$details[$i]['weight'].'<br>':'');
	            echo ($details[$i]['opt_eye_color']?'Eye Colour : '.shn_get_field_opt($details[$i]['opt_eye_color'],'opt_eye_color').'<br>':'');
	            echo ($details[$i]['opt_skin_color']?'Skin Colour : '.shn_get_field_opt($details[$i]['opt_skin_color'],'opt_skin_color').'<br>':'');
	            echo ($details[$i]['opt_hair_color']?'Hair Colour : '.shn_get_field_opt($details[$i]['opt_hair_color'],'opt_hair_color').'<br>':'');
	            echo ($details[$i]['last_seen']?'Last Seen : '.$details[$i]['last_seen'].'<br>':'');
	            echo ($details[$i]['last_clothing']?'Last Clothing : '.$details[$i]['last_clothing'].'<br>':'');
	            echo ($details[$i]['comments']?'Comments : '.$details[$i]['comments']:'');
	        } 
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
		        if(shn_show_thumb($details[$i+1]['p_uuid']))
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a>';
		        else{
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a>';
		            echo ($details[$i+1]['height']?'Height : '.$details[$i+1]['height'].'<br>':'');
		            echo ($details[$i+1]['weight']?'Weight : '.$details[$i+1]['weight'].'<br>':'');
	                echo ($details[$i+1]['opt_eye_color']?'Eye Colour : '.shn_get_field_opt($details[$i+1]['opt_eye_color'],'opt_eye_color').'<br>':'');
	                echo ($details[$i+1]['opt_skin_color']?'Skin Colour : '.shn_get_field_opt($details[$i+1]['opt_skin_color'],'opt_skin_color').'<br>':'');
	                echo ($details[$i+1]['opt_hair_color']?'Hair Colour : '.shn_get_field_opt($details[$i+1]['opt_hair_color'],'opt_hair_color').'<br>':'');
	                echo ($details[$i+1]['last_seen']?'Last Seen : '.$details[$i+1]['last_seen'].'<br>':'');
	                echo ($details[$i+1]['last_clothing']?'Last Clothing : '.$details[$i+1]['last_clothing'].'<br>':'');
	                echo ($details[$i+1]['comments']?'Comments : '.$details[$i+1]['comments']:'');
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


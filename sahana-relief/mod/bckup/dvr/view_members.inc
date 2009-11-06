<?php


/**
 * 
 * View members of each group
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once ($global['approot'] . '/inc/lib_image.inc');

/**
 * 
 * View Members in disaster victims registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Isuru Samaraweera <isuru@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
?>
<div id="home_recent">



<h1><?php echo  _t('Group Members'); ?></h1>
<?php

//shn_show_thumb_url($_SESSION['dvr']['person']['p_uuid'],'', 'dvr', 'adddvr_img',true);
include_once ($global['approot'] . '/mod/dvr/data_access.inc');
$p_uuid = $_GET['groupid'];

$headid = _shn_dvr_get_headid($p_uuid);
$_SESSION['group_head'] = $headid;
//print 'head is '.$headid;
?>
<center>

<?php
$headname = _shn_dvr_get_person_full_name($headid);
shn_show_thumb_url($headid, 'database', 'dvr', 'addvictim_img', false);
print '<br />';
echo 'Group Head'.'<br /><a href="index.php?mod=' . $global['module'] . '&act=view_individual&p_uuid=' . $headid . '">' .$headname. '</a><br />';
?>
<center>
<?php
_shn_dvr_show_members();
?>
</div>
<?php


function _shn_dvr_show_members() {
	global $global;

	#$incident_ids = shn_db_get_all_incidents($_SESSION['user_pref_ims_incident_id']);
	#$incident_sql = implode($incident_ids,"','");
	#$incident_sql = "'$incident_sql'";

	$groupid = $_GET['groupid'];
	$sql = "SELECT distinct a.p_uuid AS p_uuid, a.full_name AS full_name FROM person_uuid a ,image im,person_to_pgroup p WHERE im.x_uuid=a.p_uuid AND p.p_uuid=a.p_uuid AND p.g_uuid='{$groupid}' ORDER BY im.created ";

	$rs = $global['db']->SelectLimit($sql, 16);
              

	
	if ($rs) {
		$arr= $rs->GetAll();
	
		      $arry = array();
		      foreach($arr as $r){
				if($r['p_uuid']!=$_SESSION['group_head']){
					array_push($arry, $r);
					
				}
	          }
		
		
		
		//     print 'co'.count($arr);
	//	$headid = _shn_dvr_get_headid($groupid);
		//shn_show_thumb_url($headid, 'database', 'dvr', 'addvictim_img', false);
		_shn_dvr_show_mem_verticle($arry);
	}
	
}


function _shn_dvr_show_mem_verticle($details) {
	global $global;
	global $conf;
?>
<DIV ID="result">
<TABLE>
<?php
	for ($i = 0; $i < count($details); $i += 2) {
		if ($details[$i]) {
?>
    <TR>
        <TD>
<?php

			// print 'id is '.$details[$i]['p_uuid'];
			
			shn_show_thumb_url($details[$i]['p_uuid'], 'database', 'dvr', 'addvictim_img', false);
			echo '<br /><a href="index.php?mod=' . $global['module'] . '&act=view_individual&p_uuid=' . $details[$i]['p_uuid'] . '">' . $details[$i]['full_name'] . '</a><br />';
}
			//    echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._t('Assign to more incidents').'</a>';
			//    print 'hello';
?>
        </TD>
<?php

			if ($details[$i +1]) {
?>
        <TD>
<?php
                 
		  shn_show_thumb_url($details[$i +1]['p_uuid'], 'database', 'dvr', 'addvictim_img', false);

				echo '<br /><a href="index.php?mod=' . $global['module'] . '&act=view_individual&p_uuid=' . $details[$i +1]['p_uuid'] . '">' . $details[$i +1]['full_name'] . '</a><br />';
                
			}
			//  echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._t('Assign to more incidents').'</a>';
?>
        </TD>
<?php

		}
?>
    </TR>
    </TABLE>
</DIV>
    
<?php

	//}
}
function _shn_dvr_get_person_full_name($person_uuid)
{
	
		
    global $global;

    $db = $global['db'];
    $sql="SELECT full_name FROM person_uuid WHERE p_uuid ='{$person_uuid}'";
    $res = $db->Execute($sql);
    $group=$res->fields['full_name'];
    return $group;
	
}
?>


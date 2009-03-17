
<?php
include_once ($global['approot'] . '/inc/lib_image.inc');
/**
 * Home Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera(isuru@opensource.lk) 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 ?>
<div id="home">
<h2><?php echo  _t('Disaster Victim Registry'); ?></h2>
<p>
<?php

	 print _t("The Disaster Victim Registry is a central online repository where information on all the disaster victims and families, especially identified casualties, evacuees and displaced people can be stored. Information like name, age, contact number, identity card number, displaced location, and other details are captured. Picture and finger print details of the people can be uploaded to the system. People can also be captured by group for efficiency and convenience."  );
?>

</p>

<strong><?php echo _t("Features include:")?></strong>
<ul>
    <li>
    <?php

	print _t("Capture Information on Disaster Victim groups (Tourists, Passengers, Families, etc.)")
?>
    </li>
    <li>
    <?php print _t("Capture Information on each disaster victim") ?>
    </li>
    <li>
    <?php print _t("Picture upload and finger print upload facility")?>
    </li>
    <li>
    <?php print _t("Searching for different groups and individuals") ?>
    </li>
    <li>
    <?php print _t("Modify Information on groups and individuals") ?>
    </li>
    <li>
    <?php print _t("Various Reporting functionalities") ?>
    </li>
   <!-- <li>
    <?php print _t("Forecasting methods based on statistics") ?>
   
    </li>-->
</ul>
<strong><?php echo _t("Description of Actions:")?></strong><br/>
    <ul>
        <li><a href="index.php?mod=dvr&act=add_new_grp"><b><?php echo  _t('Add New Group'); ?> </b></a><br/><?php echo  _t('Adding a new disaster victim group'); ?></li>
        <li><a href="index.php?mod=dvr&act=add_new_indv"><b><?php echo  _t('Add New Individuals'); ?> </b> </a><br/><?php echo  _t('Adding a disaster victim under each and every victim group'); ?></li>
        <li><a href="index.php?mod=dvr&act=search_group"><b><?php echo  _t('Search & Edit Group'); ?></b></a><br/><?php echo  _t('Searching and editing a victim group'); ?></li>
        <li><a href="index.php?mod=dvr&act=search_individual"><b><?php echo  _t('Search & Edit Individuals'); ?></b></a><br/><?php echo  _t('Searching and editing a victim'); ?>
        <li><a href="index.php?mod=dvr&act=list_groups"><b><?php echo  _t('List groups/ View members'); ?></b></a><br/><?php echo  _t('List all the groups and view members'); ?></li>
        <li><a href="index.php?mod=dvr&act=drill_downby_group"><b><?php echo  _t('Drill Down By Group'); ?> </b></a><br/><?php echo  _t('Drill down by disaster victim group report'); ?></li>
        <li><a href="index.php?mod=dvr&act=drill_downby_shelter"><b><?php echo  _t('Drill Down By Shelter'); ?> </b></a><br/><?php echo  _t('Drill down by shelter report'); ?></li>
        <li><a href="index.php?mod=dvr&act=drill_downby_incident"><b><?php echo  _t('Drill Down By Incident'); ?> </b></a><br/><?php echo  _t('Drill down by incident report'); ?></li>
</ul>




<br/>
</div>

<div id="home_recent">



<h1><?php echo  _t('Latest updates on Reported  Victims'); ?></h1>
<?php

    _shn_dvr_home_show_dvr();
?>
</div>

<?php




function _shn_dvr_home_show_dvr()
{
    global $global; 
    global $conf;
   
    $sql= "SELECT distinct a.p_uuid AS p_uuid, a.full_name AS full_name FROM person_uuid a ,image im, resource_to_incident pi where im.x_uuid=a.p_uuid and a.p_uuid=pi.x_uuid and im.x_uuid=pi.x_uuid and pi.incident_id='{$_SESSION['dvr']['incident_id']}' and category='dvr_person' ORDER BY im.created DESC";
   // $sql= "SELECT distinct a.p_uuid AS p_uuid, a.full_name AS full_name FROM person_uuid a ,image im where im.x_uuid=a.p_uuid and category='dvr_person' ORDER BY im.created DESC";        

           $rs = $global['db']->SelectLimit($sql,$conf['mod_dvr_images']);
   
    if($rs){
        $arr = $rs->GetAll();
   
        _shn_dvr_search_show_verticle($arr);
    }
}









function _shn_dvr_search_show_verticle($details)
{
    global $global;
    global $conf;
?>
<DIV ID="result">
<TABLE>
<?php
    for($i=0; $i<count($details); $i+=2){
        if($details[$i]){
?>
    <TR>
        <TD>
<?php
          shn_show_thumb_url($details[$i]['p_uuid'],'database','dvr','addvictim_img',false);
	        echo '<br /><a href="index.php?mod='.$global['module'].'&act=view_individual&p_uuid='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	      
	      
   
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
    shn_show_thumb_url($details[$i+1]['p_uuid'],'database','dvr','addvictim_img',false);
               
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=view_individual&p_uuid='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		            
		        } 
              //  echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._t('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            }
?>
    </TR>
<?php
        }
      ?>
      
          </TABLE>
</DIV>
<?php
    }
?>




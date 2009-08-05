<?php
/**Home page of the Organization Registry
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage or
 */
	include_once "view_org.inc";
	global $global;
	include_once $global['approot']."/inc/reporting/lib_chart.inc";
	global $conf;
	$db=$global["db"];
	$q="SELECT count(o_uuid) as cnt FROM org_main";
	$res=$db->Execute($q);
	$org_no=0;
	if(!$res->EOF){
		// I see no use of the following code hence commenting it.
		/*$q="SELECT value FROM config WHERE module_id='admin' AND confkey='acl_base'";
		$res_tmp=$db->Execute($q);
		if($res_tmp->fields[0]=='installed'){
			$org_no=($res->fields[0])-1;
		}else{*/
			$org_no=($res->fields[0]);
		/*}
		$org_no=($org_no<0)?0:($org_no+1);*/
	}else{
		$org_no="Zero";	
	}

?>
<div id="home">
  <h1>
    <?php echo _lc($conf['mod_or_name'])?>
  </h1>
	<div>
		<b><em>
			<?php echo _t("\"who is doing what and where\"")?> 
		</b></em>
	</div>
	<p>
    <?php echo _t('The Organization Registry keeps track of every registered organization.').' '._t('It captures not only the places where they are active, but also captures information on the range of services they are providing in each area.')."\n"?>
	</p>

	<h2>
		<?php echo _t("Current features include:")?>
	</h2>
	
	<ul>
		<li>
			<?php echo _t("Capturing organizational information of a relief organization and all the activities they have in the region")."\n"?>
		</li>	
		<li>
			<?php echo _t('Capturing the essential services each group is providing and where')."\n"?>
		</li>
		<li>
			<?php echo _t('Reporting on the services and support in the region')."\n"?>
		</li>
		<li>
			<?php echo _t('Importantly where there are no aid services being provided')."\n"?>
		</li>
	</ul>

<br />
<strong><?php echo _t("Description of Actions:");?></strong>
<br />
<ul>
	<li><a href="index.php?mod=or&act=reg_org"><b><?php echo  _t('Register an organization'); ?>
	</b></a><br />
	<?php echo  _t('Adds an organization\'s details to sahana.'); ?></li>
	<li><a href="index.php?mod=or&act=reg_operation"><b><?php echo  _t('Register a branch'); ?>
	</b> </a><br />
	<?php echo  _t('Adds the details of a branch of an organization to sahana.'); ?></li>
	<li><a href="index.php?mod=or&act=search"><b><?php echo  _t('Search organizations'); ?></b></a><br />
	<?php echo  _t('Find the organisation(s) by specifying its details.'); ?></li>
	<li><a href="index.php?mod=or&act=view_org"><b><?php echo  _t('View And Edit'); ?></b></a><br />
	<?php echo  _t('View a list of registered organizations. Their details can be viewed / edited by clicking on the appropriate links.'); ?>

</ul>
<br />


</div>

    
<div align=center><?php 
   

    if ($org_no > 0) {    
    ?>
    <div align=center><?php echo _t('Service Coverage') ?> </div>
<br />

<div align=center>
<?php echo "<div class='message information' align='left' style='width: 765px; margin-left: 20px;'>";?>
<strong><?echo _t("Important:")."<br/>";?></strong><?php    echo _t("If you add a new Organization/Department or a Branch, It may take few minutes to update the pie chart.");
    echo "</div>";  ?>
</div>
    <?php
        print("<table align=center><tr><td>");
	    shn_chart_display("shn_or_service_coverage_chart"); 
        print("</td></tr></table><p></p>");
	?></div>
<?php 
    } 
    ?>


<div><a href="index.php?mod=or&act=view_org">
<center><strong> <?php echo $org_no ?></strong><?php echo _t(" Organizations/Departments/Branches have been registered")?>
</center>
</a></div>
<?php
	ob_start();
	_shn_or_viewform_latest_orgs(5);
	$content = ob_get_contents();
	ob_end_clean();

if($content != ""){
	?>

<br />
<div id="note"><strong><?php echo _t("Recently registered organizations")?></strong>
</div>
	<?php
	echo $content;
}

	require_once($global['approot']."/inc/lib_rss.inc");
	shn_rss_add_feed('new_org_list',_t('Recently Registered organizations'));

?>


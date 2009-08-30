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
    <h2>
        <?php echo _lc($conf['mod_or_name'])?>
    </h2>
    <div>
        <b>
	    <em>
                <?php echo _t("\"who is doing what and where\"")?> 
	    </em>
	</b>
    </div>
	
    <p>
        <?php echo _t('The Organization Registry keeps track of every registered organization.').' '._t('It captures not only the places where they are active, but also captures information on the range of services they are providing in each area.')."\n"?>
    </p>
    
    <h3>
        <?php echo _t('Functionality')."\n" ?>
    </h3>
    
    <ul>
        <li>
	    <strong>
	        <a href="index.php?mod=or&act=search">
	            <?php echo _t('Search')."\n"; ?>
		</a>
	    </strong>
	    <div class="info">
	        <?php echo  _t('Search for an organization or organizations by specifying its details.'); ?>
            </div>
	</li> 
	<li>
	    <strong>
	        <?php echo  _t('Register'); ?>
	    </strong>
	    <ul>
	        <li>
		    <a href="index.php?mod=or&act=reg_org">
		        <?php echo  _t('Register an Organization'); ?>
		    </a>
		    <div class="info">
		        <?php echo  _t('Add an organization\'s details to the database.'); ?>
		    </div>
		</li>
		<li>
		    <a href="index.php?mod=or&act=reg_operation">
		        <?php echo  _t('Register a Department or Branch Under a Registered Organization')."\n"; ?>
		    </a>
		    <div class="info">
		        <?php echo  _t('If you have already added an organization, you can register a branch or department of that organization with this function.').' '.
			            _t('The branch will be able to be allocated tasks indepedently from the parent organization.')."\n"; ?>
		    </div>
		</li>
	    </ul>
	</li>
	
	<li>
	    <strong>
	        <a href="index.php?mod=or&act=view_org">
		    <?php echo  _t('View And Edit'); ?>
	        </a>
	    </strong>
	    
	    <div class="info">
		<?php echo  _t('This function returns a list of registered organizations.').' '._t('Their details can then be viewed and updated.'."\n"); ?>
	    </div>
	</li>

	<li>
	    <strong>
	        <?php echo  _t('Reports'); ?>
	    </strong>
	    
	    <ul>
	        <li>
		    <a href="index.php?mod=or&act=drill_report_loc">
		        <?php echo  _t('Drill Down by Geographic Coverage'); ?>
		    </a>
		    <div class="info">
		        <?php echo  _t('This report allows users to identify which sectors are operating within a location.').' '._t("It's useful for identifying whether any gaps in exist."); ?>
		    </div>
		</li>
	        <li>
		    <a href="index.php?mod=or&act=drill_report_org">
		        <?php echo  _t('Drill Down by Organizational Coverage'); ?>
		    </a>
		    <div class="info">
		        <?php echo  _t('This report indicates the number of organizations within a single sector that are offering services at each location.'); ?>
		    </div>
		</li>
		
		<li>
	            <a href="index.php?mod=or&act=org_sector">
		        <?php echo  _t('Organizations by Sector'); ?>
		    </a>
                    <div class="info">
		        <?php echo  _t('This report provides a list of all organizations, services they offer, their locations and contact information.'); ?>
		    </div>
		</li>
            </ul>
	</li>
    </ul>
</div> <!-- end of <div id="home> -->
<div>

<?php if($org_no > 0) {
  // if there are registered organisations, 
  // then display a pie chart of demonstrating their distribution
?>
  <h2><?php echo _t('Service Coverage') ?></h2>

  <div style="margin: 1em auto;">
    <?php shn_chart_display("shn_or_service_coverage_chart"); ?>
  </div>

  <div class="message information">
    <strong>
      <?php echo _t("Important:"); ?><br/>
    </strong>
    <?php echo _t("If you add a new organization, department or branch, it may take few minutes to appear in the pie chart."); ?>
  </div>
    
<?php
} else {
// if organisations haven't been registered yet, then say so
?>
<div class="org_no">
  <a href="index.php?mod=or&act=view_org">
    <?php
      echo _t("No organizations, departments or branches have been registered.");
    ?>
  </a>
</div><?php 
} //endif
?>
</div>
<?php
if ( $org_no == 1 ){
?>
<div class="org_no">
  <a href="index.php?mod=or&act=view_org">
      <?php
        echo _t("One organization, department or branch has been registered.");
      ?>
  </a>
</div>
<?php
	} elseif ( $org_no > 1 ){ 
?>
<div class="org_no">
  <a href="index.php?mod=or&act=view_org">
    <?php echo $org_no.' '._t(" organizations, departments and branches have been registered"); ?>
  </a>
</div>
<?php
}
?>

<?php
	ob_start();
	_shn_or_viewform_latest_orgs(5);
	$content = ob_get_contents();
	ob_end_clean();

if($content != ""){
	?>
<br />
<div id="note">
    <?php echo _t("Recently registered organizations")?>
</div>
	<?php
	echo $content;

	require_once($global['approot']."/inc/lib_rss.inc");
	shn_rss_add_feed('new_org_list',_t('Recently registered organizations'));
}

<?php
/**
* The Situation Report (SITRep) Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Pradeeper <pradeeper@respere.com>
* @copyright    Respere - http://respere.com/
* @package		sahana
* @subpackage   sr
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*  
*/

include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once "lib_form.inc";
include_once "handler_report_store.inc";
include_once "lib_reports.inc";
include_once($global['approot'].'inc/lib_log.inc');


function shn_sr_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    shn_mod_menuopen(_t('Situation Reporting'));
    	shn_mod_menuitem('default',_t('Home'));
    	shn_mod_menuitem('create',_t('Create'));
    	shn_mod_menuitem('update',_t('Update'));
    	shn_mod_menuitem('view',_t('View'));
    shn_mod_menuclose();

    include $global['approot'].'/inc/handler_mainmenu.inc';

}

// Form submition capture
function shn_sr_form_submit()
{
	$key=$_POST['key'];
	
	switch ($key) {
		
		// Report registration
		case "reg":
			$rpt_name=$_POST['name'];
			$rpt_desc=$_POST['desc'];
			
			echo $_POST['alert_head'];
			
			// check whether there was a report name provided
			if(strlen($_POST['name']) == 0) {
				$chk = 'empty';
				add_error(
					_t('Please create a name for the report.')
				);
			}
			
			// determine if $chk has already been intialized,
			// which occurs when strlen($_POST['name']) == 0.
			// if not, intialize it from the report's name
			if (!$chk){
				$chk = shn_sr_chk_rpt_name($rpt_name);
			}
			// checking whether the report name is already in the db
			if ($chk=="No"){
				// if no then register
				shn_sr_store_reg_new_report($rpt_name,$rpt_desc);
			} elseif ($chk=='empty') {
				// don't do anything, the error message is generated above
				shn_sr_report_register();
			} else {
				// if name is already there then ask for another name
				add_error(
				  _t('A report has already been registered with this name.').' '.
				  _t('Please create a unique name for your report.').' '.
				  _t('We suggest using the format YYYYMMDD-name.')
				  );
				
				shn_sr_report_register();
			}

		break;
		
		// Report detail update
		case "reports":
			if($_POST['chk']=="Save"){ // check whether user has pressed 'save' or 'cancel'
				$rpt_id=$_POST['id'];
				$rpt_name=$_POST['name'];
				$rpt_summary=$_POST['summary'];
				$rpt_event=$_POST['event'];
				$rpt_action=$_POST['action'];
				$rpt_figure=$_POST['figure'];
				shn_sr_store_report_update($rpt_id, $rpt_name, $rpt_summary, $rpt_event, $rpt_action, $rpt_figure);
			} else {
				// back to main report list
				add_warning(_t('Editing of the report has been canceled.'));
				shn_sr_report_list("update");
					
			}
		break;	
	}
}

function shn_sr_default()
{
	?>
	<h1>
	  <center><?php echo (_t("Situation Reporting")); ?></center>
	</h1>
	
	<p>
	  <?php echo (_t("The Situation Reporting module allows responding agencies to generate reports about the current situation in each incident.").' '.
	  _t('Reports can be worked on collaboratively.'));
	  ?>
	</p>
    <!-- Hidden as a test
    <h2>
      <?php echo (_t("Functionality")); ?>
    </h2>
      
    <ul>
      <li>
        <a href="index.php?mod=sr&act=create"><b><?php echo  (_t("Create").' :')?></b></a><br />
        <?php echo  (_t("This function creates new situation reports."))?>
      </li>
      <li>
        <a href="index.php?mod=sr&act=update"><b><?php echo  (_t("Update").' :')?></b></a><br />
        <?php echo  (_t("Reports can be updated collaboratively and can be host as a single version."))?>
      </li>
      <li>
        <a href="index.php?mod=sr&act=view"><b><?php echo  (_t("View").' :')?></b></a><br/>
        <?php echo  (_t("This will provides, reports navigation and easy browsing. Exporting reports in to other formats (such as PDF, Text, etc.) will be available soon."))?>
      </li>
    </ul>
    -->
<h2>
	<?php 
	  //To do, check if reports have been generated before posting this
	  echo (_t("Latest Reports")); ?>
	</h2>
	  <?php
	  //displays a list of reports in <div id="result">
	  shn_sr_report_list_core(); 
	  //To do, check if reports have been generated before posting this ?>
	  <h2>
	  <?php echo _t("Create a New Report"); ?>
	  </h2>
	  <?php shn_sr_report_register();
    
}

function shn_sr_create()
{
	print '<h1>'."Report an incident".'</h1>';
	// capture basic "report" information
	shn_sr_report_register();
}


function shn_sr_update()
{
	// List all the reports
	shn_sr_report_list("update",'all');
}

// update a selected report
function shn_sr_report_update()
{
	// capture the id and report name from URL
	$rpt_id=$_GET['id'];
	$rpt_name=$_GET['rpt'];
	shn_sr_report_detail_form($rpt_id, $rpt_name);
}

// view a selected report
function shn_sr_report_view()
{
	// capture the id and report name from the URL
	$rpt_id=$_GET['id'];
	$rpt_name=$_GET['rpt'];
	//print "report id is $rpt_id and report name is $rpt_name";
	shn_sr_pull_report($rpt_id);
}

function shn_sr_view()
{
	shn_sr_report_list("view");
}


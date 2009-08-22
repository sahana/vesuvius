<?php

include_once($global['approot']."inc/user_feedback.inc");
include_once ($global['approot']."/inc/lib_menu.inc");

function shn_home_default()
{

  global $conf;    

?>
  <h2>
    <center>
     <?php echo _t("Welcome to the Sahana FOSS Disaster Management System")."\n" ?>
     </center>
  </h2>

  <div id="home";>
    <p>
		<?php echo _t('Sahana is a collection of web based disaster management
    	modules that enhance the preparation for, response to and recovery from
    	large-scale humanitarian coordination and collaboration problems in 
    	disaster situations.');?>
    </p>
  </div>

  <h2>
    <?php 	echo _t('Activated Modules') ?>
  </h2>

<div id="result";>
  <table>
    <thead style="height: 3em;">
      <td>
        <?php echo _t("Module Name") ?>
      </td>
      <td>
        <?php echo _t("Module Description")."\n" ?>
      </td>
    </thead>
  <?php

#	_shn_home_module_info searches to see whether the module is activated,
#	it then returns the full name of the module and it's description in a table.
# See line 216 onwards for full details

    _shn_home_module_info('sr',_t(
       "The situation reporting module provides a mechanism to store and
        retrieve reports easily. Reports can be updated collaboratively
        between users of Sahana.")."\n");
  
  _shn_home_module_info('pre',_t(
       "Most disasters and there effects can be identify before it occurs.
        Identifying and tracking those information will helps to do a 
        efficient and effective planing for recover or minimize the damage
        and public education. From that effort for relief waorks and 
        rehabilitation can be minimized. Sahana disaster preparedness 
        system is addressing requirements of pre disaster deployments. 
        Sahana disaster preparedness system is addressing four basic 
        functionalities in disaster preparedness: Assessing
        Vulnerabilities, Planning, Reporting and Warning."));  
  
  _shn_home_module_info('msg',_t(
       "Messaging module is the main communicative root of the Sahana 
        system. It is used to send SMS, e-mail alerts and/or messages to
        various groups and individuals before, after and during a disaster.
        It also provides a convenient way of grouping mobile phone numbers
        and e-mail addresses."));
        
  _shn_home_module_info('sm',_t(
        "The Situation Awareness module provides a mechanism to 
         collaboratively provide an overview of the developing disaster,
         using online mapping (GIS). You can add markers and pictures to
         pin point incidents on the map.")."\n");

    _shn_home_module_info('gps',_t(         
         "The GPS Interface module provides the ability to use Sahana 
          with a GPS. The data is imported/exported via GPX files which
          can be transferred to/from a GPS device via software such as 
          GPS Babel.")."\n");

    _shn_home_module_info('hr',_t(
       "The Housing Registry And Reconstruction Module is a
        centralized database in which users can track homeless 
        families, damaged houses, contractors and reconstruction sites
        effectively."));
        
    _shn_home_module_info('itag',_t(
       "Provides image management capabilities."));
        
    _shn_home_module_info('pnm',_t(
       "This module is the public interface for the press and media. It 
       provides access to the most up-to-date information about the 
       situation."));     
                
    _shn_home_module_info('gis',_t(
       "Allows you to locate activities on a map providing current 
        situation awareness."));

    _shn_home_module_info('cr',_t("This module tracks all shelters and 
       stores basic details regarding them. It collaborates with other 
       modules to track people associated with a shelter, the services 
       available etc."));

    _shn_home_module_info('dvr',_t(
       "The Disaster Victim Registry is a central online repository where
        information on all the disaster victims and families, especially 
        identified casualties, evacuees and displaced people can be stored.
        Information like name, age, contact number, identity card number, 
        displaced location, and other details are captured. Picture and 
        finger print details of the people can be uploaded to the system."));

    _shn_home_module_info('rms',_t("Tracks requests for aid and matches 
       them against donors who have pledged aid."));

    _shn_home_module_info('cr',_t("Tracks the location, distibution, 
       capacity and breakdown of victims in shelter."));
       
    _shn_home_module_info('ws',_t(
       "Web service module provides a set of web services which can be 
        used by other Sahana Instances and third-party systems to share 
        information with Sahana."));
       
    _shn_home_module_info('ms',_t(
       "The MapServer Configuration module provides the ability to 
        configure maps to be displayed by the integrated UMN MapServer. 
        Please note that you have to install the UMN/Mapserver GIS Server
        on your system to use this module."));
        
    _shn_home_module_info('ims',_t(
       "The Sahana Inventory Management System is a database to keep 
        track of all aid items and supplies kept in your Organization's
        inventories. It not only keeps track of the location and 
        quantities of items available, but it also tracks expiry dates, 
        re-order levels and items in transit. The system is designed to 
        be simple to a diverse groups of users to interact and manage 
        stocks in inventories located around the region.")); 
        
    _shn_home_module_info('dms',_t(
       "The Disease Surviellance Module contains data mining and 
        surviellance informations on spreading of diseases. Graphs, maps
        and charts are being used to represent those information. The 
        simple disease diagnosis system can be used in rulal areas and 
        also as a primary disease diagnosis. This module also consists 
        of data collecting and storing system for data analyzing and 
        mining purposes."));
       
    _shn_home_module_info('sn',_t(
       "This is the administrative portal of the Sahana social network, 
        from here you would be able to do the administrative functions 
        such as view all the details of SN members,making interest groups
        based on various conditions and let members know about those 
        groups. Not only that through this portal the admin would give 
        authentication for particualar members to share info over the 
        network."));       
        
    _shn_home_module_info('vol',_t("
      The volunteer registry keeps track of all Volunteers working in the 
      disaster region. It captures not only the places where they are 
      active, but also captures information on the range of services they 
      are providing in each area."));
      
    _shn_home_module_info('vm',_t("
    The volunteer management module keeps track of projects and volunteers."));      
        
    _shn_home_module_info('cs',_t("
      The Aid Catalog is used by the Inventory and the Request Management
      System as a reference classification of all aid item types. Item 
      types are classified and grouped by type (e.g. food, medical) and 
      units are associated to aid types for quantifying purposes by the 
      other modules. The quantities of Aid is not kept in this module 
      but for example in the Inventory and Request / Pledge Management 
      Modules."));
        
    _shn_home_module_info('rs',_t("
      The Reporting System helps to generate reports based on Sahana's
      database. It aggregates all the module reports in one place for 
      making easier the user to view, search reports and charts. On the 
      other hand it performs as the administrator's interface for 
      module reports."));      
      
    _shn_home_module_info('pref',_t("
      User Preferences Module allow you to configure Sahana."));
       
    _shn_home_module_info('admin',_t("The System Administration module 
    allows you to configure and customize Sahana based on your requirements."));
  ?>
    </table>
  </div> <?php /*<div id="result">*/?>
  <p>
    <div id="home-sys-info" style="float:left";>
    <?php
      echo _t("For more detail on the Sahana system, see the ").
        '<a href="http://www.sahana.lk">' ._t("Sahana Website").'</a><br/>';
        
      echo _t("For live help from the Sahana community on using this 
        application, go to ").'<a href="http://www.sahana.lk/chat">'.
        _t("Sahana Community Chat").".\n</a>\n<br/>";
        
     echo _t("To access Sahana documentation, go to ").
        '<a href="http://wiki.sahana.lk/doku.php?id=doc:home">'.
        _t("Sahana Wiki")."\n</a>\n<br/>";

     if ($conf['root_name'] != '') {
         echo '<br/>'._t("Administrator")." : ".$conf['root_name'];
         }
         if ($conf['root_email'] != '') {
           echo '.<br/>'._t("Email")." : ".$conf['root_email'];
         }
         if ($conf['root_tel'] != '') {
             echo '<br/>'._t("Telephone")." : ".$conf['root_tel'];
         }
     ?>
    </div>
  </p>
<?php
} // closes function shn_home_default()

function _shn_home_module_info($module, $description) 
{
    global $conf;  ?>

    <?php
    if ($conf['mod_'.$module.'_enabled']) { 
	
	# Have used inline styles because I didn't want to disrupt the sahana.css
	# Will fix. -timClicks
	?>
        <tr>
            <td style ="padding:1em;" >
              <strong>
                 <?php
				  echo "<a href=\"index.php?mod=$module\" >\n";
                  echo $conf['mod_'.$module.'_name']."\n" ?>
                </a>
              </strong> 
            </td>
            <td style ="padding:1em;" >
              <?php echo $description."\n" ?>
            </td>
        </tr>
<?php }
}

/**
 * Show a welcome page for first time users.
 *
 */
function shn_home_welcome(){
    global $global; 
?>
<div id="install-success-wrapper" style="float:left";>
  <h2>
    <?php echo _t("Welcome to the Sahana FOSS Disaster Management System")?> 
  </h2>

  <div id="install-success" style="float:left";>
    <h4>
      <?php echo _t("Congratulations!").' '._t('You have successfully installed Sahana.')?>
    </h4>
    <p>
     <?php echo _t("Sahana works through a series of modules.")." ".
    _t("Each module has its own functionality, for example the \"Situation
        Awareness\" module provides a map of the current event.")." ".
    _t("Modules are semi-autonomous.")." ".
    _t("By this, we mean that each works independently and should be considered an
        application in its own right.")." ".
    _t("This has several advantages, enabling developers to quickly build new components.")." ".
    _t("The disadvantage of this approach is that the learning curve for new users is a little steeper.")." ".
    _t("Don't worry, Sahana has been successfully deployed in disasters all around the world.")
    ?>
    </p>
  </div><?php /* id="install-success" */ ?>
  
  <div id="first-steps" style="float:left";>
    <h4>
      <?php echo _t("First Steps") ?>
    </h4>
    <div>
      <h5>
        <?php echo _t("Name Your Disaster") ?>
      </h5>
      <p>
      <?php echo 
        _t("Before you begin experimenting with all of the modules,
           you need to give your event a label.")." ".
       _t("This will be used by Sahana to collate all of the data.")
      ?>
      </p>

      <h5>
        <?php echo _t("Setup your location") ?>
      </h5>
      <p>
      <?php echo 
        _t("Sahana also needs to know the relevant locations of your event.")." ".
        _t("You can set your locations within three levels.")." ".
        _t("Locations and level are set arbitraily by you.")." ".
        _t("They are completely flexible, and may be set according to your needs.")
      ?>
      </p>
    
      <h5>
        <?php echo _t("Customization") ?>
      </h5>
      <p>
      <?php echo 
        _t("You may need to customize Sahana according to your requirements.")." ".
        _t("You can do this via the \"Administration\" tab in menu.")." ".
        _t("By default this appears on the left.")
       ?>
      </p>

      <tt>
       <?php echo _t("Note: This information is repeated in the \"Administration\" menu.") ?>
      </tt>
    </div>
  </div><?php /* id="first-steps" */?>
  <div id="nav-tips">
    <h4>
      <?php echo _t("Navigation Tips") ?>
    </h4>
    <p>
    <?php echo 
      _t("Sahana's main navigation is split into two menus.").' '.
      _t("One selects the module you wish to operate, known as the 
        \"Main Menu\" the other, known as the \"Module Menu\" 
        navigates within that module.").' '.
       _t("By default, the Main Menu appears under the Module Menu.")
      ?>
     </p>
  </div><?php /*id="nav-tips"*/ ?>
</div><?php /*id="install-success-wrapper"*/
	if(shn_acl_is_enabled()){
		if($_SESSION['logged_in']===true && $_SESSION['user']=="admin" && $_SESSION['user_id']=="1"){
			shn_admin_default();
			// unset it the first time flag so that this never appears again
			$_SESSION['first_time_run']=false;
		}else{
			$_SESSION['last_module']="admin";
			$_SESSION['last_action']="default";
		?>
		
  <div class="message information">
    <strong> 
    <?php
    echo _t(
      "Please login as an Administrator to customize Sahana.")
    ?> 
    </strong>
  </div>
<?php
		}
	}else{
		shn_admin_default();
		// unset it the first time flag so that this never appears again
		$_SESSION['first_time_run']=false;
	}
}

function shn_home_bug_report(){
  echo "<div class=\"bug-report\">";
	echo "<h2 class=\"bug-report\">"._t("Sahana bug reporting")."</h2>";
	
	shn_form_fopen("bug_report_cr");
	shn_form_fsopen(_t("Report a bug"));	
	shn_form_text(_t("Your name"),"reporter_name",null,array("req"=>true));
	shn_form_text(_t("Contact email"),"reporter_email");
	shn_form_text(_t("Bug Title"),"title",null,array("req"=>true));
	shn_form_text(_t("Module(s)"),"target_module");
	shn_form_textarea("What you did before you caught the bug","steps",null,array("req"=>true));
	shn_form_textarea(_t("Bug Description / Additional Notes"),"notes");
	shn_form_fsclose();
	shn_form_submit(_t("Cancel"),"name='cancel'");
	shn_form_submit(_t("Create Bug Report"),"name='download_rep'");
	shn_form_fclose();
  echo "</div>";
}

function shn_home_bug_report_cr(){
	//shn_home_bug_create??
	global $global,$conf;
	if(isset($_POST['cancel'])){
		shn_home_default();
	}else if(isset($_POST['download_rep'])){
		$reporter_name = $_POST['reporter_name'];
		$error = false;
		if(isset($reporter_name)==false || strlen($reporter_name)==0){
			add_error(_t("Please enter your name"));
			$error = true;
		}
		$reporter_email = $_POST['reporter_email'];
		$bug_title = $_POST['title'];
		if(isset($bug_title)==false || strlen($bug_title)==0){
			add_error(_t("Please enter a title for the bug"));
			$error = true;
		}
		$bug_module = $_POST['target_module'];
		$steps = $_POST['steps'];
		if(isset($steps)==false || strlen($steps)==0){
			add_error(_t("Please enter what you did before this bug appeared."));
			$error = true;
		}
		$notes = $_POST['notes'];
		
		if($error==false){
		$comment = "<!--Please email this file to bugs@sahana.lk-->";
		$timestamp = date("Ymdhis");
		$tname = "shn-bug-report".$timestamp;//tempnam("/tmp","shn-bug-report");
		if(is_writable($global['approot']."www/tmp/")){
			$fp = fopen($global['approot']."www/tmp/".$tname,"w+");		
		
			fwrite($fp,"<?xml version=\"1.0\"?>");
			fwrite($fp,$comment);
			fwrite($fp,"<bug-report id=\"$timestamp\">");
			fwrite($fp,"<reporter-name>$reporter_name</reporter-name>");
			fwrite($fp,"<reporter-email>$reporter_email</reporter-email>");
			fwrite($fp,"<title>$bug_title</title>");
			fwrite($fp,"<module>$bug_module</module>");
			fwrite($fp,"<steps>$steps</steps>");
			fwrite($fp,"<notes>$notes</notes>");
			fwrite($fp,"<environment>".$_SERVER['HTTP_USER_AGENT']."</environment>");
			fwrite($fp,"</bug-report>");
			fclose($fp);
		
			echo "<h2>"._t("Thank you for your effort towards making Sahana better.")."</h2>";
			echo "<div class='message information'>";
			echo "<p>"._t("Please download the bug report from the link below and email it to ")."<a href=\"mailto:bugs@sahana.lk\">bugs@sahana.lk</a></p>";
			echo "<br/>";
			echo "<a href=\"?mod=home&act=download_bug_report&stream=text&brpt_id=$tname\">"._t("Download the bug report here")."</a>";
			echo "</div>";
		}else{
			add_error(sprintf(_t("The path \"%s\" is not writable"),$global['approot']."www/tmp/"));
			add_error(_t(
			  "Unfortunately, reporting this bug failed. 
			  Sahana lacks file write permissions to the folder."));							
		}
		}else{
			shn_home_bug_report();
		}
	}
	
	
}

function shn_home_faq(){
	_shn_home_faq();
}

/*
 * Enable disable user feedback user interface.
 */

function shn_home_userfb(){
    echo "<h2>"._t("Help / User feedback preferences")."</h2>";
	shn_form_fopen("userfb_cr","home",array("req"=>false));
	shn_form_fsopen(_t("Enable or disable help and user feeback"));
	$value = shn_get_user_pref_value("home","shn_user_pref_feedback_enabled");
	$valstr = ($value==true?'enabled':'disabled');
	shn_form_radio(array("enabled"=>_t("Enabled"),"disabled"=>_t("Disabled")),_t("Help / User feedback"),"userfb_status","",array('value'=>$valstr));
	shn_form_fsclose();
	shn_form_submit(_t("Cancel"),"name='cancel'");
	shn_form_submit(_t("Save"));
	shn_form_fclose();
}
	
function shn_home_userfb_cr(){
	if(!$_POST['cancel']){
		$valstr = $_POST['userfb_status'];
		if($valstr=='enabled'){
			$ret = shn_user_pref_update('home','shn_user_pref_feedback_enabled',true);
			if($ret == true){
				add_confirmation(_t("Your preferences were successfully updated."));
			}else{
				add_error(_t("An error occured while updating your preferences."));
			}
		}else{
			$ret = shn_user_pref_update('home','shn_user_pref_feedback_enabled',false);
			if($ret == false){
				add_confirmation(_t("Your preferences were successfully updated."));
			}else{
				add_error(_t("An error occured while updating your preferences."));
			}
		}
		shn_home_userfb();
	}else{
		shn_home_default();
	}
}

function shn_text_home_download_bug_report(){
	global $global;
	$bug_report_id = $_REQUEST['brpt_id'];
	header("Content-type: text/xml");
	header("Content-Disposition: attachment; filename=\"$bug_report_id\"");
	$content = file_get_contents($global['approot']."www/tmp/"."/".$bug_report_id);
	print $content;	
	//unlink($global['approot']."www/tmp/"."/".$bug_report_id);
}

// Default stream welcome function 
function shn_XST_home_default() {
    // Currently the stream only redirect to home if there is an error
    echo _t('Welcome to Sahana on the '.$_REQUEST['stream'].' stream.');
}

function shn_home_about(){
	global $global,$conf;
	echo _t('<h2>About Sahana</h2>');
	if(file_exists($global['approot']."about.inc")){
		include_once $global['approot']."about.inc";
		
		global $about;		
		if(function_exists("apache_get_version")){
			$about['apache_version'] = apache_get_version();
		}else{
			$about['apache_version'] = _t("Unable to determine Apache HTTPD version.");
		}
		
		$about['php_version'] = phpversion();
		
		$sql = "SHOW VARIABLES LIKE \"character_set_database\";";
		$res = $global['db']->Execute($sql);
		$about['database_charset']=$res->fields['Value'];

        $sql = "SHOW VARIABLES LIKE \"collation_database\";";
        $res = $global['db']->Execute($sql);
        $about['database_collation']=$res->fields['Value'];		
		
		
		$sql = "SELECT VERSION()";
		$res = $global['db']->Execute($sql);
		$about['mysql_version'] = $res->Fields(0);
		?>
		
		<table border="0" class="about-sahana">
		  <tr>
		      <th colspan="2" valign="middle"><?php echo 'System Information' ?></th>
		  </tr>
		  <tr>
		      <td width="40%"><?php echo _t("Sahana Version") ?></td>
		      <td><?php echo $about['version']?></td>
		  </tr>
		  <tr>
              <td><?php echo _t("Release") ?></td>
              <td><?php echo $about['release'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Release Information")?></td>
              <td><?php echo $about['release_info'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Release Date")?></td>
              <td><?php echo $about['release_date'] ?></td>
          </tr>
          <tr>
            <th colspan="2" valign="middle"><?php echo 'Database Information' ?></th>
          </tr>
          <tr>
              <td><?php echo _t("Database Name")?></td>
              <td><?php echo $conf['db_name'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Database Character Set")?></td>
              <td><?php echo $about['database_charset'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Database Collation")?></td>
              <td><?php echo $about['database_collation'] ?></td>
          </tr>
          <tr>
              <th colspan="2" valign="middle"><?php echo 'Environment Information' ?></th>
          </tr>
          <tr>
              <td><?php echo _t("Apache HTTPD Version")?></td>
              <td><?php echo $about['apache_version'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("PHP Version")?></td>
              <td><?php echo $about['php_version'] ?></td>
          </tr>
          <tr>
              <td><?php echo _t("MySQL Version")?></td>
              <td><?php echo $about['mysql_version'] ?></td>
          </tr>
          <tr>
              <th colspan="2" valign="middle"><?php echo 'System Administrator Information' ?></th>
          </tr>
          <tr>
              <td><?php echo _t("Administrator Name")?></td>
              <td><?php echo ((($conf['root_name']!=null) && (strlen(trim($conf['root_name']))>0))?($conf['root_name']):_t('Information not available')) ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Email")?></td>
              <td><?php echo ((($conf['root_email']!=null) && (strlen(trim($conf['root_email']))>0))?($conf['root_email']):_t('Information not available')) ?></td>
          </tr>
          <tr>
              <td><?php echo _t("Telephone")?></td>
              <td><?php echo ((($conf['root_tel']!=null) && (strlen(trim($conf['root_tel']))>0))?($conf['root_tel']):_t('Information not available')) ?></td>
          </tr>          
		</table>
		<br/>
		<hr/>
		
		<?php
		  $readme = file_get_contents($global['approot']."README");
		?>
		      <script type="text/javascript">
		          var flag=true;
		          function showReadme(){
		              var readmeBlock = document.getElementById('readme');
                      if(readmeBlock){
		                  if(flag==true){
		                      readmeBlock.style.display='block';
		                      flag=false;
		                  }else{
		                      readmeBlock.style.display='none';
		                      flag=true;
		                  }
		              }
		          }
		      </script>
		      <a href="#" onclick="showReadme()"><?php echo _t("Show/Hide Readme") ?></a>
		      <div id="readme" class="hide">
		          <pre>
		          <?php echo $readme; ?>
		          </pre>
		          <br/>
		          <a href="#" onclick="showReadme()"><?php echo _t("Hide Readme") ?></a>
		      </div>  
		      
		      <br/>
		      <a href="http://www.gnu.org/licenses/lgpl.html" target="_blank"><?php echo _t("View License") ?></a>
		<?php
		
		return;
	}else{
		echo _t("About page information cannot be generated.");
		return;
	}
}

function shn_home_mainmenu(){
	global $global,$conf;
	shn_mod_menuopen(_t($conf['mod_home_name']));
	shn_mod_menuitem('about',_t('About Sahana'),'home');
	shn_mod_menuclose();
	include $global['approot']."/inc/handler_mainmenu.inc";
}

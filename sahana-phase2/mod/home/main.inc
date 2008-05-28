<?PHP
include_once($global['approot']."inc/user_feedback.inc");
include_once ($global['approot']."/inc/lib_menu.inc");

function shn_home_default()
{

    global $conf;
    
    ?>

    <div id="home">

    <?php echo "<h2>"._t("Welcome to the Sahana FOSS Disaster Management System")."</h2>"?>
<!--        <img src="theme/default/img/home_pic1.png" align="left" /> -->
    <p><?php echo _t("Sahana is a collection of web based disaster management applications that provides solutions to large-scale humanitarian coordination and collaboration in disaster situation and its aftermath. Sahana consists of several modules for following functionalities:"); ?></p>
        <ul>
    
<?php
    _shn_home_module_info('gis',_t("Allows you to locate activities on a map providing current situation awareness."));
    _shn_home_module_info('mpr',_t("Helps to report and search missing person."));
    _shn_home_module_info('dvr',_t("Traces internally displaced people (IDPs) and their needs."));
    _shn_home_module_info('or',_t("Lists 'who is doing what & where'. Allows relief agencies to self organize the activities rendering fine coordination among them."));
    _shn_home_module_info('rms',_t("Tracks requests for aid and matches them against donars who have pledged aid."));
    _shn_home_module_info('cr',_t("Tracks the location, distibution, capacity and breakdown of victims in shelter."));
    _shn_home_module_info('ims',_t("Effectively and efficiently manage relief aid, enables  transfer of inventory items to different inventories and notify when items are required to refill."));
    _shn_home_module_info('msg',_t("Allows communication by email and SMS text messaging to groups."));
    _shn_home_module_info('vol',_t("Allows managing volunteers by capturing their skills, availability and allocation."));
    _shn_home_module_info('cs',_t("Captures information on different catalogues and measurement units. These information are being used in systems such as Inventory Management System and Request Management System."));
    _shn_home_module_info('sync',_t("Allows data exchange between instances of Sahana by synchronization."));
?>

        </ul>
    <p>
    <?php
        echo _t("For more detail on Sahana system, see ") .
                          '<a href="http://www.sahana.lk">' .
                          _t("Sahana Website").'</a><br/>';
        echo _t("For live help from the Sahana community on using this application, go to ").
              '<a href="http://www.sahana.lk/chat">'._t("Sahana Community Chat")."</a><br/>";
        
        echo _t("To access Sahana documentation, go to ").
              '<a href="http://wiki.sahana.lk/doku.php?id=doc:nwhome">'._t("Sahana Wiki")."</a><br/>";

        if ($conf['root_name'] != '') {
            echo '<br/>'._t("Administrator: ").$conf['root_name'];
        }
        if ($conf['root_email'] != '') {
            echo '.<br/>'._t("Email")." : ".$conf['root_email'];
        }
        if ($conf['root_tel'] != '') {
            echo '<br/>'._t("Telephone")." : ".$conf['root_tel'];
        }
    ?>
        </p>
    </div>

<?php
}
function _shn_home_module_info($module, $description) 
{
    global $conf;

    if ($conf['mod_'.$module.'_enabled']) {
        echo "<li><a href=\"index.php?mod=$module\" ><strong>".$conf['mod_'.$module.'_name'].'</strong></a> - ';
        echo _t($description)."</li>\n";
    }

}

/**
 * Show a welcome page for first time users.
 *
 */
function shn_home_welcome(){
	global $global;
	echo _t("<h2>Welcome to the Sahana FOSS Disaster Management System</h2>")
	?>
<h4><?php echo _t("Congratulations !. You have successfully installed Sahana.")?></h4>
<p><?php echo _t("You may need to customize sahana according to your requirements.") ?></p>
	<?php
	if(shn_acl_is_enabled()){
		
		if($_SESSION['logged_in']===true && $_SESSION['user']=="admin" && $_SESSION['user_id']=="1"){
			shn_admin_default();
			// unset it the first time flag so that this never appears again
			$_SESSION['first_time_run']=false;
		}else{
		
			$_SESSION['last_module']="admin";
			$_SESSION['last_action']="default";
		?>
<div class="message information"><strong> <?php
echo _t("Please login by entering the administrator username and password in the respective text boxes on the left side
		panel to proceed customizing sahana.")
?> </strong></div>
<?php
		}
	}else{
		shn_admin_default();
		// unset it the first time flag so that this never appears again
		$_SESSION['first_time_run']=false;
	}
}

function shn_home_bug_report(){
	echo "<h2>"._t("Sahana bug reporting")."</h2>";
	
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
}

function shn_home_bug_report_cr(){
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
		
			echo "<h2>"._t("Thank you for your effort towards making sahana better.")."</h2>";
			echo "<div class='message information'>";
			echo "<p>"._t("Please download the bug report from the link below and email it to ")."<a href=\"mailto:bugs@sahana.lk\">bugs@sahana.lk</a></p>";
			echo "<br/>";
			echo "<a href=\"?mod=home&act=download_bug_report&stream=text&brpt_id=$tname\">"._t("Download the bug report here")."</a>";
			echo "</div>";
		}else{
			add_error(sprintf(_t("The path \"%s\" is not writable"),$global['approot']."www/tmp/"));
			add_error(_t("Failed to create bug report due to the lack of file write permissions to the above folder."));							
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
				add_confirmation(_t("Your preference was successfully saved."));
			}else{
				add_error(_t("An error occured while saving your preference."));
			}
		}else{
			$ret = shn_user_pref_update('home','shn_user_pref_feedback_enabled',false);
			if($ret == false){
				add_confirmation(_t("Your preference was successfully saved."));
			}else{
				add_error(_t("An error occured while saving your preference."));
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
	global $global;
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
		
		$sql = "SELECT VERSION()";
		$res = $global['db']->Execute($sql);
		$about['mysql_version'] = $res->Fields(0);
		
		?>
		<table border="0">
		  <tr>
		      <th colspan="2" valign="center"><?php echo 'System Information' ?></td>
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
              <th colspan="2" valign="center"><?php echo 'Environment Information' ?></td>
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
              <th colspan="2" valign="center"><?php echo 'System Administrator Information' ?></td>
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
		      <a href="http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt" target="_blank"><?php echo _t("View License") ?></a>
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

?>

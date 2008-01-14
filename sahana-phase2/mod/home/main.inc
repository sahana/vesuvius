<?PHP



function shn_text_home_help()
{
    if(empty($_GET['help_id'])){
        echo "var help_arr = new Array(".count($_SESSION['form_help']).");\n";
        if(isset($_SESSION['form_help']))
            foreach($_SESSION['form_help'] as $help_id => $value){
                $clean_value = preg_replace(array('@([\r\n])[\s]+@','@"@'), array(' ',"'"),$value);
                echo "help_arr[".$help_id."] = \"$clean_value\";\n";
            }
    }else{
        echo $_SESSION['form_help'][$_GET['help_id']];
    }
}


function shn_home_default()
{
    global $conf;
    
    ?>

    <div id="home">

    <?php echo "<h2>"._("Welcome to the Sahana FOSS Disaster Management System")."</h2>"?>
<!--        <img src="theme/default/img/home_pic1.png" align="left" /> -->
    <p><?php echo _("Sahana is a collection of web based disaster management applications that provides solutions to large-scale humanitarian coordination and collaboration in disaster situation and its aftermath. Sahana consists of several modules for following functionalities:"); ?></p>
        <ul>
    
<?php
        _shn_home_module_info('gis',_("Allows you to locate activities on a map providing current situation awareness."));
        _shn_home_module_info('mpr',_("Helps to report and search missing person."));
        _shn_home_module_info('dvr',_("Traces internally displaced people (IDPs) and their needs."));
    _shn_home_module_info('or',_("Lists 'who is doing what & where'. Allows relief agencies to self organize the activities rendering fine coordination among them."));
    _shn_home_module_info('rms',_("Tracks requests for aid and matches them against donars who have pledged aid."));
    _shn_home_module_info('cr',_("Tracks the location, distibution, capacity and breakdown of victims in shelter."));
    _shn_home_module_info('ims',_("Effectively and efficiently manage relief aid, enables  transfer of inventory items to different inventories and notify when items are required to refill."));
    _shn_home_module_info('msg',_("Allows communication by email and SMS text messaging to groups."));
    _shn_home_module_info('vol',_("Allows managing volunteers by capturing their skills, availability and allocation."));
    _shn_home_module_info('cs',_("Captures information on different catalogues and measurement units. These information are being used in systems such as Inventory Management System and Request Management System."));
    _shn_home_module_info('sync',_("Allows data exchange between instances of Sahana by synchronization."));
?>

        </ul>
    <p>
    <?php
        echo _("For more detail on Sahana system, see ") .
                          '<a href="http://www.sahana.lk">' .
                          _("Sahana Website").'</a><br/>';
        echo _("For live help from the Sahana community on using this application, go to ").
              '<a href="http://www.sahana.lk/chat">'._("Sahana Community Chat")."</a><br/>";
        
        echo _("To access Sahana documentation, go to ").
              '<a href="http://wiki.sahana.lk/doku.php?id=doc:nwhome">'._("Sahana Wiki")."</a><br/>";

        if ($conf['root_name'] != '') {
            echo '<br/>'._("Administrator: ").$conf['root_name'];
        }
        if ($conf['root_email'] != '') {
            echo '.<br/>'._("Email")." : ".$conf['root_email'];
        }
        if ($conf['root_tel'] != '') {
            echo '<br/>'._("Telephone")." : ".$conf['root_tel'];
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
        echo _($description)."</li>\n";
    }

}

/**
 * Show a welcome page for first time users.
 *
 */
function shn_home_welcome(){
	global $global;
	echo _("<h2>Welcome to the Sahana FOSS Disaster Management System</h2>")
	?>
<h4><?php echo _("Congratulations !. You have successfully installed Sahana.")?></h4>
<p><?php echo _("You may need to customize sahana according to your requirements.") ?></p>
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
echo _("Please login by entering the administrator username and password in the respective text boxes on the left side
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
	echo "<h2>"._("Sahana bug reporting")."</h2>";
	
	shn_form_fopen("bug_report_cr");
	shn_form_fsopen(_("Report a bug"));	
	shn_form_text(_("Your name"),"reporter_name",null,array("req"=>true));
	shn_form_text(_("Contact email"),"reporter_email");
	shn_form_text(_("Bug Title"),"title",null,array("req"=>true));
	shn_form_text(_("Module(s)"),"target_module");
	shn_form_textarea("What you did before you caught the bug","steps",null,array("req"=>true));
	shn_form_textarea(_("Bug Description / Additional Notes"),"notes");
	shn_form_fsclose();
	shn_form_submit(_("Cancel"),"name='cancel'");
	shn_form_submit(_("Create Bug Report"),"name='download_rep'");
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
			add_error(_("Please enter your name"));
			$error = true;
		}
		$reporter_email = $_POST['reporter_email'];
		$bug_title = $_POST['title'];
		if(isset($bug_title)==false || strlen($bug_title)==0){
			add_error(_("Please enter a title for the bug"));
			$error = true;
		}
		$bug_module = $_POST['target_module'];
		$steps = $_POST['steps'];
		if(isset($steps)==false || strlen($steps)==0){
			add_error(_("Please enter what you did before this bug appeared."));
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
		
			echo "<h2>"._("Thank you for your effort towards making sahana better.")."</h2>";
			echo "<div class='message information'>";
			echo "<p>"._("Please download the bug report from the link below and email it to ")."<a href=\"mailto:bugs@sahana.lk\">bugs@sahana.lk</a></p>";
			echo "<br/>";
			echo "<a href=\"?mod=home&act=download_bug_report&stream=text&brpt_id=$tname\">"._("Download the bug report here")."</a>";
			echo "</div>";
		}else{
			add_error(sprintf(_("The path \"%s\" is not writable"),$global['approot']."www/tmp/"));
			add_error(_("Failed to create bug report due to the lack of file write permissions to the above folder."));							
		}
		}else{
			shn_home_bug_report();
		}
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

?>
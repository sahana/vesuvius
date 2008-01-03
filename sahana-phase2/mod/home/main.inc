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

?>
<?php
/**
 * This is the main file for the Sahana module. Once the module is selected in the 
 * post all actions are passed to this file for processing.
 * <Description of file> 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   akshit sharma
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage theme
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**
 * Place all your dependant libraries below. Given are some typical ones
 * required for the module
 */
include_once $global['approot'].'/inc/lib_menu.inc';
include_once $global['approot'].'/inc/lib_form.inc';
include_once $global['approot'].'/inc/lib_validate.inc';
include_once $global['approot'].'/inc/lib_errors.inc';
include_once $global['approot'].'inc/lib_session/session.inc';

include_once($global['approot'].'inc/lib_log.inc');

/**
 *  This function adds relevant CSS and JavaScript files
 *  to the html header.
 */
 
function shn_theme_html_head()
{
    global $global; 
    include $global['approot']."/inc/lib_xhtml.inc";  
	
	$extra_headers = array( '<script type="text/javascript" src="theme/custom_theme/colorpicker/js/jquery.js" ></script>',
							'<script type="text/javascript" src="theme/custom_theme/colorpicker/js/colorpicker.js" ></script>',
							'<script type="text/javascript" src="theme/custom_theme/colorpicker/js/eye.js" ></script>',
							'<script type="text/javascript" src="theme/custom_theme/colorpicker/js/utils.js" ></script>',
							'<script type="text/javascript" src="theme/custom_theme/colorpicker/js/layout.js?ver=1.0.2" ></script>',
							'<link rel="stylesheet" type="text/css" href="theme/custom_theme/colorpicker/css/colorpicker.css"/>',
							'<link rel="stylesheet" type="text/css" href="theme/custom_theme/colorpicker/css/layout.css"/>'
						   );
						  
    shn_display_xhtml_head($extra_headers);
}


/**
 * This function allows you to override the mainmenu. This is often done 
 * to include the modules own menu
 * 
 * @access public
 * @return void
 */

function shn_theme_mainmenu() 
{
    global $global;
    $module = $global['module'];
    
    // Create the module menu
    shn_mod_menuopen(_t('Custom Theme Module'));
    shn_mod_menuitem('default',_t('Home'));
    shn_mod_menuitem('modify',_t('Modify Theme'));
    shn_mod_menuitem('upload',_t('Upload Custom Logo'));
    shn_mod_menuclose();
   
    // include the main menu so that the user can navigate outside the module
    include $global['approot'].'/inc/handler_mainmenu.inc';
} 


/**
 * This function displays the default page of the module when it is selected
 * This function has to exist! 
 *
 * @access public
 * @return void
 */
function shn_theme_default()
{
    global $global, $conf;

	?>		
	<div id="home">
		<h2><?php echo  _t('Custom Theme Module'); ?></h2>
		<p><?php echo  _t('This is the \'Custom Theme\' module. <br/><br/> Use the \'Modify Theme\' link to customize various page elements to your liking or use the \'Upload Logo\' link to upload your own logo for the site. <br/>')?></p>
		<p><?php echo  _t('Initially, only the site admin can customize various site elements and upload own logo to customize the site for all users.<br/>')?></p>
		<p><?php echo  _t('Other non-admin role\'s users (if they have permission) can also customize site elements or upload their own logo.<br/>')?></p>
		<p><?php echo  _t('Any changes made by any non-admin role\'s user (as mentioned above) will be visible only to that user. Other users will still be viewing the site as the admin customized it, untill they customize the site on their own (in which case also, their customizations will be limited to them only).<br/>')?></p>
		<p><?php echo  _t('The site admin may grant access permissions for other role\'s users by using the admin page for the custom_theme module.<br/>')?></p>		
		<?php 

		//check if current theme is not custom_theme
		if($conf['theme'] != 'custom_theme')
		{
			add_warning ('Your theme is currently not set to custom_theme. Note that any customizations 
			you make using this module will not be effective unless the theme is set to custom_theme.');

			//display link to change theme
			echo ('<p>Go to <a href=\'index.php?mod=admin&act=conf_list\'>Config Values</a> to select custom_theme.</p>');
		}

		else
			echo ('<p>Your theme is set to custom_theme. Any customizations you make will be effective immidiately.</p>');
		?>
	</div>

	<?php
}


/**
 * This is function calls another function that generates the form
 *
 * @access public
 * @return void
 */
function shn_theme_modify()
{
    echo '<h2>'._t('Enter the values for the customizable CSS elements here.').'</h2> <br />';
    echo '<br />';
	
	//this function generates form.
	shn_theme_display_form();
}


/** 
 * This function displays form for uploading own logo by the user
 */
function shn_theme_upload(){
    shn_form_fopen('upload_submit',null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_('Upload logo'));
    shn_form_upload(_('Logo'),"map");
    shn_form_fsclose();
    shn_form_submit(_("Save"));
    shn_form_fclose();	
}


/**
 * This function stores the uploaded logo to the file system with the 
 * currently logged username as the media uuid.
 */
function shn_theme_upload_submit(){
	global $global;
	include_once($global['approot']."/inc/lib_image.inc");
    $logo_id = $_SESSION['user'];
    $info = getimagesize($_FILES["map"]['tmp_name']);
    if($_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
		shn_image_save_to_file("map","www/theme/custom_theme/logos","jpeg_maps",$logo_id);
    } 
    add_confirmation(_(" New logo was succesfully saved"));
}


/**
 * This function displays the form with various CSS element's values 
 * as entered previously by the user.
 * If no values are entered by the user, the values entered by the site 
 * admin are shown.
 * If neither the user nor the admin has entered any values, default values
 * are shown.
 */
function shn_theme_display_form()
{    
	global $global;
    
	$db = $global['db'];
	
	//get the previouly entered values by the user (if any)
	$username = $_SESSION['user'];
	$q = "SELECT * FROM theme_custom_values where username='$username'";
	$res = $db->Execute($q);

	//if $res is not null, i.e. the user has entered some previous values. Load them.
	if (!$res->EOF && isset($res))
	{
		$row = $res->FetchRow();
		$css1 = $row['css1'];
		$css2 = $row['css2'];
		$css3 = $row['css3'];
		$css4 = $row['css4'];
		$css5 = $row['css5'];
		$css6 = $row['css6'];
		$css7 = $row['css7'];
		$css8 = $row['css8'];
		$css9 = $row['css9'];
		$logo = $row['logo'];
		$parent = $row['parent'];
	}
	
	//if user has not entered any previous value
	else
	{
		//check if site admin has entered any custom values
		$adminname= $conf['root_name'];
		$q1 = "SELECT * FROM theme_custom_values where username='$adminname'";
		$res1 = $db->Execute($q1);
		
		//if $res1 is not null, i.e. the site admin has entered some custom values. Load them.
		if (!$res1->EOF && isset($res1))
		{
			$row = $res1->FetchRow();
			$css1 = $row['css1'];
			$css2 = $row['css2'];
			$css3 = $row['css3'];
			$css4 = $row['css4'];
			$css5 = $row['css5'];
			$css6 = $row['css6'];
			$css7 = $row['css7'];
			$css8 = $row['css8'];
			$css9 = $row['css9'];
			$logo = $row['logo'];
			$parent = $row['parent'];
		}
		
		//neither the user nor the site admin has entered any values. Load default values.
		else
		{
			$css1 = '#fff';
			$css2 = '#fff';
			$css3 = '#000';
			$css4 = '#369';
			$css5 = '#369';
			$css6 = '#003366';
			$css7 = '#333333';
			$css8 = '#ffffff';
			$css9 = '#ffffff';
			$logo = False;
			$parent = 'default';
		}
	}
	
	if ($logo)
		$checked = "checked";
	else
		$checked = "";

	// create form with the values loaded above
	shn_form_fopen("save_form", null,array('req_message'=>true));
		shn_form_fsopen("Customize Sahana");
			shn_form_text("Central Box Border Color","css1","size='7'",array("req"=>true, "help"=>"Central Box Border Color", "value"=>$css1));
			shn_form_text("Central Box BG Color","css2","size='7'",array("req"=>true, "help"=>"Central Box BG Color", "value"=>$css2));
			shn_form_text("Text Color","css3","size='7'",array("req"=>true, "help"=>"Text Color", "value"=>$css3));
			shn_form_text("Header BG Color","css4","size='7'",array("req"=>true, "help"=>"Header BG Color", "value"=>$css4));
			shn_form_text("Footer BG Color","css5","size='7'",array("req"=>true, "help"=>"Description of CSS element 5", "value"=>$css5));
			shn_form_text("Upper Menu BG Color","css6","size='7'",array("req"=>true, "help"=>"Description of CSS element 6", "value"=>$css6));
			shn_form_text("Lower Menu BG Color","css7","size='7'",array("req"=>true, "help"=>"Description of CSS element 7", "value"=>$css7));
			shn_form_text("Upper Menu Text Color","css8","size='7'",array("req"=>true, "help"=>"Description of CSS element 8", "value"=>$css8));
			shn_form_text("Lower Menu Text Color","css9","size='7'",array("req"=>true, "help"=>"Description of CSS element 9", "value"=>$css9));
			shn_form_text("Parent Theme","parent","size='20'",array("req"=>true, "help"=>"Description of parent theme", "value"=>$parent));		
			shn_form_label("Use Custom Logo  &nbsp; &nbsp; <input type=\"checkbox\" name=\"logo\" ".$checked." align=\"left\" />", "");
			echo "(default logo will be used if unchecked)";
		shn_form_fsclose();
		echo '<br /> <center>';
		shn_form_submit("Submit");                       // Create the submit button
		echo '</center> <br />';
    shn_form_fclose();                               // Close the form
}

function shn_theme_save_form () {

    global $global, $conf;
	include_once($global['approot']."/inc/lib_image.inc");
	include_once($global['approot']."/inc/lib_uuid.inc");

	//get post data
    $css1 = $_POST['css1'];
    $css2 = $_POST['css2'];
    $css3 = $_POST['css3'];
    $css4 = $_POST['css4'];
	$css5 = $_POST['css5'];
	$css6 = $_POST['css6'];
	$css7 = $_POST['css7'];
	$css8 = $_POST['css8'];
	$css9 = $_POST['css9'];
	$parent = $_POST['parent'];

	if (isset($_POST['logo']))
		$logo = True;
	else
		$logo = False;
	
	//check if the color entered is a valid hexadecimal color code or not
	$pattern = '/^#(([a-fA-F0-9]{3}$)|([a-fA-F0-9]{6}$))/';
	if (!preg_match($pattern,$css1)) {
		add_error('<strong>Central Box Border Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }

	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css2)) {
		add_error('<strong>Central Box BG Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }

	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css3)) {
		add_error('<strong>Text Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }

	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css4)) {
		add_error('<strong>Header BG Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }

	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css5)) {
		add_error('<strong>Footer BG Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }
	
	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css6)) {
		add_error('<strong>Upper Menu BG Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }
	
	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css7)) {
		add_error('<strong>Lower Menu BG Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }
	
	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css8)) {
		add_error('<strong>Upper Menu Text Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }
	
	//check if the color entered is a valid hexadecimal color code or not
	if (!preg_match($pattern,$css9)) {
		add_error('<strong>Lower Menu Text Color</strong> is not a valid hexadecimal color!');
        $error=true;
    }

	//check if the parent theme added is a valid theme or not
	if ($parent!='default' and $parent!='classic' and $parent!='green_theme') {
		add_error('<strong>'.$parent.'</strong> is not a valid Sahana theme!');
        $error=true;
    }
	
	//show if any errors come up
    if ($error) {
	    echo '<h2>'._t('Please correct the errors mentioned above.').'</h2> <br />';
	    echo '<br />';
		shn_theme_display_form();
    } else {
		//store in DB
		$db = $global['db'];
		$username = $_SESSION['user'];
		
		//check if an entry already exists in the DB for this user or not
		$checkquery = "select * from theme_custom_values where username='$username'";
		$checkres = $db ->Execute($checkquery);
		
		//if exists, then upgdate it with latest values entered
		if (isset($checkres) && !$checkres->EOF)
			$q2 = "update theme_custom_values set css1='$css1', css2='$css2', css3='$css3', css4='$css4', css5='$css5', css6='$css6', css7='$css7', css8='$css8', css9='$css9', logo='$logo', parent='$parent', username='$username' where username='$username'";
		
		//if doesnt exist, then insert the new values
		else
			$q2 = "insert into theme_custom_values values (NULL, '$css1', '$css2', '$css3', '$css4', '$css5', '$css6', '$css7', '$css8', '$css9', '$logo', '$parent', '$username')";
		$res2 = $db ->Execute($q2);

		echo '<h2>'._t('Your theme has been updated.').'</h2> <br />';
		echo '<br />';
		add_confirmation ('Congratulations! Your customizations have been successfully saved.');

		if($conf['theme'] != 'custom_theme')
		{
			add_warning ('Your theme is currently not set to custom_theme. Note that any customizations 
			you make using this module will not be effective unless the theme is set to custom_theme.');

			//display link to change theme
			echo ('<p>Go to <a href=\'index.php?mod=admin&act=conf_list\'>Config Values</a> to select custom_theme.</p>');

		}
		//display link to go back to sahana home
		echo '<p>Go to <a href=\'index.php\'>Sahana Home</a>.</p>';
	
   }
}

/**
 * This function generates the CSS based on the custom values and echoes it.
 * It is called by lib_xhtml for generating CSS (print/mobile/screen)
 */
function shn_text_theme_gen_css(){
 
    global $global,$conf;
    $username = $_SESSION['user'];
	
	// if the theme is set to custom_theme
    if($conf['theme'] == 'custom_theme')
    {
	    $db = $global['db'];
	    $q = "SELECT * FROM theme_custom_values where username='$username'";
	    $res = $db->Execute($q);

		//if $res is not null, i.e. the user has stored his own preferences for custom_theme. 
		//Load those values.
		if (!$res->EOF && $res)
		{
			$row = $res->FetchRow();
			$css1 = $row['css1'];
			$css2 = $row['css2'];
			$css3 = $row['css3'];
			$css4 = $row['css4'];
			$css5 = $row['css5'];
			$css6 = $row['css6'];
			$css7 = $row['css7'];
			$css8 = $row['css8'];
			$css9 = $row['css9'];
			$logo = $username;
			$wants = $row['logo'];
			$parent = $row['parent'];
		}
		else
		{
			$adminname= $conf['root_name'];
			$q1 = "SELECT * FROM theme_custom_values where username='$adminname'";
			$res1 = $db->Execute($q1);
		
			//if $res1 is not null, i.e. the admin has stored preferences for custom_theme. 
			//Load those values.
			if (!$res1->EOF && $res1)
			{
				$row = $res1->FetchRow();
				$css1 = $row['css1'];
				$css2 = $row['css2'];
				$css3 = $row['css3'];
				$css4 = $row['css4'];
				$css5 = $row['css5'];
				$css6 = $row['css6'];
				$css7 = $row['css7'];
				$css8 = $row['css8'];
				$css9 = $row['css9'];
				$logo = $adminname;
				$wants = $row['logo'];
				$parent = $row['parent'];
			}
			
			// neither the user, nor the site admin have stored any preferences 
			// load default values in this case
			else
			{
				$css1 = '#fff';
				$css2 = '#fff';
				$css3 = '#000';
				$css4 = '#369';
				$css5 = '#369';
				$css6 = '#003366';
				$css7 = '#333333';
				$css8 = '#ffffff';
				$css9 = '#ffffff';
				$logo = 'default';
				$wants = False;
				$parent = 'default';
			}
		}

	    $type = $_REQUEST['type'];
	    if ($type == 'screen')
			$type = 'sahana';

	    header("Content-type: text/css");

	    //echo parent CSS 
	    $fn = $global['approot'].'/www/theme/'.$parent.'/'.$type.'.css';
	    $fh = fopen($fn, "r");

        while (!feof($fh)) {
	       	$line = fgets($fh);
			echo $line;
	    }
	    fclose($fh);
  
		// either default values are loaded
		// or admin/user's preferences are loaded but they have unchecked need for custom logo.
		// in both cases, use the default site logo
		if ($logo == 'default' || $wants == false)
			$url = 'theme/default/img/sahana_logo.png';
		
		// otherwise load the custom logo depending on whose preferences are loaded (user's or admin's)
		else 
		{
			$q = "select * from media where x_uuid = \"".$logo."\"";
			$res = $db->Execute($q);
			
			//if they have not uploaded any custom logo file, then use default logo
			if (!$res->EOF && $res)
			{
				$row = $res->FetchRow();
				$filename = $row['media_id'];
				$filename = $filename.".".$row['media_type'];
				$url = 'theme/custom_theme/logos/'.$filename;
			}
			else
				$url = 'theme/default/img/sahana_logo.png';
		}

	    //now echo custom values
	    echo 'div #home {border: 10px '.$css1.' solid; background-color: '.$css2.'; }';
	    echo 'body { font-size: 0.8em; color: '.$css3.'; background: #369; }';
	    echo 'div #header {background: url('.$url.') '.$css4.' no-repeat left top; } ';
	    echo 'div #footer {background-color: '.$css5.'; } ';
		echo 'form.head {background:'.$css4.';}';
		echo 'form.head select {background:'.$css4.';}';
		echo 'div#modmenuwrap ul li a {background: '.$css6.'; color: '.$css8.';}';
		echo 'div#modmenuwrap ul li a:hover {background: '.$css6.'; color: '.$css8.';}';
		echo 'div#menuwrap ul li a {background: '.$css7.'; color: '.$css9.';}';
		echo 'div#menuwrap ul li a:hover {background: '.$css7.'; color: '.$css9.';}';

    }
	
	// if the theme is not set to custom_theme, 
	// just echo whatever the css files of whatever theme is set
    else 
    {
	    $type = $_REQUEST['type'];
	    if ($type == 'screen')
			$type = 'sahana';
	
	    header("Content-type: text/css");

	    $fn = $global['approot'].'/www/theme/'.$conf['theme'].'/'.$type.'.css';
	    $fh = fopen($fn, "r");

        while (!feof($fh)) {
	       	$line = fgets($fh);
			echo $line;
	    }
	    fclose($fh);
    }

}

/**
 * This function saves the admin's preferences for which roles should be allowed
 * access to the custom_theme module.
 */
function shn_theme_save_permissions () {

    global $global, $conf;
	$db=$global['db'];
	$roles=array();

   	//get list of permissions
	$q="select * from sys_user_groups";	
	$res=$db->Execute($q);
	
	//empty table
	$q1 = "delete from sys_group_to_module where module=\"theme\" and group_id>1";
	$res1 = $db ->Execute($q1);
		
	//insert entries
	while(($res!=null) &&(!$res->EOF))
	{		
		$role_id = $res->fields["group_id"];
		if ($role_id!=1 && isset($_POST[$role_id]))
		{
			$q3 = "insert into sys_group_to_module values ($role_id, \"theme\", \"enabled\")";
			$res3 = $db ->Execute($q3);
		}
		$res->MoveNext();
	}
	echo '<h2>'._t('Your changes have been saved.').'</h2> <br />';
	echo '<br />';
	add_confirmation ('Congratulations! Your permissions have been saved.');
	
	//display link to go back to sahana home
	echo '<p>Go to <a href=\'index.php\'>Sahana Home</a>.</p>';
	echo '<p>Go to <a href=\'index.php?mod=theme&act=default\'>Custom Theme Home</a>.</p>';
	echo '<p>Go to <a href=\'index.php?mod=theme&act=adm_default\'>Permissions Page</a>.</p>';
	
}


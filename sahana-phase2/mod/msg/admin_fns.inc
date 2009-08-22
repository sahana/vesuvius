<?php
/**
* 
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Mifan Careem <mifan@respere.com>
* @copyright  Respere - http://respere.com/
* @package	  Sahana - http://sahana.lk/
* @subpackage msg
* @version 	  $Id: admin_fns.inc,v 1.5 2009-08-22 17:17:22 ravithb Exp $
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


function shn_msg_adm_default()
{
	global $global;
    global $conf;
    $module = $global['module'];
    
    //Admin plugin front-controller
	
	if(isset($_REQUEST['submod']) && isset($_REQUEST['seq'])){
		global $global;
		include_once ($global['approot'].'/mod/msg/plugins/'.$_REQUEST['submod'].'/admin.inc');
		switch($_REQUEST['seq']){
			case 'commit':
						shn_plugin_commit();
						break;
		}
		shn_msg_adm_show_mod_menu();
		echo "<h2>"._t("Messaging:SMS Admin Page")."</h2>";
		shn_msg_adm_show_mods();
		shn_msg_adm_find_mods();
	}
	else if(isset($_REQUEST['submod'])){
		global $global;
		shn_msg_adm_show_mod_menu();
		include_once ($global['approot'].'/mod/msg/plugins/'.$_REQUEST['submod'].'/admin.inc');
		shn_plugin_default();
	}
	else if(isset($_REQUEST['seq'])){
		switch($_REQUEST['seq']){
			case 'plugin_commit':
								_shn_msg_adm_store_plugin($_REQUEST['mod_msg']);
								break;
		}
	}
	
	else{
    	//General Messaging
    	shn_msg_adm_show_mod_menu();
		echo "<h2>"._lc($conf['mod_msg_name'])." "._t("Administraion")."</h2>";
		shn_msg_adm_plugin_conf();
		
	}
}


/**
 * Find and show Messaging plugin configuration links
 * Auto-detects plugins 
 * Uses same plugin architecture as in GIS subsystem
 * @access public
 * @return void
 */
function shn_msg_adm_find_mods()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
	shn_form_fopen(adm_gis_conf,null,array('req_message'=>false));
	shn_form_fsopen(_t("SMS Plugin Configuration"));
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			echo "$count.	<a href='index.php?mod=msg&act=admin&submod=$file'>"."$name"."</a><br>";
			$count++;
		}
	}
	shn_form_fsclose();
	shn_form_fclose();	
}

/**
 * Find and allow of selection of messaging plugin
 * @access public
 * @return void
 */
function shn_msg_adm_plugin_conf()
{
	global $global;
	global $conf;
	$db=$global['db'];
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	
	$query_mod="select value from config where module_id='msg' and confkey='plugin'";
	$result=$db->Execute($query_mod);
	if(!$res->EOF){
		$mod_name=$result->fields['value'];
	}
	
	
	
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
	while($file = readdir($dir)){
		if(!is_dir($file)){
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
			$options_array[$file] = $name;
		}
	}
	$extra_opts_form['req_message'] = 'false';
	
	shn_form_fopen(msg_plugin_commit,null,array('req_message'=>false));
	shn_form_fsopen(_t("Messaging Module SMS Gateway plugins"));
?>
	<ul>
	<li><?php echo _t("Sahana supports a modular messaging SMS gateway plugin architecture ");?> </li>
	<li><?php echo _t("You can select which SMS gateway to use as your default");?></li>
    <li><?php echo _t("Select the default SMS gateway plugin from the detected plugins below:");?> </li>
    <li><?php echo _t("For more information on adding custom plugins, refer to the documentation within the mod/msg subdirectory");?> </li>
	</ul>
<?php
	shn_form_fsclose();
	//shn_form_hidden('req');
	shn_form_fsopen(_t("Detected messaging module SMS plugins"));
	$mod_name = $conf['mod_msg_plugin'];
    shn_form_radio($options_array,_t("Select Messaging SMS plugin"),"mod_msg",null,((isset($mod_name))?array("value"=>$mod_name):null));
	shn_form_fsclose();
	shn_form_submit(_t("Done"));
	shn_form_fclose();	
}

/**
 * Find and show message plugin configuration links at top
 * Auto-detects plugins 
 * @access public
 * @return void
 */
function shn_msg_adm_show_mod_menu()
{
?>
<?php
	global $global;
	global $conf;
	include_once($global['approot'].'/inc/lib_modules.inc');
	include_once($global['approot'].'/inc/lib_form.inc');
	$count=1;
	$msg_plugins_dir=$global['approot'].'/mod/msg/plugins/';
	$dir = opendir($msg_plugins_dir);
?>
	<div id="submenu_v">
		<a href="index.php?mod=admin&act=msg_sms_plugin"><?php echo _t("General Description")?></a>
<?php
	while($file = readdir($dir)){
		if(!is_dir($file)){
			//shows nice name of plugin
			include($global['approot'].'/mod/msg/plugins/'."$file".'/conf.inc');
			$name = $conf['plugin_name'];
?>
<!--<a href="index.php?mod=msg&act=admin&submod=<?php echo $file?>"><?php echo _t($name)?></a>-->
<a href="index.php?mod=admin&act=msg_sms_plugin&submod=<?php echo $file?>"><?php echo _t($name)?></a>
<?php
			$count++;
		}
	}
?>
	</div><!--/div id=submenu_v-->
<?php
}

/**
 * Email SMTP administation
 */
function _shn_msg_adm_email_conf()
{
	global $global;
	include_once($global['approot'].'/inc/lib_validate.inc');
	
	_shn_msg_adm_email_conf_db($_REQUEST['host'],'smtp_host');
	_shn_msg_adm_email_conf_db($_REQUEST['port'],'smtp_port');
	_shn_msg_adm_email_conf_db($_REQUEST['username'],'smtp_user');
	_shn_msg_adm_email_conf_db($_REQUEST['pass'],'smtp_pass');
	_shn_msg_adm_email_conf_db($_REQUEST['name'],'smtp_sender_name');
	_shn_msg_adm_email_conf_db($_REQUEST['mail_id'],'smtp_sender_email');
	
	add_confirmation(_t('Email Configuration Saved'));
	
}

function _shn_msg_adm_email_conf_db($value,$conf_key_val)
{
	if($value!=null){
		global $global;
		$db = $global['db'];
		$conf_key = 'mod_msg_'.$conf_key_val;
		$check_sql = "SELECT * FROM config WHERE confkey='{$conf_key}'";
		$result=$check_sql;
		if($result->EOF){
			//Insert
			$sql = "INSERT INTO config (module_id,confkey,value) VALUES ('msg','{$conf_key}','{$value}')";	
		}
		else{
			//Update
			$sql = "UPDATE config SET value='{$value}' where confkey='$conf_key'";
		}
		
		$db->Execute($sql);
	}
}

/**
 * Store plugin option
 * @todo handle update
 */
function _shn_msg_adm_store_plugin($plugin)
{
	global $global;
	$db = $global['db'];
	
	$sql = "INSERT INTO config(module_id,confkey,value) " .
			" VALUES ('msg','mod_msg_plugin','{$plugin}')";
	$db->Execute($sql);
	add_confirmation(_t('Configuration Saved'));
}



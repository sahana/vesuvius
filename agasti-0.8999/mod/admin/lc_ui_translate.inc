<?php
/**
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage localization
* @package    Sahana - http://sahana.sourceforge.net
* @author     Prabath Kumarasinghe<prabath321@gmail.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

function _shn_admin_set_locale()
{
	global $global;
	include_once $global['approot']."/inc/lib_locale/lib_locale.inc";
	$lc_list = _shn_get_lang_list();
	shn_form_fopen("lc_ui_trns",null,array('req_message'=>false));
    shn_form_fsopen(_t("Interactive Translation"));
    $locale = $_SESSION["locale"];
    shn_form_select($lc_list,_t("Please select language: "),"locale",'',array('value'=>"$locale"));
    shn_form_submit(_t("Set Locale"));
    shn_form_fclose();
}

function _shn_admin_lc_set_ui_translate()
{
	shn_form_fopen("lc_ui_trns_enable",null,array('req_message'=>false));
	shn_form_fsclose();
	//echo 'LOCALE = '.$_SESSION["locale"];
?>
    <h2><?php echo _t("Interactive Translation")?></h2>
        <p><?php echo _t("This interface allows a user to translate Sahana into their mother tongue through the user interface. Please follow the instructions below.")?></p>
	<ul>
	<li><b><?php echo _("Setp 1 : ")?></b> <br/><?php echo _("First of all please give file and directory permissions to sahana/res folder");?></li>
	<li><b><?php echo _("Setp 2 : ")?></b> <br/><?php echo _("When you press the 'Enable Localization' button then you enter a localization mode, afterwards when you right click on any word phrase in the user interface you'll get a prompt box into which you can type the required translation and press ok")?></li>
	<li><b><?php echo _("Step 3 : ")?></b> <br/><?php echo _("When you finish translation, please go to Administration->Language/Locale->Update Translation")?></li>
	<li><b><?php echo _("Step 4 : ")?></b> <br/><?php echo _("Finally press update button")?></li>
	<li><b><?php echo _("Step 5 : ")?></b> <br/><?php echo _("Afterwards go to Administration->Language/Locale->setLocale and set the particular locale")?></li>
	</ul>
    </div>

<?php
    shn_form_fsclose();
    shn_form_submit(_t("Enable Localization"),"name=lc");
    shn_form_submit(_t("Disable Localization"),"name=lc_dis");
    //shn_form_submit(_t("Update"),"name='lc_update'");
    //shn_form_submit(_t("Compile"));
    shn_form_fclose();
}

function _shn_admin_lc_ui_trns_enable()
{
	$_SESSION['admin']['locale']['enable'] = "set";
	$locale = $_SESSION["locale"];
	$file_name = "../res/locale/$locale/LC_MESSAGES/sahana.po";

	if(!file_exists($file_name)) {
		$return = array();
        $cmd = 'xgettext --keyword=__ --keyword=_e ' .
        '--keyword=_t  --default-domain=sahana ' .
        '--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .
        '--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana.po';
        ///_shn_admin_lc_load('../res/locale/' . $locale. '/LC_MESSAGES/sahana.po');
        system($cmd, &$return);
        $cmd = 'xgettext --keyword=__ --keyword=_e ' .
        '--keyword=_t  --default-domain=sahana ' .
        '--language=php ../*/*/*.inc ../*/*.inc ../*/*/*/*/*.inc ' .
        '--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po';
        system($cmd, &$return);
	}
	add_confirmation("Localization mode enable succesfully, please refresh your browser and Please right click on word phrases. ");
	//$_SESSION['admin']['locale']['enable_first'] = "set";
	//echo $_SESSION['admin']['locale']['enable'];
}

function _shn_admin_lc_ui_trns_disable()
{
	add_confirmation("Localization mode disable Ssuccesfully, please refresh your browser ");
	$_SESSION['admin']['locale']['enable'] = "reset";
	//$_SESSION['admin']['locale']['enable_first'] = "reset";
	//echo $_SESSION['admin']['locale']['enable'];
}

function _shn_admin_lc_ui_trns_update()
{
	$cmd = "mv -v -f sahana_test.po sahana.po";
	//echo exec("");
	//echo $return_value;
	echo "<h2>"._t("Sahana translation succesfully updated")."</h2>";
}
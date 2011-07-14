<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */



function _shn_admin_set_locale() {
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



function _shn_admin_lc_set_ui_translate() {
	shn_form_fopen("lc_ui_trns_enable",null,array('req_message'=>false));
	shn_form_fsclose();
	?>
	<h2><?php echo _t("Interactive Translation")?></h2>
		<p><?php echo _t("This interface allows a user to translate Sahana into their mother tongue through the user interface. Please follow the instructions below.")?></p>
		<ul>
		<li><b><?php echo _("Setp 1 : ")?></b> <br/><?php echo _("First of all please give file and directory permissions to sahana/res folder");?></li>
		<li><b><?php echo _("Setp 2 : ")?></b> <br/><?php echo _("When you press the 'Enable Localization' button then you enter a localization mode, afterwards when you right click on any word phrase in the user interface you'll get a prompt box into which you can type the required translation and press OK")?></li>
		<li><b><?php echo _("Step 3 : ")?></b> <br/><?php echo _("When you finish translation, please go to Administration->Language/Locale->Update Translation")?></li>
		<li><b><?php echo _("Step 4 : ")?></b> <br/><?php echo _("Finally press update button")?></li>
		<li><b><?php echo _("Step 5 : ")?></b> <br/><?php echo _("Afterwards go to Administration->Language/Locale->setLocale and set the particular locale")?></li>
		</ul>
	</div>

	<?php
	shn_form_fsclose();
	shn_form_submit(_t("Enable Localization"),"name=lc");
	shn_form_submit(_t("Disable Localization"),"name=lc_dis");
	shn_form_fclose();
}



function _shn_admin_lc_ui_trns_enable() {
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
	add_confirmation("Localization mode enabled succesfully, please refresh your browser and please right-click on word phrases. ");
}



function _shn_admin_lc_ui_trns_disable() {
	add_confirmation("Localization mode disabled succesfully, please refresh your browser ");
	$_SESSION['admin']['locale']['enable'] = "reset";
}



function _shn_admin_lc_ui_trns_update() {
	$cmd = "mv -v -f sahana_test.po sahana.po";
	echo "<h2>"._t("Sahana translation succesfully updated")."</h2>";
}


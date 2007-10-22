<?php
/**
*
* PHP version 4 and 5
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
	shn_form_fopen("lc_ui_trns");
    shn_form_fsopen(_("User Interface Language Translation"));
    $locale = $_SESSION["locale"];
    shn_form_select($lc_list,"Please select language: ","locale",'',array('value'=>"$locale"));
    shn_form_submit(_("Set Locale"));
    shn_form_fclose();	
}

function _shn_admin_lc_set_ui_translate()
{	
	shn_form_fopen("lc_ui_trns_enable");
	shn_form_fsclose();
	echo 'LOCALE = '.$_SESSION["locale"];
?>
    <h2><?=_("Sahana User Interface Language Translation")?></h2>
        <p><?=_("This interface allow user to transalte Sahana into their mother tongue though user interface, Please follow below instructions")?></p>
	<ul>
	<li><b><?=_("Setp 1 : ")?></b> <br/><?=_("Please click on localization button then your are entering to localization mode, afterwards when you right click on any word phrase in the user interface you get promt box please type required translate on it and press ok")?></li>
	<li><b><?=_("Step 2 : ")?></b> <br/><?=_("After translation done please press update buttton below")?></li>
	<li><b><?=_("Step 3 : ")?></b> <br/><?=_("Finally press compile button")?></li>
	<li><b><?=_("Step 4 : ")?></b> <br/><?=_("Afterward go to Administration->Localization->setLocale and set to particular locale")?></li>
	</ul>
    </div>

<?php
    shn_form_fsclose();
    shn_form_submit(_("Enable Localization"),"name=lc");
    shn_form_submit(_("Disable Localization"),"name=lc_dis");
    //shn_form_submit(_("Update"),"name='lc_update'");
    //shn_form_submit(_("Compile"));
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
        '--keyword=_p  --default-domain=sahana ' .
        '--language=php ../*/*/*.inc ' .
        '--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana.po';
        ///_shn_admin_lc_load('../res/locale/' . $locale. '/LC_MESSAGES/sahana.po');
        system($cmd, &$return);  
        $cmd = 'xgettext --keyword=__ --keyword=_e ' .
        '--keyword=_p  --default-domain=sahana ' .
        '--language=php ../*/*/*.inc ' .
        '--output=../res/locale/' . $locale. '/LC_MESSAGES/sahana_temp.po';
        system($cmd, &$return);        	
	}		
	add_confirmation("Localization Mode Enable Succesfully, First refersh your browser and Please right click on word phrases. ");
	//$_SESSION['admin']['locale']['enable_first'] = "set";
	//echo $_SESSION['admin']['locale']['enable'];
}

function _shn_admin_lc_ui_trns_disable()
{
	add_confirmation("Localization Mode Disable Succesfully, Please refersh your browser ");
	$_SESSION['admin']['locale']['enable'] = "reset";
	//$_SESSION['admin']['locale']['enable_first'] = "reset";
	//echo $_SESSION['admin']['locale']['enable'];
}

function _shn_admin_lc_ui_trns_update()
{
	$cmd = "mv -v -f sahana_test.po sahana.po";
	//echo exec("");
	//echo $return_value; 
	echo "<h2>Sahana Translation Succesfully Updated</h2>";	
}
	


?>
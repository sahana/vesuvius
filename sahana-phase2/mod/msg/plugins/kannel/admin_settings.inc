<?php
/**
* The Sahana Messaging Module
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Sriganeshan<sri@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	messaging
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

    global $global;
    include_once($global['approot'].'/inc/lib_modules.inc');
    include_once($global['approot'].'/inc/lib_form.inc');
    include_once($global['approot'].'/inc/lib_validate.inc');
    include_once($global['approot'].'/mod/msg/conf.inc');
    require_once $global['approot']."/inc/handler_db.inc";
    require_once $global['approot']."/inc/lib_config.inc";

function _shn_kannel_config_setfile()
{
    
    $mod = 'msg';
    $act = 'adm_set';
    print '<h2>' . _t("Kannel Configuration") .'</h2>';
    global $conf;
    copy($conf['input_file'],$conf['output_file']);

    $form_opts['name']="Kanne_settings";
    $form_opts['req_message']=true;
    shn_form_fopen($act,$msg,$form_opts);
 
    $help_device_port = _t("The port to which the modem or phone is connected to, in a computer through a data cable").'<br />'._t("eg: if connected to USB port the device port value should be").' /dev/ttyUSB0.<br/>'._t("This should be visible when you type")." 'dmesg | tail' "._t("on the terminal, after connecting the device to a computer");

    $help_id = _t("The model number of the phone or modem").'<br/>'._t("eg: if the phone is SonyEriccson k700i, then the model number is 700.");

    shn_form_fsopen(_t("Kannel Settings"));
?>
    <ul>
	<li><?php echo _t("Kannel is the sms gateway used in the messaging module to send sms");?>
        </li>
	<li><?php echo _t("kannel can be downloaded from ")."<a href='http://kannel.org/download.shtml' target=_blank>"."www"."."."kannel"."."."org/download"."."."shtml"."</a><br>";?> 
        </li>
        <li><?php echo _t("In order to configure kannel the following configuration values should be given");?>
        </li>
    </ul>
<?php    
    shn_form_fsclose();
    shn_form_fsopen(_t("Phone/Modem Settings"));
    shn_form_text(_t("Interface"),'interface',null,array('req'=>true,'help'=>$help_device_port));
    shn_form_text(_t("Model number"),'model_no',null,array('req'=>true,'help'=>$help_id));
    shn_form_fsclose();

    shn_form_submit(_t('Save'));
    shn_form_fclose();
}

function shn_msg_validate_settings()
{
    global $global;
    $error_flag=false;

    $conf['device']=trim($_POST['interface']);
    $conf['id']=trim($_POST['model_no']);
   
        if( $conf['device']=='')
         {
           add_error(_t("Please enter the interface"));
           $error_flag=true;
         }
        else if(preg_match('/^[0-9._, ]*$/', $conf['device']))
         {
           add_error(_t("Please enter a valid interface"));
           $error_flag=true;
         }
        else
         {
          ;
         }
        if($conf['id']=='')
         {
           add_error(_t("Please enter the model number"));
           $error_flag=true;
         }
        if(!preg_match('/^[0-9]*$/', $con['id']))
         {
           add_error(_t("Please enter a valid model number"));
           $error_flag=true;
         }
     return $error_flag;

}//end of function shn_msg_validate_settings()
     
function _shn_kannel_config_savefile()
{
    global $conf;

    $mod='msg';
    $interface='interface';
    $id='id';
 
    $conf['device']=trim($_POST['interface']);
    $conf['id']=trim($_POST['model_no']);

    shn_db_config_update($mod,$interface,$conf['device']);
    shn_db_config_update($mod,$id,$conf['id']);
    $array['device']=shn_db_get_config($mod,$interface);
    $array['id']=shn_db_get_config($mod,$id);
    $array['detect-string']=shn_db_get_config($mod,$id);
    $out="../msg/kannel.conf";
    $in="../msg/kannel.con";
    shn_config_file_update_new($array,$conf['input_file'],$conf['output_file']);
    _shn_kannel_operation_file();
}

function _shn_kannel_operation_file()
{
    print '<h2>' . _t("Kannel Operations") .'</h2>';
    add_confirmation(_t("your settings were saved.<br/>Copy the configuration file kannel.conf in /tmp/ to /etc/kannel/ and convert it into an executable file and proceed with Kannel Operations"));
 
    $form_opts['name']="Kannel_operations";
    $form_opts['req_message']=false;
    shn_form_fopen(null,null,$form_opts);
    shn_form_fsopen(_t("Starting Kannel"));

?>
	<ul>
	<li><?php echo _t("Make sure you have copied the configuration file kannel.conf to /etc/kannel");?> </li>
	<li><?php echo _t("Open a terminal and, as the root user, type the commands:");?> </li>
	<ul>
	<li><?php echo '<b>'."cd /etc/kannel".'</b>' ;?></li>
	<li><?php echo '<b>'."bearerbox kannel.conf".'</b>' ;?></li>
	</ul>
	<li><?php echo _t("Open a 2nd terminal and, as the root user, type the commands:");?> </li>
	<ul>
	<li><?php echo '<b>'."cd /etc/kannel".'</b>' ;?></li>
	<li><?php echo '<b>'."smsbox kannel.conf".'</b>' ;?></li>
	</ul>
	</ul>
	<ul>
	<li><?php echo _t("On successful configuration Kannel should output in the 1st terminal: ").'<b>'._t(" AT SMSC successfully opened").'</b>'."";?></li>
	<li><?php echo _t("If not re-check and re-enter your configuration values");?></li>
	</ul>
<?php
    shn_form_fsclose();
    print "<br/>";
    shn_form_fsopen(_t("Shutting down Kannel"));
?>
    <ul>
	<li><?php echo _t("Press ").'<b>'."CTRL + C".'</b>'._t(" on both the terminals");?></li>
    </ul><br/>
<?php  
    shn_form_fsclose(); 
    shn_form_fclose();
}  

function shn_config_file_update_new($modify, $config_file, $output_file)
{
    global $global;
    $fh_c = fopen($config_file,'r');
    if (!( $fh_t = fopen($output_file,'w') ))
        return false; // if unable to open the file for write

    while (! feof ($fh_c) )
    {
        $line = fgets($fh_c,1024);
	$match = false;
        // iterate through the list of possible replacements in the line
        foreach ($modify as $search => $replace )
        {
            if (preg_match('/'.$search.'/',$line))
            {
                $match = true;
		if($search=='device')
                fputs($fh_t,$search." = ".$replace."\n");
		else
		fputs($fh_t,$search." = "."\"".$replace."\""."\n");
            }
        }
        if (!$match) // if no match was found output the default line
            fputs($fh_t, $line);
    }
    fclose($fh_c);
    fclose($fh_t);
    return true;
}

?>


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
* @subpackage	rms
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
    print '<h2>' . _("Kannel Configurations & SMTP Settings") .'</h2>';
    global $conf;
    copy($conf['input_file'],$conf['output_file']);

    $form_opts['name']="Kanne_settings";
    $form_opts['req_message']=true;
    shn_form_fopen($act,$msg,$form_opts);
 
    $help_device_port = _("The port to which the modem or phone is connected to, in a computer   through a data cable<br /> eg:- if connected to USB port the device port value should be /dev/ttyUSB0.<br/> This should be visible when you type 'dmesg | tail' on the terminal, after connecting the device to a computer");

    $help_id = _("The model number of the phone or modem<br/>eg:-if the phone is SonyEriccson k700i,then the model number is 700.");

    shn_form_fsopen(_("Kannel Settings"));
?>
    <ul>
	<li><?php echo _("Kannel is the sms gateway used in the messaging module to send sms");?>
        </li>
	<li><?php echo _("kannel can be downloaded from ")."<a href='http://kannel.org/download.shtml'>"."www"."."."kannel"."."."org/download"."."."shtml"."</a><br>";?> 
        </li>
        <li><?php echo _("In order to configure kannel the following configuration values should be given");?>
        </li>
    </ul>
<?php    
        shn_form_fsclose();
        shn_form_fsopen(_("Phone/Modem Settings"));
	shn_form_text(_("Interface"),'interface',null,array('req'=>true,'help'=>$help_device_port));
        shn_form_text(_("Model number"),'model_no',null,array('req'=>true,'help'=>$help_id));
        shn_form_fsclose();
	
        shn_form_fsopen(_("SMTP SERVER/E-MAIL SETTINGS"));
        shn_form_text(_("SMTP host name"),'host',null,array('req'=>true));
        shn_form_text(_("SMTP Username"),'username',null,array('req'=>true));
        shn_form_password(_("SMTP Password"),'password',null,array('req'=>true));
        shn_form_text(_("Sender name"),'name',null,array('req'=>true));
        shn_form_text(_("Sender mail ID"),'mail_id',null,array('req'=>true));
        shn_form_fsclose();
        shn_form_submit(_('Save'));
        shn_form_fclose();
}

function shn_msg_validate_settings(){

        global $global;
        $error_flag=false;

        $conf['device']=trim($_POST['interface']);
        $conf['id']=trim($_POST['model_no']);
        $smtp_server=trim($_POST['host']);
        $smtp_username=trim($_POST['username']);
        $smtp_password=trim($_POST['password']);
        $sender_name=trim($_POST['name']);
        $sender_id=trim($_POST['mail_id']);
   
        if( $conf['device']=='')
         {
           add_error(_("Please enter the interface"));
           $error_flag=true;
         }
        else if(preg_match('/^[0-9._, ]*$/', $conf['device']))
         {
           add_error(_("Please enter a valid interface"));
           $error_flag=true;
         }
        else
         {
          ;
         }
        if($conf['id']=='')
         {
           add_error(_("Please enter the model number"));
           $error_flag=true;
         }
        if(!preg_match('/^[0-9]*$/', $con['id']))
         {
           add_error(_("Please enter a valid model number"));
           $error_flag=true;
         }
        if($smtp_username=='' || $smtp_password=='')
         {
           add_error(_("Please enter a valid username and password"));
	   $error_flag=true;
         }
        if($smtp_server=='' || !preg_match('/^[a-z.]*$/',$smtp_server))
         { 
           add_error(_("Please enter a valid SMTP server name"));
           $error_flag=true;
         }
        if($sender_name=='' || $sender_id=='')
         {
           add_error(_("Please enter Sender name and Sender mail ID"));
           $error_flag=true;
         }
        if(!shn_valid_email($sender_id))
         {
           add_error(_("Please enter valid Sender mail ID"));
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
        $server='server';
        $usrname='username';
        $password='password';
        $from_name='from_name';
        $from_id='from_id';
 
        
        $conf['device']=trim($_POST['interface']);
        $conf['id']=trim($_POST['model_no']);
        $smtp_server=trim($_POST['host']);
        $smtp_username=trim($_POST['username']);
        $smtp_password=trim($_POST['password']);
        $sender_name=trim($_POST['name']);
        $sender_id=trim($_POST['mail_id']);

        shn_db_config_update($mod,$interface,$conf['device']);
	shn_db_config_update($mod,$id,$conf['id']);
        shn_db_config_update($mod,$server,$smtp_server);
	shn_db_config_update($mod,$usrname,$smtp_username);
	shn_db_config_update($mod,$password,$smtp_password);
	shn_db_config_update($mod,$from_name,$sender_name);
	shn_db_config_update($mod,$from_id,$sender_id);
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
    print '<h2>' . _("Kannel Operations") .'</h2>';
    add_confirmation(_("your settings were saved.<br/>Copy the configuration file kannel.conf in /tmp/ to /etc/kannel/ and convert it into an executable file and proceed with Kannel Operations"));
 
    $form_opts['name']="Kannel_operations";
    $form_opts['req_message']=false;
    shn_form_fopen(null,null,$form_opts);
    shn_form_fsopen(_("Starting Kannel"));

?>
	<ul>
	<li><?php echo _("Make sure you have copied the configuration file kannel.conf to /etc/kannel");?> </li>
	<li><?php echo _("Open a terminal and, as the root user, type the commands:");?> </li>
	<ul>
	<li><?php echo '<b>'."cd /etc/kannel".'</b>' ;?></li>
	<li><?php echo '<b>'."bearerbox kannel.conf".'</b>' ;?></li>
	</ul>
	<li><?php echo _("Open a 2nd terminal and, as the root user, type the commands:");?> </li>
	<ul>
	<li><?php echo '<b>'."cd /etc/kannel".'</b>' ;?></li>
	<li><?php echo '<b>'."smsbox kannel.conf".'</b>' ;?></li>
	</ul>
	</ul>
	<ul>
	<li><?php echo _("On successful configuration Kannel should output in the 1st terminal: ").'<b>'._(" AT SMSC successfully opened").'</b>'."";?></li>
	<li><?php echo _("If not re-check and re-enter your configuration values");?></li>
	</ul>
<?php
    shn_form_fsclose();
    print "<br/>";
    shn_form_fsopen(_("Shutting down Kannel"));
?>
    <ul>
	<li><?php echo _("Press ").'<b>'."CTRL + C".'</b>'._(" on both the terminals");?></li>
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

 	  	 

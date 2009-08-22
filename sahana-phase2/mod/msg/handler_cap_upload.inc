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
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/


print '<h2>' . _t("CAP file upload") . '</h2>';

switch ($_REQUEST['seq'])
{
    case '' :
        _shn_cap_upload_getfile();
        break;

    case 'cap_upload':
               _shn_cap_upload_savefile();
               break;
}

function _shn_cap_upload_getfile()
{
    $mod = 'msg';
    $act = 'cap_upload';
?>
    <div class="form-container">
    <form  id='formset' enctype="multipart/form-data" action="index.php?mod=<?php echo $mod?>&act=<?php echo $act?>" method="POST">
    <fieldset>
    <legend>Message Upload</legend>
    <input type="hidden" name="MAX_FILE_SIZE" value="1000000" />
    Choose a file : <input name="up_file" type="file" /><br />
    </fieldset>
<?php
    shn_form_hidden(array('seq'=>'cap_upload'));
    shn_form_fsopen(_t("Save as"));
    shn_form_radio(array('msg'=>_t("Messages"),'tpl'=>_t("Template")),'','type',null,array('value'=>'msg'));
    shn_form_fsclose();
?>
    <input type="submit" value="Upload CAP Message" />
    </form>
    </div>
<?php

}

function _shn_cap_upload_savefile()
{
    $MSG_DIR = '../res/msg';
    
    switch ($_POST['type'])
    {
        case 'msg': $file_path = $MSG_DIR.'/cap/messages/';
                    break;
        case 'tpl': $file_path = $MSG_DIR.'/cap/templates/';
                    break;
    }
    
    $file_name = $file_path . basename( $_FILES['up_file']['name']);
    
    if(move_uploaded_file($_FILES['up_file']['tmp_name'], $file_name))
    {
        $str = "The file : ". $_FILES['up_file']['name'] . " has been uploaded";
        _shn_html_print_message($str);
        _shn_cap_upload_getfile();
    }
    else
    {
        add_error(_t("Error Uploading the file"));
        display_errors();
        _shn_cap_upload_getfile();
    }
}



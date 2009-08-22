<?php
/**
 * Dump File Upload Handler 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
$file=$_FILES['file_dump'];
//allowed upload file extention list 
$extentions=array('xml','gz','bz2');

//check weather a file was uploaed
if(isset($file)){
    //get the extention and the tmp name of the file
    $ext=end(explode('.',$_FILES['file_dump']['name']));
    $_SESSION['sync']['file']="./tmp/".basename($_FILES['file_dump']['name']);
    //check for tmp file permision
    if(!is_writable('./tmp')){
        add_error(_t('Make sure the tmp folder is writerble'));
    }
    //check weather an error occored
    else if($file['error']!= 0){
        //give error information
        switch ($file['error']){
            case 1:
            case 2:
                add_error(_t('The uploaded file exceeds the MAX upload size'));
                break;
            case 3:
                add_error(_t('The uploaded file was only partially uploaded.'));
                break;
            case 4:
                add_error(_t('No file was uploaded :  Please press the browse button and select a file to upload before you press the next button'));
                break;
        }
    }
    //check for extention
    else if(!in_array($ext,$extentions)){
        add_error("<b>".strtoupper($ext)."</b> : "._t("Extention is not a valied Sahana dump file extention."));
    }
    //move the uploaded file to the tmp directory
    else if (move_uploaded_file($_FILES['file_dump']['tmp_name'],$_SESSION['sync']['file']))
    {
        _shn_sync_file_details();
        return;
    }
    else{
        add_error(_t('Possible file upload attack!'));
    }
}
echo "<h2>"._t('Upload File')."</h2>";
//Print the error message If an error occord with the Upload File
display_errors($return=false,$clean_errors=true,$exit=false);
//draw upload form
_shn_sync_upload_form();



//Upload Data Dump Form
function _shn_sync_upload_form(){
    shn_form_fopen("upload&amp",null,array('enctype'=>'enctype="multipart/form-data"'));
    shn_form_fsopen(_t('Upload Sahana Dump File'));
    echo '<p>'._t('Upload a data file you want to import. ')."<em><strong>"._t('important: ')."</strong></em>"._t('This system will only accept data files which have been exported by Sahana Instances.')."</p>";
    shn_form_upload(_t('File'),'file_dump');
    shn_form_fsclose();
    shn_form_submit(_t('Next'));
    shn_form_fclose();
}

//this function print file details and sync form
function _shn_sync_file_details(){
    //calculate the file creation date
    $name=explode('.',$_FILES['file_dump']['name']);
    $name=$name[0];
    $time=(int)substr($name, -10, 10);
    $ins=substr($name, -15, 4);

    $_SESSION['fileinfo']=$_FILES['file_dump'];

    echo "<h2>"._t('Import File')."</h2>";
    add_confirmation(_t('The information about the uploaded file are given bellow.'));
    display_submit_message('confirmation',_t('The file was uploaded successfully...'));
?>
    <center>
    <br />
    <table>
    <thead><td colspan="2"><?php echo _t('Upload File Info')?></td></thead>
    <tr><td><?php echo _t('Name')?> </td><td><?php echo $_FILES['file_dump']['name']?></td></tr>
    <tr><td><?php echo _t('Type')?> </td><td><?php echo $_FILES['file_dump']['type']?></td></tr>
    <tr><td><?php echo _t('Size')?> </td><td><?php echo ((int)$_FILES['file_dump']['size']/1000).' kb'?></td></tr>
    <tr><td colspan="2"></td></tr>
    <tr><td><?php echo _t('Time Created')?></td><td><?php echo date("F j, Y, g:i a",$time)?></td></tr>
    <tr><td><?php echo _t('Dump Instance')?></td><td><?php echo $ins?></td></tr>
    </table >
    </center>
    <br />
<?php
    shn_form_fopen('synchronize',NULL,array('req_message'=>false));
    echo "<center>";
    echo "<a href=\"#\" onclick=\"document.getElementById('adv_opt').style.display='block';\">"._t('Advance Options')."</a>";
    shn_form_submit(_t('Import'));
    echo "</center>";
    echo "<div id='adv_opt' style='display:none'>";
    shn_form_fsopen(_t('Advance Options'));
//     $options=array('0'=>'0','1'=>'1','2'=>'2');
//     shn_form_select($options,_t('Threshold'), 'threshold');
    $options=array('yes'=>_t('Yes'),'no'=>_t('No'));
    shn_form_select($options,_t('Overwrite existing data'),'oed');
    shn_form_fsclose();
    echo "</div>";
    shn_form_fclose();
}

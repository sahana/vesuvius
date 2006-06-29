<?php
/* $Id: add.inc,v 1.5 2006-06-29 06:32:00 thushari Exp $ */
/* last modify : 2006/03/31 */

/**
 * Data Import upload file 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
global $global;

require_once($global['approot'].'mod/imp/contact/bao/contact.inc');
require_once($global['approot'].'mod/imp/parser_contact.inc');

require_once($global['approot'].'mod/imp/mapfield.inc');

/**
*
*This is upload_file Class contains file upload functins
*
*/

class Upload_Files { 
    
    var $ext_array;
    var $temp_file_name; 
    var $file_name; 
    var $upload_dir; 
    

    /* {{{CSV file add Form */
/**
 * This validates the file type
 * 
 * @access public
 * @return void
 */
   
function shn_imp_imp_per_validate_extension() { 
  
    $file_name = trim($this->file_name); 
    $extension = strtolower(strrchr($file_name,".")); 
    $ext_array = $this->ext_array; 
    $ext_count = count($ext_array); 
    
    if (!$file_name) { 
        return false; 
    } else { 
        if (!$ext_array) { 
            return true; 
        } else { 
            foreach ($ext_array as $value) { 
                $first_char = substr($value,0,1); 
                    if ($first_char <> ".") { 
                        $extensions[] = ".".strtolower($value); 
                    } else { 
                        $extensions[] = strtolower($value); 
                    } 
            } 

             
            foreach ($extensions as $value) { 
                if ($value == $extension) { 
                    $valid_extension = "TRUE"; 
                }                 
            } 

             
            if ($valid_extension) { 
                return true; 
            } else { 
                return false; 
            } 
        } 
    } 
} //end of the extension validate function

/* }}} */
}

/**
* This is the end of class
*
*/


/* {{{CSV file add Form */
/**
 * This displays the file upload form
 * 
 * @access public
 * @return void
 */
function shn_imp_imp_per_upload($errors=false) 
{
global $global;
   if($errors)
        display_errors();

	shn_form_fopen("imp_per",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_file'));
    shn_form_fsopen(_('Upload File'));
    shn_form_upload(_('Upload File'),"uploadfile");
    shn_form_fsclose();
echo '<p> Upload file should be in CSV format </p>'; 

    shn_form_fsopen(_('File Header Information'));
    shn_form_checkbox(_('First row contains column haders'),"skipcolumnheader",'skip',array('req'=> false));
    shn_form_fsclose();

    shn_form_fsopen(_('Content Information')); 
     shn_js_toggle_layer();
      /* To be discussed */
     shn_form_select(array("INDIVIDUAL"=>_('Individual'),"ORGANIZATION"=>_('Organization'),"CAMPS"=>_('Camps')),
            'Content Type',
            "contacttype",
            'onchange="toggle();" onload="toggle();" id="contacttype"');
   

 ?>
<div id="options">


<?php
    
 shn_form_radio(array('Decease','Victims','Volunteer'),_('Type of Individuals'),"Individualtype",'decease',array('req'=>false)); 
?>
</div>
<?php 
    shn_form_fsclose();
    shn_form_submit(_('Continue'));
    shn_form_fclose();
}
/* }}} */



/* {{{XML file add Form */
/**
 * This displays the file upload form
 * 
 * @access public
 * @return void
 */
function shn_imp_imp_xml_upload($errors=false) 
{
global $global;
   if($errors)
        display_errors();

	shn_form_fopen("imp_xml",null,array('enctype'=>'enctype="multipart/form-data"'));

    shn_form_hidden(array('seq'=>'upload_file'));
    shn_form_fsopen(_('Upload File'));
    shn_form_upload(_('Upload File'),"uploadfile");
    shn_form_fsclose();
echo '<p> Upload file should be a XML one </p>'; 

    //shn_form_fsclose();
    shn_form_submit(_('Continue'));
    shn_form_fclose();
}
/* }}} */

/* {{{CSV file add Form validate */
/**
 * This validates the entry of upload form
 * 
 * @access public
 * @return void
 */
function shn_imp_imp_per_upload_form_valid(){

global $global;

$error_flag = false; 

   if($_FILES['uploadfile']['error']==UPLOAD_ERR_NO_FILE){ 
   add_error(_("please enter a valid file")); 
    $error_flag = true;
     }
     
   else {
	$upload_class = new Upload_Files; 
	$upload_class->temp_file_name = trim($_FILES['uploadfile']['tmp_name']); 
	$upload_class->file_name = trim(strtolower($_FILES['uploadfile']['name']));
	$upload_class->upload_dir = $global['approot'].'mod/imp/upload_tmp/'; 
	
	$upload_class->ext_array = array(".csv"); 
  	$valid_ext = $upload_class->shn_imp_imp_per_validate_extension(); 
	       
      if (!$valid_ext) { 
           add_error(_("The file is not a csv one, please try again!")); 
           $error_flag = true;
	  } else if (is_uploaded_file($_FILES['uploadfile']['tmp_name'])){
		$uploaddir = $global['approot'].'mod/imp/upload_tmp/'; 
		$uploadfile =$uploaddir.basename($_FILES['uploadfile']['name']);


	    if (move_uploaded_file($_FILES['uploadfile']['tmp_name'], $uploadfile)) {
    			     $error_flag = false; 
			    } 		       
              } else {
               	add_error(_("file cannot uploaded"));
 				 $error_flag = true;
	        }

   }//end of outer else 

  
 if($error_flag) 
   return false;
  else{ 
      return true;
  } 
} //end function
/* }}} */

/* {{{XML file add Form validate */
/**
 * This validates the entry of upload form
 * 
 * @access public
 * @return void
 */
function shn_imp_imp_xml_upload_form_valid(){

global $global;

$error_flag = false; 

   if($_FILES['uploadfile']['error']==UPLOAD_ERR_NO_FILE){ 
   add_error(_("please enter a valid file")); 
    $error_flag = true;
     }
     
   else {
	$upload_class = new Upload_Files; 
	$upload_class->temp_file_name = trim($_FILES['uploadfile']['tmp_name']); 
	$upload_class->file_name = trim(strtolower($_FILES['uploadfile']['name']));
	$upload_class->upload_dir = $global['approot'].'mod/imp/upload_tmp/'; 
	
	$upload_class->ext_array = array(".xml"); 
  	$valid_ext = $upload_class->shn_imp_imp_per_validate_extension(); 
	       
      if (!$valid_ext) { 
           add_error(_("The file is not a xml one, please try again!")); 
           $error_flag = true;
	  } else if (is_uploaded_file($_FILES['uploadfile']['tmp_name'])){
		$uploaddir = $global['approot'].'mod/imp/upload_tmp/'; 
		$uploadfile =$uploaddir.basename($_FILES['uploadfile']['name']);


	    if (move_uploaded_file($_FILES['uploadfile']['tmp_name'], $uploadfile)) {
    			     $error_flag = false; 
			    } 		       
              } else {
               	add_error(_("file cannot uploaded"));
 				 $error_flag = true;
	        }

   }//end of outer else 

  
 if($error_flag) 
   return false;
  else{ 
      return true;
  } 
} //end function
/* }}} */

/**
* This function process the upload file
*
*@return void
*@access public
*
*/ 

function shn_imp_imp_per_postprocess()
{
 global $global;

 $filename=$global['approot'].'mod/imp/upload_tmp/'.$_FILES['uploadfile']['name'];
 $_SESSION['filename'] = $filename;

    if (isset($_POST["skipcolumnheader"])){
      $skipColumnHeader = FALSE;
    }
    else  $skipColumnHeader =TRUE;

  $_SESSION['skipColumnHeader'] =  $skipColumnHeader; 
   
  $contactType = $_POST["contacttype"]; 
  $_SESSION['contactType'] = $contactType;
  $_SESSION['individualtype'] = $_POST["Individualtype"] ;

 
$seperator = ',';
$mapper = array( );
$parser =& new imp_import_parser_contact($mapper);
$parser->shn_imp_imp_per_setMaxLinesToProcess(100);
$parser->shn_imp_imp_per_run($filename,$seperator,$mapper,$skipColumnHeader,imp_import_parser::MODE_MAPFIELD,$contactType); 
$mapfield =& new imp_Import_Form_MapField;
$mapfield->shn_imp_imp_per_preProcess(); 
$mapfield->shn_imp_imp_per_buildQuickForm();


} //end function


/* }}} */

/**
 * This is a buch of javascript helps for the collapse and expanind of a
 * given division.
 * @todo Move to somewhere 
 * @access public
 * @return void
 */
function shn_js_toggle_layer()
{
?>
<script language="javascript">
function toggle(){
	var el=document.getElementById('contacttype');
	if(el.value =='INDIVIDUAL'){
	document.getElementById('options').style.display='block';
	}
	else{
	document.getElementById('options').style.display='none';
	}
}
toggle();
</script>
<?php
}



?>

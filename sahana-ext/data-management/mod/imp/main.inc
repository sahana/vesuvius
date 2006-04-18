<?php
/* $Id: main.inc,v 1.2 2006-04-18 07:06:46 janakawicks Exp $ */
/* Last modified : 03/04/2006 */

/**
 * Main Controller of the Data Import Module 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot']."/inc/lib_modules.inc";
include_once $global['approot']."/inc/lib_menu.inc";
include_once $global['approot']."/inc/lib_form.inc";
include_once $global['approot']."/inc/lib_validate.inc";
include_once $global['approot']."/inc/lib_errors.inc";


/* {{{ Main Menu */
/**
 * This function defines the menu list.
 * @access public
 * @return void
 */

 //$mapresult = array(); 
function shn_imp_mainmenu() 
{
    global $global;
    $module = $global['module'];

    // Create the module menu
    shn_mod_menuopen(_("Data Import Module"));

    shn_mod_menuitem("default",_("Home"));
    shn_mod_menuitem("imp_per",_("Import Data"));
    shn_mod_menuclose();
   
    // include the main menu
    include $global['approot']."/inc/handler_mainmenu.inc";
} 

/* {{{ Action: Default (Home Page) */
/**
 * 
 * This function displays the home page of the data import module
 *
 * @access public
 * @return void
 */
function shn_imp_default()
{
    global $global;
  require($global['approot'].'mod/imp/home.inc');	

}
/* }}} */



/* {{{ Action: Upload */
/**
 * This is the upload Controller
 * @access public
 * @return void
 */

function shn_imp_imp_per()
{
    global $global;
    require($global['approot'].'mod/imp/add.inc');    

   switch ($_REQUEST['seq']) {
     case 'upload_file':

         if(shn_imp_imp_per_upload_form_valid()){
                     shn_imp_imp_per_postprocess();
	 }
	 else {
            echo '<h2 align="center">'._('Upload File').'</h2>';
            echo '<h2 align="center">('._('Upload CSV File').')</h2>';
           shn_imp_imp_per_upload(true);
	 }

       break;
    
    	     
     default:
            echo '<h2 align="center">'._('Upload File').'</h2>';
            echo '<h2 align="center">('._('Upload CSV File').')</h2>';
	        shn_imp_imp_per_upload();
     break;

   } 

   
 
}
/* }}} */

/* {{{ Action: preview and import*/
/**
 * This is the preview and import Controller
 * @access public
 * @return void
 */

function shn_imp_imp_per_mapfield()
{ 

   global $global; 

    require_once($global['approot'].'mod/imp/add.inc');
    require_once($global['approot'].'mod/imp/import.inc');
 switch ($_REQUEST['seq']){ 
   case 'map_field' :
    echo '<h2 align="center">'._('Preview Matching').'</h2>';	   
    shn_imp_imp_per_previewForm(); 
    break; 

   case 'preview':
    echo '<h2 align="center">'._('Summary').'</h2>'; 
     if ($_SESSION['contactType'] === 'ORGANIZATION')
      shn_imp_imp_per_Import_Organization();
     else if ($_SESSION['contactType'] === 'INDIVIDUAL')
       shn_imp_imp_per_Import_Individual() ; 
        else  
         shn_imp_imp_per_Import_Camp();
   break;
   default :  
     break;
} 
}
/*}}}*/


/* {{{ Action: support to preview controller */
/**
 * this preview the matching 
 * @access public
 * @return void
 */
function shn_imp_imp_per_previewForm()
{
   
    
    $matchresult = $_POST['mappedvalue']; 
    $map = $_SESSION['mapper']; 
    $colcount = count($matchresult);
   
    //used to store the matching result.  
     global  $mapresult; 
    for ($i=0; $i< $colcount; $i++)
    { 

	    foreach ( $matchresult as $key=>$value) {
            $mapresult[$key] = $map[$value] ;  
	    }

    }

           
	shn_form_fopen("imp_per_mapfield",null,array('req'=> false));  
        shn_form_hidden(array('seq'=>'preview'));
	shn_form_fsopen('Notice'); 
        ?>
        <p><?=_('The information below previews the results of importing your data in Sahana.If you are ready to import press Import Now '); ?></p> 
	 

	<?php
	shn_form_fsclose();
        shn_form_fsopen(_('Preview'));

        ?>
	
	
  <div id = "result">
   <table> 
   <?php
    if ($_SESSION['rowDisplayCount']=== 2) 
    {    
     $k = 0; 	    
    ?>
     <thead>
            <td><?=_("Field Name")?></td>
	     <td><?=_("Row1 Data")?></td>
            <td><?=_("Row2 Data ")?></td>
            <td><?=_("Matching Fields")?></td>
        </thead>
    <?php
    }  
    else { 
     $k = 1;     	    
     ?>
     <thead>
            <td><?=_("Row1 Data")?></td>
            <td><?=_("Row2 Data")?></td>
	    <td><?=_("Row3 Data")?></td>
	    <td><?=_("Matching Fields")?></td>
            
        </thead>
    <?php
     }	    
    	
  $_dataValues= $_SESSION['dataValues'];


 for ( $i = 0; $i < $colcount; $i++ ){
 ?><tr><?
  for ($j = $k; $j<= $_SESSION['rowDisplayCount'];$j++){
  ?>  
	
<td><?php echo $_dataValues[$j][$i]?></td> 
	           
     <?php
  } ?>  

 	   <td><?php echo $mapresult[$i];?> </td>
	   </tr>
     <?php  
  
	        
       }
      ?>
   </table>
</div> 
<?php
 shn_form_fsclose(); 
     shn_form_submit(_('Import Now')); 

     shn_form_fclose(); 
$_SESSION['mapping'] = $mapresult;

}
/* }}} */


?>


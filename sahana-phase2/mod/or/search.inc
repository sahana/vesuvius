<?php
/*
*
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra <ravindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";
include_once $global['approot']."/inc/lib_location.inc";
include_once $global['approot']."/inc/lib_errors.inc";


function _shn_or_form_search()
{
global $global;
$db=$global["db"];
 
?>
<h2>Search for Organizations by Service and Location</h2>
<div id="formcontainer">
<?php
shn_form_fopen("search_cr");
  shn_form_fsopen("Organization Type");
_shn_or_display_org_type($error);
shn_form_fsclose();
shn_form_fsopen("Organization Sector");
_shn_or_display_sector($error);
shn_form_fsclose();
  shn_form_fsopen(_("Search Based on"));    
shn_form_opt_select('opt_location_type','',null,null);
   shn_form_fsclose();                      

    $location_inf = shn_location_form('1','4'); 
    

?>
</br>
<center>
<?php
//create the submit button
shn_form_submit(_("Search"));
?>
</center>
</br>
<?php
        //close the form
     	shn_form_fclose();
?>				     
</div>
<?php
}

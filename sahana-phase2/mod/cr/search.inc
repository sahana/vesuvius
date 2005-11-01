<?php
/* $Id; */

/**Search for  CR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Chathra Hendehewa <chathra@opensource.lk>
* @author   Mifan Careem <mifan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

include_once($global['approot'].'/inc/lib_form.inc');

function _shn_cr_srch(){
	global $global;
?>
	 	  <h2>Search for a Camp</h2>
 <?php
			shn_form_fopen("sercmp");
			shn_form_fsopen("SEARCH");
			shn_form_hidden(array('seq'=>'next'));
			shn_form_text('Name of the Camp','cmp_id','size="20"',array('req'=>true));
 ?>
 <br>		<?php
         shn_form_opt_select("opt_location_type","Location Type");
			shn_form_fsclose();
			shn_form_fclose();

}

?>


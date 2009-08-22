<?php
/**Admin controller of the Reporting Module 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ishan Liyanage <ishan@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage rs
*/
include_once 'nice_name.inc';

function shn_rs_adm_default(){
	echo "<h2>"._("Update database metadata tables")."</h2>";
    shn_form_fopen("adm_generate_matadata",null,array('req_message'=>false));
    ?>
    <p>You can update database meta data tables, if required. Those metadata tables use in Dynamic reporting and exporting interfaces to display database table nice names to users.</p>
    <br>
    <?php
    shn_form_submit(_t("Update"));
    shn_form_fclose();
}

function shn_rs_adm_generate_matadata(){
    _shn_rs_nice_name_extracter();	
    add_confirmation('Metadata tables updated successfully.');
    shn_rs_adm_default();
}

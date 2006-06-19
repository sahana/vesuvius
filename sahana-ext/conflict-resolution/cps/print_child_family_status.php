<?php
/* $Id; */

/**Child library for  CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/
ob_start();

$child_code=$_GET['1'];
$center_name=$_GET['2'];
$opt_child_family_status=$_GET['3'];
$opt_house_not_backed_reason=$_GET['4'];
	$has_income=$_GET['5'];
	$income_description=$_GET['6'];
	$materials=$_GET['7'];
	$is_needed=$_GET['8'];
	$opt_house=$_GET['9'];
	
	


	
	$csv_output="\t\tChild Family Situation\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tCurrently Family is\t\t\t".$opt_child_family_status."\015\012
\t\tIf the family is not back to their previous house due to:\t\t\t".$opt_house_not_backed_reason."\015\012
\t\tDoes Family has sufficient income?\t\t\t".$has_income."\015\012
\t\tFamily Details\t\t\t".$income_description."\015\012
\t\tSpecial Material needed?\t\t\t".$is_needed."\015\012
\t\tSpecial Material Needs\t\t\t".$materials."\015\012
\t\tDuring the Tsunami:\t\t\t".$opt_house."\015\012

" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  



?>
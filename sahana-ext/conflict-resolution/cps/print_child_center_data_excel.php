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

$center_code=$_GET['1'];
$center_name=$_GET['2'];;
$date=$_GET['3'];;
$filed_by=$_GET['4'];;
$function=$_GET['5'];;
	

$csv_output="\t\tChild Center Details\015\012\015\012";
$csv_output .= "\t\tCenterCode\t\t\t".$center_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tDate \t\t\t".$date."\015\012
\t\tFiled by\t\t\t".$filed_by."\015\012
\t\tFunction\t\t\t".$function."\015\012
" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  

?>
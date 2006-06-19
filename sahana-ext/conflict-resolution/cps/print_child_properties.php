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
$q1=$_GET['3'];
$q2=$_GET['4'];
$q3=$_GET['5'];
$q4=$_GET['6'];
$q5=$_GET['7'];
$q6=$_GET['8'];
$q7=$_GET['9'];
$other=$_GET['10'];

$csv_output="\t\tChild Properties\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tDoes the child?\t\t\t"."\015\012
\t\tSeem to be a beating child?\t\t\t".$q1."\015\012
\t\tVictim of a sexualabuse?\t\t\t".$q2."\015\012
\t\tSeems to be a neglecting child?\t\t\t".$q3."\015\012
\t\tVictim of child trafficcing?\t\t\t".$q4."\015\012
\t\tVictim of domestic violence? \t\t\t".$q5."\015\012
\t\tDrink Alcohol?\t\t\t ".$q6."\015\012
\t\tNeed TDH follow up?\t\t\t".$q7."\015\012
\t\tOther Details\t\t\t".$other."\015\012

" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  




?>
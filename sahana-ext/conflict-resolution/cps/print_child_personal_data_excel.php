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

$cd=$_GET['1'];
$opt_child_center_names=$_GET['2'];;
	$full_name=$_GET['3'];;
	$family_name=$_GET['4'];;
	$local_name=$_GET['5'];;
	$dob=$_GET['6'];;
	$pob=$_GET['7'];;//to child_personal
	$pr=$_GET['8'];//to child_personal
	$cf=$_GET['9'];;//to child_personal
  $idtype=$_GET['10'];//birth certificate changeisuru
  $age=$_GET['11'];
	$id_card=$_GET['12'];
	$agegroup=$_GET['13'];
	$maritalstatus=$_GET['14'];
  $country=$_GET['15'];
	$religion=$_GET['16'];
	$race=$_GET['17'];
  $gender=$_GET['18'];
  $opt_bc_status=$_GET['19'];
  $is_reg=$_GET['20'];
if($is_reg==1)
$is_reg='Yes';
else
$is_reg='No';


$csv_output="\t\tChildPersonal Data\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t".$cd."\015\012
\t\tCenter Code\t\t".$opt_child_center_names."\015\012
\t\tFirst Name\t\t".$local_name."\015\012
\t\tLastName\t\t".$full_name."\015\012
\t\tFamilyName\t\t".$family_name."\015\012
\t\tDOB\t\t".$dob."\015\012
\t\tPlaceofBirth\t\t".$pob."\015\012
\t\tCurrent Address\t\t".$pr."\015\012
\t\tComingFrom\t\t".$cf."\015\012
\t\tBirthCertificate\t\t".$opt_bc_status."\015\012
\t\tBCNumber\t\t".$id_card."\015\012
\t\tAge\t\t".$age."\015\012
\t\tGender\t\t".$gender."\015\012
\t\tMaritalStatus\t\t".$maritalstatus."\015\012
\t\tCountry\t\t".$country."\015\012
\t\tReligion\t\t".$religion."\015\012
\t\tRace\t\t".$race."\015\012
\t\tIs Registeredin School\t\t".$is_reg."\015\012
" ;
$csv_output .= "\015\012";
   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  

?>
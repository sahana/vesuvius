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
$relationship_type=$_GET['3'];;
$name=$_GET['4'];;
$age=$_GET['5'];;
	
	$profession=$_GET['6'];;
	$issLivingwithChild=$_GET['7'];;//to child_personal
	$isAlive=$_GET['8'];//to child_personal
	$loc=$_GET['9'];;//to child_personal
$incen=$_GET['10'];//birth certificate changeisuru
$isschool=$_GET['11'];
$isofffoster=$_GET['12'];
$age=$_GET['12'];
$isdied=$_GET['12'];
$ismissing=$_GET['12'];

$csv_output="\t\tChild Relation Data\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t\t".$cd."\015\012
\t\tCenter Code\t\t\t\t".$opt_child_center_names."\015\012
\t\tRelationShip Type\t\t\t\t".$relationship_type."\015\012
\t\tName\t\t\t\t".$name."\015\012
\t\tAge\t\t\t\t".$age."\015\012
\t\tProfession\t\t\t\t".$profession."\015\012
\t\tIsAlive\t\t\t\t".$isAlive."\015\012
\t\tIs Living With Child\t\t\t\t".$issLivingwithChild."\015\012
\t\tLocation If Not Living With Child\t\t\t\t".$loc."\015\012
\t\tInCenter\t\t\t\t".$incen."\015\012
\t\tIs Registered in School\t\t\t\t".$isschool."\015\012
\t\tISOfficialFostering\t\t\t\t".$isofffoster."\015\012
\t\tAge\t\t\t\t".$age."\015\012
\t\tIs Died\t\t\t\t".$isdied."\015\012
\t\tIs Missing\t\t\t\t".$ismissing."\015\012
" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  




?>
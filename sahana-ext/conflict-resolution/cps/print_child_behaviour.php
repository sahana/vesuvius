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
$answered_by=$_GET['3'];
$q1=$_GET['4'];
$q2=$_GET['5'];
$q3=$_GET['6'];
$q4=$_GET['7'];
$q5=$_GET['8'];
$q6=$_GET['9'];
$q7=$_GET['10'];
$q8=$_GET['11'];
$q9=$_GET['12'];
$q10=$_GET['13'];
$q11=$_GET['14'];
$q12=$_GET['15'];
$q13=$_GET['16'];
$q15=$_GET['17'];
$q16=$_GET['18'];
$q17=$_GET['19'];
$q18=$_GET['20'];
$q19=$_GET['21'];
$q20=$_GET['22'];
$who=$_GET['23'];

	
$csv_output="\t\tChild Behaviour Details\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tSpontaneous answer given by:?\t\t\t".$answered_by."\015\012
\t\tSince the tsunami: ,have there been changes in the childs behaviour and emotions?\t\t\t"."\015\012
\t\tDoes the Child:?\t\t\t"."\015\012


\t\tHave difficulty leaving the house, the family or the caregiver, and or/clings to the mother/caregiver?\t\t\t".$q1."\015\012
\t\tHave more problems in concentrating or remembering, for example in school homework?\t\t\t".$q18."\015\012
\t\tHave more sleep difficulties than before, such as getting to sleep or sudden awakenings?\t\t\t".$q3."\015\012
\t\tShow signs of having lost his /her  appetite and eats less than before?\t\t\t".$q2."\015\012
\t\tHave recurrent dreams or nightmares which refer to the tsunami? \t\t\t".$q5."\015\012

\t\tShow more difficulty in controlling emotions, such as getting upset, angry?\t\t\t".$q7."\015\012
\t\tShow signs of being more afraid of strangers than before ?\t\t\t".$q4."\015\012
\t\tIs  afraid of another tsunami and  talks about it frequently?\t\t\t".$q9."\015\012
\t\tShow signs of being  less interested in education and future life?\t\t\t".$q6."\015\012
\t\tNever want to talk about  it and avoid everything  places or situations that remind him/her of it?\t\t\t".$q11."\015\012
\t\tShow signs of being  more aggressive than before, both with caregivers and family members, or at school?\t\t\t".	$q8."\015\012
\t\tSeem more withdrawn or shy than before?\t\t\t".$q13."\015\012

\t\tOften cry and look sad?\t\t\t".$q10."\015\012
\t\tOften seem distracted, dreamy or deep in thoughts?\t\t\t".$q15."\015\012
\t\tWhen playing or drawing, act out his/her experience of the tsunami?\t\t\t".$q12."\015\012
\t\tSay he/she has pictures of his / her tsunami experience coming suddenly in the mind ?\t\t\t".$q16."\015\012
\t\tSeek more attention from adults caring for him / her? \t\t\t".$q17."\015\012
\t\tHas the family or the child received support since the tsunami from a professional counsellor for these problems?\t\t\t".$q19."\015\012
\t\tIf Yes From who ?\t\t\t".$who."\015\012
\t\tHave you noticed any improvement after that?\t\t\t".$q20."\015\012


" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  



?>
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
$question1=$_GET['3'];
$q1explain=$_GET['4'];
$question2=$_GET['5'];
$q2explain=$_GET['6'];
$question3=$_GET['7'];
$question3explain=$_GET['8'];
$question4=$_GET['9'];
$question5=$_GET['10'];
$question6=$_GET['11'];
$question7=$_GET['12'];
$question8=$_GET['13'];
$question9=$_GET['14'];
$question10=$_GET['15'];
$question11=$_GET['16'];
$question11explain=$_GET['17'];
	$question12=$_GET['18'];
$question12explain=$_GET['19'];
	$question13=$_GET['20'];
	$question13explain=$_GET['21'];
		$question14=$_GET['22'];
	$question14explain=$_GET['23'];
	
$csv_output="\t\tChild Health Details\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tDoes the child show any disability (mental or physical)?\t\t\t".$question1."\015\012
\t\tExplain in Detail\t\t\t".$q1explain."\015\012
\t\tHas the child received any specific assistance or support for that? (Special school, artificial limb...)\t\t\t".$question2."\015\012
\t\tExplain in Detail\t\t\t".$q2explain."\015\012
\t\tHas the child been physically affected by the tsunami?\t\t\t".$question3."\015\012
\t\tExplain in detail \t\t\t".$question3explain."\015\012
\t\tDoes child have physical problems? "."\015\012
\t\tHeadaches\t\t\t".$question4."\015\012
\t\tNausea, feels sick\t\t\t".$question5."\015\012
\t\tEye problems (not if corrected by glasses)\t\t\t".$question6."\015\012
\t\tRashes or other skin problems\t\t\t".$question7."\015\012
\t\tAches and pains (not stomach or headaches)\t\t\t".$question8."\015\012
\t\tVomiting, throwing up\t\t\t".	$question9."\015\012
\t\tHas the child been seen by a doctor since the tsunami\t\t\t".$question10."\015\012
\t\tBefore Tsunami? "."\015\012
\t\tDid the child suffer from any chronic disease?\t\t\t".$question11."\015\012
\t\tExplain in detail\t\t\t".$question11explain."\015\012
\t\tHad the child been seriously ill or injured in the last 12months?\t\t\t".$question12."\015\012
\t\tExplain in detail\t\t\t".$question12explain."\015\012
\t\tHas the child been operated in the last 12 months?\t\t\t".$question13."\015\012
\t\tExplain in detail\t\t\t".$question13explain."\015\012
\t\tAt Present Child health is still affected?\t\t\t".$question14."\015\012
\t\tExplain in detail\t\t\t".$question14explain."\015\012


" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  




?>
<?php
ob_start();

//$select="select * from person_details where opt_gender='{$opt_gender}'";                  
//ob_start();

$child_code=$_GET['1'];
        $center_name=$_GET['2'];
$date=$_GET['3'];
	$rep_name=$_GET['4'];
	$rep_relation=$_GET['5'];
	$rep_address=$_GET['6'];
	$rep_phone=$_GET['7'];
	$rep_email=$_GET['8'];
	
	
/*	$dor=$_GET['6'];
	$rep_fullname=$_GET['7'];;//to child_personal
	$rep_relation=$_GET['8'];//to child_personal
	$rep_phone=$_GET['9'];;//to child_personal
        $rep_email=$_GET['10'];//birth certificate changeisuru
$address=$_GET['11'];
/*\t\tReporters Relation\t\t\t".$rep_relation."\015\012
\t\tReporters Phone\t\t\t".$rep_phone."\015\012
\t\tReportersEmail\t\t\t".$rep_email."\015\012
\t\tReporters Address\t\t\t".$address."\015\012
*/

	
	$csv_output="\t\tChild Reporter Details\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tDate Of First Registered \t\t\t".$date."\015\012
\t\tReporters Name\t\t\t".$rep_name."\015\012
\t\tReporters Relation\t\t\t".$rep_relation."\015\012
\t\tReporters Address\t\t\t".$rep_address."\015\012
\t\tReporters Phone\t\t\t".$rep_phone."\015\012
\t\tReporters Email\t\t\t".$rep_email."\015\012

" ;
$csv_output .= "\015\012";


   header("Content-type: application/vnd.ms-excel");
   header("Content-disposition: csv" . date("Y-m-d") . ".xls");
   print $csv_output;
   exit;  




/*

header("Content-type: application/octet-stream");  
header("Content-Disposition: attachment; filename=AjayExcel.xls");  
header("Pragma: no-cache");  
header("Expires: 0");  
header("Lacation: excel.htm?id=yes"); 
print "$headern$data";  

*/
?>
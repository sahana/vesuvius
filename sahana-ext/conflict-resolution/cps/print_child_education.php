<?php
ob_start();

//$select="select * from person_details where opt_gender='{$opt_gender}'";                  
//ob_start();

$child_code=$_GET['1'];
$center_name=$_GET['2'];
$is_school_tsunami=$_GET['3'];
$school_name_tsunami=$_GET['4'];
$why_tsunami=$_GET['5'];
$level_tsunami=$_GET['6'];
$is_gngto_school_now=$_GET['7'];
$school_name_now=$_GET['8'];
$why_now=$_GET['9'];
$level_now=$_GET['10'];
$is_gngto_tution=$_GET['11'];
$is_religious=$_GET['12'];
$is_temple=$_GET['13'];
$bf1=$_GET['14'];
$bf1reg=$_GET['15'];
$bf2=$_GET['16'];
$bf2reg=$_GET['17'];
	
	
	
$csv_output="\t\tChild Education Details\015\012\015\012";
$csv_output .= "\t\tChildCode\t\t\t".$child_code."\015\012
\t\tCenter Name\t\t\t".$center_name."\015\012
\t\tWas the child going to school before tsunami?\t\t\t".$is_school_tsunami."\015\012
\t\tSchool Name\t\t\t".$school_name_tsunami."\015\012
\t\tWhy\t\t\t".$why_tsunami."\015\012
\t\tLevel\t\t\t".	$level_tsunami."\015\012
\t\tIs the child going to school now?\t\t\t".$is_gngto_school_now."\015\012
\t\tSchool Name\t\t\t".$school_name_now."\015\012
\t\tWhy\t\t\t".$why_now."\015\012
\t\tLevel\t\t\t".$level_now."\015\012
\t\tIs the child going to tution Now?\t\t\t".$is_gngto_tution."\015\012
\t\tIs the child goingto religious school now\t\t\t".$is_religious."\015\012
\t\tIs the child goingto temple or mosque now\t\t\t".$is_temple."\015\012
\t\tChilds Best Friend Name\t\t\t".	$bf1."\015\012
\t\tBest Friend registered in center\t\t\t".$bf1reg."\015\012
\t\tBest Friend Name\t\t\t".$bf2."\015\012
\t\tBest Friend registered in center\t\t\t".$bf2reg."\015\012

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
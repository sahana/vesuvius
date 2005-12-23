<form action='' method='POST'>
<?php
/*
This new version of the little toy, at 19 november 2005, let you to set as link not all days of the week
i use it for reservation page for a camping web site and the start of the week is possible only at the week end and no in all days of the week
NB: THERE IS A LITTLE BUG IN THE CORE JAVASCRIPT: SOMETIME , in the previous month, the days linkable are not
active;

please report any other bug or problem at andreabersi@gmail.com

Ciao

Andrea Bersi
AOSTA (ITALY)
http://abmcr.altervista.org

*/
//require the class file php
require_once ("cal_class.php");
//include in the file the javascript core
//NB: the core file is included one time only for all istances of class
//it is better to include it in the head of page 
echo '<script language="javascript" type="text/javascript" src="calendar.core.js"></script>';
//create the instance of calendar
$calendario=new Calendar("en");
//$calendario->grandezza_carattere="Small";
//print the calendar in italian version of date i.e.: dd/mm/yyyy
$calendario->CreateCalendar(date("d/m/Y"),"uno",date("m/d/Y"),"12/31/2006");
echo "<hr>";
//set a background for the week days
$calendario->sfondo_settimana="Green";
//set only a few days of the week linkable
$calendario->giorni_settimana_linkabili="2,3,5";
//print the calendar in english version of date i.e.: mm/dd/yyyy
$calendario->CreateCalendar(date("m/d/Y"),"due",date("m/d/Y"),"12/31/2005",1);
?>
<table width="50%" align="center">
<tr><td>Example of text</td><td>
<?php
//print the calendar in italian version of date i.e.: dd/mm/yyyy
$calendario->sfondo_settimana="#ff0066";
$calendario->CreateCalendar("20/11/2005","tre",date("m/d/Y"),"12/31/2007");
?></td><tr></table>
<input type="submit"></form>

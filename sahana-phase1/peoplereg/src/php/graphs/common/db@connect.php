<?php
 # db@connect.php - Database library functions.
 # Author: Buddhika Siddhisena [Bud@babytux.org]
 # License : GPL
 # Created: 31/12/2004
 # Updated: 04/01/2005

// Site configuration
require_once("/var/www/mambo/sahana/common/site@config.php");

//Connect to database
$conn=mysql_connect($host,$dbuser,$dbpassword);
$link = $conn;

//Select database
if (!mysql_select_db($database,$conn)){
	echo ("Error selecting a database");
	exit();
}

function get_page($pageurl){
 $page = file($pageurl);
 $page = implode('',$page);
 return $page;
}

function dbsel($val,$fname,$width,$table,$fldset,$crit=''){
 # Creates a drop down from a database
 global $conn;
 
 $sql="select $fldset from $table";
 if ($crit)
  $sql .= " WHERE $crit";
  
 $rs=mysql_query($sql);xdb($sql);
 $num_rows=mysql_num_rows($rs);
 if($num_rows==0) return;
 $matches=array();
 $matches=preg_split("/\,/",$fldset);
 //Assume keyfield to be first in fieldlist
 $keyid='';$keyval='';$cont='';
 if(count($matches)>1){
  list($keyid,$keyval)=$matches;db("KEYID=$keyid, KEYVAL=$keyval");
 }

 $cont="<select name=\"$fname\" width=\"$width\">";
 for($i=0;$i<$num_rows;$i++){
  $row=mysql_fetch_array($rs);
  if($row[$keyid]==$val){
   $cont.="<option value=\"$row[$keyid]\" selected>$row[$keyval]</option>";
  }
  else{$cont.="<option value=\"$row[$keyid]\">$row[$keyval]</option>";}
 }#end for($i=0;$i<$num_rows;$i++)
 $cont.="</select>";
return $cont;
}

# prototype: function get_data($table,$fldset,$fldprefx,$crit,$sort,$handle)
# Desc: Fetch data from database. Returns number of results
# Fields: $table - table name, $fldset - field set;
#       $fldprefx - prefix used for creating variables,
#       $crit - criteria, $sort - sort order, $handle - register a callback func. Passes $row as arg
#       $page_size - number of results to show on a page (0 to show all)
#       $page_id - current page to display
# Author : Bud (bud@codevalley.cc)
# Created : 24/11/2002  Updated : 23/02/2003
function get_data($table,$fldset,$fldprefx='',$crit='',$sort='',$handle='',$page_size=0,$page_id=1)
{
global $conn;

$page_id=($page_id<=0)?1:$page_id;

// build query
 $sql = "SELECT $fldset FROM $table";
 if ($crit)
  $sql .= " WHERE $crit";
 if ($sort)
  $sql .= " ORDER BY $sort"; xdb("sql :$sql");

	$rs = mysql_query($sql);
	$num_results = mysql_num_rows($rs); xdb("No of results:$num_results");
	if ($num_results==0)
	 return 0;

	$page_start=0; $page_end=$num_results;
// work out paging
	if ($page_size>0){
		if(!($page_id>0)) {db("Page ID must be positive");return 0;}
		$page_start=$page_size * ($page_id-1);db("PG_START : $page_start");
		if($num_results>=$page_size){$page_end=$page_start+$page_size;} db("PG_END : $page_end");
		if ($page_start>=$num_results){ xdb("Start record exceeds total records");return 0;}
		if ($page_end>=$num_results) $page_end=$num_results;
		# seek the internel row pointer (mysQL only)
		mysql_data_seek($rs,$page_start);
	}#end if ($page_size>0)

	$row='';

	for ($i=$page_start;$i<$page_end;$i++){
		$row = mysql_fetch_array($rs);
		if($handle)
			$handle($row); //execute handle
	}

	// put last data into global variables
	// handle special aggrigated functions count(*), max(*) etc.
	if (eregi("^.+ AS (.+)",$fldset,$xx)){$fldset= $xx[1];}
	if(!$handle){
		$fld_arr = split(',',$fldset);
		for ($i=0;$i<count($fld_arr);$i++){
			$GLOBALS[$fldprefx.$fld_arr[$i]]=$row[$i]; db("<br>global var: $fld_arr[$i] val: $row[$i]");
		}
	}
	// clean up
	mysql_free_result($rs);
 return $num_results;

}
?>

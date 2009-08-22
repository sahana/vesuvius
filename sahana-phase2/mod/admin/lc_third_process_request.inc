<?php
// Get a file into an array.  In this example we'll go through HTTP to get
// the HTML source of a URL.
define('LENGTH', 8);
$locale = $_REQUEST['locale'];
//_find_translated_str();
//_store_msgid($_REQUEST['msgid'],$locale);

function _find_translated_str()
{
	$msgid = $_REQUEST['msgid'];
	$msgid = trim($msgid);
	$msgstr = $_REQUEST['msgstr'];
	$locale = $_REQUEST['locale'];	
	$tag = $_REQUEST['tag'];
	
	if(strlen($msgid)>70) {
		$msgid = substr($msgid,0,70);	
	}
	
	$_SESSION['admin']['locale']['sahana_po'] = implode('', file("../res/locale/$locale/LC_MESSAGES/sahana_temp.po"));	
	$position = strpos($_SESSION['admin']['locale']['sahana_po'],$msgid);	

	if($tag=='true') {	
		_replace_str_confirm($position,$msgid,$msgstr,$locale);
	}else if($position!=null)
		_find_str();
	else 
		_find_translated_str_and_replace();
}


function _find_translated_str_and_replace()
{
	$msgid = $_REQUEST['msgid'];
	$msgstr = $_REQUEST['msgstr'];
	$locale = $_REQUEST['locale'];	
	$_SESSION['admin']['locale']['sahana_po'] = implode('', file("../res/locale/$locale/LC_MESSAGES/sahana.po"));	
	$_SESSION['admin']['locale']['sahana_po'] = $_SESSION['admin']['locale']['sahana_po'];
	//$msgid = strrev($msgid);
	//$msgid = utf8_decode($msgid);
	//$msgid = utf8_decode("u0DC3");

	//echo iconv("UTF-8","ISO-8859-1",$msgid);
	//echo $msgid;
	$position = strpos($_SESSION['admin']['locale']['sahana_po'],$msgid);
	$str = substr($_SESSION['admin']['locale']['sahana_po'],0,$position);
	$strlastmsgidposition = strrpos($str,"msgid");
	++$strlastmsgidposition;
	$qutationpos = strpos($str,"\"",$strlastmsgidposition);
	++$qutationpos; 
	$secondqutationpos = strpos($str,"\"",$qutationpos);
	$strlength =  $secondqutationpos - $qutationpos;
	$finalstr = substr($str,$qutationpos,$strlength);
	echo 'tag111'.$finalstr;
}


function _find_str()
{
	$msgid = $_REQUEST['msgid'];
	$msgstr = $_REQUEST['msgstr'];
	$locale = $_REQUEST['locale'];
	$msgid = trim($msgid);
	$msgstr = addslashes($msgstr);
	//$lines = file('sahana.po');
	// Loop through our array, show HTML source as HTML source; and line numbers too.
	$_SESSION['admin']['locale']['sahana_po'] = implode('', file("../res/locale/$locale/LC_MESSAGES/sahana.po"));  

	if(strlen($msgid)>70) {
		$msgid = substr($msgid,0,70);
		$position = strpos($_SESSION['admin']['locale']['sahana_po'],$msgid);	
		_replace_str_confirm($position,$msgid,$msgstr,$locale);
	}else {
		$i=0;
		$position=1;
		while($position!=null) {	
			if($i!=0) {
				$position = strlen($msgid) + $position;	
			}				
			$position = strpos($_SESSION['admin']['locale']['sahana_po'],$msgid,$position);
			$qutationpos = strpos($_SESSION['admin']['locale']['sahana_po'],"\"",$position);
			//$qutationpos = $position+strlen("Organization Registry");
			$qutationcheck = $position+strlen($msgid);			
			if($qutationcheck==$qutationpos) {			
				$position =$position;			
				_replace_str_confirm($position,$msgid,$msgstr,$locale);
				break;	
			}		
			$i++;
	 	}
	}
}


/*function _replace_str($position,$msgid,$msgstr,$locale)
{
	$strlength = strlen($msgid);
	$positionfirst = $position + $strlength; 
	$positionfirst = strpos($_SESSION['admin']['locale']['sahana_po'],"msgstr",$positionfirst);
	$positionsecond = $positionfirst + 7;
	$qutationpos = strpos($_SESSION['admin']['locale']['sahana_po'],"\"",$positionsecond);
	++$qutationpos; 
	$secondqutationpos = strpos($_SESSION['admin']['locale']['sahana_po'],"\"",$qutationpos);
	//$stringlegth = strlen($_SESSION['admin']['locale']['sahana_po']);
	//$secondposition = $position - $stringlegth + $qutationpos;
	$strlength =  $secondqutationpos - $qutationpos;
	//echo 'STRlength = '.$strlength;
	//echo 'second = '.$secondqutationpos;
	//echo 'first = '.$qutationpos;
	$str = substr($_SESSION['admin']['locale']['sahana_po'],$qutationpos,$strlength);
	
	if($strlength==0) {
		_replace_str_confirm($position,$msgid,$msgstr,$locale);			
	}else {
		echo 'tag222'.$str;
	}
	
}*/


function _replace_str_confirm($position,$msgid,$msgstr,$locale)
{
	if($msgid!='') {
		//echo 'Machan inside';
		$strlength = strlen($msgid);
		$positionfirst = $position + $strlength; 
		$positionfirst = strpos($_SESSION['admin']['locale']['sahana_po'],"msgstr",$positionfirst);
		$position = $positionfirst + LENGTH;
		$qutationpos = strpos($_SESSION['admin']['locale']['sahana_po'],"\"",$position);
		$qutationpos = $qutationpos - $position;
		$stringlegth = strlen($_SESSION['admin']['locale']['sahana_po']);
		$secondposition = $position - $stringlegth + $qutationpos;
		echo 'POSITION'.$secondposition;
		$var = $msgstr;
		$_SESSION['admin']['locale']['sahana_po'] = substr_replace($_SESSION['admin']['locale']['sahana_po'],$var,$position,$secondposition);
	
		$filename = "../res/locale/$locale/LC_MESSAGES/sahana.po";
		$somecontent = $_SESSION['admin']['locale']['sahana_po'];


		if(is_writable($filename)) {   
    		if(!$handle = fopen($filename, 'w+')) {
         		echo "Cannot open file ($filename)";
         		exit;
    		}
			if(fwrite($handle, $somecontent) === FALSE) {
        		echo "Cannot write to file ($filename)";
        		exit;
    		}
    		echo "Success, wrote to file ($filename) .$msgstr"."MSGID = ".$msgid;
    		fclose($handle);

		}else {
    		echo "The file $filename is not writable";
		}
	}//else{
	//echo 'noposition';
	//}	
}


/*function _store_msgid($msgid,$locale)
{
	$filename = "../res/locale/$locale/LC_MESSAGES/test";
	$somecontent = $msgid;


	if(is_writable($filename)) {   
    	if(!$handle = fopen($filename, 'w+')) {
         	echo "hey Cannot open file ($filename)";
         	exit;
    	}
		if(fwrite($handle, $somecontent) === FALSE) {
        	echo "hey Cannot write to file ($filename)";
        	exit;
    	}
    	echo "<h1>hey Success, wrote to file ($filename) </h1>.$msgstr";
    	fclose($handle);

	}else {
    	echo "hey The file $filename is not writable";
	}
}*/

	
 


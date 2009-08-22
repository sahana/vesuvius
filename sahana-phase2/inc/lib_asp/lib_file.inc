/**
* Description for file
* http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana ASP
* @subpackage  
* @author     Pradeeper <pradeeper@opensource.lk>
*/
<?php
// Lib that handle the file and directory 

function check_dir($dir_name)
{
	// echk whether the dir is already there or not
	if(is_dir($dir_name)) {
		$dir_exist="true";
		//echo "file name is $dir_name \n";
		//echo "detect the file/DIR within check function\n";
	} else {
		$dir_exist="false";
		//echo "did NOT detect a file/DIR within the check function\n";
	}
	return $dir_exist;
}// end of dir check function

function msg($err, $succ, $notsucc) // status of the error, successful msg, unsuccessful msg
{
	if ($err==0){
		echo $succ;
	} else {
		echo $notsucc;
	}
}// end of msg function


function check_file($file_name)
{
	// check whether the file is already there or not
	if(file_exists($file_name)) {
		$file_exist="true";
		//echo "file name is $file_name \n";
		//echo "detect the file/DIR within check function\n";
	} else {
		$file_exist="false";
		//echo "did NOT detect a file/DIR within the check function\n";
	}
	return $file_exist;
}// end of dir check function


function creat_dir($name)
{
	//if(is_dir($dir_name)){
	$q=check_dir($name);
	if ($q=="false"){
		echo "Creating the DIR $name \n";
		exec("mkdir $name 2>&1", $out, $error);
		msg($c=$error, $a="DIR $name created successfully [new!]\n", $b="cannot create the DIR [new]!\n");
	} else {
		echo "$name dir is already there!\n";
	}
}// end of sh_asp_creat_dir function

function remove_file($nametoberemove)
{
	$filename=check_file($nametoberemove);
	if ($filename=="true"){
		echo "removing the file $nametoberemove \n";
		exec("rm -rf $nametoberemove 2>&1", $out, $error);
		msg($c=$error, $a="$nametoberemove deletion is sucessfull!\n", $b="Cannot delete the file $nametoberemove, please check the permission.\n");
	} 
	if ($filename=="false") {
		echo "can't locate the file/dir call $nametoberemove.\n";
	} 
}// end of remove_file function


function slink($source, $destination)
{
	$filename=check_file($source);
	if ($filename=="true"){
		echo "Linking the file $source to $destination.\n";
		exec("ln -s $source $destination 2>&1", $out, $error);
		msg($c=$error, $a="Linking $source to $destination is sucessfull!\n", $b="Cannot link the $source to $destination, please check the permission.\n");
	} 
	if ($filename=="false") {
		echo "can't link the $source to $destination.\n";
	} 
}// end of slink function



function copy_file($source, $destination)
{
	$filename=check_file($source);
	if ($filename=="true"){
		echo "copying the $source to $destination.\n";
		exec("cp -rf $source $destination 2>&1", $out, $error);
		msg($c=$error, $a="$source copying to $destination is sucessfull!\n", $b="Cannot copy the $source, please check the permission.\n");
	} 
	if ($filename=="false") {
		echo "can't locate the file/dir call $source.\n";
	} 
}// end of copy_file function


function lock($yesno)
{
	$lockfile="/tmp/sahana-asp";
	if ($yesno=="yes"){ // if main ask to lock the file
		echo "locking the file\n";
		$chk=check_file($lockfile); // checking the lock file
		if ($chk=="true"){
			echo "Sahana-ASP is already running...\n";
		} if ($chk=="false") {
			echo "Starting Sahana-ASP...";
			exec("touch $lockfile 2>&1", $out, $error);
			msg($c=$error, $a="->loked!\n", $b="\nCannot lock the process...\n");
		}
	} if ($yesno=="no") { // if main ask to unlock the file
		echo "unlocking the Sahana-ASP!\n";
		system("rm $lockfile");
	}
}//end of lock file





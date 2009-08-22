<?php
/**
* This file helps in extracting the nice names from sql files
* Sahana - http://sahana.sourceforge.net
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    module
* @subpackage rs
* @author     Nishantha Pradeep <ucscnishantha@gmail.com>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
$db=$global['db'];
//$db->debug=true;
function _shn_rs_sql_file_finder() {
	global $global;
	$approot = $global['approot'];
	///echo $approot;
    $dir    = $approot.'mod';
    //echo $dir;
    $sql_file= '/inst/dbcreate.sql';
    $modules = scandir($dir);
    //print_r($modules);
    $sql_list[0]=$approot.'/inst/mysql-dbcreate.sql';
$counter=1;
for($c=0;$c<count($modules);$c++) {
	if($c!==0 && $c!==1) {
		if($modules[$c]=="vm")
			continue;
		
		$sql_path=$dir.'/'.$modules[$c].'/inst/dbcreate.sql';
		if (file_exists($sql_path)) {
		$sql_list[$counter]=$sql_path;
		$counter++;
		}
		//echo $mod_dir;
		//$instt=scandir($mod_dir);

		/*foreach($instt as $i) {
			if($i=='inst'){
			$sql_list[$counter]=$dir.$modules[$c].$sql_file;
			echo $dir.$modules[$c].$sql_file;
			$counter++;
			break;
			}
		}*/
		//echo "</br>";
		
	}
}
//print_r($sql_list);
return $sql_list;
}


//////////////////////////////////////////////////////
function _shn_rs_nice_name_extracter() {
	global $global;
$db=$global['db'];
$sql_file=_shn_rs_sql_file_finder();

for($sql_f=0; $sql_f < count($sql_file); $sql_f++) {


$file=fopen($sql_file[$sql_f],"r");
$table_name="";
$field_name="";
$nice_field_name="";
$no_need=false;
$no_need_request=false;
$ready_for_neglect=false;
while (!feof ($file)) {
	$temp1=5;
	$temp2=5;
	$buffer = trim(fgets($file));
	$string=explode(" ",$buffer);
	if($buffer=="" || ($no_need==true && $string[0]!="CREATE" ))
		continue;
	else {
		$no_need=false;
		if($ready_for_neglect==true)
			$no_need_request=true;
		else
			$no_need_request=false;
		
		if($string[1]=="name"){
			for($counter=3; $counter < count($string); $counter++) {
				
			}
			
		}else {
			if(!_shn_rs_test_cases($string[0])){

			}
			else  {
			switch($string[0]){
				case "PRIMARY":
					break;
				case "FOREIGN":
					$more=0;
					$foreign_table=array();
					$foreign_table_field=array();
					$for_counter=0;
					if($string[2]{0}=="(")
						$this_table=substr($string[2],1,-1);
					else
						$this_table=$string[2];
					for($refer=3;$refer < count($string);$refer++)	{
						if($string[$refer]=="REFERENCES")
							$more=1;
						if($more==1)
							if($string[$refer+1]!="--") {
								$fo_table=explode("(",$string[$refer+1]);
								$foreign_table[$for_counter]=$fo_table[0];
								$foreign_table_field[$for_counter]=substr($fo_table[1],0,-1);
								$for_counter++;
								$sql="UPDATE dr_fields SET tab_for_key='".$foreign_table[0]."', field_for_key='".$foreign_table_field[0]."' WHERE field_name='".$this_table."' AND table_name='".$table_name."'";
					            $db->Execute($sql);
					            
							}
							else
								break;
					

					}
					
					break;
				case "INSERT" :
					break;
				case "DROP" :
					break;
				case "*" :
					break;
				case "/*" :
					break;
				case "/**":
					break;
				case "*/" :
					break;
				case "--" :
					if($string[1]=="no") {
						$no_need_request=true;
						$ready_for_neglect=true;
					}
					break;
				case ");":
					break;
				case "(":
					break;
				case "CREATE":
					if($no_need_request==true) {
						$no_need=true;
						$ready_for_neglect=false;
						continue;
					}
					$table_name="";
					$nice_name="";
					if(substr($string[2],-1)=="(")
						$temp=substr($string[2],0,-1);
					
					else 
						$temp=$string[2];
					if(substr($temp,-1)=="`")
						$test=substr($temp,1,-1);
					else
						$test=$temp;

					$table_name=$test;
					
					for($counter2=0; $counter2 < count($string); $counter2++) {
						if($string[$counter2]=="--"){ 
							$temp=1;
							continue;
						}
						if($temp==1)
							$nice_name=$nice_name.' '.$string[$counter2];
						
					} 
					if($nice_name=="")
						$nice_name=$table_name;
						$sql="SELECT table_name FROM dr_tables WHERE table_name='".$table_name."'";
						$res=$db->Execute($sql);
						if($res->EOF){
							$sql="INSERT INTO dr_tables (table_name, usrfr_table_name) VALUES ('".$table_name."','".$nice_name."')";
							$db->Execute($sql);
						}
						else
						{
							$sql="UPDATE dr_tables SET usrfr_table_name='".$nice_name."' WHERE table_name='".$table_name."'";
							$db->Execute($sql);
						}
					$nice_name="";
					
					break;
				default :
					$field_name="";
                    $nice_field_name="";
					if($string[0]{0}=="(") {
						$temp_ff=substr($string[0],1);
					}
					else {
						$temp_ff=$string[0];
					}
					
					if(substr($temp_ff,-1)=="`") {
						$test_f=substr($temp_ff,1,-1);
					}
					else {
						$test_f=$temp_ff;
					}
					$field_name=$test_f;

					for($counterr=2; $counterr < count($string); $counterr++) {
						if($string[$counterr]=="--"){ 
							$temp2=1;
							continue;
						}
						if($temp2==1)
							$nice_field_name=$nice_field_name.' '.$string[$counterr];
						
					}
					if($nice_field_name=="")
						$nice_field_name=$field_name;
						$sql="SELECT field_name FROM dr_fields WHERE field_name='".$field_name."' AND table_name='".$table_name."'";
					    $res=$db->Execute($sql);
						if($res->EOF){
							$sql="INSERT INTO dr_fields (field_name, table_name, usrfr_field_name, opt_field_type, tab_for_key, field_for_key) VALUES ('".$field_name."','".$table_name."','".$nice_field_name."','none','none','none')";
							$db->Execute($sql);	
						}
						else
						{
							$sql="UPDATE dr_fields SET usrfr_field_name='".$nice_field_name."' WHERE table_name='".$table_name."',tab_for_key='none',field_for_key='none' AND field_name='".$field_name."'";
							$db->Execute($sql);	
						}
					
			}	
			}	
		
		}
			
	}

}
fclose($file);
}
}

function _shn_rs_test_cases($first_string) {
	if(($first_string{2}=="=")||($first_string{3}=="=")||($first_string{1}=="=")||($first_string{2}=="*"))
		return false;
	if(($first_string{2}=="/")||($first_string{0}==")")||($first_string{0}=="("))
		return false;
	if(($first_string{2}=="I")||($first_string{2}=="S")||($first_string{2}=="C"))
		return false;
	if((($first_string{0}=="*") && ($first_string{1}!="*"))||($first_string{2}=="\t"))
		return false;
	return true;
}


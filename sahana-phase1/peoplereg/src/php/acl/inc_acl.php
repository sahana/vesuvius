<?php
 # inc_acl.php - Access controll for PHP.
 # Author: Buddhika Siddhisena [Bud@babytux.org]
 # License : GPL
 # Created: 11/01/2005
 # Updated: 31/01/2005

function checkacl($user,$module_name,$access_levels){
 
 #-- database config --
$host = "localhost";
$dbuser="root"; $dbpassword="";

$database="erms";

$accessleveltable = 'TBLACCESSLEVELS';
$accessleveltable_fields = 'AccessLevels';
$accessmodulestable='TBLACCESSMODULES';
$accessmodulestable_fields='ModuleId,ModuleName';
$accesspermissions='TBLACCESSPERMISSIONS';
$accesspermissions_fields=' ModuleId ,AccessLevel,Permission,RoleId';
$moduleaccesslevels='TBLMODULEACCESSLEVELS';
$moduleaccesslevels_fields=' ModuleId,AccessLevel';
$rolestable='TBLROLES';
$rolestable_fields=' RoleId,RoleName,Description';
$userrolestable='TBLUSERROLES';
$userrolestable_table='RoleId,UserName';

 //Connect to database
$dbconn=mysql_connect($host,$dbuser,$dbpassword);

//Select database
if (!mysql_select_db($database,$dbconn)){
	echo ("Error selecting a database");
	exit();
}

$sql="SELECT AccessLevel,Permission FROM $accesspermissions a,  $userrolestable b, $accessmodulestable c WHERE b.RoleId=a.RoleId AND a.ModuleId=c.ModuleId AND c.ModuleName LIKE '$module_name' AND UserName LIKE '$user'";

$rs=mysql_query($sql);
$status=true;
if(mysql_num_rows($rs)==0){$status=false;} # If we didnt get any result we deny

for($i=0;$i<mysql_num_rows($rs);$i++){
  $row=mysql_fetch_array($rs);
  if (!(preg_match("/$row[AccessLevel]/",$access_levels)) || preg_match("/^n/i",$row['Permission'])){$status=false;}
}

mysql_close($dbconn);
return $status;
}

#checkacl("sanjiva","People Registry","EDIT");
?>

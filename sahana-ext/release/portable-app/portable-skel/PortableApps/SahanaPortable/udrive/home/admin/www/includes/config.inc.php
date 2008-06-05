<?
/*
####################################################
# Name: The Uniform Server Configuration 1.7
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex) 
# Web: http://www.uniformserver.com
####################################################
*/

/* Globals */
// Version
$version = "2.0.4";
$uniserver = file_get_contents("includes/.version");
$unisecure = "0"; //Use secure.php if set to 1
$devmode = "0"; //Developer Mode = 1
$usip = getenv("REMOTE_ADDR");
$hname = gethostbyaddr($REMOTE_ADDR); //Not being used nowssssss

/* Path variables - NO BACKSLASH */
// Local Variables
$drive = $_ENV['Disk'] . ":";
	if($drive == ":"){ 
		$path = realpath(dirname($_SERVER['config.inc.php'])); 
		$pathArray = explode("\\",$path); 
		$drive="$pathArray[0]/$pathArray[1]"; 
}
$usr = "$drive/usr";
$www = "$drive/www";
$home = "$drive/home";

/* htpasswd Variables - NO BACKSLASH */ 
// Required
$htpasswd = "$drive/htpasswd/";
$aphtpasswd = "$htpasswd/home/admin/www/.htpasswd";
$whtpasswd = "$htpasswd/www/.htpasswd";
$mysqlpwd = "$home/admin/www/mysql_password";

/* Web Variables - NO BACKSLASH */ 
// Host
$host = $_SERVER["HTTP_HOST"];
// Server - DO NOT CHANGE
$server = "http://$host";
$server_path = "$www"; //$_SERVER["DOCUMENT_ROOT"]
// Admin Panel
$apanel = "$server/apanel";
$apanel_path = "$home/admin/www";
?>

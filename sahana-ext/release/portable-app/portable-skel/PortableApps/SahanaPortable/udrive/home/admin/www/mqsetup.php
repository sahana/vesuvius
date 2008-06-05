<?
// Resets cookie to keep phpMyAdmin happy after restarting server with browser still running
// Note: name must be phpMyAdmin value anything I am using FALSE path as set in original cookie
// setcookie('phpMyAdmin', 'FALSE', false, '/apanel/phpMyAdmin/', false, 0); // set cookie
setcookie('phpMyAdmin', 'FALSE', true, '/apanel/phpMyAdmin/', false, 0); // reset cookie
/*
####################################################
# Name: The Uniform Server Setup
# Developed By: The Uniform Server Development Team
# Modified Last By: Olajide Olaolorun (empirex)
# Web: http://www.uniformserver.com
# MPG Test code V0.1 23-6-07
####################################################
*/

// Includes
include "includes/config.inc.php";
include "$apanel_path/includes/lang/".file_get_contents("includes/.lang").".php";
include "includes/header.php";
include "includes/secure.php";


if ( !(file_exists($mysqlpwd)) ) {
    $FHandle = fopen($mysqlpwd, 'w');
    fclose($FHandle);
}


if ($_POST['submit']) {

//get old password
    $tfile = fopen($mysqlpwd, "r");
    $oldpass = fgets($tfile);

//read and set new password
    $nwpass = $_POST['qpass'];
    $urdata = "$nwpass";

// Database configuration
$dbhost = 'localhost';    //server name localhost
$dbuser = 'root';         //User name default root
$dbpass = $oldpass;       //Set to old Password
$dbname = 'mysql';        //database name

// Open database  
$conn = mysql_connect($dbhost, $dbuser, $dbpass) or die('Error connecting to mysql');
mysql_select_db($dbname) or die('Cannot select database');

// Create query string (not sure if you need to flush privs)
$query = 'SET PASSWORD FOR \'root\'@\'localhost\' = PASSWORD(\'' . $nwpass . '\')';
$result = mysql_query($query);

// Close database
mysql_close($conn);

//Crude test
if($result){
//echo "MySQL DB Updated";

//Assume database was updated write new password into file
    $wfile = fopen($mysqlpwd, 'w');
    fwrite($wfile, $urdata);
    fclose($wfile);
}
else{
//Database not written no need to change file  
echo "MySQL DB failed to update";

}

//echo"Old password = $oldpass";

?>

    <div id="main">
    <h2>» <?=$US['mqsetup-head']?></h2>
    <h3><?=$US['mqsetup-sub-0']?></h3>
    <p>
    <?=$US['mqsetup-success']?>
    <br />
    <br />
    <?=$US['mqsetup-pass']?>: <?=$_POST['qpass'];?>
    </p>
    </div>

<?
}

else {
    $tfile = fopen($mysqlpwd, "r");
    $fcontents = fgets($tfile);
?>

    <div id="main">
        <h2>» <?=$US['mqsetup-head']?></h2>
        <h3><?=$US['mqsetup-sub-0']?></h3>

        <p><?=$US['mqsetup-text-0']?></p>
        <form action="<?=$PHP_SELF?>" method="post">
        <table width="100%">
        <tr>
        <td width="100">
        <p><?=$US['mqsetup-pass']?></p>
        </td>
        <td>
        <input type="text" name="qpass" value="<?=$fcontents?>" />
        </td>
        </tr>
        </table>
        <br />
        <input type="submit" name="submit" value="<?=$US['mqsetup-change']?>" />
        </form>
    </div>

<?
    fclose($tfile);
}

// Footer
include "includes/footer.php";
?>
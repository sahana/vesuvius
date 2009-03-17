<?php

/**
* A simple web front-end for PHPunit. A complete hack
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

define('debug_show_queries', false);

error_reporting(E_ALL ^ E_NOTICE);
ini_set("display_errors", "1");

global $global,$dao;
$global=array('approot'=>realpath(dirname(__FILE__)).'/../../../');
require_once($global['approot'].'mod/vm/main.inc');

// Define the correct constants for your DB here.
define (TEST_DB_HOST,"storage1");
define (TEST_DB_NAME,"sahana2_summer07_testing");
define (TEST_DB_USER,"sahana_admin");
define (TEST_DB_PASSWD,"trysahana");

//define ('TEST_DB_HOST',"localhost");
//define ('TEST_DB_NAME',"sahana");
//define ('TEST_DB_USER',"root");
//define ('TEST_DB_PASSWD',"");

$test = $_REQUEST['test'];
$title = empty($test)? 'RunTest' : $test;
?>
<html>
	<head>
		<title><?php echo $title?></title>
		<style type="text/css">
			.ok {
				color: #0c0;
				font-weight: bold;
			}

			.fail {
				color: #c00;
				font-weight: bold;
			}
		</style>
	</head>
	<body>
<h2><?php echo $title?></h2>
<p>
The following unit tests are available:
<ul>
	<li>ProjectControllerTest tests the VM module's main project controller.</li>
	<li>ValidationTest tests the VM module's input validation functions, such as dates and times.</li>
	<li>daoTest tests database queries.</li>
</ul>
Click on the name of a test to run it. Click on the link next to a test to view its source code.<br />
<i>Note:</i> the database tests are very query-intensive, and refreshing quickly can lead to concurrency issues with our
current setup. Please click once and wait for the test to complete.
</p>
<?php

foreach(glob(sql_regcase("*test*")) as $file)
	if(stristr($file, 'test') && !stristr('RunTest.php,TestIncludes.php', $file)) {
		$name = str_replace('.php', '', $file);
		echo "<a href=\"RunTest.php?test=$name\">$name</a> ";
		echo "<small>(<a href=\"RunTest.php?source=$name\">view unit test source</a>)</small><br />";
	}

?>
<br />
<form action="RunTest" method="get">
	<label for="test">Test name: </label>
	<input type="text" name="test" id="test" value="<?php echo $test; ?>"/>
	<input type="submit" value="Run" />
</form>
<?php

if(isset($_GET['source'])) {
	echo "<b><tt>Source listing for $name.php</tt></b><br />";
	highlight_file($_GET['source'].'.php');
	die;
}
$name = $test;
if(!empty($test)) {
	if(!file_exists($test))
		$test .= '.php';
	if(file_exists($test)) {
		require_once('TestIncludes.php');
		require_once "PHPUnit/Framework/TestCase.php";
		require_once "PHPUnit/Framework/TestSuite.php";
		require_once "PHPUnit/TextUI/TestRunner.php";
		echo '<big><pre>';
		echo "running $name...\n";
		ob_start();
		include($test);
        $suite  = new PHPUnit_Framework_TestSuite($name);
        $result = PHPUnit_TextUI_TestRunner::run($suite);
		$out = htmlentities(ob_get_clean());
		$out = preg_replace('/(OK.*)/', "<span class=\"ok\">$1</span>", $out);
		$out = preg_replace("/(FAILURES.*)/", "<span class=\"fail\">$1</span>", $out);
		$out = preg_replace("/(Failed asserting that.*)/", "<span class=\"fail\">$1</span>", $out);
		echo $out;
		echo '</pre></big>';
	} else {
		echo "$test not found";
	}

}
?>
	</body>
</html>

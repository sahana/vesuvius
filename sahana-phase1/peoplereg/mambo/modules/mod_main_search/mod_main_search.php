<?php
/**
* @package Mambo_4.5.1
* @copyright (C) 2004 Virtusa Corporation
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL
*/

/** ensure this file is being included by a parent file */
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

if (!defined( '_MOS_MAIN_SEARCH_MODULE' )) {
	/** ensure that functions are declared only once */
	define( '_MOS_MAIN_SEARCH_MODULE', 1 );

?>
	<form method="get" action="index.php">
		<input type="hidden" name="option" value="com_report">
		<input type="hidden" name="type" value="search">
		<input type="text" name="q"><br />
		<input type="submit" value="Search for people!"><br />
	</form>
	<a href="/">Sahana home page</a><br />
	<a href="/mambo/index.php">People registry home page</a><br />
	<? if ($my->id) { ?>
	<a href="/mambo/index.php?option=com_report&amp;step=0">Add new entry</a><br />
	<? } else { ?>
	<a href="/mambo/index.php?option=com_report&amp;step=0">Report a missing person</a><br />
	<? } ?>
	<a href="/mambo/index.php?option=com_weblinks&catid=69&Itemid=43">Important links</a><br />
	<a href="/mambo/index.php?option=com_content&amp;task=section&amp;id=4&Itemid=41">Statistics and charts</a><br />
	<a href="/mambo/index.php?option=com_content&task=view&id=22&Itemid=45">Confused? See the FAQ</a><br />
	<br />
	<?php
}
?>


<?php
/**
* @package Mambo_4.5.1
* @copyright (C) 2004 Virtusa Corporation
* @license http://www.gnu.org/copyleft/gpl.html GNU/GPL
*/

/** ensure this file is being included by a parent file */
defined( '_VALID_MOS' ) or die( 'Direct Access to this location is not allowed.' );

if (!defined( '_MOS_SUMMARY_STATS_MODULE' )) {
	define( '_MOS_SUMMARY_STATS_MODULE', 1 );

	#$database->setQuery('select count(*) from sahana_entities');
	$database->setQuery('select count(distinct related_id) from sahana_entity_relationships');
	$entities = $database->loadResult();

	echo '<b>Total families : ' . $entities . '</b>';
	echo '<ul>';



	echo '</ul>';
}

?>

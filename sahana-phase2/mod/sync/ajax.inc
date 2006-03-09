<?php
/* $Id: ajax.inc,v 1.1 2006-03-09 09:17:32 janakawicks Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    <package>
 * @subpackage <subpackage>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */

function shn_sync_ajax_addnew($url)
{
    $result = new xajaxResponse();
    $result->addAppend('sync_dsc_list','innerHTML','Hello');
    return $result->getXML;
}

?>

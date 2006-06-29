<?php
/* $Id: home.inc,v 1.2 2006-06-29 06:06:28 thushari Exp $ */

/** 
 * Home Page of the Data Import Module 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
?>
<div id="home">
<h2><?= _('Data Import'); ?></h2>
<!-- <img src="theme/default/img/mpr.png"/> -->
<p><?= _('This module intelligently import and merge external data sources into Sahana. Initially we concentrate on importing disaster data which is in comma-seperated-value(CSV) type file format.'); ?>
<?= _('Features Include:');?></p>


<ul>
    <li><?= _('Upload File:allows to easily upload information which are related to people (victims) from other external data files which must be in comma-separated-values format (CSV) into Sahana'); ?></li>
    <li><?= _('Matching:provide intelligent mapping of import data fields with Sahana data fields.'); ?></li>
    <li><?= _('Preview: Preview the result of the matching process '); ?></li>
    <li><?= _('Summary: Dispaly result of the process'); ?></li>
</ul>
</div>


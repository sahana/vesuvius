<?php
/** 
 * Home Page of the Reporting System. 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

    ?>
    <div id="home">
    <h2><?= _('Reporting System'); ?></h2>
    <div><p><?= _('The Reporting System helps to generate reports based on sahana database. It aggregates all the module reports in one place for making easier the user to view, search reports and charts. On the other hand it performs as the administrator interface for sahana module reports.'); ?></p></div>

    <br></br>
    <div><h3><b><em><?= (_("Features Include:")) ?></em></b></h3></div>
    <ul>
    <li><b><?= _('Module Reports Aggregator'); ?> </b><?= _(' - Aggregates all the module reports. This will show a detail view of each module report.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=sample"><b><?= _('Generate Sample Reports'); ?></b></a><?= _(' - Enables user to generate module based reports which are relavent to the sahana database or custom reports which are not relavent to sahana database.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=search"><b><?= _('Report/Chart Search'); ?> </b> </a><?= _(' - Enables user to search reports and charts.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=config"><b><?= _('Configuration'); ?></b></a><?= _(' - Enables to configure the frequency of updating modules reports and charts.'); ?></li>
    </ul>

</div>





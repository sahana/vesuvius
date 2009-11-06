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
    <h2><?php echo  _t('Reporting System'); ?></h2>
    <div><p><?php echo  _t('The Reporting System helps to generate reports based on sahana database. It aggregates all the module reports in one place for making easier the user to view, search reports and charts. On the other hand it performs as the administrator interface for sahana module reports.'); ?></p></div>

    <br></br>
    <div><h3><b><em><?php echo  (_t("Features Include:")) ?></em></b></h3></div>
    <ul>
    <li><b><?php echo  _t('Module Reports Aggregator'); ?> </b><?php echo  _t(' - Aggregates all the module reports. This will show a detail view of each module report.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=sample"><b><?php echo  _t('Generate Sample Reports'); ?></b></a><?php echo  _t(' - Enables user to generate module based reports which are relavent to the sahana database or custom reports which are not relavent to sahana database.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=search"><b><?php echo  _t('Report/Chart Search'); ?> </b> </a><?php echo  _t(' - Enables user to search reports and charts.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=config"><b><?php echo  _t('Configuration'); ?></b></a><?php echo  _t(' - Enables to configure the frequency of updating modules reports and charts.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=dnd_table"><b><?php echo  _t('Reports from one table'); ?></b></a><?php echo  _t(' - User can generate and export reports from one table at a time.'); ?></li>
    <li><a href="index.php?mod=rs&amp;act=dnd_multiple_table"><b><?php echo  _t('Reports from several tables'); ?></b></a><?php echo  _t(' - User can generate and export reports from several tables at a time.'); ?></li>
    </ul>
    <div><h3><b><em><?php echo _('Supported File formats &amp; Extentions :')?></em></h3></div>
<?php
//print a list of available file formats
    global $dieconf;
    echo "<ul>";
    foreach($dieconf['formats'] as $key=>$format){
        echo "<li>";
        echo $format;
        echo "&nbsp;&nbsp;&nbsp;( ";
        foreach($dieconf['extentions'][$key] as $extention)
                echo " .$extention ";
        echo " )</li>";
    }
    echo "<li> PDF format  (.pdf)</li>";
    echo "<li> ODS - OpenDocument spreadsheet  (.ods)</li>";
    echo "</ul>";
?>
</div>





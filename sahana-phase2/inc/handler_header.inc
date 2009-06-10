<?php
/* $Id: handler_header.inc,v 1.21 2009-06-10 19:55:08 gmiernicki Exp $ */
/**
 *
 * Sahana HTML footer
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage form
 * @author     Chamindra de Silva (chamindra@opensource.lk>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
?>
    <div id="header" class="clearfix">
        <?php  ?>
        <h1><?php echo _t("Sahana FOSS Disaster Management System")?></h1>
        <?php 
            global $conf;
            if(file_exists($global['approot'].'conf/sysconf.inc.php'))
            {
                shn_db_get_incident_select();
                _shn_lc_lang_list(); 
            }
        ?>
    </div>
    <!-- /header -->



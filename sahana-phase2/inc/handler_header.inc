<?php 
/* $Id: handler_header.inc,v 1.16 2006-11-13 17:46:26 chamindra Exp $ */
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
        <h1><?=_("Sahana FOSS Disaster Management System")?></h1>
        <?php 
            global $conf;
            if(file_exists($global['approot'].'conf/sysconf.inc'))
            {
                _shn_lc_lang_list(); 
               #shn_db_get_incident_list();
               shn_db_get_incident_select();
            }
        ?>
    </div>
    <!-- /header -->



<?php
/* $Id: handler_component.php,v 1.7 2009-08-22 17:17:25 ravithb Exp $ */

/**
 *
 * This is simple component handler that creates a box where you can 
 * put some informations, great for watches.. Still under development..
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage zz_deprecated
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @todo make is better
 */

/**
 * 
 * Shows the component box 
 *
 * @param body $body 
 * @param string $title 
 * @param string $options 
 * @access public
 * @return void
 */
function show_component($body, $title='Component', $options=array('title'=>true))
{
    global $conf;
?>
<!-- Component Begin -->
<div>
    <!-- Component Title Begin -->
    <table cellpadding=0 cellspacing=0>
    <tr>
    <td class="com_title">
    <?php echo  ($options['title']?''.$title.
    '</td><td class="com_title" align="right"><img src="theme/'.$conf['theme'].'/img/x.gif"></td>'
    :''); ?>
    </tr>
    <!-- Component Title End -->
    <tr height="5px"><td colspan="2"></td></tr>
    <!-- Body Content Begin -->
    <tr><td colspan="2">
    <?php echo  $body; ?>
    </td>
    </tr>
    <!-- Body Content End -->
    </table>
</div>
<!-- Component End -->
<?php
}


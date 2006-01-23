<?php
/* $Id: handler_component.php,v 1.2 2006-01-23 11:05:05 janakawicks Exp $ */

/**
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
 * show_component 
 * 
 * @param mixed $body 
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
    <?= ($options['title']?''.$title.
    '</td><td class="com_title" align="right"><img src="theme/'.$conf['theme'].'/img/x.gif"></td>'
    :''); ?>
    </tr>
    <!-- Component Title End -->
    <tr height="5px"><td colspan="2"></td></tr>
    <!-- Body Content Begin -->
    <tr><td colspan="2">
    <?= $body; ?>
    </td>
    </tr>
    <!-- Body Content End -->
    </table>
</div>
<!-- Component End -->
<?php
}
?>

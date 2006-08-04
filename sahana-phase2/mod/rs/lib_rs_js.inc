<?php
/**
 * Lib rs javascript
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author       Sanjeewa Jayasinghe <sditfac@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage rs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

function shn_sample_change_form()
{
?>
<script type="text/javascript">
    function changeform()
    {
    var x=document.mod_select.mod_name.options[document.mod_select.mod_name.selectedIndex].value;
    if(x!='none')
        {
        document.mod_select.submit();
        }
    }
</script>
<?php
}
?>
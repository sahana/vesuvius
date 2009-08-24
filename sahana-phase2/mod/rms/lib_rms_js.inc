<?php
/**
* The Sahana Resquest Management System
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		sahana
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_rms_js_requester($newreqstr=false)
{
?>
<script language="JavaScript" type="text/javascript">
    function hideNewReqster()
    {
        document.getElementById('reqstr_new').style.visibility = 'hidden';
    }
    
    function showNewReqster()
    {
    	    var id = document.getElementById('reqstr_id');
        id.getElementsByTagName('form')[0].reqstr_id.disabled = true;
        id.getElementsByTagName('form')[0].reqstr_next.disabled = true;
        //document.getElementById('reqstr_id').style.visibility = 'hidden';
        document.getElementById('reqstr_new').style.visibility = 'visible';
    }
<?php
    if($newreqstr)
        print "showNewReqster();";
    else
        print "hideNewReqster();";
?>
</script>
<?php
}

function _shn_rms_js_category()
{
?>
<script language="JavaScript" type="text/javascript">
    function selectCat()
    {
        var id = document.getElementById('item_new');
        id.getElementsByTagName('form')[0].cat_sel.value = "true";
        id.getElementsByTagName('form')[0].submit();
    }
</script>
<?php
}

function _shn_rms_js_donor($newdonor=false)
{
?>
<script language="JavaScript" type="text/javascript">
    function hideNewDonor()
    {
        document.getElementById('donor_new').style.visibility = 'hidden';
    }
    
    function showNewDonor()
    {
        var id = document.getElementById('donor_id');
        id.getElementsByTagName('form')[0].donor_id.disabled = true;
        id.getElementsByTagName('form')[0].donor_next.disabled = true;
        document.getElementById('donor_new').style.visibility = 'visible';
    }
<?php
    if($newdonor)
        print "showNewDonor();";
    else
        print "hideNewDonor();";
?>
</script>
<?php
}
?>

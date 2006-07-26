<?php
/**
* The Sahana Resquest Management System
* Ajax Library for the RMS
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

function _shn_rms_ajax_init($replace_block)
{
?>

<script language="JavaScript" type="text/javascript">

var http_request = false;

function replaceContent() 
{
    if (http_request.readyState == 4)
    {
        if (http_request.status == 200)
        {
            //alert(http_request.responseText);
            result = http_request.responseText;
            document.getElementById('<?=$replace_block?>').innerHTML = result; 
        }
        else
        {
            alert(http_request.status + 'There was a problem with the request.');
        }
    }
    
}

function makeRequest(url, parameters)
{
    http_request = false;
    if (window.XMLHttpRequest)
    {
        http_request = new XMLHttpRequest();
        if (http_request.overrideMimeType)
        {
            http_request.overrideMimeType('text/xml');
        }
    }
    else if (window.ActiveXObject)
    {
        try
        {
            http_request = new ActiveXObject("Msxml2.XMLHTTP");
        }
        catch (e)
        {
            try
            {
                http_request = new ActiveXObject("Microsoft.XMLHTTP");
            }
            catch (e) {}
         }
    }
      
    if (!http_request)
    {
        alert('Cannot create XMLHTTP instance');
        return false;
    }

    http_request.onreadystatechange = replaceContent;
    http_request.open('GET', url + parameters, true);
    http_request.send(null);
}

</script>

<?php
}
?>
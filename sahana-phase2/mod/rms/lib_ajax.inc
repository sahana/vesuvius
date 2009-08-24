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

function _shn_rms_ajax_init($replace_block1, $replace_block2)
{
?>

<script language="JavaScript" type="text/javascript">

var http_request = false;
var block;

function replaceContent() 
{
    if (http_request.readyState == 4)
    {
        if (http_request.status == 200)
        {
            //alert(http_request.responseText);
            result = http_request.responseText;
            if(block == 'cat'){
            document.getElementById('<?=$replace_block1?>').innerHTML = result;
            document.getElementById('<?=$replace_block2?>').innerHTML = ""; 
            document.getElementById('itm_unit').innerHTML = ""; 
            document.getElementById('qty').value = "";
            }
            else{
            	if(block == 'subcat'){
            		document.getElementById('<?=$replace_block2?>').innerHTML = result;
            		document.getElementById('itm_unit').innerHTML = "";
            		document.getElementById('qty').value = ""; 
            	}
            }
        }
        else
        {
            alert(http_request.status + 'There was a problem with the request.');
        }
    }
    
}

function ct_list() 
{
    if (http_request.readyState == 4)
    {
        if (http_request.status == 200)
        {
            //alert(http_request.responseText);
            result = http_request.responseText;
            document.getElementById('sub_cat').innerHTML += result; 
        }
        else
        {
            alert(http_request.status + 'There was a problem with the request.');
        }
    }
    
}

function showUnit() 
{
    if (http_request.readyState == 4)
    {
        if (http_request.status == 200)
        {
            //alert(http_request.responseText);
            result = http_request.responseText;
            document.getElementById('itm_unit').innerHTML = result; 
            document.getElementById('qty').value = "";
        }
        else
        {
            alert(http_request.status + 'There was a problem with the request.');
        }
    }
    
}

function makeRequest(url, parameters, cat, callback)
{
    http_request = false;
    block = cat;
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
    
    if (callback==null)
    {
        http_request.onreadystatechange = replaceContent;
    }
    else
    {
    	http_request.onreadystatechange = callback;
    }
    http_request.open('GET', url + '&par='+parameters, true);
    http_request.send(null);
}

</script>

<?php
}
?>
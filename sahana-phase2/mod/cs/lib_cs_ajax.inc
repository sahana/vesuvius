<?php
/**
 * AJAX Library of catalog system  
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
 * @subpackage cs
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

/**
 * This function prints the ajax function to get an array of unit list in add.inc
 * called in shn_cs_additem_form1_result() in add.inc
 * @access private
 * @return void
 */
function shn_cs_additem_form1_result_ajax()
{
?>
<script type="text/javascript">
    var url = "index.php?"; 
     var http;
        
    function getHTTPObject() 
    {
        var xmlhttp;
        
        //conditional compliation
        /*@cc_on
        @if (@_jscript_version >= 5)
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
        @else
            xmlhttp = false;
        @end @*/

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();

            } catch (e) {
            xmlhttp = false;
            }
        }

    return xmlhttp;
    }

function handleHttpResponse(){
        if (http.readyState == 4) 
    { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
                if (results[0]!="null")
            {                
                var x=document.getElementsByName('unit_select[]');

                    for (i=0; i<=x[0].options.length+1; i++)
                    {
                            x[0].options[0]=null;
                            }

                j=0;
                for (i=1; i<results.length-1; i=i+2, j++)
                    {
                    //alert(results[i]);
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                          x[0].options[j] = opt;
                            }
                    }
        } 
    }

    function change_units(selection){
    
        http = getHTTPObject();

        var url2=url + "act=unit_cat&mod=xst&stream=text&cat="+selection;
          http.open("GET", url2, true); 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
</script>
<?php
}

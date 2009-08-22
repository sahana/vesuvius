<?php
/**
 * Library containing ajax functions for synchronization servers
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     J P Fonseka <jo@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage sync
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

/**Function connect to a sahana server and get details
 * @param form_data
 * @return string  - xajax out put
 */

function _shn_server_ajax_connect($url){
    _print_xajax_headers();
    echo "<cmd n='as' t='status' p='innerHTML'><![CDATA[";
    global $global;
    $para="?mod=sync&act=info&stream=text";
    try{
        $xml=file($url.$para);
    } catch (Exception $e) {
    echo 'Caught exception: ',  $e->getMessage(), "\n";
    }
    $connect=$xml;
//access the web service
    if($connect){
?>
        <ul><li>Instance ID:<?php echo $xml[0]?></li>
                <li>Owner:<?php echo $xml[1]?></li>
                <li>Contact:<?php echo $xml[2]?></li>
                </ul>
        <form action="" method="post">
                <input type="submit" value="Add Server">
        </form>
<?php
        //$global['xajax']->addAssign("status", "innerHTML", $html);
    }
    else{
?>
        <b>Can not connect to server...</b><br/>
        <form action='#' onSubmit='connect(\"".$url."\");return false;'><input type='submit' value='Retry'></form>
<?php
    }
    echo "]]></cmd>";
    _print_xajax_close();
}



function _print_xajax_headers(){
        header("Content-type: text/xml");
        header("Cache-Control: no-cache, must-revalidate");
        echo "<?xml version='1.0' ?>";
        echo "<xjx>";
}

function _print_xajax_close(){
    echo "</xjx>";
    exit(0);
}


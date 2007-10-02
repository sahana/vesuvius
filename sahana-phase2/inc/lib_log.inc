<?php
/**
* Sahana logging and cronology library
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    framework
* @subpackage logging 
* @author     Chamindra de Silva <chamindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/


include_once($global['approot'].'inc/lib_uuid.inc');
include_once($global['approot'].'inc/lib_form.inc');


function shn_log_form($UUID)
{


}

/**
 * shn_log_event 
 * 
 * @param string UUID 
 * @param string action
 * @param string message
 * @param string details
 * @return void
 */
function shn_log_event($UUID,$comments,$date=null,$details=null)
{
 
    global $conf, $global;

    $datetime = ($date)? $date : date("Y-m-d H:i:s");

    $sql['event_date'] = $datetime;
    $sql['user_uuid'] = $_SESSION['userid']; 
    //$userlogid=$_SESSION['userlogid'];
    $sql['module'] = $global['module'];
    $sql['log_uuid'] = shn_create_uuid('log');
    $sql['opt_cron_type'] = 'cron';
    $sql['pgoc_uuid'] = $UUID;
    $sql['comments'] = $message;
    $sql['action'] = $global['action'];
    $sql['details'] = $details;

    shn_db_insert($sql,'chronology'); 
}


function shn_log_display($UUID=null)
{
    global $global;
    global $conf;

?>
    <div id="result">
    <table>
    <thead>
<?php
    shn_form_table_row(array('Date/Time','Module:Action','By User','Comments'));
?> 
    </thead>
<?php
    $sql = "SELECT event_date,action,module,user_uuid,comments,pgoc_uuid from chronology
            WHERE pgoc_uuid = '$UUID' 
            ORDER BY event_date DESC";
    add_warning("UUID is $sql");
    $rs = $global['db']->Execute($sql);
    if ($rs) {
        while ($arr = $rs->FetchRow()) {

            $act = shn_breadcrumb_get_nicename($arr[2], $arr[1]);
            $mod = $conf['mod_'.$arr[2].'_name'];

            shn_form_table_row(array($arr[0],$mod.':'.$act,$arr[3],$arr[4]));
        }
    }
?>
    </table>
    </div>
<?php
}

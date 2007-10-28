<?php
/**
 *  
 * This is a generic error handler, you can create and manage a error container
 * and display the errors.
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage errors
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @author     Chamindra de Silva <chaindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

// The following are three global containers to hold the messages or 
// confirmation, warning and error following a submit
$global['submit_errors'] = array();
$global['submit_warnings'] = array();
$global['submit_confirmations'] = array();

function add_warning($warning)
{
	global $global;
    array_push($global['submit_warnings'],$warning);
}	

function add_confirmation($confirmation)
{
	global $global;
    array_push($global['submit_confirmations'],$confirmation);
}	

// this function will display the submit message of a 
// certain type as contained in the container specified by the type
// @TODO: add generic check for container existance
function display_submit_message($type = 'warning',
              $msg = 'please note the following:')
{
    global $global;
    $container = 'submit_'.$type.'s';

    // return if there are no errors
    if (count($global[$container]) == 0 ) return;
?>
    <div class="<?=$type?> message">
     <p><em><?=$msg?></em></p>
     <ul>
<?php
	foreach ($global[$container] as $i){
		echo '<li>'.$i.'<br></li>';
	}
?>
     </ul>
    </div>
<?php
	$global[$container] = null;
}


/**
 * If you want to display the errors call this function.  
 */
function display_errors($error_title=null,$return=false,$clean_errors=true)
{
    global $global;

    if (null == $error_title) {
        $error_title = _('Oops. There are few errors :');
    }

    // return if there are no errors
    if (count($global['submit_errors']) == 0 ) return;
    
    $output = "<div class=\"error message\">";

    $output .= '<p><em>'.$error_title.'</em><p>';

    $output .= "<ul>";
	foreach ($global['submit_errors'] as $error){
		$output .= "<li>"._($error).'<br></li>';
	}
    $output .= "</ul>";
    $output .= "</div>";

    //Clean Errors
	if($clean_errors)
        clean_errors();

    if($return)
        return $output;
    else{
        echo $output;
        return 1;
    }
}


function add_error($error)
{
	global $global;
    if(is_array($error))
    	array_push($global['submit_errors'],$error);
    else
        $global['submit_errors'][] = $error;
}	

function clean_errors()
{
	global $global;
	$global['submit_errors'] = NULL;
}

function is_errors()
{
    global $global;
    if(empty($global['submit_errors']))
        return false;
    else
        return true;
}

function shn_error_display_restricted_access($msg=null)
{ ?>
    <div class="error message">
    	
        <p><em><?=_('Sorry, you do not have permisssion to access this section')?></em><br/>
        <?php if($msg!=null){?>
        <br /><strong><?=$msg?></strong><br /><br />
        <?php }?>
        <?=_('This could be because:')?>
        <ul>
        <li><?=_('You have not logged in or Anonymous access is not allowed to this section')?></li>
        <li><?=_('Your username has not been given permission to access this section')?></li>
        </ul>
        <p><?=_('To gain access to this section please contact the administrator')?></p>
    </div> <!-- /error -->
<?php
}

function shn_error_dummy_header() 
{
global $global;
?>
    <body>
    <div id="container">
    <div id="header" class="clearfix">
        <h1><?=_("Sahana FOSS Disaster Management System")?></h1>
    </div>
    <div id="wrapper" class="clearfix">
    <div id="content" class="clearfix">      
<?php
}

function shn_error_dummy_footer()
{
global $global;
?>
    </div> <!-- /content -->
<?php
    include($global['approot'].'inc/handler_footer.inc');
?>
    </div> <!-- /wrapper -->
    </div> <!-- /container -->
    </body>
    </html>
<?php
}

/**
 * Sahana's custom PHP error handler
 * 
 * @param int $errorno 
 * @param string $errmsg 
 * @param string $filename 
 * @param int $linenum 
 * @param array $vars 
 * @access public
 * @return void
 */
function shn_sahana_error_handler($errno, $errmsg, $filename, $linenum, $vars) 
{
    global $global;

    switch ($errno) {

        // Decide which errors you want the system to report actively. 
        // The ones uncommented are reported

        case E_ERROR:              // Fatal run-time errors
        case E_WARNING:            // Run-time warnings (non-fatal errors)
        case E_PARSE:              // Compile-time parse errors
        //case E_NOTICE:           // Run-time notices.
        case E_CORE_ERROR:         // Fatal errors that occur during PHP's initial startup
        //case E_CORE_WARNING:     // Warnings (non-fatal errors) that occur during PHP's initial startu
        case E_COMPILE_ERROR:      // Fatal compile-time errors
        // case E_COMPILE_WARNING: // Compile-time warnings (non-fatal errors
        case E_USER_ERROR:         // User-generated error messages
        //case E_USER_WARNING:     // User-generated warning messages
        //case E_USER_NOTICE:      // User-generated notices

            shn_error_analyze_and_display_help($errno, $errmsg, $filename, $linenum, $vars);
            break;

        default:                   // Ignore other errors
    }
}

/**
 * Intelligent analysis of error message and environmental conditions and reporting
 * of probable error in user friendly terms
 * 
 * @param int $errno 
 * @param string $errmsg 
 * @param string $filename 
 * @param int $linenum 
 * @param array $vars 
 * @access public
 * @return void
 */

function shn_error_analyze_and_display_help($errno, $errmsg, $filename, $linenum, $vars)
{
    global $global;
    global $conf;

    include_once($global['approot'].'conf/sysconf.inc');

    //add_error("the error message was ".$errmsg);
    //echo "the error message was ".$errmsg;
    if ($conf['debug']) {
        add_warning('Error Message :'.$errmsg);
        add_warning('Filename '.$filename.' at line '.$linenum); 
        //add_warning($vars); 
    }

    // analyse error message
    if (preg_match("/Can't connect to local MySQL/",$errmsg)) {
        add_error(_('The Sahana database is currently inaccesible'));
    } else {
        if ($errno == E_WARNING ) {   
            return; 
        } else {
            add_error(_('The system is currently unavailable'));
        }
    }

    $included_files = get_included_files();

    foreach ($included_files as $filename) {

        // calculate at what output stage the error happened so we know what remains to output (HTML)
        if (preg_match('/handler_html_head.inc/', $filename)) $output_stage['html_header'] = 'passed';
        if (preg_match('/handler_header.inc/', $filename)) $output_stage['header'] = 'passed';
        if (preg_match('/handler_footer.inc/', $filename)) $output_stage['footer'] = 'passed';
    }

    if (!isset($_REQUEST['stream'])) { // If error happened in an HTML stream

        // Complete the page based on where the error happened
        if ( $output_stage['html_header'] != 'passed' ) {
            require_once ($global['approot'].'inc/handler_html_head.inc');
        }
        if ( $output_stage['header'] != 'passed' ) {
            shn_error_dummy_header();
        }

        display_errors(_('System Error'));
        if ($conf['debug']) {
            display_submit_message('warning','Technical Error Details');
        }

        if ($conf['root_name'] != '') {
            echo '<br/>'._('For urgent assistance, please contact the system administrator below:');
            echo '<br/>'._('Name: ').$conf['root_name'].
                   '.<br/>Email: '.$conf['root_email'].' Telephone: '.$conf['root_tel'];
        }

        if ( $output_stage['footer'] != 'passed' ) {
            shn_error_dummy_footer();

            //ob_flush();  // At the end of the stream it flushes anyway
        }

    }
    exit(0);

}

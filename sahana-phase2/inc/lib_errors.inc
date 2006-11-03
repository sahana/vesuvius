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
 * @package    framework
 * @subpackage presentation
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
    <div id="<?=$type?>">
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
function display_errors($return=false,$clean_errors=true,$exit=false)
{
    global $global;

    // return if there are no errors
    if (count($global['submit_errors']) == 0 ) return;
    
    $output = "<div id=\"error\">";
	if($exit){
//		$output .= '<b>'._('O my god you killed Kenny !!!').'</b><br>'; 
	}else{
        $output .= '<p><em>'._('Oops. There were a few errors :').'</em><p>';
	}
    $output .= "<ul>";
	foreach ($global['submit_errors'] as $error){
		$output .= "<li>"._($error).'<br></li>';
	}
    $output .= "</ul>";
    $output .= "</div>";

    //Clean Errors
	if($clean_errors)
        clean_errors();

	if($exit)
		exit(1);
	else{
        if($return)
            return $output;
        else{
            echo $output;
		    return 1;
        }
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

function shn_error_display_restricted_access()
{ ?>
    <div id="error">
        <p><em><?=_('Sorry, you do not have permisssion to access this section')?></em>.<br/><br/><?=_('This could be because:')?></ul>
        <ul>
        <li><?=_('You have not logged in or Anonymous access is not allowed to this section')?></li>
        <li><?=_('Your username has not been given permission to access this section')?></li>
        </ul>
        <p><?=_('To gain access to this section please contact the administrator')?></p>
    </div> <!-- /error -->
<?php
}
?>

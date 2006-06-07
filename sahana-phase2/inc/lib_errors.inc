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
 * @author     Chaindra de Silva <chaindra@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */


$error_container = array();

/**
 * If you want to display the errors call this function.  
 *
 * 
 * @param bool $return 
 * @param bool $clean_errors 
 * @param bool $exit 
 * @access public
 * @return mixed
 */
function display_errors($return=false,$clean_errors=true,$exit=false)
{
    global $error_container;

    // return if there are no errors
    if (count($error_container) == 0 ) return;
    
    $output = "<div id=\"error\">";
	if($exit){
//		$output .= '<b>'._('O my god you killed Kenny !!!').'</b><br>'; 
	}else{
        $output .= '<p><em>Oops. There were a few errors :</em><p>';
	}
    $output .= "<ul>";
	foreach ($error_container as $error){
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

/**
 * Insert an error to the container
 * 
 * @param string $error 
 * @access public
 * @return void
 */
function add_error($error)
{
	global $error_container;
    if(is_array($error))
    	array_push($error_container,$error);
    else
        $error_container[] = $error;
}	
/**
 * Insert an error debug message to the container
 * 
 * @param string $file 
 * @param integer $line 
 * @param integer $intNumber 
 * @param string  $strmessage 
 * @access public
 * @return void
 */
function add_error_debug($file,$line,$intNumber,$strmessage)
{
	global $error_container;
	array_push($error_container,array($file,$line,$intNumber,$strmessage));
}
/**
 * Remove an error from the container
 * 
 * @param integer $index 
 * @access public
 * @return void
 * @todo code this function remove_error
 */
function remove_error($index)
{
	
}

/**
 * Clean the error container
 * 
 * @access public
 * @return void
 */
function clean_errors()
{
	global $error_container;
	$error_container = NULL;
}

/**
 * This function will return errors from the error container
 * 
 * @access public
 * @return void
 */
function return_errors()
{
	global $error_container;
	return $error_container;
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


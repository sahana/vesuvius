<?php
/**
* Sahana error library 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Janaka Wickramasinghe <janaka@opensource.lk>
* @author     Chaindra de Silva <chaindra@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

/**
* Error Container
*/

$error_container = array();

/**
 * display_errors 
 * 
 * @param mixed $return 
 * @param mixed $clean_errors 
 * @param mixed $exit 
 * @access public
 * @return void
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
        $output .= '<p><em>Oops. There were a few errors in the form submitted:</em><p>';
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
 * add_error 
 * 
 * @param mixed $error 
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
 * add_error_debug 
 * 
 * @param mixed $file 
 * @param mixed $line 
 * @param mixed $intNumber 
 * @param mixed $strmessage 
 * @access public
 * @return void
 */
function add_error_debug($file,$line,$intNumber,$strmessage)
{
	global $error_container;
	array_push($error_container,array($file,$line,$intNumber,$strmessage));
}
/**
 * remove_error 
 * 
 * @param mixed $index 
 * @access public
 * @return void
 */
function remove_error($index)
{
	
}

/**
 * clean_errors 
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
 * return_errors 
 * 
 * @access public
 * @return void
 */
function return_errors()
{
	global $error_container;
	return $error_container;
}

?>

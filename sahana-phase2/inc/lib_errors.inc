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
* Display Errors
* @param bool $clean_erros clean the error container 
* @param bool $exit Exit the script execution 
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
* Add Errors to the container
* @param string $error Error Message to display
*/
function add_error($error)
{
	global $error_container;
    if(is_array($error))
    	array_push($error_container,$error);
    else
        $error_container[] = $error;
}	
function add_error_debug($file,$line,$intNumber,$strmessage)
{
	global $error_container;
	array_push($error_container,array($file,$line,$intNumber,$strmessage));
}
/** 
* Remove Error from the container
* @param integer $index
* @todo Need to implement
*/
function remove_error($index)
{
	
}

/** 
* Clean the error container
*/
function clean_errors()
{
	global $error_container;
	$error_container = NULL;
}

/**
* Return Errors
*/
function return_errors()
{
	global $error_container;
	return $error_container;
}

?>

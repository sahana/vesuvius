<?php

/**
 * shn_home_default 
 * 
 * @access public
 * @return string
 */
function shn_home_default()
{
$message = _t("
        Welcome to the Sahana FOSS Disaster Management System
        Sahana is an integrated set of pluggable, web based disaster management applications that pr ovide solutions to large-scale humanitarian problems in the aftermath of a disaster. These applications a nd problems they address are as follows:");
    switch ($_GET['stream_type']){
        case 'soap' :
            return $message;
        break;

        case 'xml' :
            return '<description>'.$message.'</description>';
        break;

        default:
            return $message;
        break;

    }
        
}

/**
 * This is a test function
 * 
 * @param string $var1 
 * @param string $var2 
 * @access public
 * @return void
 */
function shn_home_test($var1, $var2)
{

}


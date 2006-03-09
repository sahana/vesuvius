<?php
/* $Id: lib_st_soap.inc,v 1.1 2006-03-09 09:21:13 janakawicks Exp $ */

/**
 *
 * <Description goes here>
 *
 * PHP version 4 and 5
 * * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    <package>
 * @subpackage <subpackage>
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */
 
require_once($global['approot'].'/3rd/nusoap/lib/nusoap.php');

function shn_stream_init($filename)
{
    global $global;
    $global['soap_server'] = new soap_server();
    
    $namespace = 'urn:'.$global['module'];
    $global['soap_server']->configureWSDL($global['module'],$namespace);

    //open the file and create the wsdl file
    $content = file($filename);

    $flag_in = false;
    foreach($content as $line){
        if(preg_match('/\/\*\*/',$line)){
            $flag_in = true;
            $input_param = array();
            $output_param = null;
            $function_name = '';
            $style = 'rpc';
            $use = 'encoded';
            $documentation = null;
        }
        if(preg_match('/function (.*)\(/',$line,$matches) && $flag_in){
            $flag_in = false;
            $function_name = $matches[1];
            $global['soap_server']->register($function_name,
                                            $input_param,
                                            $output_param,
                                            $namespace,
                                            $namespace.'#'.$function_name,
                                            $style,
                                            $use,
                                            $documentation );
        }

        if($flag_in){
            if(preg_match('/ \* @param (.*?)\s+\$(.*)/',$line, $matches))
                $input_param[$matches[2]] = 'xsd:'.$matches[1];
            
            if(preg_match('/ \* @return (.*)/',$line, $matches))
                $output_param = array('return'=>$matches[1]);

            if(preg_match('/ \* (.*)/',$line,$matches) && ! preg_match('/ * @/',$line))
                $documentation .= $matches[1];
        }
    }
}

function shn_stream_close($function,$output)
{
    global $global;

    $HTTP_RAW_POST_DATA = isset($HTTP_RAW_POST_DATA) ? $HTTP_RAW_POST_DATA : '';
    $global['soap_server']->service($HTTP_RAW_POST_DATA);
}

?>

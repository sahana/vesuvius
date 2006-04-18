<?php 
/* $Id: lib_uuid.inc,v 1.8 2006-04-18 11:11:58 jayasinghe Exp $ */

/**
 *
 * This is the library that generates global unique ids. 
 * Each "Sahana" instance will be given a unique id(40) which will be prefixed 
 * to the primary keys.
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage not_define
 * @author     Janaka Wickramasinghe <janaka@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 * @todo       define a subpackage
 */

/**
 * shn_generate_uuid 
 * 
 * @access public
 * @return void
 */
function shn_generate_uuid($width=2)
{
   //random number between 0-36
    for($i=0;$i<$width;$i++){
        if(($num = rand(0,36)) < 27 ) 
            $uuid .= chr($num+97);
        else
            $uuid .= 36 - $num;
    }
    return $uuid;
}
 
/**
 * shn_create_uuid 
 * 
 * @param string $type 
 * @access public
 * @return void
 */
function shn_create_uuid($type='person')
{
    global $conf;
    
    switch ($type){
        case 'person':
        case 'p' :
                $gen_id = 'p-'._shn_gen_id('person');
            break;

        case 'org':
        case 'o' :
        case 'organization':
                $gen_id = 'o-'._shn_gen_id('organization');
            break;

        case 'camp':
        case 'c' :
                $gen_id = 'c-'._shn_gen_id('camp');
            break;

        case 'request' :
        case 'req' :
        case 'r' : 
                $gen_id = 'r-'._shn_gen_id('request');
	break;
	case 'catalogue' :
        case 'cata' :
        case 'ct' : 
                $gen_id = 'ct-'._shn_gen_id('catalogue');
	break;
	case 'unit':
	case 'uni':
        case 'un' : 
                $gen_id = 'un-'._shn_gen_id('unit');
	break;
        default :    

            break;
    }
    
    return $conf['base_uuid'].$gen_id;
}

/**
 * _shn_gen_id 
 * 
 * @param string $type 
 * @access protected
 * @return void
 */
function _shn_gen_id($type='person')
{
    global $global;
    
    $global['db']->CreateSequence($type,1);
    return $global['db']->GenID($type);
}
?>

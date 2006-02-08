<?php 
/* $Id: lib_uuid.inc,v 1.2 2006-02-08 08:19:34 ravids Exp $ */

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

function shn_generate_uuid()
{
    //Sleep for random 2sec = 2000000 milli seconds
    usleep(rand(0,2000000));

    //Get the micro time now and {hash (sha1)} just to make 40 characters wide
    return sha1($microtime());
    
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
                $gen_id = _shn_gen_id('person').'p';
            break;

        case 'org':
        case 'o' :
        case 'organization':
                $gen_id = _shn_gen_id('organization').'o';
            break;

        case 'camp':
        case 'c' :
                $gen_id = _shn_gen_id('camp').'c';
            break;

        case 'request' :
        case 'req' :
        case 'r' :
            break;
                $gen_id = _shn_gen_id('request').'r';
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

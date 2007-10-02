<?php 
/* $Id: lib_uuid.inc,v 1.22 2007-10-02 20:03:41 mifanc Exp $ */

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
 * @package    moduleAPI
 * @subpackage UUID
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
function shn_generate_uuid($width)
{
   //random number between 0-36
    for($i=0;$i<$width;$i++){
        if(($num = rand(1,36)) < 27 ) 
            $uuid .= chr($num+96);
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
    	
        case 'victim_group':
              
              
        $gen_id='gr-'._shn_gen_id('victim_group');
        
        
       // print 'it is'.$gen_id;
        break;
       
        case 'person':
        case 'p' :
                $gen_id = 'p-'._shn_gen_id('person');
                break;
       


        case 'org':
        case 'o' :
       
        
        case 'organization':
                $gen_id = 'o-'._shn_gen_id('organization');
                break;

	    case 'location':
        case 'lc':
        		$gen_id = 'lc-'._shn_gen_id('loc_seq');
        		break;

        case 'landmark':
        case 'l':
        		$gen_id = 'o-'._shn_gen_id('landmark');
        		break;

        case 'log':
                $gen_id = 'lg-'._shn_gen_id('log');
                break;

        case 'camp':
        case 'c' :
                $gen_id = 'c-'._shn_gen_id('camp');
                break;
        		
        case 'gis':
        case 'g':
        		$gen_id = 'g-'._shn_gen_id('gis');
        		break;
		case 'wikimap':
        case 'wm':
        		$gen_id = 'wm-'._shn_gen_id('wikimap');
        		break;

        case 'request' :
        case 'req' :
        case 'r' : 
                $gen_id = 'r-'._shn_gen_id('request');
                break;
    	case 'pledge' :
        case 'pl' :
                $gen_id = 'pl-'._shn_gen_id('pledge');
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

       case 'unit_type':
       case 'unt':
                $gen_id = 'ut-'._shn_gen_id('unit_type');
                break;
       
        case 'report':
        case 'rep':
                $gen_id = 'rpt-'._shn_gen_id('report');
                break;
        
        case 'messaging':
        case 'msg':
                $gen_id = 'msg-'._shn_gen_id('messaging');
                break;

		case 'inventory':
		case 'inv':
		$gen_id = 'inv-'._shn_gen_id('inventory');
		break;
		
		case 'volunteer':
		case 'vm':
		$gen_id = 'vm-'._shn_gen_id('volunteer');
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
    global $conf;
    
    if($conf['db_engine'] == 'mysql'){
    $engine = $conf['mysql_engine'];

    $global['db']->Execute("set storage_engine ='{$engine}'");
    
    }


    $global['db']->CreateSequence($type,1);
    return $global['db']->GenID($type);
}
?>

<?php
/* $Id: contact.inc,v 1.1 2006-03-20 11:26:11 janakawicks Exp $ */

/**
 * Data Import upload file 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	  Thushari Silva <atpsilva@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage imp
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */
require_once ($global['approot'].'mod/imp/utils/array.inc');





class imp_Contact_BAO_Contact  
{
   
    /**
     * static field for all the contact information that we can potentially import
     *
     * @var array
     * @static
     */
    static $_importableFields = null;

   
    function __construct()
    {
      
    }
    
 
    
    /**
     * combine all the importable fields from the lower levels object
     *
     * The ordering is important, since currently we do not have a weight
     * 
     *
     * @param int $contactType contact Type
     * @return array array of importable Fields
     * @access public
     */
    function &shn_imp_imp_per_importableFields( $contactType = 'Individual', $status = null ) {
       global $global;
    // the line below is commented coz,
        // if the importableFields are once set then they do not
        // allow to set with different contactTypes
    
        if ( ! self::$_importableFields || ! imp_Utils_Array::value( $contactType, self::$_importableFields ) ) {
           if ( ! self::$_importableFields ) {
              self::$_importableFields = array();
           }
            if (!$status) {
                $fields = array( 'do_not_import' => array( 'title' =>_('- do not import -')));
            } 

 
         switch ($contactType) { 
	     case 'Individual' : 
		require_once($global['approot'].'mod/imp/Contact/DAO/individual.inc');
                  eval('$tmpFields = array_merge($fields, imp_Contact_DAO_Individual::import( ));');
                   $fields = array_merge( $fields, $tmpFields ); 
		   break; 
	     case 'Organization' : 
		  require_once($global['approot'].'mod/imp/Contact/DAO/Organization.inc');
		   eval('$tmpFields = array_merge($fields, imp_Contact_DAO_Organization::import( ));');
                   $fields = array_merge( $fields, $tmpFields ); 
		   break;
	 } 
	   
      
                     
           
           
           
            self::$_importableFields[$contactType] = $fields;
        }
        return self::$_importableFields[$contactType];
    }

}
   
   
   
    
?>

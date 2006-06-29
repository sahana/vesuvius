<?php
/* $Id: parser_contact.inc,v 1.4 2006-06-29 06:32:01 thushari Exp $ */
/* last modify 2006/03/31  */

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

global $global; 
 require_once($global['approot'].'mod/imp/parser.inc');


/**
 * class to parse contact csv files
 */
 class imp_import_parser_contact extends imp_import_parser {  
    protected $_mapperKeys;  
    protected $_updateWithId;
    protected $_retCode;

    /**
     * Array of succesfully imported contact id's
     *
     * @array
     */
    protected $_newContacts;

    /**
     * Array of succesfully imported related contact id's
     *
     * @array
     */
    protected $_newRelatedContacts;

    /**
     * class constructor
     */
    function __construct( $mapperKeys ) {
       parent::__construct();
        $this->_mapperKeys =& $mapperKeys;
      
    }

    /**
     * the initializer code, called before the processing
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_init( ) {
	global $global;
        include_once($global['approot'].'/mod/imp/contact/bao/contact.inc');
	
        $fields =& imp_Contact_BAO_Contact::shn_imp_imp_per_importableFields($this->_contactType);
	$_SESSION['fields']= $fields; 
	 
	$this->_fields = $fields; 
        
	$_SESSION['headerpattern']= $this->shn_imp_imp_per_getHeaderPatterns();
	$_SESSION['dataPattern'] = $this->shn_imp_imp_per_getDataPatterns() ; 


         foreach ($fields as $name => $field) {
           $this->shn_imp_imp_per_addField( $name, $field['title'], $field['type'], $field['headerPattern'], $field['dataPattern']);
         }

        $this->_newContacts = array();

        $this->shn_imp_imp_per_setActiveFields( $this->_mapperKeys );
      
              
        $this->_updateWithId = false;
        if (in_array('id',$this->_mapperKeys)) {
            $this->_updateWithId = true;
        }
    }

    /**
     * handle the values in mapField mode
     *
     * @param array $values the array of values belonging to this line
     *
     * @return boolean
     * @access public
     */
    function shn_imp_imp_per_mapField( &$values ) {
    // write code to view table which contains details of CSV files with matching fields.	    
        return imp_Import_Parser::VALID;
    }
    

    /**
     * handle the values in preview mode
     *
     * @param array $values the array of values belonging to this line
     *
     * @return boolean      the result of this processing
     * @access public
     */
    function shn_imp_imp_per_preview( &$values ) {
        return $this->summary($values);
    }
 
/**
     * the initializer code, called before the processing
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_fini( ) {
    }
 
    
  }// end of the import_parser_contact class 
?>

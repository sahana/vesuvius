<?php
/* $Id: field.inc,v 1.1 2006-03-20 11:26:11 janakawicks Exp $ */


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

require_once ($global['approot'].'mod/imp/utils/type.inc');

class imp_Import_Field {
  
    /**#@+
     * @access protected
     * @var string
     */

    /**
     * name of the field
     */
    public $_name;

    /**
     * title of the field to be used in display
     */
    public $_title;

    /**
     * type of field
     * @var enum
     */
    public $_type;

    /**
     * is this field required
     * @var boolean
     */
    public $_required;

    /**
     * data to be carried for use by a derived class
     * @var object
     */
    public $_payload;

    /**
     * regexp to match the CSV header of this column/field
     * @var string
     */
     public $_headerPattern;

    /**
     * regexp to match the pattern of data from various column/fields
     * @var string
     */
     public $_dataPattern;

  

    
    /**
     * value of this field
     * @var object
     */
    public $_value;

    
   

    
    function __construct( $name, $title, $type = imp_Utils_Type::T_INT, $headerPattern = '//', $dataPattern = '//') {
        $this->_name      = $name;
        $this->_title     = $title;
        $this->_type      = $type;
        $this->_headerPattern = $headerPattern;
        $this->_dataPattern = $dataPattern;
            
        $this->_value     = null;
    }

    function shn_imp_imp_per_resetValue( ) {
        $this->_value     = null;
    }

    /**
     * the value is in string format. convert the value to the type of this field
     * and set the field value with the appropriate type
     */
    function shn_imp_imp_per_setValue( $value ) {
        $this->_value = $value;
    }

    function shn_imp_imp_per_validate( ) {
        //  echo $this->_value."===========<br>";
        $message = '';

        if ( $this->_value === null ) {
            return true;
        }


        
   }

}

?>

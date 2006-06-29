<?php
/* $Id: field.inc,v 1.4 2006-06-29 06:32:00 thushari Exp $ */
/* last modify : 2006/03/31 */

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

    /**
     * This class contains data and operation related to the matching  
     * @var class
     * access public
     */
class imp_Import_Field {
  
    /**#@+
     * @access protected
     * @var string
     */

    /**
     * name of the field
     */
    var $_name;

    /**
     * title of the field to be used in display
     */
    var $_title;

    /**
     * type of field
     * @var enum
     */
    var $_type;

    /**
     * is this field required
     * @var boolean
     */
    var $_required;

    /**
     * data to be carried for use by a derived class
     * @var object
     */
    var $_payload;

    /**
     * regexp to match the CSV header of this column/field
     * @var string
     */
     var $_headerPattern;

    /**
     * regexp to match the pattern of data from various column/fields
     * @var string
     */
     var $_dataPattern;

  

    
    /**
     * value of this field
     * @var object
     */
    var $_value;

    
   
    /**
     * This is the class constructor
     * @var object
     */
    
    function imp_Import_Field( $name, $title, $type = imp_Utils_Type::T_INT, $headerPattern = '//', $dataPattern = '//') {
        $this->_name      = $name;
        $this->_title     = $title;
        $this->_type      = $type;
        $this->_headerPattern = $headerPattern;
        $this->_dataPattern = $dataPattern;
            
        $this->_value     = null;
    }

     /**
     * 
     * reset the field value 
     */
    function shn_imp_imp_per_resetValue( ) {
        $this->_value     = null;
    }

    /*}}}*/
    
    /**
     * the value is in string format. convert the value to the type of this field
     * and set the field value with the appropriate type
     */
    function shn_imp_imp_per_setValue( $value ) {
        $this->_value = $value;
    }

}

?>

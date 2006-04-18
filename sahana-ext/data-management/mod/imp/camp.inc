<?php
/* $Id: camp.inc,v 1.1 2006-04-18 07:06:46 janakawicks Exp $ */


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


include_once ($global['approot'].'mod/imp/utils/array.inc');
include_once ($global['approot'].'mod/imp/utils/type.inc');


class imp_Contact_DAO_Camp {
    /**
    * static instance to hold the table name
    *
    * @var string
    * @static
    */
    static $_tableName = 'imp_Camp';
    /**
    * static instance to hold the field values
    *
    * @var array
    * @static
    */
    static $_fields = null;
    
    /**
    * static instance to hold the values that can
    * be imported / apu
    *
    * @var array
    * @static
    */
    static $_import = null;
   
   
    /**
    * class constructor
    *
    * @access public
    * @return imp_individual
    */
    function __construct() 
    {
        
    }
    
    /**
    * returns all the column names of this table
    *
    * @access public
    * @return array
    */
    function &fields() 
    {
        if (!(self::$_fields)) {
            self::$_fields = array(
                'c_uuid'=>array(
                    'name'=>'c_uuid',
                    'type'=>imp_Utils_Type::T_INT,
                    'required'=>true,
		    'import'=>true,
		    'headerPattern'=>'/name/i',
                    'dataPattern'=>'/^\w+(\s\w+)?$/',
		   
                ) ,
                'name'=>array(
                    'name'=>'name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Name') ,
                    'maxlength'=>60,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_camp.name',
                    'headerPattern'=>'/name/i',
                    'dataPattern'=>'/^\w+(\s\w+)?$/',
                   
                ) ,
                'contact_name'=>array(
                    'name'=>'contact_name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Contact Name') ,
                    'maxlength'=>30,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_camp.contact_name',
                    'headerPattern'=>'/^conatact|(c(ontact\s)?name)$/i',
                    'dataPattern'=>'/^\w+$/',
                    
                ) ,
                'contact_no'=>array(
                    'name'=>'contact_no',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Contact Number') ,
                    'maxlength'=>10,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_camp.contact_no',
                    'headerPattern'=>'/^contact|(c(ontact\s)?no)$/i',
                    'dataPattern'=>'//',
                   
                ) ,
                'services'=>array(
                    'name'=>'services',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Services') ,
                    'maxlength'=>2,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_camp.services',
                    'headerPattern'=>'/services/i',
                    'dataPattern'=>'//',
                ) ,
                'men'=>array(
                    'name'=>'men',
                    'type'=>imp_Utils_Type::T_INT,
		    'title'=>_('Men') ,
		    'import'=>true,
		    'where'=>'imp_camp.men',
                    'headerPattern'=>'/men/i',
                    'dataPattern'=>'//',
	    ) ,
		 'women'=>array(
                    'name'=>'women',
                    'type'=>imp_Utils_Type::T_INT,
		    'title'=>_('Women') ,
                    'import'=>true,
		    'where'=>'imp_camp.women',
		    'headerPattern'=>'/women/i',
		    'dataPattern'=>'//',
		    

         	),
                'family'=>array(
                    'name'=>'family',
                    'type'=>imp_Utils_Type::T_INT,
		    'title'=>_('Family') ,
                    'import'=>true,
		    'where'=>'imp_camp.family',
		    'headerPattern'=>'/family/i',
		    'dataPattern'=>'//',

                ) ,
                'children'=>array(
                    'name'=>'children',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Children'),
		    'import'=>true,
		    'where'=>'imp_camp.children',
		    'headerPattern'=>'/children/i',
		    'dataPattern'=>'//',
                ) ,
                'total'=>array(
                    'name'=>'total',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Total') ,
                    'import'=>true,
		    'where'=>'imp_camp.total',
		    'headerPattern'=>'/total/i',
		    'dataPattern'=>'//',
                   
                ) ,
                'opt_camp_service'=>array(
                    'name'=>'Camp Service',
                    'type'=>imp_Utils_Type::T_INT,
                    'title'=>_('Camp Service') ,
                    'maxlength'=>50,
                    'size'=>imp_Utils_Type::HUGE,
                    'import'=>true,
                    'where'=>'imp_camp.opt_camp_service',
                    'headerPattern'=>'/^camp|(c(amp\s)?service)$/i',
                    'dataPattern'=>'//',
                    
                ) ,
                'value'=>array(
                    'name'=>'value',
		    'title'=>_('Value') ,
                    'type'=>imp_Utils_Type::T_BOOLEAN,
		    'import'=>true,
		    'where'=>'imp_camp.value',
		    'headerPattern'=>'/value/i',
		    'dataPattern'=>'/^{0,1}?$/',
                ) ,
		   
                 'comments'=>array(
                    'name'=>'comments',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Comments'),
		    'maxlength'=>50,
                    'import'=>true,
                    'where'=>'imp_camp.comments',
                    'headerPattern'=>'/comments/i',
		    'dataPattern'=>'//',
              ),
	      
	    );
        }
        return self::$_fields;
    }
    /**
    * returns the names of this table
    *
    * @access public
    * @return string
    */
   function getTableName() 
    {
        return self::$_tableName;
    }
    /**
    * returns the list of fields that can be imported
    *
    * @access public
    * return array
    */
    function &import() 
    {
        if (!(self::$_import)) {
            self::$_import = array();
            $fields = &self::fields();
            foreach($fields as $name=>$field) {
                if (imp_Utils_Array::value('import', $field)) {
                        self::$_import[$name] = &$fields[$name];
                    
                }
            }
        }
        return self::$_import;
    }
   
 

 /**
    * returns the list of header pattern og the imported field
    *
    * @access public
    * return array
    */


    
}
?>


<?php
/* $Id: organization.inc,v 1.1 2006-04-18 07:06:46 janakawicks Exp $ */


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


class imp_Contact_DAO_Organization{
    /**
    * static instance to hold the table name
    *
    * @var string
    * @static
    */
    static $_tableName = 'imp_Organization';
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
                'o_uuid'=>array(
                    'name'=>'o_uuid',
                    'type'=>imp_Utils_Type::T_INT,
                    'required'=>true,
		    'import'=>true,
		   
                ) ,
		'parent_id'=>array(
                    'name'=>'parent_id',
                    'type'=>imp_Utils_Type::T_INT,
                    'required'=>true,
		    'import'=>true,
		   
                ) ,
                'name'=>array(
                    'name'=>'name',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Name') ,
                    'maxlength'=>100,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.full_name',
                    'headerPattern'=>'/name/i',
                    'dataPattern'=>'/^\w+(\s\w+)?$/',
                   
                ) ,
                'opt_org_type'=>array(
                    'name'=>'opt_org_type',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Organization Type') ,
                    'maxlength'=>50,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.family_name',
                    'headerPattern'=>'/^org|(o(rg\s)?type)$/i',
                    'dataPattern'=>'/^\w+$/',
                    
                ) ,
                'reg_no'=>array(
                    'name'=>'reg_no',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Registration Number') ,
                    'maxlength'=>100,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.l10n_name',
                    'headerPattern'=>'/^reg|(r(eg\s)?no)$/i',
                    'dataPattern'=>'/^\w+$/',
                   
                ) ,
                'man_power'=>array(
                    'name'=>'man_power',
                    'type'=>imp_Utils_Type::T_STRING,
                    'title'=>_('Man Power') ,
                    'maxlength'=>50,
                    'size'=>imp_Utils_Type::BIG,
                    'import'=>true,
                    'where'=>'imp_individual.custom_name',
                    'headerPattern'=>'/^man|(m(an\s)?power)$/i',
                    'dataPattern'=>'/^\w+(\s\w+)?+$/',
                ) ,
                'resources'=>array(
                    'name'=>'resources',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Resources') ,
                    'import'=>true,
		    'where'=>'imp_individual.serial',
                    'headerPattern'=>'/resources/i',
                    'dataPattern'=>'/^\w+(\s\w+)?+$/',
	    ) ,
		 'privacy'=>array(
                    'name'=>'privacy',
                    'type'=>imp_Utils_Type::T_INT,
		    'title'=>_('Privacy') ,
                    'import'=>true,
		    'where'=>'imp_individual.opt_id_type',
		    'headerPattern'=>'/privacy/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$/',
         	),
                'opt_sector'=>array(
                    'name'=>'opt_sector',
                    'type'=>imp_Utils_Type::T_STRING,
		    'title'=>_('Organization Sector') ,
                    'import'=>true,
		    'where'=>'imp_individual.isReliefWorker',
		    'headerPattern'=>'/sector/i',
		    'dataPattern'=>'/^\w+(\s\w+)?+$',             
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

<?php
/* $Id: parser.inc,v 1.2 2006-04-18 07:06:46 janakawicks Exp $ */
/* last modified 2006/03/31
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
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL
 
 */
global $global;

require_once($global['approot'].'/mod/imp/parser.inc');

/**
 * class to parse contact csv files
 */
/*
*
* This class is used to process the upload file 
*
*/


abstract class imp_import_parser
{

    const
        MAX_ERRORS      = 250,
        MAX_WARNINGS    = 25,
        VALID           =  1,
        WARNING         =  2,
        ERROR           =  4,
        CONFLICT        =  8,
        STOP            = 16,
        DUPLICATE       = 32,
        MULTIPLE_DUPE   = 64,
        NO_MATCH        = 128;

    /**
     * various parser modes
     */
    const
        MODE_MAPFIELD = 1,
        MODE_PREVIEW  = 2,
        MODE_SUMMARY  = 4,
        MODE_IMPORT   = 8;

    /**
     * codes for duplicate record handling
     */
    const
         DUPLICATE_NOCHECK = 16;

    /**
     * various Contact types
     */
   /**
     const
        CONTACT_INDIVIDUAL     = 1,
        CONTACT_ORGANIZATION   = 4;
 */
    var $_fileName;

    /**#@+
     * @access protected
     * @var integer
     */

    /**
     * imported file size
     */
    var $_fileSize;

    /**
     * seperator being used
     */
    var $_seperator;

    /**
     * total number of lines in file
     */
    var $_lineCount;

    /**
     * total number of non empty lines
     */
    var $_totalCount;

    /**
     * running total number of valid lines
     */
    var $_validCount;

    /**
     * running total number of invalid rows
     */
    var $_invalidRowCount;

    /**
     * maximum number of invalid rows to store
     */
    var $_maxErrorCount;

    /**
     * array of error lines, bounded by MAX_ERROR
     */
    var $_errors;

    /**
     * total number of conflict lines
     */
    var $_conflictCount;

    /**
     * array of conflict lines
     */
    var $_conflicts;

       
    /**
     * running total number of warnings
     */
    var $_warningCount;

    /**
     * running total number of un matched Conact
     */
    var $_unMatchCount;

    /**
     * array of unmatched lines
     */
    var $_unMatch;

    /**
     * maximum number of warnings to store
     */
    var $_maxWarningCount;

    /**
     * array of warning lines, bounded by MAX_WARNING
     */
    var $_warnings;

    /**
     * array of all the fields that could potentially be part
     * of this import process
     * @var array
     */
    var $_fields;

    /**
     * array of the fields that are actually part of the import process
     * the position in the array also dictates their position in the import
     * file
     * @var array
     */
    var $_activeFields;

    /**
     * cache the count of active fields
     *
     * @var int
     */
    var $_activeFieldCount;

    /**
     * maximum number of non-empty/comment lines to process
     *
     * @var int
     */
    var $_maxLinesToProcess;

    /**
     * cache of preview rows
     *
     * @var array
     */
    var $_rows;


    /**
     * filename of error data
     *
     * @var string
     */
    var $_errorFileName;


    /**
     * filename of conflict data
     *
     * @var string
     */
    var $_conflictFileName;


    /**
     * filename of duplicate data
     *
     * @var string
     */
    var $_duplicateFileName;

    /**
     * filename of mismatch data
     *
     * @var string
     */
    var $_misMatchFilemName;


    /**
     * contact type
     *
     * @var int
     */

   var $_contactType;
    
   
    /**
     * this is the class constructor
     *
     * 
     */

    function imp_import_parser() {
	    $this->_maxWarningCount = $this->MAX_WARNINGS;
        $this->_maxLinesToProcess = 0;
	$this->_maxErrorCount =$this->MAX_ERRORS;
    }
/* }}} */
     

   /**
     * this is check the null values
     * @return void
     * @access public
     * 
     */
    
    function shn_imp_imp_per_isNull( $value ) {
        if ( ! isset( $value ) || $value === null || $value === '' ) {
            return true;
        }
        if ( is_array( $value ) ) {
            foreach ( $value as $key => $value ) {
                if ( ! self::shn_imp_imp_per_isNull( $value ) ) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }


    /**
     * this processes the upload file
     * @return void
     * @access public
     * 
     */
    
    function shn_imp_imp_per_run( $fileName,
                  $seperator = ',',
                  &$mapper,
                  $skipColumnHeader = false,
                  $mode = self::MODE_PREVIEW,
                  $contactType = 'INDIVIDUAL',
                  $onDuplicate = self::DUPLICATE_NOCHECK ) {
	
		  
        switch ($contactType) {
        case 'INDIVIDUAL' :
            $this->_contactType = 'Individual';
            break;
        case 'ORGANIZATION' :
            $this->_contactType = 'Organization';
            break;  
        case 'CAMPS' :
            $this->_contactType = 'Camps';
            break;          
	    
       	}
        
        $this->shn_imp_imp_per_init();
      
        $this->_seperator = $seperator;
        $fd = fopen( $fileName, "r" );
        if ( ! $fd ) {
		echo 'Cannot open the file';
            return false;
        }

        $this->_lineCount  = $this->_warningCount= 0;
        $this->_invalidRowCount = $this->_validCount= 0;
        $this->_totalCount = $this->_conflictCount = 0;
    
        $this->_errors   = array();
        $this->_warnings = array();
        $this->_conflicts = array();

        $this->_fileSize = number_format( filesize( $fileName ) / 1024.0, 2 );
     
	if ( $mode == self::MODE_MAPFIELD ) {
            $this->_rows = array( );
	  } else {
            $this->_activeFieldCount = count( $this->_activeFields );
	    $SESSION['ColumnCount'] =  $this->_activeFieldCount ;
        }

               
        while ( ! feof( $fd ) )
       	{ //begining of the while
            $this->_lineCount++;
             
          $values = fgetcsv( $fd,8192, $seperator);
             
            if ( ! $values ) {
		   continue;
	       }
            self::shn_imp_imp_per_encloseScrub($values);

            // skip column header if we're not in mapfield mode
            if ( $mode != self::MODE_MAPFIELD && $skipColumnHeader ) {
                    $skipColumnHeader = false;
                    continue;
            }

            /* trim whitespace around the values */
            $empty = true;
            foreach ($values as $k => $v) {
                $values[$k] = trim($v, " .\t\r\n");
            }

            if ( $this->shn_imp_imp_per_isNull( $values ) ) {
                continue;
            }

            $this->_totalCount++;
            
            if ( $mode == self::MODE_MAPFIELD ) {
                $returnCode = $this->shn_imp_imp_per_mapField( $values );
            } else if ( $mode == self::MODE_PREVIEW ) {
                $returnCode = $this->shn_imp_imp_per_preview( $values );
            } else { 
	   
                $returnCode = self::ERROR;
            }

            // note that a line could be valid but still produce a warning
            if ( $returnCode & self::VALID ) {
                $this->_validCount++;
                if ( $mode == self::MODE_MAPFIELD ) {
                    $this->_rows[] = $values;
		    $_SESSION['dataValues']= $this->_rows;
		    $this->_activeFieldCount = max( $this->_activeFieldCount, count( $values ) );
                }
            }

            if ( $returnCode & self::WARNING ) {
                $this->_warningCount++;
                if ( $this->_warningCount < $this->_maxWarningCount ) {
                    $this->_warningCount[] = $line;
                }
            } 

            if ( $returnCode & self::ERROR ) {
                $this->_invalidRowCount++;
                if ( $this->_invalidRowCount < $this->_maxErrorCount ) {
                    array_unshift($values, $this->_lineCount);
                    $this->_errors[] = $values;
                }
            } 

            if ( $returnCode & self::CONFLICT ) {
                $this->_conflictCount++;
                array_unshift($values, $this->_lineCount);
                $this->_conflicts[] = $values;
            } 

             if ( $returnCode & self::NO_MATCH ) {
                $this->_unMatchCount++;
                array_unshift($values, $this->_lineCount);
                $this->_unMatch[] = $values;
            } 
            
           
            // we give the derived class a way of aborting the process
            // note that the return code could be multiple code or'ed together
            if ( $returnCode & self::STOP ) {
                break;
            }

            // if we are done processing the maxNumber of lines, break
            if ( $this->_maxLinesToProcess > 0 && $this->_validCount >= $this->_maxLinesToProcess ) {
                break;
            }
        } // end of the while loop

        fclose( $fd );

               
        return $this->shn_imp_imp_per_fini();
    } 

    /* }}} */

 

    /**
     * Given a list of the importable field keys that the user has selected
     * set the active fields array to this list
     *
     * @param array mapped array of values
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_setActiveFields( $fieldKeys ) {
        $this->_activeFieldCount = count( $fieldKeys );
        foreach ( $fieldKeys as $key ) {
            if ( empty( $this->_fields[$key] ) ) {
                $this->_activeFields[] =& new imp_Import_Field( '', ts( '- do not import -' ) );
            } else {
                $this->_activeFields[] = clone( $this->_fields[$key] );
            }
        }
    }
    

    /**
     * 
     * set the active fields value array to this list
     *
     * @param array 
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_setActiveFieldValues( $elements ) {
        $maxCount = count( $elements ) < $this->_activeFieldCount ? count( $elements ) : $this->_activeFieldCount;
        for ( $i = 0; $i < $maxCount; $i++ ) {
            $this->_activeFields[$i]->shn_imp_imp_per_setValue( $elements[$i] );
        }

        // reset all the values that we did not have an equivalent import element
        for ( ; $i < $this->_activeFieldCount; $i++ ) {
            $this->_activeFields[$i]->shn_imp_imp_per_resetValue();
        }

        // now validate the fields and return false if error
        $valid = self::VALID;
        for ( $i = 0; $i < $this->_activeFieldCount; $i++ ) {
            if ( ! $this->_activeFields[$i]->shn_imp_imp_per_validate() ) {
                // no need to do any more validation
                $valid = self::ERROR;
                break;
            }
        }
        return $valid;
    }

   /*}}} */ 

   /**
     * 
     * get the selected title value to a array 
     *
     * @return void
     * @access public
     */
   
    function shn_imp_imp_per_getSelectValues() {
        $values = array();
        foreach ($this->_fields as $name => $field ) {
            $values[$name] = $field->_title;
        }
        return $values;
    }

    /* }}} */

    
    /**
     * 
     * get header patterns  
     *
     * @return void
     * @access public
     */

    function shn_imp_imp_per_getHeaderPatterns() {
        $values = array();
        foreach ($this->_fields as $name => $field ) {
           $values[$name] = $field['headerPattern'];
        }
        return $values;
    }

    /*}}}*/
    

     /**
     * 
     * get data patterns  
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_getDataPatterns() {
        $values = array();
        foreach ($this->_fields as $name => $field ) {
            $values[$name] = $field['dataPattern'];
      	}
        return $values;
    }


    /* }}} */

    /**
     * 
     * This adds the fileds to be imported
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_addField( $name, $title, $type = imp_Utils_Type::T_INT,
                       $headerPattern = '//', $dataPattern = '//',
                       $hasLocationType = false) {
    global $global;
			       
     require_once($global['approot'].'/mod/imp/field.inc');	       
        $this->_fields[$name] =& new imp_Import_Field($name, $title, $type, $headerPattern, $dataPattern);
        if ( empty( $name ) ) {
            $this->_fields['doNotImport'] =& new imp_Import_Field($name, $title, $type, $headerPattern, $dataPattern);
        }
    }

    /**
     * setter function
     *
     * @param int $max 
     *
     * @return void
     * @access public
     */
    function shn_imp_imp_per_setMaxLinesToProcess( $max ) {
        $this->_maxLinesToProcess = $max;
    }

   
   
    /** 
     * Remove single-quote enclosures from a value array (row)
     *
     * @param array $values
     * @param string $enclosure
     * @return void
     * @static
     * @access public
     */
    function shn_imp_imp_per_encloseScrub(&$values, $enclosure = "'") {
        if (empty($values)) 
            return;

        foreach ($values as $k => $v) {
            $values[$k] = preg_replace("/^$enclosure(.*)$enclosure$/", '$1', $v);
        }
    }

} //end of the import_parser class


?>





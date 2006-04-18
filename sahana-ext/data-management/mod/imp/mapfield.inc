<?php
/* $Id: mapfield.inc,v 1.2 2006-04-18 07:06:46 janakawicks Exp $ */
/* Last modified : 31/03/2005 */

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

require_once($global['approot'].'mod/imp/parser_contact.inc');


/**
 * This class gets the name of the file to upload 
 */
class imp_Import_Form_MapField {

    /**
     * cache of preview data values
     *
     * @var array
     * @access protected
     */
    var $_dataValues;

    /**
     * mapper fields
     *
     * @var array
     * @access protected
     */
    var $_mapperFields;

    
    /**
     * number of columns in import file
     *
     * @var int
     * @access protected
     */
    var $_columnCount;


    /**
     * column headers, if we have them
     *
     * @var array
     * @access protected
     */
    var $_columnHeaders;

    /**
     * an array of booleans to keep track of whether a field has been used in
     * form building already.
     *
     * @var array
     * @access protected
     */
    var $_fieldUsed;
    

    /**{{{ */
    
    /**
     * Attempt to resolve the header with our mapper fields
     *
     * @param header
     * @param mapperFields
     * @return string
     * @access public
     */
    public function shn_imp_imp_per_defaultFromHeader($header, &$patterns) {
        foreach ($patterns as $key => $re) {
            /* Skip the first (empty) key/pattern */
            if ( empty( $re ) ) {
                continue;
            }

            if (preg_match($re, $header)) {
                $this->_fieldUsed[$key] = true;
                return $key;
            }
        }
        return '';
    }

    /**}}} */

    /**{{{ */
    /**
     * Guess at the field names given the data and patterns from the schema
     *
     * @param patterns
     * @param index
     * @return string
     * @access public
     */
    public function shn_imp_imp_per_defaultFromData(&$patterns, $index) {
        $best = '';
        $bestHits = 0;
        $n = count($this->_dataValues);
        
        foreach ($patterns as $key => $re) {
            if (empty($re)) continue;

            /* Take a vote over the preview data set */
            $hits = 0;
            for ($i = 0; $i < $n; $i++) {
                if (preg_match($re, $this->_dataValues[$i][$index])) {
                    $hits++;
                }
            }

            if ($hits > $bestHits) {
                $bestHits = $hits;
                $best = $key;
            }
        }
    
        if ($best != '') {
            $this->_fieldUsed[$best] = true;
        }
        return $best;
    }


    /**}}} */

    /**
     * Function to set variables up before form is built
     *
     * @return void
     * @access public
     */
    public function shn_imp_imp_per_preProcess()
    {
    
     	$this->_mapperFields = $_SESSION['fields']; //mapper fields
        $this->_dataValues = $_SESSION['dataValues']; //csv data file 
        $this->_columnCount = count($this->_dataValues[0]); //$_SESSION['columnCount'];
	
	$skipColumnHeader = $_SESSION['skipColumnHeader'];
          
        if ( $skipColumnHeader ) {
           $_SESSION['rowDisplayCount'] = 3;
            /* if we had a column header to skip, stash it for later */
           // $this->_columnHeaders[] = $_SESSION['dataValues'][0];
        } else {
            $_SESSION['rowDisplayCount'] = 2;
        }
   
   }

   /*}}} */

   /**{{{ */
    /**
     * Function to actually build the form
     *
     * @return void
     * @access public
     */
    public function shn_imp_imp_per_buildQuickForm()
    {
        $defaults = array( );
        $mapperKeys      = array_keys( $this->_mapperFields );
        $hasHeaders      = !empty($_SESSION['dataValues'][0]);
        $headerPatterns  = $_SESSION['headerpattern'];
        $dataPatterns    = $_SESSION['dataPattern'];
    
	
       /* Initialize all field usages to false */
        foreach ($mapperKeys as $key) {
            $this->_fieldUsed[$key] = false;
        }

      
//coding relate to perform mapping 
     for ( $i = 0; $i < $this->_columnCount; $i++ ){ 
       if ($hasHeaders) {
             $defaults["mapper[$i]"] = array($this->shn_imp_imp_per_defaultFromHeader($_SESSION['dataValues'][0][$i],                                                                                    $headerPatterns),0);
                    
                } else {
                    // Otherwise guess the default from the form of the data
                    $defaults["mapper[$i]"] = array($this->shn_imp_imp_per_defaultFromData($dataPatterns, $i),0);
                }
     }

     $mapperKeys = array_reverse($mapperKeys) ; 
        
  	echo '<h2 align="center">'._('Mapping Field').'</h2>';
	shn_form_fopen("imp_per_mapfield",null,array('req'=> false));  

        shn_form_hidden(array('seq'=>'map_field'));
	
	shn_form_fsopen(_('Map Field'));
        ?>	
    	<p><?= _('Review the values shown below from the first 2 rows of your import file and select the matching Sahana database fields from the drop-down lists in the right-hand column. Select - do not import - for any columns in the import file that you want ignored.'); ?></p>
	<?php
 
       // coding for display the table 
?> 
<div id = "result">
   <table> 
   <?php
    if ($_SESSION['rowDisplayCount']=== 2) 
    {    
     $k =0; 	    
    ?>
     <thead>
            <td><?=_("Field Name")?></td>
	        <td><?=_("Row1 Data")?></td>
            <td><?=_("Row2 Data ")?></td>
           <td><?=_("Matching Fields")?></td> 
        </thead>
    <?php
    }  
    else { 
      $k =1;	    
     ?>
     <thead>
            <td><?=_("Row1 Data")?></td>
            <td><?=_("Row2 Data")?></td>
	    <td><?=_("Row3 Data")?></td>
           <td><?=_("Matching Fields")?></td> 
        </thead>
    <?php
     }	    
 $vic_map = $mapperKeys;

 for ( $i = 0; $i < $this->_columnCount; $i++ ){
 ?><tr><?
  for ($j = $k; $j<= $_SESSION['rowDisplayCount'];$j++){
  ?>  
	
<td><?php echo $this->_dataValues[$j][$i]?></td> 
	           
     <?php
  } ?>  

  <?php
	  
      $searchItem = $defaults["mapper[$i]"][0] ; 
        
	  if (array_search($searchItem,$mapperKeys)){
	    $mapperKeys[] = $searchItem;
	    $_SESSION['mapper'] = $mapperKeys;
	   
	  }	 
	  else { 
              $mapperKeys[] = 'do_not_import';
	    $_SESSION['mapper'] = $mapperKeys;
		  
	      }  
?>   
	   <td><?php shn_form_select($_SESSION['mapper'],"","mappedvalue[$i]")?> </td>
	   </tr>
     <?php  
  
	        
       }
      ?>
   </table>
</div> 
      <?php
        
     
     shn_form_fsclose(); 
     shn_form_submit(_('Continue')); 

     shn_form_fclose(); 
     
     $_SESSION['mapper']= $mapperKeys; 
     
    }

  /**}}} */ 
 

}


/* {{{ */ 

/* 
* delete an given element from an array
* access public 
* to be discussed to put in a library

*/ 

function removeElement($item, $array) 
{ 
    if (($key = array_search($item, $array)) !== false) 
    { 
        if ($key == 0) 
        { 
            // Remove the first element 
            array_shift($array); 
        } 
        elseif ($key < (count($array)-1)) // Not first or last item 
        { 
            // A fairly simple process of removing the middle element 
            $arr1 = $arr2 = $array; 
            array_splice($arr1, 0, ($key+1)); 
            array_splice($arr2, $key); 
            $array = array_merge($arr1, $arr2); 
        } 
        else 
        { 
            // Remove the last element 
            array_pop($array); 
        } 
    } 
    return $array; 
} 


/* }}} */ 

?>

<?php
/**Search page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan Careem <mifan@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya Gunawardana <saumya@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

?>
    <h3> Advanced Search </h3>
<?php
	 //include the form handler 
    require_once ($global['approot'].'/inc/handler_form.inc');
    //include the database handler 
    required_once($global['approot'].'inc/handler_db.inc');
    
    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);

    $body = array (
    	array ( 'type'=>'text','desc' => 'Name', 'size' => '30','name'=>'name'),
    	array ( 'type'=>'dropdown','desc' => 'Option', 'name'=>'option','options'=>
    		array(
    			array('drop_desc'=>'Exactly'),
    			array('drop_desc'=>'Like'),
    			array('drop_desc'=>'Start From')
    		)
    	),
    	array ( 'type'=>'dropdown','desc' => 'Option', 'name'=>'option','options'=>
    		array(
    			array('drop_desc'=>'Or'),
    			array('drop_desc'=>'And'),
    			array('drop_desc'=>'Not')
    		)	
    	)
    );//end of body
    shn_show_form($body);
    
    $tail = array (
        array('type'=>"submit",'value'=>"Next")
    ); // end of tail
?>

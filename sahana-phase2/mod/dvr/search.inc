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
    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);

    $body = array ( 
                array ( 'type'=>'radio','desc'=>'Select the type of the entry you want to enter, from the following list', 
                        'name'=>'add_option', 'align'=>'right','options'=> 
                        array ( 
                            array ( 'drop_desc' => 'Individual - <i>If you want to add details of individuals choose this
 option</i>', 'value' => 'individual'),
                            array ( 'drop_desc' => 'Group - <i>If you want to add details of individuals choose this option</i
>', 'value' => 'group')
                            )
                    )
                );//end of body
    shn_show_form($body);
    
    <?php
    $tail = array (
        array('type'=>"submit",'value'=>"Next")
    ); // end of tail
?>
?>

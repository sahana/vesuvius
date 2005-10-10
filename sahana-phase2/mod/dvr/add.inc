<?php
/* $Id: add.inc,v 1.1 2005-10-10 03:59:38 janakawicks Exp $ */

/**Main home page of the DVR
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Mifan 
* @author     Janaka Wickramasinghe <janaka@opensource.lk> 
* @author     Saumya 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

function _shn_dvr_add_default()
{
?>
    <h1 align="center">Add Entry</h1>
<?php
    $header = array (array('method'=>"POST",'action'=>'')); // end of header
    shn_show_form($header);
?>
    <div id="add_opt">
<?php
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
                );
    shn_show_form($body);
?>
    </div><!-- /add_opt -->
<?php    
    $body = array ( 
        array('type'=>'radio','desc'=>'<br/>Select the type of the entry from the following list','name'=>'add_type','align'=>'right','options'=>
            array(
                array('drop_desc'=>'Diceased&nbsp; - <i>Details of deceased people</i>','value'=>'deceased','br'=>1),
                array('drop_desc'=>'Displaced - <i>Details of displaced people</i>','value'=>'displaced','br'=>1),
                array('drop_desc'=>'Missing&nbsp; &nbsp;  - <i>Details of missing people</i>','value'=>'missing','br'=>1),
                array('drop_desc'=>'Affected&nbsp;&nbsp;  - <i>details of affected people</i>','value'=>'affected','br'=>1)
            )
        )
    ); // end of body
    shn_show_form($body);
    
    $body = array ( 
        array('type'=>'radio','desc'=>'Select your preference from the following list','name'=>'prefer','align'=>'right','options'=>
            array(
                array('drop_desc'=>'Tabbed Form','value'=>'tab'),
                array('drop_desc'=>'Listed Form','value'=>'list','br'=>1)
            )
        )
    );
    shn_show_form($body);
?>
    <div id="check">
<?php
    $body = array ( 
        array('type'=>'checkbox','name'=>'remember','value'=>'save','drop_desc'=>'Save Preferences')
    ); // end of body
    shn_show_form($body);
?>
    </div><!-- /check -->
<?php
    $tail = array (
        array('type'=>"submit",'value'=>"Next")
    ); // end of tail
    //@todo remove later
?>
    <input type="hidden" name="add_sequence" value="start" />
<?php
    shn_show_form($tail);
   
}

function _shn_dvr_add_show_form()
{
    echo "My Form Goes here";    
}

?>

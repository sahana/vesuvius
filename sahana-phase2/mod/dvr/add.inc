<?php
/* $Id: add.inc,v 1.3 2005-10-21 09:15:08 janakawicks Exp $ */

/**Main home page of the DVR
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

//@todo: put thsi some where else later
include_once($global['approot'].'/mod/dvr/errors.inc');
include_once($global['approot'].'/inc/lib_errors.inc');

function _shn_dvr_add_default($error=false)
{
    global $global;
?>
    <h1 align="center">Add Entry</h1>
<?php
    if($error)
        display_errors();

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
    //assign the post variables
    $add_option = $_POST['add_option'];
    $add_type = $_POST['add_type'];
    $prefer = $_POST['prefer'];

    //trim them
    $add_option = trim($add_option);
    $add_type = trim($add_type);
    $prefer = trim($prefer);
    
    //Check for the post variables
    if($add_option != 'individual' && $add_option != 'group'){
        $error = true;
        add_error(SHN_ERR_DVR_ADD_OPTION);
    }

    if($add_type != 'deceased' && $add_type != 'displaced' && $add_type != 'missing' && $add_type != 'affected'){
        $error = true;
        add_error(SHN_ERR_DVR_ADD_TYPE);
    }
    if($prefer != 'tab' && $prefer != 'list'){
        $error = true;
        add_error(SHN_ERR_DVR_PREFER);
    }
       
    //if erros send back to the main from with errors
    if($error){
        _shn_dvr_add_default(true);
        return false;
    }    

    global $global;
    //@todo : should get the module_id by now
    $rs = $global['db_cache']->Execute("SELECT a.section, a.forms, a.form_meta, b.name, b.caption, b.type, b.form_meta FROM module_metadata a, metadata b WHERE a.module_id = 1 AND a.forms = 1 AND a.meta_id = b.meta_id order by a.section, a.element_order");
    $result = $rs->GetAll();
    $tabs = "<div id=\"tabs\">";
    foreach($result as $rec){
        $cur_section = $rec['a.section'];
        if($cur_section == $section){
            if(trim($rec['b.caption']) != '')
                $tab_container .= _($rec['b.caption']).' : ';
            if($rec['b.type'] == 'text')
                $tab_container .= '<input type="text" name="'.$rec['b.name'].'" ><br>';
            if($rec['b.type'] == 'dropdown'){
                $tab_container .= '<select name="'.$rec['b.name'].'">';
                $tmparr = split('\|',$rec['b.form_meta']);
                foreach ($tmparr as $tmp){
                    list ($n,$v) = split(",",$tmp);
                    $tab_container .= '<option value="'.$v.'">'.$n.'</option>';
                }
                $tab_container .= '</select>';
            }
        }else{
           if(trim($cur_section) != ''){
                $tab_no++;
                $tabs .= '<a href="#tabs'.$tab_no.'">'.$cur_section.'</a>';
                $section = $cur_section;
                if($tab_container)
                    $tab_container .= '</p><p id="tabs'.$tab_no.'">';
                else
                    $tab_container = '<p id="tabs'.$tab_no.'">';
                $tab_container .= $rec['b.caption'].' : ';
                if($rec['b.type'] == 'text')
                    $tab_container .= '<input type="text" name="'.$rec['b.name'].'" ><br>';
                if($rec['b.type'] == 'dropdown'){
                    $tab_container .= '<select name="'.$rec['b.name'].'">';
                    $tmparr = split('\|',$rec['b.form_meta']);
                    foreach ($tmparr as $tmp){
                        list ($n,$v) = split(",",$tmp);
                        $tab_container .= '<option value="'.$v.'">'.$n.'</option>';
                    }
                    $tab_container .= '</select><br>';
                }


            }
        }
    }
    $tabs .= "</div>";
    echo "<form>";
    echo $tabs;
    echo "<br><div id=\"tab_content\">".$tab_container."</p></div>";
    echo "</form></div>";
}
    
?>

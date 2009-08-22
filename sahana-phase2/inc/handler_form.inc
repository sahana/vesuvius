<?php
/**
 *
 * This is a generic form template handler(NOTE: this is deprecated use lib_form.inc)
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage zz_deprecated
 * @author     Pradeeper <pradeeper@opensource.lk>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @deprecated This handler is replaced by the lib_form.inc
 *
 */


/**
 * Creates the HTML form
 * 
 * @param string $arropt 
 * @param 'action'=>'' $'action'=>'' 
 * @param 'id'=>'dataform') $'id'=>'dataform') 
 * @param mixed $return 
 * @access public
 * @return void
 */
function shn_form_open($arropt=array('method'=>'POST','action'=>'','id'=>'dataform'),$return=false)
{
    $output = '<form '.($arropt['id']?'':'id="dataform" ');
    foreach ($arropt as $k => $v){
        $output .= "$k=\"$v\" ";
    }
    $output .= ">\n";
    if($return)
        return $output;
    else
        echo $output;
}

/**
 * You can add HTML form elements as an array
 * 
 * @param mixed $arr 
 * @param mixed $return 
 * @param mixed $default_val_req 
 * @access public
 * @return void
 */
function shn_form_add_component($arr,$return=false,$default_val_req=false)
{
    switch ($arr['type']){
        case 'text' :
        case 'password' :
        case 'button' :
        case 'submit' :
            $output .= '<input ';
            if($arr['type']=="submit")
                $output .= _shn_form_dump_key_val($arr,array('desc','br','caption_align')); //don't dump 'desc' and 'br' and 'value'
            else
                $output .= _shn_form_dump_key_val($arr,array('desc','value','br','caption_align')); //don't dump 'desc' and 'br' and 'value'
            $output .= ($default_val_req?_shn_form_default_req($arr['type'],$arr['name'],$arr['value']):' value="'.$arr['value'].'" '); //value assgined
            $output .= ' />'."\n"; // end of 'input type'
            $output = _shn_form_set_caption($arr['desc'],$arr['caption_align'],$output); //Set the caption NOTE: assign all back
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n"; // this will generate the 'break'.
        break;

        case 'hidden' :
            $output .= '<input ';
            if($arr['type']=="submit")
                $output .= _shn_form_dump_key_val($arr,array('desc','br','caption_align')); //don't dump 'desc' and 'br' and 'value'
            else
                $output .= _shn_form_dump_key_val($arr,array('desc','value','br','caption_align')); //don't dump 'desc' and 'br' and 'value'
            $output .= ($default_val_req?_shn_form_default_req($arr['type'],$arr['name'],$arr['value']):' value="'.$arr['value'].'" '); //value assgined
            $output .= ' />'."\n"; // end of 'input type'
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n"; // this will generate the 'break'.
            break; 
        case 'textarea' :
            $output .= '<textarea ';
            $output .= _shn_form_dump_key_val($arr,array('desc','value','br','type'));
            $output .= ' >';
            $output .= ($default_val_req?_shn_form_default_req($arr['type'],$arr['name'],$arr['value']):$arr['value']); //value assgined
            $output .= '</textarea>';
            $output = _shn_form_set_caption($arr['desc'],$arr['caption_align'],$output); //Set the caption NOTE: assign all back
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n"; // this will generate the 'break'.
        break;
        
        case 'checkbox' :
            $output .= '<input ';
            $output .= _shn_form_dump_key_val($arr,array('desc','br','caption_align','selected')); //don't dump 'desc' and 'br' and 'value'
            $output .= ($default_val_req?_shn_form_default_req($arr['type'],$arr['name'],$_POST[$arr['name']]):($arr['selected']?' checked':'')); //check assgined
            $output .= ' />'."\n"; // end of 'input type'
            $output = _shn_form_set_caption($arr['desc'],$arr['caption_align'],$output); //Set the caption NOTE: assign all back
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n"; // this will generate the 'break'.
        break;    

        case 'label' :
            $output .= _shn_form_set_caption($arr['desc']);
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n";
        break;
    
        case 'radio' :
            $output .= _shn_form_set_caption($arr['desc']);
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n";
            foreach($arr['options'] as $option){
                $output_opt = '<input type="'.$arr['type'].'" name="'.$arr['name'].'" ';
                $output_opt .= _shn_form_dump_key_val($option,array('drop_desc','br','caption_align','selected'));
                $output_opt .= ($default_val_req?_shn_form_default_req($arr['type'],$option['value'],$_POST[$arr['name']]):($option['selected']?' checked':''));
                $output_opt .= ' />'."\n"; // end of 'input type'
                $output_opt = _shn_form_set_caption($option['drop_desc'],$option['caption_align'],$output_opt,false); //Set the caption NOTE: assign all back
                $output_opt .= ($arr['br']?_shn_form_br($option['br']):'')."\n"; // this will generate the 'break'.
                $output .= $output_opt;
            }
        break;
        case 'dropdown' :
            $output .= '<select '.$arr['multiple'].' '. _shn_form_dump_key_val($arr,array('desc','br','options')). ">\n";
            foreach($arr['options'] as $option){
                $output_opt = '<option '._shn_form_dump_key_val($option,array('drop_desc','selected'));
                $output_opt .= ($default_val_req?_shn_form_default_req($arr['type'],$option['value'],$_POST[$arr['name']]):($option['selected']?' selected':''));
                $output_opt .= ">" . _shn_form_set_caption($option['drop_desc'],'','',false) .'</option>'."\n";
                $output .= $output_opt;
            }
            $output .= "</select>\n"; 
            $output = _shn_form_set_caption($arr['desc'],$arr['caption_align'],$output); //Set the caption NOTE: assign all back
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n";
        break;
        case 'multiselect' :
            $output .= '<select multiple '._shn_form_dump_key_val($arr,array('desc','br','options')). ">\n";
            foreach($arr['options'] as $option){
                $output_opt = '<option '._shn_form_dump_key_val($option,array('drop_desc','selected'));
                $output_opt .= ($default_val_req?_shn_form_default_req($arr['type'],$option['value'],$_POST[$arr['name']]):($option['selected']?' selected':''));
                $output_opt .= ">" . _shn_form_set_caption($option['drop_desc'],'','',false) .'</option>'."\n";
                $output .= $output_opt;
            }
            $output .= "</select>\n"; 
            $output = _shn_form_set_caption($arr['desc'],$arr['caption_align'],$output); //Set the caption NOTE: assign all back
            $output .= ($arr['br']?_shn_form_br($arr['br']):'')."\n";
        break;
		case 'date' :
			$output .="<label>".$arr['desc']."</label>\n<select name=\"".$arr['name']."_dd\"  SIZE=1>\n";
			for($i=1; $i<=31; $i++) {
				if(($i<10)&($i>=0)) {
					$output .="<option>0".$i."</option>\n";
				} else {
					$output .="<option>".$i."</option>\n";
				}
			}
			$output .="</select>\n";
			$output .="<select name=\"".$arr['name']."_mm\"  SIZE=1>\n";
			for($i=1; $i<=12; $i++) {
				if(($i<10)&($i>=0)) {
					$output .="<option>0".$i."</option>\n";
				} else {
					$output .="<option>".$i."</option>\n";
				}
			}
			$output .="</select>\n";
			$output .="<select name=\"".$arr['name']."_yyyy\"  SIZE=1>\n";
			$current_year = date("Y");
			for($i=$current_year; $i>=1900; $i--) {
				$output .="<option>".$i."</option>\n";
			}
			$output .="</select>\n";
			$output .="<br />";
        break;
}
    if($return)
        return $output;
    else
        echo $output;
}

/**
 * You can add list of HTML form elements as an array
 * 
 * @param mixed $arr_list 
 * @param mixed $section 
 * @param string $legend 
 * @param mixed $return 
 * @param mixed $default_val_req 
 * @access public
 * @return void
 */
function shn_form_add_component_list($arr_list,$section=true,$legend='',$return=false,$default_val_req=false)
{
    if($section)
        $output ="<fieldset>\n".($legend?"<legend>$legend</legend>\n":'');
    foreach($arr_list as $arr){
        if($arr['section_start'])
            $output .="<fieldset>\n<legend>{$arr['section_start']}</legend>\n";
        $output .= shn_form_add_component($arr,true,$default_val_req);
        if($arr['section_end'])
            $output .="</fieldset>\n";
    }
    if($section)
        $output .="</fieldset>\n";
    if($return)
        return $output;
    else
        echo $output;
}

/**
 * Use this function to close the HTML form
 * 
 * @param mixed $return 
 * @access public
 * @return void
 */
function shn_form_close($return=false)
{
    $output = "</form>\n";
    if($return)
        return $output;
    else
        echo $output;
}



/**
 * Generate given number of line breaks
 * 
 * @param mixed $number 
 * @access protected
 * @return void
 */
function _shn_form_br($number)
{
    for ($i=0; $i<$number; $i++)
        $output .= '<br>';
    return $output;
}

/**
 * Auto Populated the POST values if available.
 * 
 * @param mixed $type 
 * @param mixed $name 
 * @param string $value 
 * @access protected
 * @return void
 */
function _shn_form_default_req($type,$name,$value="")
{
    switch ($type){
        case 'text':
        case 'password':
        case 'hidden':
            $output = ($_POST[$name]?' value="'.$_POST[$name].'" ':' value="'.$value.'" ');
        break;
        case 'textarea' :
            $output = ($_POST[$name]?$_POST[$name]:$value);
        break;
        case 'checkbox' :
            $output = ($value?' checked':'');
        break;
        case 'radio' :
            $output = ($name==$value?' checked':'');
        break;
        case 'dropdown' :
            $output = ($name==$value?' selected':'');
        break;
    }
    return $output;    
}

/**
 * Dumps the given associative array into $key="value" sequence
 * 
 * @param mixed $arr 
 * @param mixed $keys_ignore 
 * @access protected
 * @return void
 */
function _shn_form_dump_key_val($arr,$keys_ignore)
{
    foreach ($arr as $k => $v){
        if(! (in_array($k,$keys_ignore))){
                $output .= $k.'="'.$v.'" ';
        }
    }
    return $output;
}

/**
 * Sets the caption of a input field
 * 
 * @param mixed $caption 
 * @param string $align 
 * @param string $str 
 * @param mixed $tag 
 * @access protected
 * @return void
 */
function _shn_form_set_caption($caption,$align="left",$str="",$tag=true)
{
    if(!$caption)
        return $str;
    if($tag)
        $caption = "<label>$caption</label>";
    if($align=='right')
        $output = $str.$caption;
    else
        $output = $caption.$str ;
    return $output;
}


/**
 * Use this function to display form
 * 
 * @param mixed $form 
 * @access public
 * @return void
 */
function shn_show_form($form)
{
 
    foreach ($form as $x) { // header part of the form         
        
        switch($x['method']) {
        
            case "POST": // POST method
                echo '<form id="dataform" name="',$x['name'],'" method="',$x['method'],'" action="',$x['action'],'">'; 
            break;

            
        }// end of switch
    } // end of header part of the form

	print"<fieldset>";
    foreach ($form as $y) { // body part of the form
		$y['legend']?print"<legend>".($y['legend'])."</legend>":print"";
	}

    foreach ($form as $y) { // body part of the form
                
                switch($y['type']){ // cheack for the 'input' type
                
                case "text": // if 'input' type is *text*
                    echo '<label>'.$y['desc'].'</label>';
                    echo '<input '; 
                    foreach ($y as $k => $v){
                        if($k != 'desc' && $k != 'br') // if $k is NOT equal 'desc' and 'br'
                            echo $k.'="'.$v.'" '; // print
                    }
                    echo '">'; // end of 'text'
                    // this will generate the 'break'.
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                        echo "<br>";    
                    } 
                break;
            

                
                case "password" : // if 'input' type is passward
                    echo '<label>'.$y['desc'].'</label>';
                    echo '<input ';
                    foreach($y as $k => $v) {
                        if ($k != 'desc' && $k != 'br') // if $k is NOT equal 'desc' and 'br'
                            echo $k.'="'.$v.'" ';    
                    }
                    echo '">';
                    // this will generate the 'break'.
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                        echo "<br>";    
                    }
                break; // end of passwd
                
               


                case "hidden" : // if 'input' type is hidden
                    echo '<input type=hidden name=';
                    foreach($y as $k => $v) {
                        if ($k != 'type')
                            echo $k.'="'.$v.'" ';
                    }
                break;


                
                case "radio" : // if 'input' type is *radio*
                    
                    // check for line break request before the radio button
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                        echo "<br>";
                    }
                    // start the radio 
                    echo '<label>'.$y['desc'].'</label>';
                    foreach($y['options'] as $k){
                        //echo $y['class'];
                        $output= '<input type="radio" name="'.$y['name'].'" value="'.$k['value'].'" '.
                            ($y['class']?'class="'.$y['class'].'"':'').' > ';
                        if($y['align']=='right')
                            echo $output.$k['drop_desc'];
                        else
                            echo $k['drop_desc'].$output;
                        // check whether a line break requested...
                        for ($i=1; $i<=$k['br']; $i++)
                        {
                            if ($k['br']==0)
                                break;
                            echo "<br>";
                        }
                        
                } // end of 'radio'
                break;

                
                
                
                
                case "dropdown" : // if 'input' type is *dropdown*

                    echo '<label>'.$y['desc'].'</label>',' <select name="',$y['name'],'">';
                    foreach($y['options'] as $k){ // generating the values for drop down menu
                        if ($k['select']==1){ // check whether which one is defult
                            $select = " selected";
                        } else { // else make it nothing, otherwise it makes all checked
                                $select = "";
                               } // end of the default selection
                                   
                        echo '<option value="'.$k['value'].'"',$select,'>',$k['drop_desc'];
                        
                    }
                    echo '</select><br />';
                                            // check whether a line break requested...
                        for ($i=1; $i<=$k['br']; $i++)
                        {
                            if ($k['br']==0)
                                break;
                            echo "<br>";
                        }                         
                break; //end of 'drop down'
            

                case "location" : // if 'input' type is location
                echo '<label>'.$y['desc'].'</label>';
                global $global;
                include_once $global['approot']."/inc/handler_location.inc";
                echo $output; 
                break;
               
                
                case "checkbox" : // if 'input' type is *check box*
                    if ($y['select']==1){ // check whether which one is defult
                        $select = "checked";
                    } else { // else make it nothing, otherwise it makes all checked
                                $select = "";
                            }
                    
                    if ($y['align']=='right') {
                    echo '<input type="checkbox" name="',$y['name'],'" value="',$y['value'],'"',
                                                        $select,'>',$y['drop_desc'],'<label>',$y['desc'].'</label>';
                    }
                    echo $y['desc'],'<input type="checkbox" name="',$y['name'],'" value="',$y['value'],'"',
                                                        $select,'>',$y['drop_desc'];
                                                        
                    // check whether a line break requested...
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                            echo "<br>";
                        }
                break; // end of checkbox


                
                case "multiselect" : // if 'input' type is a multiple selection
                    echo '<label>'.$y['desc'].'</label>','<select multiple size="',$y['size'],'" name="',$y['name'],'">';
                        foreach($y['option'] as $k){
                            echo '<option ';
                            if ($k['select']==1) // if this option selected...
                                echo 'selected ';
                            echo 'value="',$k['value'],'"> ',$k['drop_desc'],'</option>';
                        }                
                    echo "</select>"; // end of the list
                                            // check whether a line break requested...
                        for ($i=1; $i<=$y['br']; $i++)
                        {
                            if ($y['br']==0)
                                break;
                            echo "<br>";
                        }
                break;
               
                
                case "txtarea" : // if 'input' type is a txtarea
                    echo '<label>'.$y['desc'].'</label>';
                    echo '<textarea name="',$y['name'],'" rows=',$y['rows'],' cols=',$y['cols'],'>';
                    echo '</textarea>';
                    // check whether a line break requested...
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                            echo "<br>";
                        }

                break; //end of txtarea
               
                case "seperator" : // this is a seperator
                    echo "<hr>"; // drow a line ;-)
                break;

            }
    } // end of body part of the form

    print"</fieldset>";

foreach ($form as $x) { // tail part of the form

    switch($x['type']) { // cheack the type
        
        case "submit":
            echo '<input type="submit" value="',$x['value'],'">';
            echo '</form>';
        break;
    } // end of switch
    
}// end of foreach
echo "<br>";

} // end of the show_form function

// vim: set tabstop=4 shiftwidth=4 fdm=marker:


<?php
/*
*
* Sahana HTML form handler
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Pradeeper <pradeeper@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*
*/
// 2nd October 2005

function shn_show_form($form)
{
 
    foreach ($form as $x) { // header part of the form         
        
        switch($x['method']) {
        
            case "POST": // POST method
                echo '<form method="',$x['method'],'" action="',$x['action'],'">'; 
            break;

            
        }// end of switch
    } // end of header part of the form
  


    foreach ($form as $y) { // body part of the form
            switch($y['type']){ // cheack for the 'input' type
                
                
                case "text": // if 'input' type is *text*
                    echo $y['desc'];
                    echo '<input type=text '; 
                    foreach($y as $v){
                       echo 'size=',$v['size'] ,' name="',$v['name'];
                    
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
                    echo $y['desc'];
                    echo '<input type="password" ';
                    foreach($y as $k) {
                        echo 'size=',$k['size'],' name="',$k['name'];
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
                
                
                
                case "radio" : // if 'input' type is *radio*
                    
                    // check for line break request before the radio button
                    for ($i=1; $i<=$y['br']; $i++)
                    {
                        if ($y['br']==0)
                            break;
                        echo "<br>";
                    }
                    // start the radio 
                    echo $y['desc'];
                    foreach($y['options'] as $k){
                       if($y['align']=='right'){ // if radio for right side
                            echo $k['drop_desc'],'<input type="radio" name="',
                                        $y['name'],'" value="',$k['value'],'" >';
                       }else { // default is to have radio on left
                            echo '<input type="radio" name="',
                                        $y['name'],'" value="',$k['value'],'" >',$k['drop_desc'];
                       }
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
                    echo $y['desc'],' <select name="',$y['name'],'">';
                    foreach($y['options'] as $k){ // generating the values for drop down menu
                      echo '<option>',$k['drop_desc'];
                    }
                    echo '</select><br>'; 
                    echo $k['select'];
                break; //end of 'drop down'
            

                
                
                case "checkbox" : // if 'input' type is *check box*
                    if ($y['select']==1){ // check whether which one is defult
                        $select = "checked";
                    } else { // else make it nothing, otherwise it makes all checked
                                $select = "";
                            }
                    
                    if ($y['align']=='right') {
                    echo '<input type="checkbox" name="',$y['name'],'" value="',$y['value'],'"',
                                                        $select,'>',$y['drop_desc'],' ',$y['desc'];
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
                    echo $y['desc'],'<br><select multiple size="',$y['size'],'" name="',$y['name'],'">';
                        foreach($y['option'] as $k){
                            echo '<option ';
                            if ($k['select']==1) // if this option selected...
                                echo 'selected ';
                            echo 'value="',$k['value'],'"> ',$k['drop_desc'],'</option>';
                        }                
                    echo "</select>"; // end of the list
                break;
               
                
                case "txtarea" : // if 'input' type is a txtarea
                    echo '<textarea name="',$y['name'],'" rows=',$y['rows'],' cols=',$y['cols'],'>';
                    echo '</textarea>';
                break; //end of txtarea
               
                case "seperator" : // this is a seperator
                    echo "<hr>"; // drow a line ;-)
                break;

            }
    } // end of body part of the form


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

?>

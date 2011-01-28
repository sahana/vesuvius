<?php
/**
* The Sahana 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author		Sudheera R. Fernando <sudheera@opensource.lk>
* @author		Ravindra De Silva <ravindra@opensource.lk><ravi@computer.org>
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @package		framework
* @subpackage	rms
* @tutorial
* @license		http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

function _shn_html_print_alert($alert)
{
?>
<div class="alert"> <!-- TODO: change style -->
    <strong><?php print _t("Alert") . " : $alert"?></strong>
</div>
<?php
}

function _shn_html_print_message($msg,$br = false)
{
    $br_str = '';
    if ($br == true)
        $br_str = '<br />';
?>
    <div class="message">
    <strong><?php print $msg?></strong>
    <?php print $br_str ?>
    </div>
<?php
}

/**
 * _shn_create_unique_database_field_value 
 * 
 * @param string $base 
 * @param string $width 
 * @param string $table 
 * @param string $field 
 * @access protected
 * @return string
 */

function shn_create_unique_database_field_value($base,$width,$table,$field,$constraints=null){
	global $global;
	$db=$global["db"];
	$not_done=true;
	$retry_limit=10;
	
	$count=0;
	while (($not_done)and ($count<$retry_limit)){
		$uuid=$base[0];
		for($i=0;$i<$width;$i++){
        		if(($num = rand(0,36)) < 27 ) 
            		$uuid .= chr($num+97);
        		else
            		$uuid .= 36 - $num;
    		}
    		
    		$q="select $field from $table where $field='$uuid'";
    		$res=$db->Execute($q);
    		if(($res==NULL)or($res->EOF==true)){
    			$not_done=false;
    		}
    		$count++;
	}
	return $uuid;
}

function shn_reset_form_javascript($form,$reset_what){
?>
<script type="text/javascript">
    function change_action(action){
    		var x=document.getElementsByName("<?php echo $reset_what?>");
    		if(action=="reset"){
            for (i=0; i<=(x[0].options.length); i++){
	            x[0].options[0]=null;
            }
            
            results = db_str.split(",");
            
            for (i=0; i<results.length; i++){
		 	    opt = document.createElement("option") ;
  			    opt.value = results[i] ;
  			    opt.text = results[i].replace(/[^A-Za-z]$/,"");
                x[0].options[i] = opt;
               
            }
           	var remove=document.getElementsByName("removed");
		    var add=document.getElementsByName("added");
		    add[0].value=",";
		    remove[0].value=",";
    		}else{
         	document.<?php echo $form?>.submit();
         	return;
    		}
    } 
</script>
<?php
}

function shn_add_remove_javascript($name,$db_arr,$sort=true)
{
	$count=0;
	foreach ($db_arr as $x) {
		if($count==0){
        			$db_str.=$x;	
        		}else{
        			$db_str.=",".$x;	
        		}
        	$count++;
	}
	$db_str.=",";

            
?>
<script type="text/javascript">
var db_str="<?php echo $db_str;?>"; 
var sort=<?php if($sort==true) {echo "true";}else{ echo "false";}?>;
 // sort function - ascending (case-insensitive)
        function sortFuncAsc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(1);
            if (value1 < value2) return(-1);
            return(0);
        }

        // sort function - descending (case-insensitive)
        function sortFuncDesc(record1, record2) {
            var value1 = record1.optText.toLowerCase();
            var value2 = record2.optText.toLowerCase();
            if (value1 > value2) return(-1);
            if (value1 < value2) return(1);
            return(0);
        }

        function sortSelect(selectToSort, ascendingOrder) {
            if (arguments.length == 1) ascendingOrder = true;    // default to ascending sort

            // copy options into an array
            var myOptions = [];
            for (var loop=0; loop<selectToSort.options.length; loop++) {
                myOptions[loop] = { optText:selectToSort.options[loop].text, optValue:selectToSort.options[loop].value };
            }

            // sort array
            if (ascendingOrder) {
                myOptions.sort(sortFuncAsc);
            } else {
                myOptions.sort(sortFuncDesc);
            }

            // copy sorted options from array back to select box
            selectToSort.options.length = 0;
            for (var loop=0; loop<myOptions.length; loop++) {
                var optObj = document.createElement('option');
                optObj.text = myOptions[loop].optText;
                optObj.value = myOptions[loop].optValue;
                selectToSort.options.add(optObj);
            }
        }

        function add_types(){
			/*we need to check whether the new type is in the database
			if so, notify and reject,therefore check against db_str  */
			var y=document.getElementsByName("type");
			
			// blank space validation added by Ravith.
			y_val = y[0].value 
			y_val.replace(/^\s+|\s+$/g, '')
			
			if(y_val==null || y_val==""){
			     alert("<?php echo _("Whitespace is not a valid input."); ?>");
			     return;
			}
			// end of blank space validation
			var exist=search(db_str,y[0].value);
			
			if(exist){
                alert("<?php echo _t("The type already exists in the list") ?>");
                return;
            }        
            	/*Now we need to check whether we added it during this session
			if so, notify and reject,therefore check against added  */
            var add=document.getElementsByName("added");
            if(add[0].value!=0){
           		exist=search(add[0].value,y[0].value);
            		if(exist){
                		alert("<?php echo _t("The Type Exists,you just added it") ?>");
                		return;
            		}
            	}
            var x=document.getElementsByName("<?php echo $name?>");	
            opt = document.createElement("option") ;
            opt.text = y[0].value ;
            opt.value = y[0].value ;
            var k=x[0].options.length;
            x[0].options[k]=opt;
            if(sort==true){
            		sortSelect(x[0], true) ;
            	}
            add[0].value=add[0].value+y[0].value+",";
            y[0].value=null;
            
        }

        function remove_types(){
            var x=document.getElementsByName("<?php echo $name?>");
            removeSelectedOptions(x[0]);
            if(sort==true){
            		sortSelect(x[0], true) ;
            	}
        }

        function hasOptions(obj) {
    	    if (obj!=null && obj.options!=null) { return true; }
	            return false;
	    }
	
        function removeSelectedOptions(from) { 
	        if (!hasOptions(from)) { return; }
	        if (from.type=="select-one") {
		        from.options[from.selectedIndex] = null;
		    }
	        else {
		        var remove=document.getElementsByName("removed");
		        z=document.getElementsByName("added");
		        var add=new String(z[0].value);
		        for (var i=(from.options.length-1); i>=0; i--) { 
        			var o=from.options[i]; 
			        if (o.selected) { 
					    exist=search(db_str,o.text);
					    if(exist){
					    		remove[0].value= remove[0].value+","+o.value;
					    		// remove the removed value from db_str
					    		var vals = db_str.split(",");
					    		db_str="";
					    		for(n=0;n<vals.length;n++){
					    			if(vals[n].length>0){
					    				// not a blank string
					    				if(vals[n].toLowerCase() != o.text.toLowerCase()){
					    					db_str += (vals[n]+",");
					    				} 
					    			}
					    		}
					    }else{
					    		z[0].value=search_and_replace(add,o.text);	
					    }
				        from.options[i] = null; 
				    }
			  		}
            }
             	from.selectedIndex = -1; 

	    } 

        function search(str_arr,value){
        		value=value+",";
        		if (window.RegExp) {
            		var re = new RegExp(value);
        			if (re.test(str_arr)) {
            			return true;
            		}
            }
           
            return false;
        }
        
        function search_and_replace(str_obj,value){
        	    	value=value+",";
        		if (window.RegExp) {
            		var re = new RegExp(value);
        			str_obj=str_obj.replace(re,"");  
        		}
        		return new String(str_obj);
        }
	
</script>
<?php
}

function shn_action_change_javascript($form,$change)
{
?>
<script type="text/javascript">
    function change_action(action){
        var x=document.getElementsByName("<?php echo $change?>");
         x[0].value=action;
         document.<?php echo $form?>.submit();
         return;
    }
</script>
<?php
}

function obj2array($obj) {
  $out = array();
  foreach ($obj as $key => $val) {
    switch(true) {
        case is_object($val):
         $out[$key] = obj2array($val);
         break;
      case is_array($val):
         $out[$key] = obj2array($val);
         break;
      default:
        $out[$key] = $val;
    }
  }
  return $out;
}


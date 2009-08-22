<?php
/**Internal Library of the Catalog 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @author     Sanjeewa Jayasinghe <sditfac@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot'] . "/inc/lib_form.inc";


/**
 * Generates the java script required for AJAX functionality 
 * 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_sub_cat_jscript($max,$form,$change,$item_flag = false)
{
    global $global;
    $fetch_server = "index.php?";
?>           
<script type="text/javascript">
	var url = "<?php echo $fetch_server?>"; 
    var curlevel = 0;
    var http;
    var null_data;
    var max=<?php echo $max ?>;
    
    function getHTTPObject() {
        var xmlhttp;
        //conditional compliation
        /*@cc_on
        @if (@_jscript_version >= 5)
            try {
                xmlhttp = new ActiveXObject("Msxml2.XMLHTTP");
            } catch (e) {
                try {
                    xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
                } catch (E) {
                    xmlhttp = false;
                }
            }
        @else
            xmlhttp = false;
        @end @*/

        if (!xmlhttp && typeof XMLHttpRequest != 'undefined') {
            try {
                xmlhttp = new XMLHttpRequest();
            } catch (e) {
            xmlhttp = false;
            }
        }
    return xmlhttp;
    }

    // The callback funtion
    function handleHttpResponse() {
        if (http.readyState == 4) { // Split the comma delimited response into an array  
                results = http.responseText.split(",");
            if (results[0] != "null") {
                    null_data = false;
                    curlevel = curlevel+1;
                     var x = document.getElementsByName(curlevel);
                     x[0].style.visibility = 'visible';
                    j = 0;
                 var x = document.getElementsByName(curlevel);
                for (i = 0; i <= x[0].options.length+1; i++){
                        x[0].options[0] = null;
                    }
                    for (i = 1; i < results.length-1; i = i+2, j++) {
                         opt = document.createElement("option") ;
                          opt.value = results[i] ;
                          opt.text = results[i+1].replace(/[^A-Za-z0-9]$/,"");
                          x[0].options[j] = opt;
                        x[0].selectedIndex = -1;
                    }
                } else {
                    null_data = true;
                }

            for (i = max; i > curlevel; i = i-1) {
                 var x = document.getElementsByName(i);
                 x[0].style.visibility = 'hidden';

             }
       
        } 
    }

    function update_next_level(selection,level)
    {
        curlevel = level;
    	var item_flag = "<?php echo $item_flag?>"; 
        http = getHTTPObject();
        var url2 = url + "act=sub_cat&mod=xst&stream=text&cat=" + selection+"&flag="+item_flag;
        http.open("GET", url2, true); 
//      http.onreadystatechange = null; 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
    
    function set_name_submit()
    {
        var name = "";
        var element = "";
        var last_lvl;
        
            if(null_data == true){
                last_lvl = curlevel+1 ;
            } else {
                last_lvl = curlevel;
            }
            
            for(i = 0;i < last_lvl;i++) {
                    element = "\""+i+"\"";
                var x = document.getElementsByName(i);
                if(i+1 == last_lvl) {
                    name = name+x[0].options[x[0].selectedIndex].text;
                } else {
                    name = name+x[0].options[x[0].selectedIndex].text+"->";
                }
        	}
        
        var x = document.getElementsByName("<?php echo $change?>");
        x[0].value = name;
        document.<?php echo $form;?>.submit();
        return;
    }
    
     var x = document.getElementsByName(0);
     x[0].selectedIndex = -1;
    for (i = max; i > 0; i = i-1) {
    	var x = document.getElementsByName(i);
        x[0].style.visibility = 'hidden';
    }
</script>
<?php
}


/**
 * shn_location 
 * Generates a set of select boxes with locations with in the given levels. Will add to the form. 
 * @param mixed $from 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_sub_cat($max,$form,$inventory_id,$item_flag = false)
{
    $parent_array = array();
    
    global $global;
    $db = $global["db"];
    
    if ($item_flag == true) {
		$query = "SELECT name,ct_uuid FROM ct_catalogue WHERE parentid = '0' AND final_flag = '0' ";
    	$res = $db->Execute($query);
    } else {
    	$query = "SELECT name,ct_uuid FROM ct_catalogue WHERE parentid = '0' ";
    	$res = $db->Execute($query);
    }
    
	$parent_array["none"] = "";
    while (!$res == NULL && !$res->EOF) {
    	$parent_array[$res->fields["ct_uuid"]] = $res->fields["name"];
    	$res->MoveNext();
    }
    
    if ($parent_array == null) {
    	$parent_array["1"] = _t("None");
    	shn_form_fsopen(_t('Information'));
    	?>
    	<p><?php echo  _t('There is no catalog found by that name'); ?><a href="index.php?mod=cs&act=addmain"><?php echo  _t("Add Catalog"); ?></a><?php echo  _t(' First'); ?></p> 
    	<?php
    	shn_form_fsclose();
    } else {
    	shn_form_fsopen(_t("Select the Catalog"));
    	$select_opts = 'onChange=update_next_level(this.options[this.selectedIndex].value,0)';    
    	shn_form_select($parent_array,'',0,$select_opts,null);
    	shn_form_fsclose();
    	shn_form_fsopen(_t('Select the Category or Classification'));
    		
    	for ($i = 1; $i < $max + 1; $i++) {
    		$select_opts = 'onChange=update_next_level(this.options[this.selectedIndex].value,' . $i . ') visible="false"';    
    		shn_form_select(array(),'',$i,$select_opts,null);
    	}
    		
    	shn_sub_cat_jscript($max,$form,"item_name",$item_flag);
    	shn_form_hidden(array('item_name' => ""));
    	shn_form_hidden(array('inventory_id' => $inventory_id));
    	//_shn_cs_item_name_javascript("item_name",$max,$form);
    	shn_form_button(_t("Next"),"onClick='set_name_submit()'");
    	shn_form_fsclose();
    
    //shn_form_submit(_t("Next"));
    }
}


function _shn_cs_item_name_javascript($change,$levels,$form)
{
?>
<script type="text/javascript">
    function set_name_submit()
    {
            var lvl = <?php echo $levels;?>
            var name;
            alert(lvl);
            for(i = 0 ; i < lvl; i++) {
                var x = document.getElementsByName("<?php echo $change?>");
                name = name + "-" + x[0].value;
        	}
        
        var x = document.getElementsByName("<?php echo $change?>");
        x[0].value = name;
        document.<?php echo $form;?>.submit();
        return;
    }
</script>
<?php
}

/**.
 *This function returns the unit array of a particular item 
 * @access public
 * @return array
 */
function get_unitid_array()
{    
    global $global;
    $db = $global["db"];
    
    $itemid = get_itemid();

    $itemarray = array();
    $query = "SELECT * FROM ct_cat_unit WHERE ct_uuid = '$itemid'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
    	$temp2 = $res->fields['unit_uuid'];
    	$query = "SELECT name FROM ct_unit WHERE unit_uuid = '$temp2'";
    	$unit_res = $db->Execute($query);    
    	$itemarray[$res->fields['unit_uuid']] = $unit_res->fields['name'];
    	$res->MoveNext();
    }

    return $itemarray;
}

/**.
 *This function returns the item ID 
 * @access public
 * @return varchar
 */
function get_itemid()
{

    $itemid = trim($_POST['0']);
    // this 5 should be replaced by the $max that is retrieved from the DB
	$max_depth = get_max_depth();
    for ($i = 1; $i < $max_depth; $i++) {
        $itemid = trim($_POST[$i]);
    
        if ($itemid == null) {
        	$itemid = $_POST[$i - 1];
        	break;
        }
    }

	return $itemid;
}

/**.
 *This function the multiplier of unit convertion
 * @access public
 * @return double
 */
function unit_converter($from_unit_id,$to_unit_id)
{

    global $global;
    $db = $global["db"];

    $query1 = "SELECT multiplier FROM ct_unit WHERE unit_uuid = '$from_unit_id'";
    $res1 = $db->Execute($query1);
    $from_multiplier = $res1->fields['multiplier'];
    if ($from_multiplier == 0) {
        $from_multiplier = 1;
    }

    $query2 = "SELECT multiplier FROM ct_unit WHERE unit_uuid = '$to_unit_id'";
    $res2 = $db->Execute($query2);
    $to_multiplier = $res2->fields['multiplier'];
    
    if ($to_multiplier == 0) {
        $to_multiplier = 1;
    }

    $multiplier = $to_multiplier / $from_multiplier;

    return $multiplier;
    
}

/**.
 *This function return the unit name of given unit id
 * @access public
 * @return varchar
 */
function get_unit_name($unit_id)
{
    global $global;
    $db = $global["db"];
    $query = "SELECT name FROM ct_unit WHERE unit_uuid = '$unit_id'";
    $res = $db->Execute($query);
    $name = $res->fields['name'];

    return $name;
}

/**.
 *This function return all the unit names
 * @access public
 * @return array
 */
function get_all_unit_names()
{
	global $global;
    $db = $global["db"];
    $query = "SELECT name FROM ct_unit";
    $res = $db->Execute($query);
    $unit_name_arr = array();

    while (!$res == NULL && !$res->EOF) {
    	array_push($unit_name_arr,$res->fields['name']);
    	$res->MoveNext();
    }
    
    return $unit_name_arr;
}


/**
 * This function validates the selected catalog in sub_cat form.
 *This function is called by shn_cs_additem_form1_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_sub_cat_form()
{
	$error_flag = false;
	clean_errors();

	$itemid = null;
	$max_depth = get_max_depth();
	
    for ($i = 0; $i < $max_depth; $i++) {
    	$itemid = trim($_POST[$i]);
        if ($itemid != null) {
        break;
        }
    }

    if ($itemid == null || $itemid == 'none') {
    	add_error(_t("Please select the Catalog that you need"));
    	$error_flag = true;
    }    

	return $error_flag;
}


/**.
 *This function returns the unit array of a particular item 
 * @access public
 * @return array
 */
function _shn_cs_get_units($parent_id)
{
    global $global;
    $db = $global["db"];

    $myoptions = array();

    $query = "SELECT * FROM ct_cat_unit WHERE ct_uuid = '$parent_id'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
	    $temp2 = $res->fields['unit_uuid'];
    	$query1 = "SELECT name FROM ct_unit WHERE unit_uuid = '$temp2'";
    	$res2 = $db->Execute($query1);

    	$myoptions[$res->fields['unit_uuid']] = $res2->fields['name'];
    	$res->MoveNext();
    }
    
    return $myoptions;
}


/**.
 *This function returns the maximum depth of the catalog/Item tree 
 * @access public
 * @return double
 */
function get_max_depth()
{
    global $global;
    $db = $global['db'];

    $query = "SELECT option_code FROM field_options WHERE field_name = 'opt_cs_depth'";
    $res = $db->Execute($query);
    $depth = $res->fields["option_code"];

    return $depth;
}

/**.
 *This function returns base unit of the category that the given unit belongs to  
 * @access public
 * @return varchar unit_uuid
 */

function convert_to_base_unit($unit_id)
{
    global $global;
    $db = $global['db'];

    $query1 = "SELECT unit_type_uuid FROM ct_unit WHERE unit_uuid = '$unit_id'";
    $res1 = $db->Execute($query1);
    $unit_type_uuid = $res1->fields['unit_type_uuid'];

    $query2 = "SELECT unit_uuid FROM ct_unit WHERE unit_type_uuid = '$unit_type_uuid' AND base_flag = '1' ";
    $res2 = $db->Execute($query2);
    $base_unit_uuid = $res2->fields['unit_uuid'];

    return $base_unit_uuid;
}

/**.
 *This function returns the array of parent ID array of a particular item 
 * @access public
 * @return array
 */
 
function shn_cs_get_parentid_arr($in_id)
{
    global $global;
    $db = $global['db'];
    $temp_cat_parent_arr = array();
    $final_parent_id_array = array();

    $query = "SELECT parentid FROM ct_catalogue WHERE ct_uuid = '$in_id'";
    $res = $db->Execute($query);
    $par_id = $res->fields["parentid"];

    $final_parent_id_array = _shn_cs_recursive_parent_search($temp_cat_parent_arr,$par_id);

    return $final_parent_id_array;
}

/**.
 *This function do a recurcive search to find the parents of a particular catalog/ item
 * @access private
 * @return array
 */
function _shn_cs_recursive_parent_search($in_array,$parent_id_in)
{
    global $global;
    $db = $global['db'];

    if ($parent_id_in == '0') {
    	array_push($in_array,$parent_id_in);
    	return $in_array;
    } else {
    	array_push($in_array,$parent_id_in);
    	$query = "SELECT parentid FROM ct_catalogue WHERE ct_uuid = '$parent_id_in'";
    	$res = $db->Execute($query);
    	$par_par_id = $res->fields["parentid"];
    	return _shn_cs_recursive_parent_search($in_array,$par_par_id);
    }
}

/**.
 *This function returns the array of child ID array of a particular item 
 * @access public
 * @return array
 * @todo
 */
function shn_cs_get_child_id_arr($in_id)
{

}

/**.
 *This function returns the array of next level child ID array of a particular item catalog
 * @access public
 * @return array
 * @todo
 */
function shn_cs_get_next_level_child_id_arr($in_id)
{
    $next_level_ID_arr = array();
    global $global;
    $db = $global['db'];
    $query = "SELECT ct_uuid FROM ct_catalogue WHERE parentid = '$in_id'";
    $res = $db->Execute($query);

    while (!$res == NULL && !$res->EOF) {
    	array_push($next_level_ID_arr,$res->fields["ct_uuid"]);
    	$res->MoveNext();
    }
   return $next_level_ID_arr;
}

/**.
 *This function returns the level number of the item/catalogue 
 * @access public
 * @return int
 */
function shn_cs_get_level_count($in_id)
{
    return count(shn_cs_get_parentid_arr($in_id));
}

function shn_cs_generate_maincat_serial()
{
    global $global;
    $db = $global['db'];
	$temp_serial_arr = array();

    $serial_query = "SELECT serial FROM ct_catalogue WHERE parentid = '0'";
    $serial_res = $db->Execute($serial_query);
	while (!$serial_res == NULL && !$serial_res->EOF) {
		array_push($temp_serial_arr,($serial_res->fields["serial"]));
		$serial_res->MoveNext();
	}
	rsort($temp_serial_arr,SORT_NUMERIC);
	$next_serial = $temp_serial_arr[0] + 1;
	$next_serial .= ".";

    return $next_serial;
}

function shn_cs_generate_subcat_item_serial($parent_id_in)
{
    global $global;
    $db = $global['db'];

	//this will give the parents serial number
    $parent_serial_query = "SELECT serial FROM ct_catalogue WHERE ct_uuid = '$parent_id_in'";
    $parent_serial_res = $db->Execute($parent_serial_query);

	$serial_item_arr = explode(".",$parent_serial_res->fields["serial"]);
	array_pop($serial_item_arr);

    $child_serials_query = "SELECT serial FROM ct_catalogue";
    $child_serials_res = $db->Execute($child_serials_query);
	$child_serial_arr = array();
	
	while (!$child_serials_res == NULL && !$child_serials_res->EOF) {
	    $child_item_arr = explode(".",$child_serials_res->fields["serial"]);
	    array_pop($child_item_arr);
		$flag = false;
			
		for ($x = 0; $x < count($serial_item_arr); $x++) { 
		    if (($serial_item_arr[$x]) == ($child_item_arr[$x])) {
		    	$flag = true;
		    	continue;
		    } else {
		    	$flag = false;
		    	break;
		    }
		}

		if ($flag == true) {
		    $num = count($serial_item_arr);
			if (isset($child_item_arr[$num])) {
		    	array_push($child_serial_arr,$child_item_arr[$num]);
		    } else {
		    	array_push($child_serial_arr,'0');
		    }
		}
		$child_serials_res->MoveNext();
	}//end of while

	rsort($child_serial_arr,SORT_NUMERIC);
	$next_serial_suffix = $child_serial_arr[0] + 1;
	$next_serial_suffix .= ".";
	$next_serial = ($parent_serial_res->fields["serial"]) . $next_serial_suffix;

    return $next_serial;
}


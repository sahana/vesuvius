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
* @author    Sanjeewa Jayasinghe <sditfac@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/

global $global;
include_once $global['approot']."/inc/lib_form.inc";


/**
 * Generates the java script required for AJAX functionality 
 * 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_sub_cat_jscript($max,$form,$change,$item_flag=false){
    global $global;
    $fetch_server="xml.php?";
?>           
<script type="text/javascript">
    var url = "<?php echo $fetch_server?>"; 
   	var curlevel=0;
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
    function handleHttpResponse(){
        if (http.readyState == 4) { // Split the comma delimited response into an array  
            	results = http.responseText.split(",");
            if (results[0]!="null"){
            		null_data=false;
            		curlevel=curlevel+1;
     	    		var x=document.getElementsByName(curlevel);
     	    		x[0].style.visibility='visible';
        			j=0;
			 	var x=document.getElementsByName(curlevel);
				for (i=0; i<=x[0].options.length+1; i++){
	            		x[0].options[0]=null;
            		}
            		for (i=1; i<results.length-1; i=i+2, j++){
		 	    		opt = document.createElement("option") ;
  			    		opt.value = results[i] ;
  			    		opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
  			    		x[0].options[j] = opt;
                		x[0].selectedIndex=-1;
            		}
            	}else{
            		null_data=true;
            	}

            for (i=max; i>curlevel; i=i-1){
             	var x=document.getElementsByName(i);
             	x[0].style.visibility='hidden';
		 	    
		 	}
       
        } 
    }

    function update_next_level(selection,level){
     	curlevel=level;
	var item_flag = "<?php echo $item_flag?>"; 
        http = getHTTPObject();
        var url2=url + "act=sub_cat&cat=" + selection+"&flag="+item_flag;
      	http.open("GET", url2, true); 
//        http.onreadystatechange = null; 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
    
    	   function set_name_submit()
    {
    		var name="";
    		var element="";
    	    var last_lvl;
    		if(null_data==true){
    			last_lvl= curlevel+1 ;
    		} else{
    			last_lvl= curlevel;
    		}
    	    for(i=0;i<last_lvl;i++){
    	    		element="\""+i+"\"";
    			var x=document.getElementsByName(i);
    			if(i+1==last_lvl){
        			name=name+x[0].options[x[0].selectedIndex].text;
        		}else{
        			name=name+x[0].options[x[0].selectedIndex].text+"->";
        		}
        }
        
        var x=document.getElementsByName("<?php echo $change?>");
        x[0].value=name;
        document.<?php echo $form;?>.submit();
        return;
    }
    
     var x=document.getElementsByName(0);
     x[0].selectedIndex=-1;
    for (i=max; i>0; i=i-1){
    		var x=document.getElementsByName(i);
        x[0].style.visibility='hidden';
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
function shn_sub_cat($max,$form,$item_flag=false)
{
	
	$parent_array=array();
	
	global $global;
	$db=$global["db"];
	if($item_flag==true)
		{
		$query="select name,ct_uuid from ct_catalogue where parentid='0' and final_flag='0' ";
		$res=$db->Execute($query);
		}
	else
		{
		$query="select name,ct_uuid from ct_catalogue where parentid='0' ";
		$res=$db->Execute($query);
		}
	
	while(!$res==NULL && !$res->EOF)
	{
	$parent_array[$res->fields["ct_uuid"]]=$res->fields["name"];
	$res->MoveNext();
	}
	
	if($parent_array==null){
	$parent_array["1"]=_("None");
	shn_form_fsopen(_('Information'));
	?>
	<p><?= _('There is no any root catalogue found. '); ?><a href="index.php?mod=cs&act=addmain">Add root Catalogue</a><?= _(' First'); ?></p>
	
	<?php
	shn_form_fsclose();
	}

	else{
	shn_form_fsopen(_("Select the root Category"));
	$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,0)';	
	shn_form_select($parent_array,'',0,$select_opts,null);
	shn_form_fsclose();
	shn_form_fsopen(_('Select the sub category'));
	for($i=1;$i<$max+1;$i++){
	$select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$i.') visible="false"';	
	shn_form_select(null,'',$i,$select_opts,null);
	}
	shn_sub_cat_jscript($max,$form,"item_name",$item_flag);
	shn_form_hidden(array('item_name'=>""));
	//_shn_cs_item_name_javascript("item_name",$max,$form);
	shn_form_button(_("Next"),"onClick='set_name_submit()'");
	shn_form_fsclose();
	
	//shn_form_submit(_("Next"));
	}
}

function _shn_cs_item_name_javascript($change,$levels,$form)
{
?>
<script type="text/javascript">
    function set_name_submit()
    {
    		var lvl=<?php echo $levels;?>
    	    var name;
    	    alert(lvl);
    	    for(i=0;i<lvl;i++){
    			var x=document.getElementsByName("<?php echo $change?>");
        		name=name+"-"+x[0].value;
        }
        
        var x=document.getElementsByName("<?php echo $change?>");
        x[0].value=name;
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
	$db=$global["db"];
	
	$itemid=get_itemid();

	$itemarray=array();
	$query="select * from ct_cat_unit where ct_uuid='$itemid'";
	$res=$db->Execute($query);

	while(!$res==NULL && !$res->EOF)
	{
	$temp2=$res->fields['unit_uuid'];
	$query="select name from ct_unit where unit_uuid ='$temp2'";
	$unit_res=$db->Execute($query);	
	$itemarray[$res->fields['unit_uuid']]=$unit_res->fields['name'];
	$res->MoveNext();
	}

return $itemarray;
}

/**.
 *This function returns the unit array of the 
 * @access public
 * @return varchar
 */
function get_itemid()
{

	$itemid = trim($_POST['0']);
	// this 5 should be replaced by the $max that is retrieved from the DB
	for($i=1;$i<5;$i++)
	{
	$itemid = trim($_POST[$i]);
	
		if($itemid==null)
		{
		$itemid = $_POST[$i-1];
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
	$db=$global["db"];

	$query1="select multiplier from ct_unit where unit_uuid='$from_unit_id'";
	$res1=$db->Execute($query1);
	$from_multiplier=$res1->fields['multiplier'];
	if ($from_multiplier==0)
	{
		$from_multiplier=1;
	}

	$query2="select multiplier from ct_unit where unit_uuid='$to_unit_id'";
	$res2=$db->Execute($query2);
	$to_multiplier=$res2->fields['multiplier'];
	if ($to_multiplier==0)
	{
		$to_multiplier=1;
	}

	$multiplier=$to_multiplier/$from_multiplier;

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
	$db=$global["db"];
	$query="select name from ct_unit where unit_uuid='$unit_id'";
	$res=$db->Execute($query);
	$name=$res->fields['name'];

	return $name;
}


/**
 * This function validates the selected catalogue in sub_cat form.
 *This function is called by shn_cs_additem_form1_submit() in main.inc
 * @access private
 * @return boolean
 */
function _shn_cs_validate_sub_cat_form()
{
$error_flag=false;
clean_errors();

$itemid=null;

	for($i=0;$i<5;$i++)
	{
	$itemid = trim($_POST[$i]);
		if($itemid!=null)
		{
		break;
		}
	}

	if($itemid==null)
	{
	add_error(_("Please Select the Catalogue that you need"));
	$error_flag=true;
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
	$db=$global["db"];

	$myoptions=array();

	$query="select * from ct_cat_unit where ct_uuid='$parent_id'";
	$res=$db->Execute($query);

	while(!$res==NULL && !$res->EOF)
	{
	$temp2=$res->fields['unit_uuid'];
	$query1="select name from ct_unit where unit_uuid ='$temp2'";
	$res2=$db->Execute($query1);

	$myoptions[$res->fields['unit_uuid']]=$res2->fields['name'];;
	$res->MoveNext();
	}
	
	return $myoptions;
	
}


/**.
 *This function returns the maximum depth of the catalogue/Item tree 
 * @access public
 * @return double
 */
function get_max_depth()
{
	global $global;
	$db=$global['db'];

	$query="select option_code from field_options where field_name='opt_cs_depth'";
	$res=$db->Execute($query);
	$depth=$res->fields["option_code"];

	return $depth;
}


?>

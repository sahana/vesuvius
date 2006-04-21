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
function shn_sub_cat_jscript($max,$form,$change){
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
        http = getHTTPObject();
        var url2=url + "act=sub_cat&cat="+selection;
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
function shn_sub_cat($max,$form)
{
	
	$parent_array=array();
	
	global $global;
	$db=$global["db"];
	$query="select name,ct_uuid from ct_catalogue where parentid='0' ";
	$res=$db->Execute($query);
	
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
	shn_sub_cat_jscript($max,$form,"item_name");
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
 *This function returns the unit array of the 
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



?>

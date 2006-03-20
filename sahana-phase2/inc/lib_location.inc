<?php
/**
 *
 * This is the location library. A vital component of the framework.
 * locations are used by several modules like organization regsitry,Camp registry 
 * This library has nearly everything you need to do with locations 
 * 
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage location
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */


global $global;
include_once $global['approot']."/inc/handler_form.inc";


/**
 * Returns a comma seperated string of descendants 
 * 
 * @param mixed $loc 
 * @access public
 * @return void
 */
function shn_location_get_descendants($loc)
{
    global $global;
    $db=$global["db"];
    $q="select search_id from location where location_id=$loc";
    $res=$db->Execute($q);
    $search="'".$res->fields[0]."%'";
    $q="select location_id from location where search_id LIKE $search";
    $res=$db->Execute($q);
    while(!$res==NULL && !$res->EOF){
         $loc=$loc."{$res->fields[0]}";
            $res->MoveNext();
            if(!$res->EOF)
                $loc=$loc.",";
    }
   return  $loc; 
}


/**
 * Returns an array containing location levels(code,description)
 * suitable to be used in a select box.
 * 
 * @access public
 * @return void
 */
 /*
function shn_location_levels_form()
{
    global $global;
    $db=$global["db"];
    $q = "select option_code,option_description from field_options where field_name='opt_location_type'";
    $res=$db->Execute($q);
    $options=array();
    while(!$res==NULL && !$res->EOF){
        array_push(
            $options,
            array(  'drop_desc'=>$res->fields[1],
                        'value'=>$res->fields[0],
            )       
        );
        $res->MoveNext();
    }
    return $options;
}
*/
function shn_location_level_range_form($name,$label,$sel)
{
    global $global;
    $db=$global["db"];
    $q = "select option_code,option_description from field_options where field_name='opt_location_type'";
    $res=$db->Execute($q);
    $options=array();
    while(!$res==NULL && !$res->EOF){
        $options[$res->fields[0]]=$res->fields[0]."---".$res->fields[1];
              
        $res->MoveNext();
    }
    $extra_opts['value']=$sel;
    $extra_opts['req']=true;
    shn_form_fsopen($label);
    shn_form_select($options,$label, $name,$select_opts = "", $extra_opts);
 	shn_form_fsclose();
}

/**
 * Returns the list of parents of the location. Starting from country for each
 * level the name and location id is returned. 
 * 
 * @param mixed $child 
 * @access public
 * @return array
 */
function shn_get_parents($child)
{
    global $global;
    $db=$global['db'];
    $q="select search_id,name,location_id from location where location_id=$child";
    $res_temp=$db->Execute($q);
    $final=array();
    $final[0]=$res_temp->fields[0];
    $final[1]=$res_temp->fields[1];
    $final[2]=$res_temp->fields[2];
    $bsd_village=$res_temp->fields[0];
    $loc=split("\.", $bsd_village);
    $loc_return=array();
    for($k=0;$k<count($loc)-1;$k++){
        $cur=$cur.$loc[$k];
        $temp=array();
        $temp[0]=$cur;     
        $q="select name,location_id from location where search_id='$cur'";
        $res_loc=$db->Execute($q);
        $temp[1]=$res_loc->fields[0];
        $temp[2]=$res_loc->fields[1];
        array_push(
            $loc_return,
            $temp
            );
        if($k!=count($loc)-1){
            $cur=$cur.".";
        }
	}
        array_push(
            $loc_return,
            $final
            );
     return $loc_return;
}

/**
 * Returns the level of the location 
 * 
 * @param mixed $loc 
 * @access public
 * @return mixed
 */
function shn_get_level($loc){
    global $global;
    $db=$global['db'];
    $q="select option_code from field_options,location where field_options.option_code =location.opt_location_type and location.location_id=$loc and field_name='opt_location_type'";
    $res=$db->Execute($q);
    return $res->fields[0];
}

/**
 * Returns whether the location is in the last level or not 
 * 
 * @param mixed $loc 
 * @access public
 * @return bool
 */
function shn_is_last_level($loc){
    global $global;
    $db=$global['db'];
    $q="select option_code from field_options where field_name='opt_location_type' order by option_code desc";
    $res=$db->Execute($q);
    $last=$res->fields[0];
    $q="select option_code from field_options,location where field_options.option_code =location.opt_location_type and location.location_id=$loc and field_name='opt_location_type'";
    $res=$db->Execute($q);
    if($last==$res->fields[0]){
        return true;
    }else {
        return false;
    }

}

/**
 * Returns the last location level avaliable 
 * @param mixed $loc
 * @access public
 * @return void
 */
function shn_get_last_level(){
    global $global;
    $db=$global['db'];
    $q="select option_code,option_description from field_options where field_name='opt_location_type' order by option_code desc";
    $res=$db->Execute($q);
    $last=array();
    $last[0]=$res->fields[0];
    $last[1]=$res->fields[1];
    return $last;

}

/**
 * Generates the java script required for AJAX functionality 
 * 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location_jscript($to){
    global $global;
    $fetch_server="xml.php?";
?>           
<script type="text/javascript">
    var url = "<?php echo $fetch_server?>"; 
    var curlevel=0;
    var http;
    var to=<?php echo $to ?>;
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

            curlevel=curlevel+1;
            var x=document.getElementsByName(curlevel);
            for (i=0; i<=x[0].options.length+1; i++){
	            x[0].options[0]=null;
            }
            var next=results[1];
            j=0;
            for (i=1; i<results.length-1; i=i+2, j++){
		 	    opt = document.createElement("option") ;
  			    opt.value = results[i] ;
  			    opt.text = results[i+1].replace(/[^A-Za-z]$/,"");
                x[0].options[j] = opt;
               //x[0].appendChild(opt);
            }
            if(curlevel<to){
                 update_next_level(next,curlevel);
            }
        } 
    }

    function update_next_level(selection,level){
        curlevel=level;
        http = getHTTPObject();
        var url2=url + "act=get_loc&lvl="+curlevel+"&sel="+selection;
        http.open("GET", url2, true); 
//        http.onreadystatechange = null; 
        http.onreadystatechange = function(){}; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
</script>
<?php
}

/**
 * Generates a set of select boxes with locations with in the given levels. Will add to the form. 
 * 
 * @param mixed $from 
 * @param mixed $to 
 * @param mixed $value( if the value is given ,select boxes will be
 * poplulated with locations related to that value) 
 * @access public
 * @return void
 */
 /*
function shn_location_form($from,$to,$value=NULL){
	shn_location_jscript($to);
	if($value!=NULL){
        $location_inf = _shn_location_form_value($from,$to,$value);  
	}else {
        $location_inf = _shn_location_form($from,$to);  
	}
	shn_form_add_component_list($location_inf,$section=true,$legend='',$return=false,$default_val_req=$error);
}
*/
/**
 * shn_location 
 * Generates a set of select boxes with locations with in the given levels. Will NOT add to the form. 
 * @param mixed $from 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location($range){
	shn_location_jscript($range["end"]);
	$location_inf = _shn_location_form($range);  
	return $location_inf ;
}

/**
 * Generates a set of select boxes with locations with the given parent, with in the given levels. 
 * Will NOT add to the form.  
 * 
 * @param mixed $parent 
 * @param mixed $to 
 * @access public
 * @return void
 */
function shn_location_parent($parent,$range){
	shn_location_jscript($range["end"]);
	$location_inf = _shn_location_form_parent($parent,$range);  
	return $location_inf ;
}

/**
 * Generates a set of select boxes with locations with all the levels. 
 * Will NOT add to the form.  
 * 
 * @access public
 * @return void
 */
function shn_location_all(){
    global $global;
//    $db=$global['db'];
//    $q="select option_code from field_options where field_name='opt_location_type' order by option_code";
//    $res=$db->Execute($q);
//    $from=$res->fields[0];
//    $res->MoveLast();
//    $to=$res->fields[0];
	$range= shn_or_get_loc_range();
   	shn_location_jscript($range["end"]);
	$location_inf = _shn_location_form($range);  
	return $location_inf ;
}

/**
 * Generates a set of select boxes with locations with in the given levels.
 * Originally developed for organization regsitry in mind,but there
 * is a better method now.
 * @deprecated version - Jan 31, 2006
 * @param mixed $from 
 * @param mixed $to 
 * @param mixed $value 
 * @access public
 * @return void
 */
function shn_location_form_org($range,$value=NULL)
{
	shn_location_jscript($range["end"]);
	if($value!=NULL){
        _shn_location_form_value($range,$value);  
	}else {
        _shn_location_form($range);  
	}
   // shn_form_add_component_list($location_inf,$section=true,$legend='Base Location *(req)',$return=false,$default_val_req=$error);
}

/**
 * Adds a location to the database.Retrives the values to insert from the POST variables. 
 * 
 * @access public
 * @return void
 */
function shn_location_add()
{
    global $global;
    $db=$global['db'];
    $loc=$_POST{"loc_name"};
    $desc=$_POST{"desc"};
    $iso=$_POST{"iso"};
    $level=$_POST{"level"};
    if($level==1){
        $q="INSERT INTO location(parent_id,search_id,opt_location_type,name,iso_code,description) VALUES (0,'0','1','{$loc}','{$iso}','{$desc}')";
        $res=$db->Execute($q);
        $q="select location_id from location where name='{$loc}' and opt_location_type=1";
        $res=$db->Execute($q);
        $id=$res->fields[0];
        $q="update location set search_id=$id where location_id=$id";
        $res=$db->Execute($q);
    }else {
        $level=$level-1;
        $parent=$_POST{"$level"};
        $level=$level+1;
        $q="select count(*) from location where parent_id=$parent";
        $res=$db->Execute($q);
        $count=$res->fields[0]+1;
        $q="select search_id from location where location_id=$parent";
        $res=$db->Execute($q);
        $search_id=$res->fields[0].".".$count;
        $q="INSERT INTO location(parent_id,search_id,opt_location_type,name,iso_code,description) VALUES ($parent,'{$search_id}','{$level}','{$loc}','{$iso}','{$desc}')";
        $res=$db->Execute($q);
    }
}

function _shn_location_form_parent($parent,$range){   
    global $global;
    $db=$global['db'];
    $value=$parent;
    $loc=array();
    $loc_arr=shn_or_get_parents($value);
    $parent_level=shn_get_level($parent);
    $from=$range["start"];
    $to=$range["end"];
    $cur=$from;
    while($cur<=$parent_level){
        $q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
        $res=$db->Execute($q);
        while(!$res==NULL && !$res->EOF){
            if($cur==$from)
                 $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." order by location.name";
            else
                $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." and parent_id=".$selection;
	    $res_options=$db->Execute($q);
            $options=array();
            if(!$res_options->EOF){
                $selection=$loc_arr[$cur-1][2];
            }
            while(!$res_options->EOF){
                    $sel= $loc_arr[$cur-1][2];
                    $selected=($sel==$res_options->fields[1])?true:false;
                    
                array_push(
                    $options,
                    array(  'drop_desc'=>$res_options->fields[0],
                        'value'=>$res_options->fields[1],
                        'selected'=>$selected
                     )       
                );
                                $res_options->MoveNext();
            }
                                $loc_box=array('desc'=>_($res->fields[1].":"),'type'=>"dropdown",'name'=>$res->fields[0],'options'=>$options,'onChange'=>'update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')','br'=>'1');    
            array_push(
                $loc,
                 $loc_box
             );
            $res->MoveNext();
        }
        $cur=$cur+1;
}
   
    $from=$parent_level;
    $cur=$from[0]+1;
    $selection=$parent;
    while($cur<=$to){
        $q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
        $res=$db->Execute($q);
        while(!$res==NULL && !$res->EOF){
            $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." and parent_id=".$selection;
            $res_options=$db->Execute($q);
            $options=array();
            if(!$res_options->EOF){
                $selection=$res_options->fields[1];
            }
            while(!$res_options->EOF){
                    
                array_push(
                    $options,
                    array(  'drop_desc'=>$res_options->fields[0],
                        'value'=>$res_options->fields[1]
                     )       
                );
                                $res_options->MoveNext();
            }
                                $loc_box=array('desc'=>_($res->fields[1].":"),'type'=>"dropdown",'name'=>$res->fields[0],'options'=>$options,'onChange'=>'update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')','br'=>'1');    
            array_push(
                $loc,
                 $loc_box
             );
            $res->MoveNext();
        }
        $cur=$cur+1;
}
   return $loc;
}

/**
 * _shn_location_form_value 
 * 
 * @param mixed $from 
 * @param mixed $to 
 * @param mixed $value 
 * @access protected
 * @return void
 */
function _shn_location_form_value($range,$value)
{   
    global $global;
    $db=$global['db'];
    $from=$range["start"];
    $to=$range["end"];
    $loc=array();
    if($value!=NULL){
        $loc_arr=shn_get_parents($value);
    }
    $cur=$from;
    while($cur<=$to){
        $q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
        $res=$db->Execute($q);
        while(!$res==NULL && !$res->EOF){
            if($cur==$from)
                 $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." order by location.name";
            else
                $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." and parent_id=".$selection;
            $res_options=$db->Execute($q);
            $options=array();
            if(!$res_options->EOF){
                $selection=$loc_arr[$cur-1][2];
            }
            while(!$res_options->EOF){
            
                 $options[$res_options->fields[1]]=$res_options->fields[0];
                 $res_options->MoveNext();
            }
            $select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
            $extra_opts['value']=$loc_arr[$cur-1][2];
            $extra_opts['req']=true;
            shn_form_select($options,$res->fields[1].":",$res->fields[0],$select_opts,$extra_opts);
                                $loc_box=array('desc'=>_($res->fields[1].":"),'type'=>"dropdown",'name'=>$res->fields[0],'options'=>$options,'onChange'=>'update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')','br'=>'1');    
            $res->MoveNext();
        }
        $cur=$cur+1;
}
  
}


/**
 * _shn_location_form 
 * 
 * @param mixed $from 
 * @param mixed $to 
 * @access protected
 * @return void
 */
function _shn_location_form($range)
{   

    global $global;
    $db=$global['db'];
    $loc=array();
    $from=$range["start"];
    $to=$range["end"]; 
    $cur=$from;
    while($cur<=$to){
        $q = "select option_code,option_description from field_options where field_name='opt_location_type' and option_code=".$cur;
        $res=$db->Execute($q);
        while(!$res==NULL && !$res->EOF){
            if($cur==$from)
                 $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." order by location.name";
            else
                $q = "select location.name,location.location_id from location where location.opt_location_type=".$res->fields[0]." and parent_id=".$selection;
            $res_options=$db->Execute($q);
            $options=array();
            if(!$res_options->EOF){
                $selection=$res_options->fields[1];
            }
            while(!$res_options->EOF){
                
                    $options[$res_options->fields[1]]=$res_options->fields[0];
                    $res_options->MoveNext();
            }
            $select_opts='onChange=update_next_level(this.options[this.selectedIndex].value,'.$res->fields[0].')';
            shn_form_select($options,$res->fields[1].":",$res->fields[0],$select_opts,array('req'=>true));
            $res->MoveNext();
        }
        $cur=$cur+1;
}

   
}

?>

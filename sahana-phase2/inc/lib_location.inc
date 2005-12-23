<?php
/**
* This library helps uses phpgacl library to manage ACL
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

global $global;
include_once $global['approot']."/inc/handler_form.inc";

function shn_location_jscript($from,$to){
    global $global;
    $fetch_server="xml.php?";
?>           
<script type="text/javascript">
    var url = "<?php echo $fetch_server?>"; 
    var curlevel=0;
    var http;
    var from=<?php echo $from ?>;
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
            for (i=1; i<results.length-1; i=i+2){
		 	    opt = document.createElement("option") ;
  			    opt.value = results[i] ;
  			    opt.text =results[i+1] ;
			    x[0].appendChild(opt)
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
        http.onreadystatechange = null; 
        http.onreadystatechange = handleHttpResponse; 
        http.send(null);
    }
</script>
<?php
}

function shn_location_form($from,$to,$value=NULL){
	shn_location_jscript($from,$to);
	if($value!=NULL){
        $location_inf = _shn_location_form_value($from,$to,$value);  
	}else {
        $location_inf = _shn_location_form($from,$to);  
	}
	shn_form_add_component_list($location_inf,$section=true,$legend='',$return=false,$default_val_req=$error);
}
function shn_location($from,$to){
	shn_location_jscript($from,$to);
	$location_inf = _shn_location_form($from,$to);  
	return $location_inf ;
}
function shn_location_form_org($from,$to,$value=NULL){
	shn_location_jscript($from,$to);
	if($value!=NULL){
        $location_inf = _shn_location_form_value($from,$to,$value);  
	}else {
        $location_inf = _shn_location_form($from,$to);  
	}
    shn_form_add_component_list($location_inf,$section=true,$legend='Base Location Information',$return=false,$default_val_req=$error);
}


function _shn_location_form_value($from,$to,$value){   
    global $global;
    $db=$global['db'];
    $loc=array();
    if($value!=NULL){
        $loc_arr=shn_or_get_parents($value);
    }
      /*
    $msg=array('desc'=>_("Type the Zip Code OR select from List Boxes"),'type'=>"label",'name'=>'zip','br'=>'3');  
    array_push(
            $loc,
            $msg            
       
    );

    $zip=array('desc'=>_("Zip Code"),'type'=>"text",'name'=>'zip','br'=>'1');  
    array_push(
            $loc,
            $zip            
       
    );
    */
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
   return $loc;
}


function _shn_location_form($from,$to){   
    global $global;
    $db=$global['db'];
    $loc=array(); 
      /*
    $msg=array('desc'=>_("Type the Zip Code OR select from List Boxes"),'type'=>"label",'name'=>'zip','br'=>'3');  
    array_push(
            $loc,
            $msg            
       
    );

    $zip=array('desc'=>_("Zip Code"),'type'=>"text",'name'=>'zip','br'=>'1');  
    array_push(
            $loc,
            $zip            
       
    );
    */
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
                array_push(
                    $options,
                    array(  'drop_desc'=>$res_options->fields[0],
                        'value'=>$res_options->fields[1],
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

function shn_location_add(){
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
?>

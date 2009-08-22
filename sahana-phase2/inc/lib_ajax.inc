<?php
/**
 *
 * Sahana Ajax library
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    moduleAPI
 * @subpackage form 
 * @author     Ishan Liyanage <ishanul@gmail.com>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_ajax_create_ajax_call() {
	?>
    <script>
    var xmlHttp;
	var ids = new Array();
	var names = new Array();		
	var count=-1;	
	
///////////////////////////////////////
		
	function get_data(str,event,print_element,input_element,set_url,hidden) {
	if(window.event) { //IE
		keynum = event.keyCode;
	}
	else if(event.which) { // Netscape/Firefox/Opera
		keynum = event.which;
	}
		
	//alert(keynum);
			
	if(keynum==27){
		test();
		return;		
		//alert(splited_value[0]);
	}
	else if(keynum==38 || keynum==40){
		get_array(keynum);
	return;	
	}
	else if(keynum==39 || keynum==37){
		set_value(print_element,input_element);
		return;	
	}	
							
	//alert(keynum);
			
	if (str.length==0){
  		document.getElementById(print_element).innerHTML="";
  		return;
  	}
  	
	xmlHttp=GetXmlHttpObject()
	
	if (xmlHttp==null){
  		alert ("Your browser does not support AJAX!");
  		return;
  	}
	var url=set_url;
	
	if(hidden!="NULL"){
		hidden_input=document.getElementById(hidden).value;
	}
	else{
		hidden_input="NULL";
	}	
			//alert(hidden);
										
	url=set_url+"&input="+str+"&print="+print_element+"&input_ele="+input_element+"&parent_id="+hidden_input+"&eve="+keynum;
	//alert(url)
	url=url+"&sid="+Math.random();
			
	xmlHttp.onreadystatechange=stateChanged;
	xmlHttp.open("GET",url,true);
	xmlHttp.send(null);
		
	}
	
////////////////////////////////////////////////////////////////
	
	function stateChanged(){
	
		if (xmlHttp.readyState==4){
			var load = document.getElementById('content');
			//document.getElementById('test').innerHTML='Loaded......';
			//document.getElementById('test').setAttribute('class','loading');
			var olddiv = document.getElementById('test');
			load.removeChild(olddiv);
			ids=new Array();
			names=new Array();		
			count=-1;
							
			//alert(xmlHttp.responseText);
				
			value=xmlHttp.responseText.split(':');	
			splited_value=value[3].split(';');
				
		if(splited_value==""){
			splited_value[1]="";
			splited_value[0]="";		
		}
		
		//def_display="--select--";			
		//def_value='<div id="def" onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch(this.innerHTML,this.id,value[0],value[2]);" class="suggest_link">'+def_display+'</div>'
		
		ids[0]=splited_value[0];
		names[0]=splited_value[1];			
		new_value='<div id='+splited_value[0]+' onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch(this.innerHTML,this.id,value[0],value[2]);" class="suggest_link">'+splited_value[1]+'</div>';
	
			j=1;
			
		for(i=4;i<value.length;i++){
			splited_value=value[i].split(';');
			ids[i-3]=splited_value[j-1];	
			names[i-3]=splited_value[j];				
			old_value='<div id='+splited_value[j-1]+' onmouseover="javascript:suggestOver(this);" onmouseout="javascript:suggestOut(this);" onclick="javascript:setSearch(this.innerHTML,this.id,value[0],value[2]);" class="suggest_link">'+splited_value[j]+'</div>';		
			new_value=new_value+old_value;
			j+2	;
		}
		
		//document.getElementById(value[0]).focus();
						
		document.getElementById(value[0]).innerHTML=new_value;
		}
		
		else {
			<?php
			_shn_set_load_print();
			shn_ajax_add_popup(_t('Fetching data from the server. Please wait......'));
			?>
			
		}
	}
	
//////////////////////////////////////////////////
	
	function get_array(key){
		if(key==40){
				
		//alert(count);	
			
			if(count<ids.length-1){		
				count++;			
				document.getElementById(ids[count]).className = 'suggest_link_over'; 
				document.getElementById(ids[count-1]).className = 'suggest_link';		
			}
		}		
		else if(key==38){
			if(count>0){			
				count--;		
				document.getElementById(ids[count]).className = 'suggest_link_over';		
				document.getElementById(ids[count+1]).className = 'suggest_link';
			}	
		//setSearchfamilyHint(names[count],ids[count]);				
		}				  
	}
	
//////////////////////////////////////////////////	
		 
	function set_value(print,input){
		
		setSearch(names[count],ids[count],print,input);	
		
	}

    </script>
<?php
}

function _shn_ajax_create_suggest($input_element,$print_element){
	?>
    <script>
    
    //Mouse over function
    
	function suggestOver(div_value) {
	div_value.className = 'suggest_link_over';
	}
	
	//Mouse out function
	
	function suggestOut(div_value) {
	div_value.className = 'suggest_link';
	count=-1;
	}

    </script>
   <?php 
}

function _shn_ajax_set_common_styles(){
	?>
	<style type="text/css" media="screen">
    body1 {
    font: 11px arial;
			}
			.suggest_link {
				background-color:#FFF424;
				padding: 2px 6px 2px 6px;
				border-top:1px solid #ccc;
				border-bottom:1px solid #ccc;
				
			}
			.suggest_link_over {
				background-color: #DAD11F;
				padding: 2px 6px 2px 6px;
				cursor:pointer;
				border-top:1px solid #ccc;
				border-bottom:1px solid #ccc;
				
			}
			
    </style>
    <?php
}

function _shn_ajax_create_xml_http_object(){
	?>
	<script>
	function GetXmlHttpObject(){
		var xmlHttp=null;
	try{
		
  		// Firefox, Opera 8.0+, Safari
  		
  		xmlHttp=new XMLHttpRequest();
  	}
	catch (e){
		
  // Internet Explorer
  
  	try{
  	xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
    }
  	catch (e){
    xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
    }
  }
return xmlHttp;
}
  
    </script>
	<?php
}

function _shn_ajax_set_result_to_element($input_element,$print_element,$hidden,$reset){
	?>
	<script>
	function setSearch(value,id,print,input) {
		document.getElementById(print).innerHTML = '';
			
		if(null!=<?php echo $reset;?>){
			if(document.getElementById("text"+input).value!=value){
				<?php foreach($reset as $rs){?>
					document.getElementById('text<?php echo $rs;?>').value= ''
					document.getElementById('<?php echo $rs;?>').value= '';
				<?php }?>
			}
		}
		document.getElementById("text"+input).value = value;
		document.getElementById(input).value = id;
		}
	</script>
	<?php
}

function _shn_ajax_set_div_styles($print_element){
	?>
    <style type="text/css" media="screen">
    
    #<?php echo $print_element;?>{
				z-index: 100; 
				position:absolute; 
				background-color: #CCCCCC;
						
			    display:inline;
				color:#000000;
				text-align: left; 
				font-weight: bold;
				
	}

    </style>
 <?php   
}

function _shn_ajax_hide_popup($print_element){
	?>
	<script>
	window.onclick=test;
	function test(){
		<?php
		foreach($print_element as $ele){
		?>	
		document.getElementById('<?php echo $ele;?>').innerHTML = '';
		<?php
		}
		?>
	}
	</script>
	<?php
}
function _shn_set_load_print(){
	?>
	function _shn_load_pop_up(message){
    var load = document.getElementById('test');
		if(load==null){
    		var newdiv = document.createElement('div');
    		newdiv.innerHTML = message;
    		var loadId = 'test';
    		newdiv.setAttribute('id',loadId);
    		newdiv.setAttribute('class','loading');
    		newdiv.setAttribute('className','loading');
    		var ni = document.getElementById('content');
    		ni.insertBefore(newdiv,ni.childNodes[0]);
		}
		else{
			document.getElementById('test').innerHTML=message;
			document.getElementById('test').setAttribute('class','loading');
			document.getElementById('test').setAttribute('className','loading');
		}
    }
	<?php
}
function shn_ajax_add_popup($message){
?>
    _shn_load_pop_up('<?php echo $message;?>');
    
<?php	
}
function shn_ajax_add_suggest($input_element,$print_element,$hidden,$reset=null){
	
    _shn_ajax_create_suggest($input_element,$print_element); 
    
    _shn_ajax_set_result_to_element($input_element,$print_element,$hidden,$reset); 
    _shn_ajax_set_div_styles($print_element);
}
function shn_ajax_initiate_request(){
	_shn_ajax_create_xml_http_object();
	_shn_ajax_create_ajax_call(); 
	_shn_ajax_set_common_styles();
}
function shn_ajax_text_look_up($label,$name,$hint=null,$url,$value=null,$flag,$extra_opts=null){
    global $global;
    if(NULL==$hint){
        $hint=array('hint');
    }
    if($global["initiate_ajax"]==false){
	    shn_ajax_initiate_request();
	    $global["initiate_ajax"]=true;
    }

	_shn_ajax_hide_popup($hint);
    for($index=0;$index<count($name);$index++){
	    if(true==$flag){
            if(0==$index){
		        $reset=array_slice($name,1);	
		        shn_ajax_add_suggest($name[0],$hint[0],$name[0],$reset);
		        $extra_opts['value']=$value[0];
		        shn_form_text($label[0],'text'.$name[0],"size=\"30\" autocomplete=off  onclick=\"get_data('*',event,'".$hint[0]."','".$name[0]."','".$url."','NULL')\" onkeyup=\"get_data(this.value,event,'".$hint[0]."','".$name[0]."','".$url."','NULL')\"" ,$extra_opts);
                $extra_opts['help']=null;
		        echo "<div id='".$hint[0]."' style='left: 442px'></div>";
		        ?>
                <input type="hidden" id="<?php echo $name[0]?>" name="<?php echo $name[0]?>"  value= />
	
	            <?php
		        }
		        else
		        {
	//$url=$url.'&parent_id=2';//=document.getElementById(\'hidden_'.$name[$index-1].'\').value';
                    $reset=array_slice($name,$index+1);
                    shn_ajax_add_suggest($name[$index],$hint[$index],$name[$index],$reset);
                    $extra_opts['value']=$value[$index];
                    shn_form_text($label[$index],'text'.$name[$index],"size=\"30\" autocomplete=off onclick=\"get_data('*',event,'".$hint[$index]."','".$name[$index]."','".$url."','".$name[$index-1]."')\" onkeyup=\"get_data(this.value,event,'".$hint[$index]."','".$name[$index]."','".$url."','".$name[$index-1]."')\"" ,$extra_opts);
     				//echo $name[$index-1];
                    echo "<div id='".$hint[$index]."' style='left: 442px'></div>";
                    ?>
                    <input type="hidden" id="<?php echo $name[$index]?>" name="<?php echo $name[$index]?>"  value= />
	
	                <?php
		        }
        }
		else{
			$reset=array_slice($name,$index+1);
            shn_ajax_add_suggest($name[$index],$hint[$index],$name[$index],$reset);
            $extra_opts['value']=$value[$index];
            shn_form_text($label[$index],'text'.$name[$index],"size=\"30\" autocomplete=off onclick=\"get_data('*',event,'".$hint[$index]."','".$name[$index]."','".$url."','".($name[$index-1])."')\" onkeyup=\"get_data(this.value,event,'".$hint[$index]."','".$name[$index]."','".$url."','".$name[$index-1]."')\"" ,$extra_opts);

            echo "<div id='".$hint[$index]."' style='left: 442px'></div>";
            ?>
            <input type="hidden" id="<?php echo $name[$index]?>" name="<?php echo $name[$index]?>"  value= />
	
	<?php
		}
	}

}



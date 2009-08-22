<?php
/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */
?>

<script type="text/javascript">
	function form_clear(form_name)
	{
		var oforms = document.forms[form_name];
		//alert(oforms['first_name'].value);
		oforms['first_name'].value = "";
		oforms['last_name'].value = "";
		oforms['middle_name'].value = "";
		oforms['nick_name'].value = "";
		oforms['opt_title'].value = "";
		oforms['opt_gender'].value = "";
		oforms['birth_date'].value = "";
		oforms['opt_age_group'].value = "";
		oforms['opt_religion'].value = "";
		oforms['opt_race'].value = "";
		oforms['opt_marital_status'].value = "";
		oforms['occupation'].value = "";
		oforms['description'].value = "";

		if(form_name == 'group_form'){			
			oforms['opt_group_type'].value = "";
			oforms['opt_relationship_type'].value = "";
		}
	}

	function pr_remove_number(child_id,parent_id)
    {			
		var p = document.getElementById(parent_id);
		var c = document.getElementById(child_id);
		p.removeChild(c);
				    
    }

	function pr_add_number(number_list,field){
		var field_msg = field.name+'_msg';			
		var list_value = field.value;
		if(list_value == ""){
			document.getElementById(field_msg).style.display = "block";
			document.getElementById(field_msg).innerHTML = "<span style='color:red'>Error! Please enter " + field.name + " number.</span>";
		}
		else{
			var parent_element = number_list;
			var child_element = document.createElement('li');
			
			child_element.setAttribute('id',list_value);
			
			child_element.innerHTML = list_value + '<input type="hidden" name="'+ field.name + '_array[]' +'" value="'+ list_value +'">' 
											     + ' <a href="#" onclick="pr_remove_number(\''+ list_value +'\',\''+field.name+'_list\');">'+'Remove'+'</a>';
			document.getElementById(field.name + '_list').style.display = "block";
			parent_element.insertBefore(child_element, parent_element.firstChild);
			document.getElementById(field_msg).style.display="none";								
			field.value = "";				
		}
	}

	function pr_add_identity(identity_value,identity_type){		
		var field_name = identity_type.value;
		var field_value = identity_value.value;

		var selected = identity_type.selectedIndex;
		var selected_text = identity_type.options[selected].text;
		
		var d = document.getElementById(field_name);
		
		if(d == null){			
			if(identity_value.value != ""){
				document.getElementById('number_exist_msg').style.display = "none";
						
				var parent_div = document.getElementById('identity_list');
				
				var child_div = document.createElement('div');
				child_div.setAttribute("id",field_name);
		
				child_div.innerHTML = "<label>" + selected_text + "</label>" +
									"<input type=\"text\" name=\"" + field_name + "\" value=\"" + field_value + "\"\>&nbsp;"+
									"<input type=\"button\" value=\"Remove\" onclick=\"pro_remove_identity('"+ field_name +"')\"/>";
				
				parent_div.appendChild(child_div);
				identity_value.value = "";
			}
			else{
				document.getElementById('number_exist_msg').style.display = "block";
				document.getElementById('number_exist_msg').innerHTML = "<span style='color:red'>" + selected_text + " cannot be empty!</span>";
			}
		}
		else{			
			document.getElementById('number_exist_msg').style.display = "block";
			document.getElementById('number_exist_msg').innerHTML = "<span style='color:red'>" + selected_text + " is already exists.</span>";
		}
	}
				
	function pro_remove_identity(child_div) {	
		if (confirm("Do you really want to remove this field?")){
			document.getElementById('number_exist_msg').style.display = "none";
			var d = document.getElementById('identity_list');		
			var olddiv = document.getElementById(child_div);		
			d.removeChild(olddiv);		
		}
	}

	function pr_remove_field(field_id) {		
		var tbody = document.getElementById('address_list');
		var tr = document.getElementById(field_id);		
		tbody.removeChild(tr);
		document.getElementById('address_list_msg').innerHTML='';

		var rows = document.getElementById('address_list').childNodes;
		if(rows.length == 0){
			document.getElementById('address_table').style.display="none";
		}
	}

	function remove_all_list(form_name)
	{		
		var oforms = document.forms[form_name];
		oforms['address'].value = ""
		oforms['postal_code'].value = "";
		
		remove_child_from_parent('telephone_list');
		remove_child_from_parent('mobile_list');
		remove_child_from_parent('email_list');
		remove_child_from_parent('web_url_list');
	}

	function remove_child_from_parent(parent)
	{
		var node = document.getElementById(parent);

		var len = node.childNodes.length;
		
		for(var i=len-1; i > -1; i--){
			node.removeChild(node.childNodes[i]);
		}
	}

	var formblock;
	var forminputs;
		
	function prepare(formid) {
		formblock= document.getElementById(formid);
		if(formblock != null){
			forminputs = formblock.getElementsByTagName('input');
		}
	}
		
	function select_all(name, value,formid) {		
		prepare(formid);
		for (i = 0; i < forminputs.length; i++) {
			// regex here to check name attribute
			var regex = new RegExp(name, "i");
			if (regex.test(forminputs[i].getAttribute('name'))) {
				if (value) {
					forminputs[i].checked = true;
				} else {
					forminputs[i].checked = false;
				}
			}
		}
	}


	// ***** Person popup window functions *********************************************************
	
	var popup_dragging = false;
	var popup_target;
	var popup_mouseX;
	var popup_mouseY;
	var popup_mouseposX;
	var popup_mouseposY;
	var popup_oldfunction;
	
	
	// ***** popup_mousedown *******************************************************
	
	function popup_mousedown(e)
	{
	  var ie = navigator.appName == "Microsoft Internet Explorer";
	
	  popup_mouseposX = ie ? window.event.clientX : e.clientX;
	  popup_mouseposY = ie ? window.event.clientY : e.clientY;
	}
	
	
	// ***** popup_mousedown_window ************************************************
	
	function popup_mousedown_window(e)
	{
	  var ie = navigator.appName == "Microsoft Internet Explorer";
	
	  if ( ie && window.event.button != 1) return;
	  if (!ie && e.button            != 0) return;
	
	  popup_dragging = true;
	  popup_target   = this['target'];
	  popup_mouseX   = ie ? window.event.clientX : e.clientX;
	  popup_mouseY   = ie ? window.event.clientY : e.clientY;
	
	  if (ie)
	       popup_oldfunction = document.onselectstart;
	  else popup_oldfunction = document.onmousedown;
	
	  if (ie)
	       document.onselectstart = new Function("return false;");
	  else document.onmousedown   = new Function("return false;");
	}
	
	
	// ***** popup_mousemove *******************************************************
	
	function popup_mousemove(e)
	{
	  var ie      = navigator.appName == "Microsoft Internet Explorer";
	  var element = document.getElementById(popup_target);
	  var mouseX  = ie ? window.event.clientX : e.clientX;
	  var mouseY  = ie ? window.event.clientY : e.clientY;
	
	  if (!popup_dragging) return;
	
	  element.style.left = (element.offsetLeft+mouseX-popup_mouseX)+'px';
	  element.style.top  = (element.offsetTop +mouseY-popup_mouseY)+'px';
	
	  popup_mouseX = ie ? window.event.clientX : e.clientX;
	  popup_mouseY = ie ? window.event.clientY : e.clientY;
	}
	
	// ***** popup_mouseup *********************************************************
	
	function popup_mouseup(e)
	{
	  var ie      = navigator.appName == "Microsoft Internet Explorer";
	  var element = document.getElementById(popup_target);
	
	  if (!popup_dragging) return;
	
	  popup_dragging = false;
	
	  if (ie)
	       document.onselectstart = popup_oldfunction;
	  else document.onmousedown   = popup_oldfunction;
	}
	
	// ***** popup_exit ************************************************************
	
	function popup_exit(e)
	{
	  var ie      = navigator.appName == "Microsoft Internet Explorer";
	  var element = document.getElementById(popup_target);
	
	  popup_mouseup(e);
	  element.style.display = 'none';
	}
	
	
	// ***** popup_show ************************************************************
	
	function popup_show(id, drag_id, exit_id, position, x, y, position_id)
	{
	  var element      = document.getElementById(id);
	  var drag_element = document.getElementById(drag_id);
	  var exit_element = document.getElementById(exit_id);
	
	  var width        = window.innerWidth  ? window.innerWidth  : document.documentElement.clientWidth;
	  var height       = window.innerHeight ? window.innerHeight : document.documentElement.clientHeight;
	
	  element.style.position = "absolute";
	  element.style.display  = "block";
	
	  if (position == "element" || position == "element-right" || position == "element-bottom")
	  {
	    var position_element = document.getElementById(position_id);
	
	    for (var p = position_element; p; p = p.offsetParent)
	      if (p.style.position != 'absolute')
	      {
	        x += p.offsetLeft;
	        y += p.offsetTop;
	      }
	
	    if (position == "element-right" ) x += position_element.clientWidth;
	    if (position == "element-bottom") y += position_element.clientHeight;
	
	    element.style.left = x+'px';
	    element.style.top  = y+'px';
	  }
	
	  if (position == "mouse")
	  {
	    element.style.left = (document.documentElement.scrollLeft+popup_mouseposX+x)+'px';
	    element.style.top  = (document.documentElement.scrollTop +popup_mouseposY+y)+'px';
	  }
	
	  if (position == "screen-top-left")
	  {
	    element.style.left = (document.documentElement.scrollLeft+x)+'px';
	    element.style.top  = (document.documentElement.scrollTop +y)+'px';
	  }
	
	  if (position == "screen-center")
	  {
	    element.style.left = (document.documentElement.scrollLeft+(width -element.clientWidth )/2+x)+'px';
	    element.style.top  = (document.documentElement.scrollTop +(height-element.clientHeight)/2+y)+'px';
	  }
	
	  if (position == "screen-bottom-right")
	  {
	    element.style.left = (document.documentElement.scrollLeft+(width -element.clientWidth )  +x)+'px';
	    element.style.top  = (document.documentElement.scrollTop +(height-element.clientHeight)  +y)+'px';
	  }
	
	  drag_element['target']   = id;
	  drag_element.onmousedown = popup_mousedown_window;
	
	  exit_element.onclick     = popup_exit;
	}
	
	
	// ***** Attach Events *********************************************************
	
	if (navigator.appName == "Microsoft Internet Explorer")
	     document.attachEvent   ('onmousedown', popup_mousedown);
	else document.addEventListener('mousedown', popup_mousedown, false);
	
	if (navigator.appName == "Microsoft Internet Explorer")
	     document.attachEvent   ('onmousemove', popup_mousemove);
	else document.addEventListener('mousemove', popup_mousemove, false);
	
	if (navigator.appName == "Microsoft Internet Explorer")
	     document.attachEvent   ('onmouseup', popup_mouseup);
	else document.addEventListener('mouseup', popup_mouseup, false);
	
	
	function popup_clear(oform)
	{			
		oform['full_name'].value = "";
		oform['person_id'].value = "";
		oform['first_name'].value = "";
		oform['last_name'].value = "";
		oform['occupation'].value = "";
		oform['address'].value = "";
	}
</script>
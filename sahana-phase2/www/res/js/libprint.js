/**
* Sahana Optical Character Recognition Form library, Genarates the required form layout
*
* Javascript version 1.2 and CSS1
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Hayesha Somarathne - hayesha@opensource.lk, hayeshais@gmail.com
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package	  framework
* @subpackage printing
* @tutorial	  
* @license	  http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
*/


/**
 * This section contains the necessary CSS styles for the page
 *
 */
document.writeln(
        '<style type="text/css">'                                       +

//A4 page height: 843.829pt; width:596.971pt; 

		'#print { float: left; width: 510pt; padding: 0; margin: 0 auto; }'	+

		'#print-wrapper { float: left; width: 510pt; border: #000 1pt solid; padding: 2pt; margin: 4pt auto; }'	+
		'#print-wrapper h2, #print-wrapper h3 { font-family: Arial, Helvetica, sans-serif; }'	+
		'#print-wrapper h2 { text-align: center; font-family: Georgia, Times, serif; }'	+

		'.top-layout { float: left; width: 510pt; margin: 10pt 0 5pt 0; }'	+
		'.top-layout .top-left { float: left; border: #000 5pt solid; margin: 4pt 0 0 15pt; padding: 0; }'	+
		'.top-layout .top-middle { float: left; border: #000 5pt solid; margin: 4pt 0 0 235pt; padding: 0; }'	+
		'.top-layout .top-right { float: right; border: #000 5pt solid; margin: 4pt 15pt 0 0; padding: 0; }'	+

		'.bottom-layout { float: left; width: 510pt; margin: 5pt 0 10pt 0; }'	+
		'.bottom-layout .bottom-left { float: left; border: #000 5pt solid; margin: 0 0 4pt 15pt; padding: 0; }'	+
		'.bottom-layout .bottom-right { float: right; border: #000 5pt solid; margin: 0 15pt 4pt 0; padding: 0; }'	+

		'ul#instructions { float: left; width: 450pt; list-style-type: circle; margin: 5pt 0 0 24pt; }'	+
		'ul#instructions li { margin: 0; padding: 2pt 0; font-size: 8pt; }'	+

		'.heading { float: left; width: 480pt; margin: 0; padding: 5pt; text-align: center; font-size: 14pt; font-weight: bold; }'	+

		'.fieldset-heading { float: left; clear: both; font-weight: bold; margin: 11pt 2pt 0 15pt; padding: 0; display: block; }'	+
		'.description { float: left; clear: both; margin: 1pt 0 0 15pt; padding: 0 2pt; font-size: 8pt; width: 465pt; }'	+

		'.item-wrap, .label-left, .label-right, .character { float: left; border: #000 1px solid; }'	+
		'.item-wrap { clear: both; margin: 5pt 0 5pt 15pt; width: 465pt; }'	+
		'.item-wrap .label-left { height: 10pt; font-size: 8pt; text-transform: uppercase; width: 330pt; padding: 2pt 5pt; }'	+
		'.item-wrap .label-right { height: 10pt; width: 112pt; padding: 2pt 5pt; }'	+
		'.character { height: 10pt; width: 10pt; padding: 2pt; }'	+

		'.item-wrap-small, .small-left, .small-right, .dob-dd, .dob-mm, .dob-yy, .option-label { float: left; border: #000 1px solid; }'	+
		'.small-left, .small-right, .dob-dd, .dob-mm, .dob-yy, .option-label { font-size: 8pt; text-transform: uppercase; padding: 1pt 5pt; height: 10pt; }'	+
		'.item-wrap-small { width: 223pt; margin: 5pt 0 5pt 15pt; }'	+
		'.item-wrap-small .small-left { width: 144pt; color: #000; }'	+
		'.item-wrap-small .small-right { width: 56pt; }'	+
		'.dob-dd, .dob-mm, .dob-yy { width: 16pt; color: #ddd; font-size: 5pt; }'	+
		'.option-label { width: 205pt; height: 10pt; }'	+

		'.space { float: left; clear: both; }'	+
	'</style>' );


/**
 * This section contains the IE specific CSS styles for the page
 *
 */
document.writeln(
	//This section handles the specific CSS styles that are required 
	//by IE versions including six and below
	'<!--[if lte IE 6]>'	+
		'<style type="text/css">'	+
			'#print, #print-wrapper { width: 490pt; }'	+
			'#print-wrapper { padding-left: 25pt; }'	+
			'.top-layout .top-left { margin-left: 0; }'	+
			'.top-layout .top-middle { margin-left: 117pt; }'	+
			'.bottom-layout .bottom-left { margin-left: 0; }'	+
			'.fieldset-heading { font-weight: bold; margin: 0; }'	+
			'.item-wrap { border: #000 1px solid; margin-left: 0; width: 474pt; }'	+
			'.item-wrap .label-left { width: 330pt; }'	+
			'.item-wrap .label-right { width: 125pt; }'	+
			'.character { height: 10pt; width: 15pt; padding: 2pt; }'	+
		'</style>'	+
	'<![endif]-->'	+

	//This section handles the specific CSS styles that are required 
	//by IE versions seven
	'<!--[if IE 7]>'	+
		'<style type="text/css">'	+
			''	+
		'</style>'	+
	'<![endif]-->');


/**
 * This function initialize the functionality
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_init() {
	shn_print_hide_basic_layout();
	shn_print_create_basic_elements_layout();
} 



/**
 * This function hides the unwanted elements from the page
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_hide_basic_layout() {

	var header = document.getElementById('header').style.display = 'none';
	var menu = document.getElementById('wrapper_menu').style.display = 'none';
	var wrapper = document.getElementById('wrapper').style.background = 'url(none)';
	var content = document.getElementById('content').style.display = 'none';
	var footer = document.getElementById('footer').style.display = 'none';
	var body_bgcolor = document.getElementsByTagName('body')[0].style.background = '#fff';
}



/**
 * This function layouts the basic format of the page
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_create_basic_elements_layout() {

	var dom_print, dom_content_wrapper;
	var dom_form_wrapper = [];

		dom_print = document.createElement('div');
		dom_print.setAttribute('id','print');	
		document.getElementsByTagName('body')[0].appendChild(dom_print);

		dom_content_wrapper = document.getElementById('content');
		dom_form_wrapper = getElementsByClass('div', 'form-container');

		//check whether the content in the page is relavent to genarate the form
		if ((dom_form_wrapper == '' && dom_content_wrapper != '') || (dom_form_wrapper == null  && dom_content_wrapper != '') ) {
			
			//on failure alerts the user and redirected to the current page
			alert("This functionality does not available for the content on this page.");
			location.reload();
		}
		//on succes necessary operations are being carried out
		else {  
			//creates a wrapper to hold the generate content
			var dom_wrapper = document.createElement('div');
			dom_wrapper.setAttribute('id','print-wrapper');
			document.getElementById('print').appendChild(dom_wrapper);

			//append the top layout to the page
			shn_print_layout_top('print-wrapper');
		
			//appends the user instructions to the page
			shn_print_user_instructions();
		
			//extracts and appends the heading of the page
			shn_print_set_page_header(shn_print_read_page_heading());
				
			//handles the rest of the processing in the page
			shn_print_get_fieldset_content();	

			//append the bottom layout to the page
			shn_print_layout_bottom('print-wrapper');
		}
}


/**
 * This function creates the basic top layout for the page
 *			 ________________________________
 *			|  _		 _            _	 |
 * @param string1	| |_|		|_|          |_| |
 * @access protected	|				 |
 * @return void
 */
function shn_print_layout_top(parent_id) {

	var dom_div;	
		dom_div = document.createElement('div');
		dom_div.setAttribute('class','top-layout');
		dom_div.setAttribute('className', 'top-layout');
		dom_div.innerHTML += '<div class="top-left"> </div>';
		dom_div.innerHTML += '<div class="top-middle"> </div>';
		dom_div.innerHTML += '<div class="top-right"> </div>';
		document.getElementById(parent_id).appendChild(dom_div);
}


/**
 * This function creates the basic bottom layout for the page
 *			|  _		     	     _	|
 * @param string1	| |_|		    	    |_|	|
 * @access protected	|_______________________________|
 * @return void
 */
function shn_print_layout_bottom(parent_id) {

	var _dom_div;
		_dom_div = document.createElement('div');
		_dom_div.setAttribute('class','bottom-layout');
		_dom_div.setAttribute('className', 'bottom-layout');
		_dom_div.innerHTML += '<div class="bottom-left"> </div>';
		_dom_div.innerHTML += '<div class="bottom-right"> </div>';
		document.getElementById(parent_id).appendChild(_dom_div);

}




/**
 * This function adds the user instruction into the page
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_user_instructions() {

	var dom_ul, dom_li;
		user_instructions = [];

		user_instructions[0] = "Fill the necessary fields with CAPITAL LETTERS.";
		user_instructions[1] = "Always use one box per letter and leave one box space to seperate words.";
		user_instructions[2] = "Using a pencil is the best over pens.";

		dom_ul = document.createElement('ul');
		dom_ul.setAttribute('id','instructions');
		document.getElementById('print-wrapper').appendChild(dom_ul);
		for ( var i = 0; i <user_instructions.length; i++ ) {
			dom_li = document.createElement('li');
			document.getElementById('instructions').appendChild(dom_li);
			//alert(user_instructions[i]);
			document.getElementById('instructions').getElementsByTagName("li")[i].innerHTML = user_instructions[i];
		}
}




/**
 * This function returns the height of the element having the given id
 *
 * @param string
 * @access protected
 * @return string
 */
function shn_print_get_height(id) {
	
	var pageHeight = document.getElementById(id).offsetHeight;
  return pageHeight;
}



/**
 * This function gets the content within the fieldset element and populate
 * the extracted values under necessary groupings
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_get_fieldset_content() {
	
	// declares the necessary variables and arrays 
	var dom_fieldset = [], dom_legend = [], dom_div_info = [], dom_label = [], val1 = [], val3 = [], val2_div = [], val2_span = [], _val2_p = [];

		// extracts the content within the fieldset element  
		var val = document.getElementsByTagName('fieldset');

		// traverse throught each fieldset element
		for (i = 0; i <val.length; i++) {

			dom_fieldset = val[i].innerHTML;
			//alert(val[i].innerHTML);

			//extract the values from legend element and store it in a variable
  			val1 = document.getElementsByTagName('fieldset')[i].getElementsByTagName('legend');

			//extract the values from span element and store it in a variable
			val2_span = document.getElementsByTagName('fieldset')[i].getElementsByTagName('span'); 
			//alert('_val2_span : '+_val2_span);
			
			//extract the values from div element and store it in a variable
			val2_div = document.getElementsByTagName('fieldset')[i].getElementsByTagName('div');
			//alert('_val2_div : '+val2_div);
			
			//extract the values from p element and store it in a variable
			_val2_p = document.getElementsByTagName('fieldset')[i].getElementsByTagName('p');
			//alert('_val2_p : '+_val2_p);			
			
			//traverse along the length of the val1 array

   			for (a = 0; a < val1.length; a++) {
				var _tmp_l = [], _tmp_t = [], _tmp_t_t, _tmp_l_ = [], _tmp_o = [];
				var count_o_l = 0;
				//prints the value extracted from legend element
  				var dom_legend = shn_print_display_legend(val1[a].innerHTML);
				
				//prints the user information under each category
				display_user_info(val2_div, val2_span, _val2_p);
				
				//extract the values from lable elements and store them into a variable
				val3 = document.getElementsByTagName('fieldset')[i].getElementsByTagName('label');
				var _val_input = document.getElementsByTagName('fieldset')[i].getElementsByTagName('input');
				var _val_select = document.getElementsByTagName('fieldset')[i].getElementsByTagName('select');
				//var _val_option = document.getElementsByTagName('fieldset')[i].getElementsByTagName('option');
				var _val_textarea = document.getElementsByTagName('fieldset')[i].getElementsByTagName('textarea');
				
				for (count_l = 0; count_l < val3.length; count_l++) {
					_tmp_l[_tmp_l.length] = val3[count_l].innerHTML;
				}
				
				for(count_i = 0; count_i < _val_input.length; count_i++){
					var el_input = _val_input[count_i];
					if(el_input.getAttribute("type") == 'text'){
						_tmp_t[_tmp_t.length] = el_input.getAttribute("type"); 
					}
					if(el_input.getAttribute("type") == 'file'){
						_tmp_t[_tmp_t.length] = el_input.getAttribute("type");
					}
					if(el_input.getAttribute("type") == 'radio'){
						_tmp_t[_tmp_t.length] = el_input.getAttribute("type"); 
					}
					if(el_input.getAttribute("type") == 'password'){
						_tmp_t[_tmp_t.length] = el_input.getAttribute("type"); 
					}
					if(el_input.getAttribute("type") == 'checkbox'){
						_tmp_t[_tmp_t.length] = el_input.getAttribute("type"); 
					}
				}

				for(count_s = 0; count_s < _val_select.length; count_s++){
					_tmp_t[_tmp_t.length] = 'select';
				}

				for(count_t = 0; count_t < _val_textarea.length; count_t++){
					_tmp_t[_tmp_t.length] = 'textarea';
				}

				//traverse along the length of the val3 array
				for (b = 0; b < val3.length; b++) {
					//assigns the values in _tmp_l array to dom_label variable
   					var dom_label = val3[b].innerHTML;

					//creates the outer wrapper 
					var _dom_item_wrap = document.createElement('div');
					var _dom_item_wrap_small = document.createElement('div');

 					if ((_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Date of Birth') || (_tmp_l[b] == 'Manufactured Date : ') || (_tmp_l[b] == 'Expire Date :') || (_tmp_l[b] == 'Date of Event') )) {
 						shn_print_add_dob_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small');
 					}
 					else if ((_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Skin Colour') || (_tmp_l[b] == 'Eye Colour') || (_tmp_l[b] == 'Home Phone') || (_tmp_l[b] == 'Adult Males') || (_tmp_l[b] == 'Adult Females') || (_tmp_l[b] == 'Children') || (_tmp_l[b] == 'Displaced') || (_tmp_l[b] == 'Missing') || (_tmp_l[b] == 'Dead') || (_tmp_l[b] == 'Rehabilitated') || (_tmp_l[b] == 'Mobile') || (_tmp_l[b] == 'Phone : ') || (_tmp_l[b] == 'Mobile No : ') || (_tmp_l[b] == 'Telephone') || (_tmp_l[b] == 'Country:') || (_tmp_l[b] == 'Men') || (_tmp_l[b] == 'Women') || (_tmp_l[b] == 'Infected Count') || (_tmp_l[b] == 'Total Count') || (_tmp_l[b] == 'Capacity') )) {
 						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small' );
 					}
					else if ( (_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Full Name') || (_tmp_l[b] == 'Address') || (_tmp_l[b] == 'Address : ') || (_tmp_l[b] == 'Other relevant resources : ') || (_tmp_l[b] == 'Equipment : ') || (_tmp_l[b] == 'Organization Name : '))) {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap');
					}
					else if (_tmp_t[b] == 'text') {
						shn_print_add_input_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap');
					}
					if (_tmp_t[b] == 'file') {
						shn_print_add_input_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap');
					}
					if (_tmp_t[b] == 'radio') {
						shn_print_add_input_r_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small' );b
					}
					if (_tmp_t[b] == 'checkbox') {
						shn_print_add_input_c_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small' );
					}

					if ( (_tmp_t[b] == 'select') && ( (_tmp_l[b] == 'Address') || (_tmp_l[b] == 'Holding Company') )) {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap');
					}
					else if (_tmp_t[b] == 'select') { 
						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small' );
					}
					if ( (_tmp_t[b] == 'textarea') && (_tmp_l[b] == 'Mobile') ) {
						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small' );
					}
					else if (_tmp_t[b] == 'textarea') {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap');
					}
					shn_print_add_ocr_layout();
				}
   			}
 			shn_print_add_line_brake('print-wrapper');
		}
}



/**
 * This function appends the extracted description under each fieldset category 
 *
 * @param string, string, string
 * @access protected
 * @return void
 */
function shn_print_display_description(dom_div, dom_span, dom_p) {

	var _dom_span = document.createElement('span');
	
	// checks whether the dom_span variable is not empty and appends that value
	if ((dom_span != '' || dom_span != null) ) {
		//remove if any of the text is available
		if (dom_span == '[Help]' || dom_span == '*' ) {
			_dom_span.innerHTML += '';
		} 
		else {
			_dom_span.innerHTML += dom_span;
		}
	}
	// checks whether the dom_div variable is not empty and appends that value
	if ((dom_div != '' || dom_div != null) ) {
		_dom_span.innerHTML += dom_div;
	}
	// checks whether the dom_p variable is not empty and appends that value
	if ( (dom_p != '' || dom_p != null)) {
		for (var dp = 0; dp < dom_p.length; dp++) {
			_dom_span.innerHTML += dom_p[dp];
		}
	}
	_dom_span.setAttribute('class','description');
	_dom_span.setAttribute('className','description');
	document.getElementById('print-wrapper').appendChild(_dom_span);

  return _dom_span;
}


/**
 * This function creates a new legend element and appends the extracted value
 * form the page 
 *
 * @param array
 * @access protected
 * @return void
 */
function shn_print_display_legend(dom_legend) {
	
	shn_print_add_line_brake('print-wrapper');
	shn_print_add_line_brake('print-wrapper');
	shn_print_add_line_brake('print-wrapper');
  	var _dom_legend = document.createElement('legend');
	_dom_legend.setAttribute('class','fieldset-heading');
  	_dom_legend.appendChild(document.createTextNode(dom_legend));
  	document.getElementById('print-wrapper').appendChild(_dom_legend);

 return dom_legend;	
}


/**
 * This function includes the necessary basic page layout to necessary
 * point in the page 
 *
 * @param none
 * @access protected
 * @return string
 */
 function shn_print_adds_page_layout() {
	//append the bottom layout to the page at the end
	shn_print_layout_bottom('print-wrapper');
 
	shn_print_add_space('print-wrapper');
	//shn_print_add_space('print-wrapper');

	//append the top layout to the page at the end
	shn_print_layout_top('print-wrapper');

	//alert ("page height : " + shn_print_get_height('print-wrapper'));
}

/**
 * This function gets the content included at heading section of the page and returns 
 * the content as an array
 *
 * @param none
 * @access protected
 * @return string
 */
function shn_print_read_page_heading() {

	var page_heading;
	var h1 = [], h2 = [];
		h1 = document.getElementById('content').getElementsByTagName('h1');
		h2 = document.getElementById('content').getElementsByTagName('h2');

	if (h1.length == 1) {
		page_heading = h1[0].innerHTML;
	}
	
	else if (h2.length == 1) {
		page_heading = h2[0].innerHTML;
	}
  return page_heading;
}

/**
 * This function sets the heading for the page
 *
 * @param $string
 * @access protected
 * @return void
 */
function shn_print_set_page_header(heading) {

	dom_h1 = document.createElement('h1');
	dom_h1.setAttribute('class','heading');
	dom_h1.setAttribute('className','heading');
	document.getElementById('print-wrapper').appendChild(dom_h1);
	dom_h1.innerHTML = heading;
}



/**
 * This function returns an array of elements that matches the given class
 *
 * @param none
 * @access protected
 * @return void
 */
function getElementsByClass(elem, classname) {
    classes = [];
    alltags = document.getElementsByTagName(elem);
    for (var traversing=0; traversing<alltags.length; traversing++)
        if (alltags[traversing].className == classname)
            classes[classes.length] = alltags[traversing];
    return classes;
}


//var getvalue=document.getElementById("myimage").getAttribute("src")

/**
 * This function adds a line brake
 *
 * @param string, string, string
 * @access protected
 * @return void
 */
function display_user_info(dom_div, dom_span, dom_p) {

	var element_p = document.createElement('p');
	if ( dom_div != null || dom_div != '' ) {
		for ( var div_l = 0; div_l < dom_div.length; div_l++ ) {
			//element_p.innerHTML += dom_div[div_l];	
		}
	}
	else if ( dom_span != null || dom_span != '') {
		for ( var span_l = 0; span_l < dom_span.length; span_l++ ) {
			//element_p.innerHTML += dom_span[span_l];	
		}
	}
	else if ( dom_p != null || dom_p != '') {
		for ( var p_l = 0; p_l < dom_p.length; p_l++ ) {
			element_p.innerHTML += dom_p[p_l];	
		}	
	}
	
	element_p.setAttribute('class','description');
	element_p.setAttribute('className','description');
	document.getElementById('print-wrapper').appendChild(element_p);
}



/**
 * This function adds a line brake
 *
 * @param string
 * @access protected
 * @return void
 */
function shn_print_add_line_brake(id) {

	dom_br = document.createElement('br');
	document.getElementById(id).appendChild(dom_br);
}

/**
 * This function adds space to the page
 *
 * @param string
 * @access protected
 * @return void
 */
function shn_print_add_space(id) {

	_dom_space = document.createElement('span');
	_dom_space.setAttribute('class', 'space');
	_dom_space.innerHTML = '<br /><br />';
	document.getElementById(id).appendChild(_dom_space);
}


/**
 * This function 
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_add_ocr_layout() {

	var page_height = shn_print_get_height('print-wrapper');
		if ( ((1050 > page_height) && (page_height > 900))  ) {
 			shn_print_adds_page_layout();
		}
		if ( ((2000 > page_height) && (page_height > 1850))  ) {
 			shn_print_adds_page_layout();
		}
	shn_print_add_line_brake('print-wrapper');
}



/**
 * This function appends the required layout to the page
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_appent_to_wrapper(_tdom_wrap, _class) {
	//_tdom_wrap.setAttribute('class',_class);
	_tdom_wrap.setAttribute('className',_class);
	document.getElementById('print-wrapper').appendChild(_tdom_wrap);
}



/**
 * This function appends the vlaue to the label, if extracted
 * label is empty then assings the legend's value 
 *
 * @param none
 * @access protected
 * @return void
 */
function shn_print_set_label(dom_label, dom_legend, _dom_wrapper, class_name) {
	if (dom_label == '' || dom_label == null) {
		// append the value of dom_legend to the wrapper if dom_label variable is empty
		_dom_wrapper.innerHTML +="<div class='"+class_name+"'>"+dom_legend+"</div>";
	}
	else {
		//append the value of dom_label variable to the wrapper
		_dom_wrapper.innerHTML +="<div class='"+class_name+"'>"+dom_label+"</div>";
	}
  return _dom_wrapper;
}



/**
 * This function generates the necessary layout for the input field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 30; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}



/**
 * This function generates the necessary layout for the input type radio element
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_r_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
// 	for (var counter = 0; counter < 20; counter++) {
// 	_dom_wrapper.innerHTML +="<div class='character'></div>";
// 	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}




/**
 * This function generates the necessary layout for the input type checkbox element
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_c_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	//for (var counter = 0; counter < 20; counter++) {
	//	_dom_wrapper.innerHTML +="<div class='character'></div>";
	//}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}




/**
 * This function generates the necessary layout for the select field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_select_basic_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 45; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}



/**
 * This function generates the necessary layout for the select field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_select_layout(dom_label, dom_legend, _dom_wrapper, _class, _tmp_o) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";

	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < _tmp_o.length; counter++) {
	_dom_wrapper.innerHTML +="<div class='option-label'>"+_tmp_o[counter]+"</div>";
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}



/**
 * This function generates the necessary layout for the textarea element 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_textarea_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 90; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}



/**
 * This function generates the necessary layout for the dateofbirth field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_dob_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";


	//append the dob year layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <4; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
	}
	
	//append the dob month layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
	}

	//append the dob day layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
	}

	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}



/**
 * This function generates the necessary layout for the input field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_wrapper, _class) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 14; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class);
}

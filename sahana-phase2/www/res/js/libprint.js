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
 * @package    framework
 * @subpackage printing
 * @tutorial	  
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 
 
/** 
 *
 * README: Sahana OCR friendly Web Form Version 1.1
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * This JavaScript(EMACScript) library provides the functionality to generate Optical Character Recognition friendly forms having compliance with W3C standard web forms.
 *
 *			 ___________________________________________________
 *			|  _			  _           		 _  |
 *			| |_|			 |_|          		|_| |
 *			|  ______________________________________ ________  |
 *			| |______________________________________|________| |	
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			|  ______________________________________ ________  |
 *			| |______________________________________|________| |	
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			|  ______________ ______     ______________ ______  | 
 *			| |______________|______|   |______________|______| |	
 *			| |_|_|_|_|_|_|_|_|_|_|_|   |_|_|_|_|_|_|_|_|_|_|_| |
 *			|  ______________________________________ ________  |
 *			| |______________________________________|________| |	
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			|  ______________________________________ ________  |
 *			| |______________________________________|________| |	
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
 *			|  _		     	     			 _  |
 *			| |_|		    	    		        |_| |
 *			|___________________________________________________|
 *
 *
 * ~ HOW TO USE
 * ~~~~~~~~~~~~
 *
 * 1. First of all copy the file called "libprint.js" to a suitable folder.
 * 2. Links the "libprint.js" file to the HEAD section of the HTML source as shown below:
 *  eg:
 *	<script type="text/javascript" src="../javascript/libprint.js"></script>
 *
 * 3. Then calls the "shn_print_init()" function at your prefered location in the HTML source
 *  eg: 
 *	<a onclick="javascript:shn_print_init()" href="javascript:void(0)" title="XForm">XForm</a>
 *
 * 4. Clicks on the link "XForm" to get the generated output and then navigate through File >> Print in the web browser to print the page.
 *
 * 5. Once the user click on the XForm and needs to switched on to the normal view just click on F5 key or refresh the page
 *
 *
 *
 *
 * ~ LIMITATIONS
 * ~~~~~~~~~~~~~
 *
 * 1. Currently library doesn't give the facility to the user to change the generated field layout structure dynamically except for the date layout.
 *
 * 2. The library will only function in its maximum accuracy when the system is used with en_US locale, with other locales it only generats a form with a basic layout 
 *
 * 3. This version s the generated form only to match a A4 page.
 *
 * 4. Currently the library renders the page accurately with FF2, Opera 8 and IE6   
 *
 * 5. Element extraction process get limits to following parameters:
 *   ~ The form elements should resides within the given DIV element having the CLASS attribute "form-container", but you can change the class attribute name provided that you change the JavaScript library(libprint.js) appropriatly ( in the library search and finds the "shn_print_create_basic_elements_layout()" function and change the "form-container" value to the value used in your HTML source).
 *   ~ The library supports the extaction of required elements only if the elements are structured as shown below.
 *
 *	<div class="form-container">
 *		<fieldset><legend>Personal Details</legend>
 *			<label>First Name</label>
 *			<input type="text" name="fname" class="fname" />
 *			<label>Surname</label>
 *			<input type="text" name="sname" class="sname" />
 *			.......
 *		</fieldset>
 *		<fieldset><legend>Features</legend>
 *			<label for="height">Height</label>
 *			<input type="text" name="height" />
 *			<label>Hair Colour</label>
 *			<select name="opt_hair_color">
 *				<option value="bla" >Black</option>
 *				<option value="bro" >Brown</option>
 *			</select>
 *			.......
 *		</fieldset>
 *		<fieldset><legend>Other Details</legend>
 *			<label>Last Seen location</label>
 *			<input type="text" name="fname" class="fname" />
 *			<label for="physical_comments">Other Distinctive Features</label> 
 *			<textarea name="physical_comments" cols="30" rows="4" ></textarea>
 *			.......
 *		</fieldset>
 *	</div>
 *
 *
 *   ~ Accuracy of the functionality fails if the elements are nested within several fieldset elements as shown below.
 *
 *	<div class="form-container">
 *		<fieldset>
 *			<fieldset><legend>Personal Details</legend>
 *				<label>First Name</label>
 *				<input type="text" name="fname" class="fname" />
 *				<label>Surname</label>
 *				<input type="text" name="sname" class="sname" />
 *				.......
 *			</fieldset>
 *		</fieldset>
 *		<fieldset>
 *			<fieldset><legend>Features</legend>
 *				<label for="height">Height</label>
 *				<input type="text" name="height" />
 *				<label>Hair Colour</label>
 *				<select name="opt_hair_color">
 *					<option value="bla" >Black</option>
 *					<option value="bro" >Brown</option>
 *				</select>
 *				.......
 *			</fieldset>
 *			<fieldset><legend>Other Details</legend>
 *				<label>Last Seen location</label>
 *				<input type="text" name="fname" class="fname" />
 *				<label for="physical_comments">Other Distinctive Features</label>
 *				<textarea name="physical_comments" cols="30" rows="4" ></textarea>
 *				.......
 *			</fieldset>
 *		</fieldset>
 *	</div>
 *	
 */



/**
 * This section contains the necessary CSS style rules for the page
 *
 */
document.writeln(
        '<style type="text/css">'                                       +

//A4 page height: 843.829pt; width:596.971pt; 
		'#print { float: left; width: 510pt; padding: 0; margin: 0 auto; }'	+

		'#print-wrapper { float: left; width: 510pt; /*border: #000 1pt solid;*/ padding: 2pt; margin: 4pt auto; }'	+
		'#print-wrapper h2, #print-wrapper h3 { font-family: Arial, Helvetica, sans-serif; }'	+
		'#print-wrapper h2 { text-align: center; font-family: Georgia, Times, serif; }'	+

		'.top-layout { display: block; width: 510pt; margin: 14pt 0 5pt 0; }'	+
		'.top-layout .top-left { float: left; border: #000 10pt solid; margin: 4pt 0 0 15pt; padding: 0; }'	+
		'.top-layout .top-middle { float: left; border: #000 10pt solid; margin: 4pt 0 0 235pt; padding: 0; }'	+
		'.top-layout .top-right { float: right; border: #000 10pt solid; margin: 4pt 15pt 0 0; padding: 0; }'	+

		'.bottom-layout { display: block; width: 510pt; margin: 5pt 0 12pt 0; }'	+
		'.bottom-layout .bottom-left { float: left; border: #000 10pt solid; margin: 0 0 4pt 15pt; padding: 0; }'	+
		'.bottom-layout .bottom-right { float: right; border: #000 10pt solid; margin: 0 15pt 4pt 0; padding: 0; }'	+

		'ul.instructions { float: left; width: 450pt; list-style-type: circle; margin: 5pt 0 0 24pt; }'	+
		'ul.instructions li { margin: 0; padding: 2pt 0; font-size: 8pt; }'	+

		'.heading { float: left; width: 480pt; margin: 0; padding: 5pt; text-align: center; font-size: 14pt; font-weight: bold; }'	+

		'.fieldset-heading { float: left; clear: both; font-weight: bold; margin: 11pt 2pt 0 15pt; padding: 0; display: block; }'	+
		'.description { float: left; clear: both; margin: 1pt 0 0 15pt; padding: 0 2pt; font-size: 8pt; width: 465pt; }'	+

		'.item-wrap, .label-left, .label-right, .character { float: left; border: #000 1px solid; }'	+
		'.item-wrap { clear: both; margin: 5pt 0 5pt 15pt; width: 466pt; }'	+
		'.item-wrap .label-left { height: 10pt; font-size: 8pt; text-transform: uppercase; width: 330pt; padding: 2pt 5pt; }'	+
		'.item-wrap .label-right { height: 10pt; width: 112pt; padding: 2pt 5pt; }'	+
		'.character { height: 10pt; width: 10pt; padding: 2pt; }'	+

		'.item-wrap-small, .small-left, .small-right, .dob-dd, .dob-mm, .dob-yy, .dob-space, .option-label { float: left; border: #000 1px solid; }'	+
		'.small-left, .small-right, .dob-dd, .dob-mm, .dob-yy, .option-label { font-size: 8pt; text-transform: uppercase; padding: 1pt 5pt; height: 10pt; }'	+
		'.item-wrap-small { width: 224pt; margin: 5pt 0 5pt 15pt; }'	+
		'.item-wrap-small .small-left { width: 144pt; color: #000; }'	+
		'.item-wrap-small .small-right { width: 56pt; }'	+
		'.small-right { text-align: right;  }'	+
		'.small-right a, .small-right a:link { text-decoration: none;  }'	+
		'.dob-dd, .dob-mm, .dob-yy { width: 14pt; color: #ddd; font-size: 5pt; }'	+
		'.dob-space { height: 7pt; border: solid #000 3pt; }'	+
		'.option-label { width: 205pt; height: 10pt; }'	+
		'.space { float: left; clear: both; }'	+
		'a.close, a.close:link { float: right; padding: 2px 2px 0 0; font-size: 10px; margin: 0; }'	+
		'.popup a.dateselection { float: left; padding: 2px 12px; margin: 0 auto; font-size: 11px; font-weight: bold; text-transform: uppercase; color: #000; }'	+
		'.popup a.dateselection:hover { color: #fff; background-color: #000; }'	+
	'</style>' );


/**
 * This section contains the IE specific CSS style rules for the page
 *
 */
document.writeln(
	//This section handles the specific CSS style rules that are required for IE versions six and below
	'<!--[if lte IE 6]>'	+
		'<style type="text/css">'	+
			'#print, #print-wrapper { width: 490pt; }'	+
			'#print-wrapper { padding-left: 25pt; }'	+
			'.top-layout .top-left { margin-left: 0;  }'	+
			'.top-layout .top-middle { margin-left: 117pt; }'	+
			'.bottom-layout .bottom-left { margin-left: 0; }'	+
			'.instructions { margin-left: 1pt; }'	+
			'.fieldset-heading { font-weight: bold; margin: 0; }'	+
			'.item-wrap { margin-left: 0; width: 473pt; }'	+
			'.item-wrap .label-left { width: 323pt; }'	+
			'.item-wrap .label-right { width: 125pt; }'	+
			'.character { height: 10pt; width: 13pt; padding: 1pt; }'	+
			'.item-warp-small { margin-left: 0; }'	+
			'.item-wrap-small .small-left { width: 143pt; }'	+
			'.item-wrap-small .small-right { width: 55pt; }'	+
		'</style>'	+
	'<![endif]-->'	+

	//This section handles the specific CSS style rules that are required for IE version seven
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
		//on success necessary operations are being carried out
		else {  
			//creates a wrapper to hold the generate content
			var dom_wrapper = document.createElement('div');
			dom_wrapper.setAttribute('id','print-wrapper');
			document.getElementById('print').appendChild(dom_wrapper);

			//append the top layout to the page
			shn_print_layout_top('print-wrapper');
		
			//appends the user instructions to the page
			//shn_print_user_instructions();
		
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
		
		shn_print_user_instructions(parent_id);
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
function shn_print_user_instructions(parent_id) { //parent_id

	var dom_ul, dom_li;

		dom_ul = document.createElement('ul');
		dom_ul.setAttribute('class','instructions');
		dom_ul.setAttribute('className','instructions');
		dom_ul.innerHTML += '<li> Fill the necessary fields with CAPITAL LETTERS. </li>';
		dom_ul.innerHTML += '<li> Always use one box per letter and leave one box space to seperate words. </li>';
		document.getElementById(parent_id).appendChild(dom_ul); //'print-wrapper'
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

var present_date_fields = [];
function shn_print_get_fieldset_content() {
	
	// declares the necessary variables and arrays 
	var dom_fieldset = [], dom_legend = [], dom_div_info = [], dom_label = [], val1 = [], val3 = [], val2_div = [], val2_span = [], _val2_p = [];
	var dom_desc;

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
				
				if (_val2_p != null) {
					dom_desc = document.createElement('p');
					dom_desc.setAttribute('class','description');
					dom_desc.setAttribute('className', 'description');
					if (_val2_p[a] != null) {
						dom_desc.innerHTML = _val2_p[a].innerHTML;
					}
					document.getElementById('print-wrapper').appendChild(dom_desc);
				}

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
					
					var date_indx = 0;
 					if ((_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Date of Birth') || (_tmp_l[b] == 'Manufactured Date : ') || (_tmp_l[b] == 'Expire Date :') || (_tmp_l[b] == 'Date of Event') )) {
 						shn_print_add_dob_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b);
						present_date_fields[date_indx] = "id-"+date_indx
						date_indx++ 
 					}
 					else if ((_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Skin Colour') || (_tmp_l[b] == 'Eye Colour') || (_tmp_l[b] == 'Home Phone') || (_tmp_l[b] == 'Adult Males') || (_tmp_l[b] == 'Adult Females') || (_tmp_l[b] == 'Children') || (_tmp_l[b] == 'Displaced') || (_tmp_l[b] == 'Missing') || (_tmp_l[b] == 'Dead') || (_tmp_l[b] == 'Rehabilitated') || (_tmp_l[b] == 'Mobile') || (_tmp_l[b] == 'Phone : ') || (_tmp_l[b] == 'Mobile No : ') || (_tmp_l[b] == 'Telephone') || (_tmp_l[b] == 'Country:') || (_tmp_l[b] == 'Men') || (_tmp_l[b] == 'Women') || (_tmp_l[b] == 'Infected Count') || (_tmp_l[b] == 'Total Count') || (_tmp_l[b] == 'Capacity') )) {
 						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b);
 					}
					else if ( (_tmp_t[b] == 'text') && ((_tmp_l[b] == 'Full Name') || (_tmp_l[b] == 'Address') || (_tmp_l[b] == 'Address : ') || (_tmp_l[b] == 'Other relevant resources : ') || (_tmp_l[b] == 'Equipment : ') || (_tmp_l[b] == 'Organization Name : '))) {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap', b);
					}
					else if (_tmp_t[b] == 'text') {
						shn_print_add_input_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap', b);
					}
					if (_tmp_t[b] == 'file') {
						shn_print_add_input_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap', b);
					}
					if (_tmp_t[b] == 'radio') {
						shn_print_add_input_r_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b );b
					}
					if (_tmp_t[b] == 'checkbox') {
						shn_print_add_input_c_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b );
					}

					if ( (_tmp_t[b] == 'select') && ( (_tmp_l[b] == 'Address') || (_tmp_l[b] == 'Holding Company') )) {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap', b);
					}
					else if (_tmp_t[b] == 'select') { 
						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b );
					}
					if ( (_tmp_t[b] == 'textarea') && (_tmp_l[b] == 'Mobile') ) {
						shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_item_wrap_small,'item-wrap-small', b );
					}
					else if (_tmp_t[b] == 'textarea') {
						shn_print_add_textarea_layout(dom_label, dom_legend, _dom_item_wrap, 'item-wrap', b);
					}
					shn_print_add_ocr_layout();
				}
   			}
 			shn_print_add_line_brake('print-wrapper');
		}
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
	_dom_legend.setAttribute('className','fieldset-heading');
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
	shn_print_add_space('print-wrapper');	
	shn_print_add_space('print-wrapper');
	shn_print_layout_bottom('print-wrapper');
 
	shn_print_add_space('print-wrapper');
	shn_print_add_space('print-wrapper');
	shn_print_add_space('print-wrapper');
	shn_print_add_space('print-wrapper');

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
	_dom_space.setAttribute('className', 'space');
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
		if ( ((920 > page_height) && (page_height > 830))  ) {
 			shn_print_adds_page_layout();
		}
		if ( ((1810 > page_height) && (page_height > 1770))  ) {
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
function shn_print_appent_to_wrapper(_tdom_wrap, _class, _id_tag) {
	_tdom_wrap.setAttribute('class',_class);
	_tdom_wrap.setAttribute('className',_class);
	_tdom_wrap.setAttribute('id','id-'+_id_tag);
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
function shn_print_add_input_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 29; counter++) {
		_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}



/**
 * This function generates the necessary layout for the input type radio element
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_r_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
// 	for (var counter = 0; counter < 20; counter++) {
// 	_dom_wrapper.innerHTML +="<div class='character'></div>";
// 	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}




/**
 * This function generates the necessary layout for the input type checkbox element
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_c_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	//for (var counter = 0; counter < 20; counter++) {
	//	_dom_wrapper.innerHTML +="<div class='character'></div>";
	//}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}



/**
 * This function generates the necessary layout for the select field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_select_basic_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 45; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}



/**
 * This function generates the necessary layout for the select field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_select_layout(dom_label, dom_legend, _dom_wrapper, _class, _tmp_o, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";

	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < _tmp_o.length; counter++) {
	_dom_wrapper.innerHTML +="<div class='option-label'>"+_tmp_o[counter]+"</div>";
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}



/**
 * This function generates the necessary layout for the textarea element 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_textarea_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'label-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='label-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 87; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}



/**
 * This function generates the necessary layout for the dateofbirth field 
 *
 * @param string, string, string
 * @access protected
 */
var choice;
function shn_print_add_dob_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	//this section should implements ajax functionality to allow the user to select the  
	//matching date format, such as MM-DD-YYYY or DD-MM-YYYY or YYYY-MM-DD	
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	var closable = 'closable';
	_dom_wrapper.innerHTML +="<div class='small-right'><a href='#' title='Change Layout' onclick=\"popout();popup('closable', event );\"> X</a></div>";

	shn_print_create_popup_wrapper();
	
	if (choice == 'dd-mm-yyyy') {
		_dom_wrapper = shn_print_generate_d_m_y(_dom_wrapper);
	}
	else if (choice == 'mm-dd-yyyy') {
		_dom_wrapper = shn_print_generate_m_d_y(_dom_wrapper);	
	}
	else if (choice == 'yyyy-mm-dd') {
		_dom_wrapper = shn_print_generate_y_m_d(_dom_wrapper);	
	}	
	else {
		//append the dob year layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <4; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
		}
	
		_dom_wrapper.innerHTML +="<div class='dob-space'></div>";
	
		//append the dob month layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <2; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
		}
	
		_dom_wrapper.innerHTML +="<div class='dob-space'></div>";

		//append the dob day layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <2; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
		}	
	}

	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}


/**
 * This function generates the necessary layout for the y_m_d 
 *
 * @param string
 * @access protected
 * @return string
 */
function shn_print_generate_y_m_d(_dom_wrapper) {

	//append the dob year layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <4; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";
	
	//append the dob month layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";

	//append the dob day layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
	}

 return _dom_wrapper;
}


/**
 * This function generates the necessary layout for the d_m_y 
 *
 * @param string
 * @access protected
 * @return string
 */
function shn_print_generate_d_m_y(_dom_wrapper) {

	//append the dob day layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";
	
	//append the dob month layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";

	//append the dob year layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <4; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
	}

 return _dom_wrapper;
}
 


/**
 * This function generates the necessary layout for the m_d_y  
 *
 * @param string
 * @access protected
 * @return string
 */
function shn_print_generate_m_d_y(_dom_wrapper) {

	//append the month year layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";
	
	//append the dob day layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <2; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
	}
	
	_dom_wrapper.innerHTML +="<div class='dob-space'></div>";

	//append the dob year layout to the wrapper
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter <4; counter++) {
		_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
	}

 return _dom_wrapper;
}


function shn_print_event(format) {

  var cho = document.getElementById("date"+format).innerHTML;
  choice = cho;
  alert(choice + present_date_fields);

/*	
	if (choice == 'dd-mm-yyyy') {
		_dom_wrapper = shn_print_generate_d_m_y(_dom_wrapper);
	}
	else if (choice == 'mm-dd-yyyy') {
		_dom_wrapper = shn_print_generate_m_d_y(_dom_wrapper);	
	}
	else if (choice == 'yyyy-mm-dd') {
		_dom_wrapper = shn_print_generate_y_m_d(_dom_wrapper);	
	}	
	else {
		//append the dob year layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <4; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-yy'>Y</div>";
		}
	
		_dom_wrapper.innerHTML +="<div class='dob-space'></div>";
	
		//append the dob month layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <2; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-mm'>M</div>";
		}
	
		_dom_wrapper.innerHTML +="<div class='dob-space'></div>";

		//append the dob day layout to the wrapper
		//creates and appends required # of boxes where values going to be inputed
		for (var counter = 0; counter <2; counter++) {
			_dom_wrapper.innerHTML +="<div class='dob-dd'>D</div>";
		}	
	}*/
  //alert(choice);
}


/**
 * This function generates the popup div which holds the list of available date types  
 *
 */
function shn_print_create_popup_wrapper() {

	var typeList = new Array(3);
	typeList[0] = 'dd-mm-yyyy';
	typeList[1] = 'mm-dd-yyyy';
	typeList[2] = 'yyyy-mm-dd';

	var _dom_closable = document.createElement('div');
	_dom_closable.setAttribute('id','closable');
	_dom_closable.setAttribute('class','popup');
	_dom_closable.setAttribute('className','popup');
	
	_dom_closable.innerHTML +="<a href='#' name='close' onclick='popout();' class='close'>Close</a><br />";
	for (var indx = 0; indx < typeList.length; indx++ ) {
		_dom_closable.innerHTML +="<a href='#' id='date"+indx+"' class='dateselection' onclick='shn_print_event("+indx+");' title='"+ typeList[indx]+"' > " + typeList[indx]+ " </a> <br />";
	}
	
  	document.getElementById('print-wrapper').appendChild(_dom_closable);  	
}


/**
 * This function generates the necessary layout for the input field 
 *
 * @param string, string, string
 * @access protected
 * @return string
 */
function shn_print_add_input_geography_layout(dom_label, dom_legend, _dom_wrapper, _class, _id_tag) {
	
	_dom_wrapper = shn_print_set_label(dom_label, dom_legend, _dom_wrapper, 'small-left');

	//append the right layout to the wrapper
	_dom_wrapper.innerHTML +="<div class='small-right'></div>";
	
	//creates and appends required # of boxes where values going to be inputed
	for (var counter = 0; counter < 14; counter++) {
	_dom_wrapper.innerHTML +="<div class='character'></div>";
	}
	shn_print_appent_to_wrapper(_dom_wrapper, _class, _id_tag);
}

/**
 *#################################################################################################################
 * This section contains the necessary functions required to handle the popup window 
 *
 */
 
    
function shn_print_move_object(objectId, newXCoordinate, newYCoordinate) {
	// get a reference to the cross-browser style object and make sure the object exists
	var styleObject = shn_print_get_style_object(objectId);
	if(styleObject) {
		styleObject.left = newXCoordinate + 'px';
		styleObject.top = newYCoordinate + 'px';
	 return true;
	} 
	else {
	 // we couldn't find the object, so we can't very well move it
	 return false;
	}
}

function shn_print_get_style_object(objectId) {
    // cross-browser function to get an object's style object given its id
    if(document.getElementById && document.getElementById(objectId)) {
    // W3C DOM
    return document.getElementById(objectId).style;
    } else if (document.all && document.all(objectId)) {
    // MSIE 4 DOM
    return document.all(objectId).style;
    } else if (document.layers && document.layers[objectId]) {
    // NN 4 DOM.. note: this won't find nested layers
    return document.layers[objectId];
    } else {
    return false;
    }
}


/**
 * Copyright (c) 2002 NuSphere Corporation
 *
 * This library is free software; you can redistribute it and/or modify it under the terms of 
 * the GNU Lesser General Public License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public 
 *  License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License along with this library; if not, 
 * write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * If you have any questions or comments, please email:
 * 
 * Dietrich Ayala
 * dietrich@ganx4.com
 * http://dietrich.ganx4.com/nusoap
 * 
 * NuSphere Corporation
 * http://www.nusphere.com
 * 
 */
 
 
//Shows the messages
var oDesc;
var xOffset = 5;
var yOffset = -5;
function popup(targetObjectId, eventObj){
	if(oDesc = new make_obj(targetObjectId)){
		oDesc.css.visibility = "visible"
		// move popup div to current cursor position 
		// (add scrollTop to account for scrolling for IE)
		var newXCoordinate = (eventObj.pageX)?eventObj.pageX + xOffset : eventObj.x + xOffset + ((document.body.scrollLeft)?document.body.scrollLeft:document.documentElement.scrollLeft); 
		var newYCoordinate = (eventObj.pageY)?eventObj.pageY + yOffset : eventObj.y + yOffset + ((document.body.scrollTop)?document.body.scrollTop:document.documentElement.scrollTop);
		shn_print_move_object(targetObjectId, newXCoordinate, newYCoordinate);
	}
}
    
function popout(){ // Hides message
	if(oDesc) oDesc.css.visibility = "hidden"
}


// POP-UP CAPTIONS...
function lib_bwcheck(){ //Browsercheck (needed)
	this.ver=navigator.appVersion
	this.agent=navigator.userAgent
	this.dom=document.getElementById?1:0
	this.opera5=this.agent.indexOf("Opera 5")>-1
	this.ie5=(this.ver.indexOf("MSIE 5")>-1 && this.dom && !this.opera5)?1:0;
	this.ie6=(this.ver.indexOf("MSIE 6")>-1 && this.dom && !this.opera5)?1:0;
	this.ie4=(document.all && !this.dom && !this.opera5)?1:0;
	this.ie=this.ie4||this.ie5||this.ie6
	this.mac=this.agent.indexOf("Mac")>-1
	this.ns6=(this.dom && parseInt(this.ver) >= 5) ?1:0;
	this.ns4=(document.layers && !this.dom)?1:0;
	this.bw=(this.ie6 || this.ie5 || this.ie4 || this.ns4 || this.ns6 || this.opera5)

 return this    
}
    
var bw = new lib_bwcheck()
//Makes crossbrowser object.
function make_obj(obj){
	this.evnt=bw.dom? document.getElementById(obj):bw.ie4?document.all[obj]:bw.ns4?document.layers[obj]:0;
	if(!this.evnt) return false
	this.css=bw.dom||bw.ie4?this.evnt.style:bw.ns4?this.evnt:0;
	this.wref=bw.dom||bw.ie4?this.evnt:bw.ns4?this.css.document:0;
	this.writeIt=b_writeIt;
        
 return this
}
    
// A unit of measure that will be added when setting the position of a layer.
//var px = bw.ns4||window.opera?"":"px";
function b_writeIt(text){
	if (bw.ns4){
		this.wref.write(text);this.wref.close()
	}
	else this.wref.innerHTML = text
}

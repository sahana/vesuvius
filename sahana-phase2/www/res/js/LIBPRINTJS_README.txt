		#=======================================================#
			Sahana OCR friendly Web Form Version 1.0
		#=======================================================#

This JavaScript(EMACScript) library provides the functionality to generate Optical Character Recognition friendly forms out of web forms.

			 ___________________________________________________
			|  _			  _           		 _  |
			| |_|			 |_|          		|_| |
			|  ______________________________________ ________  |
			| |______________________________________|________| |	
			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
			|  ______________________________________ ________  |
			| |______________________________________|________| |	
			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
			|  ______________ ______     ______________ ______  | 
			| |______________|______|   |______________|______| |	
			| |_|_|_|_|_|_|_|_|_|_|_|   |_|_|_|_|_|_|_|_|_|_|_| |
			|  ______________________________________ ________  |
			| |______________________________________|________| |	
			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
			| |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_| |
			|  _		     	     			 _  |
			| |_|		    	    		        |_| |
			|___________________________________________________|


!How to use
~~~~~~~~~~~

* First of all copy the file called "libprint.js" to a suitable folder.
* Links the "libprint.js" file to the HEAD section of the HTML source as shown below:
  eg:
	<script type="text/javascript" src="../javascript/libprint.js"></script>

* Then calls the "shn_print_init()" function at your prefered location in the HTML source
  eg: 
	<a onclick="javascript:shn_print_init()" href="javascript:void(0)" title="XForm">XForm</a>

* Clicks on the link "XForm" to get the generated output and then navigate through File >> Print in the web browser to print the page.

* Once the user click on the XForm and needs to switched on to the normal view just click refresh


!Limitations
~~~~~~~~~~~~~

1. Current library doesn't give the facility to the user to change the generated field layout structure dynamically.

2. This version formats the generated form to match a A4 page only.

3. Element extraction process get limits to following parameters:
   - The form elements should resides within the given DIV element having the CLASS attribute "form-container", but you can change the class attribute name provided that you change the JavaScript library(libprint.js) appropriatly ( in the library search and finds the "shn_print_create_basic_elements_layout()" function and change the "form-container" value to the value used in your HTML source).
   - The library supports the extaction of required elements only if the elements are structured as shown below.

	<div class="form-container">
		<fieldset><legend>Personal Details</legend>
			<label>First Name</label>
			<input type="text" name="fname" class="fname" />
			<label>Surname</label>
			<input type="text" name="sname" class="sname" />
			.......
		</fieldset>
		<fieldset><legend>Features</legend>
			<label for="height">Height</label>
			<input type="text" name="height" />
			<label>Hair Colour</label>
			<select name="opt_hair_color">
				<option value="bla" >Black</option>
				<option value="bro" >Brown</option>
			</select>
			.......
		</fieldset>
		<fieldset><legend>Other Details</legend>
			<label>Last Seen location</label>
			<input type="text" name="fname" class="fname" />
			<label for="physical_comments">Other Distinctive Features</label>
			<textarea name="physical_comments" cols="30" rows="4" ></textarea>
			.......
		</fieldset>
	</div>


   - Accuracy of the functionality fails if the elements are nested within several fieldset elements as shown below.

	<div class="form-container">
		<fieldset>
			<fieldset><legend>Personal Details</legend>
				<label>First Name</label>
				<input type="text" name="fname" class="fname" />
				<label>Surname</label>
				<input type="text" name="sname" class="sname" />
				.......
			</fieldset>
		</fieldset>
		<fieldset>
			<fieldset><legend>Features</legend>
				<label for="height">Height</label>
				<input type="text" name="height" />
				<label>Hair Colour</label>
				<select name="opt_hair_color">
					<option value="bla" >Black</option>
					<option value="bro" >Brown</option>
				</select>
				.......
			</fieldset>
			<fieldset><legend>Other Details</legend>
				<label>Last Seen location</label>
				<input type="text" name="fname" class="fname" />
				<label for="physical_comments">Other Distinctive Features</label>
				<textarea name="physical_comments" cols="30" rows="4" ></textarea>
				.......
			</fieldset>
		</fieldset>
	</div>
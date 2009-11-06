/**Client side validation for forms
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author	  Mifan Careem <mifan@opensource.lk>
* @author	  Janaka Wickramasinghe <janaka@opensource.lk> 
* @author	  Saumya Gunawardana <saumya@opensource.lk>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

//validate email address 
function emailvalidation(entered, alertbox)
{
	with (entered){
		apos=value.indexOf("@");
		dotpos=value.lastIndexOf(".");
		lastpos=value.length-1;
		if (apos<1 || dotpos-apos<2 || lastpos-dotpos>3 || lastpos-dotpos<2) {
			if (alertbox) {
				alert(alertbox);
			} 
			return false;
		}else {
			return true;
		}
	}
}

//validate the correct range of an numeric field 
function valuevalidation(entered, min, max, alertbox, datatype)
{
	with (entered){
		checkvalue=parseFloat(value);
		if (datatype){
			smalldatatype=datatype.toLowerCase();
   			if (smalldatatype.charAt(0)=="i") {
   				checkvalue=parseInt(value)
   			};
  		}
		if ((parseFloat(min)==min && checkvalue<min) || (parseFloat(max)==max && checkvalue>max) || value!=checkvalue){
			if (alertbox!="") {
				alert(alertbox);
			} 
			return false;
		}else {
			return true;
		}
	}
}

//validate the number of digits entered 
function digitvalidation(entered, min, max, alertbox, datatype)
{
	with (entered){
		checkvalue=parseFloat(value);
		if (datatype){
			smalldatatype=datatype.toLowerCase();
   			if (smalldatatype.charAt(0)=="i") {
   				checkvalue=parseInt(value); 
   				if (value.indexOf(".")!=-1) {
   					checkvalue=checkvalue+1
   				}
   			};
  		}
		if ((parseFloat(min)==min && value.length<min) || (parseFloat(max)==max && value.length>max) || value!=checkvalue){
			if (alertbox!="") {
				alert(alertbox);
			} 
			return false;
		}else {
			return true;
		}
	}
}

//validate for empty fields 
function emptyvalidation(entered, alertbox)
{
	with (entered){
		if (value==null || value==""){
			if (alertbox!="") {
				alert (alertbox);
			} 
			return false;
		}else {
			return true;
		}
	}
}

// Test if a field is between min and  max length
function lengthcheck(field, min, max,alertbox)
{
	with (field){
	if ((value.length >= min) && (value.length <= max)){
   		return true;
   	}else{
       alert (alertbox);
    }
    }
    return false;
}

//validate the zip code 
function validatezip(field) 
{
	var valid = "0123456789-";
	var hyphencount = 0;

	if (field.length!=5 && field.length!=10) {
		alert("Please enter your 5 digit or 5 digit+4 zip code.");
		return false;
	}
	for (var i=0; i < field.length; i++) {
		temp = "" + field.substring(i, i+1);
		if (temp == "-") hyphencount++;
		if (valid.indexOf(temp) == "-1") {
			alert("Invalid characters in your zip code.  Please try again.");
			return false;
		}
		if ((hyphencount > 1) || ((field.length==10) && ""+field.charAt(5)!="-")) {
			alert("The hyphen character should be used with a properly formatted 5 digit+four zip code, like '12345-6789'.   Please try again.");
			return false;
   		}
	}
	return true;
}
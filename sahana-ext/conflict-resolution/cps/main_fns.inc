<?php
/* $Id; */

/**
* Default functions of CPS
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author   Isuru Samaraweera
* 
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/

//home page of the child protection system
function shn_cps_default(){
?>
<h1 align="center">Children Registry</h1>
<br>
<div id="resulthome">
<img src="theme/default/img/cr.png" align="center" />
<ul>
   <li>Children Registry is the central repository to manage Children.</li>
	<br>
	<li>Helps to coordinate children activities in an efficient manner.</li>
	<br>
	<li>Explore the facilities like Adding Children based on different categories </li>
	<br>
	<li>Explore the facilities like Editing Children based on different categories </li>
	<br>
	<li>Explore the facilities like Viewing Information on Children based on different categories </li>
	<br>
	<li>Data BackUp and Restore</li>
	<li>Export Data in to Differnt Formats(Excel,Pdf etc)</li>
	<br>
	<br>
	
</ul>
	
</div>
								
	
	<?php
	}

//add children center
function shn_cps_achildcenter(){
global $global;
include($global['approot'].'/mod/cps/child_center.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
																												
} 

//add child personal data
function shn_cps_achildpersonal()
{

global $global;
include($global['approot'].'/mod/cps/child_personal.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
}

//add child relational data
function shn_cps_achildrelation()
{
global $global;
include($global['approot'].'/mod/cps/child_relation.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
}

//add child family status
function shn_cps_achildfstatus()
{
global $global;
include($global['approot'].'/mod/cps/child_familystatus.inc');
require_once($global['approot'].'/inc/handler_form.inc');
//check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{

if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
}

//add child reporter
function shn_cps_achildreporter()
{

global $global;
include($global['approot'].'/mod/cps/reporting_person.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}}
break;
default:
_shn_cps_cadd_start();
break;
}
}


//add child education
function shn_cps_achildeducation()
{

global $global;
include($global['approot'].'/mod/cps/child_educational_details.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
}

//add child health
function shn_cps_achildhealth()
{

global $global;
include($global['approot'].'/mod/cps/child_health.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:
_shn_cps_cadd_start();
break;
}
}

//add child behaviour
function shn_cps_achildbehaviour()
{

global $global;
include($global['approot'].'/mod/cps/child_behaviour.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:

_shn_cps_cadd_start();
break;
}
}




//add child properties
function shn_cps_achildproperties()
{

global $global;
include($global['approot'].'/mod/cps/child_properties.inc');
require_once($global['approot'].'/inc/handler_form.inc');
// check action sequence
switch($_REQUEST['seq']){
case 'chk':
if($_POST['print'])
_shn_cps_print();
else
{
if(_shn_cps_validate_error())
_shn_cps_cadd_start(true);
else
{
_shn_cps_cadd_commit();
}
}
break;
default:

_shn_cps_cadd_start();
break;
}
}






//edit child center
function shn_cps_edtchildcenter()
{
global $global;
include($global['approot'].'/mod/cps/childcenteredit.inc');
require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);

	switch($str)
        {
	case 'chck':
if($_POST['print'])
_shn_cps_print();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {
 _shn_cps_cedt_commit();
   
}
}	
break;
case 'disp':
_shn_cps_cedt_start();
break;	
case 'cedt':
{  
$code=substr($ostr,4);//getting the center from the url
_shn_cps_cedt_showform(false,$code);
}
break;
case 'cdel':
{  
$code=substr($ostr,4);//getting the center from the url
_shn_cps_cdel_childcenter($code);
}
break;
default :
_shn_cps_search_edt_frm();
break;
}
																																											
} 



//edit child personal data
function shn_cps_edtchildpersonal()
{
global $global;
  include($global['approot'].'/mod/cps/childpersonaledit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
	if($_POST['print'])
_shn_cps_print_data();
else
{
if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
        else
        {
         _shn_cps_cedt_commit();
        }
	
}
	break;
	case 'disp':
	_shn_cps_cedt_start();
	break;	
        case 'cedt':
        {
        $code=substr($ostr,4);//getting the child_code from the url
        _shn_cps_cedt_showform(false,$code);
        }
        break;
        case 'cdel':
        {
        $code=substr($ostr,4);//getting the child_code from the url
        _shn_cps_cdel_childpersonal($code);
        }
        break;
	default :
	_shn_cps_search_edt_frm();
     	break;
	}
																														
 } 

//edit child reporter
function shn_cps_edtchildreporter()
{
global $global;
  include($global['approot'].'/mod/cps/child_reporter_edit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
	if($_POST['print'])
_shn_cps_print_data();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
        else
        {
         _shn_cps_cedt_commit();
        }
	
}
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
        case 'cedt':
        {
        $code=substr($ostr,4);//getting the child_code from the url
        _shn_cps_cedt_showform(false,$code);
        }
        break;
        case 'cdel':
        {
        $code=substr($ostr,4);//getting the child_code from the url
        _shn_cps_cdel_childpersonal($code);
        }
        break;
	default :
	_shn_cps_search_edt_frm();
     	break;
	}
	
																																												
 } 




//edit child relation data
function shn_cps_edtchildrelation()
{


global $global;
  include($global['approot'].'/mod/cps/childrelationedit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
	if($_POST['print'])
_shn_cps_print();
else
{

	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
}	
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);

}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childrelation($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 






//edit child family data
function shn_cps_edtchildfstatus()
{


global $global;
  include($global['approot'].'/mod/cps/child_familystatusedit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
	if($_POST['print'])
_shn_cps_print();
else
{

	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
}
	
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);

}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childfamilystatus($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 


//edit child educational details
function shn_cps_edtchildeducation()
{
  global $global;
  include($global['approot'].'/mod/cps/child_educational_detailsedit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
if($_POST['print'])
_shn_cps_print();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
}	
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);

}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childeducation($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 


//edit child health
function shn_cps_edtchildhealth()
{
global $global;
include($global['approot'].'/mod/cps/child_healthedit.inc');
require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
if($_POST['print'])
_shn_cps_print();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
	}
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);
}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childhealth($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 

//edit child behaviour data

function shn_cps_edtchildbehaviour()
{


global $global;
  include($global['approot'].'/mod/cps/child_behaviouredit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
if($_POST['print'])
_shn_cps_print();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
	}
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);

}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childbehaviour($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 





//edit child properties
function shn_cps_edtchildproperties()
{
global $global;
  include($global['approot'].'/mod/cps/child_propertiesedit.inc');
  require_once($global['approot'].'/inc/handler_form.inc');
	// check action sequence
$ostr=$_REQUEST['seq'];
$str=substr($ostr,0,4);
	switch($str)
        {
	case 'chck':
if($_POST['print'])
_shn_cps_print();
else
{
	if(_shn_cps_validate_error())
       _shn_cps_cedt_showform(true,0);
       else
       {

 _shn_cps_cedt_commit();
       }
	}
	break;
	case 'disp':
  
	_shn_cps_cedt_start();
	break;	
case 'cedt':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cedt_showform(false,$code);

}
break;
case 'cdel':
{
$code=substr($ostr,4);//getting the child_code from the url
_shn_cps_cdel_childproperties($code);

}
break;
	default :
  
	_shn_cps_search_edt_frm();

	     	break;
		}
	
																																												
} 


function shn_cps_backuprestore()
{
include('backuprestore/backup.php');
}



//query view
function shn_cps_queryview()

{
global $global;
include($global['approot'].'/mod/cps/query_view.inc');
require_once($global['approot'].'/inc/handler_form.inc');
$seq=$_REQUEST['seq'];

switch($seq)
{
case 'res':
shn_cps_query_results();
//include("testexcel.inc");
break;
default:
shn_cps_query_view();

}

}

?>

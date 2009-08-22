<?php
/* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     H Iroshan <iroshanmail@gmail><http://www.fosspirit.blogspot.com>
* @package    sahana
* @subpackage amp
*/



function _shn_amp_save_mashup(){
shn_form_fopen("save_mashup",null,array('req_message'=>false));
shn_form_fsopen(_t("Save Mashup"));
//shn_form_select($methods,"Methods",'method',null,array('br'=>false));
//shn_form_hidden(array('wbsmod'=>$_POST['method'],'wsdl_url'=>$url));
shn_form_text(_t("Mashup Name : "),'amp_name','size="50"',array('br'=>false));
shn_form_submit(_t('Save >>'));
shn_form_fsclose();
shn_form_fclose();

}

function shn_amp_save_mashup(){

//need to implement here
//var_dump($_SESSION);
global $global;
$db = $global['db']; 
$user_id=$_SESSION['user_id'];
$amp_service= $_SESSION['amp_service'];
$amp_url_list=array();
$amp_url_list=$_SESSION['amp_url'];
$amp_name=$_POST['amp_name'];
$amp_id=shn_create_uuid('amp');

$wbsmod=$_SESSION['wbsmod'];
 $query = "INSERT INTO amp_mashup VALUES('$amp_id','$amp_name','$user_id','$amp_service','$wbsmod')";
 $db->Execute($query);


for($i=1;$i<sizeof($amp_url_list);$i++)	{
	
   		$amp_url=$_SESSION['amp_url'][$i];
   		$query = "INSERT INTO amp_mashup_url VALUES('$amp_id','$amp_url');";
 		$db->Execute($query);
   		
}
echo '<h2>Masup Save Sucessfully</h2>';	
}


function shn_amp_add_url(){
//need to implement here
shn_form_fopen("load_other_url",null,array('req_message'=>false));
//var_dump($_SESSION);
shn_form_fsopen("Locate Sahana instence");
shn_form_text(_t("URL : "),'wsdl_url','size="50"',array('br'=>false));
shn_form_hidden(array('method'=>$_SESSION['service']));
shn_form_submit(_t('Add Url>>'));
shn_form_fsclose();
return;
}




?>


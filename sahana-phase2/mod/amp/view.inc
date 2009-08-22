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



function shn_amp_view_result($results){
$item="item";
$headers[] = array();
$hsize=sizeof($results[0]->$item);
$arr = $results[0]->item;
$headers[]=$arr;

for($j=1;$j<sizeof($results);$j++){
	$records = $results[$j]->$item;
		for($k=0;$k<$hsize;$k++){
		$tb_items[$j][$k]=$records[$k];
		
		//echo $records[$k];
		}
	//var_dump($records);
	
	//echo $records[$j];
		
}
shn_amp_add_filter($results,"test","test");
shn_html_table($tb_items, $headers, null, array('class'=>'wide'));

return;
}

function shn_amp_view_mashup()
{
global $global;
$db = $global['db'];
$user_id=$_SESSION['user_id'];
$query = "SELECT mashup_uuid,name FROM amp_mashup WHERE user_uuid=$user_id";
$res=$db->Execute($query);

 $type_list=array();
    $type_list[] = array('Masup Names');
    while((!$res==NULL) && (!$res->EOF)) {
    	    $type_list[] = array($res->fields["name"]);
    		$res->MoveNext();
    }

_shn_amp_view_mashup($type_list);


}



function _shn_amp_view_mashup($results){


$headers[] = array();
$hsize=sizeof($results[0]);
$arr = $results[0];

$headers[]=$arr;
 
//echo sizeof($results);
for($j=1;$j<sizeof($results);$j++){

	$records = $results[$j];
		for($k=0;$k<$hsize;$k++){
		$tb_items[$j][$k]=$records[$k];
		
		
		}
	
}

shn_html_table($tb_items, $headers, null, array('class'=>'wide'));

}

function shn_amp_delete_empmashup(){
global $global;
$db = $global['db'];
$mashup_uuid=$_SESSION['mashup_uuid'];
$query = "DELETE FROM amp_mashup WHERE mashup_uuid='$mashup_uuid'";
$res=$db->Execute($query);
echo '<h2>Delete Complete</h2><br />';

}

function shn_amp_show_mashup(){
global $global;
$db = $global['db'];
$mashup_uuid=$_POST['mashup'];
$_SESSION['mashup_uuid']=$mashup_uuid;
$_SESSION['del_muid']=$mashup_uuid;
$_SESSION['cstatus']='false';
$query = "SELECT url FROM amp_mashup_url WHERE mashup_uuid='$mashup_uuid'";
$res=$db->Execute($query);

$_SESSION['sec_flag']='true';
 $url_list=array();
$_SESSION['edit_url']=null;
 while((!$res==NULL) && (!$res->EOF)) {

  	 $url_list[] =$res->fields["url"];
     $res->MoveNext();
    }
  //var_dump($url_list);
  if($url_list==null)
  {
 echo '<h2>Empty Mashup</h2><br />';
$_SESSION['url']=null;
$_SESSION['edit_url']=null;
$_SESSION['amp_url']=null;

shn_form_fopen("delete_empmashup",null,array('req_message'=>false));
shn_form_fsopen(_t("Delete Mashup"));
shn_form_submit(_t('Delete>>'));
shn_form_fsclose();
shn_form_fclose();

shn_form_fopen("locate_ws",null,array('req_message'=>false));
shn_form_fsopen(_t("Add Instense"));
shn_form_hidden(array('status'=>'true'));
shn_form_submit(_t('Add>>'));
shn_form_fsclose();
shn_form_fclose();


  
  }else{
   $_SESSION['amp_url']=null;
    $_SESSION['amp_url']=$url_list;
    for($p=0;$p<sizeof($url_list);$p++){
	$swquery ="SELECT service,wbsmod FROM amp_mashup WHERE mashup_uuid='$mashup_uuid'";
	$res=$db->Execute($swquery);
	
	
	
	$url=$url_list[$p];

	$_SESSION['amp_service']=$res->fields["service"];
	$_SESSION['wbsmod']=$res->fields["wbsmod"];

	shn_amp_sahana_load_other_method_add($url);
	}
			}

}

function shn_amp_add_filter($results,$murl,$mmethod){
$item="item";
$headers[] = array();
$hsize=sizeof($results[0]->$item);
$arr = $results[0]->item;
$headers[]=$arr;

global $global;
$db = $global['db'];
$mashup_uuid=$_SESSION['mashup_uuid'];
$time=time();
$temp_query = "INSERT INTO  amp_filter(create_time,uid,masup_url,method,column_name,value)
VALUES (".$time.",'".$_SESSION['user_id']."','".$murl."','".$mmethod;

//echo time();
for($j=0;$j<$hsize;$j++){
		$temp_query_data= $temp_query."','".$arr[$j];
		//echo $temp_query_data;
		for($k=1;$k<sizeof($results);$k++){
		$records = $results[$k]->$item;
		$query=$temp_query_data."','".$records[$j]."')";
		
		//echo $query;
		$res=$db->Execute($query);
		//$tb_items[$j][$k]=$records[$k];
		
		//;
		}
	//var_dump($records);
	
	//echo $records[$j];
		
}

}





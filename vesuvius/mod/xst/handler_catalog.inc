<?
/**
 * @name         Extensible Streaming
 * @version      1.0
 * @package      xst
 * @author       Ishan Liyanage <ishanul@gmail.com>
 * @author       Richard Smith <s0459387@sms.ed.ac.uk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


function shn_text_catalog_unit_cat() {
	global $global;
	$db  = $global['db'];
	$cat = mysql_real_escape_string($_GET{"cat"});
	$q   = "select unit_uuid,name from ct_unit where unit_type_uuid ='$cat'";
	$res_child=$db->Execute($q);

	if(!$res_child==NULL && !$res_child->EOF){
		while(!$res_child->EOF){
			$res=$res.",".$res_child->fields[0];
			$res=$res.",".$res_child->fields[1];
			$res_child->MoveNext();
		}
		echo $res;
	} else {
		echo "null,";
	}
}



function shn_text_catalog_sub_cat(){
	global $global;
	$db   = $global['db'];
	$cat  = mysql_real_escape_string($_GET{"cat"});
	$flag = mysql_real_escape_string($_GET{"flag"});
	if($flag==false) {
		$q="select ct_uuid,name from ct_catalogue where parentid='{$cat}'";
		$res_child=$db->Execute($q);
	} else if($flag==true) {
		$q="select ct_uuid,name from ct_catalogue where parentid='{$cat}' and final_flag='0' ";
		$res_child=$db->Execute($q);
	}

	$res=$res.","."";
	$res=$res.","."";

	if(!$res_child==NULL && !$res_child->EOF){
		while(!$res_child->EOF){
			$res=$res.",".$res_child->fields[0];
			$res=$res.",".$res_child->fields[1];
			$res_child->MoveNext();
		}
		echo $res;
	} else {
		echo "null,";
	}
}

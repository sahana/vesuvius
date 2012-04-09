<?
/**
 * @name         UUID Library
 * @version      1.1
 * @package      framework
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.1101
 */



/**
 * shn_generate_uuid
 *
 * @access public
 * @return void
 */
function shn_generate_uuid($width) {
	//random number between 0-36
	for($i=0;$i<$width;$i++){
		if(($num = rand(1,36)) < 27 ) {
			$uuid .= chr($num+96);
		} else {
			$uuid .= 36 - $num;
		}
	}
	return $uuid;
}



/**
 * @access public
 * @return void
 */
function shn_is_p_uuid_valid($p_uuid) {
	global $global;
	$q = "
		SELECT *
		FROM person_seq;
	";
	$result = $global['db']->Execute($q);
	$id = $result->fields["id"];

	$e = explode("person.", $p_uuid);
	$num = (int)$e[1];

	if($num > $id) {
		return false;
	} else {
		return true;
	}
}



/**
 * shn_create_uuid
 *
 * @param string $type
 * @access public
 * @return void
 */
function shn_create_uuid($type='person') {
	global $conf;
	global $global;

	switch ($type){
		case 'person':
		case 'p' :
			$gen_id = $conf['base_uuid'].'person.'._shn_gen_id('person');
			break;

		case 'pfif_note':
		case 'pfn' :
			$gen_id = $conf['base_uuid'].'note.'._shn_gen_id('pfif_note');
			break;

		case 'image':
		case 'img' :
			$gen_id = _shn_gen_id('image');
			break;

		case 'image_tag':
		case 'tag' :
			$gen_id = _shn_gen_id('image_tag');
			break;

		case 'mpres':
			$gen_id = _shn_gen_id('mpres');
			break;

		case 'edxl_co_header':
			$gen_id = _shn_gen_id('edxl_co_header');
			break;

		case 'edxl_de_header':
			$gen_id = _shn_gen_id('edxl_de_header');
			break;

		case 'voice_note':
			$gen_id = _shn_gen_id('voice_note');
			break;

		case 'incident':
		case 'inc' :
			$gen_id = _shn_gen_id('incident');
			break;

		case 'hospital' :
		case 'h' :
			$gen_id = _shn_gen_id('hospital');
			break;

		default :
			$gen_id = null;
			break;
	}

	// temporary for debugging....
	//require_once($global['approot'].'/mod/lpf/lib_lpf.inc');
	//daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, "gen_id >> ".$gen_id, print_r(debug_backtrace(), true));
	//daoErrorLog(__FILE__, __LINE__, __METHOD__, __CLASS__, __FUNCTION__, "gen_id >> ".$gen_id, print_r(get_defined_vars(), true));

	return $gen_id;
}



/**
 * _shn_gen_id
 *
 * @param string $type
 * @access protected
 * @return void
 */
function _shn_gen_id($type = 'person') {
	global $global;
	global $conf;
	if($conf['db_engine'] == 'mysql'){
		if(isset($conf['storage_engine']) && $conf['storage_engine'] != '' && strlen(trim($conf['storage_engine'])) > 0) {
			$engine = $conf['storage_engine'];
			$global['db']->Execute("set storage_engine ='{$engine}'");
		}
	}
	$tables = $global['db']->MetaTables("TABLE", false, false);
	$type .= "_seq";
	if(array_search($type, $tables) == false) {
		$global['db']->CreateSequence($type, 1);
	}
	return $global['db']->GenID($type);
}

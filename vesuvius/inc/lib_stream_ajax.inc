<?
/**
 * @name         AJAX Stream Library
 * @version      1.0
 * @package      framework
 * @subpackage   stream_ajax
 * @author       H J P Fonseka <jo@respere.com>
 * @author       Janaka Wickramasinghe <janaka@opensource.lk>
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


require_once($global['approot']."/3rd/xajax/xajax.inc.php");

function shn_stream_init() {
	global $global;

	//create the xajax objects
	$global['xajax'] = new xajax();
	$global['xajax_res']= new xajaxResponse();

	//xajax finction registry
	$global['xajax_functions']=array();
}



function shn_stream_close() {
	global $global;

	//since the security is checked only after the initialization, process the request here
	$module=explode('_',$_REQUEST['xajax']);
	$module=$module[0];

	//for safty strip out any slashes
	$module  = str_replace('/','_' , $module);

	//include the module xajax library
	$filename = $global['approot'].'/mod/'.$module.'/xajax.inc';

	if(file_exists($filename)){
		require_once($filename);
		//registor the available functions
		foreach($global['xajax_functions'] as $function){
		$global['xajax']->registerFunction($function);
		}
	} else{
		add_error('Function does not exists');
	}

	//process the xajax request
	$global['xajax']->processRequests();
}



function shn_ajax_check_perms() {
	return ALLOWED;
	//skip authentication for the moment
}


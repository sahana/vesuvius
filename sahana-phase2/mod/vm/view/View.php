<?php

/**
* A super class with references to the model and the template engine
*
* PHP version 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author       Antonio Alcorn
* @author       Giovanni Capalbo
* @author		Sylvia Hristakeva
* @author		Kumud Nepal
* @author		Ernel Wint
* @copyright    Lanka Software Foundation - http://www.opensource.lk
* @copyright    Trinity Humanitarian-FOSS Project - http://www.cs.trincoll.edu/hfoss
* @package      sahana
* @subpackage   vm
* @tutorial
* @license        http://www.gnu.org/copyleft/lesser.html GNU Lesser General
* Public License (LGPL)
*/

/**
 * View.php - define the View class.
 *
 * The View class is a superclass of all views in the entire module. Mainly, it takes care of setting up
 * the PHP Template library.
 */


class View
{

	/**
	 * Define instance variables
	 */

	protected $model;		//a reference to the particular model being used (Volunteer, Project, etc.)
	protected $engine;		//a reference to the Template Engine Object for later use when displaying

	/**
	 * The View constructor, which simply creates a smarty object and sets the appropriate directories
	 * for a Smarty object, so that all subclasses can use this object to display
	 * PHP Templates.
	 *
	 * @param $model a reference to the model used in the particular View.
	 */

	function View(&$model=null) {
		global $global;
		$this->model = &$model;
		$this->engine = new Whiz(SHN_VM_ENGINE_CACHE_DIR, SHN_VM_ENGINE_TEMPLATE_DIR);
	}

	function displayConfirmation($msg) {
		echo "<div class=\"confirmation message\">$msg</div>\n";
	}

	/**
	 * Displays the paging navigation based on the act-vm_action pairs. Relies on call to DAO::getCurrentPage()
	 * first to set some global variables. This is based upon the sahana paging navigation mechanism, but is
	 * a bit different to handle different page sizes and different navigations when form POST data is involved.
	 *
	 * @param $url		the base url to use when creating the navigation links
	 * @param $use_post	true to use submit buttons instead of links to navigate the pages. if this
	 * 					is true, $url will be ignored by the template because the current form will
	 * 					simply be submitted with the paging inputs.
	 */
	function showPagingNavigation($url, $use_post=false) {
	    global $global;

	    $res = $global['vm_page_result'];
	    $rpp = $global['vm_page_rpp'];

	    //if no records were found return
	    if($res->RecordCount() == 0){
	        return;
	    }

	    if(isset($_REQUEST['page'])) {
	        $page=$_REQUEST['page'];
	    } else {
	        $page=1;
	    }

	    //Calculate starting and ending page numbers to use as links where
	    // we want to show 10 or 11 consecutive links plus some ellipses. The
	    // links themselves are figured out in the template file.
	    //For example, if the current page is 55 out of 200, then start
	    // would be 50 and end would be 60, leading eventually to a menu of links:
	    // 1...50 51 52 53 54 55 56 57 58 59 60...200
	    //If the current page is 3, this code would produce links for pages 1 through 10

	    $start = $page - 5;
	    $end = $page + 5;
	    $last = $res -> LastPageNo();

	    if($start < 1) {
	        $end = $end - $start + 1;
	        $start = 1;
	    }

	    if($end > $last) {
	        $start = $start - ($end - $last);
	        $end = $last;
	        if($start < 1) {
	            $start = 1;
	        }
	    }

		$this->engine->assign('use_post', $use_post);
		$this->engine->assign('url', $url);
	    $this->engine->assign('page', $page);
	    $this->engine->assign('last', $last);
	    $this->engine->assign('rpp', $rpp);
	    $this->engine->assign('start', $start);
	    $this->engine->assign('end', $end);
	    $this->engine->display('volunteer/paging_navigation.tpl');
	}
}



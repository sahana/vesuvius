<?php
/**
 * skel xajax library
 * 
 * @package    framework
 * @author J P Fonseka <jo@respere.com>
 * @copyright  Respere http://www.respere.com
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 */

global $global;

// you have to add all the function names to this array inorder for xajax to work
array_push($global['xajax_functions'],'skel_hello_world');
array_push($global['xajax_functions'],'skel_calculate');
array_push($global['xajax_functions'],'skel_check_user');
array_push($global['xajax_functions'],'skel_add_user');
array_push($global['xajax_functions'],'skel_slow');


function skel_hello_world(){
    global $global;
    $global['xajax_res']->addAssign('click_me','innerHTML','Hello World!');
    return $global['xajax_res']->getXML();
}


function skel_calculate($val1 ,$val2){
    global $global;
    $result = $val1 + $val2 ;
    $global['xajax_res']->addAssign('result','innerHTML',$result);
    return $global['xajax_res']->getXML();
}

function skel_check_user($user){
    global $global;
    if( array_key_exists($user,$_SESSION['demo_users'])){
        $global['xajax_res']->addAssign('check','innerHTML','<span style=\'color:red\'>User id not available</span>');
    }
    else{
        $global['xajax_res']->addAssign('check','innerHTML','<span style=\'color:green\'>User id available</span>');
    }
    return $global['xajax_res']->getXML();
}

function skel_add_user($form){
    global $global;
    $_SESSION['demo_users'][$form['user_id']]=$form['email'];
    $users = print_r($_SESSION['demo_users'],true);
    $global['xajax_res']->addAssign('users','innerHTML',$users);
    return $global['xajax_res']->getXML();
}

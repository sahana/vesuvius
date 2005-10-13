<?php
/**
* This is the config file for the OR module, specifies configuration
* settings plus  ACL settings
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @package    Sahana - http://sahana.sourceforge.net
* @author     Ravindra De Silva
* @copyright  Lanka Software Foundation - http://www.opensource.lk
*/



// provide the nice display name for the OR  module
$conf['mod_or_name'] = "Organization Registry";

/**********************************************************************/
/* specify ACL settings
* the syntax for specifying ACL has been made easy as possible
* therefore it does not allow you to specify very granular ACLs
* when the module is installed these ACL settings will be read 
* and thereafter you can specify very granular permissions through
* the Administration page.
* in this file specify 
* 1. action groups
* 2. custom roles
* 3. permissions for the roles to action groups
* 4. list the actions with group information (action groups the action belongs to)
* thats all you can and should do here
* for example you add a custom role "Branch Manager"
* then you give permission to him to "create"
* but if you want to prevent him create branches ,but still
* allow him to create him users, you can specify that also
* with lot of effort ,therefore specify those kind of permissions
* from the administrator interface.
*/

/**
*specify the action groups and symbolic letters
*from now on 'C' means 'create'
*/
$conf['shn_or_action_groups'] = array(
    'create' => 'cre',
    'delete' => 'del',
    'update' => 'upd',
    'view'   => 'viw',
	'access' => 'acc'
);

/**
*by default "admin","user",and "guest" roles
*are avaliable ,but if the module requires additional
*roles ,specify them here.
* e.g "owner","manager"
*/

$conf['shn_or_specific_roles'] = array(
    'D'=>'Data Entry Operator',
    'B'=>'Branch Manager'
);

// list available permissions for OR module
$conf['shn_perms_or'] = array(
    'cre' => 'ABDGU',
    'del' => 'A',
    'upd' => 'ABDU',
    'viw'   => 'ABDGU',
	'acc' => 'ABDU'
);

// assign the functions to permissions to be used by the ACL
/**
*we dont want the guest to enter to OR
* therefore action group is 'A' which is avaliable
*only to logged in users("admin","data entry operator","user")
*/
$conf['shn_or_default'] = array(
    'perms'=>array('acc')
);
$conf['shn_or_register'] = array(
    'perms'=>array('cre')
);

$conf['shn_or_org_vw'] = array(
    'perms'=>array('viw'),
    'cases'=>array('all','one')
);
/*
*when the edit org page loads its possible to update
*organization data and create or delete branches 
*so this function is only avaliable to admin
*/
$conf['shn_or_edit_org']=array('cre','del','upd');


//branches
$conf['shn_or_view_branch'] = array('viw'); 
$conf['shn_or_add_branch'] = 'C';
/*
* when the user clicks the link to edit branch ,the
*action is "shn_or_edit_branch", once the edit page loads
*user will  make changes and click the submit button, and the
*relevant action is "shn_or_edit_branch_submit", and permissions
*for "shn_or_edit_branch_submit" are derived from 
*"shn_or_edit_branch"
*but you can overide by having a seperate entry in this config 
*for "shn_or_edit_branch_submit".
*but i dont see a reason why you should !
*/
$conf['shn_or_edit_branch'] = 'U'; 
$conf['shn_or_del_branch'] = 'D'; 

//users
$conf['shn_or_add_user']='C';
$conf['shn_or_edit_user']='U';
$conf['shn_or_del_user']='D';
// advanced search
$conf['shn_or_adv_search']='V';
$conf['shn_or_browse']='V';
//reports
$conf['shn_or_location_report']='V';
$conf['shn_or_services_report']='V';
$conf['shn_or_organization_report']='V';
//consoles
$conf['shn_or_admin_console']='ACDV';

?>




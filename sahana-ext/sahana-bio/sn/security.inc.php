<?php

/**
 * Security Controller of the Social Network
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botejue
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

global $global;
if(isset($global['module_actions'])==false){
    $global['module_actions'] = array();
}
$actions = array();

//main function

$actions[_t('Social Networking Default')]['functions'] = array ('shn_sn_default');

$actions[_t('Sign Up')]['functions'] = array ('shn_sn_signup','shn_sn_signup_cr');

$actions[_t('Friends Page')]['functions'] = array ('shn_sn_friends');
$actions[_t('Search People')]['functions'] = array('shn_sn_search_people','shn_sn_search_people_cr');
$actions[_t('Add Friends')]['functions'] = array('shn_sn_add_as_friend');
$actions[_t('View Profiles')]['functions'] = array('shn_sn_view_profile');
$actions[_t('View My Profile')]['functions'] = array('shn_sn_my_prof');
$actions[_t('Edit My Profile')]['functions'] = array('shn_sn_edit_my_prof','shn_sn_change_name','shn_sn_change_name_cr','shn_sn_change_personal_details','shn_sn_change_personal_details_cr','shn_sn_change_medical_information','shn_sn_change_medical_information_cr','shn_sn_change_contact_information','shn_sn_change_contact_information_cr','shn_sn_change_profile_visibility','shn_sn_change_profile_visibility_cr');
$actions[_t('User Interests')]['functions'] = array('shn_sn_add_interest','shn_sn_find_people_with_interest','shn_sn_add_interest_form','shn_sn_add_interest_cr','shn_sn_default');
$actions[_t('Request Forum')]['functions'] = array('shn_sn_log_forum','shn_sn_default','shn_sn_notification','shn_sn_req_access');
$actions[_t('Add Post')]['functions'] = array('shn_sn_add_post','_shn_sn_add_post','shn_sn_view_forum','shn_sn_default','_shn_sn_view_forum','shn_sn_req_access','shn_sn_view_post','shn_sn_forum_index');
$actions[_t('Edit Post')]['functions'] = array('shn_sn_edit_post');
$actions[_t('Delete Post')]['functions'] = array('shn_sn_delete_post');

$actions[_t('Groups Page')]['functions'] = array ('shn_sn_groups','shn_sn_req_access_group','shn_sn_view_group_members','shn_sn_add_as_friend');

$actions[_t('Mailbox Page')]['functions'] = array ('shn_sn_mailbox');
$actions[_t('Mail Inbox')]['functions'] = array ('shn_sn_mail_inbox');
$actions[_t('Mail Outbox')]['functions'] = array ('shn_sn_mail_outbox');
$actions[_t('Mail Bin')]['functions'] = array ('shn_sn_mail_bin');

$actions[_t('Notifications')]['functions'] = array('shn_sn_view_notifications');

//admin function

$actions[_t('Admin Home')]['functions'] = array ('shn_sn_ad_default','shn_sn_ad_adinmenu','shn_sn_ad_home');

//Group admin function
$actions[_t('Group Admin Panel')]['functions'] = array ('shn_sn_ad_manage_groups','shn_sn_ad_groups_adinmenu');

//category type mamagement
$actions[_t('View Category')]['functions'] = array ('shn_sn_ad_view_category');
$actions[_t('Create Category')]['functions'] = array ('shn_sn_ad_create_category','shn_sn_ad_create_category_cr');
$actions[_t('Edit Category')]['functions'] = array ('shn_sn_ad_edit_category','shn_sn_ad_edit_category_confirm','shn_sn_ad_edit_categoty_cr');
$actions[_t('Delete Category')]['functions'] = array ('shn_sn_ad_delete_category','shn_sn_ad_delete_category_confirm','shn_sn_ad_delete_category_cr');

//group management
$actions[_t('View Group')]['functions'] = array ('shn_sn_ad_view_groups_info');
$actions[_t('Create Group')]['functions'] = array ('shn_sn_ad_create_groups','_shn_sn_get_sub_categories','shn_sn_ad_create_groups_cr');
$actions[_t('Edit Group')]['functions'] = array ('shn_sn_ad_edit_groups_info','shn_sn_ad_edit_groups_info_confirm','shn_sn_ad_edit_groups_info_cr');
$actions[_t('Delete Group')]['functions'] = array ('shn_sn_ad_delete_groups','shn_sn_ad_delete_groups_confirm','shn_sn_ad_delete_groups_cr');
$actions[_t('Add/Delete Group Note')]['functions'] = array ('shn_sn_ad_add_group_note','shn_sn_ad_add_group_note_cr','shn_sn_ad_edit_group_note','shn_sn_ad_edit_group_note_cr','shn_sn_ad_delete_group_note','shn_sn_ad_delete_group_note_cr');

//Role admin function
$actions[_t('Role Admin Panel')]['functions'] = array ('shn_sn_ad_manage_roles','shn_sn_ad_roles_adinmenu');

//role management
$actions[_t('View Role')]['functions'] = array ('shn_sn_ad_view_roles_info');
$actions[_t('Assing/Ressing SN Roles to Users')]['functions'] = array ('shn_sn_ad_search_people_module','shn_sn_ad_search_people_module_cr','shn_sn_ad_add_roles_to_module_users','shn_sn_ad_add_roles_to_module_users_cr','shn_sn_ad_delete_roles_from_module_users','shn_sn_ad_delete_roles_from_module_users_cr','shn_sn_ad_manage_roles');
$actions[_t('Assing/Ressing Forum Roles to Users')]['functions'] = array ('shn_sn_ad_search_people_forum','shn_sn_ad_search_people_forum_cr','shn_sn_ad_add_roles_to_forum_users','shn_sn_ad_add_roles_to_forum_users_cr','shn_sn_ad_delete_roles_from_forum_users','shn_sn_ad_delete_roles_from_forum_users_cr','shn_sn_ad_manage_roles');
$actions[_t('Assing/Ressing Group Roles to Users')]['functions'] = array ('shn_sn_ad_search_people_group','shn_sn_ad_search_people_group_cr','shn_sn_ad_add_roles_to_group_users','shn_sn_ad_add_roles_to_group_users_cr','shn_sn_ad_delete_roles_from_group_users','shn_sn_ad_delete_roles_from_group_users_cr','shn_sn_ad_manage_roles');
$actions[_t('View Users Roles Request')]['functions'] = array ('shn_sn_ad_approove_req','shn_sn_ad_approove_req_cr','shn_sn_ad_manage_roles','shn_sn_ad_roles_adinmenu');

//User admin function
$actions[_t('Usre Admin Panel')]['functions'] = array ('shn_sn_ad_manage_users','shn_sn_ad_manage_users_adinmenu');
$actions[_t('View/Delete User Profile')]['functions'] = array ('shn_sn_ad_manage_users','shn_sn_ad_manage_users_adinmenu','shn_sn_ad_view_users_profile','shn_sn_ad_delete_users_profile_cr');
$actions[_t('Add Notices to Users')]['functions'] = array ('shn_sn_ad_manage_users','shn_sn_ad_manage_users_adinmenu','shn_sn_ad_add_notices_to_users','shn_sn_ad_add_notices_to_users_cr');

//Forum adin function
$actions[_t('Forum Admin Panel')]['functions'] = array ('shn_sn_ad_manage_forums','shn_sn_ad_manage_forums_adinmenu');

//forum management
$actions[_t('View Forum')]['functions'] = array ('shn_sn_ad_view_current_forums');
$actions[_t('Create Forum')]['functions'] = array ('shn_sn_ad_create_new_forums','shn_sn_ad_create_forums_cr');
$actions[_t('Edit Forum')]['functions'] = array ('shn_sn_ad_edit_forums','shn_sn_ad_edit_forum_info_confirm','shn_sn_ad_edit_forum_info_cr');
$actions[_t('Delete Forum')]['functions'] = array ('shn_sn_ad_delete_forums','shn_sn_ad_delete_forums_confirm','shn_sn_ad_delete_forums_cr');
$actions[_t('Post by Admin')]['functions'] = array ('shn_sn_ad_post_to_forum','shn_sn_ad_view_forum','shn_sn_ad_create_topic_cr','shn_sn_ad_delete_topic','shn_sn_ad_delete_topic_cr','shn_sn_ad_add_post','shn_sn_ad_add_post_cr','shn_sn_ad_delete_post','shn_sn_ad_delete_post_cr','shn_sn_ad_edit_post','shn_sn_ad_edit_post_cr');
$actions[_t('Add/Delete Forum Note')]['functions'] = array ('shn_sn_ad_add_forum_note','shn_sn_ad_add_forum_note_cr','shn_sn_ad_edit_forum_note','shn_sn_ad_edit_forum_note_cr','shn_sn_ad_delete_forum_note','shn_sn_ad_delete_forum_note_cr');

$global['module_actions']=array('sn'=>$actions);
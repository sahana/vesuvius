<?php
/** Main Controller User Interface of the Social Network
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author     Ravith Botheju <ravithb@gmail.com>
 * @author     G.W.R. Sandaruwan <sandaruwan[at]opensource[dot]lk> <rekasandaruwan[at]gmail[dot]com
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    sahana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

function _shn_sn_signup_form(){
	global $global;
	echo "<h2>"._t("Sign Up for Social Networking Module")."</h2>";
	shn_form_fopen('signup','sn',array('enctype'=>"enctype='multipart/form-data'"));
	shn_form_fsopen(_t('Account Details'));

	shn_form_text(_t('Full Name'),'full_name','');
	shn_form_text(_t('Family Name'),'family_name');
	shn_form_text(_t('User Name'),'username','');
	shn_form_password(_t('Password for Login'),'password','');
	shn_form_password(_t('Confirm Password'),'password_rep','');

	shn_form_fsclose();

	shn_form_fsopen(_t('Personal Details'));

	$radio_options = array('male'=>_t('Male'),'female'=>_t('Female'));
	shn_form_select(  $radio_options,_t('Gender'),'gender');

	shn_form_upload(_t('Picture'),'picture');
	shn_form_date(_t("Date of Birth"),'dob');
	shn_form_opt_select(_t('opt_marital_status'), 'Marital Status');
	shn_form_opt_select(_t('opt_religion'), 'Religion');
	shn_form_opt_select(_t('opt_race'), 'Race');
	shn_form_opt_select(_t('opt_country'), 'Country');

	shn_form_fsclose();

	shn_form_fsopen(_t('Medical Information'));
	shn_form_text(_('Height'),'height','');
	shn_form_text(_('Weight'),'weight','');
	shn_form_opt_select(_t('opt_blood_type'), 'Blood Group');
	shn_form_opt_select(_t('opt_eye_color'), 'Eye Color');
	shn_form_opt_select(_t('opt_skin_color'), 'Skin Color');
	shn_form_opt_select(_t('opt_hair_color'), 'Hair Color');

	shn_form_fsclose();

	shn_form_fsopen(_t('Professional Information'));

	shn_form_text(_t('Occupation'),'occupation');

	shn_form_fsclose();

	shn_form_fsopen(_t('Contact Information'));

	$db = $global['db'];
	$query = "SELECT * FROM field_options WHERE field_name='opt_contact_type'";
	$res = $db->Execute($query);

	while($row = $res->FetchRow()){
		shn_form_text($row['option_description'],'contact_'.$row['option_code']);
	}

	shn_form_fsclose();

	shn_form_fsopen(_t('Public/Private Profile'));

	shn_form_checkbox(_t('Show my profile to everyone'),'show_profile');

	shn_form_fsclose();

	shn_form_fsopen(_t('Human User Validation'));
	echo _t("Please type in the text in the image to the text box to make sure you are not a bot.");
	echo "<br/><div style=\"padding-left:220px;\"><img src=\"index.php?mod=pref&act=captcha&stream=image\" border=\"0\"/></div><br/>";
	shn_form_text(_t('Image Text'),'captcha_text');
	shn_form_fsclose();

	shn_form_submit(_t('Cancel'),"name='cancel'");
	shn_form_submit(_t('Submit'),"name='save'");
	shn_form_fclose();
}

function _shn_sn_signup_cr(){
	global $global;
	$db = &$global['db'];

	$errors = false;
	include_once $global['approot'].'inc/lib_uuid.inc';
	if($_SESSION['security_captcha_key'] !=md5(trim($_POST["captcha_text"]))){
		add_error(_t("Please provide the text in the image correctly to prove you are not a bot"));
		$errors = true;
	}else if(trim($_POST['password'])!=trim($_POST['password_rep'])){
		add_error(_t('Your passwords doesn\'t match'));
		$errors = true;
	}else{

		$p_uuid = shn_create_uuid('person');
		$sn_role_id = shn_acl_get_group_id('Social Networking User');
		$ret = shn_auth_add_user(($_POST['full_name']." ".$_POST['family_name']),$_POST['username'],$_POST['password'],$sn_role_id,$p_uuid);
		if($ret==false){
			$db->FailTrans();
		}
		$query1 = "INSERT INTO person_details (p_uuid,birth_date,opt_country,opt_race,opt_religion,opt_marital_status,opt_gender,occupation) VALUES (?,?,?,?,?,?,?,?)";
		$db->Execute($query1,array($p_uuid,$_POST['dob'],$_POST['opt_country'],$_POST['opt_race'],$_POST['opt_religion'],$_POST['opt_marital_status'],$_POST['gender'],$_POST['occupation']));

		$query2 = "INSERT INTO person_physical (p_uuid,opt_blood_type,height,weight,opt_eye_color,opt_skin_color,opt_hair_color) VALUES (?,?,?,?,?,?,?)";
		$db->Execute($query2,array($p_uuid,$_POST['opt_blood_type'],$_POST['height'],$_POST['weight'],$_POST['opt_eye_color'],$_POST['opt_skin_color'],$_POST['opt_hair_color']));

		$query4 = "SELECT * FROM field_options WHERE field_name='opt_contact_type'";
		$res4 = $db->Execute($query4);

		while($row = $res4->FetchRow()){
			$query5 = "INSERT INTO contact (pgoc_uuid,opt_contact_type,contact_value) VALUES (?,?,?)";
			$db->Execute($query5,array($p_uuid,$row['option_code'],$_POST['contact_'.$row['option_code']]));
		}

		if(isset($_POST['show_profile'])){
			$query6 = "INSERT INTO sn_public_profile (p_uuid,public_profile) VALUES (?,?)";
			$db->Execute($query6,array($p_uuid,1));
		}else{
			$query6 = "INSERT INTO sn_public_profile (p_uuid,public_profile) VALUES (?,?)";
			$db->Execute($query6,array($p_uuid,0));
		}

		include_once $global['approot'].'inc/lib_image.inc';
		if($_FILES['picture']['error']!=null && $_FILES['picture']['error']!=UPLOAD_ERR_NO_FILE){
			// errors in image upload
			$db->FailTrans();
			add_error(shn_file_upload_error_msg($_FILES['picture']['error']));

		}else{
			shn_image_to_db($_FILES['picture'],$p_uuid);
		}

		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();
		if(!$failed){
			add_confirmation(_t('Sign up successful.'));

		}else{
			_shn_sn_signup_form();
		}
		return;
	}
	if($errors == true){
		_shn_sn_signup_form();
	}
}

function _shn_sn_add_interest_form($interests=null){
	echo "<h2>"._t("New Interest")."</h2>";

	shn_form_fopen('add_interest','sn',array('req_message'=>false));
	shn_form_fsopen(_t('Search Interests'));
	shn_form_text(_t('Search Text'),'search_text','');
	shn_form_submit(_t('Search'),' name="search" ');
	shn_form_fsclose();
	shn_form_fclose();
	if(isset($interests)){
		shn_form_fopen('add_interest','sn',array('req_message'=>false));
		shn_form_fsopen(_t('Search Result'));
		if(count($interests)>0){
			echo "<hr/>";
		}else{
			echo _t("No matching interest found. Please feel free to add one");
		}
		foreach($interests as $intr){
			echo "<h5>".$intr['interest']."</h5>";
			echo "<p>".$intr['description']."</p>";
			shn_form_hidden(array('interest_id'=>$intr['interest_id']));
			shn_form_submit(_t('Add Interest'), ' name="add_intr" ');
			echo "<hr/>";
		}
		shn_form_fsclose();
		shn_form_fclose();
	}

	shn_form_fopen('add_interest','sn');
	shn_form_fsopen(_t('Add Interest'));
	shn_form_text(_t('Display Text'),'display_text','',array('req'=>true));
	shn_form_textarea(_t('Short Description'),'description');
	shn_form_fsclose();
	shn_form_submit(_t('Cancel'),' name="cancel" ');
	shn_form_submit(_t('Save'),' name="save" ');
	shn_form_fclose();
}

function _shn_sn_add_interest_cr(){
	global $global;
	$db=$global['db'];
	//$db->debug=true;
	if(isset($_POST['save'])){
		$text = $_POST['display_text'];
		$description = $_POST['description'];
		$user_id = $_SESSION['user_id'];

		if(strlen(trim($text))==0){
			add_error(_t('Pleae enter the display text.'));
			_shn_sn_add_interest_form();
			return;
		}

		$db->StartTrans();
		$interest_id = $db->GenID('sn_interest_seq');
		$query1 = "INSERT INTO sn_interests (interest_id,interest,description) VALUES(?,?,?)";
		$db->Execute($query1,array($interest_id,$text,$description));

		$query2 = "INSERT INTO sn_user_interest(interest_id,p_uuid) VALUES(?,?)";
		$db->Execute($query2,array($interest_id,$user_id));
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();

		if($failed){
			add_error(_t('An unknown error occured while saving data'));
			return;
		}else{
			add_confirmation(_t("Your interest has been added successfully."));
			shn_sn_default();
			return;
		}
	}else if(isset($_POST['search'])){
		$query3 = "SELECT * FROM sn_interests si JOIN sn_user_interest sui ON si.interest_id=sui.interest_id  AND sui.p_uuid!=? WHERE si.interest LIKE ? OR si.description LIKE ?";
		$res3 = $db->Execute($query3,array($_SESSION['user_id'],'%'.$_POST['search_text'].'%','%'.$_POST['search_text'].'%'));
		_shn_sn_add_interest_form($res3->GetAssoc());
	}else if(isset($_POST['add_intr'])){
		$user_id = $_SESSION['user_id'];
		$interest_id = $_POST['interest_id'];
		if(isset($interest_id)){
			$db->StartTrans();

			$query2 = "INSERT INTO sn_user_interest(interest_id,p_uuid) VALUES(?,?)";
			$db->Execute($query2,array($interest_id,$user_id));
			$failed = $db->HasFailedTrans();
			$db->CompleteTrans();

			if($failed){
				add_error(_t('An unknown error occured while saving data'));
				return;
			}else{
				add_confirmation(_t("Your interest has been saved successfully."));
				shn_sn_default();
				return;
			}
		}
	}
}

function _shn_sn_find_people_with_interest(){
	global $global;
	$db = $global['db'];
	$query = "SELECT interest,description FROM sn_interest WHERE interest_id=?";
	$res = $db->Execute($query,array($_REQUEST['interest_id']));
	echo "<h4>".$res->fields['interest']."</h4>";
	echo "<p>".$res->fields['description']."</p>";
	echo "<hr/>";
	echo "<h5>"._t("People with similar interest.")."</h5>";
	_shn_sn_search_people_cr(array('by_interest'=>true,'interest_id'=>$_REQUEST['interest_id']));
}

function _shn_sn_get_user_interests(){
	global $global;
	$db = $global['db'];

	$query = "SELECT si.interest_id,si.interest FROM sn_user_interest sui JOIN sn_interests si ON si.interest_id=sui.interest_id AND sui.p_uuid=? ";
	$res = $db->Execute($query,array($_SESSION['user_id']));
	return $res->GetAssoc();
}

function _shn_sn_friends_page(){
	global $global;
	$db = $global['db'];
	//$db->debug = true;
	echo "<h2>"._t("Sahana Social Networking :: My Friends")."</h2>";
	shn_tabmenu_open();
	shn_tabmenu_item('friends',_t('My Friends'));
	shn_tabmenu_item('search_people',_t('Find A Friend'));
	shn_tabmenu_close();
	echo "<br/><hr/>";
	$count = $db->Execute("SELECT COUNT(*) FROM sn_friends sf LEFT OUTER JOIN person_uuid pu ON sf.p_uuid = pu.p_uuid LEFT OUTER JOIN person_details pd ON pd.p_uuid = pu.p_uuid WHERE sf.friend_p_uuid = ?",array($_SESSION['user_id']));
	$count = $count->fields['c'];
	$query = "SELECT pd.*,pu.* FROM sn_friends sf LEFT OUTER JOIN person_uuid pu ON sf.p_uuid = pu.p_uuid LEFT OUTER JOIN person_details pd ON pd.p_uuid = pu.p_uuid WHERE sf.friend_p_uuid =?";
	$rpp = 5;
	$page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
	$res = $db->SelectLimit($query,$rpp,$rpp*($page-1),array($_SESSION['user_id']));
	if($res->RecordCount()==0){
		echo "<div><em>"._t("Currenty you don't have any friens. Try the Friend Finder in the above menu.")."</em></div><hr/>";
	}
	while($row = $res->FetchRow()){
		echo "<div>";
		echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$row['p_uuid']."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' width='200' height='150'/>";
		echo "<br/>";
		echo "<em>".$row['full_name']." ".$row['family_name']."</em>";
		echo "<br/><br/><span>";
		shn_acl_secure_hyperlink('sn','view_profile',_t('View Full Profile'),'',array('p_uuid'=>$row['p_uuid']));
		echo "</span></div><hr/>";
	}
	if($count > 0){
		echo "<span>"._t("Page : ");
		for($i=1;$i<=(($count%$rpp)==0?($count/$rpp):(($count/$rpp)+1));$i++){
			shn_acl_secure_hyperlink('sn','friends',$i,'',array('page'=>$i));
			echo "&nbsp;&nbsp;";
		}
		echo "</span>";
	}
}

function _shn_sn_search_people_page(){

	$full_name = $_REQUEST['full_name'];

	shn_form_fopen('search_people','sn',array('req_message'=>false));
	shn_form_fsopen();
	shn_form_text(_t('Name'),'person_name','',array('value'=>$full_name));
	shn_form_fsclose();
	shn_form_submit(_t("Search"),' name="search" ');
	shn_form_fclose();
}

function _shn_sn_search_people_cr($params=array()){
	global $global;
	include_once($global['approot'].'inc/lib_image.inc');
	$db = $global['db'];
	$res = null;
	$rpp = 5;
	$page = 1;
	$name = '';
	if(count($params)>0){
		if(isset($parms['by_interest'])){
			$interest_id = $params['interest_id'];
			$count = $db->Execute("SELECT COUNT(*) as c FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid JOIN sn_user_interest sui ON sui.p_uuid=pd.p_uuid WHERE sui.interest_id=?",array($interest_id));
			$count = $count->fields['c'];
			$query = "SELECT pu.*,pd.*,sf.p_uuid AS sf_p_uuid FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid JOIN sn_user_interest sui ON sui.p_uuid=pd.p_uuid WHERE sui.intereest_id=? ";

			$page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
			$res = $db->SelectLimit($query,$rpp,$rpp*($page-1),array($interest_id));
			if($res->RecordCount()==0){
				echo "<div><em>"._t("No records found.")."</em></div><hr/>";
			}
		}
	}else{
		//$db->debug = true;
		_shn_sn_search_people_page();
		echo "<br/><hr/>";
		$name = $_POST['person_name'];
		$count = $db->Execute("SELECT COUNT(*) as c FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid LEFT OUTER JOIN sn_friends sf ON sf.p_uuid=pd.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%')");
		$count = $count->fields['c'];
		$query = "SELECT pu.*,pd.*,sf.p_uuid AS sf_p_uuid FROM person_uuid pu JOIN person_details pd ON pd.p_uuid=pu.p_uuid LEFT OUTER JOIN sn_friends sf ON sf.p_uuid=pd.p_uuid WHERE (full_name LIKE '%".$name."%' OR family_name LIKE '%".$name."%') ";
		$page = isset($_REQUEST['page'])?$_REQUEST['page']:1;
		$res = $db->SelectLimit($query,$rpp,$rpp*($page-1));
		if($res->RecordCount()==0){
			echo "<div><em>"._t("No records found.")."</em></div><hr/>";
		}
	}
	while($res && $row = $res->FetchRow()){
		if(isset($_SESSION['user_id']) && $_SESSION['user_id']!=$row['p_uuid']){
			echo "<div>";
			echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$row['p_uuid']."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' widhth='200' height='150'/>";
			echo "<br/>";
			echo "<em>".$row['full_name']."</em>&nbsp;&nbsp;&nbsp;&nbsp;";
			shn_acl_secure_hyperlink('sn','view_profile','View Profile',null,array('p_uuid'=>$row['p_uuid'],'s_person_name'=>$name,'s_page'=>$page,'s_act'=>'search_people'),'');
			echo "<br/><br/>";
			if($row['sf_p_uuid']==NULL){
				shn_form_fopen('add_as_friend','sn',array('req_message'=>false));
				shn_form_hidden(array('target_p_uuid'=>$row['p_uuid'],'full_name'=>$row['full_name'],'family_name'=>$row['family_name']));
				shn_form_submit(_t('Add as Friend'));
				shn_form_fclose();
			}else{
				printf(_t("You are already a friend of %s"),$row['full_name']);
			}
			echo "</div><hr/>";
		}
	}
	if($count > 0){
		echo "<span>"._t("Page : ");
		for($i=1;$i<=(($count%$rpp)==0?($count/$rpp):(($count/$rpp)+1));$i++){
			shn_acl_secure_hyperlink('sn','search_people',$i,'',array('page'=>$i,'person_name'=>$name,'search'=>'search'));
			echo "&nbsp;&nbsp;";
		}
		echo "</span>";
	}

}

function _shn_sn_add_as_friend(){
	global $global;
	$db = $global['db'];

	if(isset($_SESSION['user_id'])){
		$friend_p_uuid = $_POST['target_p_uuid'];
		$p_uuid = $_SESSION['user_id'];

		$db->StartTrans();
		$query = $db->Prepare("INSERT INTO sn_friends (p_uuid,friend_p_uuid) VALUES (?,?)");
		$db->Execute($query,array($p_uuid,$friend_p_uuid));
		$db->Execute($query,array($friend_p_uuid,$p_uuid));
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();

		if($failed){
			add_error(_t('An unknown error occured while adding friend.'));
		}else{
			add_confirmation(_t(sprintf('You are now freinds with %s.',($_POST['full_name'].' '.$_POST['family_name']))));
		}
	}

}

function _shn_sn_mailbox_page(){
	global $global;
	$db = $global['db'];
	echo "<h2>"._t("Sahana Social Networking :: Mailbox")."</h2>";
	shn_acl_secure_hyperlink('sn','mailbox',_t('Compose'),'',array('sact'=>'compose'));
	echo "<br/>";
	echo "<br/>";
	$inbox_count = _shn_sn_get_unread_message_count();
	shn_tabmenu_open();
	shn_tabmenu_item('mailbox',sprintf(_t('Inbox (%d)'),$inbox_count),'sn',array('query_string'=>'folder=inbox&sact=open'));
	shn_tabmenu_item('mailbox',_t('Outbox'),'sn',array('query_string'=>'folder=outbox&sact=open'));
	shn_tabmenu_item('mailbox',_t('Bin'),'sn',array('query_string'=>'folder=bin&sact=open'));
	shn_tabmenu_close();

	echo "<div>";
	if(isset($_REQUEST['folder'])){
		switch(strtolower($_REQUEST['folder'])){
			case 'inbox':
				_shn_sn_mail_inbox();
				break;
			case 'outbox':
				_shn_sn_mail_outbox();
				break;
			case 'bin':
				_shn_sn_mail_bin();
				break;
		}
	}else if(strtolower($_REQUEST['sact'])=='compose'){
		_shn_sn_mail_compose();
	}else if(strtolower($_POST['sact'])=='send'){
		_shn_sn_mail_send();
	}else if(strtolower($_REQUEST['sact'])=='view'){
		_shn_sn_mail_view();
	}else if(strtolower($_POST['sact'])=='delete'){
		_shn_sn_mail_delete();
	}else{
		// go to inbox by default
		_shn_sn_mail_inbox();
	}

	echo "</div>";

}

function _shn_sn_mail_inbox(){
	global $global;
	$db = $global['db'];
	echo "<h4>"._t("Inbox")."</h4>";
	$page = isset($_POST['page'])?$_POST['page']:1;
	$rpp = 1;
	$query = "SELECT * FROM sn_messages JOIN person_uuid ON p_uuid=from_p_uuid WHERE to_p_uuid = ? AND status IN ('UNREAD','READ') ORDER BY date DESC";
	$res = $db->SelectLimit($query,$rpp,$rpp*($page-1),array($_SESSION['user_id']));
	if($res->RecordCount()>0){
		shn_form_fopen('mailbox','sn',array('req_message'=>false));
		shn_form_hidden(array('bin'=>'true'));
		shn_form_submit(_t('Delete'),'name=sact');
		shn_form_fsopen(_t('Inbox'));
		echo "<table>";
		echo "<tr><th>&nbsp;</th><th>"._t("From")."</th><th>"._t("Subject")."</th><th>"._t("Date")."</th></tr>";
		while($row = $res->FetchRow()){
			$hyperlink = shn_acl_secure_hyperlink('sn','mailbox',$row['full_name'],null,array('sact'=>'view','msgid'=>$row['message_id'],'page'=>$page),'',true);
			echo "<tr><td>";
			shn_form_checkbox('','msgid[]','',array('value'=>$row['message_id']));
			echo "</td>";
			echo "<td><a href='".$hyperlink."'>".$row['full_name']."</a></td>";
			echo "<td><a href='".$hyperlink."'>".$row['subject']."</a></td>";
			echo "<td><a href='".$hyperlink."'>".$row['date']."</a></td>";
			echo "</tr>";
		}
		echo "</table>";
		shn_form_fsclose();
		shn_form_submit(_t('Delete'),'name=sact');
		shn_form_fclose();

		$count_query = "SELECT COUNT(*) AS c FROM sn_messages WHERE to_p_uuid = ? AND status='UNREAD'";
		$tres =  $db->Execute($count_query,array($_SESSION['user_id']));
		$no_of_pages = $tres->fields['c'];
		$no_of_pages = (($no_of_pages%$rpp)==0)?$no_of_pages:($no_of_pages+1);
		if($no_of_pages>1){
			echo "<div><span>"._t('Page')."</span>";
			for($i=1;$i<$no_of_pages;$i++){
				shn_acl_secure_hyperlink('sn','mailbox',$i,null,array('folder'=>'inbox','sact'=>'open','page'=>"$i"));
				echo "&npsp;&nbsp;";
			}
			echo "</div>";
		}
	}else{
		echo "<p>".sprintf(_t("No messages in your %s."),_t('inbox'))."</p>";
	}
}
function _shn_sn_mail_outbox(){
	global $global;
	$db = $global['db'];
	echo "<h4>"._t("Outbox")."</h4>";
	$query = "SELECT * FROM sn_messages WHERE from_p_uuid = ? ORDER BY date";
	$res = $db->Execute($query,array($_SESSION['user_id']));
	if($res->RecordCount()>0){
		echo "<table>";
		echo "<tr><th>&nbsp;</th><th>"._t("Subject")."</th><th>"._t("Date")."</th></tr>";
		while($row = $res->FetchRow()){
			echo "<tr><td>&nbsp;</td>";
			echo "<td>".$row['subject']."</td>";
			echo "<td>".$row['date']."</td>";
			echo "</tr>";
		}
		echo "</table>";
	}else{
		echo "<p>".sprintf(_t("No messages in your %s."),_t('outbox'))."</p>";
	}
}
function _shn_sn_mail_bin(){
	global $global;
	$db = $global['db'];
	echo "<h4>"._t("Bin")."</h4>";
	$query = "SELECT * FROM sn_messages JOIN person_uuid ON p_uuid=from_p_uuid WHERE to_p_uuid = ? AND status!='DELETED' ORDER BY date DESC";
	$res = $db->Execute($query,array($_SESSION['user_id']));
	if($res->RecordCount()>0){
		shn_form_fopen('mailbox','sn',array('req_message'=>false));
		shn_form_hidden(array('confirm'=>'true'));
		shn_form_submit(_t('Delete'),'name=sact');
		shn_form_fsopen(_t('Bin'));
		echo "<table>";
		echo "<tr><th>&nbsp;</th><th>"._t("From")."</th><th>"._t("Subject")."</th><th>"._t("Date")."</th></tr>";
		while($row = $res->FetchRow()){
			echo "<tr><td>";
			shn_form_checkbox('','msgid[]','',array('value'=>$row['message_id']));
			echo "</td>";
			echo "<td>".$row['full_name']."</td>";
			echo "<td>".$row['subject']."</td>";
			echo "<td>".$row['date']."</td>";
			echo "</tr>";
		}
		echo "</table>";
		shn_form_fsclose();
		shn_form_submit(_t('Delete'),'name=sact');
		shn_form_fclose();
	}else{
		echo "<p>".sprintf(_t("No messages in your %s."),_t('bin'))."</p>";
	}
}
function _shn_sn_mail_compose(){
	global $global;
	$db = $global['db'];
	shn_form_fopen('mailbox','sn',array('req_message'=>false));
	shn_form_hidden(array('sact'=>'send'));
	shn_form_fsopen(_t("New Message"));

	$res = $db->Execute("SELECT sf.friend_p_uuid,pu.full_name FROM sn_friends sf JOIN person_uuid pu ON sf.friend_p_uuid=pu.p_uuid WHERE sf.p_uuid=?",array($_SESSION['user_id']));

	if($res){
		$opts = $res->GetAssoc();
	}
	shn_form_select($opts,_t('Recepients'),'recepients[]','size="5" multiple="multiple"',array('req'=>true));


	shn_form_text(_t('Subject'),'subject','size="80"',array('req'=>false,));
	shn_form_wysiwyg(_t('Message'),'message',array('tool_bar'=>"Basic"));
	shn_form_fsclose();
	shn_form_submit(_t('Send'),' name="send" ');
	shn_form_fclose();
}
function _shn_sn_mail_send(){
	global $global;
	$db = $global['db'];
	if(isset($_POST['recepients'])==false){
		add_error(_t('Please select atleast one recepient.'));
		_shn_sn_mail_compose();
		return;
	}else{
		//$db->debug = true;
		$db->StartTrans();
		$query = $db->Prepare("INSERT INTO sn_messages(from_p_uuid,to_p_uuid,subject,message,date,status,folder) VALUES(?,?,?,?,?,?,?)");

		foreach($_POST['recepients'] as $r){
			$date = date('Y-m-d H:i:s');
			$from = $_SESSION['user_id'];
			$db->Execute($query,array($from,$r,$_POST['subject'],$_POST['message'],$date,'UNREAD','Inbox'));
		}
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();
		if($failed){
			add_error(_t("An unknown error occured while sending your mail(s)."));
		}else{
			add_confirmation(_t("Your mail was sent successfully."));
		}
	}
}

function _shn_sn_mail_view(){
	global $global;
	$db = $global['db'];
	//$db->debug = true;
	$message_id = $_REQUEST['msgid'];
	$return_page = $_REQUEST['page'];
	shn_form_fopen('mailbox','sn',array('req_message'=>false));
	shn_form_hidden(array('msgid'=>$message_id,'bin'=>'true'));
	shn_form_submit(_t('Delete'),' name="delete" ');
	shn_form_fsopen(_t('Message'));
	$query  = "SELECT sm.*,frm_p.full_name AS msg_from FROM sn_messages sm JOIN person_uuid frm_p ON sm.from_p_uuid=frm_p.p_uuid
                    WHERE sm.message_id=? AND sm.to_p_uuid=?";
	$res = $db->Execute($query,array($message_id,$_SESSION['user_id']));
	//var_dump($res->fields);
	$fields = $res->fields;
	shn_form_label(_t("From :"),null,array('br'=>'false'));
	echo $fields['msg_from']."<br/>";
	shn_form_label(_t("Subject :"),null,array('br'=>'false'));
	echo $fields['subject']."</br>";
	shn_form_label(_t("Date :"),null,array('br'=>'false'));
	echo $fields['date']."</br>";
	shn_form_label(_t('Message :'),null,array('br'=>'false'));
	echo $fields['message']."<br/>";
	echo "<br/>";
	shn_acl_secure_hyperlink('sn','mailbox',_t('<< Back To Inbox'),null,array('folder'=>'inbox','mact'=>'open','page'=>$return_page));

	$query2 = "UPDATE sn_messages SET status='READ' WHERE message_id=? AND to_p_uuid=?";
	$db->Execute($query2,array($message_id,$_SESSION['user_id']));
	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_sn_mail_delete(){
	global $global;
	$db = $global['db'];
	//$db->debug = true;
	if(isset($_POST['confirm'])){
		// delete messages permanently
		$db->StartTrans();
		$message_id = $_POST['msgid'];
		$query = "UPDATE sn_messages SET folder='Bin' ,status='DELETED' WHERE message_id=? AND to_p_uuid=?";
		if(is_array($message_id)){
			foreach ($message_id as $msg_id){
				$db->Execute($query,array($msg_id,$_SESSION['user_id']));
			}
		}else{
			$db->Execute($query,array($message_id,$_SESSION['user_id']));
		}
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();
		if($failed){
			add_error(_t("An unknown error occured while deleting messages"));
		}else{
			add_confirmation(_t("Message deleted."));
		}
	}else if(isset($_POST['bin'])){
		//move messages to bin
		$db->StartTrans();
		$message_id = $_POST['msgid'];
		$query = "UPDATE sn_messages SET folder='Bin' WHERE message_id=? AND to_p_uuid=?";
		if(is_array($message_id)){
			foreach ($message_id as $msg_id){
				$db->Execute($query,array($msg_id,$_SESSION['user_id']));
			}
		}else{
			$db->Execute($query,array($message_id,$_SESSION['user_id']));
		}
		$failed = $db->HasFailedTrans();
		$db->CompleteTrans();
		if($failed){
			add_error(_t("An unknown error occured while deleting messages"));
		}else{
			add_confirmation(_t("Message deleted."));
		}
	}
}

function _shn_sn_view_profile($tp_uuid=null){
	global $global;
	$db = $global['db'];

	$show_full_profile = false;
	if($tp_uuid==null && isset($_REQUEST['p_uuid'])==true){
		$tp_uuid = $_REQUEST['p_uuid'];
	}

	$profile_query = "SELECT public_profile FROM sn_public_profile WHERE p_uuid=?";
	$p_uuid = (isset($tp_uuid))?$tp_uuid:$_SESSION["user_id"];
	$profile_res = $db->GetCol($profile_query,array($p_uuid));
	if($p_uuid==$_SESSION['user_id']){
		// show the full profile of the user to himself
		$show_full_profile = true;
	}else{
		// chck if the profile is of a friend of the current user.
		$friend_query = "SELECT COUNT(*) AS c FROM sn_friends WHERE p_uuid=? AND friend_p_uuid=?";
		$friend_res = $db->GetCol($friend_query,array($_SESSION['user_id'],$p_uuid));
		if($friend_res[0]>0){
			$show_full_profile = true;
		}else{
			$show_full_profile = ($profile_res->fields['public_profile']==true);
		}
	}

	shn_form_fopen('','sn',array('req_message'=>false));
	shn_form_fsopen(_t('Account Details'));


	$query1 = "SELECT
                   pu.full_name,
                   pu.family_name,
                   u.user_name,
                   pd.opt_gender,
                   pd.birth_date,
                   pd.opt_marital_status,
                   pd.opt_religion,
                   pd.opt_race,pd.opt_country,
                   pd.occupation,
                   pp.height,
                   pp.weight,
                   pp.opt_blood_type,
                   pp.opt_eye_color,
                   pp.opt_skin_color,
                   pp.opt_hair_color
               FROM person_uuid pu 
               JOIN users u ON pu.p_uuid=u.p_uuid 
               JOIN person_details pd ON pd.p_uuid=u.p_uuid 
               JOIN person_physical pp ON pp.p_uuid=u.p_uuid
               WHERE u.p_uuid=?";
	$res1 = $db->Execute($query1,array($p_uuid));
	$full_name = $res1->fields["full_name"];

	shn_form_label(_('Full Name :'),$full_name);

	$user_name = $res1->fields["user_name"];

	shn_form_label(_('User Name :'),$user_name);
	shn_form_label(_('Password :'),'********');
	//shn_acl_secure_hyperlink('pref','ch_passwd','Change Password',$stream=null,$params=array(),$text_opts='');
	shn_form_fsclose();

	shn_form_fsopen(_t('Personal Details'));

	echo "Profile Image : ";
	echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$tp_uuid."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' width='150' height='125'/>";
	echo "<br><br>";

	$query3 = "SELECT opt_gender,birth_date,opt_marital_status,opt_religion,opt_race,opt_country,occupation FROM person_details WHERE p_uuid=?";
	$res3 = $db->Execute($query3,array($_SESSION["user_id"]));
	$gender = $res1->fields["opt_gender"];
	$dob = $res1->fields["birth_date"];
	$marital_status = $res1->fields["opt_marital_status"];
	$religion = $res1->fields["opt_religion"];
	$race = $res1->fields["opt_race"];
	$country = $res1->fields["opt_country"];
	$occupation = $res1->fields["occupation"];

	shn_form_label(_('Gender :'),$gender);
	shn_form_label(_('Date of Birth :'),$dob);

	if($show_full_profile){
		if($marital_status=="unk"){

			shn_form_label(_('Marital Status :'),"Unknown");
		}
		else if($marital_status=="sin"){

			shn_form_label(_('Marital Status :'),"Single");
		}
		else if($marital_status=="mar"){

			shn_form_label(_('Marital Status :'),"Married");
		}
		else if($marital_status=="div"){

			shn_form_label(_('Marital Status :'),"Divorced");
		}

		if($religion){
			shn_form_label(_('Religion :'),_shn_sn_get_option_description($religion));
		}

		if($race){
			shn_form_label(_('Race :'),_shn_sn_get_option_description($race));
		}

		if($country){
			shn_form_label(_('Country :'),_shn_sn_get_option_description($country));
		}

		shn_form_fsclose();

		shn_form_fsopen(_t('Medical Information'));

		//$query7 = "SELECT height,weight,opt_blood_type,opt_eye_color,opt_skin_color,opt_hair_color FROM person_physical WHERE p_uuid=?";
		//$res7 = $db->Execute($query7,array($_SESSION["user_id"]));
		$height = $res1->fields["height"];
		$weight = $res1->fields["weight"];
		$blood_type = $res1->fields["opt_blood_type"];
		$eye_color = $res1->fields["opt_eye_color"];
		$skin_color = $res1->fields["opt_skin_color"];
		$hair_color = $res1->fields["opt_hair_color"];

		shn_form_label(_('Height :'),$height);
		shn_form_label(_('Weight :'),$weight);

		if($blood_type){
			shn_form_label(_t('Blood Group :'),_shn_sn_get_option_description($blood_type));
		}

		if($eye_color){
			shn_form_label(_t('Skin Color :'),_shn_sn_get_option_description($eye_color));
		}

		if($skin_color){
			shn_form_label(_t('Eye Color :'),_shn_sn_get_option_description($skin_color));
		}

		if($hair_color){
			shn_form_label(_t('Hair Color :'),_shn_sn_get_option_description($hair_color));
		}

		shn_form_fsclose();

		shn_form_fsopen(_t('Professional Information'));
		shn_form_label(_t('Occupation :'),$occupation);

		shn_form_fsclose();

		shn_form_fsopen(_t('Contact Information'));

		$db = $global['db'];
		$query11 = "SELECT fo.option_description,c.contact_value FROM field_options fo JOIN contact c ON fo.option_code=c.opt_contact_type WHERE fo.field_name='opt_contact_type' AND c.pgoc_uuid=";
		$res11 = $db->Execute($query11,array($_SESSION["user_id"]));

		while($row = $res11->FetchRow()){

			shn_form_label(_t($row['option_description'].':'),$row['contact_value']);
		}

		shn_form_fsclose();

		shn_form_fsopen(_t('Public/Private Profile'));

		$query12 = "SELECT public_profile FROM sn_public_profile WHERE p_uuid=?";
		$res12 = $db->Execute($query12,array($_SESSION["user_id"]));
		$public_profile_description = $res12->fields["public_profile"];

		if($public_profile_description=="1"){
			shn_form_label(_('Profile Visibility :'),'Show my profile to everyone');
		}
		else if($public_profile_description=="0"){
			shn_form_label(_('Profile Visibility :'),'Show my profile to my friends only');
		}

		shn_form_fsclose();
		shn_form_fclose();
		if(isset($_REQUEST['s_act']) && $_REQUEST['s_act']=='search_people'){
			shn_form_fopen('search_people','sn',array("req_message"=>false));
			shn_form_hidden(array('page'=>$_REQUEST['s_page'],'person_name'=>$_REQUEST['s_person_name'],'search'=>'true'));
			shn_form_submit(_t('<< Back'));
			shn_form_fclose();
		}
	}
}

function _shn_sn_edit_my_prof(){
	global $global;
	$db = $global['db'];

	shn_form_fopen('','sn',array('req_massege'=>false));
	shn_form_fsopen(_t('Account Details'));

	$query1 = "SELECT full_name,family_name FROM person_uuid WHERE p_uuid=?";
	$res1 = $db->Execute($query1,array($_SESSION["user_id"]));
	$full_name = $res1->fields["full_name"];

	echo "<table border=0>";
	echo "<tr><td>";
	shn_form_label(_('Full Name :'),$full_name);
	echo "</td><td>";
	shn_acl_secure_hyperlink('sn','change_name',_t('Change Name'),$stream=null,$params=array(),$text_opts='');
	echo "</td></tr>";

	$query2 = "SELECT user_name FROM users WHERE p_uuid=?";
	$res2 = $db->Execute($query2,array($_SESSION["user_id"]));
	$user_name = $res2->fields["user_name"];

	echo "<tr><td>";
	shn_form_label(_('User Name :'),$user_name);
	echo "</td><td>";
	echo "can't change user name";
	echo "</td></tr>";

	echo "<tr><td>";
	shn_form_label(_('Password :'),'********');
	echo "</td><td>";
	shn_acl_secure_hyperlink('pref','ch_passwd',_t('Change Password'),$stream=null,$params=array(),$text_opts='');
	echo "</td></tr>";
	echo "</table>";
	shn_form_fsclose();

	shn_form_fsopen(_t('Personal Details'));

	echo "Profile Image : ";
	echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$_SESSION["user_id"]."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' width='150' height='125'/>";
	echo "<br><br>";

	$query3 = "SELECT opt_gender,birth_date,opt_marital_status,opt_religion,opt_race,opt_country,occupation FROM person_details WHERE p_uuid=?";
	$res3 = $db->Execute($query3,array($_SESSION["user_id"]));
	$gender = $res3->fields["opt_gender"];
	$dob = $res3->fields["birth_date"];
	$marital_status = $res3->fields["opt_marital_status"];
	$religion = $res3->fields["opt_religion"];
	$race = $res3->fields["opt_race"];
	$country = $res3->fields["opt_country"];
	$occupation = $res3->fields["occupation"];

	shn_form_label(_('Gender :'),$gender);
	shn_form_label(_('Date of Birth :'),$dob);

	if($marital_status=="unk"){

		shn_form_label(_t('Marital Status :'),"Unknown");
	}
	else if($marital_status=="sin"){

		shn_form_label(_t('Marital Status :'),"Single");
	}
	else if($marital_status=="mar"){

		shn_form_label(_t('Marital Status :'),"Married");
	}
	else if($marital_status=="div"){

		shn_form_label(_t('Marital Status :'),"Divorced");
	}

	if($religion){

		$query4 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res4 = $db->Execute($query4,array($religion));
		$gender_description = $res4->fields["option_description"];

		shn_form_label(_t('Religion :'),$gender_description);
	}

	if($race){

		$query5 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res5 = $db->Execute($query5,array($race));
		$race_description = $res5->fields["option_description"];

		shn_form_label(_t('Race :'),$race_description);
	}

	if($country){

		$query6 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res6 = $db->Execute($query6,array($country));
		$country_description = $res6->fields["option_description"];

		shn_form_label(_t('Country :'),$country_description);
	}

	echo "<br>";
	shn_acl_secure_hyperlink('sn','change_personal_details',_t('Change Personal Details'),$stream=null,$params=array(),$text_opts='');

	shn_form_fsclose();

	shn_form_fsclose();

    shn_form_fsopen(_t('Professional Information'));
    shn_form_label(_('Occupation :'),$occupation);

    shn_form_fsclose();
    
	shn_form_fsopen(_t('Medical Information'));

	$query7 = "SELECT height,weight,opt_blood_type,opt_eye_color,opt_skin_color,opt_hair_color FROM person_physical WHERE p_uuid=?";
	$res7 = $db->Execute($query7,array($_SESSION["user_id"]));
	$height = $res7->fields["height"];
	$weight = $res7->fields["weight"];
	$blood_type = $res7->fields["opt_blood_type"];
	$eye_color = $res7->fields["opt_eye_color"];
	$skin_color = $res7->fields["opt_skin_color"];
	$hair_color = $res7->fields["opt_hair_color"];

	shn_form_label(_('Height :'),$height);
	shn_form_label(_('Weight :'),$weight);

	if($blood_type){

		$query8 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res8 = $db->Execute($query8,array($blood_type));
		$blood_type_description = $res8->fields["option_description"];

		shn_form_label(_('Blood Group :'),$blood_type_description);
	}

	if($eye_color){

		$query8 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res8 = $db->Execute($query8,array($eye_color));
		$eye_color_description = $res8->fields["option_description"];

		shn_form_label(_('Skin Color :'),$eye_color_description);
	}

	if($skin_color){

		$query9 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res9 = $db->Execute($query9,array($skin_color));
		$skin_color_description = $res9->fields["option_description"];

		shn_form_label(_('Eye Color :'),$skin_color_description);
	}

	if($hair_color){

		$query10 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res10 = $db->Execute($query10,array($hair_color));
		$hair_color_description = $res10->fields["option_description"];

		shn_form_label(_('Hair Color :'),$hair_color_description);
	}
	echo "<br>";
	shn_acl_secure_hyperlink('sn','change_medical_information',_t('Change Medical Information'),$stream=null,$params=array(),$text_opts='');

	shn_form_fsopen(_t('Contact Information'));

	$query11 = "SELECT * FROM (SELECT option_code,option_description FROM field_options fo WHERE fo.field_name='opt_contact_type' ) opts LEFT OUTER JOIN (SELECT * FROM contact WHERE pgoc_uuid=? ) ctct ON ctct.opt_contact_type = opts.option_code";
	$res11 = $db->Execute($query11,array($_SESSION["user_id"]));

	while($row = $res11->FetchRow()){

		shn_form_label(_t($row['option_description'].':'),$row['contact_value']);
	}

	echo "<br>";
	shn_acl_secure_hyperlink('sn','change_contact_information','Change Contact Information',$stream=null,$params=array(),$text_opts='');
	shn_form_fsclose();

	shn_form_fsopen(_t('Public/Private Profile'));

	$query12 = "SELECT public_profile FROM sn_public_profile WHERE p_uuid=?";
	$res12 = $db->Execute($query12,array($_SESSION["user_id"]));
	$public_profile_description = $res12->fields["public_profile"];

	if($public_profile_description=="1"){
		shn_form_label(_('Profile Visibility :'),'Show my profile to everyone');
	}
	else if($public_profile_description=="0"){
		shn_form_label(_('Profile Visibility :'),'Show my profile to my friends only');
	}
	echo "<br>";
	shn_acl_secure_hyperlink('sn','change_profile_visibility',_t('Change Profile Visibility'),$stream=null,$params=array(),$text_opts='');

	shn_form_fsclose();
	shn_form_fclose();
}

function _shn_sn_change_name(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	echo "<h2><center>"._t("Edit Full Name Confirme")."</center></h2>";

	shn_form_fopen('change_name_cr','sn',$form_opts);

	shn_form_fsopen(_t("Edit Full Name"));

	$query1 = "SELECT full_name,family_name FROM person_uuid WHERE p_uuid=?";
	$res1 = $db->Execute($query1,array($_SESSION["user_id"]));
	$full_name = $res1->fields["full_name"];

	shn_form_label(_t('Old Full Name :'),$full_name);

	shn_form_text(_t('New Full Name'),'full_name','');

	shn_form_fsclose();

	shn_form_submit(_t("Edit"),'name="edit_full_name"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	echo "<br><br>";
	shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_change_personal_details(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	echo "<h2><center>"._t("Edit Personal Details Confirme")."</center></h2>";

	$query = "SELECT image_id FROM image WHERE x_uuid=?";
	$res = $db->Execute($query,array($_SESSION["user_id"]));
	$image_id = $res->fields["image_id"];

	shn_form_fopen('change_personal_details_cr','sn',array('enctype'=>"enctype='multipart/form-data'"));
	shn_form_hidden(array('image_id'=>$image_id));

	shn_form_fsopen(_t('Current Personal Details'));

	echo "Profile Image :";
	echo "<img src='index.php?mod=sn&act=view_img&stream=image&x_uuid=".$_SESSION["user_id"]."&rand=".substr(md5(rand(0,2500)),0,5)."' border='0' width='150' height='125'/>";
	echo "<br><br>";

	$query3 = "SELECT opt_gender,birth_date,opt_marital_status,opt_religion,opt_race,opt_country,occupation FROM person_details WHERE p_uuid=?";
	$res3 = $db->Execute($query3,array($_SESSION["user_id"]));
	$gender = $res3->fields["opt_gender"];
	$dob = $res3->fields["birth_date"];
	$marital_status = $res3->fields["opt_marital_status"];
	$religion = $res3->fields["opt_religion"];
	$race = $res3->fields["opt_race"];
	$country = $res3->fields["opt_country"];
	$occupation = $res3->fields["occupation"];

	shn_form_label(_('Gender :'),$gender);
	shn_form_label(_('Date of Birth :'),$dob);

	if($marital_status=="unk"){

		shn_form_label(_t('Marital Status :'),"Unknown");
	}
	else if($marital_status=="sin"){

		shn_form_label(_t('Marital Status :'),"Single");
	}
	else if($marital_status=="mar"){

		shn_form_label(_t('Marital Status :'),"Married");
	}
	else if($marital_status=="div"){

		shn_form_label(_t('Marital Status :'),"Divorced");
	}

	if($religion){

		$query4 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res4 = $db->Execute($query4,array($religion));
		$religon_description = $res4->fields["option_description"];

		shn_form_label(_t('Religion :'),$religon_description);
	}

	if($race){

		$query5 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res5 = $db->Execute($query5,array($race));
		$race_description = $res5->fields["option_description"];

		shn_form_label(_t('Race :'),$race_description);
	}

	if($country){

		$query6 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res6 = $db->Execute($query6,array($country));
		$country_description = $res6->fields["option_description"];

		shn_form_label(_t('Country :'),$country_description);
	}

	shn_form_fsclose();

	shn_form_fsopen(_t('CurrentProfessional Information'));
	shn_form_label(_t('Occupation :'),$occupation);

	shn_form_fsclose();

	shn_form_fsopen(_t('Personal Details'));

	$radio_options = array('male'=>_t('Male'),'female'=>_t('Female'));
	shn_form_select(  $radio_options,_t('Gender'),'gender','',array('value'=>$gender));

	shn_form_upload(_t('Picture'),'picture');
	shn_form_date(_t("Date of Birth"),'dob',array('value'=>$dob));
	shn_form_opt_select(_t('opt_marital_status'), 'Marital Status','',array('value'=>$marital_status));
	shn_form_opt_select(_t('opt_religion'), 'Religion','',array('value'=>$religion));
	shn_form_opt_select(_t('opt_race'), 'Race','',array('value'=>$race));
	shn_form_opt_select(_t('opt_country'), 'Country','',array('value'=>$country));

	shn_form_fsclose();

	shn_form_fsopen(_t('Professional Information'));

	shn_form_text(_t('Occupation'),'occupation','',array('value'=>$occupation));

	shn_form_fsclose();

	shn_form_submit(_t("Save"),'name="edit_personal_details"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	echo "<br><br>";
	shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_change_medical_information(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	echo "<h2><center>"._t("Edit Medical Information Confirme")."</center></h2>";

	shn_form_fopen('change_medical_information_cr','sn',$form_opts);

	shn_form_fsopen(_t('Current Medical Information'));

	$query7 = "SELECT height,weight,opt_blood_type,opt_eye_color,opt_skin_color,opt_hair_color FROM person_physical WHERE p_uuid=?";
	$res7 = $db->Execute($query7,array($_SESSION["user_id"]));
	$height = $res7->fields["height"];
	$weight = $res7->fields["weight"];
	$blood_type = $res7->fields["opt_blood_type"];
	$eye_color = $res7->fields["opt_eye_color"];
	$skin_color = $res7->fields["opt_skin_color"];
	$hair_color = $res7->fields["opt_hair_color"];

	shn_form_label(_t('Height :'),$height);
	shn_form_label(_t('Weight :'),$weight);

	if($blood_type){

		$query8 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res8 = $db->Execute($query8,array($blood_type));
		$blood_type_description = $res8->fields["option_description"];

		shn_form_label(_t('Blood Group :'),$blood_type_description);
	}

	if($eye_color){

		$query8 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res8 = $db->Execute($query8,array($eye_color));
		$eye_color_description = $res8->fields["option_description"];

		shn_form_label(_t('Skin Color :'),$eye_color_description);
	}

	if($skin_color){

		$query9 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res9 = $db->Execute($query9,array($skin_color));
		$skin_color_description = $res9->fields["option_description"];

		shn_form_label(_t('Eye Color :'),$skin_color_description);
	}

	if($hair_color){

		$query10 = "SELECT option_description FROM field_options WHERE option_code=?";
		$res10 = $db->Execute($query10,array($hair_color));
		$hair_color_description = $res10->fields["option_description"];

		shn_form_label(_t('Hair Color :'),$hair_color_description);
	}

	shn_form_fsopen(_t('Medical Information'));
	
	shn_form_text(_t('Height'),'height','',array('value'=>$height));
	shn_form_text(_t('Weight'),'weight','',array(value=>$weight));
	shn_form_opt_select(_t('opt_blood_type'), 'Blood Group','',array('value'=>$blood_type));
	shn_form_opt_select(_t('opt_eye_color'), 'Eye Color','',array('value'=>$eye_color));
	shn_form_opt_select(_t('opt_skin_color'), 'Skin Color','',array('value'=>$skin_color));
	shn_form_opt_select(_t('opt_hair_color'), 'Hair Color','',array('value'=>$hair_color));

	shn_form_fsclose();

	shn_form_submit(_t("Save"),'name="edit_medical_information"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	echo "<br><br>";
	shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();
}

function _shn_sn_change_contact_information(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];
	echo "<h2><center>"._t("Confirm Contact Information")."</center></h2>";

	shn_form_fopen('change_contact_information_cr','sn',$form_opts);
	shn_form_hidden(array('pgoc_uuid'=>$_SESSION['user_id']));

	shn_form_fsopen(_t('Contact Information'));

	$db = $global['db'];
	
	$query2 = "SELECT * FROM (SELECT option_code,option_description FROM field_options fo WHERE fo.field_name='opt_contact_type' ) opts LEFT OUTER JOIN (SELECT * FROM contact WHERE pgoc_uuid=? ) ctct ON ctct.opt_contact_type = opts.option_code";
	$res = $db->Execute($query2,array($_SESSION['user_id']));//$db->Execute($query);

	while($row = $res->FetchRow()){
		shn_form_text($row['option_description'],'contact_'.$row['option_code'],'',array('value'=>$row['contact_value']));
		shn_form_hidden(array('old_'.$row['option_code'].'_value'=>$row['contact_value']));
	}

	shn_form_fsclose();

	shn_form_submit(_t("Save"),'name="edit_contact_information"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	echo "<br><br>";
	shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_change_profile_visibility(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	echo "<h2><center>"._t("Edit Profile Visibility Confirme")."</center></h2>";

	shn_form_fopen('change_profile_visibility_cr','sn',$form_opts);

	shn_form_fsopen(_t('Current Profile Visibility'));

	$query12 = "SELECT public_profile FROM sn_public_profile WHERE p_uuid=?";
	$res12 = $db->Execute($query12,array($_SESSION["user_id"]));
	$public_profile_description = $res12->fields["public_profile"];

	if($public_profile_description=="1"){
		shn_form_label(_t('Profile Visibility :'),'Show my profile to everyone');
	}
	else if($public_profile_description=="0"){
		shn_form_label(_t('Profile Visibility :'),'Show my profile to my friends only');
	}
	shn_form_fsclose();

	shn_form_fsopen(_t('Public/Private Profile'));

	shn_form_checkbox(_t('Show my profile to everyone'),'show_profile');

	shn_form_fsclose();

	shn_form_submit(_t("Edit"),'name="edit_profile_visibility"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	echo "<br><br>";
	shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_view_forum(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	//$db->debug=true;
	$query2 = "SELECT role_id FROM sn_forum_role WHERE user_id=? AND forum_id=";
	$res2 = $db->Execute($query2,array($_SESSION["user_id"],$forum_id));
	$role_id=$res2->fields["role_id"];
	if($role_id==null || $role_id=="f5"){

		$query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
		$res = $db->Execute($query,array($forum_id));
		$forum_name= $res->fields["forum_name"];

		echo "<h2><center>"._t("Current Topic of Forum&nbsp::").$forum_name."</center></h2>";

		shn_form_fopen('','sn',array('req_message'=>false));

		shn_form_fsopen(_t('Current Topic'));
		shn_form_hidden(array('forum_id'=>$forum_id));

		$page=0;
		if(isset($_REQUEST['page'])){
			$page=$_REQUEST['page'];

		}

		$q="SELECT COUNT(*) AS c FROM sn_forum_topic WHERE forum_id=?";
		$rs = $db->Execute($q,array($forum_id));
		$count=$rs->fields['c'];
		$rpp=10;

		$query = "SELECT topic_id, topic FROM sn_forum_topic WHERE forum_id=?";
		$res = $db->SelectLimit($query,$rpp,$page*$rpp,array($forum_id));

		echo "<table border = 2>";
		echo "<tr><th>"._t("Topic")."</th></tr>";
		while($row=$res->FetchRow()){
			$topic_id = $row["topic_id"];
			$topic = $row["topic"];

			echo "<tr>";
			echo "<td>";
			shn_acl_secure_hyperlink('sn','view_post',$topic,$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id),$text_opts='');
			echo "</td>";
			echo "</tr>";
		}
		echo "</table>";
		echo "<br>";
		$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
		if($page>0){
			shn_acl_secure_hyperlink('sn','view_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
			echo "&nbsp";
			shn_acl_secure_hyperlink('sn','view_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
		}
		for($i=0;$i<$page_count;$i++){
			echo "&nbsp";
			shn_acl_secure_hyperlink('sn','view_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
			echo "&nbsp";
		}
		if($page<($page_count-1)){
			echo "&nbsp";
			shn_acl_secure_hyperlink('sn','view_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
			echo "&nbsp";
			shn_acl_secure_hyperlink('sn','view_forum','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
		}

		shn_form_fsclose();

		shn_acl_secure_hyperlink('sn','forum_index',_t('Go Back'),$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id),$text_opts='');
		shn_form_fclose();
	}
	else{

		$query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
		$res = $db->Execute($query,array($forum_id));
		$forum_name= $res->fields["forum_name"];

		$q="SELECT COUNT(*) AS c FROM sn_forum_topic WHERE forum_id=?";
		$rs = $db->Execute($q,array($forum_id));
		$count=$rs->fields['c'];

		if($count=='0'){

			echo "<h2><center>"._t("Create New Topic to Forum &nbsp::").$forum_name."</center></h2>";

			shn_form_fopen('view_forum','sn',array('req_message'=>false));

			shn_form_fsopen(_t('Create New Topic'));
			shn_form_hidden(array('forum_id'=>$forum_id));

			shn_form_text(_('Topic'),'topic');

			shn_form_fsclose();

			shn_form_submit(_t("Create Topic"),'name="create_topic"');
			shn_form_submit(_t("Cancel"),'name="cancel"');

			shn_form_fclose();

			shn_form_fclose();

		}
		else{

			echo "<h2><center>"._t("Current Topic of Forum&nbsp::").$forum_name."</center></h2>";

			shn_form_fopen('view_forum','sn',array('req_message'=>false));

			shn_form_fsopen(_t('Current Topic'));
			shn_form_hidden(array('forum_id'=>$forum_id));

			$page=0;
			if(isset($_REQUEST['page'])){
				$page=$_REQUEST['page'];

			}

			$q="SELECT COUNT(*) AS c FROM sn_forum_topic WHERE forum_id=?";
			$rs = $db->Execute($q,array($forum_id));
			$count=$rs->fields['c'];
			$rpp=10;

			$query = "SELECT topic_id, topic FROM sn_forum_topic WHERE forum_id=?";
			$res = $db->SelectLimit($query,$rpp,$page*$rpp,array($forum_id));

			echo "<table border = 2>";
			echo "<tr><th>"._t("Topic")."</th></tr>";
			while($row=$res->FetchRow()){
				$topic_id = $row["topic_id"];
				$topic = $row["topic"];

				echo "<tr>";
				echo "<td>";
				shn_acl_secure_hyperlink('sn','add_post',$topic,$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id),$text_opts='');
				echo "</td>";
				echo "</tr>";

			}
			echo "</table>";
			echo "<br>";
			$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
			if($page>0){
				shn_acl_secure_hyperlink('sn','view_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
			}
			for($i=0;$i<$page_count;$i++){
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
				echo "&nbsp";
			}
			if($page<($page_count-1)){
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
			}

			shn_form_fsclose();

			shn_form_fsopen(_t('Create New Topic'));
			shn_form_hidden(array('forum_id'=>$forum_id));

			shn_form_text(_('Topic'),'topic');

			shn_form_fsclose();

			shn_form_submit(_t("Create Topic"),'name="create_topic"');
			shn_form_submit(_t("Cancel"),'name="cancel"');

			shn_form_fsopen(_t("Available Notices")); ?>
<div class="info"><?= _t("These are the available forum notices.");?></div>
			<?php

			$page=0;
			if(isset($_REQUEST['page'])){
				$page=$_REQUEST['page'];

			}
			$q="SELECT COUNT(*) AS c FROM sn_forum_note";
			$rs = $db->Execute($q);
			$count=$rs->fields['c'];
			$rpp=5;

			$note_query = "SELECT g.forum_id, g.forum_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_forums g JOIN sn_forum_note gn ON g.forum_id=gn.forum_id WHERE gn.forum_id=? ORDER BY note_id DESC";
			$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($forum_id));

			echo "<ul>";
			while($row=$rs->FetchRow()){
				$forum_id = $row["forum_id"];
				$forum_name = $row["forum_name"];
				$note_id = $row["note_id"];
				$subject = $row["subject"];
				$date = $row["date"];
				$note = $row["note"];
				echo "<li> Group Name :".$forum_name." Date :".$date."</li>";
				echo "<li> Subject :".$subject."</li>";
				echo "<li> Nitice :".$note."</li>";
				echo "<hr>";
			}
			echo "</ul>";
			echo "<br>";
			$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
			if($page>0){
				shn_acl_secure_hyperlink('sn','view_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
			}
			for($i=0;$i<$page_count;$i++){
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
				echo "&nbsp";
			}
			if($page<($page_count-1)){
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
				echo "&nbsp";
				shn_acl_secure_hyperlink('sn','view_forum','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
			}

			shn_form_fsclose();

			shn_form_fclose();
		}
	}
}

function _shn_sn_create_topic_cr(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic = $_REQUEST['topic'];

	$topic_id = shn_create_uuid('sn_topic');

	$sql = "INSERT INTO sn_forum_topic(forum_id,user_id,topic_id,topic) VALUES (?,?,?,?)";
	$res = $db->Execute($sql,array($forum_id,$_SESSION["user_id"],$topic_id,$topic));
	shn_sn_default();

}

function _shn_sn_add_post(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	//$db->debug=true;
	$query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
	$res = $db->Execute($query,array($forum_id));
	$forum_name= $res->fields["forum_name"];

	$query = "SELECT topic FROM sn_forum_topic WHERE topic_id=?";
	$res = $db->Execute($query,array($topic_id));
	$topic= $res->fields["topic"];

	echo "<h2><center>"._t("Add Post to Forum &nbsp::").$forum_name."</center></h2>";

	shn_form_fopen('add_post','sn',$form_opts);
	shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id));

	shn_form_fsopen($topic);

	$page=5;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	//$db->debug=true;
	$q="SELECT COUNT(*) AS c FROM sn_forum_post WHERE topic_id=?";
	$rs = $db->Execute($q,array($topic_id));
	$count=$rs->fields['c'];
	$rpp=3;

	$query = "SELECT forum_id, user_id, post_id, post,date FROM sn_forum_post WHERE topic_id=? ORDER BY post_id DESC";
	$rs = $db->SelectLimit($query,$rpp,$page*$rpp,array($topic_id));

	echo "<ul>";
	while($row=$rs->FetchRow()){
			
		$query = "SELECT pu.full_name FROM person_uuid pu JOIN sn_forum_post fp ON pu.p_uuid=fp.user_id WHERE fp.user_id=?";
		$res = $db->Execute($query,array($row['user_id']));
		$full_name= $res->fields["full_name"];

		$query2 = "SELECT role_id FROM sn_forum_role WHERE user_id=?";
		$res2 = $db->Execute($query2,array($_SESSION["user_id"]));
		$role_id= $res2->fields["role_id"];

		if($role_id=="f1" || $role_id=="f2" ){
			echo "<li><div>Post by &nbsp: ".$full_name."  When the &nbsp: ".$row['date']."</div></li>";
			echo "<li><div>".$row['post']."</div></li>";
			echo "<br>";
			shn_acl_secure_hyperlink('sn','edit_post',_t('Edit'),$stream=null,$params=array('forum_id'=>$row['forum_id'],'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
			echo"&nbsp &nbsp";
			shn_acl_secure_hyperlink('sn','delete_post',_t('Delete'),$stream=null,$params=array('forum_id'=>$row['forum_id'],'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
			echo "<br><hr>";

		}
		else if($_SESSION["user_id"]==$row['forum_id'] && $role_id=="f3"){
			echo "<li><div>Post by &nbsp: ".$full_name."  When the &nbsp: ".$row['date']."</div></li>";
			echo "<li><div>".$row['post']."</div></li>";
			echo "<br>";
			shn_acl_secure_hyperlink('sn','edit_post',_t('Edit'),$stream=null,$params=array('forum_id'=>$row['forum_id'],'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
			echo"&nbsp &nbsp";
			shn_acl_secure_hyperlink('sn','delete_post',_t('Delete'),$stream=null,$params=array('forum_id'=>$row['forum_id'],'topic_id'=>$topic_id,'post_id'=>$row['post_id']),$text_opts='');
			echo "<br><hr>";

		}
		else if($role_id=="f4"){
			echo "<li><div>Post by &nbsp: ".$full_name."  When the &nbsp: ".$row['date']."</div></li>";
			echo "<li><div>".$row['post']."</div></li>";
			echo "<br><hr>";

		}
	}
	echo "</ul>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','add_post','First',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','add_post','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','add_post',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','add_post','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','add_post','Last',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_form_fsopen(_t('Add New Post'));

	shn_form_wysiwyg(_t('New Post'), 'sn_post' , array('value'=>$post));

	shn_form_fsclose();

	shn_form_submit(_t("Reply"),'name="post"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	shn_form_fclose();

}

function _shn_sn_add_post_cr(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	$post = $_REQUEST['sn_post'];

	$post_id = shn_create_uuid('sn_post');
	$date=date("Y-m-d");

	if($_POST['sn_post']==null){
		add_error(_t("Please type the post"));
		shn_sn_add_post();
	}else{
		$sql = "INSERT INTO sn_forum_post(forum_id,user_id,topic_id,post_id,date,post) VALUES (?,?,?,?,?,?)";
		$res = $db->Execute($sql,array($forum_id,$_SESSION["user_id"],$topic_id,$post_id,$date,$post));
		shn_sn_default();
	}
}

function _shn_sn_forum_index(){
	global $global;
	$db=$global['db'];
	//$db->debug = true;
	$forums_query = "SELECT forum_id FROM sn_forum_role WHERE user_id=? AND role_id!='f5'";
	$writable_forums_by_user = $db->GetCol($forums_query,array($_SESSION['user_id']));
	//var_dump($writable_forums_by_user);
	echo "<h2><center>"._t("Forum Index")."</center></h2>";

	shn_form_fopen('log_forum','sn',array('req_message'=>false));
	shn_form_hidden(array('user_id'=>$_SESSION["user_id"],'full_name'=>$full_name));

	shn_form_fsopen(_t("Available Forums")); ?>
<div class="info"><?= _t("These are the available forums ditails.");?></div>
	<?php

	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM sn_forums";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=10;

	$note_query = "SELECT forum_id,forum_name,description FROM sn_forums ORDER BY forum_name ";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp);
	echo "<table border = 2>";
	echo "<tr><th>"._t("Forum Name")."</th><th>"._t("Description")."</th> <th></th></tr>";
	while($row=$rs->FetchRow()){
		$forum_id = $row["forum_id"];
		$forum_name = $row["forum_name"];
		$description = $row["description"];
		$dis_id = $row["dis_id"];
		echo "<tr>";
		echo "<td>";
		shn_acl_secure_hyperlink('sn','view_forum',$forum_name,$stream=null,$params=array('forum_id'=>$forum_id),$text_opts='');
		echo "</td>";
		echo "<td>".$description."</td>";
		echo "<td>";
		if(array_search($forum_id,$writable_forums_by_user)===FALSE){
			shn_acl_secure_hyperlink('sn','req_access',_t('Request Access'),$stream=null,$params=array('forum_id'=>$forum_id),$text_opts='');
		}
		echo "</td></tr>";
	}
	echo "</table>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','log_forum','First',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','log_forum','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','log_forum',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','log_forum','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','log_forum','Last',$stream=null,$params=array('forum_id'=>$forum_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_form_fclose();

}

function _shn_sn_req_access(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];

	echo "<h2><center>"._t("Requesting Role of Forum")."</center></h2>";

	shn_form_fopen('req_access','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Message to forum admin'));
	shn_form_hidden(array('user_id'=>$_SESSION["user_id"],'forum_id'=>$forum_id));

	$query2 = "SELECT forum_name FROM sn_forums WHERE forum_id=?";
	$res2 = $db->Execute($query2,array($forum_id));
	$forum_name=$res2->fields["forum_name"];

	$query3 = "SELECT full_name FROM person_uuid WHERE p_uuid=?";
	$res3 = $db->Execute($query3,array($_SESSION["user_id"]));
	$full_name=$res3->fields["full_name"];

	shn_form_text(_t('Subject'),'subject','',array('value'=>$forum_name));

	$stored_role = _shn_sn_get_stored_forum_role();
	shn_form_select($stored_role,_t('Available Roles'),'sn_available_role');
	//shn_form_multi_select('sn_available_role', $stored_role,'Available Roles','','length=100%');

	shn_form_textarea(_t('Message'),'message','',array('value'=>_t('I am '.$full_name.'. Requesting Authentication of forum : '.$forum_name)));

	shn_form_fsclose();

	shn_form_submit(_t("Request"),'name="req_forum"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	shn_form_fclose();
}

function _shn_sn_req_access_cr(){
	global $global;
	$db = $global['db'];
	$subject = $_POST['subject'];
	$message = $_POST['message'];
	$forum_id = $_POST['forum_id'];
	$req_role = $_POST['sn_available_role'];
	$target_user_id = $_SESSION['user_id'];

	// get the forum admin user_id
	$query = "SELECT user_id FROM sn_forum_role WHERE forum_id=? AND role_id='f2'";
	$res = $db->GetCol($query,array($forum_id));
	if(count($res)==0){
		// get the system admin user_id
		$query = "SELECT user_id FROM sn_forum_role WHERE forum_id=? AND role_id='f1'";
		$res = $db->GetCol($query,array($forum_id));
	}
	$no_errors = true;
	foreach($res as $p_uuid){
		$no_errors &= shn_sn_add_notifications_for_user($p_uuid,$subject,$message,'ad_add_roles_to_forum_users','sn',array('forum_id'=>$forum_id,'req_role'=>$req_role,'p_uuid'=>$target_user_id),null,$db->GenID('sn_notification_seq'));
	}
	if($no_errors==false){
		add_error(_t('Unknow error occured.'));
		shn_sn_forum_index();
	}else{
		add_confirmation(_t('Your request was sucessfully sent and will be acted upon. Please be patient'));
		shn_sn_forum_index();
	}
}

function _shn_sn_view_post(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	//$db->debug=true;
	$query = "SELECT forum_name, description FROM sn_forums WHERE forum_id=?";
	$res = $db->Execute($query,array($forum_id));
	$forum_name= $res->fields["forum_name"];

	$query1 = "SELECT topic FROM sn_forum_topic WHERE topic_id=?";
	$res1 = $db->Execute($query1,array($topic_id));
	$topic= $res1->fields["topic"];

	echo "<h2><center>"._t("Add Post to Forum &nbsp::").$forum_name."</center></h2>";

	shn_form_fopen('add_post','sn',$form_opts);
	shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id));

	shn_form_fsopen($topic);
	$page=5;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	//$db->debug=true;
	$q="SELECT COUNT(*) AS c FROM sn_forum_post WHERE topic_id=?";
	$rs = $db->Execute($q,array($topic_id));
	$count=$rs->fields['c'];
	$rpp=3;

	$query = "SELECT user_id, post,date FROM sn_forum_post WHERE topic_id=? ORDER BY post_id DESC";
	$rs = $db->SelectLimit($query,$rpp,$page*$rpp,array($topic_id));

	echo "<ul>";
	while($row=$rs->FetchRow()){
			
		$query = "SELECT pu.full_name FROM person_uuid pu JOIN sn_forum_post fp ON pu.p_uuid=fp.user_id WHERE fp.user_id=?";
		$res = $db->Execute($query,array($row['user_id']));
		$full_name= $res->fields["full_name"];

		echo "<li><div>Post by &nbsp: ".$full_name."  When the &nbsp: ".$row['date']."</div></li>";
		echo "<li><div>".$row['post']."</div></li>";
		echo "<br><hr>";
	}
	echo "</ul>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','view_post','First',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_post','&lt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_post',($i+1),$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_post','&gt',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_post','Last',$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_acl_secure_hyperlink('sn','view_forum',_t('Go Back'),$stream=null,$params=array('forum_id'=>$forum_id,'topic_id'=>$topic_id),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_edit_post(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	$post_id = $_REQUEST['post_id'];

	echo "<h2><center>"._t("Edit Post")."</center></h2>";

	shn_form_fopen('edit_post','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Edit Post'));
	shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$post_id));

	$query2 = "SELECT post FROM sn_forum_post WHERE post_id=?";
	$res2 = $db->Execute($query2,array($post_id));
	$post=$res2->fields["post"];
	echo "<p>"._t("Are you sure you need to delete this post:<br> ").$post;

	shn_form_fsclose();

	shn_form_fsopen(_t('Edit Post'));

	shn_form_wysiwyg(_t('New Post'), 'sn_post' , array('value'=>$post));

	shn_form_fsclose();

	shn_form_submit(_t("Edit"),'name="edit_post"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	shn_form_fclose();

}

function _shn_sn_edit_post_cr(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	$post_id = $_REQUEST['post_id'];
	$post = $_REQUEST['sn_post'];

	if($_POST['sn_post']==null){
		add_error(_t("Please type the post"));
		shn_sn_edit_post();
	}else{
		$sql = "UPDATE sn_forum_post SET post=? WHERE forum_id=? AND topic_id=? AND post_id=?";
		$res = $db->Execute($sql,array($post,$forum_id,$topic_id,$post_id));
		shn_sn_add_post();

	}
}

function _shn_sn_delete_post(){
	global $global;
	$db=$global['db'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	$post_id = $_REQUEST['post_id'];

	echo "<h2><center>"._t("Delete Post")."</center></h2>";

	shn_form_fopen('delete_post','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Delete post'));
	shn_form_hidden(array('forum_id'=>$forum_id,'topic_id'=>$topic_id,'post_id'=>$post_id));

	$query2 = "SELECT post FROM sn_forum_post WHERE post_id=?";
	$res2 = $db->Execute($query2,array($post_id));
	$post=$res2->fields["post"];
	echo "<p>"._t("Are you sure you need to delete this post :<br>").$post;

	shn_form_fsclose();

	shn_form_submit(_t("Delete"),'name="delete_post"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	shn_form_fclose();

}

function _shn_sn_delete_post_cr(){
	global $global;
	$db = $global['db'];
	$module = $global['module'];

	$forum_id = $_REQUEST['forum_id'];
	$topic_id = $_REQUEST['topic_id'];
	$post_id = $_REQUEST['post_id'];

	$query = "DELETE FROM sn_forum_post WHERE forum_id=? AND topic_id=? AND post_id=";
	$res = $db->Execute($query,array($forum_id,$topic_id,$post_id));
	shn_sn_add_post();
}

function _shn_sn_groups_page(){
	global $global;
	$db=$global['db'];

	echo "<h2><center>"._t("Groups")."</center></h2>";

	shn_form_fopen('','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Membered Groups'));
	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM sn_groups";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=5;

	$note_query = "SELECT g.group_id, g.group_name, g.description FROM sn_groups g JOIN sn_group_role gr ON g.group_id=gr.group_id WHERE gr.user_id=? ";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($_SESSION["user_id"]));
	echo "<table border=2>";
	echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th></tr>";
	while($row=$rs->FetchRow()){
		$group_id = $row["group_id"];
		$group_name = $row["group_name"];
		$description = $row["description"];
		echo "<tr>";
		echo "<td>";
		shn_acl_secure_hyperlink('sn','view_group_members',$group_name,$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
		echo "</td>";
		echo "<td>".$description."</td>";
		echo "</tr>";
			
	}
	echo "</table>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','groups','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_form_fsopen(_t("Non Membered Groups")); ?>
<div class="info"><?= _t("These are the available groups ditails.");?></div>
	<?php

	$page1=0;
	if(isset($_REQUEST['page1'])){
		$page1=$_REQUEST['page1'];

	}
	$q1="SELECT COUNT(*) AS c FROM sn_groups";
	$rs1 = $db->Execute($q1);
	$count1=$rs->fields['c'];
	$rpp1=5;
	//$db->debug=true;
	$note_query1 = "select distinct group_id,group_name,description,user_id from (select g.*,gr.user_id from sn_groups g left outer join sn_group_role gr on g.group_id=gr.group_id) tt ";
	$rs1 = $db->SelectLimit($note_query1,$rpp1,$page1*$rpp1);
	$user_id1 = $rs1->fields["user_id"];
	echo "<table border=2>";
	echo "<tr><th>"._t("group Name")."</th><th>"._t("Description")."</th></tr>";
	while($row=$rs1->FetchRow()){
		//var_dump($row);
		if($user_id==null){
			$group_id = $row["group_id"];
			$group_name = $row["group_name"];
			$description = $row["description"];
			echo "<tr>";
			echo "<td>";
			shn_acl_secure_hyperlink('sn','req_access_group',$group_name,$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
			echo "</td>";
			echo "<td>".$description."</td>";
			echo "</tr>";

		}
	}
	echo "</table>";
	echo "<br>";
	$page_count1 = (($count1%$rpp1)==0)?($count1/$rpp1):(($count1/$rpp1)+1);
	if($page1>0){
		shn_acl_secure_hyperlink('sn','groups','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page1-1)),$text_opts='');
	}
	for($i1=0;$i1<$page_count1;$i1++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups',($i1+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i1),$text_opts='');
		echo "&nbsp";
	}
	if($page1<($page_count1-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page1+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','groups','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count1-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_acl_secure_hyperlink('sn','default',_t('Go Back'),$stream=null,$params=array(),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_req_access_group(){
	global $global;
	$db=$global['db'];

	$group_id = $_REQUEST['group_id'];

	echo "<h2><center>"._t("Requesting Role of Group")."</center></h2>";

	shn_form_fopen('req_access_group','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Message to group admin'));
	shn_form_hidden(array('user_id'=>$_SESSION["user_id"],'group_id'=>$group_id));

	$query2 = "SELECT group_name FROM sn_groups WHERE group_id=?";
	$res2 = $db->Execute($query2,array($group_id));
	$group_name=$res2->fields["group_name"];

	$query3 = "SELECT full_name FROM person_uuid WHERE p_uuid=?";
	$res3 = $db->Execute($query3,array($_SESSION["user_id"]));
	$full_name=$res3->fields["full_name"];

	shn_form_text(_t('Subject'),'subject','',array('value'=>$group_name));

	$stored_role = _shn_sn_get_stored_group_role();
	shn_form_select($stored_role,_t('Available Roles'),'sn_available_role');

	shn_form_textarea(_t('Message'),'message','',array('value'=>_t('I am '.$full_name.'. Requesting Authentication of group : '.$group_name)));

	shn_form_fsclose();

	shn_form_submit(_t("Request"),'name="req_group"');
	shn_form_submit(_t("Cancel"),'name="cancel"');

	shn_form_fclose();
}

function _shn_sn_req_access_group_cr(){
	global $global;
	$db = $global['db'];
	$subject = $_POST['subject'];
	$message = $_POST['message'];
	$group_id = $_POST['group_id'];
	$req_role = $_POST['sn_available_role'];
	$target_user_id = $_SESSION['user_id'];

	// get the forum admin user_id
	$query = "SELECT user_id FROM sn_group_role WHERE group_id=? AND role_id='g2'";
	$res = $db->GetCol($query,array($group_id));
	if(count($res)==0){
		// get the system admin user_id
		$query = "SELECT user_id FROM sn_group_role WHERE group_id=? AND role_id='g1'";
		$res = $db->GetCol($query,array($group_id));
	}
	$no_errors = true;
	foreach($res as $p_uuid){
		$no_errors &= shn_sn_add_notifications_for_user($p_uuid,$subject,$message,'ad_add_roles_to_group_users','sn',array('group_id'=>$group_id,'req_role'=>$req_role,'p_uuid'=>$target_user_id),null,$db->GenID('sn_notification_seq'));
	}
	if($no_errors==false){
		add_error(_t('Unknow error occured.'));
		shn_sn_forum_index();
	}else{
		add_confirmation(_t('Your request was sucessfully sent and will be acted upon. Please be patient'));
		shn_sn_forum_index();
	}
}

function _shn_sn_view_group_members(){
	global $global;
	$db=$global['db'];

	$group_id = $_REQUEST['group_id'];

	$query2 = "SELECT group_name FROM sn_groups WHERE group_id=?";
	$res2 = $db->Execute($query2,array($group_id));
	$group_name=$res2->fields["group_name"];

	echo "<h2><center>"._t("View Members of Group ::".$group_name)."</center></h2>";

	shn_form_fopen('','sn',array('req_message'=>false));

	shn_form_fsopen(_t('Add Memberes as Friend'));
	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(pu.full_name) AS c FROM person_uuid pu JOIN sn_group_role gr ON pu.p_uuid=gr.user_id WHERE gr.group_id=?";
	$rs = $db->Execute($q,array($group_id));
	$count=$rs->fields['c'];
	$rpp=10;

	$note_query = "SELECT pu.full_name FROM person_uuid pu JOIN sn_group_role gr ON pu.p_uuid=gr.user_id WHERE gr.group_id=? AND gr.user_id!=?";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($group_id,$_SESSION["user_id"]));
	echo "<table border=2>";
	echo "<tr><th>"._t("Members Name")."</th></tr>";
	while($row=$rs->FetchRow()){
		$full_name = $row["full_name"];
		echo "<tr>";
		echo "<td>";
		shn_acl_secure_hyperlink('sn','search_people',$full_name,$stream=null,$params=array('full_name'=>$full_name),$text_opts='');
		echo "</td>";
		echo "</tr>";
			
	}
	echo "</table>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','view_group_members','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_form_fsopen(_t("Available Group Notices")); ?>
<div class="info"><?= _t("These are the available group notices.");?></div>
	<?php

	$page=0;
	if(isset($_REQUEST['page'])){
		$page=$_REQUEST['page'];

	}
	$q="SELECT COUNT(*) AS c FROM sn_group_note";
	$rs = $db->Execute($q);
	$count=$rs->fields['c'];
	$rpp=5;

	$note_query = "SELECT g.group_name, gn.note_id, gn.date, gn.subject, gn.note FROM sn_groups g JOIN sn_group_note gn ON g.group_id=gn.group_id WHERE gn.group_id=? ORDER BY note_id DESC";
	$rs = $db->SelectLimit($note_query,$rpp,$page*$rpp,array($group_id));

	echo "<ul>";
	while($row=$rs->FetchRow()){
		//$group_id = $row["group_id"];
		$group_name = $row["group_name"];
		$note_id = $row["note_id"];
		$subject = $row["subject"];
		$date = $row["date"];
		$note = $row["note"];
		echo "<li> Group Name :".$group_name." Date :".$date."</li>";
		echo "<li> Subject :".$subject."</li>";
		echo "<li> Nitice :".$note."</li>";
		echo "<hr>";
	}
	echo "</ul>";
	echo "<br>";
	$page_count = (($count%$rpp)==0)?($count/$rpp):(($count/$rpp)+1);
	if($page>0){
		shn_acl_secure_hyperlink('sn','view_group_members','First',$stream=null,$params=array('group_id'=>$group_id,'page'=>0),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','&lt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page-1)),$text_opts='');
	}
	for($i=0;$i<$page_count;$i++){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members',($i+1),$stream=null,$params=array('group_id'=>$group_id,'page'=>$i),$text_opts='');
		echo "&nbsp";
	}
	if($page<($page_count-1)){
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','&gt',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page+1)),$text_opts='');
		echo "&nbsp";
		shn_acl_secure_hyperlink('sn','view_group_members','Last',$stream=null,$params=array('group_id'=>$group_id,'page'=>($page_count-1)),$text_opts='');
	}

	shn_form_fsclose();

	shn_acl_secure_hyperlink('sn','groups',_t('Go Back'),$stream=null,$params=array('group_id'=>$group_id),$text_opts='');
	shn_form_fclose();

}

function _shn_sn_view_notifications(){
	global $global;
	$db=$global['db'];


	$notifications = shn_sn_get_notifications_for_user($_SESSION['user_id']);
	echo "<hr/>";
	foreach($notifications as $notf){

		shn_form_fopen($notf['target_action'],$notf['target_module'],array('req_message'=>false));
		shn_form_label(_t('Subject :'),$notf['subject']);
		shn_form_label(_t('Message :'),$notf['message']);
		shn_form_hidden(array('notification_id',$notf['notification_id']));
		$function_params = unserialize($notf['target_func_params']);

		$query3 = "SELECT role_name FROM sn_roles WHERE role_id=?";
		$res3 = $db->Execute($query3,array($function_params['req_role']));
		$role_name=$res3->fields["role_name"];
		echo "as ".$role_name."<br/>";

		shn_form_hidden($function_params);
		shn_form_submit(_t('Attend'),' name="attend" ');
		shn_form_fclose();
	}
}
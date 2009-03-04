<?php
/**Home Page of the Social Network
 *
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

if(isset($_SESSION['user_name'])==false){

	/*
	 * =====================================================================================
	 *     The content to be shown to the users who have not logged in.
	 * =====================================================================================
	 */
	?>
<h2>
<center><?php print (('Social Network Home')); ?></center>
</h2>
<div id="home">

<p><?php

print ("Sahana Social Network would function as a community based education portal " .
            "facilitating lot of functionalities like sharing info, creating interest" .
            " groups based on different conditions(decease condition , disaster insidents, " .
            "making own groups without any specification etc).Objectives of social network is " .
            "to facilitate rehabilitation process and community participation in disease notification" .
            " and management. With improved community participation, health care or disaster management" .
            " personnels can identify emerging public concerns and correct misinformations. If families can" .
            " discuss problems they come across in managing long term disease conditions among themselves and " .
            "share their experiences of tackling various problems, it will educate them to achieve better quality" .
            " of life and less frustration."  );
?></p>

<strong><?php echo ("Features include in SN user:")?></strong>
<ul>
	<li><?php print ("Editing My own profile"); ?></li>
	<li><?php print ("Sharing information over the public or user groups if authenticated by admin") ?>
	</li>
	<li><?php print ("Customising information to be shared") ?></li>
	<li><?php print ("Creating interest groups")?></li>
	<li><?php print ("Creating interest groups by search") ?></li>
	<li><?php print ("Creating interest groups based on decease condition or disaster insidents") ?></li>
	<li><?php print ("Feedback mechanisms") ?></li>
</ul>
<strong><?php echo ("Description of Actions:");?></strong><br />
<ul>
	<li><a href="index.php?mod=sn&act=signup"><b><?php echo ('Sign Up Now'); ?></a>
	<br />
	<?php echo _t("Create a new account for your self, it takes only a few minutes !.");?></li>
</ul>
	<?php
}else{
	?> <?php

	/*
	 * =====================================================================================
	 *      The content to be shown to the users who have logged in.
	 * =====================================================================================
	 */
	echo "<ul style='list-style:none;'>";
	echo "<li style='padding:5px;float:left;'><div style='border:1px solid black;width:150px;height:150px;padding:5px;'>";
    echo "<h4>"._t("Groups")."</h4>";
   
    echo "The groups this user is a member of.<br>";
    shn_acl_secure_hyperlink('sn','groups',_t("View Membered Groups"));
    echo "<br><br>";
    echo "Join new group.<br>";
    shn_acl_secure_hyperlink('sn','groups',_t("Join a Group"));
	echo "</div></li>";
	echo "<li  style='padding:5px;float:left;'><div style='border:1px solid black;width:150px;height:150px;padding:5px;'>";
    echo "<h4>"._t("Interests")."</h4>";
    /*
     * The interests this user has.
     */
    echo "<ul>";
    $interests = _shn_sn_get_user_interests();
    
    foreach($interests as $i=>$v){
        echo "<li>";
        shn_acl_secure_hyperlink('sn','find_people_with_interest',$v,null,array('interest_id'=>$i));
        echo "</li>";
    }
    echo "</ul>";
    shn_acl_secure_hyperlink('sn','add_interest',_t('Add Interests'));
	echo "</div></li>";
	echo "<li style='padding:5px;float:left;'><div style='border:1px solid black;width:150px;height:150px;padding:5px;'>";
    echo "<h4>"._t("Mailbox")."</h4>";
    /*
     * The Users Mailbox
     */
    $inbox_count = _shn_sn_get_unread_message_count();
    echo "<p>";printf(_t("You have <b>%d</b> unread message(s)."),$inbox_count);echo "</p>";
    shn_acl_secure_hyperlink('sn','mailbox',_t('Go to Mailbox'));
	echo "</div></li>";
	echo "<li style='padding:5px;float:left;'><div style='border:1px solid black;width:150px;height:150px;padding:5px;'>";
    echo "<h4>"._t("Notifications")."</h4>";
    $notification_count = count(shn_sn_get_notifications_for_user($_SESSION['user_id']));
    echo "<p>";printf(_t("You have %d unattended notifications."),$notification_count);echo "</p>";
    shn_acl_secure_hyperlink('sn','view_notifications',_t('View Notifications'));
	echo "</div></li>";
	echo "</ul>";
	$usr= _shn_sn_chk_user_in_sn($_SESSION["user_id"]);
	if($usr){
		?>
<ul>
	<li><b><?php shn_acl_secure_hyperlink('sn','view_profile',_t('My Profile')); ?> </b><br />
	<?php echo _t('Edit my profile'); ?></li>
	<li><b><?php shn_acl_secure_hyperlink('sn','sn_friends',_t('Friends'))?> </b>
	<br />
	<?php echo ('Sharing information over the friends in social network while seeying there profiles'); ?></li>
	<li><b><?php shn_acl_secure_hyperlink('sn','sn_forums',_t('Forums')) ?> </b>
	<br />
	<?php echo ('Share information over the public or user groups if authenticated by admin'); ?></li>
	<li><b><?php shn_acl_secure_hyperlink('sn','sn_groups',_t("Groups")); ?></b><br />
	<?php echo ('Search and join groups'); ?></li>

</ul>

	<?php
	}else{
		global $global;
        $db = $global['db'];
        $module = $global['module'];
        
		$q="SELECT full_name FROM person_uuid WHERE p_uuid=?";
        $rs = $db->Execute($q,array($_SESSION['user_id']));
        $full_name=$rs->fields['full_name'];
        
		echo "<h2>"._t("Sahana Social Networking :: My Page.  Well Come to the Social Network     :".$full_name)."</h2>";
        shn_tabmenu_open();
        shn_tabmenu_item('default',_('Home'),'sn');
        shn_tabmenu_item('friends',_('Friends'),'sn');
        shn_tabmenu_item('groups',_('Groups'),'sn');
        shn_tabmenu_item('mailbox',_('Mailbox'),'sn');
        shn_tabmenu_item('forum_index',_('Forum Index'),'sn');
        shn_tabmenu_close();

		?>
<ul>
	<li><b><?php shn_acl_secure_hyperlink('sn','view_profile',_t('View My Profile')); ?> </b><br />
	<?php echo _t('View My own profile'); ?></li>
	<li><b><?php shn_acl_secure_hyperlink('sn','edit_my_prof',_t('Edit My Profile')); ?> </b><br />
    <?php echo _t('Editing My own profile'); ?></li>
</ul>

	<?php
    $_SESSION[sn][p_uuid] = $_SESSION["user_id"];
    $_SESSION[sn][mem_username] = _shn_sn_get_username($_SESSION["user_id"]);
/*
    print _t("This is the administrative portal of the Sahana social network,From here you would be able " .
            "to do the administrative functions such as view all the details of SN members,making interest " .
            "groups based on various conditions and let members know about those groups.Not only that " .
            "through this portal the admin would give authentication for particualar members to share" .
            " info over the network.");
    echo "<br><br>"; 
  ?>


  <h4><?php echo _t("Features Include in Social Network Administrtor")?></h4>
      <ul>
          <li><?php print _t("View all the details of members"); ?> </li>
          <li><?php print _t("Make groups based on decease condition or disaster insidents") ?> </li>
          <li><?php print _t("Make forums based on diseases") ?> </li>
          <li><?php print _t("Let other members know about this gruop and send a link to involve in those groups") ?></li>
          <li><?php print _t("Authenticate members ")?></li>
          <li><?php print _t("send alerts to the members in case of any emerging concern or any system modification") ?></li>
          <li><?php print _t("send alerts to the members in case of any emerging concern or any system modification") ?></li>

      </ul>
<?php
*/
	}
}
?> <br />
</div>

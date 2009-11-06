 <?php
 /**
 * First page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Harsha Halgaswatta(harsha.halgaswatta@gmail.com)
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage s
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */

include_once $global['approot'] . '/inc/handler_form.inc';
include_once $global['approot'] . '/inc/lib_uuid.inc';
include_once $global['approot'] . '/mod/sn/lib_sn.inc';
//include_once $global['approot'] . '/inc/lib_form.inc';



	    //$_SESSION[sn][mem_username] = $_POST['username'];
		//$_SESSION[sn][p_uuid] = $result->fields['sn_mem_uuid'];

	$_SESSION[sn][p_uuid] = $_SESSION["user_id"];
	$_SESSION[sn][mem_username] = _shn_sn_get_username($_SESSION["user_id"]);
   	?>
	<div align="right">

    </div>
    <h2><center><?php print (('Social Network')); ?></center></h2>
    <div id="home">

    <p>
    <?php

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
  ?>
  </p>

  <strong><?php echo ("Features include in SN user:")?></strong>
      <ul>
          <li> <?php print ("Editing My own profile"); ?> </li>
          <li> <?php print ("Sharing information over the public or user groups if authenticated by admin") ?> </li>
          <li><?php print ("Customising information to be shared") ?></li>
          <li><?php print("Creating interest groups")?></li>
          <li><?php print ("Creating interest groups by search") ?></li>
          <li><?php print ("Creating interest groups based on decease condition or disaster insidents") ?></li>
          <li><?php print ("Feedback mechanisms") ?></li>
      </ul>

          <?php  shn_form_fopen('sn_home','sn'); ?>
  <strong><?php echo ("Description of Actions:")?></strong><br/>
      <ul>
          <li><a href="index.php?mod=sn&act=log_info"><b><?php echo  ('Home'); ?> </b></a><br/><?php echo  ('Social Network users home'); ?></li>
          <li><a href="index.php?mod=sn&act=my_prof"><b><?php echo  ('My Profile'); ?> </b></a><br/><?php echo  ('Editing My own profile'); ?></li>
     </ul>

  <?php
      //shn_form_submit('Go to home page');
      shn_form_fclose();
  ?>


<br/>
</div>





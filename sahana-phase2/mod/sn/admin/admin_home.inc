<?php
/**
 * Admin home
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


  	$_SESSION[sn][p_uuid] = $_SESSION["user_id"];
	$_SESSION[sn][mem_username] = _shn_sn_get_username($_SESSION["user_id"]);

	//echo 'this sss ssss';
?>



    <h2><center><?php print (('Social Network admin')); ?></center></h2>
    <div id="home">

  <p>
  <?php

 print ("This is the administrative portal of the Sahana social network,From here you would be able " .
 		"to do the administrative functions such as view all the details of SN members,making interest " .
	 		"groups based on various conditions and let members know about those groups.Not only that " .
	 		"through this portal the admin would give authentication for particualar members to share" .
	 		" info over the network.");
  ?>
  </p>

  <strong><?php echo ("Features include in SN user:")?></strong>
      <ul>
          <li> <?php print ("View all the details of members"); ?> </li>
          <li> <?php print ("Make groups based on decease condition or disaster insidents") ?> </li>
          <li><?php print ("Let other members know about this gruop and send a link to involve in those groups") ?></li>
          <li><?php print ("Authenticate members ")?></li>
          <li><?php print ("send alerts to the SN members in case of any emerging concern or any system modification") ?></li>
          <li><?php print ("send alerts to the SN members in case of any emerging concern or any system modification") ?></li>

      </ul>

          <?php  shn_form_fopen('sn_home','sn'); ?>
  <strong><?php echo ("Description of Actions:")?></strong><br/>
      <ul>
         <li><a href="index.php?mod=sn&act=ad_admin_home"><b><?php echo  ('Admin Home'); ?> </b></a><br/><?php echo  ('Admin Home'); ?></li>
         <li><a href="index.php?mod=sn&act=ad_view_mem"><b><?php echo  ('View Members'); ?> </b> </a><br/><?php echo  ('View all the details of SN members'); ?></li>

      </ul>




<br/>
</div>


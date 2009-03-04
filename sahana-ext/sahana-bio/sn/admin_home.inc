<?php
/**
 * Social Network Administrative Section Home Page
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
 * @package    shana
 * @subpackage sn
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */


include_once $global['approot'] . 'inc/handler_form.inc';
include_once $global['approot'] . 'inc/lib_uuid.inc';
include_once $global['approot'] . 'mod/sn/lib_sn.inc';
include_once $global['approot'] . '/mod/sn/admin_functs.inc';

function shn_sn_ad_home(){
    $_SESSION[sn][p_uuid] = $_SESSION["user_id"];
    $_SESSION[sn][mem_username] = _shn_sn_get_username($_SESSION["user_id"]);

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
}    
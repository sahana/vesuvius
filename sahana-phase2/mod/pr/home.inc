<?php
	/**
	 *
	 * PHP version 5
	 *
	 * LICENSE: This source file is subject to LGPL license
	 * that is available through the world-wide-web at the following URI:
	 * http://www.gnu.org/copyleft/lesser.html
	 *
	 * @package    Sahana - http://sahana.sourceforge.net
	 * @author     Kethees <sdkethees@gmail.com>
	 * @copyright  Lanka Software Foundation - http://www.opensource.lk
	 */

	global $conf;
	
	echo "<h2>" . $conf['mod_pr_home_header'] . "</h2>";
	
	echo "<p>";
	echo _t('The Person Registry is a central online repository where information about person can be stored. 
			Information like first name, last Name, date of birth, contact information, identity information, 
			location and other details are captured. These information can be used in other oriented modules 
			with generic person search.');	
	echo "</p>";	
	
	
	$url_gender = 'index.php?mod=pr&act=gender&stream=text';
	$url_religion = 'index.php?mod=pr&act=religion&stream=text'; 	
	$url_martial_status = 'index.php?mod=pr&act=martial_status&stream=text';
 	
 	?><center>
    <table class="dashboard">
        <tr>            
            <td>
                <div class="widget">
                    <?php shn_draw_chart(300,160,$url_gender);?>
                </div>
            </td>
            <td>
                <div class="widget">
                    <?php shn_draw_chart(300,160,$url_religion);?>
                </div>
            </td>
            <td>
                <div class="widget">
                    <?php shn_draw_chart(300,160,$url_martial_status);?>
                </div>
            </td>
        </tr>        
    </table>
</center>
<br />
<strong><?php echo _t("Features include:")?></strong>
<ul>
    <li>
    <?php

	print _t("Capture individual person information.)")
?>
    </li>
    <li>
    <?php print _t("Capture group information such as family, company and etc.") ?>
    </li>    
    <li>
    <?php print _t("Searching for different groups and individuals") ?>
    </li>
    <li>
    <?php print _t("Modify Information on groups and individuals") ?>
    </li>
    <li>
    <?php print _t("Various Reporting functionalities") ?>
    </li>
    <li>
    <?php print _t("Visualizing information based on statistics") ?>   
    </li>
</ul>
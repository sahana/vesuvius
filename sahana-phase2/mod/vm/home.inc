<?php
/* $Id: [sahana_home]/mod/vm/home.inc,v 1.0 2006/06/12  */
/**
 *
 * Volunteer Management Module -- includes files from the inc directory.
 *
 * <p>This is the main file for the Volunteer Management (VM) module.
 * It generates a three-column row which appears at the top of the 
 * VM home page. The first column displays the number of projects, 
 * the second the number of organizations, and the 
 * third the number of volunteers.</p>
 *
 * @package    Trinity_College_VM_Module
 * @copyright  Copyright {@link http://www.opensource.lk Lanka Software Foundation} 2006
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL) 
 * @author     Ravindra <ravindra@opensource.lk>
 * @author     Jonathan Damon <jonathan.damon@trincoll.edu> 
 * @author     R. Morelli <ralph.morelli@trincoll.edu>
 *
 */

/** Contains functions for viewing projects and project summary data.
 */
include_once "view_projects.inc";                       

/** Contains utility functions for the VM and VR modules.
 */
include_once $global['approot']."/mod/vm/utility_functions.inc";


global $global;                      
$db=$global["db"];                               

$proj_no= count_entries('vm_projects');
$vol_no= get_volunteer_count();  // Utility function
$org_no= count_entries('org_main') - 1;
?>

<!-- 
 This section of HTML code displays a summary for the Volunteer Management Module. Its style is defined
 in the CSS document: /usr/share/sahana/www/theme/default/sahana.css. 
-->

<div id="home">
    <h2><?=_("Volunteer Management -- Projects Overview Page")?></h2>

<table width="99%">
	<colgroup>
	<col width="33%">
	<col width="33%">
	<col width="33%">
    <thead>
        <td><strong><?=_("Projects")?></strong></td>
        <td><strong><?=_("Organizations")?></strong></td>
        <td><strong><?=_("Volunteers")?></strong></td>
    </thead>
    <tbody>
        <tr>
		<td align=center>
			<div>
        	        <a href="index.php?mod=vm&act=proj_display">
                	  <strong> <?php echo $proj_no ?></strong><?=_(" Projects have been started.")?>
	                </a>	
			</div>
		</td>
		<td align=center>
			<div>
			<a href="index.php?mod=or&act=view_org">
                	  <strong> <?php echo $org_no ?></strong><?=_(" Organizations are registered.")?>
	                </a>	
			</div>
		</td>
		<td align=center>
			<div>
			<a href="index.php?mod=vm&act=vol_display">
	                   <strong><?php echo $vol_no?></strong><?=(" Volunteers are designated to these projects.")?>
        	        </a>
	                </div>
	        </td>
        </tr>
    </tbody>
    </table>
</div>
<br />

<?php
       _shn_vm_viewform_allproj();
?>

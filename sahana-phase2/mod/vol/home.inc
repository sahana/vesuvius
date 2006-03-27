<?php
/**Home page of the Organization Registry 
*
* PHP version 4 and 5
*
* LICENSE: This source file is subject to LGPL license
* that is available through the world-wide-web at the following URI:
* http://www.gnu.org/copyleft/lesser.html
*
* @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
* @copyright  Lanka Software Foundation - http://www.opensource.lk
* @package    sahana
* @subpackage or
*/
include_once "view_vol.inc";
global $global;
global $conf;
$db=$global["db"];
$q="select count(person_uuid.p_uuid) as cnt from person_uuid,person_status where person_status.isReliefWorker=1 and person_status.p_uuid=person_uuid.p_uuid";
$res=$db->Execute($q);
if(!$res->EOF){
    $vol_no=$res->fields[0];
}
?>
<div id="home">
    <h2><?=_lc($conf['mod_vol_name'])?></h2>
		<div><?=_("The Volunteer Registry keeps track of all Volunteer working in the disaster region. It captures not only the places where they are active, but also captures information on the range of services they are providing in each area.          
				Features Include:")?>
        </div>
		<ul>
            
            <li><?=_("Registering ad-hoc volunteers willing to contribute")?></li>
            <li><?=_("Capturing the essential services each Volunteer is providing and where")?></li>
            <li><?=_("Reporting on the converge of services and support in the region and more")?></li>
            <li><?=_("importantly where there are no aid services being provided")?></li>
        </ul>
</div>
<br />
<table>
    <thead>
        <td><strong><?=_("Volunteers")?></strong></td>
        <td><strong><?=_("Please Register")?></strong></td>
    
    </thead>
    <tbody>
        <tr>
			<td>
				<div>
                <a href="index.php?mod=or&act=view_org">
                  <strong> <?php echo $vol_no ?></strong><?=_(" Volunteers have registered")?>
                </a>
				</div>
			</td>
			<td>
				<div><?=_("
					Registering as a volunteer allows us to know who is doing what where and allows us to operate more effectively as one.")?>	    
				</div>
			</td>
			
		
        </tr>
        </tbody>
        </table>
       <br />

        <div id="note">
           <strong><?=_("Last 10 Volunteers to Register")?></strong>
        </div>
<?php
		_shn_vol_viewform_all();
        //_shn_or_viewform_allorg(10);
?>

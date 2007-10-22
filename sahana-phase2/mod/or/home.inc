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
include_once "view_org.inc";
global $global;
include_once $global['approot']."/inc/reporting/lib_chart.inc";
global $conf;
$db=$global["db"];
$q="SELECT count(o_uuid) as cnt FROM org_main";
$res=$db->Execute($q);
$org_no=5;
if(!$res->EOF){
	$q="SELECT value FROM config WHERE module_id='admin' AND confkey='acl_base'";
    $res_tmp=$db->Execute($q);
        if($res_tmp->fields[0]=='installed'){
    		$org_no=($res->fields[0])-1;
   	    }else{
      	    $org_no=($res->fields[0]);
         }
    $org_no=($org_no<0)?0:$org_no;
}else{
	$org_no="Zero";
}

?>
<div id="home">
    <h2><?=_lc($conf['mod_or_name'])?></h2>
    		<div><b><i><?=_("\"who is doing what and where\"")?></i></b></div>
        <br></br>
		<div><?=_('The Organization Registry keeps track of all the relief organizations working in the disaster region. It captures not only the places where they are active, but also captures information on the range of services they are providing in each area.          
				Features Include:')?>
        </div>
		<ul>
            <li><?=_('Capturing a comprehensive list of meta data on an relief organization and all the activities they have in the region')?></li>
            <li><?=_('Capturing the essential services each group is providing and where')?></li>
            <li><?=_('Reporting on the converge of services and support in the region and more')?></li>
            <li><?=_('Importantly where there are no aid services being provided')?></li>
        </ul>
</div>
<br />
<div>
<?php shn_chart_display("shn_or_service_coverage_chart"); ?>
</div>
<table>
    <thead>
        <td><strong><?=_('Organizations')?></strong></td>
        <td><strong><?=_('Please Register')?></strong></td>
     
    </thead>
    <tbody>
        <tr>
			<td>
				<div>
                <a href="index.php?mod=or&act=view_org">
                  <strong> <?php echo $org_no ?></strong><?=_(' Organizations/Departments/Branches have registered')?>
                </a>
				</div>
			</td>
			<td>
				<div><?=_('Registering your organization allows us to know who is doing what where and allows us to operate more effectively as one.')?>	    
				</div>
			</td>
					
        </tr>
                
        </tbody>
        </table>
        <br />
        <div id="note">
           <strong><?=_('Last 5 Organizations to Register')?></strong>
        </div>
        <?php _shn_or_viewform_latest_orgs(5);?>
       
    require_once($global['approot']."/inc/lib_rss.inc");
    shn_rss_add_feed('new_org_list',_('Newly Registered organizations'));


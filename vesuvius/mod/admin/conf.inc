<?php
/**
 * @name         Administration
 * @version      1.0
 * @package      admin
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @author       Sudheera R. Fernando <sudheera@opensource.lk>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0303
 */


// provide the nice display name for the Administration module
$conf['mod_admin_name'] = _t("Administration");
$conf['mod_admin_menuorder'] = 80;

$conf['mod_admin_ims_active'] = true;
$conf['mod_admin_ims_level1'] = 'Disaster';
$conf['mod_admin_ims_level2'] = 'Events';
$conf['mod_admin_ims_level3'] = 'Incidents';

$conf['mod_admin_dependencies'] = "";

$conf['mod_admin_loc_level_start'] = 1;
$conf['mod_admin_loc_level_end'] = 3;

$conf['mod_admin_version']=1.0;


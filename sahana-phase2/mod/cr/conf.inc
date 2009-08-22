<?php
// provide the nice display name for the CR module
$conf['mod_cr_name'] = _t("Shelter Registry");
$conf['mod_cr_menuorder'] = 4;

/**
 * Alternate wording for Camp in singular form
 */
$conf['mod_cr_alt']=_t("Shelter");

/**
 * Spatial Density Report Configs
 * Modify Values here
 */
$conf['mod_cr_perc_0']=0.20;
$conf['mod_cr_perc_1']=0.40;
$conf['mod_cr_perc_2']=0.60;
$conf['mod_cr_perc_3']=0.80;
$conf['mod_cr_perc_f']=1.00;

// marker names for percentages
$conf['mod_cr_perc_0_mk']='marker_r3';
$conf['mod_cr_perc_1_mk']='marker_r3';
$conf['mod_cr_perc_2_mk']='marker_r2';
$conf['mod_cr_perc_3_mk']='marker_r1';
$conf['mod_cr_perc_f_mk']='marker';

$conf['mod_cr_dependencies'] = "";




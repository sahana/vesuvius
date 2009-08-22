
-- GROUP TYPES
INSERT INTO field_options VALUES('opt_group_type','fam','family');
INSERT INTO field_options VALUES('opt_group_type','com','company');
INSERT INTO field_options VALUES('opt_group_type','soc','society');
INSERT INTO field_options VALUES('opt_group_type','tor','tourists');
INSERT INTO field_options VALUES('opt_group_type','oth','other');
INSERT INTO field_options VALUES('opt_group_type','===','==Select Option==');

-- IDENTITY CARD / PASSPORT TYPES
INSERT INTO field_options VALUES('opt_id_type','nic','National Identity Card');
INSERT INTO field_options VALUES('opt_id_type','pas','Passport');
INSERT INTO field_options VALUES('opt_id_type','dln','Driving License Number');
INSERT INTO field_options VALUES('opt_id_type','oth','Other');

-- PERSON STATUS VALUES
INSERT INTO field_options VALUES ('opt_status','ali','Alive & Well');
INSERT INTO field_options VALUES ('opt_status','mis','Missing');
INSERT INTO field_options VALUES ('opt_status','inj','Injured');
INSERT INTO field_options VALUES ('opt_status','dec','Deceased');

-- PERSON GENDER 
-- INSERT INTO field_options VALUES ('opt_gender','unk','Unknown');
INSERT INTO field_options VALUES ('opt_gender','mal','Male');
INSERT INTO field_options VALUES ('opt_gender','fml','Female');

-- PERSON RELATIONSHIPS
INSERT INTO field_options VALUES('opt_relationship_type','fat','Father');
INSERT INTO field_options VALUES('opt_relationship_type','mot','Mother');
INSERT INTO field_options VALUES('opt_relationship_type','bro','Brother');
INSERT INTO field_options VALUES('opt_relationship_type','sis','Sister');
INSERT INTO field_options VALUES('opt_relationship_type','gft','GrandFather');
INSERT INTO field_options VALUES('opt_relationship_type','gmt','GrandMother');
INSERT INTO field_options VALUES('opt_relationship_type','gfpat','GrandFatherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gfmat','GrandFatherMaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmpat','GrandMotherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmmat','GrandMotherMaternal');
INSERT INTO field_options VALUES('opt_relationship_type','fnd','Friend');
INSERT INTO field_options VALUES('opt_relationship_type','oth','Other');

-- PERSON CONTACT TYPES
INSERT INTO field_options VALUES ('opt_contact_type','home','Home(permanent address)');
INSERT INTO field_options VALUES ('opt_contact_type','name','Contact Person');
INSERT INTO field_options VALUES ('opt_contact_type','pmob','Personal Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','curr','Current Phone');
INSERT INTO field_options VALUES ('opt_contact_type','cmob','Current Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','emai','Email address');
INSERT INTO field_options VALUES ('opt_contact_type','fax','Fax Number');
INSERT INTO field_options VALUES ('opt_contact_type','web','Website');
INSERT INTO field_options VALUES ('opt_contact_type','inst','Instant Messenger');

-- PERSON LOCATION TYPES 
INSERT INTO field_options VALUES ('opt_person_loc_type','hom','Permanent home address)');
INSERT INTO field_options VALUES ('opt_person_loc_type','imp','Impact location');
INSERT INTO field_options VALUES ('opt_person_loc_type','cur','Current location');

-- AGE GROUP VALUES
INSERT INTO field_options VALUES ('opt_age_group','unk','Unknown');
INSERT INTO field_options VALUES ('opt_age_group','inf','Infant (0-1)');
INSERT INTO field_options VALUES ('opt_age_group','chi','Child (1-15)');
INSERT INTO field_options VALUES ('opt_age_group','you','Young Adult (16-21)');
INSERT INTO field_options VALUES ('opt_age_group','adu','Adult (22-50)');
INSERT INTO field_options VALUES ('opt_age_group','sen','Senior Citizen (50+)');

-- COUNTRY VALUES
INSERT INTO field_options VALUES ('opt_country','uk','United Kingdom');
INSERT INTO field_options VALUES ('opt_country','lanka','Sri Lanka');

-- RACE VALUES 
INSERT INTO field_options VALUES ('opt_race','unk','Unknown');
INSERT INTO field_options VALUES ('opt_race','filip','Filipino');
INSERT INTO field_options VALUES ('opt_race','other','Other');

-- RELIGION VALUES 
INSERT INTO field_options VALUES ('opt_religion','unk','Unknown');
INSERT INTO field_options VALUES ('opt_religion','bud','Buddhist');
INSERT INTO field_options VALUES ('opt_religion','chr','Christian');
INSERT INTO field_options VALUES ('opt_religion','mus','Muslim');
INSERT INTO field_options VALUES ('opt_religion','oth','Other');

-- MARITIAL STATUS VALUES 
INSERT INTO field_options VALUES ('opt_marital_status','unk','Unknown');
INSERT INTO field_options VALUES ('opt_marital_status','sin','Single');
INSERT INTO field_options VALUES ('opt_marital_status','mar','Married');
INSERT INTO field_options VALUES ('opt_marital_status','div','Divorced');

-- BLOOD TYPE VALUES 
INSERT INTO field_options VALUES ('opt_blood_type','unk','Unknown');
INSERT INTO field_options VALUES ('opt_blood_type','a+','A+');
INSERT INTO field_options VALUES ('opt_blood_type','a-','A-');
INSERT INTO field_options VALUES ('opt_blood_type','b+','B+');
INSERT INTO field_options VALUES ('opt_blood_type','b-','B-');
INSERT INTO field_options VALUES ('opt_blood_type','ab+','AB+');
INSERT INTO field_options VALUES ('opt_blood_type','ab-','AB-');
INSERT INTO field_options VALUES ('opt_blood_type','o+','O+');
INSERT INTO field_options VALUES ('opt_blood_type','o-','O-');
INSERT INTO field_options VALUES ('opt_blood_type','oth','Other');

-- EYE COLOR VALUES
INSERT INTO field_options VALUES ('opt_eye_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_eye_color','bla','Black');
INSERT INTO field_options VALUES ('opt_eye_color','bro','Light Brown');
INSERT INTO field_options VALUES ('opt_eye_color','blu','Blue');
INSERT INTO field_options VALUES ('opt_eye_color','oth','Other');

-- SKIN COLOR VALUES
INSERT INTO field_options VALUES ('opt_skin_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_skin_color','bla','Black');
INSERT INTO field_options VALUES ('opt_skin_color','bro','Dark Brown');
INSERT INTO field_options VALUES ('opt_skin_color','fai','Fair');
INSERT INTO field_options VALUES ('opt_skin_color','whi','White');
INSERT INTO field_options VALUES ('opt_skin_color','oth','Other');

-- HAIR COLOR VALUES
INSERT INTO field_options VALUES ('opt_hair_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_hair_color','bla','Black');
INSERT INTO field_options VALUES ('opt_hair_color','bro','Brown');
INSERT INTO field_options VALUES ('opt_hair_color','red','Red');
INSERT INTO field_options VALUES ('opt_hair_color','blo','Blond');
INSERT INTO field_options VALUES ('opt_hair_color','oth','Other');

-- CAMP TYPE VALUES 
INSERT INTO field_options VALUES ('opt_camp_type','ngo','NGO Run Camp');
INSERT INTO field_options VALUES ('opt_camp_type','tmp','Temporary Shelter');
INSERT INTO field_options VALUES ('opt_camp_type','gov','Government Evacuation Center');

-- CAMP SERVICES 
INSERT INTO field_options VALUES ('opt_camp_service','adm','Administrative Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','snt','Sanitation Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','wat','Water Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','mdc','Medical Facilities');

-- ORGANIZATION TYPES 
INSERT INTO field_options VALUES('opt_org_type','gov','Government');
INSERT INTO field_options VALUES('opt_org_type','priv','Private');
INSERT INTO field_options VALUES('opt_org_type','ngo','NGO');
INSERT INTO field_options VALUES('opt_org_type','ingo','International NGO');
INSERT INTO field_options VALUES('opt_org_type','mngo','Multinational NGO');

-- ORGANIZATION TYPES 
INSERT INTO field_options VALUES('opt_org_sub_type','dep','Department');
INSERT INTO field_options VALUES('opt_org_sub_type','subs','Subsidiary');
INSERT INTO field_options VALUES('opt_org_sub_type','bra','Branch');

-- ORGANIZATION SECTOR VALUES
INSERT INTO field_options VALUES('opt_sector_type','sup','Supplier of Goods');
INSERT INTO field_options VALUES('opt_sector_type','comm','Communications');
INSERT INTO field_options VALUES('opt_sector_type','med','Medical Services');
INSERT INTO field_options VALUES('opt_sector_type','rehab','Rehabilitation');
INSERT INTO field_options VALUES('opt_sector_type','edu','Education');

-- LOCATION TYPE VALUES
INSERT INTO field_options VALUES ('opt_location_type','1','Country');
INSERT INTO field_options VALUES ('opt_location_type','2','State');
INSERT INTO field_options VALUES ('opt_location_type','3','City');

-- CATALOGUE MAX_DEPTH VALUE
INSERT INTO field_options VALUES ('opt_cs_depth','6','depth');
INSERT INTO field_options VALUES ('opt_cs_page_record','30','number of page records');

-- REPORT AND CHART UPDATE FREQUENCY VALUES
INSERT INTO field_options VALUES ('opt_rs_rep_freq','30','the frequency of report update');
INSERT INTO field_options VALUES ('opt_rs_cht_freq','30','the frequency of chart update');

-- INSERT MODULE VALUES
-- INSERT INTO modules VALUES ('cr', '0.2', TRUE);
-- INSERT INTO modules VALUES ('or', '0.2', TRUE);
-- INSERT INTO modules VALUES ('admin', '0.2', TRUE);
-- INSERT INTO modules VALUES ('gis', '0.2', TRUE);

-- GIS WIKI VALUES
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','gen','General');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','per','Person Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dam','Damage Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dis','Disaster Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','sos','Help Needed');

-- GIS SAVE FILE
INSERT INTO field_options VALUES('opt_geo_save_file','file_save','Publish File To Export Directory');

-- GIS FILE TYPES
INSERT INTO field_options VALUES('opt_geo_file_type','kml','KML');
INSERT INTO field_options VALUES('opt_geo_file_type','gml','GML');
INSERT INTO field_options VALUES('opt_geo_file_type','gpx','GPX');
INSERT INTO field_options VALUES('opt_geo_file_type','georss','GeoRSS');

-- GPS VALUES
INSERT INTO field_options VALUES('opt_wpt_type','air','Airstrip');
INSERT INTO field_options VALUES('opt_wpt_type','hos','Hospital');
INSERT INTO field_options VALUES('opt_wpt_type','off','Office');
INSERT INTO field_options VALUES('opt_wpt_type','pow','Place of Worship');
INSERT INTO field_options VALUES('opt_wpt_type','sch','School');
INSERT INTO field_options VALUES('opt_wpt_type','vil','Village');
INSERT INTO field_options VALUES('opt_wpt_type','war','Warehouse');
INSERT INTO field_options VALUES('opt_wpt_type','wat','Water Supply');
INSERT INTO field_options VALUES('opt_wpt_type','toi','WC');

-- INSERT CONFIG VALUES
INSERT INTO config (module_id,confkey,value) VALUES ( 'cr', 'division_type', '2');
INSERT INTO config (module_id,confkey,value) VALUES ( 'pref', 'shn_xform_enabled', 'false');

-- INSERT DEFAULT LC_FIELDS
-- Used for Translations:
-- http://wiki.sahana.lk/doku.php?id=dev:l10n#database_localization
INSERT INTO lc_fields (tablename,fieldname) VALUES ("field_options","option_description");
INSERT INTO lc_fields (tablename,fieldname) VALUES ("ct_unit","name");
INSERT INTO lc_fields (tablename,fieldname) VALUES ("ct_unit_type","name");
INSERT INTO lc_fields (tablename,fieldname) VALUES ("ct_unit_type","description");

-- INSERT DEFAULT DATA CLASSIFICATION LEVELS
INSERT INTO sys_data_classifications VALUES ( 1, 'Person Sensitive');
INSERT INTO sys_data_classifications VALUES ( 2, 'Organization Sensitive');
INSERT INTO sys_data_classifications VALUES ( 3, 'Legally Sensitive');
INSERT INTO sys_data_classifications VALUES ( 4, 'National Security Sensitive');
INSERT INTO sys_data_classifications VALUES ( 5, 'Socially Sensitive');
INSERT INTO sys_data_classifications VALUES ( 6, 'System Sensitive');
INSERT INTO sys_data_classifications VALUES ( 7, 'Not Sensitive');
INSERT INTO sys_data_classifications VALUES ( 8, 'Unclassified');

-- INSERT DEFAULT SYS USER GROUPS
INSERT INTO sys_user_groups VALUES ( 1, 'Administrator (Admin)');
INSERT INTO sys_user_groups VALUES ( 2, 'Registered User');
INSERT INTO sys_user_groups VALUES ( 3, 'Anonymous User');
INSERT INTO sys_user_groups VALUES ( 4, 'Super User (Head of Operations)');
INSERT INTO sys_user_groups VALUES ( 5, 'Organization Admin');
INSERT INTO sys_user_groups VALUES ( 6, 'Volunteer Coordinator');
INSERT INTO sys_user_groups VALUES ( 7, 'Camp Admin');
INSERT INTO sys_user_groups VALUES ( 8, 'Field Officer');

-- INSERT DEFAULT SYS USER GROUP TO DATA CLASSIFICATION MAPPINGS
-- admin role
-- admin(1) can create(8),read(4),update(2),delete(1) (totaling 15) System sensitive(6) data  
INSERT INTO sys_group_to_data_classification VALUES ( 1, 1,"-r--");
-- no perms
INSERT INTO sys_group_to_data_classification VALUES ( 1, 2,"-r--");
-- read only
INSERT INTO sys_group_to_data_classification VALUES ( 1, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 1, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 1, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 1, 6,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 1, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 1, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 2, 1,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 2,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 6,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 2, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 3, 1,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 2,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 3,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 5,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 6,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 3, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 4, 1,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 2,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 4,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 6,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 4, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 5, 1,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 2,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 6,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 5, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 6, 1,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 2,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 6,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 6, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 7, 1,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 2,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 3,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 5,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 6,"-r--");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 7,"crud");
INSERT INTO sys_group_to_data_classification VALUES ( 7, 8,"crud");

INSERT INTO sys_group_to_data_classification VALUES ( 8, 1,"c---");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 2,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 3,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 4,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 5,"cru-");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 6,"----");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 7,"cru-");
INSERT INTO sys_group_to_data_classification VALUES ( 8, 8,"cru-");

-- INSERT DEFAULT TABLE FIELD TO DATA CLASSIFICATION MAPPINGS
-- TABLE NAMES ARE SORTED IN ALPHABETICAL ORDER

-- adodb_logsql

-- alt_logins

-- audit
INSERT INTO sys_tablefields_to_data_classification VALUES ( "audit", 6);

-- camp_admin

-- camp_general

-- camp_reg
INSERT INTO sys_tablefields_to_data_classification VALUES ( "camp_reg", 5);

-- camp_services
INSERT INTO sys_tablefields_to_data_classification VALUES ( "camp_services", 7);

-- chronology
INSERT INTO sys_tablefields_to_data_classification VALUES ( "chronology", 6);

-- config
INSERT INTO sys_tablefields_to_data_classification VALUES ( "config", 6);

-- contact
INSERT INTO sys_tablefields_to_data_classification VALUES ( "contact", 5);

-- ct_cat_unit
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ct_cat_unit", 7);

-- ct_catalogue
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ct_catalogue", 6);

-- ct_unit
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ct_unit", 7);

-- ct_unit_type
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ct_unit_type", 7);

-- devel_logsql

-- field_options
INSERT INTO sys_tablefields_to_data_classification VALUES ( "field_options", 6);

-- gis_feature

-- gis_feature_class

-- gis_location

-- gis_layers

-- gis_wiki

-- gps

-- group_details
INSERT INTO sys_tablefields_to_data_classification VALUES ( "group_details", 1);

-- hr_assign_contractor_to_site_table

-- hr_assign_site_to_contractor_table

-- hr_contractor_table

-- hr_damaged_house_basic_details_table

-- hr_damaged_house_location_details_table

-- hr_family_head_details_table

-- hr_site_allocated_organization_table

-- hr_site_house_details_table

-- hr_site_infrastructure_details_table

-- hr_site_location_details_table

-- hr_site_main_coordinator_details_table

-- hr_site_name_and_uid_table

-- identity_to_person
INSERT INTO sys_tablefields_to_data_classification VALUES ( "identity_to_person", 1);

-- image
INSERT INTO sys_tablefields_to_data_classification VALUES ( "image", 6);

-- ims_alternate
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_alternate", 6);

-- ims_inventory_records
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_inventory_records", 6);

-- ims_item_records
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_item_records", 6);

-- ims_optimization
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_optimization", 7);

-- ims_relation
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_relation", 6);

-- ims_reorder_level
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_reorder_level", 6);

-- ims_transfer_item
INSERT INTO sys_tablefields_to_data_classification VALUES ( "ims_transfer_item", 6);

-- incident
INSERT INTO sys_tablefields_to_data_classification VALUES ( "incident", 6);

-- landmark_location

-- lc_fields
INSERT INTO sys_tablefields_to_data_classification VALUES ( "lc_fields", 6);

-- lc_tmp_po
INSERT INTO sys_tablefields_to_data_classification VALUES ( "lc_tmp_po", 6);

-- location
INSERT INTO sys_tablefields_to_data_classification VALUES ( "location", 6);

-- location_details
INSERT INTO sys_tablefields_to_data_classification VALUES ( "location_details", 5);

-- messaging_group

-- old_passwords

-- org_main
INSERT INTO sys_tablefields_to_data_classification VALUES ( "org_main", 2);

-- password_event_log

-- person

-- person_deceased
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_deceased", 1);

-- person_details
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_details", 1);

-- person_missing
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_missing", 1);

-- person_physical
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_physical", 1);

-- person_status
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_status", 1);

-- person_to_pgroup
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_to_pgroup", 1);

-- person_to_report
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_to_report", 1);

-- person_uuid
INSERT INTO sys_tablefields_to_data_classification VALUES ( "person_uuid", 1);

-- pgroup
INSERT INTO sys_tablefields_to_data_classification VALUES ( "pgroup", 1);

-- phonetic_word

-- report_files

-- report_keywords

-- resource_to_incident
INSERT INTO sys_tablefields_to_data_classification VALUES ( "resource_to_incident", 6);

-- rms_fulfil
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_fulfil", 6);
-- rms_pledge
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_pledge", 6);
-- rms_plg_item
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_plg_item", 6);
-- rms_priority
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_priority", 6);
-- rms_req_item
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_req_item", 6);
-- rms_request
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_request", 6);
-- rms_status
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_status", 6);
-- rms_tmp_sch
INSERT INTO sys_tablefields_to_data_classification VALUES ( "rms_tmp_sch", 8);
-- sector
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sector", 2);

-- sessions
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sessions", 6);

-- sync_instance
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sync_instance", 6);

-- sys_data_classifications
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sys_data_classifications", 6);

-- sys_group_to_data_classification
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sys_group_to_data_classification", 6);

-- sys_group_to_module

-- sys_tablefields_to_data_classification
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sys_tablefields_to_data_classification", 6);

-- sys_user_groups
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sys_user_groups", 6);

-- sys_user_to_group
INSERT INTO sys_tablefields_to_data_classification VALUES ( "sys_user_to_group", 6);

-- unit

-- unit_type

-- user_preference

-- users
INSERT INTO sys_tablefields_to_data_classification VALUES ( "users", 6);

-- vm_access_classification_to_request

-- vm_access_constraint

-- vm_access_constraint_to_request

-- vm_access_request

-- vm_courier

-- vm_hours

-- vm_image

-- vm_mailbox

-- vm_message

-- vm_position

-- vm_position_active

-- vm_position_full

-- vm_positiontype

-- vm_projects

-- vm_projects_active

-- vm_vol_active

-- vm_vol_details

-- vm_vol_position

-- vm_vol_skills

-- ws_keys


-- INSERT DEFAULT GIS CLASSIFICATIONS

-- gis_layers
INSERT INTO gis_layers VALUES ('def_disaster_areas', 'Disaster Areas', '');
INSERT INTO gis_layers VALUES ('def_infrastructure', 'Infrastructure', '');
INSERT INTO gis_layers VALUES ('def_aid', 'Aid', '');
INSERT INTO gis_layers VALUES ('def_supplies', 'Supplies', '');
INSERT INTO gis_layers VALUES ('def_coordinators', 'Coordinators', '');
INSERT INTO gis_layers VALUES ('def_people', 'People', '');

-- gis_feature_class
-- Example INSERT INTO gis_feature_class VALUES ('feature_class_uuid', 'module_ref', 'name ', 'description', 'icon', 'color'); 
--   Default
INSERT INTO gis_feature_class VALUES ('default',        '', 'Generic Feature',   '', '', ''); 

-- Disaster Area | Categories [Disaster Area, various]
INSERT INTO gis_feature_class VALUES ('da_gen_lev_0',   '', 'Disaster Level Unknown',   '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_gen_lev_1',   '', 'Disaster Level Light',     '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_gen_lev_2',   '', 'Disaster Level Moderate',  '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_gen_lev_3',   '', 'Disaster Level Heavy',     '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_gen_lev_4',   '', 'Disaster Level Extreme',   '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_hurricane',   '', 'Hurricane Area',           '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_earthquake',  '', 'Earthquake Area',          '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_mudslide',    '', 'Mudslide Area',            '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_tsunami',     '', 'Tsunami Area',             '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_disease',     '', 'Disease Area',             '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_war',         '', 'War Area',                 '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_famine',      '', 'Famine Area',              '', '', ''); 
INSERT INTO gis_feature_class VALUES ('da_drought',     '', 'Drought Area',             '', '', ''); 

-- Camps | Categories [Infrastructure, Camp] !!! USED BY CAMP REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('cr_camp',        'cr', 'Camp',                   '', '', ''); 
INSERT INTO gis_feature_class VALUES ('cr_camp_ngo',    'cr', 'Camp [NGO]',             '', '', ''); 
INSERT INTO gis_feature_class VALUES ('cr_camp_gov',    'cr', 'Camp [Goverment]',       '', '', ''); 
INSERT INTO gis_feature_class VALUES ('cr_camp_tmp',    'cr', 'Camp [Temporary]',       '', '', ''); 

-- Houseing | Categories [Infrastructure, Houseing] !!! USED BY HOUSING REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('hr_house_dmg_0', 'hr', 'House [Unknown Damage]',  '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_house_dmg_1', 'hr', 'House [Light Damage]',   '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_house_dmg_2', 'hr', 'House [Moderate Damage]','', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_house_dmg_3', 'hr', 'House [Heavy Damage]',   '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_house_dmg_4', 'hr', 'House [Extreme Damage]', '', '', ''); 

-- Sites  | Categories [Infrastructure, Sites] !!! USED BY HOUSING REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('hr_site_dmg_0',  'hr', 'Site [Unknown Damage]',  '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_site_dmg_1',  'hr', 'Site [Light Damage]',    '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_site_dmg_2',  'hr', 'Site [Moderate Damage]', '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_site_dmg_3',  'hr', 'Site [Heavy Damage]',    '', '', ''); 
INSERT INTO gis_feature_class VALUES ('hr_site_dmg_4',  'hr', 'Site [Extreme Damage]',  '', '', ''); 

-- Inventories | Categories [Infrastructure, Supplies, Inventories] !!! USED BY INVENTORY MANAGEMENT !!!
INSERT INTO gis_feature_class VALUES ('ims_inventory', 'ims', 'Inventory',              '', '', ''); 

-- Supplies | Categories [Infrastructure, Supplies]
INSERT INTO gis_feature_class VALUES ('sup_food',       '', 'Food Supplies',            '', '', ''); 
INSERT INTO gis_feature_class VALUES ('sup_water',      '', 'Water Supplies',           '', '', ''); 
INSERT INTO gis_feature_class VALUES ('sup_meds',       '', 'Medical Supplies',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('sup_shelter',    '', 'Shelter Supplies',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('sup_cook',       '', 'Cooking/Fire Supplies',    '', '', ''); 
INSERT INTO gis_feature_class VALUES ('sup_waste',      '', 'Waste Disposal Supplies',  '', '', ''); 

-- Aid Points | Categories [Infrastructure, Aid]
INSERT INTO gis_feature_class VALUES ('ap_fstaid',      '', 'First Aid',                '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ap_hosp',        '', 'Hospital',                 '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ap_firedep',     '', 'Fire Department',          '', '', ''); 

--  Vehicles
INSERT INTO gis_feature_class VALUES ('veh_convy',      '', 'Convoy',                   '', '', '');

-- Organisations  | Categories [Coordinators, Organisations] !!! USED BY ORGANISATION REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('or_org',         'or', 'Organisation',           '', '', ''); 
INSERT INTO gis_feature_class VALUES ('or_org_gov',     'or', 'Goverment Org',          '', '', ''); 
INSERT INTO gis_feature_class VALUES ('or_org_priv',    'or', 'Private Org',            '', '', ''); 
INSERT INTO gis_feature_class VALUES ('or_org_ngo',     'or', 'Internal NGO',           '', '', ''); 
INSERT INTO gis_feature_class VALUES ('or_org_ingo',    'or', 'International NGO',      '', '', ''); 
INSERT INTO gis_feature_class VALUES ('or_org_mngo',    'or', 'Multinational NGO',      '', '', ''); 

-- Persons  [People, Persons, various] !!! USED BY MISSING PERSON REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('ppl_indv_found', 'mpr', 'Person [Found]',        '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_indv_spot',  'mpr', 'Person [Spotted]',      '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_indv_known', 'mpr', 'Person [Last Known Location]', '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_ind_inj',    'mpr', 'Person [Injured]',      '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_ind_dead',   'mpr', 'Person [Dead]',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_ind_grave',  'mpr', 'Person [Grave]',        '', '', ''); 

-- Groups | Categories [People, Groups, various] !!! USED BY MISSING PERSON REGISTRY !!!
INSERT INTO gis_feature_class VALUES ('ppl_grp_found',  'mpr', 'Group [Found]',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_grp_spot',   'mpr', 'Group [Spotted]',       '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_grp_known',  'mpr', 'Group [Last Known Location]', '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_grp_inj',    'mpr', 'Group [Injured]',       '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_grp_dead',   'mpr', 'Group [Dead]',          '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ppl_grp_grave',  'mpr', 'Group [Mass Grave]',    '', '', ''); 

--   Rally Points | Categories [Rally_Points]
INSERT INTO gis_feature_class VALUES ('ryp_evac',       '', 'Evacuation Point',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ryp_resc',       '', 'Rescue Point',             '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ryp_meet',       '', 'Meeting Point',            '', '', ''); 
INSERT INTO gis_feature_class VALUES ('ryp_supply',     '', 'Supply Point',             '', '', ''); 

--   Routes | | Categories [Routes]
INSERT INTO gis_feature_class VALUES ('rot_evac',       '', 'Evacuation Route',         '', '', ''); 
INSERT INTO gis_feature_class VALUES ('rot_supply',     '', 'Supply Route',             '', '', ''); 

-- Specific | | Categories [Infrastructure, various]
INSERT INTO gis_feature_class VALUES ('fire_wall',      '', 'Fire Wall',                '', '', ''); 
INSERT INTO gis_feature_class VALUES ('flood_wall',     '', 'Flood Defences',           '', '', ''); 

-- gis_feature_to_layer
-- FIX without one feature in this table some sql statments will not work
INSERT INTO gis_feature_to_layer VALUES ('def_infrastructure', 'ims_inventory');

-- gis_feature_class_to_layer
-- Disaster Areas
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_hurricane');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_earthquake');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_mudslide');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_tsunami');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_disease');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_war');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_famine');
INSERT INTO gis_feature_class_to_layer VALUES ('def_disaster_areas', 'da_drought');

-- Infrastructure
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'cr_camp');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'cr_camp_ngo');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'cr_camp_gov');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'cr_camp_tmp');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_house_dmg_0');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_house_dmg_1');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_house_dmg_2');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_house_dmg_3');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_house_dmg_4');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_site_dmg_0');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_site_dmg_1');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_site_dmg_2');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_site_dmg_3');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'hr_site_dmg_4');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'ims_inventory');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_food');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_water');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_meds');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_shelter');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_cook');
INSERT INTO gis_feature_class_to_layer VALUES ('def_infrastructure', 'sup_waste');

-- Supplies
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'ims_inventory');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_food');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_water');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_meds');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_shelter');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_cook');
INSERT INTO gis_feature_class_to_layer VALUES ('def_supplies', 'sup_waste');

-- Coordinators
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org');
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org_gov');
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org_priv');
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org_ngo');
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org_ingo');
INSERT INTO gis_feature_class_to_layer VALUES ('def_coordinators', 'or_org_mngo');

-- People
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_indv_spot');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_indv_known');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_ind_inj');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_ind_dead');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_ind_grave');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_grp_found');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_grp_spot');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_grp_inj');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_grp_dead');
INSERT INTO gis_feature_class_to_layer VALUES ('def_people', 'ppl_grp_grave');

-- Person Registry

-- Address TYPES
INSERT INTO field_options VALUES('opt_address_type','home','Home');
INSERT INTO field_options VALUES('opt_address_type','work','Work');
INSERT INTO field_options VALUES('opt_address_type','temp','Temporary');
INSERT INTO field_options VALUES('opt_address_type','oth','Other');


-- Title
INSERT INTO field_options VALUES('opt_title','mr','Mr');
INSERT INTO field_options VALUES('opt_title','miss','Miss');
INSERT INTO field_options VALUES('opt_title','mrs','Mrs');
INSERT INTO field_options VALUES('opt_title','oth','Other');

-- Identity Type
INSERT INTO field_options VALUES('opt_identity_type','idcard','Identity Card Number');
INSERT INTO field_options VALUES('opt_identity_type','passport','Passport Number');
INSERT INTO field_options VALUES('opt_identity_type','drv_licence','Driving License Number');


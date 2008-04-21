DROP TABLE IF EXISTS `report_files`;
DROP TABLE IF EXISTS `report_keywords`;

create table report_files
	(rep_id varchar(100),
	file_name varchar(100),
	file_data longblob,
	t_stamp timestamp default current_timestamp on update current_timestamp,
	file_type varchar(10),
	file_size_kb double,
	title varchar(100));
create table report_keywords
	(rep_id varchar(100),
	keyword_key varchar(100),
	keyword varchar(100)	
	);

/* DYNAMIC REPORTS MODULE TABLES */
/* Created : 11-JUL-2007 - agnieszka.kulikowska@gmail.com
/* --------------------------------------------------------------------------*/


/*
* Main table of Dynamic Reports containing details on tables from Sahana database 
* which don't contain *confidential data (users names, passwords etc.) 
* and of those which contained data is useful for any kind of reports
*
* Last changed: 17-AUG-2007 - agnieszka.kulikowska@gmail.com
*/
DROP TABLE IF EXISTS dr_tables;
-- no reporting
CREATE TABLE dr_tables (
  table_name varchar(100) NOT NULL, /* names of tables which are good for reports*/
  usrfr_table_name varchar(150) NOT NULL, /* user-friendly names of those tables*/
  PRIMARY KEY  (table_name)
);

/*INSERT INTO `dr_tables` (`table_name`, `usrfr_table_name`) VALUES 
('landmark_location', 'Landmark locations'),
('incident', 'Incident name'),
('gis_location', 'Basic coordinates providing basic spatial functionality'),
('gis_feature', 'GIS main table'),
('gis_wiki', 'GIS-WikiMaps functionality'),
('contact', 'Contact Information for a person, org or camp'),
('user_preference', 'User Preferences'),
('sector', 'Information on the sector that org/group/person is involved in'),
('chronology', 'History of events on data'),
('location', 'Locations data'),
('location_details', 'Details on the location of person, camp or organization'),
('person_uuid', 'Person names'),
('identity_to_person', 'ID card numbers (passport/driving licence)'),
('person_details', 'Details on a person'),
('person_status', 'Person''s status'),
('person_physical', 'Physical details of a person'),
('person_missing', 'Details on a missing'),
('person_deceased', 'Details on a death'),
('person_to_report', 'Person who reported about someone'),
('pgroup', 'List of groups of people'),
('group_details', 'Description of the group'),
('person_to_pgroup', 'Person belonging to multiple groups'),
('resource_to_shelter', 'Person/group belonging to a shelter'),
('org_main', 'Information about an organization'),
('org_users', 'Organization users'),
('camp_general', 'Physical Details of Camps/Shelters'),
('camp_reg', 'Human Resource Details of Camps/Shelters'),
('camp_services', 'Services offered by camps'),
('camp_admin', 'Camp to Admin Mapping'),
('resource_to_incident', 'Resources to Incidents'),
('ct_catalogue', 'Catalogs and items'),
('ct_unit', 'Measurement units'),
('ct_unit_type', 'Measurement unit types'),
('ct_suppliers', 'Suppliers'),
('rms_request', 'Request details'),
('rms_req_item', 'Requested item details'),
('rms_priority', 'Request priority details'),
('rms_status', 'Request status'),
('rms_pledge', 'Request pledge'),
('rms_plg_item', 'Requested item pledge'),
('rms_fulfil', 'Request fulfil');

*/



/*
* Table containing details on fields of tables from Sahana database 
* which don't contain *confidential data (users names, passwords etc.) 
* and of those which contained data is useful for any kind of reports
*
* Last changed: 16-JUL-2007 - agnieszka.kulikowska@gmail.com
*/
DROP TABLE IF EXISTS dr_fields;
-- no reporting
CREATE TABLE dr_fields (
  field_name varchar(20) NOT NULL,  				
  table_name varchar(100) NOT NULL, 					
  usrfr_field_name varchar(150) NOT NULL, 	
  opt_field_type varchar(100) NOT NULL,			
  tab_for_key varchar(150) DEFAULT NULL,		
  field_for_key varchar(150) DEFAULT NULL,	
  PRIMARY KEY  (field_name, table_name),
  FOREIGN KEY (table_name) REFERENCES dr_tables(table_name)
);

/**
* Sample data for field types
*/
INSERT INTO field_options VALUES('opt_field_type','group','Grouping');
INSERT INTO field_options VALUES('opt_field_type','obs','Observed');
INSERT INTO field_options VALUES('opt_field_type','none','None');

/*
INSERT INTO `dr_fields` (`field_name`, `table_name`, `usrfr_field_name`, `opt_field_type`, `tab_for_key`, `field_for_key`) VALUES 

-- 'landmark_location' table
('landmark_uuid', 'landmark_location', 'Landmark unique id', 'obs', 'none', 'none'),
('name', 'landmark_location', 'Landmark name', 'obs', 'none', 'none'),
('opt_landmark_type', 'landmark_location', 'Landmark type', 'group', 'none', 'none'),
('description', 'landmark_location', 'Landmark description', 'obs', 'none', 'none'),
('comments', 'landmark_location', 'Landmark comments', 'obs', 'none', 'none'),
('gis_uid', 'landmark_location', 'GIS unique id', 'obs', 'none', 'none'),

-- 'incident' table
('incident_id', 'incident', 'Incident id', 'obs', 'none', 'none'),
('parent_id', 'incident', 'Parent id', 'obs', 'incident', 'incident_id'),
('search_id', 'incident', 'Search id', 'obs', 'none', 'none'),
('name', 'incident', 'Incident name', 'obs', 'none', 'none'),

-- 'gis_location' table
('poc_uuid', 'gis_location', 'Person/camp/organization location unique id', 'obs', 'none', 'none'),
('location_id', 'gis_location', 'Location id', 'obs', 'none', 'none'),
('opt_gis_mod', 'gis_location', 'GIS module option', 'obs', 'none', 'none'),
('map_northing', 'gis_location', 'Latitude of a location, Y Coordinate', 'obs', 'none', 'none'),
('map_easting', 'gis_location', 'Latitude of a location, X Coordinate', 'obs', 'none', 'none'),
-- ('map_projection', 'gis_location', '?', 'none'), field is not used
('opt_gis_marker', 'gis_location', 'Custom marker', 'obs', 'none', 'none'),
('gis_uid', 'gis_location', 'GIS unique id', 'obs', 'none', 'none'),

-- 'gis_feature' table
('feature_uuid', 'gis_feature', 'Spatial location key', 'obs', 'none', 'none'),
('poc_uuid', 'gis_feature', 'Person/camp/organization location id', 'obs', 'none', 'none'),
('feature_coords', 'gis_feature', 'Coordinates of feature type', 'obs', 'none', 'none'),
('entry_time', 'gis_feature', 'Entry time', 'obs', 'none', 'none'),

-- 'gis_wiki' table
('wiki_uuid', 'gis_wiki', 'Wiki unique id', 'obs', 'none', 'none'),
('gis_uuid', 'gis_wiki', 'GIS unique id', 'obs', 'gis_location', 'gis_uid'),
('name', 'gis_wiki', 'Name', 'obs', 'none', 'none'),
('description', 'gis_wiki', 'Description', 'obs', 'none', 'none'),
('opt_category', 'gis_wiki', 'Category', 'obs', 'none', 'none'),
('url', 'gis_wiki', 'URL', 'obs', 'none', 'none'),
('event_date', 'gis_wiki', 'Event date', 'obs', 'none', 'none'),
('placement_date', 'gis_wiki', 'Placement date', 'obs', 'none', 'none'),
('editable', 'gis_wiki', 'Possibility of edition', 'obs', 'none', 'none'),
('author', 'gis_wiki', 'Author', 'obs', 'none', 'none'),
('approved', 'gis_wiki', 'Is approved', 'obs', 'none', 'none'),

-- 'contact' table
('pgoc_uuid', 'contact', 'Person/group/org/camp unique id', 'obs', 'none', 'none'),
('opt_contact_type', 'contact', 'Contact type (phone/email/...)', 'group', 'none', 'none'),
('contact_value', 'contact', 'Phone number/adress/...', 'obs', 'none', 'none'),

-- 'user_preference' table
('p_uuid', 'user_preference', 'Person unique id', 'obs', 'none', 'none'),
('module_id', 'user_preference', 'Module id', 'obs', 'none', 'none'),
('pref_key', 'user_preference', 'Preferences key', 'obs', 'none', 'none'),
('value', 'user_preference', 'Preferences value', 'obs', 'none', 'none'),

-- 'sector' table
('pgoc_uuid', 'sector', 'Person/org/camp unique id', 'obs', 'none', 'none'),
('opt_sector', 'sector', 'Sector option', 'obs', 'none', 'none'),

-- 'chronology' table
('log_uuid', 'chronology', 'Log unique id', 'obs', 'none', 'none'),
('event_date', 'chronology', 'Event date', 'obs', 'none', 'none'),
('pgoc_uuid', 'chronology', 'Person/org/camp unique id', 'obs', 'none', 'none'),
('opt_cron_type', 'chronology', 'Type of event', 'obs', 'none', 'none'),
('module', 'chronology', 'Module', 'obs', 'none', 'none'),
('action', 'chronology', 'Action', 'obs', 'none', 'none'),
('user_uuid', 'chronology', 'User unique id', 'obs', 'none', 'none'),
('comments', 'chronology', 'Description of changes', 'obs', 'none', 'none'),
('details', 'chronology', 'Detailed description', 'obs', 'none', 'none'),

-- 'location' table
('loc_uuid', 'location', 'Location unique id', 'obs', 'none', 'none'),
('parent_id', 'location', 'Parent location id', 'obs', 'none', 'none'),
('opt_location_type', 'location', 'Loaction type', 'group', 'none', 'none'),
('name', 'location', 'Name', 'obs', 'none', 'none'),
('iso_code', 'location', 'Iso code', 'obs', 'none', 'none'),
('description', 'location', 'Loaction description', 'obs', 'none', 'none'),

-- 'location_details' table
('poc_uuid', 'location_details', 'Person/camp/organization location id', 'obs', 'none', 'none'),
('location_id', 'location_details', 'Location id', 'obs', 'location', 'loc_uuid'),
('opt_person_loc_type', 'location_details', 'Person location type (home/impact/current)', 'obs', 'none', 'none'),
('address', 'location_details', 'Address', 'obs', 'none', 'none'),
('postcode', 'location_details', 'Postal/ZIP code', 'obs', 'none', 'none'),
('long_lat', 'location_details', 'GPS location', 'obs', 'none', 'none'),

-- 'person_uuid' table
('p_uuid', 'person_uuid', 'Person unique id', 'obs', 'none', 'none'),
('full_name', 'person_uuid', 'Full name', 'obs', 'none', 'none'),
('family_name', 'person_uuid', 'Family name', 'obs', 'none', 'none'),
('l10n_name', 'person_uuid', 'Localized version of name', 'obs', 'none', 'none'),
('custom_name', 'person_uuid', 'Extra field', 'obs', 'none', 'none'),

-- 'identity_to_person' table
('p_uuid', 'identity_to_person', 'Person unique id', 'obs', 'person_uuid', 'p_uuid'),
('serial', 'identity_to_person', 'Serial number', 'obs', 'none', 'none'),
('opt_id_type', 'identity_to_person', 'ID type', 'group', 'none', 'none'),

-- 'person_details' table
('p_uuid', 'person_details', 'Person unique id', 'obs', 'person_uuid', 'p_uuid'),
('next_kin_uuid', 'person_details', 'Next of kin unique id', 'obs', 'none', 'none'),
('birth_date', 'person_details', 'Birth date', 'obs', 'none', 'none'),
('opt_age_group', 'person_details', 'Age group the person belongs to', 'group', 'none', 'none'),
('relation', 'person_details', 'Relation between the person and next of kin', 'obs', 'none', 'none'),
('opt_country', 'person_details', 'Country', 'group', 'none', 'none'),
('opt_race', 'person_details', 'Race', 'group', 'none', 'none'),
('opt_religion', 'person_details', 'Religion', 'group', 'none', 'none'),
('opt_marital_status', 'person_details', 'Marital status', 'group', 'none', 'none'),
('opt_gender', 'person_details', 'Gender', 'group', 'none', 'none'),
('occupation', 'person_details', 'Occupation', 'obs', 'none', 'none'),

-- 'person_status' table
('p_uuid', 'person_status', 'Person unique id', 'obs', 'none', 'none'),
('isReliefWorker', 'person_status', 'Is Person a relief worker', 'obs', 'none', 'none'),
('opt_status', 'person_status', 'Person''s status: missing/ingured/...', 'group', 'none', 'none'),
('updated', 'person_status', 'Time of last update', 'obs', 'none', 'none'),
('isvictim', 'person_status', 'Is the Person a victim', 'obs', 'none', 'none'),

-- 'person_physical' table
('p_uuid', 'person_physical', 'Person unique id', 'obs', 'person_uuid', 'p_uuid'),
('opt_blood_type', 'person_physical', 'Blood type', 'group', 'none', 'none'),
('height', 'person_physical', 'Height', 'obs', 'none', 'none'),
('weight', 'person_physical', 'Weight', 'obs', 'none', 'none'),
('opt_eye_color', 'person_physical', 'Eye color', 'group', 'none', 'none'),
('opt_skin_color', 'person_physical', 'Skin color', 'group', 'none', 'none'),
('opt_hair_color', 'person_physical', 'Hair color', 'group', 'none', 'none'),
('injuries', 'person_physical', 'Injuries', 'obs', 'none', 'none'),
('comments', 'person_physical', 'Comments', 'obs', 'none', 'none'),

-- 'person_missing' table
('p_uuid', 'person_missing', 'Person unique id', 'obs', 'person_uuid', 'p_uuid'),
('last_seen', 'person_missing', 'Last seen', 'obs', 'none', 'none'),
('last_clothing', 'person_missing', 'Last wearing clothing', 'obs', 'none', 'none'),
('comments', 'person_missing', 'Comments', 'obs', 'none', 'none'),

-- 'person_deceased' table
('p_uuid', 'person_deceased', 'Person unique id', 'obs', 'person_uuid', 'p_uuid'),
('details', 'person_deceased', 'Details on a death', 'obs', 'none', 'none'),
('date_of_death', 'person_deceased', 'Date of death', 'obs', 'none', 'none'),
('location', 'person_deceased', 'Location of death', 'obs', 'location', 'loc_uuid'),
('place_of_death', 'person_deceased', 'Place of death', 'obs', 'none', 'none'),
('comments', 'person_deceased', 'Comments', 'obs', 'none', 'none'),

-- 'person_to_report' table
('p_uuid', 'person_to_report', 'Person who reported id', 'obs', 'person_uuid', 'p_uuid'),
('rep_uuid', 'person_to_report', 'Person about reported id', 'obs', 'person_uuid', 'p_uuid'),
('relation', 'person_to_report', 'Relation between persons', 'obs', 'none', 'none'),

-- 'pgroup' table
('g_uuid', 'pgroup', 'Group unique id', 'obs', 'none', 'none'),
('opt_group_type', 'pgroup', 'Group type', 'group', 'none', 'none'),

-- 'group_details' table
('g_uuid', 'group_details', 'Group unique id', 'obs', 'none', 'none'),
('head_uuid', 'group_details', 'Description of the group', 'obs', 'person_uuid', 'p_uuid'),
('no_of_adult_males', 'group_details', 'Number of adult man', 'obs', 'none', 'none'),
('no_of_adult_females', 'group_details', 'Number of adult woman', 'obs', 'none', 'none'),
('no_of_children', 'group_details', 'Number of children', 'obs', 'none', 'none'),
('no_displaced', 'group_details', 'Number of displaced', 'obs', 'none', 'none'),
('no_missing', 'group_details', 'Number of missing', 'obs', 'none', 'none'),
('no_dead', 'group_details', 'Number of death', 'obs', 'none', 'none'),
('no_rehabilitated', 'group_details', 'Number of rehabilitated', 'obs', 'none', 'none'),
('checklist', 'group_details', 'Checklist', 'obs', 'none', 'none'),
('description', 'group_details', 'Description', 'obs', 'none', 'none'),

-- 'person_to_pgroup' table
('p_uuid', 'person_to_pgroup', 'Person unique id', 'obs', 'none', 'none'),
('g_uuid', 'person_to_pgroup', 'Group unique id', 'obs', 'none', 'none'),

-- 'resource_to_shelter' table
-- ('x_uuid', 'resource_to_shelter', '?', 'none'),
('c_uuid', 'resource_to_shelter', 'Camp/Shelter unique id', 'obs', 'camp_general', 'c_uuid'),

-- 'org_main' table
('o_uuid', 'org_main', 'Organization unique id', 'obs', 'none', 'none'),
('parent_id', 'org_main', 'Parent id', 'obs', 'org_main', 'o_uuid'),
('name', 'org_main', 'Name', 'obs', 'none', 'none'),
('opt_org_type', 'org_main', 'Organization type', 'group', 'none', 'none'),
-- ('reg_no', 'org_main', '?', 'none'),
-- ('man_power', 'org_main', '?', 'none'),
('equipment', 'org_main', 'Equipment', 'obs', 'none', 'none'),
('resources', 'org_main', 'Resources', 'obs', 'none', 'none'),
('privacy', 'org_main', 'Privacy', 'obs', 'none', 'none'),
('archived', 'org_main', 'Archived', 'obs', 'none', 'none'),

-- 'org_users' table
('o_uuid', 'org_users', 'Organization unique id', 'obs', 'org_main', 'o_uuid'),
('user_id', 'org_users', 'Person unique id', 'obs', 'users', 'p_uuid'),

-- 'camp_general' table
('c_uuid', 'camp_general', 'Camp/Shelter unique id', 'obs', 'none', 'none'),
('name', 'camp_general', 'Camp/Shelter name', 'obs', 'none', 'none'),
('location_id', 'camp_general', 'Location unique id', 'obs', 'location', 'loc_uuid'),
('opt_camp_type', 'camp_general', 'Camp/Shelter type', 'obs', 'none', 'none'),
('address', 'camp_general', 'Camp/Shelter address', 'obs', 'none', 'none'),
('capacity', 'camp_general', 'Camp/Shelter capacity', 'obs', 'none', 'none'),
('shelters', 'camp_general', 'Number of shelters', 'obs', 'none', 'none'),
('area', 'camp_general', 'Camp/Shelter area', 'obs', 'none', 'none'),
('personsPerShelter', 'camp_general', 'Current number of people in a Camp/Shelter', 'obs', 'none', 'none'),

-- 'camp_reg' table
('c_uuid', 'camp_reg', 'Camp/Shelter unique id', 'obs', 'none', 'none'),
('admin_name', 'camp_reg', 'Camp/Shelter administrator name', 'obs', 'none', 'none'),
('admin_no', 'camp_reg', 'Camp/Shelter administrators number', 'obs', 'none', 'none'),
('men', 'camp_reg', 'Number of man in Camp/Shelter', 'obs', 'none', 'none'),
('women', 'camp_reg', 'Number of woman in Camp/Shelter', 'obs', 'none', 'none'),
('family', 'camp_reg', 'Number of families in Camp/Shelter', 'obs', 'none', 'none'),
('children', 'camp_reg', 'Number of children in Camp/Shelter', 'obs', 'none', 'none'),
('total', 'camp_reg', 'Total number of people in Camp/Shelter', 'obs', 'none', 'none'),

-- 'camp_services' table
('c_uuid', 'camp_services', 'Camp/Shelter unique id', 'obs', 'none', 'none'),
('opt_camp_service', 'camp_services', 'Service offered by a Camp/Shelter', 'group', 'none', 'none'),
('value', 'camp_services', 'Is this service available in a Camp/Shelter', 'obs', 'none', 'none'),

-- 'camp_admin' table
('c_uuid', 'camp_admin', 'Camp/Shelter unique id', 'obs', 'none', 'none'),
('contact_puuid', 'camp_admin', 'Camp/Shelter administrator contact', 'obs', 'none', 'none'),

-- 'resource_to_incident' table
('incident_id', 'resource_to_incident', 'Incident id', 'obs', 'incident', 'incident_id'),
-- ('x_uuid', 'resource_to_incident', 'Resource id', 'none'),

-- 'ct_catalogue' table
('ct_uuid', 'ct_catalogue', 'Catalog unique id', 'obs', 'none', 'none'),
('parentid', 'ct_catalogue', 'Parent id', 'obs', 'none', 'none'),
('name', 'ct_catalogue', 'Catalog name', 'obs', 'none', 'none'),
('description', 'ct_catalogue', 'Catalog description', 'obs', 'none', 'none'),
('final_flag', 'ct_catalogue', 'Catalog final fleg', 'obs', 'none', 'none'),
('serial', 'ct_catalogue', 'Catalog serial', 'obs', 'none', 'none'),
('keyword', 'ct_catalogue', 'Catalog keyword', 'obs', 'none', 'none'),

-- 'ct_unit' table
('unit_type_uuid', 'ct_unit', 'Unit type unique id', 'obs', 'none', 'none'),
('unit_uuid', 'ct_unit', 'Unit unique id', 'obs', 'none', 'none'),
('name', 'ct_unit', 'Unit name', 'obs', 'none', 'none'),
('base_flag', 'ct_unit', 'Unit base flag', 'obs', 'none', 'none'),
('multiplier', 'ct_unit', 'Unit multiplier', 'obs', 'none', 'none'),

-- 'ct_unit_type' table
('unit_type_uuid', 'ct_unit_type', 'Unit type unique id', 'obs', 'none', 'none'),
('name', 'ct_unit_type', 'Unit name', 'obs', 'none', 'none'),
('description', 'ct_unit_type', 'Unit description', 'obs', 'none', 'none'),

-- 'ct_suppliers' table
('ct_uuid', 'ct_suppliers', 'Catalog unique id', 'obs', 'none', 'none'),
('supplier', 'ct_suppliers', 'Supplier', 'obs', 'none', 'none'),

-- 'rms_request' table
('req_uuid', 'rms_request', 'Request unique id', 'obs', 'person_uuid', 'p_uuid'),
('reqstr_uuid', 'rms_request', 'Requester unique id', 'obs', 'none', 'none'),
('loc_uuid', 'rms_request', 'Location unique id', 'obs', 'location_details', 'poc_uuid'),
('req_date', 'rms_request', 'Request date', 'obs', 'none', 'none'),
('status', 'rms_request', 'Request status', 'obs', 'none', 'none'),
('user_id', 'rms_request', 'Person unique id', 'obs', 'users', 'p_uuid'),

-- 'rms_req_item' table
('item_uuid', 'rms_req_item', 'Item unique id', 'obs', 'ct_catalogue', 'ct_uuid'),
('quantity', 'rms_req_item', 'Item quantity', 'obs', 'none', 'none'),
('pri_uuid', 'rms_req_item', 'Item primary key', 'obs', 'rms_priority', 'pri_uuid'),
('req_uuid', 'rms_req_item', 'Request unique id', 'obs', 'rms_request', 'req_uuid'),
('unit', 'rms_req_item', 'Units', 'obs', 'none', 'none'),

-- 'rms_priority' table
('pri_uuid', 'rms_priority', 'Priority unique id', 'obs', 'none', 'none'),
('priority', 'rms_priority', 'Priority', 'obs', 'none', 'none'),
('pri_desc', 'rms_priority', 'Priority description', 'obs', 'none', 'none'),

-- 'rms_status' table
('stat_uuid', 'rms_status', 'Request status unique id', 'obs', 'none', 'none'),
('status', 'rms_status', 'Status', 'obs', 'none', 'none'),
('stat_desc', 'rms_status', 'Status description', 'obs', 'none', 'none'),

-- 'rms_pledge' table
('plg_uuid', 'rms_pledge', 'Request pledge unique id', 'obs', 'none', 'none'),
('donor_uuid', 'rms_pledge', 'Donator unique id', 'obs', 'person_uuid', 'p_uuid'),
('plg_date', 'rms_pledge', 'Request pledge date', 'obs', 'none', 'none'),
('status', 'rms_pledge', 'Pledge status', 'obs', 'none', 'none'),
('user_id', 'rms_pledge', 'Person unique id', 'obs', 'users', 'p_uuid'),

-- 'rms_plg_item' table
('item_uuid', 'rms_plg_item', 'Catalog unique id', 'obs', 'ct_catalogue', 'ct_uuid'),
('quantity', 'rms_plg_item', 'Requested item pledge quantity', 'obs', 'none', 'none'),
('status', 'rms_plg_item', 'Request pledge status', 'obs', 'none', 'none'),
('plg_uuid', 'rms_plg_item', 'Request pledge unique id', 'obs', 'rms_pledge', 'plg_uuid'),
('unit', 'rms_plg_item', 'Requested pledge units', 'obs', 'none', 'none'),

-- 'rms_fulfil' table
('req_uuid', 'rms_fulfil', 'Request unique id', 'obs', 'rms_request', 'req_uuid'),
('item_uuid', 'rms_fulfil', 'Catalog unique id', 'obs', 'ct_catalogue', 'ct_uuid'),
('plg_uuid', 'rms_fulfil', 'Request pledge unique id', 'obs', 'rms_pledge', 'plg_uuid'),
('quantity', 'rms_fulfil', 'Requested item pledge fulfill quantity', 'obs', 'none', 'none'),
('ff_date', 'rms_fulfil', 'Requested item pledge fulfilled date', 'obs', 'none', 'none'),
('user_id', 'rms_fulfil', 'Person unique id', 'obs', 'users', 'p_uuid');
*/

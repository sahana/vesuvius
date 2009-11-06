--
-- Table structure for table vm_courier
--
-- drop tables
DROP TABLE IF EXISTS vm_vol_skills;
DROP TABLE IF EXISTS vm_vol_details;
DROP TABLE IF EXISTS vm_projects;
DROP TABLE IF EXISTS vm_vol_position;
DROP TABLE IF EXISTS vm_positiontype;
DROP TABLE IF EXISTS vm_position;
DROP TABLE IF EXISTS vm_message;
DROP TABLE IF EXISTS vm_mailbox;
DROP TABLE IF EXISTS vm_image;
DROP TABLE IF EXISTS vm_hours;
DROP TABLE IF EXISTS vm_courier;


CREATE TABLE vm_courier (
  message_id bigint(40) NOT NULL default 0,
  to_id varchar(60) NOT NULL default '',
  from_id varchar(60) NOT NULL default '',
  PRIMARY KEY  (message_id,to_id,from_id)
);

-- --------------------------------------------------------

--
-- Table structure for table vm_hours
--

CREATE TABLE vm_hours (
  p_uuid		varchar(60) NOT NULL,
  proj_id		varchar(60) NOT NULL,
  pos_id		varchar(60) NOT NULL,
  shift_start	datetime NOT NULL,
  shift_end		datetime NOT NULL,
  key p_uuid (p_uuid,proj_id,pos_id)
);

-- --------------------------------------------------------

--
-- Table structure for table vm_image
--

CREATE TABLE vm_image (
  img_uuid varchar(60) NOT NULL,
  original blob NOT NULL,
  image_data blob NOT NULL,
  thumb_data blob NOT NULL,
  p_uuid varchar(60) NOT NULL,
  date_added datetime NOT NULL,
  width smallint(6) NOT NULL,
  height smallint(6) NOT NULL,
  thumb_width smallint(6) NOT NULL,
  thumb_height smallint(6) NOT NULL,
  mime_type varchar(60) NOT NULL,
  name varchar(60) NOT NULL,
  PRIMARY KEY  (img_uuid),
  KEY p_uuid (p_uuid)
);

-- --------------------------------------------------------

--
-- Table structure for table vm_mailbox
--

CREATE TABLE vm_mailbox (
  p_uuid varchar(60) NOT NULL default '',
  message_id bigint(40) NOT NULL default 0,
  box int(1) NOT NULL default 0,
  checked int(1) default 0,
  PRIMARY KEY  (p_uuid,message_id,box)
);

-- --------------------------------------------------------

--
-- Table structure for table vm_message
--

CREATE TABLE vm_message (
  message_id bigint(40) NOT NULL auto_increment,
  message text,
  time timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (message_id)
);

-- --------------------------------------------------------


CREATE TABLE IF NOT EXISTS vm_position (
  pos_id varchar(60) NOT NULL,
  proj_id varchar(60) NOT NULL,
  ptype_id varchar(60) NOT NULL,
  title varchar(30) NOT NULL,
  slots smallint(6) NOT NULL,
  description text NOT NULL,
  status set('active','retired') NOT NULL default 'active',
  payrate double default 0,
  PRIMARY KEY  (pos_id),
  KEY proj_id (proj_id),
  KEY pos_id (ptype_id)
);


-- --------------------------------------------------------


--
-- Table structure for table vm_positiontype
--

CREATE TABLE vm_positiontype (
  ptype_id varchar(60) NOT NULL,
  title varchar(20) NOT NULL,
  description varchar(300) NOT NULL,
  skill_code varchar(20) NOT NULL,
  PRIMARY KEY  (ptype_id)
);

INSERT INTO vm_positiontype (ptype_id, title, description, skill_code) VALUES
('smgr', 'Site Manager', 'Site Manager', 'MGR');

-- --------------------------------------------------------

--
-- Table structure for table vm_vol_position
--

CREATE TABLE vm_vol_position (
  p_uuid varchar(60) NOT NULL default '',
  pos_id varchar(60) NOT NULL,
  status set('active','retired') default 'active',
  payrate double default NULL,
  hours bigint(20) default NULL,
  task varchar(20) default NULL,
  date_assigned datetime NOT NULL,
  PRIMARY KEY  (p_uuid,pos_id)
);


--
-- Table structure for table vm_projects
--


CREATE TABLE IF NOT EXISTS vm_projects (
  proj_id bigint(20) NOT NULL auto_increment,
  name varchar(50) default NULL,
  location_id varchar(60) default NULL,
  start_date date default NULL,
  end_date date default NULL,
  description text NOT NULL,
  status set('active','completed') NOT NULL default 'active',
  PRIMARY KEY  (proj_id)
);

-- --------------------------------------------------------

--
-- Table structure for table vm_vol_details
--

CREATE TABLE vm_vol_details (
  p_uuid varchar(60) NOT NULL default 0,
  org_id varchar(60) NOT NULL default 0,
  photo blob NOT NULL,
  date_avail_start date NOT NULL ,
  date_avail_end date NOT NULL ,
  hrs_avail_start time NOT NULL ,
  hrs_avail_end time NOT NULL ,
  status set('active','retired') NOT NULL default 'active',
  special_needs TEXT,
  PRIMARY KEY  (p_uuid)
);


-- --------------------------------------------------------

--
-- Table structure for table vm_vol_skills
--

CREATE TABLE vm_vol_skills (
  p_uuid varchar(60) default NULL,
  opt_skill_code varchar(100) default NULL,
  status set('approved','unapproved', 'denied') NOT NULL default 'unapproved'
);

--
-- Add emergency contact phone number
--

INSERT INTO field_options(field_name, option_code, option_description) VALUES('opt_contact_type', 'emphone', 'Emergency Phone Contact');


--
-- Insert skill information
--

INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI2',      'General Skills-Animals-Animal Control Vehicles');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI1',      'General Skills-Animals-Animal Handling');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI3',      'General Skills-Animals-Grief Counseling');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI4',      'General Skills-Animals-Horse Trailers');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI5',      'General Skills-Animals-Livestock Vehicles');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI8',      'General Skills-Animals-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI7',      'General Skills-Animals-Veterinarian');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ANI6',      'General Skills-Animals-Veterinary Technician');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT2',      'General Skills-Automotive-Body Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT1',      'General Skills-Automotive-Engine Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT3',      'General Skills-Automotive-Lights, Electrical');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT6',      'General Skills-Automotive-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT4',      'General Skills-Automotive-Tire Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'AUT5',      'General Skills-Automotive-Wheel and Brake Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'BAB1',      'General Skills-Baby and Child Care-Aide');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'BAB2',      'General Skills-Baby and Child Care-Leader');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'BAB3',      'General Skills-Baby and Child Care-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON1',      'General Skills-Construction Services-Glass Service');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON2',      'General Skills-Construction Services-House Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON3',      'General Skills-Construction Services-Inspection, B');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON6',      'General Skills-Construction Services-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON4',      'General Skills-Construction Services-Roofing');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'CON5',      'General Skills-Construction Services-Window Repair');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ELE1',      'General Skills-Electrical-External Wiring');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ELE2',      'General Skills-Electrical-Internal Wiring');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'ELE3',      'General Skills-Electrical-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'FOO1',      'General Skills-Food Service-Cooking');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'FOO2',      'General Skills-Food Service-Directing');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'FOO5',      'General Skills-Food Service-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'FOO3',      'General Skills-Food Service-Preparing');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'FOO4',      'General Skills-Food Service-Serving');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ1',      'General Skills-Hazardous Materials-Asbestos');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ2',      'General Skills-Hazardous Materials-Chemicals');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ3',      'General Skills-Hazardous Materials-Explosives');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ4',      'General Skills-Hazardous Materials-Flammables');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ5',      'General Skills-Hazardous Materials-Gases');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ6',      'General Skills-Hazardous Materials-Identification');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ8',      'General Skills-Hazardous Materials-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'HAZ7',      'General Skills-Hazardous Materials-Radioactive ');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF1',      'General Skills-Information Services-Book Restorati');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF2',      'General Skills-Information Services-Computer');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF3',      'General Skills-Information Services-Data Entry');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF4',      'General Skills-Information Services-Hardware (Comp');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF7',      'General Skills-Information Services-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF5',      'General Skills-Information Services-Software (Comp');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'INF6',      'General Skills-Information Services-Telephone Repa');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED1',      'General Skills-Medical-Assist to Physician');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED2',      'General Skills-Medical-Counseling');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED3',      'General Skills-Medical-Dentist');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED4',      'General Skills-Medical-First Aid');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED5',      'General Skills-Medical-Medical, Ambulance');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED6',      'General Skills-Medical-Nurse');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED9',      'General Skills-Medical-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED7',      'General Skills-Medical-Physician');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MED8',      'General Skills-Medical-Technician');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'PLU2',      'General Skills-Plumbing-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'PLU1',      'General Skills-Plumbing-Pumping-With Pump');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'PLU3',      'General Skills-Plumbing-Pumping-Without Pump');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'TRE1',      'General Skills-Tree-Evaluation of Needs');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'TRE4',      'General Skills-Tree-Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'TRE2',      'General Skills-Tree-Removal of Trees');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'TRE3',      'General Skills-Tree-Trimming of Trees');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS1',      'Unskilled-Other-Baby Care Help');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS2',      'Unskilled-Other-Clerical');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS3',      'Unskilled-Other-Food Help');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS4',      'Unskilled-Other-Heavy Labor (Moving, Erecting Tent');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS5',      'Unskilled-Other-Light Labor (Cleanup)');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS6',      'Unskilled-Other-Messenger (Local People Preferred)');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'UNS7',      'Unskilled-Other-Miscellaneous');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH1',      'Resources-Vehicle-Own Aircraft');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH5',      'Resources-Building Aide-Own Backhoe');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH2',      'Resources-Building Aide-Own Bulldozer');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH3',      'Resources-Building Aide-Own Crane');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH4',      'Resources-Building Aide-Own Forklift');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH7',      'Resources-Building Aide-Own Heavy Equipment');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH6',      'Resources-Vehicle-Own Medical; Ambulance');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH13',     'Resources-Vehicle-Own Other');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH8',      'Resources-Vehicle-Own Refrigerated');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH9',      'Resources-Vehicle-Own Steamshovel');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH10',     'Resources-Vehicle-Own Truck');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH11',     'Resources-Vehicle-Own Van, Car');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'VEH12',     'Resources-Vehicle-Own Boat(s)');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WAR1',      'Resources-Warehouse-Forklift');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WAR2',      'Resources-Warehouse-General');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WAR3',      'General Skills-Warehouse-Management');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT1',      'Unskilled-With Tools-with Brooms');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT2',      'Unskilled-With Tools-with Carpentry Tools');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT7',      'Unskilled-With Tools-with Other Tools');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT3',      'Unskilled-With Tools-with Pump, Small');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT4',      'Unskilled-With Tools-with Saws, Chainsaw');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT5',      'Unskilled-With Tools-with Wheelbarrow');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'WIT6',      'Unskilled-With Tools-with Yard Tools');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST1',     'Restriction-No Heavy Lifting');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST2',     'Restriction-Can not drive');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST1',     'Restriction-No Heavy Lifting');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST2',     'Restriction-Can not drive');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST3',     'Restriction-Can not swim');
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'REST4',     'Restriction-Handicapped');
-- Special skill type for site managers:
INSERT INTO field_options (field_name, option_code, option_description) VALUES ('opt_skill_type', 'MGR',       'Site Manager');





--
-- Dumping data for table sys_tablefields_to_data_classification
--

INSERT INTO sys_tablefields_to_data_classification (table_field, level_id) VALUES
('vm_access_classification_to_request', 6),
('vm_access_constraint', 6),
('vm_access_constraint_to_request', 6),
('vm_access_request', 6),
('vm_courier', 1),
('vm_hours', 1),
('vm_image', 1),
('vm_mailbox', 1),
('vm_message', 1),
('vm_position', 2),
('vm_positiontype', 2),
('vm_position_active', 2),
('vm_position_full', 2),
('vm_pos_volunteercount', 2),
('vm_projects', 2),
('vm_projects_active', 2),
('vm_vol_active', 1),
('vm_vol_assignment', 2),
('vm_vol_assignment_active', 2),
('vm_vol_details', 1),
('vm_vol_position', 2),
('vm_vol_skills', 2);

-- --------------------------------------------------------

--
-- Table structure for table vm_access_classification_to_request
--

CREATE TABLE vm_access_classification_to_request (
  request_id int(11) NOT NULL default 0,
  table_name varchar(200) NOT NULL default '',
  crud varchar(4) NOT NULL default '',
  PRIMARY KEY  (request_id,table_name,crud)
);

--
-- Dumping data for table vm_access_classification_to_request
--

INSERT INTO vm_access_classification_to_request (request_id, table_name, crud) VALUES
(2, 'identity_to_person', 'ru'),
(2, 'person_uuid', 'ru'),
(2, 'vm_vol_details', 'ru'),
(2, 'vm_vol_skills', 'ru'),
(3, 'vm_vol_details', 'u'),
(3, 'vm_vol_position', 'u'),
(6, 'vm_vol_details', 'u'),
(6, 'vm_vol_position', 'u'),
(7, 'location_details', 'r'),
(7, 'person_uuid', 'r'),
(7, 'vm_vol_assignment', 'r'),
(7, 'vm_vol_details', 'r'),
(8, 'identity_to_person', 'r'),
(8, 'location_details', 'r'),
(8, 'person_uuid', 'r'),
(8, 'vm_vol_assignment', 'r'),
(8, 'vm_vol_details', 'r'),
(9, 'location_details', 'r'),
(9, 'person_uuid', 'r'),
(9, 'vm_vol_assignment', 'r'),
(9, 'vm_vol_details', 'r'),
(13, 'location_details', 'r'),
(13, 'person_uuid', 'r'),
(13, 'vm_vol_assignment', 'r'),
(13, 'vm_vol_details', 'r'),
(13, 'vm_vol_skills', 'r'),
(14, 'location_details', 'r'),
(14, 'person_uuid', 'r'),
(14, 'vm_vol_assignment', 'r'),
(14, 'vm_vol_details', 'r'),
(14, 'vm_vol_skills', 'r'),
(18, 'person_uuid', 'r'),
(18, 'vm_hours', 'r'),
(18, 'vm_projects', 'r'),
(18, 'vm_vol_assignment', 'r'),
(18, 'vm_vol_details', 'r'),
(19, 'person_uuid', 'r'),
(19, 'vm_hours', 'r'),
(19, 'vm_projects', 'r'),
(19, 'vm_vol_assignment', 'r'),
(19, 'vm_vol_details', 'r'),
(20, 'person_uuid', 'r'),
(20, 'vm_hours', 'r'),
(20, 'vm_projects', 'r'),
(20, 'vm_vol_assignment', 'r'),
(20, 'vm_vol_details', 'r'),
(22, 'field_options', 'cru'),
(23, 'vm_vol_skills', 'cru'),
(24, 'vm_hours', 'c'),
(26, 'vm_projects', 'r'),
(26, 'vm_vol_assignment', 'r'),
(27, 'vm_position', 'c'),
(27, 'vm_positiontype', 'r'),
(27, 'vm_projects', 'c'),
(27, 'vm_vol_position', 'c'),
(28, 'vm_projects', 'u'),
(29, 'vm_position', 'cu'),
(29, 'vm_positiontype', 'cu'),
(29, 'vm_projects', 'cu'),
(29, 'vm_vol_position', 'cu'),
(30, 'vm_position', 'u'),
(30, 'vm_positiontype', 'u'),
(30, 'vm_projects', 'u'),
(31, 'vm_position', 'u'),
(31, 'vm_projects', 'u'),
(31, 'vm_vol_position', 'u'),
(32, 'location_details', 'r'),
(32, 'person_uuid', 'r'),
(32, 'vm_position', 'r'),
(32, 'vm_vol_details', 'r'),
(32, 'vm_vol_position', 'cru'),
(33, 'vm_proj_vol', 'u'),
(35, 'vm_projects', 'r'),
(36, 'location_details', 'r'),
(36, 'person_uuid', 'r'),
(36, 'vm_position', 'r'),
(36, 'vm_vol_details', 'r'),
(36, 'vm_vol_position', 'cru'),
(37, 'vm_access_request', 'ru'),
(38, 'vm_access_classification_to_request', 'cd'),
(38, 'vm_access_constraint_to_request', 'cd'),
(39, 'phonetic_word', 'u'),
(39, 'vm_access_request', 'c'),
(40, 'vm_access_classification_to_request', 'cd'),
(40, 'vm_access_constraint_to_request', 'cd'),
(41, 'vm_access_request', 'c'),
(43, 'vm_position', 'cru'),
(43, 'vm_positiontype', 'r'),
(44, 'vm_position', 'cru'),
(44, 'vm_positiontype', 'r'),
(45, 'vm_position', 'u'),
(47, 'vm_image', 'd'),
(48, 'field_options', 'c'),
(49, 'field_options', 'd'),
(50, 'vm_vol_skills', 'cru'),
(51, 'vm_vol_skills', 'c'),
(52, 'vm_hours', 'c'),
(53, 'vm_hours', 'ru'),
(54, 'vm_hours', 'ru'),
(55, 'sys_tablefields_to_data_classification', 'cu'),
(55, 'vm_access_request', 'crud');

-- --------------------------------------------------------

--
-- Table structure for table vm_access_constraint
--

CREATE TABLE vm_access_constraint (
  constraint_id varchar(30) NOT NULL default '',
  description varchar(200) default NULL,
  PRIMARY KEY  (constraint_id)
);

--
-- Dumping data for table vm_access_constraint
--

INSERT INTO vm_access_constraint (constraint_id, description) VALUES
('req_login', 'Require that any user be logged in'),
('req_volunteer', 'Require that the logged-in user be a volunteer'),
('req_manager', 'Require that the logged-in user be a site manager'),
('ovr_manager', 'Override all other constraints if the logged-in user is a site manager'),
('ovr_my_info', 'Override all other constraints if the logged-in user is accessing his own information'),
('ovr_my_proj', 'Override all other constraints if the logged-in user is accessing a project of his'),
('ovr_mgr_proj', 'Override all other constraints if the logged-in user is accessing a project for which he is the site manager'),
('ovr_mainops', 'Override all other constraints if the logged-in user has the Main Operations Handler role'),
('ovr_mgr_pos', 'Override all other constraints if the logged-in user is accessing a position in a project for which he is the site manager');

-- --------------------------------------------------------

--
-- Table structure for table vm_access_constraint_to_request
--

CREATE TABLE vm_access_constraint_to_request (
  request_id int(11) NOT NULL default 0,
  constraint_id varchar(30) NOT NULL default '',
  PRIMARY KEY  (request_id,constraint_id)
);

--
-- Dumping data for table vm_access_constraint_to_request
--

INSERT INTO vm_access_constraint_to_request (request_id, constraint_id) VALUES
(2, 'ovr_my_info'),
(4, 'req_login'),
(5, 'req_login'),
(7, 'ovr_mgr_proj'),
(8, 'ovr_manager'),
(8, 'ovr_my_info'),
(10, 'req_login'),
(11, 'req_login'),
(12, 'req_login'),
(13, 'ovr_manager'),
(14, 'ovr_manager'),
(15, 'req_login'),
(16, 'req_login'),
(16, 'req_volunteer'),
(19, 'ovr_mgr_proj'),
(21, 'req_manager'),
(22, 'ovr_mainops'),
(24, 'ovr_mgr_pos'),
(24, 'ovr_my_info'),
(26, 'ovr_my_proj'),
(27, 'ovr_manager'),
(28, 'ovr_mgr_proj'),
(29, 'ovr_manager'),
(32, 'ovr_mgr_proj'),
(33, 'ovr_mgr_proj'),
(34, 'req_login'),
(34, 'req_volunteer'),
(36, 'ovr_manager'),
(44, 'ovr_mgr_proj'),
(43, 'ovr_mgr_proj'),
(45, 'ovr_mgr_proj'),
(46, 'req_login'),
(47, 'ovr_my_info'),
(48, 'ovr_mainops'),
(48, 'ovr_manager'),
(49, 'ovr_mainops'),
(52, 'ovr_mgr_pos'),
(52, 'ovr_my_info'),
(53, 'ovr_mgr_pos'),
(53, 'ovr_my_info'),
(54, 'ovr_mgr_pos'),
(54, 'ovr_my_info');

-- --------------------------------------------------------

--
-- Table structure for table vm_access_request
--

CREATE TABLE vm_access_request (
  request_id int(11) NOT NULL auto_increment,
  act varchar(100) default NULL,
  vm_action varchar(100) default NULL,
  description varchar(300) default NULL,
  PRIMARY KEY  (request_id)
);

--
-- Dumping data for table vm_access_request
--

INSERT INTO vm_access_request (request_id, act, vm_action, description) VALUES
(25, 'volunteer', 'process_add', 'Process Volunteer - Volunteer Add or Edit'),
(1, 'volunteer', 'display_add', 'Display Volunteer - Volunteer Add'),
(2, 'volunteer', 'display_edit', 'Display Volunteer - Volunteer Edit'),
(3, 'volunteer', 'display_confirm_delete', 'Display Volunteer - Volunteer Retire Confirmation'),
(4, 'volunteer', 'display_change_pass', 'Display Volunteer - Volunteer Password Edit'),
(5, 'volunteer', 'process_change_pass', 'Process Volunteer - Volunteer Password Edit'),
(6, 'volunteer', 'process_delete', 'Process Volunteer - Volunteer Retire'),
(7, 'volunteer', 'display_list_all', 'Display Volunteer - List all Volunteers'),
(8, 'volunteer', 'display_single', 'Display Volunteer - Single Volunteer''s Information'),
(9, 'volunteer', 'display_list_assigned', 'Display Volunteer - List only assigned volunteers'),
(10, 'volunteer', 'display_mailbox', 'Display Volunteer - Mailbox'),
(11, 'volunteer', 'display_message', 'Display Volunteer - Message View'),
(12, 'volunteer', 'process_send_message', 'Process Volunteer - Message Send'),
(13, 'volunteer', 'display_search', 'Display Volunteer - Search'),
(14, 'volunteer', 'process_search', 'Process Volunteer - Search'),
(15, 'volunteer', 'display_send_message', 'Display Volunteer - Message Send'),
(16, 'volunteer', 'display_portal', 'Display Volunteer - Portal'),
(17, 'volunteer', 'default', 'Display Default - Default Page'),
(18, 'volunteer', 'display_report_all', 'Display Volunteer - Report all Volunteers'),
(19, 'volunteer', 'display_custom_report', 'Display Volunteer - Custom Report'),
(20, 'volunteer', 'display_custom_report_select', 'Display Volunteer - Custom Report Select'),
(26, 'project', 'display_single', 'Display Project - Project Information'),
(27, 'project', 'display_add', 'Display Project - Project Add'),
(28, 'project', 'display_edit', 'Display Project - Project Edit'),
(29, 'project', 'process_add', 'Process Project - Project Add or Edit'),
(30, 'project', 'process_delete', 'Process Project - Project Retire'),
(31, 'project', 'display_confirm_delete', 'Display Project - Project Retire Confirmation '),
(32, 'project', 'display_assign', 'Process Project - Assign to Project'),
(33, 'project', 'process_remove_from_project', 'Process Project - Retire from Project'),
(34, 'project', 'display_my_list', 'Display Project - List projects pertaining to logged-in user'),
(35, 'project', 'default', 'Display Project - List all projects'),
(44, 'project', 'add_position', 'Display Project - Position Add'),
(45, 'project', 'remove_position', 'Process Project - Position Remove'),
(36, 'project', 'display_select_project', 'Display Project - Assign to Project - Select Project to assign to'),
(47, 'volunteer', 'process_remove_picture', 'Process Volunteer - Picture Remove'),
(46, 'volunteer', 'process_delete_message', 'Process Volunteer - Message Delete'),
(43, 'project', 'process_add_position', 'Process Project - Position Add'),
(37, 'adm_default', 'display_acl_situations', 'Display Admin - ACL Select Request to Modify Constraints for'),
(38, 'adm_default', 'display_acl_modify', 'Display Admin - ACL Edit Constraints'),
(39, 'adm_default', 'process_update_phonetics', 'Process Admin - Update Search Registry'),
(40, 'adm_default', 'process_acl_modifications', 'Process Admin - ACL Edit Constraints'),
(48, 'volunteer', 'process_add_skill', 'Process Volunteer - Skill Add'),
(41, 'adm_default', 'process_clear_cache', 'Process Admin - Delete PHP Templates from Cache'),
(42, 'adm_default', 'default', 'Display Admin - Home Admin Page'),
(21, 'volunteer', 'display_custom_report_select_for_mgrs', 'Display Volunteer - Custom Report Select (for Site Managers only)'),
(22, 'volunteer', 'display_modify_skills', 'Display Volunteer - Skill Set Modify'),
(23, 'volunteer', 'display_approval_management', 'Display Volunteer - Ability Approvals'),
(24, 'volunteer', 'display_log_time_form', 'Display Volunteer - Time Logging'),
(49, 'volunteer', 'process_remove_skill', 'Process Volunteer - Skill Remove'),
(50, 'volunteer', 'process_approval_modifications', 'Process Volunteer - Ability Approvals'),
(51, 'volunteer', 'process_approval_upgrades', 'Process Volunteer - Ability Upgrade'),
(52, 'volunteer', 'process_log_time', 'Process Volunteer - Time Logging'),
(53, 'volunteer', 'review_hours', 'Display Volunteer - Time Logging - Review Hours'),
(54, 'volunteer', 'process_review_hours', 'Process Volunteer - Time Logging - Review Hours'),
(55, 'adm_default', 'process_audit_acl', 'Process Admin - ACL Audit');

--
-- Create views used by VM Module
--

drop view if exists vm_position_full;
drop view if exists vm_vol_assignment;
drop view if exists vm_vol_assignment_active;
drop view if exists vm_position_active;
drop view if exists vm_projects_active;
drop view if exists vm_pos_volunteercount;
drop view if exists vm_vol_active;

create definer = CURRENT_USER sql security invoker view vm_position_full as
select vm_projects.name as project_name, vm_position.pos_id, vm_position.proj_id, ptype_id, vm_position.title, vm_position.slots, vm_position.description,
vm_positiontype.title ptype_title, vm_positiontype.description ptype_description, vm_position.status, skill_code, payrate
from vm_position left join vm_positiontype using (ptype_id) join vm_projects using (proj_id);

create definer = CURRENT_USER sql security invoker view vm_vol_assignment as
select vm_vol_position.p_uuid, proj_id, pos_id, vm_vol_position.status, vm_position_full.payrate, vm_vol_position.hours, vm_vol_position.task, ptype_id, title, slots,
vm_position_full.description, ptype_title, ptype_description, skill_code, vm_projects.name as project_name,
vm_projects.description as project_description
from vm_vol_position left join vm_position_full using (pos_id)
left join vm_projects using (proj_id);

create definer = CURRENT_USER sql security invoker view vm_vol_assignment_active as
select * from vm_vol_assignment
where status = 'active';

create definer = CURRENT_USER sql security invoker view vm_position_active as
select * from vm_position_full
where status = 'active';

create definer = CURRENT_USER sql security invoker view vm_projects_active as
select * from vm_projects
where status = 'active';

create definer = CURRENT_USER sql security invoker view vm_pos_volunteercount as
select pos_id, count(*) numVolunteers from vm_vol_assignment_active
where pos_id <> '' group by pos_id;

create definer = CURRENT_USER sql security invoker view vm_vol_active as
select * from vm_vol_details where status = 'active';



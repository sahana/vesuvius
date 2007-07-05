--
-- Table structure for table `vm_courier`
--

DROP TABLE IF EXISTS `vm_courier`;
CREATE TABLE `vm_courier` (
  `message_id` bigint(40) NOT NULL default '0',
  `to_id` varchar(60) NOT NULL default '',
  `from_id` varchar(60) NOT NULL default '',
  PRIMARY KEY  (`message_id`,`to_id`,`from_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `vm_mailbox`
--

DROP TABLE IF EXISTS `vm_mailbox`;
CREATE TABLE `vm_mailbox` (
  `p_uuid` varchar(60) NOT NULL default '',
  `message_id` bigint(40) NOT NULL default '0',
  `box` int(1) NOT NULL default '0',
  `checked` int(1) default '0',
  PRIMARY KEY  (`p_uuid`,`message_id`,`box`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `vm_message`
--

DROP TABLE IF EXISTS `vm_message`;
CREATE TABLE `vm_message` (
  `message_id` bigint(40) NOT NULL auto_increment,
  `message` text,
  `time` timestamp NOT NULL default CURRENT_TIMESTAMP,
  PRIMARY KEY  (`message_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=21 ;


--
-- Table structure for table `vm_proj_skills`
--

DROP TABLE IF EXISTS `vm_proj_skills`;
CREATE TABLE `vm_proj_skills` (
  `p_uuid` varchar(60) default NULL,
  `opt_skill_code` varchar(100) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `vm_proj_vol`
--

DROP TABLE IF EXISTS `vm_proj_vol`;
CREATE TABLE `vm_proj_vol` (
  `p_uuid` varchar(60) NOT NULL default '',
  `proj_id` bigint(20) NOT NULL default '0',
  `status` varchar(20) default NULL,
  `payrate` double default NULL,
  `hours` bigint(20) default NULL,
  `task` varchar(200) default NULL,
  PRIMARY KEY  (`p_uuid`,`proj_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


--
-- Table structure for table `vm_projects`
--

DROP TABLE IF EXISTS `vm_projects`;
CREATE TABLE `vm_projects` (
  `proj_id` bigint(20) NOT NULL auto_increment,
  `name` varchar(50) default NULL,
  `mgr_id` varchar(60) NOT NULL default '0',
  `location_id` varchar(60) default NULL,
  `start_date` date default NULL,
  `end_date` date default NULL,
  `description` text NOT NULL,
  PRIMARY KEY  (`proj_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=22 ;


--
-- Table structure for table `vm_vol_details`
--

DROP TABLE IF EXISTS `vm_vol_details`;
CREATE TABLE `vm_vol_details` (
  `p_uuid` varchar(60) NOT NULL default '0',
  `org_id` varchar(60) NOT NULL default '0',
  `photo` blob NOT NULL,
  `date_avail_start` date NOT NULL,
  `date_avail_end` date NOT NULL,
  `hrs_avail_start` time,
  `hrs_avail_end` time,
  PRIMARY KEY  (`p_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `vm_vol_skills`
--

DROP TABLE IF EXISTS `vm_vol_skills`;
CREATE TABLE `vm_vol_skills` (
  `p_uuid` varchar(60) default NULL,
  `opt_skill_code` varchar(100) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `vm_image`
--

DROP TABLE IF EXISTS `vm_image`;
CREATE TABLE `vm_image` (
  `img_uuid` varchar(60) NOT NULL,
  `original` blob NOT NULL,
  `image_data` blob NOT NULL,
  `thumb_data` blob NOT NULL,
  `p_uuid` varchar(60) NOT NULL,
  `date_added` datetime NOT NULL,
  `width` smallint(6) NOT NULL,
  `height` smallint(6) NOT NULL,
  `thumb_width` smallint(6) NOT NULL,
  `thumb_height` smallint(6) NOT NULL,
  `mime_type` varchar(60) NOT NULL,
  `name` varchar(60) NOT NULL,
  PRIMARY KEY  (`img_uuid`),
  KEY `p_uuid` (`p_uuid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Insert skill information
--

DELETE FROM field_options WHERE field_name = 'opt_skill_type';
INSERT INTO field_options VALUES('opt_skill_type', 'ANI2', 'Skilled-Animals-Animal Control Vehicles');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI1', 'Skilled-Animals-Animal Handling');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI3', 'Skilled-Animals-Grief Counseling');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI4', 'Skilled-Animals-Horse Trailers');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI5', 'Skilled-Animals-Livestock Vehicles');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI8', 'Skilled-Animals-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI7', 'Skilled-Animals-Veterinarian');
INSERT INTO field_options VALUES('opt_skill_type', 'ANI6', 'Skilled-Animals-Veterinary Technician');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT2', 'Skilled-Automotive-Body Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT1', 'Skilled-Automotive-Engine Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT3', 'Skilled-Automotive-Lights, Electrical');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT6', 'Skilled-Automotive-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT4', 'Skilled-Automotive-Tire Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'AUT5', 'Skilled-Automotive-Wheel and Brake Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'BAB1', 'Skilled-Baby and Child Care-Aide');
INSERT INTO field_options VALUES('opt_skill_type', 'BAB2', 'Skilled-Baby and Child Care-Leader');
INSERT INTO field_options VALUES('opt_skill_type', 'BAB3', 'Skilled-Baby and Child Care-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'CON1', 'Skilled-Construction Services-Glass Services');
INSERT INTO field_options VALUES('opt_skill_type', 'CON2', 'Skilled-Construction Services-House Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'CON3', 'Skilled-Construction Services-Inspection, Buildings');
INSERT INTO field_options VALUES('opt_skill_type', 'CON6', 'Skilled-Construction Services-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'CON4', 'Skilled-Construction Services-Roofing');
INSERT INTO field_options VALUES('opt_skill_type', 'CON5', 'Skilled-Construction Services-Window Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'ELE1', 'Skilled-Electrical-External Wiring');
INSERT INTO field_options VALUES('opt_skill_type', 'ELE2', 'Skilled-Electrical-Internal Wiring');
INSERT INTO field_options VALUES('opt_skill_type', 'ELE3', 'Skilled-Electrical-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'FOO1', 'Skilled-Food Service-Cooking');
INSERT INTO field_options VALUES('opt_skill_type', 'FOO2', 'Skilled-Food Service-Directing');
INSERT INTO field_options VALUES('opt_skill_type', 'FOO5', 'Skilled-Food Service-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'FOO3', 'Skilled-Food Service-Preparing');
INSERT INTO field_options VALUES('opt_skill_type', 'FOO4', 'Skilled-Food Service-Serving');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ1', 'Skilled-Hazardous Materials-Asbestos');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ2', 'Skilled-Hazardous Materials-Chemicals');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ3', 'Skilled-Hazardous Materials-Explosives');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ4', 'Skilled-Hazardous Materials-Flammables');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ5', 'Skilled-Hazardous Materials-Gases');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ6', 'Skilled-Hazardous Materials-Identification of');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ8', 'Skilled-Hazardous Materials-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'HAZ7', 'Skilled-Hazardous Materials-Radioactive');
INSERT INTO field_options VALUES('opt_skill_type', 'INF1', 'Skilled-Information Services-Book Restoration');
INSERT INTO field_options VALUES('opt_skill_type', 'INF2', 'Skilled-Information Services-Computer');
INSERT INTO field_options VALUES('opt_skill_type', 'INF3', 'Skilled-Information Services-Data Entry');
INSERT INTO field_options VALUES('opt_skill_type', 'INF4', 'Skilled-Information Services-Hardware (Computer)');
INSERT INTO field_options VALUES('opt_skill_type', 'INF7', 'Skilled-Information Services-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'INF5', 'Skilled-Information Services-Software (Computer)');
INSERT INTO field_options VALUES('opt_skill_type', 'INF6', 'Skilled-Information Services-Telephone Repair');
INSERT INTO field_options VALUES('opt_skill_type', 'MED1', 'Skilled-Medical-Assist to Physician');
INSERT INTO field_options VALUES('opt_skill_type', 'MED2', 'Skilled-Medical-Counseling');
INSERT INTO field_options VALUES('opt_skill_type', 'MED3', 'Skilled-Medical-Dentist');
INSERT INTO field_options VALUES('opt_skill_type', 'MED4', 'Skilled-Medical-First Aid');
INSERT INTO field_options VALUES('opt_skill_type', 'MED5', 'Skilled-Medical-Medical, Ambulance');
INSERT INTO field_options VALUES('opt_skill_type', 'MED6', 'Skilled-Medical-Nurse');
INSERT INTO field_options VALUES('opt_skill_type', 'MED9', 'Skilled-Medical-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'MED7', 'Skilled-Medical-Physician');
INSERT INTO field_options VALUES('opt_skill_type', 'MED8', 'Skilled-Medical-Technician');
INSERT INTO field_options VALUES('opt_skill_type', 'PLU2', 'Skilled-Plumbing-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'PLU1', 'Skilled-Plumbing-Pumping-With Pump');
INSERT INTO field_options VALUES('opt_skill_type', 'PLU3', 'Skilled-Plumbing-Pumping-Without Pump');
INSERT INTO field_options VALUES('opt_skill_type', 'MGR_APPLY',  'Apply for Site Manager');
INSERT INTO field_options VALUES('opt_skill_type', 'MGR_APPROVED',  'Approved Site Manager');
INSERT INTO field_options VALUES('opt_skill_type', 'TRE1', 'Skilled-Tree-Evaluation of Needs');
INSERT INTO field_options VALUES('opt_skill_type', 'TRE4', 'Skilled-Tree-Other');
INSERT INTO field_options VALUES('opt_skill_type', 'TRE2', 'Skilled-Tree-Removal of Trees');
INSERT INTO field_options VALUES('opt_skill_type', 'TRE3', 'Skilled-Tree-Trimming of Trees');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS1', 'Unskilled-Other-Baby Care Help');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS2', 'Unskilled-Other-Clerical');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS3', 'Unskilled-Other-Food Help');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS4', 'Unskilled-Other-Heavy Labor (Moving, Erecting Tents)');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS5', 'Unskilled-Other-Light Labor (Cleanup)');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS6', 'Unskilled-Other-Messenger (Local People Preferred)');
INSERT INTO field_options VALUES('opt_skill_type', 'UNS7', 'Unskilled-Other-Miscellaneous');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH1', 'Unskilled-Vehicle-Own Aircraft');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH5', 'Unskilled-Vehicle-Own Backhoe');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH2', 'Unskilled-Vehicle-Own Bulldozer');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH3', 'Unskilled-Vehicle-Own Crane');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH4', 'Unskilled-Vehicle-Own Forklift');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH7', 'Unskilled-Vehicle-Own Heavy Equipment');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH6', 'Unskilled-Vehicle-Own Medical; Ambulance');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH13', 'Unskilled-Vehicle-Own Other');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH8', 'Unskilled-Vehicle-Own Refrigerated');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH9', 'Unskilled-Vehicle-Own Steamshovel');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH10', 'Unskilled-Vehicle-Own Truck');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH11', 'Unskilled-Vehicle-Own Van, Car');
INSERT INTO field_options VALUES('opt_skill_type', 'VEH12', 'Unskilled-Vehicle-Own Boat(s)');
INSERT INTO field_options VALUES('opt_skill_type', 'WAR1', 'Unskilled-Warehouse-Forklift');
INSERT INTO field_options VALUES('opt_skill_type', 'WAR2', 'Unskilled-Warehouse-General');
INSERT INTO field_options VALUES('opt_skill_type', 'WAR3', 'Unskilled-Warehouse-Management');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT1', 'Unskilled-With Tools-with Brooms');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT2', 'Unskilled-With Tools-with Carpentry Tools');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT7', 'Unskilled-With Tools-with Other Tools');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT3', 'Unskilled-With Tools-with Pump, Small');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT4', 'Unskilled-With Tools-with Saws, Chainsaw');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT5', 'Unskilled-With Tools-with Wheelbarrow');
INSERT INTO field_options VALUES('opt_skill_type', 'WIT6', 'Unskilled-With Tools-with Yard Tools');

--
-- Data Classification
--

DELETE FROM sys_tablefields_to_data_classification WHERE table_field LIKE 'vm_%';
INSERT INTO sys_tablefields_to_data_classification (table_field, level_id) VALUES
('vm_courier', 1),
('vm_mailbox', 1),
('vm_message', 1),
('vm_proj_skills', 2),
('vm_proj_vol', 2),
('vm_projects', 2),
('vm_vol_details', 1),
('vm_vol_skills', 1),
('vm_image', 1),
('vm_access_classification_to_request', 6),
('vm_access_constraint', 6),
('vm_access_constraint_to_request', 6),
('vm_access_request', 6);


--
-- Access Control
--


/*
 * The vm_access_request table stores all possible 'act' - 'vm_action' pairs of possible
 * access requests made to the VM module. 'default' vm_action cases must be included for each 'act',
 * but if no 'act' is specified, the AccessController will default to 'volunteer'
 */

DROP TABLE IF EXISTS vm_access_request;
CREATE TABLE vm_access_request
(
    request_id  INTEGER(11) AUTO_INCREMENT,
    act         VARCHAR(100),
    vm_action   VARCHAR(100),
    description VARCHAR(300),

    PRIMARY KEY(request_id)
);

INSERT INTO vm_access_request VALUES
(1, 'volunteer',    'process_add',             'Process Volunteer - Add or Edit'),
(2, 'volunteer',    'display_add',             'Display Volunteer - Add'),
(3, 'volunteer',    'display_edit',            'Display Volunteer - Edit'),
(4, 'volunteer',    'display_confirm_delete',  'Display Volunteer - Delete Confirmation'),
(5, 'volunteer',    'display_change_pass',     'Display Volunteer - Edit Password'),
(6, 'volunteer',    'process_change_pass',     'Process Volunteer - Edit Password'),
(7, 'volunteer',    'process_delete',          'Process Volunteer - Delete'),
(8, 'volunteer',    'display_list_all',        'Display Volunteer - List all volunteers'),
(9, 'volunteer',    'display_single',          "Display Volunteer - Single Volunteer's Information"),
(10, 'volunteer',   'display_list_assigned',   'Display Volunteer - List only assigned volunteers'),
(11, 'volunteer',   'display_mailbox',         'Display Volunteer - Mailbox'),
(12, 'volunteer',   'display_message',         'Display Volunteer - Single Message'),
(13, 'volunteer',   'process_send_message',    'Process Volunteer - Send a Message'),
(14, 'volunteer',   'display_search',          'Display Volunteer - Search'),
(15, 'volunteer',   'process_search',          'Process Volunteer - Search'),
(16, 'volunteer',   'display_send_message',    'Display Volunteer - Send a Message'),
(17, 'volunteer',   'display_portal',          'Display Volunteer - Portal'),
(18, 'volunteer',   'default',                 'Display Default - Default Page'),

(100, 'project',    'display_single',              "Display Project - Single Project's Information"),
(101, 'project',    'display_add',                 'Display Project - Add'),
(102, 'project',    'display_edit',                'Display Project - Edit'),
(103, 'project',    'process_add',                 'Process Project - Add or Edit'),
(104, 'project',    'process_delete',              'Process Project - Delete'),
(105, 'project',    'display_confirm_delete',      'Display Project - Delete Confirmation'),
(106, 'project',    'display_assign',              'Process Volunteer - Assign to Project'),
(107, 'project',    'process_remove_from_project', 'Process Volunteer - Remove from Project'),
(108, 'project',    'display_my_list',             'Display Project - List projects pertaining to logged-in user'),
(109, 'project',    'default',                     'Display Project - List all projects'),
(110, 'project',    'display_edit_task',           'Display Volunteer - Edit Assigned Task'),
(111, 'project',    'process_edit_task',           'Process Volunteer - Edit Assigned Task'),
(112, 'project',    'display_select_project',      'Display Project - Select Project to Assign to'),

(200, 'adm_default',  'display_modify_skills',          'Display Admin - Edit Skill Set'),
(201, 'adm_default',  'process_add_skill',              'Process Admin - Add to Skill Set'),
(202, 'adm_default',  'process_remove_skill',           'Process Admin - Delete from Skill Set'),
(203, 'adm_default',  'display_acl_situations',         'Display Admin - Select ACL Situation'),
(204, 'adm_default',  'display_acl_modify',             'Display Admin - Edit ACL Constraints'),
(205, 'adm_default',  'process_update_phonetics',       'Process Admin - Update Search Registry'),
(206, 'adm_default',  'process_acl_modifications',      'Process Admin - Edit ACL Constraints'),
(207, 'adm_default',  'display_approve_managers',       'Display Admin - Approve Site Managers'),
(208, 'adm_default',  'process_manager_approval',       'Process Admin - Approve Site Managers'),
(209, 'adm_default',  'process_clear_cache',            'Process Admin - Delete PHP Templates from Cache'),
(210, 'adm_default',  'default',                        'Display Admin - Home Admin Page');

/*
 * The vm_access_classification_to_request table stores all data classification constraints to impose on a particular
 * access request
 */

DROP TABLE IF EXISTS vm_access_classification_to_request;
CREATE TABLE vm_access_classification_to_request
(
    request_id      INTEGER(11),
    table_name       VARCHAR(200),
    crud            VARCHAR(4),

    PRIMARY KEY(request_id, table_name, crud)
);

INSERT INTO `vm_access_classification_to_request` (`request_id`, `table_name`, `crud`) VALUES
(3, 'identity_to_person', 'ru'),
(3, 'person_uuid', 'ru'),
(3, 'vm_proj_vol', 'ru'),
(3, 'vm_vol_details', 'ru'),
(4, 'identity_to_person', 'd'),
(4, 'person_uuid', 'd'),
(4, 'vm_proj_vol', 'd'),
(4, 'vm_vol_details', 'd'),
(7, 'identity_to_person', 'd'),
(7, 'person_uuid', 'd'),
(7, 'vm_proj_vol', 'd'),
(7, 'vm_vol_details', 'd'),
(8, 'location_details', 'r'),
(8, 'person_uuid', 'r'),
(8, 'vm_proj_vol', 'r'),
(8, 'vm_vol_details', 'r'),
(9, 'identity_to_person', 'r'),
(9, 'location_details', 'r'),
(9, 'person_uuid', 'r'),
(9, 'vm_proj_vol', 'r'),
(9, 'vm_vol_details', 'r'),
(10, 'location_details', 'r'),
(10, 'person_uuid', 'r'),
(10, 'vm_proj_vol', 'r'),
(10, 'vm_vol_details', 'r'),
(14, 'identity_to_person', 'r'),
(14, 'location_details', 'r'),
(14, 'person_uuid', 'r'),
(14, 'vm_proj_vol', 'r'),
(14, 'vm_vol_details', 'r'),
(15, 'identity_to_person', 'r'),
(15, 'location_details', 'r'),
(15, 'person_uuid', 'r'),
(15, 'vm_proj_vol', 'r'),
(15, 'vm_vol_details', 'r'),
(100, 'vm_projects', 'r'),
(100, 'vm_proj_skills', 'r'),
(101, 'vm_projects', 'c'),
(101, 'vm_proj_skills', 'c'),
(102, 'vm_projects', 'u'),
(102, 'vm_proj_skills', 'u'),
(104, 'vm_projects', 'd'),
(104, 'vm_proj_skills', 'd'),
(104, 'vm_proj_vol', 'd'),
(105, 'vm_projects', 'd'),
(105, 'vm_proj_skills', 'd'),
(105, 'vm_proj_vol', 'd'),
(106, 'identity_to_person', 'r'),
(106, 'location_details', 'r'),
(106, 'person_uuid', 'r'),
(106, 'vm_proj_vol', 'cru'),
(106, 'vm_vol_details', 'r'),
(107, 'vm_proj_vol', 'd'),
(109, 'vm_projects', 'r'),
(110, 'vm_proj_vol', 'ru'),
(111, 'vm_proj_vol', 'ru'),
(112, 'identity_to_person', 'r'),
(112, 'location_details', 'r'),
(112, 'person_uuid', 'r'),
(112, 'vm_proj_vol', 'cru'),
(112, 'vm_vol_details', 'r'),
(200, 'field_options', 'crud'),
(201, 'field_options', 'c'),
(202, 'field_options', 'd'),
(203, 'vm_access_request', 'ru'),
(204, 'vm_access_classification_to_request', 'cd'),
(204, 'vm_access_constraint_to_request', 'cd'),
(205, 'phonetic_word', 'u'),
(206, 'vm_access_classification_to_request', 'cd'),
(206, 'vm_access_constraint_to_request', 'cd'),
(207, 'vm_vol_skills', 'cd'),
(208, 'vm_vol_skills', 'cd'),
(209, 'vm_access_request', 'crud');



/*
 * The vm_access_constraint table stores all possible constraints to impose on an access request
 */

DROP TABLE IF EXISTS vm_access_constraint;
CREATE TABLE vm_access_constraint
(
    constraint_id   VARCHAR(30),
    description     VARCHAR(200),

    PRIMARY KEY(constraint_id)
);

INSERT INTO vm_access_constraint VALUES
('req_login',           'Require that any user be logged in'),
('req_volunteer',       'Require that the logged-in user be a volunteer'),
('req_manager',         'Require that the logged-in user be a site manager'),

('ovr_manager',         'Override all other constraints if the logged-in user is a site manager'),
('ovr_my_info',         'Override all other constraints if the logged-in user is accessing his own information'),
('ovr_my_proj',         'Override all other constraints if the logged-in user is accessing a project of his'),
('ovr_mgr_proj',        'Override all other constraints if the logged-in user is accessing a project for which he is the site manager');

/*
 * The vm_access_constraints_to_request table links constraints to access requests
 */

DROP TABLE IF EXISTS vm_access_constraint_to_request;
CREATE TABLE vm_access_constraint_to_request
(
    request_id      INTEGER(11),
    constraint_id   VARCHAR(30),

    PRIMARY KEY(request_id, constraint_id)
);


INSERT INTO `vm_access_constraint_to_request` (`request_id`, `constraint_id`) VALUES
(3, 'ovr_my_info'),
(5, 'req_login'),
(6, 'req_login'),
(8, 'ovr_mgr_proj'),
(9, 'ovr_manager'),
(9, 'ovr_my_info'),
(11, 'req_login'),
(12, 'req_login'),
(13, 'req_login'),
(14, 'ovr_manager'),
(15, 'ovr_manager'),
(16, 'req_login'),
(17, 'req_login'),
(17, 'req_volunteer'),
(19, 'req_login'),
(100, 'ovr_my_proj'),
(101, 'ovr_manager'),
(102, 'ovr_mgr_proj'),
(103, 'ovr_manager'),
(106, 'ovr_mgr_proj'),
(107, 'ovr_mgr_proj'),
(108, 'req_login'),
(108, 'req_volunteer'),
(110, 'ovr_mgr_proj'),
(111, 'ovr_mgr_proj'),
(112, 'ovr_manager');








/* $id$ */

/**====================== GIS / GPS / Location Tables=============**/
/**
* Table to store Landmark Locations
* Modules: gis 
* Last Edited: 4-OCT-2006 mifan@opensource.lk
*/

DROP TABLE IF EXISTS `landmark_location`;
CREATE TABLE `landmark_location` (
  `landmark_uuid` VARCHAR(60) NOT NULL,
	`name` varchar(50) NOT NULL,
	`opt_landmark_type` VARCHAR(30) default NULL,
	`description` VARCHAR(100) default NULL,
	`comments` VARCHAR(100) default NULL,
	`gis_uid` VARCHAR(60) NOT NULL,
	PRIMARY KEY  (`landmark_uuid`)
);

/**
* Sample data for landmark types
*/
INSERT INTO field_options VALUES('opt_landmark_type','vil','Village');
INSERT INTO field_options VALUES('opt_landmark_type','tem','Temple');
INSERT INTO field_options VALUES('opt_landmark_type','vil','School');

/**
* Sample data for landmark contact types
*/
INSERT INTO field_options VALUES('opt_landmark_contact_type','cor','Coordinator');
INSERT INTO field_options VALUES('opt_landmark_contact_type','cof','Chief Of Village');
INSERT INTO field_options VALUES('opt_landmark_contact_type','mon','Monk');


/**
* Table for Geograhical Information Systems
* Stores basic coordinates providing basic spatial functionality
* Modules: all
* Last changed: 04-Oct-2006: mifan@opensource.lk
*/
DROP TABLE IF EXISTS `gis_location`;
CREATE TABLE `gis_location` (
  `poc_uuid` varchar(60) NOT NULL,
	`location_id` varchar(20) default NULL,
	`opt_gis_mod` varchar(30) default NULL,
	`map_northing` double(15,10) NOT NULL,
	`map_easting` double(15,10) NOT NULL,
	`map_projection` varchar(20) default NULL,
	`opt_gis_marker` varchar(20) default NULL,
	`gis_uid` varchar(60) NOT NULL,
	PRIMARY KEY  (`gis_uid`)
);

/**
* Default Config Data for gis mapping
*/
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'google_key', '');
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_x', '79.5');
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_y', '8.5');

/**
* Table for GIS-WikiMaps functionality
* Modules: gis
* Last edited: 04-Oct-2006: mifan@opensource.lk
*/

DROP TABLE IF EXISTS `gis_wiki`;
CREATE TABLE `gis_wiki` (
    `wiki_uuid` VARCHAR(60) NOT NULL,
    `gis_uuid` VARCHAR(60) NOT NULL,
    `name` varchar(50) NOT NULL,
    `description` VARCHAR(100) default NULL,
    `opt_category` VARCHAR(10),
    `url` varchar(50) NOT NULL,
    `event_date` timestamp NULL,
    `placement_date` timestamp NOT NULL default now(),
    `editable` boolean NOT NULL default false,
    `author` VARCHAR(30) default NULL,
    `approved` boolean default false,
    PRIMARY KEY  (`wiki_uuid`),
    FOREIGN KEY (gis_uuid) REFERENCES gis_location(gis_uid)
);

/**
 * Sample Data for WIKIMap Types
*/
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','gen','General');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','per','Person Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dam','Damage Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dis','Disaster Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','sos','Help Needed');


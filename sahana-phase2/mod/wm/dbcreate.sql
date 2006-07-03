/*$id$*/
/* 
*GIS-WikiMaps Schema 
*@author: mifan@opensource.lk
*----------------------------------------------------
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

/*
 * Sample Data for WIKIMap Types
*/
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','gen','General');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','per','Person Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dam','Damage Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','dis','Disaster Status');
INSERT INTO field_options (field_name,option_code,option_description) VALUES ('opt_wikimap_type','sos','Help Needed');	

/*$id$;*/
/* 
*Landmark Location Registry Tables and sample-data 
*@author: mifan@opensource.lk
*----------------------------------------------------
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

/*Sample data for landmark types*/
INSERT INTO field_options VALUES('opt_landmark_type','vil','Village');
INSERT INTO field_options VALUES('opt_landmark_type','tem','Temple');
INSERT INTO field_options VALUES('opt_landmark_type','vil','School');

/*Sample data for landmark types*/
INSERT INTO field_options VALUES('opt_landmark_contact_type','cor','Coordinator');
INSERT INTO field_options VALUES('opt_landmark_contact_type','cof','Chief Of Village');
INSERT INTO field_options VALUES('opt_landmark_contact_type','mon','Monk');


/* Geographic Information System and Mapping Tables
----------------------------------------------------
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

 --config options --
/*
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'google_key', '');
*/
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_x', '79.5');
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_y', '8.5');


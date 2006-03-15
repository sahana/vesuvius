/* Geographic Information System and Mapping Tables
----------------------------------------------------
*/

DROP TABLE IF EXISTS `gis_location`;
CREATE TABLE `gis_location` (
  `poc_uuid` bigint(20) NOT NULL,
	`location_id` varchar(20) default NULL,
	`opt_gis_mod` varchar(30) default NULL,
	`map_northing` double(15,10) NOT NULL,
	`map_easting` double(15,10) NOT NULL,
	`map_projection` varchar(20) default NULL,
	`opt_gis_marker` varchar(20) default NULL,
	`gis_uid` bigint(20) NOT NULL,
	PRIMARY KEY  (`gis_uid`)
);

/* --config options --*/

INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'google_key', '');
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_x', '');
INSERT INTO `config` ( `module_id` , `confkey` , `value` ) VALUES ('gis', 'center_y', '');



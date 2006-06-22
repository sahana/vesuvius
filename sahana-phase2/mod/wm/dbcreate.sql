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
	`url` varchar(50) NOT NULL,
	`event_date` timestamp default NULL,
	`placement_date` timestamp NOT NULL,
	`editable` boolean NOT NULL default 'false',
	`author` VARCHAR(30) default NULL,
	PRIMARY KEY  (`wiki_uuid`)
);


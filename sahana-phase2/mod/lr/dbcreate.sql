/*$id$*/
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

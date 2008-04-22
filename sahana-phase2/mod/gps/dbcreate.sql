/* $id$ */

/**======================  GPS waypoint/route Tables=============**/
/**
* Table to store waypoint Locations
* Modules: gps 
* author: sri@opensource.lk
*/

/**
* Sample data for waypoint types
*/
INSERT INTO field_options VALUES('opt_wpt_type','vil','Village');
INSERT INTO field_options VALUES('opt_wpt_type','bnk','Bank');
INSERT INTO field_options VALUES('opt_wpt_type','tmp','Temple');
INSERT INTO field_options VALUES('opt_wpt_type','sch','School');

/**
* Table for maintainig gpx file information
*/
DROP TABLE IF EXISTS `gpx_file`;
CREATE TABLE `gpx_file` (
  `point_uuid` VARCHAR(60) NOT NULL,
	`author_name` varchar(50) NOT NULL,
  	`event_date` timestamp NOT NULL,
	`route_name` VARCHAR(50) NOT NULL,
	`route_no` int(250) NOT NULL,
	 `opt_category` VARCHAR(10) NOT NULL,
	`sequence_no` int(250) NOT NULL,
	`point_name` varchar(50) NOT NULL,
	`description` varchar(100) default NULL,
	PRIMARY KEY  (`point_uuid`)
);

/**
*Sample route queries to check route downloading functionality
*/
INSERT INTO gpx_file VALUES ('oawlgps-1006','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','1','Fort','description1');
INSERT INTO gis_location VALUES ('oawlgps-1006' ,null,null,'6.888427734','121.0603207824' , null , null ,'oawlg-1170');

INSERT INTO gpx_file VALUES ('oawlgps-1007','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','2','Kollupitiya','description2');
INSERT INTO gis_location VALUES ('oawlgps-1007' ,null,null,'6.888427734','121.0603207825' , null , null ,'oawlg-1171');

INSERT INTO gpx_file VALUES ('oawlgps-1008','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','3','bambalapitiya','description3');
INSERT INTO gis_location VALUES ('oawlgps-1008' ,null,null,'6.888427734','121.0603207826' , null , null ,'oawlg-1172');


INSERT INTO gpx_file VALUES ('oawlgps-1009','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','4','wellawatte','description4');
INSERT INTO gis_location VALUES ('oawlgps-1009' ,null,null,'6.888427734','121.0603207827' , null , null ,'oawlg-1174');

INSERT INTO gpx_file VALUES ('oawlgps-1010','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','5','ratmalana','description5');
INSERT INTO gis_location VALUES ('oawlgps-1010' ,null,null,'6.888427734','121.0603207828' , null , null ,'oawlg-1175');

INSERT INTO gpx_file VALUES ('oawlgps-1011','sri','2007-07-30 00:00:00 ' ,'FORT-MORATWA' ,'1','scl','6','Moratuwa','description6');
INSERT INTO gis_location VALUES ('oawlgps-1011' ,null,null,'6.888427734','121.0603207829' , null , null ,'oawlg-1176');




INSERT INTO gpx_file VALUES ('oawlgps-1012','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','vil','1','Borella','description1');
INSERT INTO gis_location VALUES ('oawlgps-1012' ,null,null,'6.888427734','121.0603207824' , null , null ,'oawlg-1177');

INSERT INTO gpx_file VALUES ('oawlgps-1013','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','bnk','2','Town Hall','description2');
INSERT INTO gis_location VALUES ('oawlgps-1013' ,null,null,'6.888427733','121.0603207825' , null , null ,'oawlg-1178');

INSERT INTO gpx_file VALUES ('oawlgps-1014','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','tmp','3','Dhumulla','description3');
INSERT INTO gis_location VALUES ('oawlgps-1014' ,null,null,'6.888427739','121.0603207826' , null , null ,'oawlg-1179');


INSERT INTO gpx_file VALUES ('oawlgps-1015','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','scl','4','Thimbirigasya','description4');
INSERT INTO gis_location VALUES ('oawlgps-1015' ,null,null,'6.888427735','121.0603207827' , null , null ,'oawlg-1180');

INSERT INTO gpx_file VALUES ('oawlgps-1016','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','tmp','5','Kirlapana','description5');
INSERT INTO gis_location VALUES ('oawlgps-1016' ,null,null,'6.888427738','121.0603207828' , null , null ,'oawlg-1181');

INSERT INTO gpx_file VALUES ('oawlgps-1017','sri','2007-07-30 00:00:00 ' ,'Borella-Nugegoda' ,'2','bnk','6','Nugegoda','description6');
INSERT INTO gis_location VALUES ('oawlgps-1017' ,null,null,'6.888427732','121.0603207829' , null , null ,'oawlg-1182');

/**
* This file creates the database structure for the mpres module. The data stored in the one table is a log for what "persons" have been imported into MPR.
* Modules: MPRes
* Last changed: 2010:1006
*/

CREATE table mpres_log (
	log_index       int          NOT NULL AUTO_INCREMENT PRIMARY KEY,
	p_uuid          varchar(64)  NOT NULL,
	email_subject   varchar(256) NOT NULL,
	email_from      varchar(128) NOT NULL,
	email_date      varchar(64)  NOT NULL,
	update_time     datetime     NOT NULL,
	INDEX(`p_uuid`),
	FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


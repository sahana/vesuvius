/**
* This file creates the database log structure for the pop module.
* Modules: pop
* Last changed: 2010:0803
* v2.0
*/



DROP TABLE IF EXISTS `pop_outlog`;

CREATE table pop_outlog (
	outlog_index     int          NOT NULL AUTO_INCREMENT,
	mod_accessed     varchar(8)   NOT NULL,
	time_sent        timestamp    NOT NULL,
	send_status      varchar(8)   NOT NULL,
	error_message    varchar(512) NOT NULL,
	email_subject    varchar(256) NOT NULL,
	email_from       varchar(128) NOT NULL,
	email_recipients varchar(256) NOT NULL,
	PRIMARY KEY(outlog_index)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;



DROP TABLE IF EXISTS `pop_inlog`;


CREATE TABLE `pop_inlog` (
  `inlog_index` int(11) NOT NULL auto_increment,
  `mod_accessed` varchar(8) NOT NULL,
  `access_time` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  `access_status` varchar(8) NOT NULL,
  `error_message` varchar(512) NOT NULL,
  `p_uuid` varchar(60) NOT NULL,
  PRIMARY KEY  (`inlog_index`),
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


/**
* This file creates the database log structure for the pls module.
* Modules: pls
* Last changed: 2011.0203 ~ teh IPcalypse!
*/

CREATE TABLE `plus_access_log` (
  `access_id`   int(16)     NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `api_key`     varchar(60) NOT NULL,
  `access_time` timestamp   NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `application` varchar(32) NULL,
  `version`     varchar(16) NULL,
  `ip`          varchar(16) NULL,
  `call`        varchar(64) NULL,
  INDEX(`api_key`),
  FOREIGN KEY(`api_key`) REFERENCES `ws_keys` (`api_key`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE `plus_report_log` (
  `report_id`   int(16)     NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid`      varchar(60) NOT NULL,
  `report_time` timestamp   NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


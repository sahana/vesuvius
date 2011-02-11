/**
* DB Install script
* Modules: RAP
* Last changed: 20100921
*/

CREATE TABLE `rap_log` (
  `rap_id` int(16) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid` varchar(60) NOT NULL,
  `report_time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


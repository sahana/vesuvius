/**
* DB Install script
* Modules: RAP
* Last changed: 20100921
*/

CREATE TABLE `hospital` (
  `hospital_uuid`     int(32)      NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `name`              varchar(60)  NOT NULL,
  `short_name`        varchar(30)  NOT NULL,
  `street1`           varchar(120) NOT NULL,
  `street2`           varchar(120)          DEFAULT NULL,
  `city`              varchar(60)  NOT NULL,
  `county`            varchar(60)  NOT NULL,
  `region`            varchar(60)  NOT NULL,
  `postal_code`       varchar(16)  NOT NULL,
  `country`           varchar(32)  NOT NULL,
  `latitude`          double       NOT NULL,
  `longitude`         double       NOT NULL,
  `phone`             varchar(16)           DEFAULT NULL,
  `fax`               varchar(16)           DEFAULT NULL,
  `email`             varchar(64)           DEFAULT NULL,
  `npi`               varchar(32)           DEFAULT NULL,
  `patient_id_prefix` varchar(32)  NOT NULL,
  `creation_time`     timestamp    NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `icon_url`          varchar(128)          DEFAULT NULL,
  INDEX(`hospital_uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE `person_to_hospital` (
  `id`            int(16)      NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `hospital_uuid` int(32)      NOT NULL,
  `p_uuid`        varchar(60)  NOT NULL,
  INDEX(`hospital_uuid`),
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`)        REFERENCES `person_uuid` (`p_uuid`)        ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY(`hospital_uuid`) REFERENCES `hospital`    (`hospital_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;



INSERT INTO `hospital` (`hospital_uuid`, `name`, `short_name`, `street1`, `street2`, `city`, `county`, `region`, `postal_code`, `country`, `latitude`, `longitude`, `phone`, `fax`, `email`, `npi`, `patient_id_prefix`, `creation_time`, `icon_url`) 
VALUES
(1, 'Suburban Hospital', 'sh', '8600 Old Georgetown Rd', '', 'Bethesda', 'Montgomery', 'MD', '20817', 'USA', 38.99731, -77.10984, '3018963100', '', '', '', '911-', '2010-01-01 01:01:01', 'theme/lpf3/img/suburban.png'),
(2, 'National Naval Medical Center', 'nnmc', 'National Naval Medical Center', '', 'Bethesda', 'Montgomery', 'MD', '20889', 'US', 39.00204, -77.0945, '3012954611', '', '', '', '', '2010-09-22 18:49:34', 'theme/lpf3/img/nnmc.png');

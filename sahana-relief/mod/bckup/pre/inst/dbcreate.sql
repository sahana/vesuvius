/**
* Disaster Preparedeness Module - table
*/

/**
* Tracking information about suspectable disaster
*/
DROP TABLE IF EXISTS `pre_disaster`;
CREATE TABLE IF NOT EXISTS `pre_disaster` ( -- Disaster
  `disaster_uuid` varchar(60) NOT NULL, -- Disaster id
  `disaster` varchar(100) NOT NULL, -- Disaster
  `reason` text, -- Reason
  `possibility` varchar(10) default NULL, -- Possibility
  `description` text, -- Detailed Description
  `status` varchar(10), -- Status of disaster
  PRIMARY KEY  (`disaster_uuid`)
);

/**
* Tracking information about effects of disasters
*/
DROP TABLE IF EXISTS `pre_disaster_effects`;
CREATE TABLE `pre_disaster_effects` ( -- Effects of a disaster
  `disaster_uuid` varchar(60) NOT NULL, -- Disaster id
  `effect` varchar(20) NOT NULL, -- Possible Effects
  PRIMARY KEY  (`disaster_uuid`,`effect`),
  FOREIGN KEY(`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`)
);

/**
* Tracking information on recoverying from disasters
*/
DROP TABLE IF EXISTS `pre_disaster_recovery`;
CREATE TABLE `pre_disaster_recovery` ( -- Recoverying Details of disaster
  `id` varchar(60) NOT NULL, -- Disaster id
  `disaster_uuid` varchar(60) NOT NULL,
  `effect` varchar(20) default NULL, -- Effect
  `method` text NOT NULL, -- Recoverying Method
  `term` varchar(20) NOT NULL, -- Term
  `disaster_status` varchar(10) NOT NULL, -- Status of disaster
  `priority` varchar(20) NOT NULL, -- Priority
  PRIMARY KEY  (`id`),
  FOREIGN KEY(`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`),
  FOREIGN KEY(`effect`) REFERENCES pre_disaster_effects(`effect`)
);

/**
* Tracking areas under threat
*/
DROP TABLE IF EXISTS `pre_threat_area`;
CREATE TABLE IF NOT EXISTS `pre_threat_area` ( -- Areas under threat
  `area_uuid` varchar(60) NOT NULL, -- Area id
  `area` varchar(255) NOT NULL, -- Area name
  `loc_uuid` varchar(60) default NULL, -- Location id
  `person_uuid` varchar(60) default NULL, -- Contact Person id
  `population` int(11) default NULL, -- Population
  `families` int(11) default NULL, -- No: of Families
  `houses` int(11) default NULL, -- No: of houses
  PRIMARY KEY  (`area_uuid`)
);

/**
* Tracking possible disasters of areas
*/
DROP TABLE IF EXISTS `pre_threat_area_disaster`;
CREATE TABLE IF NOT EXISTS `pre_threat_area_disaster` ( -- Disaster of areas
  `disaster_uuid` varchar(60) NOT NULL, -- Disaster id
  `area_uuid` varchar(60) NOT NULL, -- Area id
  `threat_level` varchar(20) NOT NULL, -- Threat Level
  `status` varchar(10) NOT NULL, -- Status
  PRIMARY KEY  (`disaster_uuid`,`area_uuid`),
  FOREIGN KEY(`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`),
  FOREIGN KEY(`area_uuid`) REFERENCES pre_threat_area(`area_uuid`)
);

/**
* Tracking suitable areas for shelters
*/
DROP TABLE IF EXISTS `pre_shelter_area`;
CREATE TABLE `pre_shelter_area` ( -- Suitable areas to shelters
`area_uuid` VARCHAR( 60 ) NOT NULL , -- Area id
`area` VARCHAR( 255 ) NOT NULL , -- Location name
`address` TEXT NULL , -- Address
`loc_uuid` VARCHAR( 60 ) NULL , -- Location id
`person_uuid` VARCHAR( 60 ) NULL , -- Contact person
`ownership` VARCHAR( 15 ) NULL , -- Ownership
`owner_uuid` VARCHAR( 60 ) NULL , -- Owner
`capacity` INT NULL , -- Capacity
`land_type` VARCHAR( 20 ) NULL , -- Land Type
`status` INT NULL, -- Status
PRIMARY KEY ( `area_uuid` )
);

/**
* Tracking disasters for each shelter to establish it
*/
DROP TABLE IF EXISTS `pre_shelter_disaster`;
CREATE TABLE `pre_shelter_disaster` ( -- Disaster to shelter
`area_uuid` VARCHAR( 60 ) NOT NULL , -- Area id
`disaster_uuid` VARCHAR( 60 ) NOT NULL , -- Disaster id
PRIMARY KEY ( `area_uuid` , `disaster_uuid` ),
FOREIGN KEY(`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`),
FOREIGN KEY(`area_uuid`) REFERENCES pre_shelter_area(`area_uuid`)
);

/**
*Tracking evacuation details
*/
DROP TABLE IF EXISTS `pre_evacuation`;
CREATE TABLE `pre_evacuation` ( -- Evacuation Planning
`area_uuid` VARCHAR( 60 ) NOT NULL , -- Aread Under threat
`shelter_uuid` VARCHAR( 60 ) NOT NULL , -- Safe area
`disaster_uuid` VARCHAR( 60 ) NOT NULL , -- Disaster
`allocation` INT NOT NULL  -- Allocated Quantity
);

/**
*Disaster history
*/
DROP TABLE IF EXISTS `pre_disaster_history`;
CREATE TABLE `pre_disaster_history` ( -- Disaster History
`wrn_uuid` VARCHAR( 60 ) NOT NULL , -- ID
`disaster_uuid` VARCHAR( 60 ) NOT NULL , -- Disaster ID
`registered_date` DATETIME NOT NULL , -- Registered Date
`expired_date` DATETIME NULL , -- Expired Date
`incident_id` VARCHAR( 60 ) NULL , -- Incident ID
`type` VARCHAR( 10 ) NOT NULL , -- Type
PRIMARY KEY ( `wrn_uuid` ),
FOREIGN KEY (`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`)
);

/**
*Area history
*/
DROP TABLE IF EXISTS `pre_area_history`;
CREATE TABLE `pre_area_history` (
`warn_uuid` VARCHAR( 60 ) NOT NULL ,
`area_uuid` VARCHAR( 60 ) NOT NULL ,
`disaster_uuid` VARCHAR(60) NOT NULL,
PRIMARY KEY ( `warn_uuid` , `area_uuid`, `disaster_uuid` ),
FOREIGN KEY(`warn_uuid`) REFERENCES pre_disaster_history(`wrn_uuid`),
FOREIGN KEY(`area_uuid`) REFERENCES pre_threat_area(`area_uuid`),
FOREIGN KEY(`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`)
);

/**
*recovery planning
*/
DROP TABLE IF EXISTS `pre_recovery_plan`;
CREATE TABLE `pre_recovery_plan` (
`disaster_uuid` VARCHAR( 60 ) NOT NULL ,
`rec_id` VARCHAR( 60 ) NOT NULL ,
`access` INT NULL ,
PRIMARY KEY ( `disaster_uuid` , `rec_id` ),
FOREIGN KEY (`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`),
FOREIGN KEY (`rec_id`) REFERENCES pre_disaster_recovery(`id`)
);

/**
*Recovery Plan for areas
*/
DROP TABLE IF EXISTS `pre_area_rec_plan`;
CREATE TABLE `pre_area_rec_plan` (
`disaster_uuid` VARCHAR( 60 ) NOT NULL ,
`rec_id` VARCHAR( 60 ) NOT NULL ,
`area_uuid` VARCHAR( 60 ) NOT NULL ,
PRIMARY KEY ( `disaster_uuid` , `rec_id` , `area_uuid` ),
FOREIGN KEY (`disaster_uuid`) REFERENCES pre_disaster(`disaster_uuid`),
FOREIGN KEY (`rec_id`) REFERENCES pre_disaster_recovery(`id`),
FOREIGN KEY(`area_uuid`) REFERENCES pre_threat_area(`area_uuid`)
);

/**
* table on tracking contact details(common table)
*/
CREATE TABLE IF NOT EXISTS `contact` (
  `pgoc_uuid` varchar(60) NOT NULL,
  `opt_contact_type` varchar(10) NOT NULL default '',
  `contact_value` varchar(100) NOT NULL default '',
  PRIMARY KEY  (`pgoc_uuid`,`opt_contact_type`,`contact_value`)
);

/**
* table on tracking person details(common table)
*/
CREATE TABLE IF NOT EXISTS `person_uuid` (
  `p_uuid` varchar(60) NOT NULL,
  `full_name` varchar(100) default NULL,
  `family_name` varchar(50) default NULL,
  `l10n_name` varchar(100) default NULL,
  `custom_name` varchar(50) default NULL,
  PRIMARY KEY  (`p_uuid`)
);

DELETE FROM `field_options` WHERE `field_name` = 'opt_threat_level';
DELETE FROM `field_options` WHERE `field_name` = 'opt_recovering_term';
INSERT INTO `field_options` (`field_name`, `option_code`, `option_description`) VALUES 
('opt_threat_level', 'otl_hgh', 'high'),
('opt_threat_level', 'opt_mdt', 'moderate'),
('opt_threat_level', 'opt_low', 'low'),
('opt_recovering_term', 'ort_lng', 'long'),
('opt_recovering_term', 'ort_mid', 'mid'),
('opt_recovering_term', 'ort_sht', 'short'),
('opt_disaster_status', 'ods_pre', 'pre'),
('opt_disaster_status', 'ods_wnd', 'warned'),
('opt_disaster_status', 'ods_on', 'on'),
('opt_disaster_status', 'ods_post', 'post');






/*Disease Surviellance TABLES*/

/**
* Dropping tables if exists
* Modules: dsm 
* Last Edited: 15-May-2008 
*/

DROP TABLE IF EXISTS `diseases`;


/**
* Table to store details about disease
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE diseases 
	(dis_id varchar(60) NOT NULL PRIMARY KEY, 
	dis_name varchar(100), 
	description varchar(200),
    age_group varchar(60), 
	cause varchar(100),
    carrier varchar(100),
	med_name varchar(60),
	serial varchar(100) DEFAULT '1',
	keyword varchar(100)); 

DROP TABLE IF EXISTS `diagnosis`;


/**
* Table to store details about diagnosis
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE diagnosis 
	(dia_id varchar(60) NOT NULL PRIMARY KEY, 
	pat_id varchar(60) NOT NULL, 
	doc_id varchar(60) NOT NULL,
    prev_dia varchar(60) DEFAULT '0', 
	dia_date TIMESTAMP DEFAULT NOW(),
    gender varchar(10),
	location varchar(60),
	disease varchar(60),
	age_group varchar(60),
    FOREIGN KEY(pat_id) REFERENCES users(p_uuid),
    FOREIGN KEY(doc_id) REFERENCES users(p_uuid),
    FOREIGN KEY(disease) REFERENCES diseases(dis_id));




DROP TABLE IF EXISTS `symptoms`;


/**
* Table to store signs and symptom details
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE symptoms 
	(sym_id varchar(60) NOT NULL PRIMARY KEY, 
	upperlevel_id varchar(60), 
	description varchar(200)); 





DROP TABLE IF EXISTS `disease_symptoms`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE disease_symptoms 
	(dis_id varchar(60) NOT NULL, 
	sym_id varchar(60) NOT NULL, 
	code varchar(20), 
	priority varchar(20),
	PRIMARY KEY(dis_id,sym_id),
	FOREIGN KEY(dis_id) REFERENCES diseases(dis_id),
	FOREIGN KEY(sym_id) REFERENCES symptoms(sym_id)); 





DROP TABLE IF EXISTS `diagnosis_symptoms`;


/**
* Table to store signs and symptoms related to a patient
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE diagnosis_symptoms 
	(dia_id varchar(60) NOT NULL, 
	sym_id varchar(60) NOT NULL, 
	code varchar(20),
    PRIMARY KEY(dia_id,sym_id),
    FOREIGN KEY(dia_id) REFERENCES diagnosis(dia_id),
    FOREIGN KEY(sym_id) REFERENCES symptoms(sym_id));


DROP TABLE IF EXISTS `causative_factors`;


/**
* Table to store signs and symptom details
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE causative_factors 
	(fac_id varchar(60) NOT NULL PRIMARY KEY, 
	upperlevel_id varchar(60), 
	description varchar(200)); 





DROP TABLE IF EXISTS `disease_cau_factors`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE disease_cau_factors 
	(dis_id varchar(60) NOT NULL, 
	fac_id varchar(60) NOT NULL, 
	code varchar(20), 
	priority varchar(20),
	PRIMARY KEY(dis_id,fac_id),
	FOREIGN KEY(dis_id) REFERENCES diseases(dis_id),
	FOREIGN KEY(fac_id) REFERENCES causative_factors(fac_id)); 





DROP TABLE IF EXISTS `diagnosis_cau_factors`;


/**
* Table to store signs and symptoms related to a patient
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE diagnosis_cau_factors 
	(dia_id varchar(60) NOT NULL, 
	fac_id varchar(60) NOT NULL, 
	code varchar(20),
    PRIMARY KEY(dia_id,fac_id),
    FOREIGN KEY(dia_id) REFERENCES diagnosis(dia_id),
    FOREIGN KEY(fac_id) REFERENCES causative_factors(fac_id));


/**
* Tables for RTBS
*/

CREATE TABLE IF NOT EXISTS `rtbs_h544` (
  `notify_id` varchar(50) NOT NULL ,
  `institute` varchar(50) default NULL,
  `name_of_patient` varchar(50) default NULL,
  `name_of_the_guardian` varchar(50) default NULL,
  `disease_id` int(11) NOT NULL,
  `date_of_onset` date default NULL,
  `date_of_admission` date default NULL,
  `bht_no` varchar(20) default NULL,
  `ward` varchar(10) default NULL,
  `age` int(11) default NULL,
  `sex` enum('m','f') default NULL,
  `laboratory_results` varchar(200) default NULL,
  `home_address` varchar(200) default NULL,
  `telephone_number` varchar(15) default NULL,
  `notified_by` varchar(50) default NULL,
  `name_of_doctor` varchar(50) default NULL,
  `status_of_doctor` varchar(50) default NULL,
  `date` date default NULL,
  PRIMARY KEY  (`notify_id`),
  KEY `disease_id` (`disease_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;


CREATE TABLE IF NOT EXISTS `rtbs_disease` (
  `disease_id` int(11) NOT NULL auto_increment,
  `disease_name` varchar(50) NOT NULL,
  `disease_type` varchar(2) NOT NULL,
  PRIMARY KEY  (`disease_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `rtbs_disease_notify_to` (
  `disease_id` int(11) NOT NULL,
  `notify_to` varchar(50) NOT NULL,
  PRIMARY KEY  (`disease_id`,`notify_to`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

ALTER TABLE `rtbs_disease_notify_to`
  ADD CONSTRAINT `rtbs_disease_notify_to_ibfk_1` FOREIGN KEY (`disease_id`) REFERENCES `rtbs_disease` (`disease_id`) ON DELETE CASCADE ON UPDATE CASCADE;

ALTER TABLE `rtbs_h544`
  ADD CONSTRAINT `rtbs_h544_ibfk_1` FOREIGN KEY (`disease_id`) REFERENCES `rtbs_disease` (`disease_id`) ON DELETE NO ACTION ON UPDATE CASCADE;

/*add data*/
INSERT INTO `rtbs_disease` (`disease_id`, `disease_name`, `disease_type`) VALUES
(1, 'Cholera', 'A'),
(2, 'Plague', 'A'),
(3, 'Yellow Fever', 'A'),
(4, 'Polio Myelitis / Acute Flaccid Paralysis', 'B'),
(5, 'Diphtheria', 'B'),
(6, 'Dysentery', 'B'),
(7, 'Pertussis', 'B'),
(8, 'Enteric Fever', 'B'),
(9, 'Food Poisoning', 'B'),
(10, 'Tetanus/neonatal tetanus', 'B'),
(11, 'Measles', 'B'),
(12, 'Malaria', 'B'),
(13, 'Rubella/Congenital Rubella Syndrome', 'B'),
(14, 'Viral Hepatitis', 'B'),
(15, 'Leptospirosis', 'B'),
(16, 'Dengue Fever/ Dengue Haemorragic Fever', 'B'),
(17, 'Encephalitis (including Japanese Encephalitis)', 'B'),
(18, 'Human Rabies', 'B'),
(19, 'Mumps', 'B'),
(20, 'Meningitis', 'B'),
(21, 'Chicken Pox', 'B'),
(22, 'Simple continued fever of over 7 days or more', 'B'),
(23, 'Typhus Fever', 'B'),
(24, 'Severe Acute Respiratory Syndrome (SARS)', 'B'),
(25, 'Tuberculosis', 'B');


CREATE TABLE IF NOT EXISTS `rtbs_location` (
  `notify_id` varchar(50) NOT NULL,
  `country` varchar(50) default NULL,
  `state` varchar(50) default NULL,
  `city` varchar(50) default NULL,
  `longitude` varchar(50) default NULL,
  `latitude` varchar(50) default NULL,
  `district_id` varchar(50) default NULL,
  `moh_area` varchar(50) default NULL,
  `phi_area` varchar(50) default NULL,
  PRIMARY KEY  (`notify_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

 CREATE TABLE `rtbs_district` (
`district_id` VARCHAR( 50 ) NOT NULL ,
`district` VARCHAR( 50 ) NOT NULL ,
PRIMARY KEY ( `district_id` )
) ENGINE = InnoDB ;

ALTER TABLE `rtbs_location` ADD FOREIGN KEY ( `district_id` ) REFERENCES `rtbs_district` (
`district_id`
) ON DELETE NO ACTION ON UPDATE CASCADE ;

INSERT INTO `rtbs_district` (`district_id`, `district`) VALUES
('Ampara', 'Ampara'),
('Anuradhapura', 'Anuradhapura'),
('Badulla', 'Badulla'),
('Batticaloa', 'Batticaloa'),
('Colombo', 'Colombo'),
('Galle', 'Galle'),
('Gampaha', 'Gampaha'),
('Hambantota', 'Hambantota'),
('Jaffna', 'Jaffna'),
('Kalutara', 'Kalutara'),
('Kandy', 'Kandy'),
('Kegalle', 'Kegalle'),
('Kilinochchi', 'Kilinochchi'),
('Kurunegala', 'Kurunegala'),
('Mannar', 'Mannar'),
('Matale', 'Matale'),
('Matara', 'Matara'),
('Moneragala', 'Moneragala'),
('Mullaitivu', 'Mullaitivu'),
('Nuwara Eliya', 'Nuwara Eliya'),
('Polonnaruwa', 'Polonnaruwa'),
('Puttalam', 'Puttalam'),
('Ratnapura', 'Ratnapura'),
('Trincomalee', 'Trincomalee'),
('Vavuniya', 'Vavuniya');

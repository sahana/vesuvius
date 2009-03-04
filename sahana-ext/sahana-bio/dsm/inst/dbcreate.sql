/*Disease Surviellance TABLES*/

/**
* Dropping tables if exists
* Modules: dsm 
* Last Edited: 15-May-2008 
*/

DROP TABLE IF EXISTS `dsm_diseases`;


/**
* Table to store details about disease
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_diseases 
	(dis_id varchar(60) NOT NULL PRIMARY KEY, 
	dis_name varchar(100), 
	description varchar(200),
    age_group varchar(60), 
	cause varchar(100),
    carrier varchar(100),
	med_name varchar(60),
	serial varchar(100) DEFAULT '1',
	keyword varchar(100)); 

DROP TABLE IF EXISTS `dsm_diagnosis`;


/**
* Table to store details about diagnosis
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_diagnosis 
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




DROP TABLE IF EXISTS `dsm_symptoms`;


/**
* Table to store signs and symptom details
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_symptoms 
	(sym_id varchar(60) NOT NULL PRIMARY KEY, 
	upperlevel_id varchar(60), 
	description varchar(200)); 





DROP TABLE IF EXISTS `dsm_disease_symptoms`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_disease_symptoms 
	(dis_id varchar(60) NOT NULL, 
	sym_id varchar(60) NOT NULL, 
	code varchar(20), 
	priority varchar(20),
	PRIMARY KEY(dis_id,sym_id),
	FOREIGN KEY(dis_id) REFERENCES diseases(dis_id),
	FOREIGN KEY(sym_id) REFERENCES symptoms(sym_id)); 





DROP TABLE IF EXISTS `dsm_diagnosis_symptoms`;


/**
* Table to store signs and symptoms related to a patient
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_diagnosis_symptoms 
	(dia_id varchar(60) NOT NULL, 
	sym_id varchar(60) NOT NULL, 
	code varchar(20),
    PRIMARY KEY(dia_id,sym_id),
    FOREIGN KEY(dia_id) REFERENCES diagnosis(dia_id),
    FOREIGN KEY(sym_id) REFERENCES symptoms(sym_id));


DROP TABLE IF EXISTS `dsm_causative_factors`;


/**
* Table to store signs and symptom details
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_causative_factors 
	(fac_id varchar(60) NOT NULL PRIMARY KEY, 
	upperlevel_id varchar(60), 
	description varchar(200)); 





DROP TABLE IF EXISTS `dsm_disease_cau_factors`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_disease_cau_factors 
	(dis_id varchar(60) NOT NULL, 
	fac_id varchar(60) NOT NULL, 
	code varchar(20), 
	priority varchar(20),
	PRIMARY KEY(dis_id,fac_id),
	FOREIGN KEY(dis_id) REFERENCES diseases(dis_id),
	FOREIGN KEY(fac_id) REFERENCES causative_factors(fac_id)); 





DROP TABLE IF EXISTS `dsm_diagnosis_cau_factors`;


/**
* Table to store signs and symptoms related to a patient
* Modules: dsm
* Last Edited: JUNE-2008 virajed@opensource.lk
*/

CREATE TABLE dsm_diagnosis_cau_factors 
	(dia_id varchar(60) NOT NULL, 
	fac_id varchar(60) NOT NULL, 
	code varchar(20),
    PRIMARY KEY(dia_id,fac_id),
    FOREIGN KEY(dia_id) REFERENCES diagnosis(dia_id),
    FOREIGN KEY(fac_id) REFERENCES causative_factors(fac_id));


/**
* New tables for ICTA-BioSurvillence
*/

DROP TABLE IF EXISTS `dsm_fields`;

CREATE TABLE `dsm_fields` (
`field_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`text` TEXT NOT NULL ,
`name` TEXT NOT NULL ,
`type` VARCHAR( 100 ) NOT NULL,
`data_type` VARCHAR( 100 ) NOT NULL,
`indx` INT
);


DROP TABLE IF EXISTS `dsm_field_params`;

CREATE TABLE `dsm_field_params` (
`field_id` BIGINT NOT NULL,
`field_param_id` BIGINT NOT NULL AUTO_INCREMENT,
`param_key` VARCHAR( 200 ) NOT NULL ,
`param` TEXT,
PRIMARY KEY ( `field_param_id` )
) ;

DROP TABLE IF EXISTS `dsm_field_values`;

CREATE TABLE `dsm_field_values` (
`field_id` BIGINT NOT NULL ,
`field_value_id` BIGINT NOT NULL AUTO_INCREMENT,
`vals_text` TEXT  ,
`value` TEXT  ,
`indx` INT ,
PRIMARY KEY ( `field_value_id` )
);

DROP TABLE  IF EXISTS `dsm_field_validation`;
CREATE TABLE `dsm_field_validation` (
`validation_id` BIGINT NOT NULL AUTO_INCREMENT ,
`field_id` BIGINT NOT NULL ,
`rule` TEXT NOT NULL ,
`rule_order` INT NOT NULL DEFAULT '1',
PRIMARY KEY ( `validation_id` )
);

DROP TABLE IF EXISTS `dsm_cases`;
CREATE TABLE `dsm_cases` (
`case_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`reported_date` DATE NOT NULL ,
`last_update` DATE NOT NULL ,
`status` VARCHAR( 30 ) NOT NULL DEFAULT 'ACTIVE'
) ;

DROP TABLE  IF EXISTS `dsm_definitions`;
CREATE TABLE `dsm_definitions` (
`dis_id` VARCHAR(60) NOT NULL ,
`field_id` BIGINT NOT NULL ,
PRIMARY KEY ( `dis_id` , `field_id` )
);

DROP TABLE IF EXISTS `dsm_case_data`;
CREATE TABLE `dsm_case_data` (
`case_id` BIGINT NOT NULL ,
`data_id` BIGINT NOT NULL ,
`field_id` BIGINT NOT NULL ,
`dis_id` VARCHAR(60) NOT NULL ,
`patient_identifier` TEXT NOT NULL ,
`submission_id` BIGINT NOT NULL DEFAULT 1,
`date` date,
`value` TEXT,
PRIMARY KEY (`data_id`,`case_id`,field_id)
);

DROP TABLE IF EXISTS `dsm_case_count`;
CREATE TABLE `dsm_case_count` (
`case_id` BIGINT NOT NULL,
`dis_id` VARCHAR(60) NOT NULL ,
`date` date,
PRIMARY KEY (`case_id`)
);

DROP TABLE IF EXISTS `dsm_case_note`;
CREATE TABLE `dsm_case_note` (
`case_id` TEXT,
`dis_id` VARCHAR(60) NOT NULL ,
`note_id` BIGINT NOT NULL AUTO_INCREMENT PRIMARY KEY ,
`date` date,
`note` LONGTEXT
);

DROP TABLE IF EXISTS `dsm_diseases_risks`;
CREATE TABLE dsm_diseases_risks( 
    `dis_id` varchar(60) NOT NULL PRIMARY KEY, 
    `eff_gender` TEXT, 
    `dri_water` TEXT,
    `nutrition_level` TEXT, 
    `sanitary` TEXT,
    `seasons` TEXT
);  

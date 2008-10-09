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

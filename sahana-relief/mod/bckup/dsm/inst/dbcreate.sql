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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
*/

CREATE TABLE dsm_symptoms 
    (sym_id varchar(60) NOT NULL PRIMARY KEY, 
    upperlevel_id varchar(60), 
    description varchar(200)); 





DROP TABLE IF EXISTS `dsm_disease_symptoms`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
*/

CREATE TABLE dsm_causative_factors 
    (fac_id varchar(60) NOT NULL PRIMARY KEY, 
    upperlevel_id varchar(60), 
    description varchar(200)); 





DROP TABLE IF EXISTS `dsm_disease_cau_factors`;


/**
* Table to store signs and symptoms related to a disease
* Modules: dsm
*Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
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
* Last Edited: Mar-2009 sandaruwan[at]opensource[dot]lk
*/

CREATE TABLE dsm_diagnosis_cau_factors 
    (dia_id varchar(60) NOT NULL, 
    fac_id varchar(60) NOT NULL, 
    code varchar(20),
    PRIMARY KEY(dia_id,fac_id),
    FOREIGN KEY(dia_id) REFERENCES diagnosis(dia_id),
    FOREIGN KEY(fac_id) REFERENCES causative_factors(fac_id));


DROP TABLE IF EXISTS `dsm_diseases_risks`;

CREATE TABLE dsm_diseases_risks( 
    `dis_id` varchar(60) NOT NULL PRIMARY KEY, 
    `eff_gender` TEXT, 
    `dri_water` TEXT,
    `nutrition_level` TEXT, 
    `sanitary` TEXT,
    `seasons` TEXT
);  
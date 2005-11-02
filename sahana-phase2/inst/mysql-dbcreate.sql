/**
* MySQL database structure creation table for Sahana
*/

/*CREATE DATABASE IF NOT EXISTS sahana;
USE sahana;
*/
-- SESSIONS
DROP TABLE IF EXISTS sessions;
CREATE TABLE sessions(
	sesskey VARCHAR(32) NOT NULL,
	expiry INT NOT NULL,
	expireref VARCHAR(64),
	data TEXT NOT NULL,
	PRIMARY KEY (sesskey)
);

-- MODULES

/**
* The central table to store the status of available modules
* Modules: all
* Last changed: 2-NOV-2005 - chamindra@opensource.lk 
*/
DROP TABLE IF EXISTS modules;
CREATE TABLE modules(
	module_id VARCHAR(20) NOT NULL, -- the directory name of the module e.g. dvr, or, mpr
	version VARCHAR(10) NOT NULL, -- the module version
	active BOOL NOT NULL DEFAULT 0, -- is the module active or disabled
	PRIMARY KEY (module_id)
);

/**
* The central table to store all configuration details of the base system
* and all modules
* Modules: all
* Last changed: 2-NOV-2005 - chamindra@opensource.lk 
*/
DROP TABLE IF EXISTS config;
CREATE TABLE config(
    module_id VARCHAR(20), -- the directory name of the module e.g. dvr, or, mpr
	confkey VARCHAR(50) NOT NULL, -- the configuration key for the module
	value VARCHAR(100), -- the value 
	FOREIGN KEY (module_id) REFERENCES modules (module_id)
);


/**
* Field options meta table
* Give a custom list of options for each filed in this schema 
* prefixed with opt_. This is customizable then at deployment
* See the mysql-config.sql for default customizations
* Modules: dvr, mpr, or, cms, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS field_options;
CREATE TABLE field_options(
   field_name VARCHAR(100), -- a meta reference to the field_name
   option_code VARCHAR(20), -- a coded version of the value
   option_description VARCHAR(50) -- The nice name of the value 
);


/*** Location Classification ***/

/**
* The central table to store loactions
* Modules: dvr, mpr, rms, or, cms 
* Last changed: 28-OCT-2005 - janaka@opensource.lk  
*/

DROP TABLE IF EXISTS location;
CREATE TABLE location(
    location_id BIGINT NOT NULL AUTO_INCREMENT,
    parent_id BIGINT DEFAULT 0,
    search_id VARCHAR(20), -- a heirarchical id expressing the heirarachy
    opt_location_type VARCHAR(10),
    name VARCHAR(100) NOT NULL,
    iso_code VARCHAR(20),
    description TEXT,
    PRIMARY KEY (location_id),
    FOREIGN KEY (parent_id) REFERENCES location(location_id)
);

-- OPTIMIZATION  DEVEL
DROP TABLE IF EXISTS devel_logsql;
CREATE TABLE devel_logsql (
    created timestamp NOT NULL, 
    sql0 varchar(250) NOT NULL,
    sql1 text NOT NULL,
    params text NOT NULL,
    tracer text NOT NULL,
    timer decimal(16,6) NOT NULL
); 

/*** PERSON TABLES ***/

/**
* The central table on a person, with their associated names
* Modules: dvr, mpr, rms, or, cms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_uuid;
CREATE TABLE person_uuid (
    p_uuid BIGINT NOT NULL, -- universally unique person id
    full_name VARCHAR(100), -- the full name (contains the family name)
    family_name VARCHAR(50), -- the family name
    l10n_name VARCHAR(100), -- localized version of name
    custom_name VARCHAR(50), -- extra name field as required
    PRIMARY KEY(p_uuid)      
);

/**
* Many ID card numbers (or passport or driving licence) to person table
* Modules: dvr, mpr 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS identity_to_person;
CREATE TABLE identity_to_person (
    p_uuid BIGINT NOT NULL,
    serial VARCHAR(100), -- id card #, passport #, Driving License # etc
    opt_id_type VARCHAR(10), -- can be customized in the field options table
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);
    
/**
* Contains the Sahana system user details
* Modules: all
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/

DROP TABLE IF EXISTS users;
CREATE TABLE users (
    p_uuid BIGINT NOT NULL,
    user_name VARCHAR(100) NOT NULL,
    password VARCHAR(100),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);


/**
* Main entry table as there can be multiple entries
* per person.
* Modules: dvr, mpr 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
/*DROP TABLE IF EXISTS person_entry;
    CREATE TABLE person_entry (
    e_uuid BIGINT NOT NULL AUTO_INCREMENT,
    entry_date TIMESTAMP,
    user_uuid BIGINT,      -- details on the user who did the data entry
    reporter_uuid BIGINT,  -- details on the person who reported the entry
    p_uuid BIGINT NOT NULL,
    PRIMARY KEY (e_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (user_uuid) REFERENCES person_uuid(p_uuid)
);*/
    
/**
* Details on the person's status
* Modules: dvr, mpr, or
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_status;
CREATE TABLE person_status (
    p_uuid BIGINT NOT NULL,
    isReliefWorker TINYINT, 
    opt_status VARCHAR(10), -- missing, ingured, etc. customizable
    PRIMARY KEY (p_uuid)
);

/**
* Contact Information for a person, org or camp
* Modules: dvr, mpr, or, cms, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS contact;
CREATE TABLE contact (
    pgoc_uuid BIGINT NOT NULL, -- be either c_uuid, p_uuid or g_uuid
    opt_contact_type VARCHAR(10), -- mobile, home phone, email, IM, etc
    contact_value VARCHAR(100), 
    PRIMARY KEY (pgoc_uuid,opt_contact_type,contact_value)
    /**only pgoc_uuid should not be primary key 
    as for a person there can be several contact types 
    and values (email and mobile) or multiple mobiles
    **/
);

/**
* Details on the location of an entity (person, camp, organization)
* Modules: dvr, mpr, or, cms, rms 
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS location_details;
CREATE TABLE location_details ( 
    poc_uuid BIGINT NOT NULL, -- this can be a person, camp or organization location
    location_id VARCHAR(20), -- This gives country,province,district,town - based on l10n 
    opt_person_loc_type VARCHAR(10), -- the relation this location has to the person
    address TEXT, -- the street address        
    postcode VARCHAR(30), -- or ZIP code
    long_lat VARCHAR(20), -- logatitude and latitude (GPS location)
    PRIMARY KEY (poc_uuid,location_id),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

/**
* Contains the list of groups of people
* Modules: dvr, mpr, or
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS pgroup;
CREATE TABLE pgroup (
    g_uuid BIGINT NOT NULL AUTO_INCREMENT, -- universally unique group id
    name VARCHAR(100), -- name of the group
    opt_group_type VARCHAR(10), -- type of the group
    PRIMARY KEY (g_uuid)
);

/**
* A person can belong to multiple groups
* Modules: dvr, mpr
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_to_pgroup;
CREATE TABLE person_to_pgroup (   
    p_uuid BIGINT,
    g_uuid BIGINT
);

/**
* The main details on a person
* Modules: dvr, mpr, 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_details;
CREATE TABLE person_details (
    p_uuid BIGINT NOT NULL,
    next_kin_uuid BIGINT NOT NULL,
    birth_date DATE,
    opt_age_group VARCHAR(10),     -- The age group they belong too
    relation VARCHAR(50),
    opt_country VARCHAR(10),
    opt_race VARCHAR(10),
    opt_religion VARCHAR(10),
    opt_marital_status VARCHAR(10),
    opt_gender VARCHAR(10),
    occupation VARCHAR(100),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

/**
* Physical details of a person
* Modules: dvr, mpr, or, cms, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_physical;
CREATE TABLE person_physical (
    p_uuid BIGINT NOT NULL,
    opt_blood_type VARCHAR(10),
    height VARCHAR(10),
    weight VARCHAR(10),
    opt_eye_color VARCHAR(50),
    opt_skin_color VARCHAR(50),
    opt_hair_color VARCHAR(50),
    injuries TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

DROP TABLE IF EXISTS person_missing;
CREATE TABLE person_missing (
    p_uuid BIGINT NOT NULL,
    last_seen TEXT,
    last_clothing TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

DROP TABLE IF EXISTS person_deceased;
CREATE TABLE person_deceased (
    p_uuid BIGINT NOT NULL,
    details TEXT,
    date_of_death DATE,
    location VARCHAR(20),
    place_of_death TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (location) REFERENCES location(location_id)
);


-- ORG MAIN
DROP TABLE IF EXISTS org_main;
CREATE TABLE org_main(
	o_uuid BIGINT NOT NULL,
    parent_id BIGINT DEFAULT 0,
    name VARCHAR(100) NOT NULL ,
	opt_org_type VARCHAR(100),
	reg_no VARCHAR(100),
    man_power VARCHAR(50),
	resources VARCHAR(200),
    privacy INT(1) DEFAULT 1,
	PRIMARY KEY (o_uuid)
);

-- ORG SECTOR  INFORMATION
DROP TABLE IF EXISTS sector;
CREATE TABLE sector(
	pgoc_uuid BIGINT NOT NULL,
	opt_sector VARCHAR(100),
    PRIMARY KEY (pgoc_uuid, opt_sector)
);

-- ORG USER INFORMATION
DROP TABLE IF EXISTS org_users;
CREATE TABLE org_users(
    org_id BIGINT NOT NULL,
	user_id BIGINT NOT NULL,
	PRIMARY KEY (org_id,user_id),
	FOREIGN KEY (user_id) REFERENCES users(p_uuid),
	FOREIGN KEY (org_id) REFERENCES org_main(o_uuid)
	
);


/* ------------ TO BE USED ---------------- */

/**
* The phonetic search table stores the encoding (for Soundx, metafore, etc) 
* Modules: dvr, mpr, cms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS phonetic_word;
CREATE TABLE phonetic_word(
    encode1 VARCHAR(50),
    encode2 VARCHAR(50),
    pgl_uuid BIGINT
);
    
/* SHELTER AND CAMP TABLES */
/* --------------------------------------------------------------------------*/

/**
* Camp Registry Specific Tables added
* Modules: cms,cr
* Last changed: 01-NIV-2005 - chathra@opensource.lk  
*/

DROP TABLE IF EXISTS camp;
CREATE TABLE camp (
    c_uuid BIGINT NOT NULL,
    name VARCHAR(60),
    location_id VARCHAR(20),
    opt_camp_type VARCHAR(10),
    address TEXT,
    PRIMARY KEY (c_uuid),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

DROP TABLE IF EXISTS camp_reg;
CREATE TABLE camp_reg (
    c_uuid BIGINT NOT NULL,
    name VARCHAR(60),
    orgid BIGINT,
    contact_name VARCHAR(30),
    contact_no INT (10),
    comments VARCHAR(100),
    services INT(2),
    men INT,
    women INT,
    family INT,
    children INT,
    total INT, 
    PRIMARY KEY (c_uuid),
    FOREIGN KEY (orgid) REFERENCES org_main(o_uuid)
);

DROP TABLE IF EXISTS camp_services;
CREATE TABLE camp_services (
    c_uuid BIGINT NOT NULL,
    opt_camp_service VARCHAR(50),
    value BOOL NOT NULL default 0, 
    PRIMARY KEY (c_uuid,opt_camp_service)
    
);

DROP TABLE IF EXISTS person_camp;
CREATE TABLE person_camp(
    c_uuid BIGINT NOT NULL,
    p_uuid BIGINT NOT NULL
);


--CUSTOM CONFIGURATION LISTS (SELECT)
DROP TABLE IF EXISTS configlist;
CREATE TABLE configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	config_id BIGINT NOT NULL,
	FOREIGN KEY (config_id) REFERENCES config (config_id)
);



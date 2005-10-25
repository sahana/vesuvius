CREATE DATABASE IF NOT EXISTS sahana;
USE sahana;

-- SESSIONS
DROP TABLE IF EXISTS sessions;
CREATE TABLE sessions(
	sesskey VARCHAR(32) NOT NULL,
	expiry INT NOT NULL,
	expireref VARCHAR(64),
	data TEXT NOT NULL,
	PRIMARY KEY (sesskey)
);

-- FIELD OPTIONS TABLE
-- provides a list of options for fileds
DROP TABLE IF EXISTS field_options;
CREATE TABLE field_options(
   field_name VARCHAR(100),
   option_value VARCHAR(10),
   option_name VARCHAR(50)
);

/**** CORE LOG SCHEMA END *****/

-- MODULES
DROP TABLE IF EXISTS modules;
CREATE TABLE modules(
	module_id BIGINT NOT NULL AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	description TEXT,
	version VARCHAR(10) NOT NULL,
	active BOOL NOT NULL DEFAULT 0,
	PRIMARY KEY (module_id)
);


--CUSTOM MODULE CONFIGURATIONS
DROP TABLE IF EXISTS config;
CREATE TABLE config(
	config_id BIGINT NOT NULL AUTO_INCREMENT,
	config_group VARCHAR(100),
	name VARCHAR(50) NOT NULL,
	value TEXT,
	description TEXT,
	type VARCHAR(10),
	module_id BIGINT,
	PRIMARY KEY(config_id),
	FOREIGN KEY (module_id) REFERENCES modules (module_id)
);


--CUSTOM CONFIGURATION LISTS (SELECT)
DROP TABLE IF EXISTS configlist;
CREATE TABLE configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	config_id BIGINT NOT NULL,
	FOREIGN KEY (config_id) REFERENCES config (config_id)
);


/* Location Classification */
DROP TABLE IF EXISTS location;
CREATE TABLE location(
    location_id VARCHAR(20),
    opt_location_type VARCHAR(10),
    name VARCHAR(100) NOT NULL,
    iso_code VARCHAR(20),
    description TEXT,
    PRIMARY KEY (location_id)
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

-- Main Person ID table 
-- Contains all IDs including the UUID that gives a 100%
-- match to uniquely identify the person
DROP TABLE IF EXISTS person_uuid;
CREATE TABLE person_uuid (
    p_uuid BIGINT NOT NULL,
    name VARCHAR(100),   -- usually first name
    name_2 VARCHAR(100),   -- usually middle name
    name_3 VARCHAR(100),   -- usually aliases 
    name_4 VARCHAR(100),  -- usually surname 
    name_5 VARCHAR(100),  -- usually name of family head 
    PRIMARY KEY(p_uuid)      
);

-- Many ID card numbers (or passport or driving licence) to person table
DROP TABLE IF EXISTS identity_to_person;
CREATE TABLE identity_to_person (
    p_uuid BIGINT NOT NULL,
    serial VARCHAR(100),
    opt_id_type VARCHAR(10),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);
    

-- All users have a associated person id
DROP TABLE IF EXISTS users;
CREATE TABLE users (
    p_uuid BIGINT NOT NULL,
    username VARCHAR(100),
    password VARCHAR(100),
    acl_id INT(11),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (acl_id) REFERENCES gacl_aro(id)
);

-- Main entry table as there can be multiple entries
-- on the same person
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
    
-- Person Status
DROP TABLE IF EXISTS person_status;
CREATE TABLE person_status (
    p_uuid BIGINT NOT NULL,
    isReliefWorker TINYINT,
    opt_status VARCHAR(10),
    PRIMARY KEY (p_uuid)
);

-- Contact Information for a person, org or camp
-- mobile, home phone, email, IM
DROP TABLE IF EXISTS contact;
CREATE TABLE contact (
    pgc_uuid BIGINT NOT NULL,  -- be either c_uuid, p_uuid or g_uuid
    opt_contact_type VARCHAR(10),
    contact_value VARCHAR(100),
    PRIMARY KEY (pgc_uuid)
);

DROP TABLE IF EXISTS person_location;
CREATE TABLE person_location ( 
    p_uuid BIGINT NOT NULL,
    location_id VARCHAR(20),
    opt_person_loc_type VARCHAR(10),
    address TEXT,        
    cur_shelter VARCHAR(50),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

-- Group information
DROP TABLE IF EXISTS pgroup;
CREATE TABLE pgroup (
    g_uuid BIGINT NOT NULL AUTO_INCREMENT, 
    name VARCHAR(100),
    opt_group_type VARCHAR(10),          -- type of the group
    PRIMARY KEY (g_uuid)
);

-- Group to Persons N to M mapping
DROP TABLE IF EXISTS person_to_pgroup;
CREATE TABLE person_to_pgroup (   
    p_uuid BIGINT,
    g_uuid BIGINT
);

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
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

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
DROP TABLE IF EXISTS org_sector;
CREATE TABLE org_sector(
	org_id BIGINT NOT NULL,
	opt_org_sector VARCHAR(100),
    PRIMARY KEY (org_id, opt_org_sector),
    FOREIGN KEY (org_id) REFERENCES org_main(o_uuid)
);

-- ORG LOCATION INFORMATION
DROP TABLE IF EXISTS org_location;
CREATE TABLE org_location(
	org_id BIGINT NOT NULL,
	location_id VARCHAR(20),
    PRIMARY KEY (org_id, location_id),
	FOREIGN KEY (location_id) REFERENCES location(location_id),
	FOREIGN KEY (org_id) REFERENCES org_main(o_uuid)
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


/* SHELTER AND CAMP TABLES */
/* --------------------------------------------------------------------------*/

DROP TABLE IF EXISTS camp;
CREATE TABLE camp (
    c_uuid BIGINT NOT NULL,
    location_id VARCHAR(20),
    opt_camp_type VARCHAR(10),
    address TEXT,
    PRIMARY KEY (c_uuid),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

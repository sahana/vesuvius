/**
* MySQL database structure creation table for Sahana
*/

/*CREATE DATABASE IF NOT EXISTS sahana;
USE sahana;*/

-- SESSIONS
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
CREATE TABLE modules(
	module_id VARCHAR(20) NOT NULL, -- the directory name of the module e.g. dvr, or, mpr
	version VARCHAR(10) NOT NULL, -- the module version
	active BOOL NOT NULL DEFAULT FALSE, -- is the module active or disabled
	PRIMARY KEY (module_id)
);

/**
* The central table to store all configuration details of the base system
* and all modules
* Modules: all
* Last changed: 2-NOV-2005 - chamindra@opensource.lk 
*/
CREATE TABLE config(
    config_id BIGSERIAL,
    module_id VARCHAR(20), -- the directory name of the module e.g. dvr, or, mpr
	confkey VARCHAR(50) NOT NULL, -- the configuration key for the module
	value VARCHAR(100), -- the value 
    PRIMARY KEY(config_id),
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

CREATE TABLE location(
    loc_uuid VARCHAR(60) NOT NULL, -- universally unique location id,
    parent_id VARCHAR(60) DEFAULT NULL,
 --   search_id VARCHAR(20), -- a heirarchical id expressing the heirarachy
    opt_location_type VARCHAR(10),
    name VARCHAR(100) NOT NULL,
    iso_code VARCHAR(20),
    description TEXT,
    PRIMARY KEY (loc_uuid),
    FOREIGN KEY (parent_id) REFERENCES location(loc_uuid)
);



-- OPTIMIZATION  DEVEL
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
CREATE TABLE person_uuid (
    p_uuid VARCHAR(60) NOT NULL, -- universally unique person id
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
CREATE TABLE identity_to_person (
    p_uuid VARCHAR(60) NOT NULL,
    serial VARCHAR(100), -- id card #, passport #, Driving License # etc
    opt_id_type VARCHAR(10), -- can be customized in the field options table
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);
    
/**
* Contains the Sahana system user details
* Modules: all
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/

CREATE TABLE users (
    p_uuid VARCHAR(60) NOT NULL,
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
    e_uuid VARCHAR(60) NOT NULL AUTO_INCREMENT,
    entry_date TIMESTAMP,
    user_uuid VARCHAR(60),      -- details on the user who did the data entry
    reporter_uuid VARCHAR(60),  -- details on the person who reported the entry
    p_uuid VARCHAR(60) NOT NULL,
    PRIMARY KEY (e_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (user_uuid) REFERENCES person_uuid(p_uuid)
);*/
    
/**
* Details on the person's status
* Modules: dvr, mpr, or
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
CREATE TABLE person_status (
    p_uuid VARCHAR(60) NOT NULL,
    isReliefWorker INT, 
    opt_status VARCHAR(10), -- missing, ingured, etc. customizable
    updated TIMESTAMP DEFAULT NOW(),
    isvictim BOOL DEFAULT TRUE,
    PRIMARY KEY (p_uuid)
);

/**
* Contact Information for a person, org or camp
* Modules: dvr, mpr, or, cms, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
CREATE TABLE contact (
    pgoc_uuid VARCHAR(60) NOT NULL, -- be either c_uuid, p_uuid or g_uuid
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
CREATE TABLE location_details ( 
    poc_uuid VARCHAR(60) NOT NULL, -- this can be a person, camp or organization location
    location_id VARCHAR(60), -- This gives country,province,district,town - based on l10n 
    opt_person_loc_type VARCHAR(10), -- the relation this location has to the person
    address TEXT, -- the street address        
    postcode VARCHAR(30), -- or ZIP code
    long_lat VARCHAR(20), -- logatitude and latitude (GPS location)
    PRIMARY KEY (poc_uuid,location_id),
    FOREIGN KEY (location_id) REFERENCES location(loc_uuid)
);

/**
* Contains the list of groups of people
* Modules: dvr, mpr, or
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
CREATE TABLE pgroup (
    g_uuid VARCHAR(60) NOT NULL, -- universally unique group id
    name VARCHAR(100), -- name of the group
    opt_group_type VARCHAR(10), -- type of the group
    PRIMARY KEY (g_uuid)
);

/**
* A person can belong to multiple groups
* Modules: dvr, mpr
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
CREATE TABLE person_to_pgroup (   
    p_uuid VARCHAR(60),
    g_uuid VARCHAR(60)
);

/**
* The main details on a person
* Modules: dvr, mpr, 
* Created : 27-OCT-2005 - chamindra@opensource.lk  
* Last Updated : 07-Nov-2005 - janaka@opensource.lk
* Note: Removed the NOT NULL Constraint on next_kin_uuid
*/
CREATE TABLE person_details (
    p_uuid VARCHAR(60) NOT NULL,
    next_kin_uuid VARCHAR(60),
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
CREATE TABLE person_physical (
    p_uuid VARCHAR(60) NOT NULL,
    opt_blood_type VARCHAR(10),
    height VARCHAR(10),
    weight VARCHAR(10),
    opt_eye_color VARCHAR(50),
    opt_skin_color VARCHAR(50),
    opt_hair_color VARCHAR(50),
    injuries TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

CREATE TABLE person_missing (
    p_uuid VARCHAR(60) NOT NULL,
    last_seen TEXT,
    last_clothing TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

CREATE TABLE person_deceased (
    p_uuid VARCHAR(60) NOT NULL,
    details TEXT,
    date_of_death DATE,
    location VARCHAR(20),
    place_of_death TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (location) REFERENCES location(loc_uuid)
);


-- ORG MAIN
CREATE TABLE org_main(
	o_uuid VARCHAR(60) NOT NULL,
    parent_id VARCHAR(60) DEFAULT NULL,
    name VARCHAR(100) NOT NULL ,
	opt_org_type VARCHAR(100),
	reg_no VARCHAR(100),
    man_power VARCHAR(100),
	equipment VARCHAR(100),
	resources TEXT,
    privacy BOOLEAN DEFAULT FALSE,
    archived BOOL DEFAULT FALSE, 
	PRIMARY KEY (o_uuid),
	FOREIGN KEY (parent_id) REFERENCES org_main(o_uuid)
);

-- ORG SECTOR  INFORMATION
CREATE TABLE sector(
	pgoc_uuid VARCHAR(60) NOT NULL,
	opt_sector VARCHAR(100),
    PRIMARY KEY (pgoc_uuid, opt_sector)
);

-- ORG USER INFORMATION
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
CREATE TABLE phonetic_word(
    encode1 VARCHAR(50),
    encode2 VARCHAR(50),
    pgl_uuid VARCHAR(60)
);
    
/* SHELTER AND CAMP TABLES */
/* --------------------------------------------------------------------------*/

/**
* Camp Management System and CR  Specific Tables added
* Modules: cms
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/

CREATE TABLE camp_general (
    c_uuid VARCHAR(60) NOT NULL,
    name VARCHAR(60),
    location_id VARCHAR(20),
    opt_camp_type VARCHAR(10),
    address TEXT,
		capacity INT,
		shelters INT,
		area VARCHAR(20),
		personsPerShelter INT,
    PRIMARY KEY (c_uuid),
    FOREIGN KEY (location_id) REFERENCES location(loc_uuid)
);

/**
* Camp Management System and CR Specific Tables added
* Modules: cms
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/
CREATE TABLE camp_reg (
    c_uuid VARCHAR(60) NOT NULL,
    admin_name VARCHAR(60),
		admin_no VARCHAR(60),
		men INT,
    women INT,
    family INT,
    children INT,
    total INT, 
    PRIMARY KEY (c_uuid)
);

CREATE TABLE camp_services (
    c_uuid VARCHAR(60) NOT NULL,
    opt_camp_service VARCHAR(50),
    value BOOL NOT NULL DEFAULT FALSE, 
    PRIMARY KEY (c_uuid,opt_camp_service)
);

CREATE TABLE person_camp(
    c_uuid VARCHAR(60) NOT NULL,
    p_uuid VARCHAR(60) NOT NULL
);

CREATE TABLE camp_org(
    c_uuid VARCHAR(60) NOT NULL,
		opt_camp_service VARCHAR(50),
    o_uuid VARCHAR(60) NOT NULL,
		PRIMARY KEY (c_uuid,opt_camp_service,o_uuid)
);

CREATE TABLE camp_admin(
    c_uuid VARCHAR(60) NOT NULL,
    contact_puuid VARCHAR(60) NOT NULL,
		PRIMARY KEY (c_uuid,contact_puuid)
);

/**
* Camps in Camp Management System
*/
 
CREATE TABLE camp_cms(
    c_uuid VARCHAR(60) NOT NULL,
    camp_status VARCHAR(60) NOT NULL,
		PRIMARY KEY (c_uuid)
);

-- CUSTOM CONFIGURATION LISTS (SELECT)
CREATE TABLE configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	config_id BIGINT NOT NULL,
	FOREIGN KEY (config_id) REFERENCES config (config_id)
);

/**
* Person to Report (Contact person)  
* Modules: dvr, mpr, 
* Created : 21-Dec-2005 - janaka@opensource.lk
*/
CREATE TABLE person_to_report (
    p_uuid VARCHAR(60) NOT NULL,
    rep_uuid VARCHAR(60) NOT NULL,
    relation VARCHAR(100),
    PRIMARY KEY (p_uuid,rep_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (rep_uuid) REFERENCES person_uuid(p_uuid)
);

/**
* Audit  
* Modules: dvr, mpr, 
* Created : 21-Dec-2005 - janaka@opensource.lk
*/

CREATE TABLE audit (
    audit_id BIGSERIAL,
    updated TIMESTAMP NOT NULL DEFAULT NOW(),
    x_uuid VARCHAR(60) NOT NULL,
    u_uuid VARCHAR(60) NOT NULL,
    change_type VARCHAR(3) NOT NULL,
    change_table VARCHAR(100) NOT NULL,
    change_field VARCHAR(100) NOT NULL,
    prev_val TEXT,
    new_val TEXT,
    PRIMARY KEY(audit_id)
);


/**
* I18N/L10N specific tables
* Modules	: Framework, admin 
* Created 	: 08-Feb-2006 - sudheera@opensource.lk
* Last changed	: 21-Feb-2006 - sudheera@opensource.lk
*/

CREATE TABLE lc_fields (
    id BIGSERIAL,
    tablename VARCHAR(32) NOT NULL,
    fieldname VARCHAR(32) NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE lc_tmp_po (
    string TEXT,
    comment TEXT
);

/** 
 * Synchronization Related Tables
 * Modules : Framework, sync
 * Created : 22nd-Feb-2006 - janaka@opensource.lk
 * Last Change : 22nd-Feb-2006  - janaka@opensource.lk
 */

CREATE TABLE sync_instance (
    uuid_prefix VARCHAR(4) NOT NULL,
    name VARCHAR(100) NOT NULL,
    url TEXT NOT NULL,
    is_dsc_server BOOLEAN NOT NULL DEFAULT FALSE, -- is a discovery server
    cron_status BOOLEAN NOT NULL DEFAULT FALSE, -- cron for checking the status of the instance
    last_sync TIMESTAMP NOT NULL, -- Last Time sync with the instance
    updates_available BOOLEAN NOT NULL DEFAULT FALSE, -- This gets updated by the cron or update button
    active BOOLEAN NOT NULL DEFAULT TRUE, -- Active or deactive the instance NOTE: not remove unless the data also delete.. well
    PRIMARY KEY(uuid_prefix)
);

/** 
 * Person Image
 * Modules : Framework, sync
 * Created : 20th-Mar-2006 - janaka@opensource.lk
 * Last Change : 20th-Mar-2006  - janaka@opensource.lk
 */

CREATE TABLE image(
    image_id BIGSERIAL,
    x_uuid VARCHAR(60) NOT NULL, -- universally unique person id
    image BYTEA NOT NULL,
    image_type VARCHAR(100) NOT NULL,
    image_height INT,
    image_width INT,
    created TIMESTAMP DEFAULT NOW(),
    PRIMARY KEY (image_id)
);

/** 
 * Incident 
 * Modules : Framework
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */

CREATE TABLE incident(
    incident_id BIGSERIAL,
    parent_id BIGINT DEFAULT NULL,
    search_id VARCHAR(60),
    name VARCHAR(60),
    FOREIGN KEY (parent_id) REFERENCES incident (incident_id),
    PRIMARY KEY (incident_id)
);

/** 
 * Resources to Incidents
 * Modules : Framework
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */

CREATE TABLE resource_to_incident(
    incident_id BIGINT NOT NULL,
    x_uuid VARCHAR(60),
    FOREIGN KEY (incident_id) REFERENCES incident (incident_id),
    PRIMARY KEY (incident_id,x_uuid)
);

/** 
 * User Preferences
 * Modules : Framework
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */

CREATE TABLE user_preference(
    p_uuid VARCHAR(60) NOT NULL,
    module_id VARCHAR(20) NOT NULL,
    pref_key     VARCHAR(60) NOT NULL,
    value   VARCHAR(100),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid (p_uuid),
    FOREIGN KEY (module_id) REFERENCES modules (module_id),
    PRIMARY KEY (p_uuid,module_id,pref_key)
);

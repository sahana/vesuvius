-- SESSIONS
CREATE TABLE sessions(
	sesskey VARCHAR(32) NOT NULL,
	expiry INT NOT NULL,
	expireref VARCHAR(64),
	data TEXT NOT NULL,
	PRIMARY KEY (sesskey)
);

/**** CORE LOG SCHEMA END *****/

-- MODULES
CREATE TABLE modules(
	module_id BIGINT NOT NULL AUTO_INCREMENT,
	name VARCHAR(50) NOT NULL,
	description TEXT,
	version VARCHAR(10) NOT NULL,
	active BOOL NOT NULL DEFAULT 0,
	PRIMARY KEY (module_id)
);


--CUSTOM MODULE CONFIGURATIONS
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
CREATE TABLE configlist(
	description TEXT NOT NULL,
	value VARCHAR(50),
	config_id BIGINT NOT NULL,
	FOREIGN KEY (config_id) REFERENCES config (config_id)
);


/* Location Classification */

CREATE TABLE location_type(
    location_type_id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    PRIMARY KEY (location_type_id)
);



CREATE TABLE location(
    location_id BIGINT NOT NULL AUTO_INCREMENT,
    parent_id BIGINT DEFAULT 0,
    location_type_id BIGINT NOT NULL,
    name VARCHAR(100) NOT NULL,
    value VARCHAR(50), -- for dropdowns if needed
    decription TEXT,
    PRIMARY KEY (location_id),
    FOREIGN KEY (location_type_id) REFERENCES location_type(location_type_id)
);



/******************/

-- OPTIMIZATION  (DEVEL)
CREATE TABLE devel_logsql (
		  created timestamp NOT NULL DEFAULT NOW(),
		  sql0 varchar(250) NOT NULL,
		  sql1 text NOT NULL,
		  params text NOT NULL,
		  tracer text NOT NULL,
		  timer decimal(16,6) NOT NULL
); 

/*** PERSON TABLES ***/

-- Main person ID table 
CREATE TABLE person_id (
    p_uuid BIGINT NOT NULL AUTO_INCREMENT,
    id_1 VARCHAR(100),     -- usually nic
    id_2 VARCHAR(100),     -- usually passport #
    id_3 VARCHAR(100),     -- usually driving licence # 
    id_4 VARCHAR(100)      
);

-- All users have a associade person id
CREATE TABLE user (
    p_uuid BIGINT NOT NULL,
    username VARCHAR(100),
    password VARCHAR(100),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_id(p_uuid)
);

-- Main entry table as there can be multiple entries
-- on the same person
CREATE TABLE person_entry (
    e_uuid BIGINT NOT NULL AUTO_INCREMENT,
    entry_date TIMESTAMP,
    user_uuid BIGINT,      -- details on the user who did the data entry
    reporter_uuid BIGINT,  -- details on the person who reported the entry
    p_uuid BIGINT NOT NULL,
    PRIMARY KEY (e_uuid),
    FOREIGN KEY (p_uuid) REFERECES person_id(p_uuid),
    FOREIGN KEY (user_uuid) REFERENCES person_id(p_uuid)
);
    
-- Person names 
CREATE TABLE person_main (
    p_uuid BIGINT NOT NULL,
    name_1 VARCHAR(100),   -- usually first name
    name_2 VARCHAR(100),   -- usually middle name
    name_3 VARCHAR(100),   -- usually aliases 
    family_name_1 VARCHAR(100),  -- usually surname 
    family_name_2 VARCHAR(100),  -- usually name of family head 
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_id(p_uuid)
);

-- Contact information
CREATE TABLE person_contact (
    p_uuid  BIGINT NOT NULL,
    phone_1 VARCHAR(25),   -- usually current contact land phone
    phone_2 VARCHAR(25),   -- usually home land phone
    mobile_1 VARCHAR(25),  -- current mobile phone (SMS alert capable!) 
    mobile_2 VARCHAR(25),  -- usually mobile phone
    email_1 VARCHAR(200),
    email_2 VARCHAR(200),
    im_1 VARCHAR(200),     -- instant messenger id 
    im_2 VARCHAR(200),     -- instant messenger id 
    address_1 TEXT,        -- usually current address
    address_2 TEXT,        -- usually home address 
    address_3 TEXT,        -- usually previous address
    current_shelter,       -- if at a current shelter
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_id(p_uuid)
);

CREATE TABLE group (
    g_uuid BIGINT NOT NULL AUTO_INCREMENT, 
    name VARCHAR(100),
    g_type TINYINT,          -- type of the group
    contact_1_uuid BIGINT, 
    contact_2_uuid BIGINT, 
    PRIMARY KEY (g_uuid),
    FOREIGN KEY (contact_1_uuid) REFERENCES person_id(p_uuid),
    FOREIGN KEY (contact_2_uuid) REFERENCES person_id(p_uuid)
);

CREATE TABLE group_type (
);
    
CREATE TABLE people_working_details (
    form_id BIGINT NOT NULL,
    organization TEXT,
    address TEXT,
    phone TEXT,
    PRIMARY KEY (form_id),
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE people_location (
    form_id BIGINT NOT NULL,
    location_id BIGINT NOT NULL,
    PRIMARY KEY (form_id, location_id),
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

CREATE TABLE people_extended (
    form_id BIGINT NOT NULL,
    race TEXT,
    religion TEXT,
    marital_status VARCHAR(1),
    PRIMARY KEY (form_id),
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_group (
    group_id BIGINT NOT NULL AUTO_INCREMENT,
    group_name TEXT,
    group_type TEXT,
    PRIMARY KEY (group_id)
);

CREATE TABLE dvr_people_group (
    form_id BIGINT NOT NULL,
    group_id BIGINT NOT NULL,   
    PRIMARY KEY (form_id, group_id),
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id),
    FOREIGN KEY (group_id) REFERENCES dvr_group(group_id)
);

CREATE TABLE dvr_group_extended (
    group_id BIGINT NOT NULL,
    race TEXT,
    ethnic_group TEXT,
    other TEXT,
    PRIMARY KEY (group_id),
    FOREIGN KEY (group_id) REFERENCES dvr_group(group_id)
);

CREATE TABLE dvr_next_kin (
    form_id BIGINT NOT NULL,
    next_kin_id BIGINT NOT NULL,
    relation TEXT,
    PRIMARY KEY (form_id, next_kin_id),
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id),
    FOREIGN KEY (next_kin_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_medical (
    form_id BIGINT NOT NULL,
    blood_type VARCHAR(10),
    height VARCHAR(10),
    weight VARCHAR(10),
    eye_color VARCHAR(50),
    skin_color VARCHAR(50),
    hair_color VARCHAR(50),
    
    PRIMARY KEY (form_id) ,
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_missing (
    form_id BIGINT NOT NULL,
    last_seen TEXT,
    last_clothing TEXT,
    comments TEXT,
    PRIMARY KEY (form_id) ,
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_deceased (
    form_id BIGINT NOT NULL,
    deceased TEXT,
    date_of_death TIMESTAMP,
    place_of_death TEXT,
    comments TEXT,
    PRIMARY KEY (form_id) ,
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_injured (
    form_id BIGINT NOT NULL,
    injury_type TEXT,
    immediate_needs TEXT,
    comments TEXT,
    PRIMARY KEY (form_id) ,
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);

CREATE TABLE dvr_displaced (
    form_id BIGINT NOT NULL,
    current_address TEXT,
    previous_address TEXT,
    PRIMARY KEY (form_id) ,
    FOREIGN KEY (form_id) REFERENCES people_reg(form_id)
);


/* This is changed

CREATE TABLE metadata (
    meta_id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(50) NOT NULL,
    caption VARCHAR(50),
    type VARCHAR(50),
    form_meta TEXT,
    table_name VARCHAR(50),
    validation_func VARCHAR(50),
    PRIMARY KEY (meta_id)
);

CREATE TABLE module_metadata(
    module_id BIGINT NOT NULL,
    meta_id BIGINT NOT NULL,
    section VARCHAR(50),
    forms INT,
    form_meta TEXT,
    field_list TEXT,
    element_order INT,
    PRIMARY KEY(module_id,meta_id),
    FOREIGN KEY (meta_id) REFERENCES metadata(meta_id),
    FOREIGN KEY (module_id) REFERENCES modules(module_id)
);

CREATE TABLE people_reg(
    rec_id BIGINT NOT NULL AUTO_INCREMENT,
    form_id VARCHAR(100) NOT NULL,
    meta_id BIGINT NOT NULL,
    updated TIMESTAMP NOT NULL DEFAULT NOW(),
    active BOOLEAN NOT NULL DEFAULT TRUE,
    PRIMARY KEY (rec_id),
    FOREIGN KEY (meta_id) REFERENCES metadata(meta_id)
);

CREATE TABLE metadata_int(
    rec_id BIGINT NOT NULL,
    value BIGINT,
    PRIMARY KEY(rec_id),
    FOREIGN KEY (rec_id) REFERENCES people_reg(rec_id)
);

CREATE TABLE metadata_text(
    rec_id BIGINT NOT NULL,
    value TEXT,
    PRIMARY KEY(rec_id),
    FOREIGN KEY (rec_id) REFERENCES people_reg(rec_id)
);
   
CREATE TABLE metadata_date(
    rec_id BIGINT NOT NULL,
    value timestamp,
    PRIMARY KEY(rec_id),
    FOREIGN KEY (rec_id) REFERENCES  people_reg(rec_id)
); 

-- USERS
CREATE TABLE users(
    rec_id BIGINT NOT NULL,
	username VARCHAR(10) NOT NULL,
	password VARCHAR(40) NOT NULL,
	PRIMARY KEY (rec_id),
	FOREIGN KEY (rec_id) REFERENCES people_reg(rec_id)
);

COMMENT ON TABLE users IS 'User Information';

CREATE TABLE dirty_tables(
    tablename TEXT NOT NULL,
    updated TIMESTAMP NOT NULL DEFAULT NOW(),
    PRIMARY KEY (tablename)
);
*/



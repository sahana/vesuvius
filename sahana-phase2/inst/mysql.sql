DROP DATABASE sahana;
CREATE DATABASE sahana;
USE sahana;

-- SESSIONS
CREATE TABLE sessions(
	sesskey VARCHAR(32) NOT NULL,
	expiry INT NOT NULL,
	expireref VARCHAR(64),
	data TEXT NOT NULL,
	PRIMARY KEY (sesskey)
);

-- FIELD OPTIONS TABLE
-- provides a list of options for fileds
CREATE TABLE field_options(
   field_name VARCHAR(100),
   option_value VARCHAR(10),
   option_name VARCHAR(50),
   PRIMARY KEY (field_name,option_value)
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
insert into location_type(name,description) values('country','countries');
insert into location_type(name,description) values('province','provinces');
insert into location_type(name,description) values('district','districts');
insert into location_type(name,description) values('village','villages');

CREATE TABLE location(
    location_id BIGINT NOT NULL AUTO_INCREMENT,
    parent_id BIGINT DEFAULT 0,
    location_type_id BIGINT NOT NULL,
    iso_code VARCHAR(20),
    name VARCHAR(100) NOT NULL,
    value VARCHAR(50), -- for dropdowns if needed
    description TEXT,
    PRIMARY KEY (location_id),
    FOREIGN KEY (location_type_id) REFERENCES location_type(location_type_id)
);

insert into location(parent_id,location_type_id,name,value,description) values(0,1,'Sri Lanka','lk','Sri Lanka added as a country');
insert into location(parent_id,location_type_id,name,value,description) values(0,1,'Pakistan','pk','Pakistan added as a country');
insert into location(parent_id,location_type_id,name,value,description) values(0,1,'United Kingdom','uk','United Kingdom added as a country');
insert into location(parent_id,location_type_id,name,value,description) values(0,1,'United States','us','United States added as a country');
insert into location(parent_id,location_type_id,name,value,description) values(1,2,'Western','wes','Western  added as a province in Sri Lanka');
insert into location(parent_id,location_type_id,name,value,description) values(5,3,'Colombo','cmb','Colombo added as a district in Srilanka Western Province');
insert into location(parent_id,location_type_id,name,value,description) values(6,4,'Pettah','pet','pettah added as a village in Srilanka Western Province');

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

-- Main Person ID table 
-- Contains all IDs including the UUID that gives a 100%
-- match to uniquely identify the person
CREATE TABLE person_uuid (
    p_uuid BIGINT NOT NULL,
    PRIMARY KEY(p_uuid)      
);

-- Many ID card numbers (or passport or driving licence) to person table
CREATE TABLE identity_to_person (
    p_uuid BIGINT NOT NULL,
    serial VARCHAR(100),
    opt_id_type VARCHAR(10),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);
    

-- All users have a associated person id
CREATE TABLE user (
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
CREATE TABLE person_entry (
    e_uuid BIGINT NOT NULL AUTO_INCREMENT,
    entry_date TIMESTAMP,
    user_uuid BIGINT,      -- details on the user who did the data entry
    reporter_uuid BIGINT,  -- details on the person who reported the entry
    p_uuid BIGINT NOT NULL,
    PRIMARY KEY (e_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (user_uuid) REFERENCES person_uuid(p_uuid)
);
    
-- Person Names 
CREATE TABLE person_name (
    p_uuid BIGINT NOT NULL,
    name_1 VARCHAR(100),   -- usually first name
    name_2 VARCHAR(100),   -- usually middle name
    name_3 VARCHAR(100),   -- usually aliases 
    family_name_1 VARCHAR(100),  -- usually surname 
    family_name_2 VARCHAR(100),  -- usually name of family head 
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

-- Person Status
CREATE TABLE person_status (
    p_uuid BIGINT NOT NULL,
    isReliefWorker TINYINT,
    opt_status VARCHAR(10),
    PRIMARY KEY (p_uuid)
);

-- Contact Information for a person, org or camp
-- mobile, home phone, email, IM
CREATE TABLE contact (
    pgc_uuid BIGINT NOT NULL,  -- be either c_uuid, p_uuid or g_uuid
    opt_contact_type VARCHAR(10),
    contact_value VARCHAR(100),
    PRIMARY KEY (pgc_uuid)
);

CREATE TABLE person_location ( 
    p_uuid BIGINT NOT NULL,
    location_id BIGINT,
    opt_person_loc_type VARCHAR(10),
    address TEXT,        
    cur_shelter VARCHAR(50),
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

-- Group information
CREATE TABLE pgroup (
    g_uuid BIGINT NOT NULL AUTO_INCREMENT, 
    name VARCHAR(100),
    opt_group_type VARCHAR(10),          -- type of the group
    PRIMARY KEY (g_uuid)
);

-- Group to Persons N to M mapping
CREATE TABLE person_to_pgroup (   
    p_uuid BIGINT,
    g_uuid BIGINT
);

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

CREATE TABLE person_missing (
    p_uuid BIGINT NOT NULL,
    last_seen TEXT,
    last_clothing TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

CREATE TABLE person_deceased (
    p_uuid BIGINT NOT NULL,
    details TEXT,
    date_of_death DATE,
    location BIGINT,
    place_of_death TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (location) REFERENCES location(location_id)
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
    p_uuid VARCHAR(100) NOT NULL,
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

/* SCHEMA for Organization Registry */
/* author chathra   */
/* author ravindra  */
/* prefix : org_ */

-- ORG MAIN
CREATE TABLE org_main(
	/*id BIGINT NOT NULL AUTO_INCREMENT,*/
	id BIGINT NOT NULL,
    parent_id BIGINT DEFAULT 0,
    name VARCHAR(100) NOT NULL ,
	or_type BIGINT NOT NULL,
	reg_no VARCHAR(100),
    man_power VARCHAR(50),
	resources VARCHAR(200),
    privacy INT(1) DEFAULT 1,
	PRIMARY KEY (id),
	FOREIGN KEY (or_type) REFERENCES org_types(id)
);

-- ORG TYPE
CREATE TABLE org_types(
	id BIGINT NOT NULL AUTO_INCREMENT,
	org_type VARCHAR(50),
	PRIMARY KEY (id)
);
insert into org_types(org_type)values("Government");
insert into org_types(org_type)values("Private");
insert into org_types(org_type)values("Multinational");
insert into org_types(org_type)values("Bilateral");

-- ORG SECTORS
CREATE TABLE org_sector_types(

	id BIGINT NOT NULL AUTO_INCREMENT,
	sector VARCHAR(50),
	PRIMARY KEY (id)
);

insert into org_sector_types(sector)values("Agriculture");
insert into org_sector_types(sector)values("Area Development");
insert into org_sector_types(sector)values("Communications");
insert into org_sector_types(sector)values("Disaster Preperation");
insert into org_sector_types(sector)values("Energy");
insert into org_sector_types(sector)values("Health");
insert into org_sector_types(sector)values("Fisheries");

-- ORG SECTOR  INFORMATION
CREATE TABLE org_sector(
	org_id BIGINT NOT NULL,
	sector_id BIGINT NOT NULL,
    PRIMARY KEY (org_id, sector_id),
    FOREIGN KEY (org_id) REFERENCES org_main(id),
    FOREIGN KEY (sector_id) REFERENCES org_sector_types(id)
);

-- ORG LOCATION INFORMATION
CREATE TABLE org_location(
	org_id BIGINT NOT NULL,
	location_id BIGINT NOT NULL,
    PRIMARY KEY (org_id, location_id),
	FOREIGN KEY (location_id) REFERENCES location(location_id),
	FOREIGN KEY (org_id) REFERENCES org_main(id)
);

-- ORG USER INFORMATION
CREATE TABLE org_users(
    org_id BIGINT NOT NULL,
	user_id BIGINT NOT NULL,
	PRIMARY KEY (org_id,user_id),
	FOREIGN KEY (user_id) REFERENCES person_uuid(p_uuid),
	FOREIGN KEY (org_id) REFERENCES org_main(id)
);


/* SHELTER AND CAMP TABLES */
/* --------------------------------------------------------------------------*/

CREATE TABLE camp (
    c_uuid BIGINT NOT NULL,
    location_id BIGINT,
    opt_camp_type VARCHAR(10),
    address TEXT,
    PRIMARY KEY (c_uuid),
    FOREIGN KEY (location_id) REFERENCES location(location_id)
);

/* CONFIGURATION DATA AND VALUES */
/* ------------------------------------------------------------------------ */

-- GROUP TYPES
INSERT INTO field_options VALUES ('opt_group_type','fam','family');
INSERT INTO field_options VALUES ('opt_group_type','com','company');
INSERT INTO field_options VALUES ('opt_group_type','soc','society');
INSERT INTO field_options VALUES ('opt_group_type','oth','other');

-- IDENTITY CARD / PASSPORT TYPES
INSERT INTO field_options VALUES('opt_id_type','nic','National Identity Card');
INSERT INTO field_options VALUES('opt_id_type','pas','Passport');
INSERT INTO field_options VALUES('opt_id_type','dln','Driving License Number');
INSERT INTO field_options VALUES('opt_id_type','oth','Other');

-- PERSON STATUS VALUES
INSERT INTO field_options VALUES ('opt_status','ali','Alive & Well');
INSERT INTO field_options VALUES ('opt_status','mis','Missing');
INSERT INTO field_options VALUES ('opt_status','inj','Injured');
INSERT INTO field_options VALUES ('opt_status','dec','Deceased');

-- PERSON CONTACT TYPES
INSERT INTO field_options VALUES ('opt_contact_type','home','Home Phone (permanent address)');
INSERT INTO field_options VALUES ('opt_contact_type','pmob','Personal Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','curr','Current Phone');
INSERT INTO field_options VALUES ('opt_contact_type','cmob','Current Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','emai','Email address');
INSERT INTO field_options VALUES ('opt_contact_type','inst','Instant Messenger');

-- PERSON LOCATION TYPES 
INSERT INTO field_options VALUES ('opt_person_loc_type','hom','Permanent home address)');
INSERT INTO field_options VALUES ('opt_person_loc_type','imp','Impact location');
INSERT INTO field_options VALUES ('opt_person_loc_type','cur','Current location');

-- AGE GROUP VALUES
INSERT INTO field_options VALUES ('opt_age_group','inf','Infant (0-1)');
INSERT INTO field_options VALUES ('opt_age_group','chi','Child (1-15)');
INSERT INTO field_options VALUES ('opt_age_group','you','Young Adult (16-21)');
INSERT INTO field_options VALUES ('opt_age_group','adu','Adult (22-50)');
INSERT INTO field_options VALUES ('opt_age_group','sen','Senior Citizen (50+)');

-- COUNTRY VALUES
INSERT INTO field_options VALUES ('opt_country','uk','United Kingdom');
INSERT INTO field_options VALUES ('opt_country','lanka','Sri Lanka');

-- RACE VALUES 
INSERT INTO field_options VALUES ('opt_race','sing1','Sinhalese');
INSERT INTO field_options VALUES ('opt_race','tamil','Tamil');
INSERT INTO field_options VALUES ('opt_race','other','Other');

-- RELIGION VALUES 
INSERT INTO field_options VALUES ('opt_religion','bud','Buddhist');
INSERT INTO field_options VALUES ('opt_religion','chr','Christian');
INSERT INTO field_options VALUES ('opt_religion','oth','Other');

-- MARITIAL STATUS VALUES 
INSERT INTO field_options VALUES ('opt_marital_status','sin','Single');
INSERT INTO field_options VALUES ('opt_marital_status','mar','Married');
INSERT INTO field_options VALUES ('opt_marital_status','div','Divorced');

-- BLOOD TYPE VALUES 
INSERT INTO field_options VALUES ('opt_blood_type','ab','AB');
INSERT INTO field_options VALUES ('opt_blood_type','a+','A+');
INSERT INTO field_options VALUES ('opt_blood_type','o','O');

-- EYE COLOR VALUES
INSERT INTO field_options VALUES ('opt_eye_color','bla','Black');
INSERT INTO field_options VALUES ('opt_eye_color','bro','Light Brown');
INSERT INTO field_options VALUES ('opt_eye_color','blu','Blue');
INSERT INTO field_options VALUES ('opt_eye_color','oth','Other');

-- SKIN COLOR VALUES
INSERT INTO field_options VALUES ('opt_skin_color','bla','Black');
INSERT INTO field_options VALUES ('opt_skin_color','bro','Dark Brown');
INSERT INTO field_options VALUES ('opt_skin_color','fai','Fair');
INSERT INTO field_options VALUES ('opt_skin_color','whi','White');
INSERT INTO field_options VALUES ('opt_skin_color','oth','Other');

-- HAIR COLOR VALUES
INSERT INTO field_options VALUES ('opt_hair_color','bla','Black');
INSERT INTO field_options VALUES ('opt_hair_color','bro','Brown');
INSERT INTO field_options VALUES ('opt_hair_color','red','Red');
INSERT INTO field_options VALUES ('opt_hair_color','blo','Blond');
INSERT INTO field_options VALUES ('opt_hair_color','oth','Other');

-- CAMP TYPE VALUES 
INSERT INTO field_options VALUES ('opt_camp_type','ngo','NGO Run Camp');
INSERT INTO field_options VALUES ('opt_camp_type','tmp','Temporary Shelter');
INSERT INTO field_options VALUES ('opt_camp_type','gov','Government Run Camp');

/**
* MySQL database structure creation table for Sahana
*/
                    /**drop tables **/

-- general tables

-- DROP TABLE IF EXISTS config;
DROP TABLE IF EXISTS org_users;
DROP TABLE IF EXISTS users;
DROP TABLE IF EXISTS sys_user_to_group;
DROP TABLE IF EXISTS user_preference;
DROP TABLE IF EXISTS location_details;
DROP TABLE IF EXISTS identity_to_person;
DROP TABLE IF EXISTS person_details;
DROP TABLE IF EXISTS person_physical;
DROP TABLE IF EXISTS person_missing;
DROP TABLE IF EXISTS person_deceased;
DROP TABLE IF EXISTS person_to_report;
DROP TABLE IF EXISTS group_details;
DROP TABLE IF EXISTS org_main;
DROP TABLE IF EXISTS resource_to_shelter;
DROP TABLE IF EXISTS camp_general;
DROP TABLE IF EXISTS resource_to_incident;
DROP TABLE IF EXISTS incident;
DROP TABLE IF EXISTS sahana_version;

-- drop tables from lib_uuid


DROP TABLE IF EXISTS person;
DROP TABLE IF EXISTS organization;
-- DROP TABLE IF EXISTS loc_seq;
DROP TABLE IF EXISTS landmark;
DROP TABLE IF EXISTS log;
DROP TABLE IF EXISTS camp;
DROP TABLE IF EXISTS gis;
DROP TABLE IF EXISTS wikimap;
DROP TABLE IF EXISTS request;
DROP TABLE IF EXISTS pledge;
DROP TABLE IF EXISTS catalogue;
DROP TABLE IF EXISTS report;
DROP TABLE IF EXISTS messaging;
DROP TABLE IF EXISTS inventory;
DROP TABLE IF EXISTS unit;
DROP TABLE IF EXISTS unit_type;
DROP TABLE IF EXISTS loc_seq;



/**================= System and Config Tables =======================**/

/**
* The central table to store all configuration details of the base system
* and all modules
* Modules: all
* Last changed: 2-NOV-2005 - chamindra@opensource.lk 
*/
DROP TABLE IF EXISTS config;
-- no reporting
CREATE TABLE config(
    config_id BIGINT NOT NULL AUTO_INCREMENT,
    module_id VARCHAR(20), -- the directory name of the module e.g. dvr, or, mpr
	confkey VARCHAR(50) NOT NULL, -- the configuration key for the module
	value VARCHAR(100), -- the value 
    PRIMARY KEY(config_id),
	FOREIGN KEY (module_id) REFERENCES modules (module_id)
);

/** 
 * Tables for Module Manager
 */
DROP TABLE IF EXISTS modules;

CREATE TABLE modules (
`module` VARCHAR( 20 ) NOT NULL ,
`status` VARCHAR( 50 ) NOT NULL ,
`extra` TEXT NOT NULL ,
PRIMARY KEY ( `module` )
);


/**
* Field options meta table
* Give a custom list of options for each field in this schema 
* prefixed with opt_. This is customizable then at deployment
* See the mysql-config.sql for default customizations
* Modules: dvr, mpr, or, cr, rms, sm ,cs
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS field_options;
CREATE TABLE field_options(
   field_name VARCHAR(100), -- a meta reference to the field_name
   option_code VARCHAR(20), -- a coded version of the value
   option_description VARCHAR(50) -- The nice name of the value 
);

/** 
 * Synchronization Related Tables
 * Modules : Framework, sync
 * Created : 22nd-Feb-2006 - janaka@opensource.lk
 * Last Change : 4th-Sep-2006  - jo@opensource.lk
 */

DROP TABLE IF EXISTS sync_instance;
CREATE TABLE sync_instance (
    base_uuid VARCHAR(4) NOT NULL, -- Instance id
    owner VARCHAR(100), -- Instance owner's name
    contact TEXT, -- Contact details of the instance owner
    url VARCHAR(100) DEFAULT NULL, -- Server url if exists
    last_update TIMESTAMP NOT NULL, -- Last Time sync with the instance
    sync_count INT DEFAULT 0, -- Number of times synchronized
    PRIMARY KEY(base_uuid)
);

/**
 * Setup Related Tables
 * Modules : Not Applicable
 * Created : 09-June-2008 - Ravith Botejue
 * Last Change : 10-June-2008 Ravith Botejue
 * 
 * ** IMPORTANT - Removing the ` in the query below will make it invalid.
 * Even though this violates the style, it is absolutely required.
 */
CREATE TABLE `sahana_version` (
    `sahana_version` VARCHAR( 20 ) NOT NULL , -- Version String
    `sahana_release` VARCHAR( 40 ) NOT NULL , -- Release String
    `release_date` VARCHAR( 40 ) NOT NULL , -- Release Date
    `release_info` LONGTEXT NOT NULL , -- Release Info
    PRIMARY KEY ( `sahana_version` , `sahana_release` , `release_date` )
);
/**================= Security Tables ================================**/

/**
* Contains the Sahana system user details
* Modules: all
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/

/**
* The central table on a person, with their associated names
* Modules: dvr, mpr, rms, cr 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_uuid;
CREATE TABLE person_uuid (
    p_uuid VARCHAR(60) NOT NULL, -- universally unique person id
    full_name VARCHAR(100), -- the full name (contains the family name)
    family_name VARCHAR(50), -- the family name
    l10n_name VARCHAR(100), -- localized version of name
    custom_name VARCHAR(50), -- extra name field as required
    PRIMARY KEY(p_uuid)      
);


DROP TABLE IF EXISTS users;
-- no reporting
CREATE TABLE users (
    p_uuid VARCHAR(60) NOT NULL,  -- reference to the persons uuid
    user_name VARCHAR(100) NOT NULL,
    password VARCHAR(128), -- encrypted password
    salt VARCHAR(100), -- encrypted password
    changed_timestamp BIGINT NOT NULL,
    status VARCHAR(60) DEFAULT "active",
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

alter table users add unique (user_name);

/**
* Contains the Sahana system user alternative login details
* Modules: all
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS alt_logins;
CREATE TABLE alt_logins (
    p_uuid VARCHAR(60) NOT NULL,  -- reference to the persons uuid
    user_name VARCHAR(100) NOT NULL,
    type VARCHAR(60) DEFAULT "openid",
    PRIMARY KEY (p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

/** 
* Contains the last three passwords of users,to block reusing of passwords 
* Modules: framework
* Last changed: 18-JUL-2007 - ravindra@opensource.lk
**/

DROP TABLE IF EXISTS old_passwords;
CREATE TABLE old_passwords (
    p_uuid VARCHAR(60) NOT NULL,  -- reference to the persons uuid
    password VARCHAR(100), -- encrypted password
    changed_timestamp BIGINT NOT NULL,
    PRIMARY KEY (p_uuid,password),
    FOREIGN KEY (p_uuid) REFERENCES users(p_uuid)
);

/** 
* Contains the log of events(mainly login, password cracking attempts)
* Modules: framework
* Last changed: 18-JUL-2007 - ravindra@opensource.lk
**/

DROP TABLE IF EXISTS password_event_log;
CREATE TABLE password_event_log (
    log_id BIGINT NOT NULL AUTO_INCREMENT,
    changed_timestamp BIGINT NOT NULL ,
    p_uuid VARCHAR(60) NOT NULL,  -- reference to the persons uuid
    user_name VARCHAR(100) NOT NULL,
    comment VARCHAR(100) NOT NULL,
    event_type INT DEFAULT 1,
    PRIMARY KEY (log_id),
    FOREIGN KEY (p_uuid) REFERENCES users(p_uuid)
);


/** 
* Contains the system user groups 
* Modules: framework
* Last changed: 2-OCT-2006 - chamindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_user_groups;
CREATE TABLE sys_user_groups (
    group_id INT NOT NULL,
    group_name VARCHAR(40) NOT NULL,
    PRIMARY KEY (group_id)
);

/** 
* Contains the mapping from a user to a system group
* Modules: framework
* Last changed: 2-OCT-2006 - chamindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_user_to_group;
CREATE TABLE sys_user_to_group (
    group_id INT NOT NULL,
    p_uuid VARCHAR(60) NOT NULL,
    PRIMARY KEY(group_id,p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (group_id) REFERENCES sys_user_groups(group_id) 
);
 
/** 
* Contains the data classification levels
* Modules: framework
* Last changed: 1-May-2007 - ravindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_data_classifications;
CREATE TABLE sys_data_classifications(
    level_id INT NOT NULL,
    level VARCHAR(60) NOT NULL,
    PRIMARY KEY (level_id)
);


/** 
* Contains the mapping from a role to a data classification 
* Modules: framework
* Last changed: 1-May-2007 - ravindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_group_to_data_classification;
CREATE TABLE sys_group_to_data_classification (
    group_id INT NOT NULL,
    level_id INT NOT NULL,
    crud VARCHAR(4) NOT NULL,
    PRIMARY KEY (group_id,level_id),
    FOREIGN KEY (group_id) REFERENCES sys_user_groups(group_id),
    FOREIGN KEY (level_id) REFERENCES sys_data_classifications(level_id) 
);


/** 
* Contains the data classification levels
* Modules: framework
* Last changed: 1-May-2007 - ravindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_tablefields_to_data_classification;
CREATE TABLE sys_tablefields_to_data_classification(
    table_field VARCHAR(50) NOT NULL,
    level_id INT NOT NULL,
    FOREIGN KEY (level_id) REFERENCES sys_data_classifications(level_id),
    PRIMARY KEY (table_field,level_id)
);


/** 
* specifies whether a module is enabled for a sys group or not
* Modules: framework
* Last changed: 19-AUG-2007 -ravindra@opensource.lk
**/
DROP TABLE IF EXISTS sys_group_to_module;
CREATE TABLE sys_group_to_module (
    group_id INT NOT NULL,
    module VARCHAR(60) NOT NULL,
    status VARCHAR(60) NOT NULL,
    PRIMARY KEY(group_id,module),
    FOREIGN KEY (group_id) REFERENCES sys_user_groups(group_id) 
);
 
/**================= Shared Tables ==================================**/

/**
* The phonetic search table stores the encoding (for Soundx, metafore, etc) 
* Modules: dvr, mpr, cr 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS phonetic_word;
CREATE TABLE phonetic_word(
    encode1 VARCHAR(50),
    encode2 VARCHAR(50),
    pgl_uuid VARCHAR(60)
);


/**
* Contact Information for a person, org or camp
* Modules: dvr, mpr, or, cr, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS contact;
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
 * User Preferences
 * Modules : Framework
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */

DROP TABLE IF EXISTS user_preference;
CREATE TABLE user_preference(
    p_uuid VARCHAR(60) NOT NULL,
    module_id VARCHAR(20) NOT NULL,
    pref_key     VARCHAR(60) NOT NULL,
    value   VARCHAR(100),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid (p_uuid),

    PRIMARY KEY (p_uuid,module_id,pref_key)
);


/**
* Contains the the information on the sector that the org 
* group or person is involved in 
* Modules: or
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS sector;
CREATE TABLE sector(
	pgoc_uuid VARCHAR(60) NOT NULL,
	opt_sector VARCHAR(100),
    PRIMARY KEY (pgoc_uuid, opt_sector)
);

/**
* Chronolology table gives a history of events on data
* Modules: all 
* Created : 28-Nov-2006 - chamindra@opensource.lk
*/
DROP TABLE IF EXISTS chronology;
CREATE TABLE chronology(
    log_uuid VARCHAR(60) NOT NULL, -- the log identifier
    event_date DATETIME,           -- the date and time of the event
    pgoc_uuid VARCHAR(60),         -- the entity uuid that this associates to
    opt_cron_type VARCHAR(3),      -- type of event
    module VARCHAR(10),             
    action VARCHAR(10),            -- action
    user_uuid VARCHAR(60), 
    comments VARCHAR(100),         -- description of changes
    details VARCHAR(200)           -- more detailed description of the changes
); 
    

/**
* Auditor log table 
* Modules: dvr, mpr, 
* Created : 21-Dec-2005 - janaka@opensource.lk
*/
DROP TABLE IF EXISTS audit;
CREATE TABLE audit (
    audit_id BIGINT NOT NULL AUTO_INCREMENT,
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



/**================= Entity: Location  ===================**/

/**
* The central table to store loactions
* Modules: dvr, mpr, rms, or, cr, sm
* Last changed: 28-OCT-2005 - janaka@opensource.lk  
*/
DROP TABLE IF EXISTS location;
CREATE TABLE location(
    loc_uuid VARCHAR(60) NOT NULL, -- universally unique location id,
    parent_id VARCHAR(60) DEFAULT NULL, -- parent location id
    opt_location_type VARCHAR(10), -- location type taken from field_opts
    name VARCHAR(100) NOT NULL,
    iso_code VARCHAR(20),
    description TEXT,
    PRIMARY KEY (loc_uuid)
);

/**
* Details on the location of an entity (person, camp, organization)
* Modules: dvr, mpr, or, cr, rms, sm 
* Last changed: 27-OCT-2005 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS location_details;
CREATE TABLE location_details ( 
    poc_uuid VARCHAR(60) NOT NULL, -- this can be a person, camp or organization location
    location_id VARCHAR(60), -- This gives country,province,district,town - based on l10n 
    opt_person_loc_type VARCHAR(10), -- the relation this location has to the person
    address TEXT, -- the street address        
    postcode VARCHAR(30), -- or ZIP code
    long_lat VARCHAR(20), -- logatitude and latitude (GPS location)
    PRIMARY KEY (poc_uuid,location_id)
    
);

/**================= Entity: Spatial Location: GIS  ===================**/

/**
* Under Development
* The central table on GIS
* Adheres to OGC OpenGIS Geographic Information - Simple Feature Access Specifications
* Ref: http://www.opengeospatial.org/ 
* Modules: cr,or,ics 
* Last changed: 27-OCT-2005 - mifan@opensource.lk  
*/
DROP TABLE IF EXISTS gis_feature;
CREATE TABLE gis_feature (
    feature_uuid VARCHAR(60) NOT NULL, -- spatial location key
    poc_uuid VARCHAR(60) NOT NULL,     -- mapped entity key
    feature_coords GEOMETRY NOT NULL,  -- coordinates of feature type
    entry_time TIMESTAMP DEFAULT now(),-- entry time for log purposes 
    PRIMARY KEY  (feature_uuid)
    /*SPATIAL KEY  (feature_coords)*/
);

/*** Table for Geograhical Information Systems
* Stores basic coordinates providing basic spatial functionality
* Modules: all
* Last changed: 04-Oct-2006: mifan@opensource.lk
*/
DROP TABLE IF EXISTS gis_location;
CREATE TABLE gis_location (
    poc_uuid varchar(60) NOT NULL,
    location_id varchar(20) default NULL,
    opt_gis_mod varchar(30) default NULL,
    map_northing double(15,10) NOT NULL,
    map_easting double(15,10) NOT NULL,
    map_projection varchar(20) default NULL,
    opt_gis_marker varchar(20) default NULL,
    gis_uid varchar(60) NOT NULL,
    PRIMARY KEY  (gis_uid)
);

/*** Table for GIS-WikiMaps functionality
* Modules: sm
* Last edited: 04-Oct-2006: mifan@opensource.lk
*/
DROP TABLE IF EXISTS gis_wiki;
CREATE TABLE gis_wiki (
    wiki_uuid VARCHAR(60) NOT NULL,
    gis_uuid VARCHAR(60) NOT NULL,
    name varchar(50) NOT NULL,
    description VARCHAR(100) default NULL,
    opt_category VARCHAR(10),
    url varchar(50) NOT NULL,
    event_date timestamp NULL,
    placement_date timestamp NOT NULL default now(),
    editable boolean NOT NULL default false,
    author VARCHAR(30) default NULL,
    approved boolean default false,
    PRIMARY KEY  (wiki_uuid),
    FOREIGN KEY (gis_uuid) REFERENCES gis_location(gis_uid)
);

/*** Table for maintaining GPX file information
* Modules: gps 
*/
DROP TABLE IF EXISTS gpx_file;
CREATE TABLE gpx_file (
    point_uuid VARCHAR(60) NOT NULL,
    author_name varchar(50) NOT NULL,
    event_date timestamp NOT NULL,
    route_name VARCHAR(50) NOT NULL,
    route_no int(250) NOT NULL,
    opt_category VARCHAR(10) NOT NULL,
    sequence_no int(250) NOT NULL,
    point_name varchar(50) NOT NULL,
    description varchar(100) default NULL,
    PRIMARY KEY  (point_uuid)
);

/**================= Entity: NEW Spatial Location: GIS  ===================**/
/**
 * Table for storing geographic features
 * Stores feature type, projection type and coordinates + refrances to metadata, feature_class
 * Modules: gis
 * Last changed: 14-June-2008: Richard - s0459387@sms.ed.ac.uk
 */
DROP TABLE IF EXISTS gis_features;
CREATE TABLE gis_features (
    feature_uuid varchar(60) NOT NULL,                  -- ID
    metadata_uuid_ref varchar(60) NOT NULL,             -- Associated metadata entry UID
    feature_class_uuid_ref varchar(60) NOT NULL,        -- Associated feature type UID   DEFAULT (default feature_class id)
    feature_type varchar(60) NOT NULL,                  -- Placement type (point, line, poly)
    map_projection varchar(20) NOT NULL,                -- Projection type associated with feature
    coords varchar(500) NOT NULL,                       -- Coordinates
    coord_x DOUBLE(15,10) NOT NULL,                     -- Coordinates just x (used for location drilldown)
    coord_y DOUBLE(15,10) NOT NULL,                     -- Coordinates just y (used for location drilldown)
    coord_z DOUBLE(15,10) NOT NULL,                     -- Coordinates just z (used for location drilldown)
    PRIMARY KEY (feature_uuid),
    FOREIGN KEY (metadata_uuid_ref) REFERENCES gis_feature_metadata(metadata_uuid),         -- ON DELETE RESTRICT
    FOREIGN KEY (feature_class_uuid_ref) REFERENCES gis_feature_type(feature_class_uuid)    -- ON DELETE DEFAULT
);

/**
* Table for storing metadata belonging to geographic features
* Stores metadata relating to a feature
* Modules: gis
* Last changed: 14-June-2008: Richard - s0459387@sms.ed.ac.uk
*/
-- This table is to be extended if in future any extra data needs storing
DROP TABLE IF EXISTS gis_feature_metadata;
CREATE TABLE gis_feature_metadata (
    metadata_uuid VARCHAR(60) NOT NULL,                 -- ID
    module_item_ref VARCHAR(60) NOT NULL,               -- Ref to item in other module db (eg. a missing person)
    name varchar(60) NOT NULL,                          -- Feature name
    description VARCHAR(500) NOT NULL,                  -- Feature description
    author VARCHAR(60) NOT NULL,                        -- Author name
    url varchar(100) NOT NULL,                          -- Link associated with feature
    address varchar(200) NOT NULL,                      -- Location address of feature
    event_date timestamp NULL,                          -- Time feature occurred (if relevant)
    placement_date timestamp NOT NULL default now(),    -- Time of placement in db
    extended_data VARCHAR(200) NOT NULL,                -- Optional extra data
    url_view varchar(100) NOT NULL,                     -- URL to view module-specific feature
    url_edit varchar(100) NOT NULL,                     -- URL to edit module-specific feature
    url_del varchar(100) NOT NULL,                      -- URL to delete module-specific feature
    PRIMARY KEY (metadata_uuid)
);

/**
* Table for storing information related to feature classes and style data for displaying
* Stores feature classes (hospital, school, flood area etc)
* Modules: gis
* Last changed: 14-June-2008: Richard - s0459387@sms.ed.ac.uk
*/
DROP TABLE IF EXISTS gis_feature_class;
CREATE TABLE gis_feature_class (
    feature_class_uuid VARCHAR(60) NOT NULL,            -- ID
    module_ref VARCHAR(100) NOT NULL,                   -- Ref to associated module (eg. camp)
    name VARCHAR(100) NOT NULL,                         -- Feature type name (eg. hospital)
    description VARCHAR(300) NOT NULL,                  -- Description of feature type (eg. med size hospital capacity..)
    icon VARCHAR(250) NOT NULL,                         -- Style info - Link to icon associated with feature_type
    color VARCHAR(8) NOT NULL,                          -- Style info - colour of icon/line/poly
    PRIMARY KEY (feature_class_uuid)
);

/**
* Table for storing layers of features to be displayed in OpenLayers
* Stores names and descriptions of layers as
* Modules: gis
* Last changed: 14-June-2008: Richard - s0459387@sms.ed.ac.uk
*/
-- may be extended as development in openlayers continues
DROP TABLE IF EXISTS gis_layers;
CREATE TABLE gis_layers (
    layer_uuid VARCHAR(60) NOT NULL,                    -- ID
    name VARCHAR(60) NOT NULL,                          -- Name of layer
    description VARCHAR(200) NOT NULL,                  -- Description of layer(eg. Alpha team objectives)
    PRIMARY KEY (layer_uuid)
);

/**
* Table for storing links between layers and features to be displayed in OpenLayers
* Stores uuid ref links for features and layers
* Modules: gis
* Last changed: 14-June-2008: Richard - s0459387@sms.ed.ac.uk
*/
-- may be extended as development in openlayers continues
DROP TABLE IF EXISTS gis_feature_to_layer;
CREATE TABLE gis_feature_to_layer (
    layer_uuid_ref VARCHAR(60) NOT NULL,                -- ID ref to associated layer
    feature_uuid_ref VARCHAR(60) NOT NULL,              -- ID ref to associated feature
    PRIMARY KEY (layer_uuid_ref,feature_uuid_ref),
    FOREIGN KEY (layer_uuid_ref) REFERENCES gis_layers(layer_uuid),
    FOREIGN KEY (feature_uuid_ref) REFERENCES gis_features(feature_uuid)
);

/**
* Table for storing links bettween feature_classes and layers
* Stores uuid ref links for feature classes and feature categories
* Modules: gis
* Last changed: 28-June-2008: Richard - s0459387@sms.ed.ac.uk
*/
DROP TABLE IF EXISTS gis_feature_class_to_layer;
CREATE TABLE gis_feature_class_to_layer (
    layer_uuid_ref VARCHAR(60) NOT NULL,                -- ID ref to associated layer    
    feature_class_uuid_ref VARCHAR(60) NOT NULL,        -- ID ref to associated feature_class
    PRIMARY KEY (layer_uuid_ref,feature_class_uuid_ref),
    FOREIGN KEY (layer_uuid_ref) REFERENCES gis_layers(layer_uuid),
    FOREIGN KEY (feature_class_uuid_ref) REFERENCES gis_feature_class(feature_class_uuid)
);

/**
* Under Development
* The central table of Image Tagger
* Modules: cr,or,ics 
* Last changed: 21-FEB-2008 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS maps;
CREATE TABLE maps (
    map_uuid VARCHAR(60) NOT NULL, -- spatial location key
    name VARCHAR(100) NOT NULL, 
    description VARCHAR(200) NOT NULL, 
    width BIGINT NOT NULL DEFAULT 1,
    height BIGINT NOT NULL DEFAULT 1,
    entry_time TIMESTAMP DEFAULT now(),-- entry time for log purposes 
    PRIMARY KEY  (map_uuid)
    /*SPATIAL KEY  (feature_coords)*/
);

/**
* Under Development
* The coordinate table for Image Tagger
* Modules: cr,or,ics 
* Last changed: 24-FEB-2008 - ravindra@opensource.lk  
*/
DROP TABLE IF EXISTS map_points;
CREATE TABLE map_points (
    point_uuid VARCHAR(60) NOT NULL,
    map_uuid VARCHAR(60) NOT NULL, -- spatial location key
    type VARCHAR(100) NOT NULL,
    name VARCHAR(100) NOT NULL, 
    description VARCHAR(200), 
    latitude BIGINT NOT NULL DEFAULT 1,
    longitude BIGINT NOT NULL DEFAULT 1,
    entry_time TIMESTAMP DEFAULT now(),-- entry time for log purposes 
    PRIMARY KEY  (point_uuid)
    /*SPATIAL KEY  (feature_coords)*/
);
/**================= Entity: Person oriented  ===================**/

/*** PERSON TABLES ***/



/**
* Many ID card numbers (or passport or driving licence) to person table
* Modules: dvr, mpr 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS identity_to_person;
CREATE TABLE identity_to_person (
    p_uuid VARCHAR(60) NOT NULL,
    serial VARCHAR(100), -- id card #, passport #, Driving License # etc
    opt_id_type VARCHAR(10), -- can be customized in the field options table
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

/**
* The main details on a person
* Modules: dvr, mpr, cr
* Created : 27-OCT-2005 - chamindra@opensource.lk  
* Last Updated : 07-Nov-2005 - janaka@opensource.lk
* Note: Removed the NOT NULL Constraint on next_kin_uuid
*/
DROP TABLE IF EXISTS person_details;
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
* Details on the person's status
* Modules: dvr, mpr
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_status;
CREATE TABLE person_status (
    p_uuid VARCHAR(60) NOT NULL,
    isReliefWorker TINYINT, 
    opt_status VARCHAR(10), -- missing, ingured, etc. customizable
    updated TIMESTAMP DEFAULT NOW(),
    isvictim BOOL DEFAULT 1,
    PRIMARY KEY (p_uuid)
);

/**
* Physical details of a person
* Modules: dvr, mpr, cms, rms 
* Last changed: 27-OCT-2005 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_physical;
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

DROP TABLE IF EXISTS person_missing;
CREATE TABLE person_missing (
    p_uuid VARCHAR(60) NOT NULL,
    last_seen TEXT,
    last_clothing TEXT,
    comments TEXT,
    PRIMARY KEY (p_uuid) ,
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);

DROP TABLE IF EXISTS person_deceased;
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

/**
* The person who reported about this person
* Modules: dvr, mpr, 
* Created : 21-Dec-2005 - janaka@opensource.lk
*/
DROP TABLE IF EXISTS person_to_report;
CREATE TABLE person_to_report (
    p_uuid VARCHAR(60) NOT NULL,
    rep_uuid VARCHAR(60) NOT NULL,
    relation VARCHAR(100),
    PRIMARY KEY (p_uuid,rep_uuid),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY (rep_uuid) REFERENCES person_uuid(p_uuid)
);


/**
* Contains the list of groups of people
* Modules: dvr, mpr
* Last changed: 26-FEB-2007 - isuru@opensource.lk  
*/
DROP TABLE IF EXISTS pgroup;
CREATE TABLE pgroup (
    g_uuid VARCHAR(60) NOT NULL, -- universally unique group id
    opt_group_type VARCHAR(10), -- type of the group
    PRIMARY KEY (g_uuid)
    
);


/**
* Contains the description of the group
* Modules: dvr, mpr
* Last changed: 26-FEB-2007 - isuru@opensource.lk  
*/
-- group-details
DROP TABLE IF EXISTS group_details;
CREATE TABLE group_details(
g_uuid VARCHAR(60) NOT NULL, -- universally unique group id
head_uuid VARCHAR(60),
no_of_adult_males INT,
no_of_adult_females INT,
no_of_children INT, 
no_displaced INT, 
no_missing INT,
no_dead INT,
no_rehabilitated INT,
checklist TEXT,
description TEXT,
PRIMARY KEY(g_uuid),
FOREIGN KEY (head_uuid) REFERENCES person_uuid(p_uuid)

);



/**
* A person can belong to multiple groups
* Modules: dvr, mpr
* Last changed: 26-FEB-2007 - chamindra@opensource.lk  
*/
DROP TABLE IF EXISTS person_to_pgroup;
CREATE TABLE person_to_pgroup (   
    p_uuid VARCHAR(60),
    g_uuid VARCHAR(60)
);

/**================= Entity: Organizations related  ===================**/
/**
* Information about an organization is stored here
* Modules:
* Last changed: 12-OCT-2006 - ravindra@opensource.lk  
*/

DROP TABLE IF EXISTS org_main;
CREATE TABLE org_main(
	o_uuid VARCHAR(60) NOT NULL,
    	parent_id VARCHAR(60) DEFAULT NULL,
    	name VARCHAR(100) NOT NULL ,
	opt_org_type VARCHAR(100),
	reg_no VARCHAR(100),
    	man_power VARCHAR(100),
	equipment VARCHAR(100),
	resources TEXT,
    	privacy INT(1) DEFAULT 0,
    	archived BOOL DEFAULT 0, 
 	created TIMESTAMP DEFAULT NOW(),
	PRIMARY KEY (o_uuid),
	FOREIGN KEY (parent_id) REFERENCES org_main(o_uuid)
);

/**================= Entity: Web Services related  ===================**/
/**
* Information about web service keys is stored here
* Modules:
* Last changed: 1-SEP-2007 - ravindra@opensource.lk  
*/

DROP TABLE IF EXISTS ws_keys;
CREATE TABLE ws_keys(
    p_uuid VARCHAR(60) NOT NULL,
    domain VARCHAR(200) NOT NULL,
    api_key VARCHAR(60) NOT NULL,
    password VARCHAR(60) NOT NULL,
    secret VARCHAR(60) NOT NULL,
    PRIMARY KEY (p_uuid,domain,api_key),
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);



/**================= Entity: Camp Tables ===========================**/

/**
* Physical Details of Camps/Shelters
* Modules: cr
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/

DROP TABLE IF EXISTS camp_general;
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
* Human Resource Details of Camps/Shelters
* Modules: cr
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/
DROP TABLE IF EXISTS camp_reg;
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

/**
* Services offered by camps
* Modules: cr
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/
DROP TABLE IF EXISTS camp_services;
CREATE TABLE camp_services (
    c_uuid VARCHAR(60) NOT NULL,
    opt_camp_service VARCHAR(50),
    value BOOL NOT NULL default 0, 
    PRIMARY KEY (c_uuid,opt_camp_service)
);

/**
* Camp to Admin Mapping
* Modules: cr
* Last changed: 21-Feb-2006 - mifan@opensource.lk  
*/
DROP TABLE IF EXISTS camp_admin;
CREATE TABLE camp_admin(
    c_uuid VARCHAR(60) NOT NULL,
    contact_puuid VARCHAR(60) NOT NULL,
		PRIMARY KEY (c_uuid,contact_puuid)
);


/**
* A person/group can belong to a shelter
* Modules: dvr, mpr
* Last changed: 15-November-2007 - isuru@opensource.lk  
*/

DROP TABLE IF EXISTS resource_to_shelter;
CREATE TABLE resource_to_shelter (   
    x_uuid VARCHAR(60),
    c_uuid VARCHAR(60),


    PRIMARY KEY(x_uuid,c_uuid),
    FOREIGN KEY (c_uuid) REFERENCES camp_general(c_uuid)
);




/**================= Localization Tables ===========================**/

/**
* I18N/L10N specific tables
* Modules	: Framework, admin 
* Created 	: 08-Feb-2006 - sudheera@opensource.lk
* Last changed	: 21-Feb-2006 - sudheera@opensource.lk
*/

DROP TABLE IF EXISTS lc_fields;
CREATE TABLE lc_fields (
    id BIGINT NOT NULL AUTO_INCREMENT,
    tablename VARCHAR(32) NOT NULL,
    fieldname VARCHAR(32) NOT NULL,
    PRIMARY KEY(id)
);

/**================= Resource/Multimedia Tables ===========================**/


/** 
 * Image storage table 
 * Modules : Framework, sync
 * Created : 20th-Mar-2006 - janaka@opensource.lk
 * Last Change : 26th-FEB-2007  - isuru@opensource.lk
 */
DROP TABLE IF EXISTS image;
CREATE TABLE image(
    image_id BIGINT NOT NULL AUTO_INCREMENT,
    x_uuid VARCHAR(60) NOT NULL, -- universally unique person id
    image MEDIUMBLOB NOT NULL,
    image_type VARCHAR(100) NOT NULL,
    image_height INT,
    image_width INT,
    created TIMESTAMP DEFAULT NOW(),
    category varchar(32),
    PRIMARY KEY (image_id)
);

/** 
 * Generic Media storage table 
 * Modules : Framework, sync
 * Created : 20th-Mar-2006 - ravindra@opensource.lk
 */
DROP TABLE IF EXISTS media;
CREATE TABLE media(
    media_id VARCHAR(60) NOT NULL,
    x_uuid VARCHAR(60) NOT NULL,
    url VARCHAR(200) NOT NULL,
    media_type VARCHAR(100) NOT NULL,
    media_height INT DEFAULT 0,
    media_width INT DEFAULT 0,
    created TIMESTAMP DEFAULT NOW(),
    category varchar(32),
    PRIMARY KEY (media_id)
);


/**================ Multiple Incident Tables ========================**/
/** 
 * Incident 
 * Modules : Framework
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */
DROP TABLE IF EXISTS incident;
CREATE TABLE incident(
    incident_id BIGINT NOT NULL AUTO_INCREMENT,
    parent_id BIGINT DEFAULT NULL,
    search_id VARCHAR(60),
    name VARCHAR(60),
    FOREIGN KEY (parent_id) REFERENCES incident (incident_id),
    PRIMARY KEY (incident_id)
);

/*
 Added by Greg@NIH to allow better description of the disaster/crisis incident
*/
ALTER TABLE  `incident` 
	ADD  `shortname` VARCHAR( 16 ) NULL DEFAULT NULL,
	ADD  `date`      DATE          NULL DEFAULT NULL,
	ADD  `type`      VARCHAR( 32 ) NULL DEFAULT NULL,
	ADD  `latitude`  DOUBLE        NULL DEFAULT NULL,
	ADD  `longitude` DOUBLE        NULL DEFAULT NULL;

/** 
 * Resources to Incidents
 * Modules : Framework, or
 * Created : 28th-Mar-2006 - janaka@opensource.lk
 * Last Change : 28th-Mar-2006  - janaka@opensource.lk
 */

DROP TABLE IF EXISTS resource_to_incident;
CREATE TABLE resource_to_incident(
    incident_id BIGINT NOT NULL,
    x_uuid VARCHAR(60),
    FOREIGN KEY (incident_id) REFERENCES incident (incident_id),
    PRIMARY KEY (incident_id,x_uuid)
);

/**================ PHP and 3rd Party Tables ========================**/

/**
* This is the sessions table that stores the PHP session in the database 
* Modules: all
*/
DROP TABLE IF EXISTS sessions;
CREATE TABLE sessions(
	session_id VARCHAR(64) NOT NULL,
	sess_key VARCHAR(64) NOT NULL,
	secret VARCHAR(64) NOT NULL,
	inactive_expiry BIGINT NOT NULL,
	expiry BIGINT NOT NULL,
	data TEXT ,
	PRIMARY KEY (session_id)
);

-- OPTIMIZATION  DEVEL - @depracated ?
DROP TABLE IF EXISTS devel_logsql;
CREATE TABLE devel_logsql (
    created timestamp NOT NULL, 
    sql0 varchar(250) NOT NULL,
    sql1 text NOT NULL,
    params text NOT NULL,
    tracer text NOT NULL,
    timer decimal(16,6) NOT NULL
); 

/**================= Aggregator mashup Portal Tables ===========================**/


/** 
 * Mahup storage table 
 * Modules : amp
 * Created : 13th-june-2009 - iroshanmail@gmail.com
 * @author : H. Iroshan
 * 
 *  *  */
DROP TABLE IF EXISTS amp_mashup;
CREATE TABLE amp_mashup (
  mashup_uuid varchar(20) NOT NULL,
  name varchar(45) NOT NULL,
  user_uuid varchar(45) default NULL,
  service varchar(45) default NULL,
  wbsmod varchar(45) NOT NULL,
  PRIMARY KEY  (mashup_uuid)
);


/** 
 * Mahup storage table 
 * Modules : amp
 * Created : 13th-june-2009 - iroshanmail@gmail.com
 * @author : H. Iroshan
 * 
 *  *  */
DROP TABLE IF EXISTS amp_mashup_url;
CREATE TABLE amp_mashup_url (
  mashup_uuid varchar(20) NOT NULL,
  url varchar(150) NOT NULL,
  PRIMARY KEY  (mashup_uuid,url),
  CONSTRAINT FK_amp_mashup_url_1 FOREIGN KEY (mashup_uuid) REFERENCES amp_mashup (mashup_uuid)
);


/** 
 * Mahup filterring table 
 * Modules : amp
 * Created : 14th-june-2009 - iroshanmail@gmail.com
 * @author : H. Iroshan
 * 
 *  *  */
DROP TABLE IF EXISTS amp_filter;
CREATE TABLE amp_filter(
  amp_filter_id int(11) NOT NULL,
  create_time INTEGER NOT NULL,
  uuid varchar(20) default NULL,
  masup_url varchar(150) default NULL,
  column_name varchar(100) default NULL,
  value varchar(150) default NULL,
  method varchar(100) default NULL,
  PRIMARY KEY  (amp_filter_id)
); 


/**================= TO BE REMOVED =======================**/


CREATE DATABASE IF NOT EXISTS sahana;
USE sahana;

/* REQUEST MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/

DROP TABLE IF EXISTS `rms_request`;
CREATE TABLE rms_request (
    req_id BIGINT NOT NULL AUTO_INCREMENT,
    req_date TIMESTAMP,
    name VARCHAR(100),
    contact VARCHAR(100),
    address VARCHAR(255),
    site_name VARCHAR(100),
    site_district VARCHAR(100),
    site_address VARCHAR(255),
    comments VARCHAR(500),
    status VARCHAR(100) DEFAULT 'open',
    user_id BIGINT,
    PRIMARY KEY (req_id),
    FOREIGN KEY (user_id) REFERENCES org_user (user_id)
);

DROP TABLE IF EXISTS `rms_req_category`;
CREATE TABLE rms_req_category (
    cat_id BIGINT NOT NULL AUTO_INCREMENT,
    category VARCHAR(100) NOT NULL,
    description VARCHAR(255),
    PRIMARY KEY (cat_id)
);
/**
*Intial category type data (Should be localized??)
*/
INSERT INTO rms_req_category (category, description) values ('Blankets Shelter','later');
INSERT INTO rms_req_category (category, description) values ('Medical Drugs','later');
INSERT INTO rms_req_category (category, description) values ('Food and Nutrition','later');
INSERT INTO rms_req_category (category, description) values ('Other','Other Categories');



DROP TABLE IF EXISTS `rms_req_units`;
CREATE TABLE rms_req_units (
    unit_id BIGINT NOT NULL AUTO_INCREMENT,
    unit VARCHAR(100) NOT NULL,
    description VARCHAR(255),
    PRIMARY KEY (unit_id)
);
/**
*Intial category type data (Should be localized??)
*/
INSERT INTO rms_req_units (unit, description) values ('Kg','Kilogram');
INSERT INTO rms_req_units (unit, description) values ('m','metre');
INSERT INTO rms_req_units (unit, description) values ('Bottle','');
INSERT INTO rms_req_units (unit, description) values ('Other','Other unit');


DROP TABLE IF EXISTS `rms_req_priority`;
CREATE TABLE rms_req_priority (
    priority_id BIGINT NOT NULL AUTO_INCREMENT,
    priority VARCHAR(100) NOT NULL,
    description VARCHAR(255),
    PRIMARY KEY (priority_id)
);
/**
*Intial priority type data (Should be localized??)
*/
INSERT INTO rms_req_priority (priority,description) values ('Immediate (< 1 week)','sum desc');
INSERT INTO rms_req_priority (priority,description) values ('Medium (< 1 mon)','sum desc');
INSERT INTO rms_req_priority (priority,description) values ('Long Term (1-3 mon)','sum desc');


DROP TABLE IF EXISTS `rms_req_item`;
CREATE TABLE rms_req_item (
    req_item_id BIGINT NOT NULL AUTO_INCREMENT,
    cat_id BIGINT,
    item VARCHAR(200),
    units VARCHAR(100),
    quantity INT,
    priority_id BIGINT,
    req_id BIGINT NOT NULL,
    PRIMARY KEY (req_item_id),
    FOREIGN KEY (req_id) REFERENCES rms_request(req_id),
    FOREIGN KEY (cat_id) REFERENCES rms_req_category(cat_id),
    FOREIGN KEY (priority_id) REFERENCES rms_req_priority(priority_id)
);

DROP TABLE IF EXISTS `rms_req_ff`;
CREATE TABLE rms_req_ff (
    req_ff_id BIGINT NOT NULL AUTO_INCREMENT,
    req_item_id BIGINT,
    user_id BIGINT,
    quantity INT,
    ff_status VARCHAR(100),
    req_donor_id BIGINT,
    ff_date TIMESTAMP,
    PRIMARY KEY (req_ff_id),
    FOREIGN KEY (req_donor_id) REFERENCES rms_req_donor(req_donor_id),
    FOREIGN KEY (req_item_id) REFERENCES rms_req_item(req_item_id),
    FOREIGN KEY (user_id) REFERENCES users (puu_id)
);

DROP TABLE IF EXISTS `rms_req_donor`;
CREATE TABLE rms_req_donor (
    req_donor_id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(255),
    contact VARCHAR(255),
    comments VARCHAR(255),
    PRIMARY KEY (req_donor_id)
);

DROP TABLE IF EXISTS `rms_pledge`;
CREATE TABLE rms_pledge (
    plg_id BIGINT NOT NULL AUTO_INCREMENT,
    date TIMESTAMP,
    op_id BIGINT,
    cat_id BIGINT,
    item VARCHAR(200),
    units VARCHAR(100),
    quantity INT,
    status VARCHAR(100) DEFAULT 'not confirmed',
    user_id BIGINT,
    PRIMARY KEY (plg_id),
    FOREIGN KEY (user_id) REFERENCES org_user (user_id)
);

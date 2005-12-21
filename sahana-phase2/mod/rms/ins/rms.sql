CREATE DATABASE IF NOT EXISTS sahana;
USE sahana;

/* REQUEST MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/

DROP TABLE IF EXISTS `rms_request`;
CREATE TABLE rms_request (
    id BIGINT NOT NULL AUTO_INCREMENT,
    date TIMESTAMP,
    site_id BIGINT,
    status VARCHAR(100) DEFAULT 'open',
    requester_id BIGINT,
    PRIMARY KEY (id),
    FOREIGN KEY (requester_id) REFERENCES rms_org_psn (id),
    FOREIGN KEY (site_id) REFERENCES rms_req_site (id)
);

DROP TABLE IF EXISTS `rms_org_psn`;
CREATE TABLE rms_org_psn (
    id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(255),
    location VARCHAR(255),
    telephone VARCHAR(255),
    email VARCHAR(255),
    address VARCHAR(255),
    comments VARCHAR(255),
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS `rms_req_site`;
CREATE TABLE rms_req_site (
    id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(255),
    address VARCHAR(255),
    location VARCHAR(255),
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS `rms_item`;
CREATE TABLE rms_item (
    id BIGINT NOT NULL AUTO_INCREMENT,
    name VARCHAR(255),
    cat_id BIGINT,
    unit VARCHAR(100),
    qty BIGINT,
    PRIMARY KEY (id),
    FOREIGN KEY (cat_id) REFERENCES rms_item_cat (id)
);

DROP TABLE IF EXISTS `rms_req_item`;
CREATE TABLE rms_req_item (
    req_id BIGINT NOT NULL,
    item_id BIGINT NOT NULL,
    priority_id BIGINT,
    FOREIGN KEY (priority_id) REFERENCES rms_item_pry (id)
);

DROP TABLE IF EXISTS `rms_item_pry`;
CREATE TABLE rms_item_pry (
    id BIGINT NOT NULL AUTO_INCREMENT,
    priority VARCHAR(255),
    description VARCHAR(255),
    PRIMARY KEY (id)
);

/**
*Intial priority type data
*/
INSERT INTO rms_item_pry (priority,description) values ('Immediate (< 1 week)','desc');
INSERT INTO rms_item_pry (priority,description) values ('Medium (< 1 mon)','desc');
INSERT INTO rms_item_pry (priority,description) values ('Long Term (1-3 mon)','desc');


DROP TABLE IF EXISTS `rms_item_cat`;
CREATE TABLE rms_item_cat (
    id BIGINT NOT NULL AUTO_INCREMENT,
    category VARCHAR(255),
    description VARCHAR(255),
    PRIMARY KEY (id)
);

/**
*Intial category type data
*/
INSERT INTO rms_item_cat (category, description) values ('Blankets Shelter','later');
INSERT INTO rms_item_cat (category, description) values ('Medical Drugs','later');
INSERT INTO rms_item_cat (category, description) values ('Food and Nutrition','later');
INSERT INTO rms_item_cat (category, description) values ('Other','Other Categories');

DROP TABLE IF EXISTS `rms_req_stat`;
CREATE TABLE rms_req_stat (
    id BIGINT NOT NULL AUTO_INCREMENT,
    status VARCHAR(255),
    description VARCHAR(255),
    PRIMARY KEY (id)
);

DROP TABLE IF EXISTS `rms_ff_item`;
CREATE TABLE rms_ff_item (
    id BIGINT NOT NULL AUTO_INCREMENT,
    req_id BIGINT,
    item_id BIGINT,
    date TIMESTAMP,
    qty BIGINT,
    status VARCHAR(255),
    donor_id BIGINT,
    PRIMARY KEY (id),
    FOREIGN KEY (donor_id) REFERENCES rms_org_psn (id)
);

DROP TABLE IF EXISTS `rms_offer`;
CREATE TABLE rms_offer (
    id BIGINT NOT NULL AUTO_INCREMENT,
    date TIMESTAMP,
    donor_id BIGINT,
    status VARCHAR(255),
    PRIMARY KEY (id),
    FOREIGN KEY (donor_id) REFERENCES rms_org_psn (id)
);

DROP TABLE IF EXISTS `rms_offer_item`;
CREATE TABLE rms_offer_item (
    offer_id BIGINT NOT NULL,
    item_id BIGINT NOT NULL,
    FOREIGN KEY (offer_id) REFERENCES rms_offer (id),
    FOREIGN KEY (item_id) REFERENCES rms_item (id)
);

/* REQUEST MANAGEMENT SYSTEM TABLES */
/* --------------------------------------------------------------------------*/

DROP TABLE IF EXISTS `rms_request`;
CREATE TABLE rms_request (
    req_uuid VARCHAR(60) NOT NULL,
    reqstr_uuid VARCHAR(60),
    loc_uuid VARCHAR(60),
    req_date TIMESTAMP,
    status VARCHAR(60) DEFAULT 'open',
    user_id VARCHAR(60),
    PRIMARY KEY (req_uuid),
    FOREIGN KEY (reqstr_uuid) REFERENCES person_uuid (p_uuid),
    FOREIGN KEY (loc_uuid) REFERENCES location_details (poc_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);

DROP TABLE IF EXISTS `rms_req_item`;
CREATE TABLE rms_req_item (
    item_uuid VARCHAR(60) NOT NULL,
    quantity INTEGER,
    pri_uuid VARCHAR(255),
    req_uuid VARCHAR(60) NOT NULL,
    PRIMARY KEY (item_uuid, req_uuid),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue (ct_uuid),
    FOREIGN KEY (pri_uuid) REFERENCES rms_priority (pri_uuid),
    FOREIGN KEY (req_uuid) REFERENCES rms_request (req_uuid)
);

DROP TABLE IF EXISTS `rms_priority`;
CREATE TABLE rms_priority (
    pri_uuid VARCHAR(60),
    priority VARCHAR(100),
    pri_desc VARCHAR(255),
    PRIMARY KEY (pri_uuid)
);

INSERT INTO rms_priority VALUES ('pri_1','Immediate','');
INSERT INTO rms_priority VALUES ('pri_2','Modarate','');
INSERT INTO rms_priority VALUES ('pri_3','Low Pirority','');

DROP TABLE IF EXISTS `rms_status`;
CREATE TABLE rms_status (
    stat_uuid VARCHAR(60),
    status VARCHAR(100),
    stat_desc VARCHAR(255),
    PRIMARY KEY (stat_uuid)
);

DROP TABLE IF EXISTS `rms_pledge`;
CREATE TABLE rms_pledge (
    plg_uuid VARCHAR(60) NOT NULL,
    donor_uuid VARCHAR(60),
    plg_date TIMESTAMP,
    status VARCHAR(20) DEFAULT 'not_confirmed',
    user_id VARCHAR(60),
    PRIMARY KEY (plg_uuid),
    FOREIGN KEY (donor_uuid) REFERENCES person_uuid (p_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);

DROP TABLE IF EXISTS `rms_plg_item`;
CREATE TABLE rms_plg_item (
    item_uuid VARCHAR(60) NOT NULL,
    quantity INTEGER NOT NULL,
    status VARCHAR(255) DEFAULT 'Not Confirmed',
    plg_uuid VARCHAR(60) NOT NULL,
    PRIMARY KEY (item_uuid, plg_uuid),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue (ct_uuid),
    FOREIGN KEY (plg_uuid) REFERENCES rms_pledge (plg_uuid)
);

DROP TABLE IF EXISTS `rms_fulfil`;
CREATE TABLE rms_fulfil (
    req_uuid VARCHAR(60),
    item_uuid VARCHAR(60),
    plg_uuid VARCHAR(60),
    quantity INTEGER,
    ff_date TIMESTAMP,
    user_id VARCHAR(60) DEFAULT '1',
    PRIMARY KEY (req_uuid, item_uuid, plg_uuid, quantity, ff_date),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue (ct_uuid),
    FOREIGN KEY (plg_uuid) REFERENCES rms_pledge (plg_uuid),
    FOREIGN KEY (req_uuid) REFERENCES rms_request (req_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);

DROP TABLE IF EXISTS `rms_tmp_sch`;
CREATE TABLE rms_tmp_sch (
    sch_id VARCHAR(60)
);

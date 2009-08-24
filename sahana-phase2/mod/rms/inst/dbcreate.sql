/**
* The table structure to manage requests,pledges and fullfillments
* Modules: rms
* Last changed: 3rd-OCT-2006 - isuru@opensource.lk
*/

-- drop tables in order to support innodb installation
DROP TABLE IF EXISTS `rms_tmp_sch`;
DROP TABLE IF EXISTS `rms_fulfil`;
DROP TABLE IF EXISTS `rms_plg_item`;
DROP TABLE IF EXISTS `rms_pledge`;
DROP TABLE IF EXISTS `rms_status`;
DROP TABLE IF EXISTS `rms_req_item`;
DROP TABLE IF EXISTS `rms_priority`;
DROP TABLE IF EXISTS `ext_location`;
DROP TABLE IF EXISTS `rms_request`;


CREATE TABLE rms_request (          -- rms_request table    
    req_uuid VARCHAR(60) NOT NULL,  -- unique id for request
    reqstr_uuid VARCHAR(60),        -- unique requester id 
    loc_uuid VARCHAR(60),           -- location uuid 
    req_date TIMESTAMP,             -- request date  
    status VARCHAR(60) DEFAULT 'open', -- request status
    user_id VARCHAR(60),              -- user 
    PRIMARY KEY (req_uuid),
    FOREIGN KEY (reqstr_uuid) REFERENCES person_uuid (p_uuid),
    FOREIGN KEY (loc_uuid) REFERENCES location_details (poc_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);


CREATE TABLE ext_location (         -- existing location table for a particular    
    p_uuid VARCHAR(60) NOT NULL,  -- unique person id(requester id) for a particular user
    loc_uuid VARCHAR(60),        -- location uuid 
    PRIMARY KEY (p_uuid,loc_uuid),
    FOREIGN KEY (loc_uuid) REFERENCES rms_request(loc_uuid),
    FOREIGN KEY (p_uuid) REFERENCES users (p_uuid)
);



CREATE TABLE rms_priority (           -- rms_priority table
    pri_uuid VARCHAR(60) NOT NULL,   -- unique id
    priority VARCHAR(100),            -- priority
    pri_desc VARCHAR(255),            -- description on priority  
    PRIMARY KEY (pri_uuid)
);



CREATE TABLE rms_req_item (           -- rms_req_item table
    item_uuid VARCHAR(60) NOT NULL,   -- unique id
    quantity INTEGER,                 -- actual quantity
    pri_uuid VARCHAR(255),            -- primary key
    req_uuid VARCHAR(60) NOT NULL,    -- unique id
    unit VARCHAR(60),                 -- units  
    PRIMARY KEY (item_uuid, req_uuid),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue (ct_uuid),
    FOREIGN KEY (pri_uuid) REFERENCES rms_priority (pri_uuid),
    FOREIGN KEY (req_uuid) REFERENCES rms_request (req_uuid)
);


-- initial configurations
INSERT INTO rms_priority VALUES ('pri_1','Immediate','');
INSERT INTO rms_priority VALUES ('pri_2','Moderate','');
INSERT INTO rms_priority VALUES ('pri_3','Low Priority','');


CREATE TABLE rms_status (          -- rms_status table
    stat_uuid VARCHAR(60),         -- unique is
    status VARCHAR(100),           -- status
    stat_desc VARCHAR(255),        -- description
    PRIMARY KEY (stat_uuid)
);


CREATE TABLE rms_pledge (           -- rms_pledge table
    plg_uuid VARCHAR(60) NOT NULL,  -- unique id
    donor_uuid VARCHAR(60),         -- donor_uuid  
    plg_date TIMESTAMP,             -- date pledged
    status VARCHAR(20) DEFAULT 'not_confirmed', -- status of the pledge
    user_id VARCHAR(60),               
    PRIMARY KEY (plg_uuid),
    FOREIGN KEY (donor_uuid) REFERENCES person_uuid (p_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);


CREATE TABLE rms_plg_item (         -- rms_plg_item table
    item_uuid VARCHAR(60) NOT NULL, -- unique id
    quantity INTEGER NOT NULL,      -- quantity
    status VARCHAR(255) DEFAULT 'Not Confirmed', -- status
    plg_uuid VARCHAR(60) NOT NULL,  -- plg uuid
    unit VARCHAR(60),               -- units
    inventory VARCHAR(20),
    PRIMARY KEY (item_uuid, plg_uuid),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue(ct_uuid),
    FOREIGN KEY (plg_uuid) REFERENCES rms_pledge (plg_uuid)
);


CREATE TABLE rms_fulfil (          -- rms_fulfil table
    req_uuid VARCHAR(60),          -- unique id
    item_uuid VARCHAR(60),         -- unique id 
    plg_uuid VARCHAR(60),          -- uniqueid
    quantity INTEGER,              -- quantity
    ff_date TIMESTAMP,             -- date fullfilled 
    user_id VARCHAR(60) DEFAULT '1',
    PRIMARY KEY (req_uuid, item_uuid, plg_uuid, quantity, ff_date),
    FOREIGN KEY (item_uuid) REFERENCES ct_catalogue (ct_uuid),
    FOREIGN KEY (plg_uuid) REFERENCES rms_pledge (plg_uuid),
    FOREIGN KEY (req_uuid) REFERENCES rms_request (req_uuid),
    FOREIGN KEY (user_id) REFERENCES users (p_uuid)
);


CREATE TABLE rms_tmp_sch ( -- tmp table for searching
    sch_id VARCHAR(60)
);

/**
To be removed
**/
DROP TABLE IF EXISTS `rms_org`;

CREATE TABLE rms_org (           -- rms_organization table
    plg_uuid VARCHAR(60) NOT NULL,   -- unique id
    org_id VARCHAR(60),            -- Organization
    PRIMARY KEY (plg_uuid)
);

DROP TABLE IF EXISTS `rms_request_date`;

CREATE TABLE rms_request_date (           -- rms_request_date table
    req_uuid VARCHAR(60) NOT NULL,   -- unique id
    date DATE,            -- Date
    PRIMARY KEY (req_uuid)
);

DROP TABLE IF EXISTS `rms_request_status_date`;

CREATE TABLE rms_request_status_date (           -- rms_request_date table
    req_uuid VARCHAR(60) NOT NULL,   -- unique id
    status_date DATE,            -- Date
    PRIMARY KEY (req_uuid)
);

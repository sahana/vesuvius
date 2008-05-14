/* $id$ */

/**====================== Messaging/Alerting Tables=============**/

/**
* Table to store messaging groups
* Modules: msg 
* Last Edited: sri@opensource.lk
* 
* Note: This is not used in the new messaging/alerting module -- by Pradeeper
* 
*/

DROP TABLE IF EXISTS `messaging_group`;
CREATE TABLE messaging_group
(

	group_uuid VARCHAR(20),
	group_name VARCHAR(100),
	address VARCHAR(500),
	mobile VARCHAR(500),
	PRIMARY KEY(group_uuid)
);


/**
* Table for Store individual contact information
* Modules: msg
* Created: 09-FEB-2008 pradeeper@respere.com
* Last Edited: 09-FEB-2008 pradeeper@respere.com 
*/
DROP TABLE IF EXISTS msg_people_contact;
CREATE TABLE msg_people_contact (
    m_uuid VARCHAR(60) NOT NULL,
    name VARCHAR(100) NOT NULL,
	full_name VARCHAR(150),
	address VARCHAR(200),
	primary_method VARCHAR(6),
	primary_mobile INT(10),
	secondary_mobile INT(10),
	primary_email VARCHAR(25),
	secondary_email VARCHAR(25),
	added_date TIMESTAMP
);


/**
* Table for Store group information
* Modules: msg
* Created: 13-FEB-2008 pradeeper@respere.com
* Last Edited: 13-FEB-2008 pradeeper@respere.com 
*/
DROP TABLE IF EXISTS msg_people_group;
CREATE TABLE msg_people_group (
    m_uuid VARCHAR(60) NOT NULL,
    grp_name VARCHAR(15) NOT NULL,
	grp_des VARCHAR(25),
	grp_type VARCHAR(50) NOT NULL,-- group category from field_options
	grp_type_desc VARCHAR(100) NOT NULL, -- group category description from field_options
	grp_created_date TIMESTAMP
);


/**
* Table for Store group members
* Modules: msg
* Created: 13-FEB-2008 pradeeper@respere.com
* Last Edited: 24-FEB-2008 pradeeper@respere.com 
*/
DROP TABLE IF EXISTS msg_group_membership;
CREATE TABLE msg_group_membership (
    person_id VARCHAR(60) NOT NULL, -- person id from 'msg_people_contact'
    group_id VARCHAR(60) NOT NULL, -- group id from 'msg_people_group'
	grp_updated_date TIME -- group updated time/date
);


/**
* Table for Store Survey Message information
* Modules: msg
* Created: 25-FEB-2008 pradeeper@respere.com
* Last Edited: 25-FEB-2008 pradeeper@respere.com 
*/
DROP TABLE IF EXISTS msg_survey;
CREATE TABLE msg_survey (
    msg_id VARCHAR(60) NOT NULL,
	survey_name VARCHAR(100) NOT NULL,
	survey_key VARCHAR(70) NOT NULL,
    recipient VARCHAR(150) NOT NULL,
	message VARCHAR(200),
	send_time TIME
);

/**
* Table for Store Survey Message options
* Modules: msg
* Created: 14-May-2008 jo@respere.com
* Last Edited: 14-May-2008 jo@respere.com 
*/
DROP TABLE IF EXISTS msg_survey_opt;
CREATE TABLE msg_survey_opt (
        msg_id VARCHAR(60) NOT NULL,
	opt_num VARCHAR(3) NOT NULL,
	opt_val VARCHAR(30) NOT NULL
);


/**
* Messaging contact group categories
* Modules: msg 
* Last Edited: mifan@respere.com
*/
INSERT INTO field_options VALUES('opt_msg_group_category','non','None');
INSERT INTO field_options VALUES('opt_msg_group_category','team','Team');
INSERT INTO field_options VALUES('opt_msg_group_category','pers','Personal');
INSERT INTO field_options VALUES('opt_msg_group_category','dept','Department');
INSERT INTO field_options VALUES('opt_msg_group_category','org','Organization');
INSERT INTO field_options VALUES('opt_msg_group_category','communi','Community');
INSERT INTO field_options VALUES('opt_msg_group_category','cust','Customer');

/**
* Messaging Media Categories
* Modules: msg 
* Only add values if the medium type is supported by Sahana Messaging
* Last Edited: mifan@respere.com
*/
INSERT INTO field_options VALUES('opt_msg_medium','sms','Short Messaging/Text Messaging/SMS');
INSERT INTO field_options VALUES('opt_msg_medium','email','Electronic Mail/EMail');

/**
* Inserting Messaging module default SMS gateway
* Modules: msg 
* Last Edited: mifan@respere.com
*/
/*INSERT INTO config(module_id,confkey,value) VALUES ('msg','mod_msg_plugin','smstools');*/

/**
* SMSTools status reports
* TODO: move to plugin directory: handle within plugin arch
* Module: msg:smstools
* Created: 03-FEB-2008 mifan@respere.com
* Last Edited: mifan@respere.com
*/
DROP TABLE IF EXISTS msg_smstools_log;
CREATE TABLE msg_smstools_log (
   id int auto_increment NOT NULL,
   type char(16),
   sent DATETIME,
   received DATETIME,
   sender char(32),
   receiver char(32),
   status char(3),
   msgid char(3),
   PRIMARY KEY(id)
);

/**
* Table for received messages
*/
DROP TABLE IF EXISTS msg_received_messages;
CREATE TABLE msg_received_messages (
   id int auto_increment NOT NULL,
   received DATETIME ,
   sender char(32),
   status char(1),
   message varchar(160),
   PRIMARY KEY(id)
);

/**
* Table for Stored messages for the Messaging Module
* Modules: msg
* Created: 03-FEB-2008 mifan@respere.com
* Last Edited: 03-FEB-2008 mifan@respere.com 
*/
DROP TABLE IF EXISTS msg_stored_messages;
CREATE TABLE msg_stored_messages (
    m_uuid VARCHAR(60) NOT NULL,
    message_header VARCHAR(100) NOT NULL,
    message_content VARCHAR(500),
    message_creation_date TIMESTAMP DEFAULT now(),
    message_creation_user_id VARCHAR(60), -- user id of message creator
    PRIMARY KEY (m_uuid)
);

/**
* Table for Template messages for the Messaging Module
* Modules: msg
* Created: 03-FEB-2008 mifan@respere.com
* Last Edited: 03-FEB-2008 mifan@respere.com 
*/
DROP TABLE IF EXISTS msg_tpl_messages;
CREATE TABLE msg_tpl_messages (
    m_uuid VARCHAR(60) NOT NULL,
    message_header VARCHAR(100) NOT NULL,
    message_content VARCHAR(500),
    message_creation_date TIMESTAMP DEFAULT now(),
    message_creation_user_id VARCHAR(60), -- user id of message creator
    PRIMARY KEY (m_uuid)
);

/**
* Mapping of Stored messages to message medium
* Modules: msg
* Created: 03-FEB-2008 mifan@respere.com
* Last Edited: 03-FEB-2008 mifan@respere.com 
*/
DROP TABLE IF EXISTS msg_message_to_medium;
CREATE TABLE msg_message_to_medium (
    m_uuid VARCHAR(60) NOT NULL,
    opt_msg_message_medium VARCHAR(10) NOT NULL, -- map to medium from opt table
    PRIMARY KEY (m_uuid,opt_msg_message_medium),
    FOREIGN KEY (m_uuid) REFERENCES person_uuid(p_uuid)
);

/**
* Sent messages table
* Modules: msg
* Created: 03-FEB-2008 mifan@respere.com
* Last Edited: 03-FEB-2008 mifan@respere.com
*/
DROP TABLE IF EXISTS msg_sent_messages;
CREATE TABLE msg_sent_messages (
    m_uuid VARCHAR(60) NOT NULL,
    sender_id VARCHAR(60) NOT NULL, -- user id of sender
    recipient_number VARCHAR(20) NOT NULL,
    msg_uuid VARCHAR(60) NOT NULL,
    status bool,
    PRIMARY KEY (m_uuid),
    FOREIGN KEY (msg_uuid) REFERENCES person_uuid(p_uuid) 
);

/**
* Sent messages table
* Modules: msg
* Created: 11-FEB-2008 mifan@respere.com
* Last Edited: 11-FEB-2008 mifan@respere.com
* @todo store group information
*/
DROP TABLE IF EXISTS msg_sent_messages;
CREATE TABLE msg_sent_messages (
    m_uuid VARCHAR(60) NOT NULL,
    sender_id VARCHAR(60) NOT NULL, -- user id of sender
    recipient_number VARCHAR(20) NOT NULL,
    msg_uuid VARCHAR(60) NOT NULL, -- map to message
    status bool,
    message_sent_time TIMESTAMP DEFAULT now(),
    PRIMARY KEY (m_uuid),
    FOREIGN KEY (msg_uuid) REFERENCES msg_message(msg_uuid) 
);

/**
* Message table
* Modules: msg
* Created: 11-FEB-2008 mifan@respere.com
* Last Edited: 11-FEB-2008 mifan@respere.com 
*/
DROP TABLE IF EXISTS msg_message;
CREATE TABLE msg_message (
    msg_uuid VARCHAR(60) NOT NULL,
    message_content VARCHAR(500),
    PRIMARY KEY (msg_uuid)
);




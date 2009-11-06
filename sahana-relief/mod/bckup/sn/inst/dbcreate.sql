/**
* Social Netork tables
* Module        : sn
* Created on    : 14-june-2008
* Created by    : Harsha Halgaswatta
* Email         : Harsha.Halgaswatta@gmail.com
*/

-- drop table into order to support innodb installation
DROP TABLE if EXISTS sn_members;
DROP TABLE if EXISTS sn_posts;
DROP TABLE if EXISTS sn_forum_topics;
DROP TABLE if EXISTS sn_forum_posts;
DROP TABLE if EXISTS sn_admin;
DROP TABLE if EXISTS sn_groups;




CREATE TABLE sn_members(
	sn_mem_uuid VARCHAR(80),
	sn_mem_email VARCHAR(80),
	sn_mem_dob VARCHAR(30),
	sn_mem_homepage VARCHAR(30),
	sn_mem_alert_state VARCHAR(30),
	sn_mem_gender VARCHAR(30),
	sn_mem_country VARCHAR(30),
	sn_mem_city VARCHAR(30),
	sn_mem_interests VARCHAR(30),
	sn_mem_experience text,
	sn_mem_other_info text,
        PRIMARY KEY(sn_mem_uuid)

);


CREATE TABLE sn_admin(
   ad_uuid varchar(80),
   ad_username varchar(30),
   ad_password varchar(30),
   ad_level varchar(20)

);


CREATE TABLE sn_forum_topics(
	topic_id VARCHAR(80),
	topic_title VARCHAR(150),
	topic_create_time datetime,
	topic_owner VARCHAR(150),
        PRIMARY KEY(topic_id)

);


CREATE TABLE sn_forum_posts(
	post_id int not null auto_increment,
	topic_id VARCHAR(150),
	post_text text,
	post_create_time datetime,
	post_owner VARCHAR(150),
        PRIMARY KEY(post_id),
   FOREIGN KEY (topic_id) REFERENCES sn_forum_topics(topic_id)


);


CREATE TABLE sn_groups(
  group_id varchar(80) not null,
  group_name varchar(80),
  group_key_word varchar(30),
  group_category varchar(80),
  group_owner varchar(80),
  group_created_date datetime,
  group_description text,
  group_access_level varchar(30),
 	PRIMARY KEY(group_id)

);


CREATE TABLE sn_group_mem(
   sn_mem_uuid VARCHAR(80),
   group_id VARCHAR(80),

  FOREIGN KEY (sn_mem_uuid) REFERENCES sn_members(sn_mem_uuid) ON DELETE CASCADE,
  FOREIGN KEY (group_id) REFERENCES sn_groups(group_id)


);

CREATE TABLE sn_friend_list(
   sn_mem_uuid VARCHAR(80),
   friend_id VARCHAR(80),

  FOREIGN KEY (sn_mem_uuid) REFERENCES sn_members(sn_mem_uuid) ON DELETE CASCADE,
  FOREIGN KEY (friend_id) REFERENCES sn_members(sn_mem_uuid)


);

CREATE TABLE sn_mem_posts(
   written_id int not null auto_increment,
   sn_mem_uuid VARCHAR(80),
   written_text text,
   written_person VARCHAR(80),
   written_time datetime,

  PRIMARY KEY (written_id),
  FOREIGN KEY (sn_mem_uuid) REFERENCES sn_members(sn_mem_uuid)ON DELETE CASCADE
);
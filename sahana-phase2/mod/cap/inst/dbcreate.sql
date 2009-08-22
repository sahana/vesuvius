
DROP TABLE IF EXISTS `cap_agg`;
CREATE TABLE cap_agg (
id varchar(150) NOT NULL,
feed_url varchar(150) NOT NULL,
server_name varchar(150) NOT NULL,
last_updated timestamp NULL,
total_entries int(5) NULL,
server_location varchar(100) NOT NULL,
author varchar(100) NOT NULL,
avg_update_time int(3),
subscription_date varchar(100) ,
user varchar(30) NOT NULL,
priority int(3),
verified bool,
deleted bool,
unread int(3) NULL
);

DROP TABLE IF EXISTS `cap_agg_alerts`;
CREATE TABLE cap_agg_alerts (
id varchar(150) NOT NULL,
title varchar(100) NOT NULL,
area varchar(200) NOT NULL,
type varchar(50) NOT NULL,
severity int(1) NULL,
link varchar(100) NOT NULL,
status varchar(50) NULL,
updated timestamp,
category varchar(50) NULL,
urgency varchar(50) NULL,
certainity varchar(50) NULL,
longlat varchar(100) NULL,
alert_file_name varchar(100) NULL,
feed_id varchar(100)
);

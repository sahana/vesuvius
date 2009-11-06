/**====================== Situation Report (SITRep) Tables=============**/

/**
* SitRep information table that keep individual report information 
* Modules: sr 
* Created: 08-OCT-2008 pradeeper@respere.com
* Last Edited: 
* 
*/
DROP TABLE IF EXISTS `sitrep_info`;
CREATE TABLE sitrep_info
(
	report_id VARCHAR(20) NOT NULL,
	name VARCHAR(100) NOT NULL,
	description VARCHAR(200),
	incident_id BIGINT,
	create_date timestamp,
	FOREIGN KEY (incident_id) REFERENCES incident (incident_id),  
	PRIMARY KEY(report_id)
);

/**
* SitRep detail table that store rest of the information 
* Modules: sr 
* Created: 08-OCT-2008 pradeeper@respere.com
* Last Edited: 
* 
*/
DROP TABLE IF EXISTS `sitrep_detail`;
CREATE TABLE sitrep_detail
(
	report_id VARCHAR(20) NOT NULL,
	rcd_id MEDIUMINT NOT NULL AUTO_INCREMENT,
	update_date timestamp,
	author VARCHAR(100),
	summary LONGTEXT,
	event_dev LONGTEXT,
	act LONGTEXT,
	key_fig LONGTEXT,
	status VARCHAR(10),
	datetime timestamp,
	UNIQUE ( `rcd_id` ),
	FOREIGN KEY (report_id) REFERENCES sitrep_info (report_id),
	PRIMARY KEY(rcd_id, report_id)
);
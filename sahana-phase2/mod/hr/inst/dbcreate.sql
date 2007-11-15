/**
* Housing Registry And Reconstruction Table Structure
* Module        : hr 
* Created on    : 26 -Nov-2006 
* Created by    : Sheran Corera  
* Email         : sheran@opensource.lk
*/

-- drop table into order to support innodb installation
DROP TABLE if EXISTS hr_site_location_details_table;
DROP TABLE if EXISTS hr_site_infrastructure_details_table;
DROP TABLE if EXISTS hr_site_house_details_table;
DROP TABLE if EXISTS hr_assign_contractor_to_site_table;
DROP TABLE if EXISTS hr_site_main_coordinator_details_table;
DROP TABLE if EXISTS hr_site_allocated_organization_table;
DROP TABLE if EXISTS hr_site_name_and_uid_table;
DROP TABLE if EXISTS hr_assign_site_to_contractor_table;
DROP TABLE if EXISTS hr_contractor_table;
DROP TABLE if EXISTS hr_damaged_house_location_details_table;
DROP TABLE if EXISTS hr_damaged_house_basic_details_table;
DROP TABLE if EXISTS hr_family_head_details_table;

CREATE TABLE hr_family_head_details_table(
	family_head_name VARCHAR(80),
 	family_head_create_uid VARCHAR(80),
	family_head_dob DATE,
        PRIMARY KEY(family_head_create_uid)
);


CREATE TABLE hr_damaged_house_basic_details_table(
	damaged_house_basic_details_uid VARCHAR(80),
	damaged_house_value VARCHAR(30),
	damaged_house_total_sqft VARCHAR(30),
	damaged_house_destruction_level VARCHAR(30),
	damaged_house_address VARCHAR(100),
	damaged_house_additional_details TEXT,
        PRIMARY KEY(damaged_house_basic_details_uid),
	FOREIGN KEY (damaged_house_basic_details_uid) REFERENCES hr_family_head_details_table (family_head_create_uid)
);



CREATE TABLE hr_damaged_house_location_details_table(
	damaged_house_location_uid VARCHAR(80),
	damaged_house_location VARCHAR(20),
        PRIMARY KEY(damaged_house_location_uid),
	FOREIGN KEY (damaged_house_location_uid) REFERENCES hr_damaged_house_basic_details_table(damaged_house_basic_details_uid)
);


CREATE TABLE hr_contractor_table(
	contractor_level VARCHAR(40),
	contractor_name VARCHAR(80),
	contractor_uid VARCHAR(80),
	contractor_dob DATE,
        PRIMARY KEY(contractor_uid)
);


CREATE TABLE hr_assign_site_to_contractor_table(
	assign_site_to_contractor_uid VARCHAR(80),
	assign_site_to_contractor TEXT,
        PRIMARY KEY(assign_site_to_contractor_uid),
	FOREIGN KEY (assign_site_to_contractor_uid) REFERENCES hr_contractor_table(contractor_uid)
);


CREATE TABLE hr_site_name_and_uid_table(
	site_name VARCHAR(80),
	site_uid VARCHAR(80),
        PRIMARY KEY(site_uid)
);


CREATE TABLE hr_site_allocated_organization_table(
	site_allocated_organization_uid VARCHAR(80),
	site_allocated_organization VARCHAR(40),
        PRIMARY KEY(site_allocated_organization_uid),
	FOREIGN KEY (site_allocated_organization_uid) REFERENCES hr_site_name_and_uid_table(site_uid)
);


CREATE TABLE hr_site_main_coordinator_details_table(
	site_main_coordinator_details_uid VARCHAR(80),
	site_main_coordinator_name VARCHAR(80),
	site_main_coordinator_dob DATE,
        PRIMARY KEY(site_main_coordinator_details_uid),
	FOREIGN KEY (site_main_coordinator_details_uid) REFERENCES hr_site_allocated_organization_table(site_allocated_organization_uid)
);


CREATE TABLE hr_assign_contractor_to_site_table(
	assign_contractor_to_site_uid VARCHAR(80),
	assign_contractor_to_site TEXT,
        PRIMARY KEY(assign_contractor_to_site_uid),
	FOREIGN KEY (assign_contractor_to_site_uid) REFERENCES hr_site_main_coordinator_details_table(site_main_coordinator_details_uid)
);


CREATE TABLE hr_site_house_details_table(
	site_house_details_uid VARCHAR(80),
	planned_houses VARCHAR(40),
	constructed_houses VARCHAR(40),
	vacant_houses VARCHAR(40),
        PRIMARY KEY(site_house_details_uid),
	FOREIGN KEY (site_house_details_uid) REFERENCES hr_assign_contractor_to_site_table(assign_contractor_to_site_uid)
);


CREATE TABLE hr_site_infrastructure_details_table(
	site_infrastructure_details_uid VARCHAR(80),
	road  VARCHAR(20),
	water VARCHAR(20),
	electricity VARCHAR(20),
	telephone_or_communication VARCHAR(20),
	sewer VARCHAR(20),
        PRIMARY KEY(site_infrastructure_details_uid),
	FOREIGN KEY (site_infrastructure_details_uid) REFERENCES hr_site_house_details_table(site_house_details_uid)
);


CREATE TABLE hr_site_location_details_table(
	site_location_uid VARCHAR(80),
	site_location VARCHAR(20),
        PRIMARY KEY(site_location_uid),
	FOREIGN KEY (site_location_uid) REFERENCES hr_site_infrastructure_details_table(site_infrastructure_details_uid)
);


-- CONTRACTOR LEVEL
INSERT INTO field_options VALUES ('optn_contractor_level','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_contractor_level','lvl1','Level 1');
INSERT INTO field_options VALUES ('optn_contractor_level','lvl2','Level 2');
INSERT INTO field_options VALUES ('optn_contractor_level','lvl3','Level 3');
INSERT INTO field_options VALUES ('optn_contractor_level','lvl4','Level 4');
INSERT INTO field_options VALUES ('optn_contractor_level','lvl5','Level 5');

-- ALLOCATED ORGANIZATION
INSERT INTO field_options VALUES ('optn_site_allocated_organization','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_site_allocated_organization','slrc','SLRC');
INSERT INTO field_options VALUES ('optn_site_allocated_organization','icda','ICDA');
INSERT INTO field_options VALUES ('optn_site_allocated_organization','udc','UDC');

-- DESTRUCTION LEVEL
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','nt_dmgd','Not Damaged');
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','mnml_dmgs','Minimal Damages');
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','prtl_dmgs','Partial Damages');
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','svr_dmgs','Severe Damages');
INSERT INTO field_options VALUES ('optn_dstrctn_lvl','dstryd_cmpltly','Destroyed Completely');

-- UTILITIES - ROAD
INSERT INTO field_options VALUES ('optn_road','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_road','ys','Yes');
INSERT INTO field_options VALUES ('optn_road','no','No');

-- UTILITIES - WATER
INSERT INTO field_options VALUES ('optn_water','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_water','ys','Yes');
INSERT INTO field_options VALUES ('optn_water','no','No');

-- UTILITIES - ELECTRICITY
INSERT INTO field_options VALUES ('optn_electricity','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_electricity','ys','Yes');
INSERT INTO field_options VALUES ('optn_electricity','no','No');

-- UTILITIES - TELEPHONE OR COMMUNICATION
INSERT INTO field_options VALUES ('optn_telephone_or_communication','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_telephone_or_communication','ys','Yes');
INSERT INTO field_options VALUES ('optn_telephone_or_communication','no','No');

-- UTILITIES - SEWER
INSERT INTO field_options VALUES ('optn_sewer','nt_slctd','--Not Selected--');
INSERT INTO field_options VALUES ('optn_sewer','ys','Yes');
INSERT INTO field_options VALUES ('optn_sewer','no','No');

/**
* Child Protection System Table Structure
* Modules: cps 
* version 1.0
* Created on : 6 -Nov-2005 
* Last Modified-24-APR-2006 
* Created by : Isuru  
* email:isurunishan2000@yahoo.com  
*/

 -- Center Information  Chapter1
 DROP TABLE IF EXISTS child_center;
 CREATE TABLE child_center (
 center_code   VARCHAR(32),
 center_name  VARCHAR(100),
 date  DATE,
 filed_by TEXT,
 function TEXT,
 PRIMARY KEY (center_code));

--Reporters Information
DROP TABLE IF EXISTS child_reporter;
CREATE TABLE child_reporter(
p_uuid BIGINT UNIQUE NOT NULL,
center_code  VARCHAR(32),
rep_full_name varchar(30),
date_of_reg date,
rep_relation varchar(30),
rep_address varchar(30),
rep_phone varchar(30),
rep_email  varchar(30),
di date,
FOREIGN KEY (p_uuid) REFERENCES  person_uuid(p_uuid),
    FOREIGN KEY  (center_code) REFERENCES child_center(center_code) 
    );


 -- All children have a associated person id  Chapter2
 DROP TABLE IF EXISTS child_personal_data;
 CREATE TABLE child_personal_data (
    p_uuid BIGINT UNIQUE NOT NULL,
    center_code  VARCHAR(32),
    age INT,
    place_of_birth VARCHAR(100),
    present_residence VARCHAR(100),
    coming_from VARCHAR(100),
    first_language VARCHAR(100),
bc_status varchar(100),
date_regd date,
is_reg_in_school BOOLEAN,
    FOREIGN KEY (p_uuid) REFERENCES  person_uuid(p_uuid),
    FOREIGN KEY  (center_code) REFERENCES child_center(center_code) 
    );

 -- Family details of children Chapter3,4,5,8
--Other Relationsships
--sister/brother/mother/father/gransparents/friends/otherrelations

 DROP TABLE IF EXISTS child_family_data;
 CREATE TABLE child_family_data (
    id BIGINT AUTO_INCREMENT, 
    p_uuid BIGINT  NOT NULL,
   center_code  VARCHAR(32),
    relationship_to_child VARCHAR(100),
    
    relation_name VARCHAR(100),
    relation_is_alive    BOOLEAN,
    relation_age INT,
    relation_is_living_with_child BOOLEAN,
    relation_profession  VARCHAR(100),
    relation_location   VARCHAR(100),
    relation_is_incenter BOOLEAN,
    relation_is_registeredinschool BOOLEAN, 
    relation_is_official_fostering BOOLEAN,
    died_in_tsunami BOOLEAN,
    is_reported_missing BOOLEAN,
    reason_to_livewith VARCHAR(100),
    PRIMARY KEY(id),  
    FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
    FOREIGN KEY  (center_code) REFERENCES child_center(center_code)   
);
  


-- Child Family status Chapter6
DROP TABLE IF EXISTS child_family_status;
CREATE TABLE child_family_status(
   p_uuid BIGINT UNIQUE NOT NULL,
center_code  VARCHAR(32),
   at_present_family_status VARCHAR(100),
   reason_for_ntbk_prehouse  VARCHAR(100),
   fourth_possibility VARCHAR(100),
  family_income  BOOLEAN,
  details_family TEXT,
  special_material_needed BOOLEAN,
  details_material TEXT,   
  during_tsunami_situ VARCHAR(100),
 
  FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid),
FOREIGN KEY  (center_code) REFERENCES child_center(center_code)
  );    

 -- Child Education  Chapter7
 DROP TABLE IF EXISTS child_education;
 CREATE TABLE child_education(
   p_uuid BIGINT  UNIQUE NOT NULL,
center_code  VARCHAR(32),
   was_gng_to_school_tsunami BOOLEAN,
   school_name_tsunami  VARCHAR(100),
   level_tsunami VARCHAR(100),
   why_tsunami TEXT,
   is_gng_to_school_now BOOLEAN,
   school_name_now VARCHAR(100),
  level_now  VARCHAR(100),
  why_now TEXT,
  is_gng_tution BOOLEAN,
  is_gng_religious_school BOOLEAN,
  is_gng_templ BOOLEAN,
best_friend_1 VARCHAR(100),
best_friend_2 VARCHAR(100),
is_bf1_regd BOOLEAN,
is_bf2_regd BOOLEAN,

 FOREIGN KEY  (center_code) REFERENCES child_center(center_code),
  FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
  );    

--Child Properties Chapter8

 DROP TABLE IF EXISTS child_properties;
 CREATE TABLE child_properties(
   p_uuid BIGINT  UNIQUE NOT NULL,
center_code  VARCHAR(32),
   beating BOOLEAN,
   sexual_abuse  BOOLEAN,
neglecting  BOOLEAN,
child_trafficing  BOOLEAN,
domestic_violence  BOOLEAN,
drink_alcohol  BOOLEAN,
tdh_followup  BOOLEAN,
other VARCHAR(100),          
      

 FOREIGN KEY  (center_code) REFERENCES child_center(center_code),
  FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
  );    





-- Child health  Chapter9
DROP TABLE IF EXISTS child_health;
CREATE TABLE child_health(
   p_uuid BIGINT UNIQUE NOT NULL,
center_code  VARCHAR(32),
  is_disabled BOOLEAN,
  disability_explanation TEXT,   
  is_received_assistance BOOLEAN,
  assistance_explanation TEXT,
 is_physically_affected BOOLEAN,
 physically_affected_explanation TEXT,
 is_health_affected BOOLEAN,
 health_affected_explanation TEXT,
 has_headache BOOLEAN,
 has_nausea  BOOLEAN,
 has_eye_problems BOOLEAN,
 has_rashes_or_skin_problems BOOLEAN,
 has_aches_or_panes BOOLEAN,
 has_vomiting BOOLEAN,
 has_seen_by_doctor BOOLEAN,
 is_suffered_from_chronic_disease_before_disaster BOOLEAN,
 chronic_disease_explanation TEXT,
 has_child_been_seriouly_injured_before_disaster BOOLEAN,
 injured_explanation TEXT,
 has_child_been_operated_last12months BOOLEAN,
 operation_explanation TEXT,
at_present_still_effected BOOLEAN,
affected_explain varchar(100),
FOREIGN KEY  (center_code) REFERENCES child_center(center_code),
 FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
  );     

-- Child behaviour Chapter10
DROP TABLE IF EXISTS child_behaviour;
CREATE TABLE child_behaviour(
p_uuid BIGINT  UNIQUE NOT NULL,
center_code  VARCHAR(32),
spontanious_answer_given_by VARCHAR(100),
question1 BOOLEAN,
question2 BOOLEAN,
question3 BOOLEAN,
question4 BOOLEAN,
question5 BOOLEAN,
question6 BOOLEAN,
question7 BOOLEAN,
question8 BOOLEAN,
question9 BOOLEAN,
question10 BOOLEAN,
question11 BOOLEAN,
question12 BOOLEAN,
question13 BOOLEAN,
question14 BOOLEAN,
question15 BOOLEAN,
question16 BOOLEAN,
question17 BOOLEAN,
question18 BOOLEAN,
question19 BOOLEAN,
question20 BOOLEAN,

councellor_name VARCHAR(100),

FOREIGN KEY  (center_code) REFERENCES child_center(center_code),
 FOREIGN KEY (p_uuid) REFERENCES person_uuid(p_uuid)
);  

delete from field_options;
-- PERSON GENDER 
-- INSERT INTO field_options VALUES ('opt_gender','unk','Unknown');
INSERT INTO field_options VALUES ('opt_gender','fml','Female');
INSERT INTO field_options VALUES ('opt_gender','mal','Male');
INSERT INTO field_options VALUES ('opt_gender','fml','Female');



-- COUNTRY VALUES
INSERT INTO field_options VALUES ('opt_country','uk','United Kingdom');
INSERT INTO field_options VALUES ('opt_country','uk','United Kingdom');
INSERT INTO field_options VALUES ('opt_country','lanka','Sri Lanka');

-- RACE VALUES 
INSERT INTO field_options VALUES ('opt_race','unk','Unknown');
INSERT INTO field_options VALUES ('opt_race','unk','Unknown');

INSERT INTO field_options VALUES ('opt_race','sing1','Sinhalese');
INSERT INTO field_options VALUES ('opt_race','tamil','Tamil');
INSERT INTO field_options VALUES ('opt_race','mus','Muslim');
INSERT INTO field_options VALUES ('opt_race','bgr','Burgher');
INSERT INTO field_options VALUES ('opt_race','other','Other');
INSERT INTO field_options VALUES ('opt_race','other','Other');

-- RELIGION VALUES 

INSERT INTO field_options VALUES ('opt_religion','unk','Unknown');
INSERT INTO field_options VALUES ('opt_religion','bud','Buddhist');
INSERT INTO field_options VALUES ('opt_religion','chr','Christian');
INSERT INTO field_options VALUES ('opt_religion','hdu','Hindu');
INSERT INTO field_options VALUES ('opt_religion','isl','Islam');
INSERT INTO field_options VALUES ('opt_religion','oth','Other');
INSERT INTO field_options VALUES ('opt_religion','unk','Unknown');


-- MARITIAL STATUS VALUES 
INSERT INTO field_options VALUES ('opt_marital_status','unk','Unknown');
INSERT INTO field_options VALUES ('opt_marital_status','unk','Unknown');
INSERT INTO field_options VALUES ('opt_marital_status','sin','Single');
INSERT INTO field_options VALUES ('opt_marital_status','mar','Married');
INSERT INTO field_options VALUES ('opt_marital_status','div','Divorced');

INSERT INTO field_options VALUES ('opt_child_center_names','1','1');



--RelationShip Type

 insert into field_options values('opt_relationship_type','fat','Father');
 insert into field_options values('opt_relationship_type','fat','Father');
 
insert into field_options values('opt_relationship_type','mot','Mother');
 insert into field_options values('opt_relationship_type','bro','Brother');
 insert into field_options values('opt_relationship_type','sis','Sister');
 insert into field_options values('opt_relationship_type','gft','GrandFather');
 insert into field_options values('opt_relationship_type','gmt','GrandMother');
 insert into field_options values('opt_relationship_type','fnd','Friend');
 insert into field_options values('opt_relationship_type','oth','Other');
INSERT INTO field_options VALUES('opt_relationship_type','gfpat','GrandFatherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gfmat','GrandFatherMaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmpat','GrandMotherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmmat','GrandMotherMaternal');


--Child Family Status
insert into field_options values('opt_child_family_status','back','Back in their Own House');
 insert into field_options values('opt_child_family_status','back','Back in their Own House');
 insert into field_options values('opt_child_family_status','camp','Living in a Shelter in and IDP camp');
 insert into field_options values('opt_child_family_status','host','Hosted By relatives or Friends');
 insert into field_options values('opt_child_family_status','new','Living in a new house');
 insert into field_options values('opt_child_family_status','otherfstatus','Other');

--BirthCertificate Status
insert into field_options values('opt_bc_status','yes','Yes');
insert into field_options values('opt_bc_status','yes','Yes');

insert into field_options values('opt_bc_status','no','No');
insert into field_options values('opt_bc_status','lost','Lost');

--Months
insert into field_options values('opt_month','01','Jan');
insert into field_options values('opt_month','01','Jan');
insert into field_options values('opt_month','02','Feb');
insert into field_options values('opt_month','03','Mar');
insert into field_options values('opt_month','04','Apr');
insert into field_options values('opt_month','05','May');
insert into field_options values('opt_month','06','Jun');
insert into field_options values('opt_month','07','Jul');
insert into field_options values('opt_month','08','Aug');
insert into field_options values('opt_month','09','Sep');
insert into field_options values('opt_month','10','Oct');
insert into field_options values('opt_month','11','Nov');
insert into field_options values('opt_month','12','Dec');
insert into field_options values('opt_month','12','Dec');


--Dates
insert into field_options values('opt_date','1','1');
insert into field_options values('opt_date','1','1');
insert into field_options values('opt_date','2','2');
insert into field_options values('opt_date','3','3');
insert into field_options values('opt_date','4','4');
insert into field_options values('opt_date','5','5');
insert into field_options values('opt_date','6','6');
insert into field_options values('opt_date','7','7');
insert into field_options values('opt_date','8','8');
insert into field_options values('opt_date','9','9');
insert into field_options values('opt_date','10','10');
insert into field_options values('opt_date','11','11');
insert into field_options values('opt_date','12','12');
insert into field_options values('opt_date','13','13');
insert into field_options values('opt_date','14','14');
insert into field_options values('opt_date','15','15');
insert into field_options values('opt_date','16','16');
insert into field_options values('opt_date','17','17');
insert into field_options values('opt_date','18','18');
insert into field_options values('opt_date','19','19');
insert into field_options values('opt_date','20','20');
insert into field_options values('opt_date','21','21');
insert into field_options values('opt_date','22','22');
insert into field_options values('opt_date','23','23');
insert into field_options values('opt_date','24','24');
insert into field_options values('opt_date','25','25');
insert into field_options values('opt_date','26','26');
insert into field_options values('opt_date','27','27');
insert into field_options values('opt_date','28','28');
insert into field_options values('opt_date','29','29');
insert into field_options values('opt_date','30','30');
insert into field_options values('opt_date','31','31');

--Years
insert into field_options values('opt_year','2004','2004');
insert into field_options values('opt_year','2004','2004');
insert into field_options values('opt_year','2005','2005');
insert into field_options values('opt_year','2006','2006');
insert into field_options values('opt_year','2007','2007');
insert into field_options values('opt_year','2008','2008');
insert into field_options values('opt_year','2009','2009');
insert into field_options values('opt_year','2010','2010');


--House Not Backed Reason

insert into field_options values('opt_child_house_not_backed_reason','imp','Housing is impossible in that zone  ');
insert into field_options values('opt_child_house_not_backed_reason','par','House is Solely or partially destroyed');
insert into field_options values('opt_child_house_not_backed_reason','afr','Afraid of going back to the house ');
insert into field_options values('opt_child_house_not_backed_reason','hnlr','Not Relavant ');
insert into field_options values('opt_child_house_not_backed_reason','otherreason','Other');
insert into field_options values('opt_child_house_not_backed_reason','otherreason','Other');

--House
insert into field_options values('opt_house','hse','House was  partially or totally destroyed');
insert into field_options values('opt_house','hse','House was  partially or totally destroyed');
insert into field_options values('opt_house','pro','Family Lost Most or All of their property and belongings');





-- AGE GROUP VALUES
INSERT INTO field_options VALUES ('opt_age_group','unk','0-4');
INSERT INTO field_options VALUES ('opt_age_group','unk','0-4');
INSERT INTO field_options VALUES ('opt_age_group','inf','5-9');
INSERT INTO field_options VALUES ('opt_age_group','chi','10-14');
INSERT INTO field_options VALUES ('opt_age_group','you','15-18');
INSERT INTO field_options VALUES ('opt_age_group','adu','>18');



--Child Beahaviour Improvement
INSERT INTO field_options VALUES('opt_behaviourimp','1','Yes');
INSERT INTO field_options VALUES('opt_behaviourimp','1','Yes');

INSERT INTO field_options VALUES('opt_behaviourimp','0','No');
INSERT INTO field_options VALUES('opt_behaviourimp','2','NotRelavant');


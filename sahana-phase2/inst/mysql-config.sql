-- GROUP TYPES
INSERT INTO field_options VALUES('opt_group_type','fam','family');
INSERT INTO field_options VALUES('opt_group_type','com','company');
INSERT INTO field_options VALUES('opt_group_type','soc','society');
INSERT INTO field_options VALUES('opt_group_type','oth','other');

-- IDENTITY CARD / PASSPORT TYPES
INSERT INTO field_options VALUES('opt_id_type','nic','National Identity Card');
INSERT INTO field_options VALUES('opt_id_type','pas','Passport');
INSERT INTO field_options VALUES('opt_id_type','dln','Driving License Number');
INSERT INTO field_options VALUES('opt_id_type','oth','Other');

-- PERSON STATUS VALUES
INSERT INTO field_options VALUES ('opt_status','ali','Alive & Well');
INSERT INTO field_options VALUES ('opt_status','mis','Missing');
INSERT INTO field_options VALUES ('opt_status','inj','Injured');
INSERT INTO field_options VALUES ('opt_status','dec','Deceased');


-- PERSON GENDER 
INSERT INTO field_options VALUES ('opt_gender','unk','Unknown');
INSERT INTO field_options VALUES ('opt_gender','mal','Male');
INSERT INTO field_options VALUES ('opt_gender','fml','Female');



-- PERSON CONTACT TYPES
INSERT INTO field_options VALUES ('opt_contact_type','home','Home(permanent address)');
INSERT INTO field_options VALUES ('opt_contact_type','name','Contact Person');
INSERT INTO field_options VALUES ('opt_contact_type','pmob','Personal Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','curr','Current Phone');
INSERT INTO field_options VALUES ('opt_contact_type','cmob','Current Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','emai','Email address');
INSERT INTO field_options VALUES ('opt_contact_type','fax','Fax Number');
INSERT INTO field_options VALUES ('opt_contact_type','inst','Instant Messenger');

-- PERSON LOCATION TYPES 
INSERT INTO field_options VALUES ('opt_person_loc_type','hom','Permanent home address)');
INSERT INTO field_options VALUES ('opt_person_loc_type','imp','Impact location');
INSERT INTO field_options VALUES ('opt_person_loc_type','cur','Current location');

-- AGE GROUP VALUES
INSERT INTO field_options VALUES ('opt_age_group','unk','Unknown');
INSERT INTO field_options VALUES ('opt_age_group','inf','Infant (0-1)');
INSERT INTO field_options VALUES ('opt_age_group','chi','Child (1-15)');
INSERT INTO field_options VALUES ('opt_age_group','you','Young Adult (16-21)');
INSERT INTO field_options VALUES ('opt_age_group','adu','Adult (22-50)');
INSERT INTO field_options VALUES ('opt_age_group','sen','Senior Citizen (50+)');

-- COUNTRY VALUES
INSERT INTO field_options VALUES ('opt_country','uk','United Kingdom');
INSERT INTO field_options VALUES ('opt_country','lanka','Sri Lanka');

-- RACE VALUES 
INSERT INTO field_options VALUES ('opt_race','unk','Unknown');
INSERT INTO field_options VALUES ('opt_race','sing1','Sinhalese');
INSERT INTO field_options VALUES ('opt_race','tamil','Tamil');
INSERT INTO field_options VALUES ('opt_race','other','Other');

-- RELIGION VALUES 
INSERT INTO field_options VALUES ('opt_religion','unk','Unknown');
INSERT INTO field_options VALUES ('opt_religion','bud','Buddhist');
INSERT INTO field_options VALUES ('opt_religion','chr','Christian');
INSERT INTO field_options VALUES ('opt_religion','oth','Other');

-- MARITIAL STATUS VALUES 
INSERT INTO field_options VALUES ('opt_marital_status','unk','Unknown');
INSERT INTO field_options VALUES ('opt_marital_status','sin','Single');
INSERT INTO field_options VALUES ('opt_marital_status','mar','Married');
INSERT INTO field_options VALUES ('opt_marital_status','div','Divorced');

-- BLOOD TYPE VALUES 
INSERT INTO field_options VALUES ('opt_blood_type','unk','Unknown');
INSERT INTO field_options VALUES ('opt_blood_type','ab','AB');
INSERT INTO field_options VALUES ('opt_blood_type','a+','A+');
INSERT INTO field_options VALUES ('opt_blood_type','o','O');

-- EYE COLOR VALUES
INSERT INTO field_options VALUES ('opt_eye_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_eye_color','bla','Black');
INSERT INTO field_options VALUES ('opt_eye_color','bro','Light Brown');
INSERT INTO field_options VALUES ('opt_eye_color','blu','Blue');
INSERT INTO field_options VALUES ('opt_eye_color','oth','Other');

-- SKIN COLOR VALUES
INSERT INTO field_options VALUES ('opt_skin_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_skin_color','bla','Black');
INSERT INTO field_options VALUES ('opt_skin_color','bro','Dark Brown');
INSERT INTO field_options VALUES ('opt_skin_color','fai','Fair');
INSERT INTO field_options VALUES ('opt_skin_color','whi','White');
INSERT INTO field_options VALUES ('opt_skin_color','oth','Other');

-- HAIR COLOR VALUES
INSERT INTO field_options VALUES ('opt_hair_color','unk','Unknown');
INSERT INTO field_options VALUES ('opt_hair_color','bla','Black');
INSERT INTO field_options VALUES ('opt_hair_color','bro','Brown');
INSERT INTO field_options VALUES ('opt_hair_color','red','Red');
INSERT INTO field_options VALUES ('opt_hair_color','blo','Blond');
INSERT INTO field_options VALUES ('opt_hair_color','oth','Other');

-- CAMP TYPE VALUES 
INSERT INTO field_options VALUES ('opt_camp_type','ngo','NGO Run Camp');
INSERT INTO field_options VALUES ('opt_camp_type','tmp','Temporary Shelter');
INSERT INTO field_options VALUES ('opt_camp_type','gov','Government Run Camp');

-- CAMP SERVICES 
INSERT INTO field_options VALUES ('opt_camp_service','mdc','Medical Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','snt','Sanitation Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','wat','Water Facilities');

-- ORGANIZATION TYPES 
INSERT INTO field_options VALUES("opt_org_type","gov","Government");
INSERT INTO field_options VALUES("opt_org_type","priv","Private");
INSERT INTO field_options VALUES("opt_org_type","multi","Multinational");
INSERT INTO field_options VALUES("opt_org_type","bilat","Bilateral");

-- ORGANIZATION SECTOR VALUES
INSERT INTO field_options VALUES("opt_sector_type","agri","Agriculture");
INSERT INTO field_options VALUES("opt_sector_type","adev","Area Development");
INSERT INTO field_options VALUES("opt_sector_type","comm","Communications");
INSERT INTO field_options VALUES("opt_sector_type","dprep","Disaster Preparation");
INSERT INTO field_options VALUES("opt_sector_type","ene","Energy");
INSERT INTO field_options VALUES("opt_sector_type","hlth","Health");

-- LOCATION TYPE VALUES
INSERT INTO field_options VALUES ('opt_location_type','1','Country');
INSERT INTO field_options VALUES ('opt_location_type','2','Province');
INSERT INTO field_options VALUES ('opt_location_type','3','District');
INSERT INTO field_options VALUES ('opt_location_type','4','Village');

-- INSERT LOCATIONS (COUNTRY, PROVINCE, DISTRICT, ETC)

INSERT INTO location VALUES (1,0,'1','1','Sri Lanka','lk','Sri Lanka added as a country');
INSERT INTO location VALUES (2,0,'2','1','Pakistan','pk','Pakistan added as a country');
INSERT INTO location VALUES (3,0,'3','1','United Kingdom','uk','United Kingdom added as a country');
INSERT INTO location VALUES (4,0,'4','1','United States','us','United States added as a country');
INSERT INTO location VALUES (5,1,'1.1','2','Western','wes','Western  added as a province in Sri Lanka');
INSERT INTO location VALUES (6,5,'1.1.1','3','Colombo','cmb','Colombo added as a district in Srilanka Western Province');
INSERT INTO location VALUES (7,6,'1.1.1.1','4','Pettah','pet','pettah added as a village in Srilanka Western Province');
INSERT INTO location VALUES (8,3,'3.1','2','East Anagalia','ea','');
INSERT INTO location VALUES (9,8,'3.1.1','3','Suffolk','suf','');
INSERT INTO location VALUES (10,9,'3.1.1.1','4','ipswich','ip','');
INSERT INTO location VALUES (11,1,'1.1','2','Eastern','est','Eastern  added as a province in Sri Lanka');
INSERT INTO location VALUES (12,1,'1.1','2','south','sou','South  added as a province in Sri Lanka');
INSERT INTO location VALUES (13,5,'1.1.1','3','Kalutara','klt','Colombo added as a district in Srilanka Western Province');
INSERT INTO location VALUES (14,6,'1.1.1.1','4','dehiwala','dwh','dehiwala added as a village in Srilanka Western Province');


-- INSERT CONFIG VALUES
INSERT INTO config VALUES ( 'cr', 'division_type', '2');
INSERT INTO config VALUES('admin','acl','false');
INSERT INTO config VALUES('admin','acl_base','no');

-- INSERT THE INBUILT SAHANA ORGANIZATION
INSERT INTO org_main(o_uuid,parent_id,name,opt_org_type)VALUES(0,0,'sahana','gov');

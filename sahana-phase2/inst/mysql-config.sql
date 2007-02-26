
-- GROUP TYPES
INSERT INTO field_options VALUES('opt_group_type','fam','family');
INSERT INTO field_options VALUES('opt_group_type','com','company');
INSERT INTO field_options VALUES('opt_group_type','soc','society');
INSERT INTO field_options VALUES('opt_group_type','tor','tourists');
INSERT INTO field_options VALUES('opt_group_type','oth','other');
INSERT INTO field_options VALUES('opt_group_type','===','==Select Option==');
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
-- INSERT INTO field_options VALUES ('opt_gender','unk','Unknown');
INSERT INTO field_options VALUES ('opt_gender','mal','Male');
INSERT INTO field_options VALUES ('opt_gender','fml','Female');

--PERSON RELATIONSHIPS
INSERT INTO field_options VALUES('opt_relationship_type','fat','Father');
INSERT INTO field_options VALUES('opt_relationship_type','mot','Mother');
INSERT INTO field_options VALUES('opt_relationship_type','bro','Brother');
INSERT INTO field_options VALUES('opt_relationship_type','sis','Sister');
INSERT INTO field_options VALUES('opt_relationship_type','gft','GrandFather');
INSERT INTO field_options VALUES('opt_relationship_type','gmt','GrandMother');
INSERT INTO field_options VALUES('opt_relationship_type','gfpat','GrandFatherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gfmat','GrandFatherMaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmpat','GrandMotherPaternal');
INSERT INTO field_options VALUES('opt_relationship_type','gmmat','GrandMotherMaternal');
INSERT INTO field_options VALUES('opt_relationship_type','fnd','Friend');
INSERT INTO field_options VALUES('opt_relationship_type','oth','Other');



-- PERSON CONTACT TYPES
INSERT INTO field_options VALUES ('opt_contact_type','home','Home(permanent address)');
INSERT INTO field_options VALUES ('opt_contact_type','name','Contact Person');
INSERT INTO field_options VALUES ('opt_contact_type','pmob','Personal Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','curr','Current Phone');
INSERT INTO field_options VALUES ('opt_contact_type','cmob','Current Mobile');
INSERT INTO field_options VALUES ('opt_contact_type','emai','Email address');
INSERT INTO field_options VALUES ('opt_contact_type','fax','Fax Number');
INSERT INTO field_options VALUES ('opt_contact_type','web','Website');
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
INSERT INTO field_options VALUES ('opt_race','filip','Filipino');
INSERT INTO field_options VALUES ('opt_race','other','Other');

-- RELIGION VALUES 
INSERT INTO field_options VALUES ('opt_religion','unk','Unknown');
INSERT INTO field_options VALUES ('opt_religion','bud','Buddhist');
INSERT INTO field_options VALUES ('opt_religion','chr','Christian');
INSERT INTO field_options VALUES ('opt_religion','mus','Muslim');
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
INSERT INTO field_options VALUES ('opt_camp_type','gov','Government Evacuation Center');

-- CAMP SERVICES 
INSERT INTO field_options VALUES ('opt_camp_service','adm','Administrative Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','snt','Sanitation Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','wat','Water Facilities');
INSERT INTO field_options VALUES ('opt_camp_service','mdc','Medical Facilities');

-- ORGANIZATION TYPES 
INSERT INTO field_options VALUES('opt_org_type','gov','Government');
INSERT INTO field_options VALUES('opt_org_type','priv','Private');
INSERT INTO field_options VALUES('opt_org_type','ngo','NGO');
INSERT INTO field_options VALUES('opt_org_type','ingo','International NGO');
INSERT INTO field_options VALUES('opt_org_type','mngo','Multinational NGO');

-- ORGANIZATION TYPES 
INSERT INTO field_options VALUES('opt_org_sub_type','dep','Department');
INSERT INTO field_options VALUES('opt_org_sub_type','subs','Subsidiary');
INSERT INTO field_options VALUES('opt_org_sub_type','bra','Branch');

-- ORGANIZATION SECTOR VALUES
INSERT INTO field_options VALUES('opt_sector_type','sup','Supplier of Goods');
INSERT INTO field_options VALUES('opt_sector_type','comm','Communications');
INSERT INTO field_options VALUES('opt_sector_type','dana','DANA');
INSERT INTO field_options VALUES('opt_sector_type','ems','EMS');
INSERT INTO field_options VALUES('opt_sector_type','fs','FS');
INSERT INTO field_options VALUES('opt_sector_type','rel','Relief');
INSERT INTO field_options VALUES('opt_sector_type','rehab','Rehabilitation');
INSERT INTO field_options VALUES('opt_sector_type','sar','SAR');

-- LOCATION TYPE VALUES
INSERT INTO field_options VALUES ('opt_location_type','1','Country');
INSERT INTO field_options VALUES ('opt_location_type','2','State');
INSERT INTO field_options VALUES ('opt_location_type','3','City');

-- CATALOGUE MAX_DEPTH VALUE
INSERT INTO field_options VALUES ('opt_cs_depth','6','depth');

-- REPORT AND CHART UPDATE FREQUENCY VALUES
INSERT INTO field_options VALUES ('opt_rs_rep_freq','30','the frequency of report update');
INSERT INTO field_options VALUES ('opt_rs_cht_freq','30','the frequency of chart update');

-- INSERT MODULE VALUES
INSERT INTO modules VALUES ('cr', '0.2', TRUE);
INSERT INTO modules VALUES ('or', '0.2', TRUE);
INSERT INTO modules VALUES ('admin', '0.2', TRUE);
INSERT INTO modules VALUES ('gis', '0.2', TRUE);

-- INSERT CONFIG VALUES
INSERT INTO config VALUES ( 'cr', 'division_type', '2');
--INSERT INTO config VALUES ( 'or', 'loc_start', NULL);
--INSERT INTO config VALUES ( 'or', 'loc_range_start', 1);
--INSERT INTO config VALUES ( 'or', 'loc_range_end', 3);
--INSERT INTO config VALUES('admin','acl','false');
--INSERT INTO config VALUES('admin','acl_base','no');

-- INSERT THE INBUILT SAHANA ORGANIZATION
--INSERT INTO org_main(o_uuid,name,org_type,privacy,archive) VALUES(0,'sahana','gov','','','','',1,0);
--INSERT INTO org_main(o_uuid,name,privacy,archived) VALUES(0,'sahana',1,0);




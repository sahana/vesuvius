-- MySQL dump 9.11
--
-- Host: localhost    Database: erms
-- ------------------------------------------------------
-- Server version	4.0.22-standard

--
-- Table structure for table `HSE_INFRACTURE_MST`
--

CREATE TABLE HSE_INFRACTURE_MST (
  INFRACTURE_ID int(11) NOT NULL auto_increment,
  INFRACTURE_DESC varchar(100) NOT NULL default '',
  PRIMARY KEY  (INFRACTURE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `HSE_INFRACTURE_MST`
--

INSERT INTO HSE_INFRACTURE_MST VALUES (8,'Access');
INSERT INTO HSE_INFRACTURE_MST VALUES (7,'Water');
INSERT INTO HSE_INFRACTURE_MST VALUES (6,'Telecommunication');
INSERT INTO HSE_INFRACTURE_MST VALUES (9,'Sewerage');
INSERT INTO HSE_INFRACTURE_MST VALUES (10,'Electricity');

--
-- Table structure for table `HSE_LAND_INFRACTURE_TXN`
--

CREATE TABLE HSE_LAND_INFRACTURE_TXN (
  LAND_ID int(11) NOT NULL default '0',
  INFRACTURE_ID int(11) NOT NULL default '0',
  SEQ_ID int(6) NOT NULL auto_increment,
  PRIMARY KEY  (SEQ_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `HSE_LAND_INFRACTURE_TXN`
--

INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (109,7,66);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (108,7,62);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (108,8,61);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (107,7,56);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (107,8,55);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (109,8,65);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (109,9,67);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (110,8,69);
INSERT INTO HSE_LAND_INFRACTURE_TXN VALUES (110,7,70);

--
-- Table structure for table `HSE_LAND_TYPE_MST`
--

CREATE TABLE HSE_LAND_TYPE_MST (
  LAND_TYPE_ID int(11) NOT NULL auto_increment,
  LAND_TYPE_NAME varchar(100) NOT NULL default '',
  PRIMARY KEY  (LAND_TYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `HSE_LAND_TYPE_MST`
--

INSERT INTO HSE_LAND_TYPE_MST VALUES (1,'High');
INSERT INTO HSE_LAND_TYPE_MST VALUES (2,'Marshy');
INSERT INTO HSE_LAND_TYPE_MST VALUES (3,'Low');

--
-- Table structure for table `HSE_SUB_DIVISION_MST`
--

CREATE TABLE HSE_SUB_DIVISION_MST (
  SUB_DIV_ID int(11) NOT NULL default '0',
  SUB_DIV_NAME varchar(100) NOT NULL default '',
  DIV_ID int(11) NOT NULL default '0'
) TYPE=MyISAM;

--
-- Dumping data for table `HSE_SUB_DIVISION_MST`
--

INSERT INTO HSE_SUB_DIVISION_MST VALUES (1,'Value1',2);
INSERT INTO HSE_SUB_DIVISION_MST VALUES (0,'Value0',0);

--
-- Table structure for table `activity`
--

CREATE TABLE activity (
  Id int(11) NOT NULL auto_increment,
  Status int(11) NOT NULL default '0',
  Description varchar(100) NOT NULL default '',
  OrgCode varchar(100) NOT NULL default '',
  DateStarted date NOT NULL default '0000-00-00',
  DateCompleted date default '0000-00-00',
  Notes varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `activity`
--


--
-- Table structure for table `assistance`
--

CREATE TABLE assistance (
  Id int(11) NOT NULL auto_increment,
  Date date NOT NULL default '0000-00-00',
  Agency varchar(100) NOT NULL default '',
  Sectors int(11) default '0',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `assistance`
--


--
-- Table structure for table `assistance_activities`
--

CREATE TABLE assistance_activities (
  AssistanceId int(11) NOT NULL default '0',
  ActivityId int(11) NOT NULL default '0',
  PRIMARY KEY  (AssistanceId,ActivityId)
) TYPE=MyISAM;

--
-- Dumping data for table `assistance_activities`
--


--
-- Table structure for table `assistance_hr_deployments`
--

CREATE TABLE assistance_hr_deployments (
  AssistanceId int(11) NOT NULL default '0',
  HRDeploymentId int(11) NOT NULL default '0',
  PRIMARY KEY  (AssistanceId,HRDeploymentId)
) TYPE=MyISAM;

--
-- Dumping data for table `assistance_hr_deployments`
--


--
-- Table structure for table `assistance_partners`
--

CREATE TABLE assistance_partners (
  AssistanceId int(11) NOT NULL default '0',
  Partner int(11) NOT NULL default '0',
  PRIMARY KEY  (Partner,AssistanceId)
) TYPE=MyISAM;

--
-- Dumping data for table `assistance_partners`
--


--
-- Table structure for table `assistance_relief_disbursement`
--

CREATE TABLE assistance_relief_disbursement (
  AssistanceId int(11) NOT NULL default '0',
  ReliefDisbursementId int(11) NOT NULL default '0',
  PRIMARY KEY  (AssistanceId,ReliefDisbursementId)
) TYPE=MyISAM;

--
-- Dumping data for table `assistance_relief_disbursement`
--


--
-- Table structure for table `authorization_institutions`
--

CREATE TABLE authorization_institutions (
  AUTHORIZATION_INSTITUTION_CODE varchar(100) NOT NULL default '',
  AUTHORIZATION_INSTITUTION_NAME varchar(50) NOT NULL default '',
  PRIMARY KEY  (AUTHORIZATION_INSTITUTION_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `authorization_institutions`
--

INSERT INTO authorization_institutions VALUES ('2','Sri Lanka Police');
INSERT INTO authorization_institutions VALUES ('1','Goverment Agent');

--
-- Table structure for table `burial_site_detail`
--

CREATE TABLE burial_site_detail (
  burial_site_code int(10) NOT NULL auto_increment,
  province varchar(5) NOT NULL default '',
  district varchar(20) NOT NULL default '',
  division int(5) NOT NULL default '0',
  area varchar(200) NOT NULL default '',
  sitedescription varchar(200) NOT NULL default '',
  burialdetail varchar(200) default '',
  body_count_total int(5) unsigned default '0',
  body_count_men int(5) unsigned default '0',
  body_count_women int(5) default '0',
  body_count_children int(5) unsigned default '0',
  gps_lattitude varchar(20) default '',
  gps_longitude varchar(20) default '',
  authority_person_name varchar(100) NOT NULL default '',
  authority_name varchar(50) NOT NULL default '',
  authority_person_rank varchar(100) NOT NULL default '',
  authority_reference varchar(100) default '',
  PRIMARY KEY  (burial_site_code)
) TYPE=MyISAM;

--
-- Dumping data for table `burial_site_detail`
--

INSERT INTO burial_site_detail VALUES (8,'1','GMP',40,'1','aaasdda','3',235,0,0,0,'5','4','7','8','9','0');
INSERT INTO burial_site_detail VALUES (5,'1','CMB',1,'1','2','3',6,0,0,0,'5','4','7','8','9','0');
INSERT INTO burial_site_detail VALUES (6,'1','CMB',1,'sdad','adsad','adasd',222,0,0,0,'rwt','trt','qqeq','qeqweq','qeqwe','qewqe');
INSERT INTO burial_site_detail VALUES (7,'2','MAR',11,'polhena','near the coast','none',20,0,0,0,NULL,NULL,'Ajith','Police','constable','None');

--
-- Table structure for table `camp_history`
--

CREATE TABLE camp_history (
  CAMP_TOTAL int(5) NOT NULL default '0',
  HISTORY_ID int(10) NOT NULL auto_increment,
  CAMP_ID int(5) NOT NULL default '0',
  CAMP_MEN int(5) default '0',
  CAMP_WOMEN int(5) default '0',
  CAMP_CHILDREN int(5) default '0',
  CAMP_COMMENT varchar(255) default '',
  CAMP_FAMILY int(5) default '0',
  UPDATED_TIME time NOT NULL default '00:00:00',
  UPDATED_DATE date NOT NULL default '0000-00-00',
  PRIMARY KEY  (HISTORY_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `camp_history`
--

INSERT INTO camp_history VALUES (0,1,350,0,0,0,'',NULL,'00:20:05','2005-01-11');
INSERT INTO camp_history VALUES (20,2,350,0,0,0,'',NULL,'00:20:05','2005-01-11');
INSERT INTO camp_history VALUES (10,3,1,10,0,0,'',NULL,'00:20:05','2005-01-11');
INSERT INTO camp_history VALUES (100,4,1,100,0,0,'',NULL,'00:20:05','2005-01-11');
INSERT INTO camp_history VALUES (100,5,1,100,0,0,'',NULL,'00:20:05','2005-01-11');
INSERT INTO camp_history VALUES (100,6,1,100,0,0,'',NULL,'00:20:05','2005-01-12');

--
-- Table structure for table `camps_area`
--

CREATE TABLE camps_area (
  AREA_ID int(10) NOT NULL default '0',
  AREA_NAME varchar(50) NOT NULL default '',
  DIV_ID int(5) NOT NULL default '0',
  PRIMARY KEY  (AREA_ID),
  KEY DIV_ID (DIV_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `camps_area`
--

INSERT INTO camps_area VALUES (1,'Dehiwela',1);
INSERT INTO camps_area VALUES (2,'Thimbirigasya',2);
INSERT INTO camps_area VALUES (3,'Colombo',3);
INSERT INTO camps_area VALUES (4,'Moratuwa',4);
INSERT INTO camps_area VALUES (5,'Ratmalana',5);
INSERT INTO camps_area VALUES (6,'Kalutara',6);
INSERT INTO camps_area VALUES (7,'Panadura',7);
INSERT INTO camps_area VALUES (8,'Dodangoda',8);
INSERT INTO camps_area VALUES (9,'Bandaragama',9);
INSERT INTO camps_area VALUES (10,'Matugama',10);
INSERT INTO camps_area VALUES (11,'Matara',11);
INSERT INTO camps_area VALUES (12,'Malimbada',12);
INSERT INTO camps_area VALUES (13,'Thihagoda',13);
INSERT INTO camps_area VALUES (14,'Dickwella',14);
INSERT INTO camps_area VALUES (15,'Akuressa',15);
INSERT INTO camps_area VALUES (16,'Devinuwara',16);
INSERT INTO camps_area VALUES (17,'Athuraliya',17);
INSERT INTO camps_area VALUES (18,'Weligama',18);
INSERT INTO camps_area VALUES (19,'Welipitiya',19);
INSERT INTO camps_area VALUES (20,'Ampara',20);
INSERT INTO camps_area VALUES (21,'Uahana',21);
INSERT INTO camps_area VALUES (22,'Damana',22);
INSERT INTO camps_area VALUES (23,'Lahugala',23);
INSERT INTO camps_area VALUES (24,'Pothuvil',24);
INSERT INTO camps_area VALUES (25,'Addalachcheni',25);
INSERT INTO camps_area VALUES (26,'Akkaripattu',26);
INSERT INTO camps_area VALUES (27,'Aalaiadivermbu',27);
INSERT INTO camps_area VALUES (28,'Thirukovil',28);
INSERT INTO camps_area VALUES (29,'Navindanveli',29);
INSERT INTO camps_area VALUES (30,'Kalmunai',30);
INSERT INTO camps_area VALUES (31,'Ninthavur',31);
INSERT INTO camps_area VALUES (32,'Karaitivu',32);
INSERT INTO camps_area VALUES (33,'Sainthamaruthu',33);
INSERT INTO camps_area VALUES (34,'Sambanthuri',34);
INSERT INTO camps_area VALUES (35,'Eragama',35);
INSERT INTO camps_area VALUES (36,'Maritime Pattu',36);
INSERT INTO camps_area VALUES (37,'Oddusuddan',37);
INSERT INTO camps_area VALUES (38,'Puthukudiyiruppu',38);
INSERT INTO camps_area VALUES (39,'Negombo',39);
INSERT INTO camps_area VALUES (40,'Wattala',40);
INSERT INTO camps_area VALUES (41,'Habaraduwa',41);
INSERT INTO camps_area VALUES (42,'Ambalangoda',42);
INSERT INTO camps_area VALUES (43,'Hikkaduwa',43);
INSERT INTO camps_area VALUES (44,'Immaduwa',44);
INSERT INTO camps_area VALUES (45,'Akmeemana',45);
INSERT INTO camps_area VALUES (46,'Elpitiya',46);
INSERT INTO camps_area VALUES (47,'Weliweitiyadivitura',47);
INSERT INTO camps_area VALUES (48,'Karandeniya',48);
INSERT INTO camps_area VALUES (49,'Town and Gravets',49);
INSERT INTO camps_area VALUES (50,'Kuchcheveli',50);
INSERT INTO camps_area VALUES (51,'Kiniya',51);
INSERT INTO camps_area VALUES (52,'Muthur',52);
INSERT INTO camps_area VALUES (53,'Eachchilampththu',53);
INSERT INTO camps_area VALUES (54,'Thambalagamuwa',54);
INSERT INTO camps_area VALUES (55,'Vavuniya',55);
INSERT INTO camps_area VALUES (56,'Cheddikulam',56);

--
-- Table structure for table `camps_camp`
--

CREATE TABLE camps_camp (
  CAMP_FAMILY int(5) NOT NULL default '0',
  CAMP_ID int(5) NOT NULL auto_increment,
  AREA_NAME varchar(50) NOT NULL default '',
  DIV_ID int(5) NOT NULL default '0',
  DIST_CODE varchar(5) NOT NULL default '',
  PROV_CODE varchar(5) NOT NULL default '',
  CAMP_NAME varchar(50) NOT NULL default '',
  CAMP_ACCESABILITY varchar(255) default NULL,
  CAMP_MEN int(5) NOT NULL default '0',
  CAMP_WOMEN int(5) NOT NULL default '0',
  CAMP_CHILDREN int(5) NOT NULL default '0',
  CAMP_TOTAL int(11) default '0',
  CAMP_CAPABILITY varchar(255) default NULL,
  CAMP_CONTACT_PERSON varchar(100) default NULL,
  CAMP_CONTACT_NUMBER varchar(100) default NULL,
  LAST_UPDATE_DATE date NOT NULL default '0000-00-00',
  CAMP_COMMENT varchar(255) default NULL,
  LAST_UPDATE_TIME time NOT NULL default '00:00:00',
  PRIMARY KEY  (CAMP_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `camps_camp`
--

INSERT INTO camps_camp VALUES (0,1,'',1,'CMB','1','Subodharama Temple','this is a test accessibility',100,20,0,120,'fgfdg','','','2005-01-12','This is a test Comment,This is a test Comment\r\nThis is a test Comment, This is a test Comment\r\n','00:20:05');
INSERT INTO camps_camp VALUES (0,2,'',1,'CMB','1','Sri Mahabodhi Viharaya','',9,0,0,9,'','','','2005-01-10','fdgd','00:00:00');
INSERT INTO camps_camp VALUES (0,3,'',1,'CMB','1','St. Mary\'s College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,4,'',1,'CMB','1','Vidyananda Pirevina','',0,0,0,88,'','','','2005-01-10','70','00:00:00');
INSERT INTO camps_camp VALUES (0,5,'',1,'CMB','1','Tamil School, Dehiwela',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','280','00:00:00');
INSERT INTO camps_camp VALUES (0,6,'',1,'CMB','1','Avaramola Viharaya','',77,0,0,77,'','','','2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,7,'',2,'CMB','1','Marian Drive Private Building','',0,0,0,0,'','','','2005-01-27','120','00:20:05');
INSERT INTO camps_camp VALUES (0,8,'',2,'CMB','1','Bambalapitiya Railway Station',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,9,'',2,'CMB','1','Colpitiya Railway Station',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','70','00:00:00');
INSERT INTO camps_camp VALUES (0,10,'',3,'CMB','1','St. John\'s College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,11,'',3,'CMB','1','Rasik Fareed College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','460','00:00:00');
INSERT INTO camps_camp VALUES (0,12,'',3,'CMB','1','St. Maria College','',0,0,0,7777,'','','','2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,13,'',3,'CMB','1','Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,14,'',3,'CMB','1','St. Maria College, Social Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,15,'',3,'CMB','1','Farmel Convent',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,16,'',3,'CMB','1','St James Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','204','00:00:00');
INSERT INTO camps_camp VALUES (0,17,'',3,'CMB','1','St. John Church, St. House, St John College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,18,'',3,'CMB','1','Lunu Pokuna Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','125','00:00:00');
INSERT INTO camps_camp VALUES (0,19,'',3,'CMB','1','Dilasal Church','',0,0,0,888,'','','','2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,20,'',3,'CMB','1','Mutuwal Church, St. Mary College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','638','00:00:00');
INSERT INTO camps_camp VALUES (0,21,'',3,'CMB','1','Nazir Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','77','00:00:00');
INSERT INTO camps_camp VALUES (0,22,'',4,'CMB','1','Methodist Church, Moratumulla',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,23,'',4,'CMB','1','Baptist Church, Rawattawatta',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','42','00:00:00');
INSERT INTO camps_camp VALUES (0,24,'',4,'CMB','1','Palliyagodella Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,25,'',4,'CMB','1','Soysa College and Soysa Ramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,26,'',4,'CMB','1','Luxapathiya Sixadana Collge',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,27,'',4,'CMB','1','Lunawa Temple and Uyana Methodist Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','380','00:00:00');
INSERT INTO camps_camp VALUES (0,28,'',4,'CMB','1','Kadalana Roman Cathalic Church','',56,0,0,56,'','','','2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,29,'',4,'CMB','1','Indibedda Dharmarathna College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,30,'',4,'CMB','1','Puwakaramba High School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','275','00:00:00');
INSERT INTO camps_camp VALUES (0,31,'',4,'CMB','1','Rawatawatta Methodist College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,32,'',4,'CMB','1','Panadura Gangule Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,33,'',4,'CMB','1','Bekkegama Temple','',77,0,0,77,'','','','2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,34,'',4,'CMB','1','Mahanama College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,35,'',4,'CMB','1','St. Joseph College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,36,'',4,'CMB','1','St. Peter\'s Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','195','00:00:00');
INSERT INTO camps_camp VALUES (0,37,'',4,'CMB','1','Galkude Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,38,'',4,'CMB','1','Koralawella Gunawardhanarama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','329','00:00:00');
INSERT INTO camps_camp VALUES (0,39,'',5,'CMB','1','Roman Cathalic College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,40,'',5,'CMB','1','Christu Deva College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','900','00:00:00');
INSERT INTO camps_camp VALUES (0,41,'',5,'CMB','1','Kothalawalapura College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,42,'',5,'CMB','1','Jayawardhanaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,43,'',5,'CMB','1','Kavidhajaya College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','30','00:00:00');
INSERT INTO camps_camp VALUES (0,44,'',5,'CMB','1','Gnananda College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,45,'',5,'CMB','1','Shathrananda Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,46,'',5,'CMB','1','Subadharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1700','00:00:00');
INSERT INTO camps_camp VALUES (0,47,'',5,'CMB','1','Samudrassam Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','225','00:00:00');
INSERT INTO camps_camp VALUES (0,48,'',6,'KUL','1','Kandavivekaramaya Kalutara North',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,49,'',6,'KUL','1','Ethanmawala College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,50,'',6,'KUL','1','Julis Singho House',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,51,'',6,'KUL','1','Kumarikanda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,52,'',6,'KUL','1','Galassamekalaramaya','',0,0,0,66,'','','','2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,53,'',6,'KUL','1','Wijemanna Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,54,'',6,'KUL','1','Gnanandaramaya, Battamulla',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,55,'',6,'KUL','1','Pulinathalaramaya, Kalutara North',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,56,'',6,'KUL','1','Shandharshanaramaya, Nagoda',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','148','00:00:00');
INSERT INTO camps_camp VALUES (0,57,'',6,'KUL','1','Supermarket',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,58,'',6,'KUL','1','Welapura Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,59,'',6,'KUL','1','Near Seylana Bank',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,60,'',6,'KUL','1','Duwa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,61,'',6,'KUL','1','Kalarukkaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,62,'',6,'KUL','1','Purana Kanda Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,63,'',6,'KUL','1','Rajawatta Sama Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,64,'',6,'KUL','1','Pothupitiya College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,65,'',6,'KUL','1','Near Kattukurunda Roman Cathalic Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,66,'',6,'KUL','1','Sugatha Vimbaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,67,'',6,'KUL','1','Habaralagahalanda Praja Sala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,68,'',6,'KUL','1','Pohoddaramulla Mahigacharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,69,'',6,'KUL','1','No. of Non Camp',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','80','00:00:00');
INSERT INTO camps_camp VALUES (0,70,'',6,'KUL','1','Palathotha Tekkawatta Bikku Nikethanaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,71,'',7,'KUL','1','Galboda Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,72,'',7,'KUL','1','Walapala Saddarmodaya Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,73,'',7,'KUL','1','Walapala Ariya Rathnaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,74,'',7,'KUL','1','St. Johns College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2375','00:00:00');
INSERT INTO camps_camp VALUES (0,75,'',7,'KUL','1','Gagula Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','550','00:00:00');
INSERT INTO camps_camp VALUES (0,76,'',7,'KUL','1','Bekkegama Sunanada Ramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,77,'',7,'KUL','1','Daladawatta Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,78,'',7,'KUL','1','Vellikiriya Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','30','00:00:00');
INSERT INTO camps_camp VALUES (0,79,'',7,'KUL','1','Weragama College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,80,'',7,'KUL','1','Wijekumaranatunge Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,81,'',7,'KUL','1','Wadduwa St. Mary\'s College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,82,'',7,'KUL','1','Malamulla Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,83,'',7,'KUL','1','Bekkegama Junior College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','220','00:00:00');
INSERT INTO camps_camp VALUES (0,84,'',7,'KUL','1','Pilan Junior School, Pilan Maha Vidhayala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','230','00:00:00');
INSERT INTO camps_camp VALUES (0,85,'',7,'KUL','1','Sri Sarankaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,86,'',7,'KUL','1','Kuruppumulla Subhodharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,87,'',7,'KUL','1','Wadduwa Gangaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,88,'',7,'KUL','1','Amaramuni Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,89,'',7,'KUL','1','Melagama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,90,'',7,'KUL','1','Weragama Social Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,91,'',7,'KUL','1','Thanthirimulla Indraramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,92,'',7,'KUL','1','Kovilagodellai Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,93,'',7,'KUL','1','Tekkawatta Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,94,'',7,'KUL','1','Suwarnapunyaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,95,'',7,'KUL','1','Horethuduwa Gangaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','3000','00:00:00');
INSERT INTO camps_camp VALUES (0,96,'',7,'KUL','1','Palliyamulla Pre School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,97,'',7,'KUL','1','Punchideniya Grama Seveka 175, Gangulla Road',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,98,'',7,'KUL','1','Sri Siddharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,99,'',7,'KUL','1','Walana Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,100,'',7,'KUL','1','Rankotha Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,101,'',7,'KUL','1','Wadduwa Play Ground',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,102,'',7,'KUL','1','Elluwila Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,103,'',7,'KUL','1','Kanboddhi Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,104,'',7,'KUL','1','Nalluruwa Laksiri Florist',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','30','00:00:00');
INSERT INTO camps_camp VALUES (0,105,'',7,'KUL','1','Kanda Vihara, Gorakana',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','90','00:00:00');
INSERT INTO camps_camp VALUES (0,106,'',7,'KUL','1','Morawinna Sudhramaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,107,'',7,'KUL','1','Wattalpola Sudhramaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,108,'',7,'KUL','1','Malamulla Sripunnayawardhanaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','288','00:00:00');
INSERT INTO camps_camp VALUES (0,109,'',7,'KUL','1','Hirana Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','289','00:00:00');
INSERT INTO camps_camp VALUES (0,110,'',7,'KUL','1','Wadduwa Girl\'s School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','135','00:00:00');
INSERT INTO camps_camp VALUES (0,111,'',7,'KUL','1','Nallaruwa Abhinawaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,112,'',7,'KUL','1','Jaramirays Diyas College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,113,'',7,'KUL','1','Galweda Modera Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,114,'',7,'KUL','1','Leslly Gunawardena Mawatha',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,115,'',8,'KUL','1','Sri Subudhirajaramaya, Bombuwala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','351','00:00:00');
INSERT INTO camps_camp VALUES (0,116,'',8,'KUL','1','Sri Munindarama Maha Vihara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','109','00:00:00');
INSERT INTO camps_camp VALUES (0,117,'',8,'KUL','1','Miriswatta Maha Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','307','00:00:00');
INSERT INTO camps_camp VALUES (0,118,'',8,'KUL','1','Farm at 5th Mile Post, Bombuwala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','41','00:00:00');
INSERT INTO camps_camp VALUES (0,119,'',8,'KUL','1','House of Mr.Andradi Jayalath, Miripelawatta, Bombu',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','64','00:00:00');
INSERT INTO camps_camp VALUES (0,120,'',8,'KUL','1','House of Mrs. Chendrakanthi, PHM, Bombuwala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','26','00:00:00');
INSERT INTO camps_camp VALUES (0,121,'',8,'KUL','1','House of Mr. Wijesinghe, Dodangoda',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','41','00:00:00');
INSERT INTO camps_camp VALUES (0,122,'',9,'KUL','1','Alubomulla Central College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,123,'',9,'KUL','1','Wickramasheela Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','80','00:00:00');
INSERT INTO camps_camp VALUES (0,124,'',9,'KUL','1','Madupitiya Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,125,'',9,'KUL','1','Pathahawatta Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','54','00:00:00');
INSERT INTO camps_camp VALUES (0,126,'',9,'KUL','1','Pinwatta Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','22','00:00:00');
INSERT INTO camps_camp VALUES (0,127,'',9,'KUL','1','Waduramulla Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,128,'',9,'KUL','1','Pinwala Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','117','00:00:00');
INSERT INTO camps_camp VALUES (0,129,'',9,'KUL','1','Kolamadiriya Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,130,'',9,'KUL','1','Delegaswatta Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','8','00:00:00');
INSERT INTO camps_camp VALUES (0,131,'',9,'KUL','1','Newdawa Praja-Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','46','00:00:00');
INSERT INTO camps_camp VALUES (0,132,'',9,'KUL','1','Galthude Viharasthanaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','55','00:00:00');
INSERT INTO camps_camp VALUES (0,133,'',9,'KUL','1','Galthude Nivasa',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','35','00:00:00');
INSERT INTO camps_camp VALUES (0,134,'',10,'KUL','1','Matugama Church, Matugama Conference Hall, Mattuga',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,135,'',11,'MAR','2','Rahula College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1600','00:00:00');
INSERT INTO camps_camp VALUES (0,136,'',11,'MAR','2','Shariputhra Viduhala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,137,'',11,'MAR','2','Wewahamanduwa Wanigasekara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1200','00:00:00');
INSERT INTO camps_camp VALUES (0,138,'',11,'MAR','2','Madlha Weeratungaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,139,'',11,'MAR','2','Wijayathilakaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,140,'',11,'MAR','2','St. Thomas Girls College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,141,'',11,'MAR','2','Bodhirukkaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,142,'',11,'MAR','2','Kadeweediya Palliya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,143,'',11,'MAR','2','Dharul Ulum Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,144,'',11,'MAR','2','Weerabe Piriwena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,145,'',11,'MAR','2','Piladuwa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,146,'',11,'MAR','2','Kekanadura Neegrodharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,147,'',11,'MAR','2','Anwar Unus Housing Scheme',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','80','00:00:00');
INSERT INTO camps_camp VALUES (0,148,'',11,'MAR','2','Ilma Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','86','00:00:00');
INSERT INTO camps_camp VALUES (0,149,'',11,'MAR','2','Nilwala Kanishta Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','175','00:00:00');
INSERT INTO camps_camp VALUES (0,150,'',11,'MAR','2','Manamperi Building Up Stair',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','116','00:00:00');
INSERT INTO camps_camp VALUES (0,151,'',12,'MAR','2','Theijjawila Roya College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,152,'',12,'MAR','2','Horagoda Paliya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,153,'',12,'MAR','2','Kirimedmulla Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','46','00:00:00');
INSERT INTO camps_camp VALUES (0,154,'',13,'MAR','2','Platuwa Gunaratnana',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','115','00:00:00');
INSERT INTO camps_camp VALUES (0,155,'',14,'MAR','2','Godauda Vidiyalayae',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,156,'',14,'MAR','2','Kottagoda Sirisumana K.V',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,157,'',14,'MAR','2','Kemagoda Minikirula Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,158,'',14,'MAR','2','Galkance Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','285','00:00:00');
INSERT INTO camps_camp VALUES (0,159,'',15,'MAR','2','Poraba Mena Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','90','00:00:00');
INSERT INTO camps_camp VALUES (0,160,'',15,'MAR','2','Nimalawa Weralugahahena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','30','00:00:00');
INSERT INTO camps_camp VALUES (0,161,'',16,'MAR','2','Devinuwara Raja Maha Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','850','00:00:00');
INSERT INTO camps_camp VALUES (0,162,'',16,'MAR','2','Galgane Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,163,'',16,'MAR','2','Wajirawansha Mawatha Punchi Pansala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','220','00:00:00');
INSERT INTO camps_camp VALUES (0,164,'',16,'MAR','2','Gandara Maha Viduhala',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,165,'',16,'MAR','2','Samulu Building',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,166,'',16,'MAR','2','Galkalawita Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','203','00:00:00');
INSERT INTO camps_camp VALUES (0,167,'',17,'MAR','2','Wellnena Kanishta Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','83','00:00:00');
INSERT INTO camps_camp VALUES (0,168,'',17,'MAR','2','Athiraliya G.N Office',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','17','00:00:00');
INSERT INTO camps_camp VALUES (0,169,'',18,'MAR','2','Polwatta Kanishta Vidhyalya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,170,'',18,'MAR','2','Mirissa Sunadaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,171,'',18,'MAR','2','Weheragoda Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','370','00:00:00');
INSERT INTO camps_camp VALUES (0,172,'',18,'MAR','2','Loadstar Industries',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,173,'',18,'MAR','2','Dammala Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,174,'',18,'MAR','2','Aluthveediya Muslim Paliya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,175,'',18,'MAR','2','Anandagiri Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1235','00:00:00');
INSERT INTO camps_camp VALUES (0,176,'',18,'MAR','2','Siddartha Vidiyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,177,'',18,'MAR','2','Weheragala Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,178,'',18,'MAR','2','Polathumodara Neegrodaranaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,179,'',18,'MAR','2','Thalaramba Indrasara Vidyalya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,180,'',18,'MAR','2','Kamburugamuwa Dewagiri Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,181,'',18,'MAR','2','Bandaramulla Sudharashanaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,182,'',18,'MAR','2','Garanduwa Rathanathilakaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,183,'',18,'MAR','2','Kadolgalla Kanishta Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,184,'',18,'MAR','2','Udukawa Bodhirukkaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','20','00:00:00');
INSERT INTO camps_camp VALUES (0,185,'',18,'MAR','2','Kadolgalla Maha Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,186,'',18,'MAR','2','Denipitiya Maha Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,187,'',18,'MAR','2','Udukawa Charimount',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,188,'',18,'MAR','2','Agra Bodhi Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,189,'',18,'MAR','2','Gurubevila Naga Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,190,'',18,'MAR','2','Wekada Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,191,'',18,'MAR','2','Dewagiri Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','800','00:00:00');
INSERT INTO camps_camp VALUES (0,192,'',18,'MAR','2','Kamburugamuwa Godakanda Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','460','00:00:00');
INSERT INTO camps_camp VALUES (0,193,'',18,'MAR','2','Udupila Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,194,'',18,'MAR','2','Eduwawala Kanishta Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,195,'',18,'MAR','2','Individual houses 7 units',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','190','00:00:00');
INSERT INTO camps_camp VALUES (0,196,'',18,'MAR','2','Udukawa Bodhirukkaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','20','00:00:00');
INSERT INTO camps_camp VALUES (0,197,'',19,'MAR','2','Udukawa Kodolgalla Paliya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,198,'',19,'MAR','2','Welihida Poorwaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','800','00:00:00');
INSERT INTO camps_camp VALUES (0,199,'',19,'MAR','2','Welhida Karmantha Puraya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,200,'',19,'MAR','2','Udukawa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,201,'',19,'MAR','2','IIikpenna',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,202,'',19,'MAR','2','Kukulale Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,203,'',19,'MAR','2','Denipitiya Mahavidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1600','00:00:00');
INSERT INTO camps_camp VALUES (0,204,'',20,'AMP','5','D.S Senanayake School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','750','00:00:00');
INSERT INTO camps_camp VALUES (0,205,'',20,'AMP','5','Saddatissa Vidayalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1700','00:00:00');
INSERT INTO camps_camp VALUES (0,206,'',20,'AMP','5','Hegoda Siri Indrasara Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,207,'',20,'AMP','5','Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,208,'',20,'AMP','5','Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,209,'',20,'AMP','5','Mandala Maha Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,210,'',20,'AMP','5','D 34 Rest House',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,211,'',20,'AMP','5','Kavantissa School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,212,'',20,'AMP','5','Banadaranayake Girls School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,213,'',20,'AMP','5','Gamini School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','8','00:00:00');
INSERT INTO camps_camp VALUES (0,214,'',20,'AMP','5','Tamil School, Uahana Road',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,215,'',20,'AMP','5','Ampara Weaving School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','18','00:00:00');
INSERT INTO camps_camp VALUES (0,216,'',20,'AMP','5','Agrculture School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,217,'',20,'AMP','5','TYPEering Survey Office',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','92','00:00:00');
INSERT INTO camps_camp VALUES (0,218,'',20,'AMP','5','Viddyananda Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,219,'',21,'AMP','5','Samanalabadda','',0,0,0,234,'','','','2005-01-11','Coment','00:20:05');
INSERT INTO camps_camp VALUES (0,220,'',22,'AMP','5','Hingurana Uthara Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','130','00:00:00');
INSERT INTO camps_camp VALUES (0,221,'',22,'AMP','5','Manthotama School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','134','00:00:00');
INSERT INTO camps_camp VALUES (0,222,'',22,'AMP','5','Sambodhi Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','34','00:00:00');
INSERT INTO camps_camp VALUES (0,223,'',22,'AMP','5','Weheragala Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','280','00:00:00');
INSERT INTO camps_camp VALUES (0,224,'',22,'AMP','5','Hingurana Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','60','00:00:00');
INSERT INTO camps_camp VALUES (0,225,'',23,'AMP','5','Keriwehera Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','160','00:00:00');
INSERT INTO camps_camp VALUES (0,226,'',24,'AMP','5','Urani School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','7000','00:00:00');
INSERT INTO camps_camp VALUES (0,227,'',24,'AMP','5','Pothuvil Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','3000','00:00:00');
INSERT INTO camps_camp VALUES (0,228,'',24,'AMP','5','Sengamuwa School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','6500','00:00:00');
INSERT INTO camps_camp VALUES (0,229,'',24,'AMP','5','Komari Upper Division',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','3000','00:00:00');
INSERT INTO camps_camp VALUES (0,230,'',24,'AMP','5','Irtdra Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2500','00:00:00');
INSERT INTO camps_camp VALUES (0,231,'',25,'AMP','5','Teaching Training School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,232,'',25,'AMP','5','Al Arsha School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','762','00:00:00');
INSERT INTO camps_camp VALUES (0,233,'',25,'AMP','5','Addalachcheni National School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,234,'',25,'AMP','5','Al Munera School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','126','00:00:00');
INSERT INTO camps_camp VALUES (0,235,'',25,'AMP','5','Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','125','00:00:00');
INSERT INTO camps_camp VALUES (0,236,'',25,'AMP','5','Alamkulam Village',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','4000','00:00:00');
INSERT INTO camps_camp VALUES (0,237,'',25,'AMP','5','Sambu Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','800','00:00:00');
INSERT INTO camps_camp VALUES (0,238,'',25,'AMP','5','Palamunai Binhadji School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,239,'',25,'AMP','5','Al Hambra School - Oluvil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2050','00:00:00');
INSERT INTO camps_camp VALUES (0,240,'',25,'AMP','5','Tai Nagar Mosquel',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','120','00:00:00');
INSERT INTO camps_camp VALUES (0,241,'',25,'AMP','5','Mulativ Village',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','160','00:00:00');
INSERT INTO camps_camp VALUES (0,242,'',25,'AMP','5','Aalichcheni Village',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2500','00:00:00');
INSERT INTO camps_camp VALUES (0,243,'',25,'AMP','5','Addalachcheni 6 Village',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,244,'',25,'AMP','5','Addalachcheni 16 Village',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2400','00:00:00');
INSERT INTO camps_camp VALUES (0,245,'',26,'AMP','5','Aalim Nagar School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,246,'',26,'AMP','5','Al Rahimeeya School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','755','00:00:00');
INSERT INTO camps_camp VALUES (0,247,'',26,'AMP','5','Ampara Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,248,'',26,'AMP','5','Issankerni Seemi School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,249,'',26,'AMP','5','Ayisha Girls School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','3500','00:00:00');
INSERT INTO camps_camp VALUES (0,250,'',26,'AMP','5','Al Pashia School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,251,'',27,'AMP','5','Akkaripattu Ramkirishnan School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','8000','00:00:00');
INSERT INTO camps_camp VALUES (0,252,'',27,'AMP','5','RKM Mission',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,253,'',27,'AMP','5','Kanadupuram School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','8000','00:00:00');
INSERT INTO camps_camp VALUES (0,254,'',28,'AMP','5','Kanagarathnam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,255,'',28,'AMP','5','Thirukovil School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,256,'',28,'AMP','5','Sarasavi School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,257,'',28,'AMP','5','MM School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,258,'',28,'AMP','5','Kaliadivu School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,259,'',28,'AMP','5','Vinayakapuram School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,260,'',28,'AMP','5','Shakthi School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,261,'',28,'AMP','5','Sangaman Kanda Kovil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,262,'',28,'AMP','5','World Vision Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,263,'',28,'AMP','5','Kayathri Kovil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,264,'',29,'AMP','5','4th Coloni Kovil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,265,'',29,'AMP','5','Ranamadu Himaya School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,266,'',29,'AMP','5','15th Coloni Vivekananda School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','985','00:00:00');
INSERT INTO camps_camp VALUES (0,267,'',29,'AMP','5','Navindanveli Annamali School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','670','00:00:00');
INSERT INTO camps_camp VALUES (0,268,'',29,'AMP','5','Vavalakadi Saraswathi School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','130','00:00:00');
INSERT INTO camps_camp VALUES (0,269,'',29,'AMP','5','4th Coloni School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1100','00:00:00');
INSERT INTO camps_camp VALUES (0,270,'',29,'AMP','5','3rd Coloni School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','46','00:00:00');
INSERT INTO camps_camp VALUES (0,271,'',29,'AMP','5','19th Coloni School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,272,'',29,'AMP','5','5th Coloni Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','280','00:00:00');
INSERT INTO camps_camp VALUES (0,273,'',29,'AMP','5','Central Camp Muslim School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,274,'',29,'AMP','5','11th Coloni Tamil School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','230','00:00:00');
INSERT INTO camps_camp VALUES (0,275,'',29,'AMP','5','12th Coloni School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1050','00:00:00');
INSERT INTO camps_camp VALUES (0,276,'',29,'AMP','5','13th Coloni School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','70','00:00:00');
INSERT INTO camps_camp VALUES (0,277,'',30,'AMP','5','Vivekananda School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','550','00:00:00');
INSERT INTO camps_camp VALUES (0,278,'',30,'AMP','5','Senakuddiirrupu Ganesh School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','530','00:00:00');
INSERT INTO camps_camp VALUES (0,279,'',30,'AMP','5','Kamal Pathima School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2500','00:00:00');
INSERT INTO camps_camp VALUES (0,280,'',30,'AMP','5','Pandiriupu MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1800','00:00:00');
INSERT INTO camps_camp VALUES (0,281,'',30,'AMP','5','Periyaneelavani 01',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,282,'',30,'AMP','5','Kalmuni RKM School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','530','00:00:00');
INSERT INTO camps_camp VALUES (0,283,'',30,'AMP','5','Periyaneelavani 02',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','950','00:00:00');
INSERT INTO camps_camp VALUES (0,284,'',31,'AMP','5','Alumina School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1400','00:00:00');
INSERT INTO camps_camp VALUES (0,285,'',31,'AMP','5','Arufa School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','800','00:00:00');
INSERT INTO camps_camp VALUES (0,286,'',31,'AMP','5','Ivani Hashal School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,287,'',31,'AMP','5','Arabi School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1200','00:00:00');
INSERT INTO camps_camp VALUES (0,288,'',32,'AMP','5','Karaitivu 11 - Shanmugam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','5000','00:00:00');
INSERT INTO camps_camp VALUES (0,289,'',32,'AMP','5','Meera Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','800','00:00:00');
INSERT INTO camps_camp VALUES (0,290,'',32,'AMP','5','RKM Male School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,291,'',32,'AMP','5','Sabina School - Malliyakadu',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','3800','00:00:00');
INSERT INTO camps_camp VALUES (0,292,'',33,'AMP','5','Jumba Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','11343','00:00:00');
INSERT INTO camps_camp VALUES (0,293,'',33,'AMP','5','Al Kamaroon Schoo',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','4806','00:00:00');
INSERT INTO camps_camp VALUES (0,294,'',33,'AMP','5','Al Hiyal School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','4852','00:00:00');
INSERT INTO camps_camp VALUES (0,295,'',33,'AMP','5','Govt. Muslim Mixed School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','4339','00:00:00');
INSERT INTO camps_camp VALUES (0,296,'',34,'AMP','5','Malwatte Walathapitiya School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','125','00:00:00');
INSERT INTO camps_camp VALUES (0,297,'',34,'AMP','5','Malwatte Walathapitiya Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,298,'',34,'AMP','5','Malawatta Majupura Schhol & Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','260','00:00:00');
INSERT INTO camps_camp VALUES (0,299,'',34,'AMP','5','Malwatte Kanapathipuram Kovil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,300,'',34,'AMP','5','School near Malwatta Kovil',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','175','00:00:00');
INSERT INTO camps_camp VALUES (0,301,'',34,'AMP','5','New Mosque Poormanadiya Junction',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,302,'',34,'AMP','5','Samanthuri MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,303,'',34,'AMP','5','Al Muneer School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1300','00:00:00');
INSERT INTO camps_camp VALUES (0,304,'',34,'AMP','5','Al Mannar School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,305,'',34,'AMP','5','Saboor School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2500','00:00:00');
INSERT INTO camps_camp VALUES (0,306,'',34,'AMP','5','Veeramunai School Samanthuri',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2500','00:00:00');
INSERT INTO camps_camp VALUES (0,307,'',34,'AMP','5','Halal Jumbo Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,308,'',34,'AMP','5','Vipulananda School Malwatta',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,309,'',34,'AMP','5','Baihra School Sennalagrama',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,310,'',34,'AMP','5','Al Arsath School, Katu Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,311,'',34,'AMP','5','Dharusalam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,312,'',34,'AMP','5','Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,313,'',34,'AMP','5','Al Marijan School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1000','00:00:00');
INSERT INTO camps_camp VALUES (0,314,'',34,'AMP','5','Koraku School, Samanthuri',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,315,'',35,'AMP','5','Manigammadu Tamil School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','409','00:00:00');
INSERT INTO camps_camp VALUES (0,316,'',35,'AMP','5','Varipathchena Al Amin School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','381','00:00:00');
INSERT INTO camps_camp VALUES (0,317,'',35,'AMP','5','Eragama Ameer Alra School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','551','00:00:00');
INSERT INTO camps_camp VALUES (0,318,'',35,'AMP','5','Varipathchena Majijura School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','312','00:00:00');
INSERT INTO camps_camp VALUES (0,319,'',35,'AMP','5','Kuduvil Muslim School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','361','00:00:00');
INSERT INTO camps_camp VALUES (0,320,'',35,'AMP','5','Eragama Hospital',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','134','00:00:00');
INSERT INTO camps_camp VALUES (0,321,'',36,'MUL','9','Mulliyawalai Vidiyanantha School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,322,'',36,'MUL','9','Mulliyawalai RC School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,323,'',36,'MUL','9','Vattapalai School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,324,'',36,'MUL','9','Mulliyawalli Amil Vidiyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,325,'',36,'MUL','9','Kumulamunai School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,326,'',36,'MUL','9','Kokuthoduvai GTMS',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,327,'',36,'MUL','9','Thannerruttu CC School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,328,'',36,'MUL','9','Mulliyawallai Kalai Maha School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,329,'',36,'MUL','9','Multipurpose Hall, Murippu',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,330,'',37,'MUL','9','Oddusuddan M.V',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2200','00:00:00');
INSERT INTO camps_camp VALUES (0,331,'',38,'MUL','9','Puthukudiyiripu MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,332,'',38,'MUL','9','Eranaipalai MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,333,'',38,'MUL','9','Arasaratnam Vidiyalayam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,334,'',38,'MUL','9','Visvamadhu MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,335,'',38,'MUL','9','Suthanthirapuram GTM School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,336,'',38,'MUL','9','Vickneswara Vidiyalayam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,337,'',38,'MUL','9','Venavil GTMS',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,338,'',38,'MUL','9','Ganesa Vidiyalayam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,339,'',38,'MUL','9','Udayarkaddu MV',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','00','00:00:00');
INSERT INTO camps_camp VALUES (0,340,'',39,'GMP','1','Wellaveeediya Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,341,'',39,'GMP','1','Palangathuraya Don Bosco',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,342,'',39,'GMP','1','Palangathuraya Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','80','00:00:00');
INSERT INTO camps_camp VALUES (0,343,'',39,'GMP','1','Poruthota St. Sebastian Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,344,'',39,'GMP','1','Palangathurei Jees Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,345,'',39,'GMP','1','Dalupotha Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','20','00:00:00');
INSERT INTO camps_camp VALUES (0,346,'',40,'GMP','1','Kerawalpitiya Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','102','00:00:00');
INSERT INTO camps_camp VALUES (0,347,'',40,'GMP','1','Wattala Tamil School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','62','00:00:00');
INSERT INTO camps_camp VALUES (0,348,'',40,'GMP','1','St.Anna Primary School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,349,'',41,'GAL','2','Thittagala Ukgalwatta Temple','',0,0,0,200,'','','','2005-01-10','this is a test comment','00:20:05');
INSERT INTO camps_camp VALUES (0,350,'',41,'GAL','2','Gurullawalla Temple','',2,3,50,55,'','','','2005-01-11','Helllo There','00:20:05');
INSERT INTO camps_camp VALUES (0,351,'',41,'GAL','2','Meegahoda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,352,'',41,'GAL','2','Ahangam Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,353,'',41,'GAL','2','Harumalagoda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','229','00:00:00');
INSERT INTO camps_camp VALUES (0,354,'',41,'GAL','2','Unawatuna Gangahena Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','129','00:00:00');
INSERT INTO camps_camp VALUES (0,355,'',41,'GAL','2','Unawatuna Bonavista College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','30','00:00:00');
INSERT INTO camps_camp VALUES (0,356,'',41,'GAL','2','Kataluwa Maha Vidyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,357,'',41,'GAL','2','Koggala Muchalindaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','226','00:00:00');
INSERT INTO camps_camp VALUES (0,358,'',41,'GAL','2','Kataluwa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,359,'',41,'GAL','2','Kalahe Sumangalodaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,360,'',41,'GAL','2','Bodhiraja Temple, Unawatuna',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','331','00:00:00');
INSERT INTO camps_camp VALUES (0,361,'',41,'GAL','2','Galkettiya Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','103','00:00:00');
INSERT INTO camps_camp VALUES (0,362,'',41,'GAL','2','Tanahena Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','29','00:00:00');
INSERT INTO camps_camp VALUES (0,363,'',41,'GAL','2','Peellagoda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','156','00:00:00');
INSERT INTO camps_camp VALUES (0,364,'',41,'GAL','2','Wellathota Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1005','00:00:00');
INSERT INTO camps_camp VALUES (0,365,'',41,'GAL','2','Kahawennagama Maakandugoda Nigoradharamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1500','00:00:00');
INSERT INTO camps_camp VALUES (0,366,'',41,'GAL','2','Lanumodara Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','215','00:00:00');
INSERT INTO camps_camp VALUES (0,367,'',41,'GAL','2','Mooderagama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,368,'',41,'GAL','2','Yatagala Rajamaha Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','193','00:00:00');
INSERT INTO camps_camp VALUES (0,369,'',41,'GAL','2','Liyanagoda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','806','00:00:00');
INSERT INTO camps_camp VALUES (0,370,'',41,'GAL','2','Mihiripana Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','206','00:00:00');
INSERT INTO camps_camp VALUES (0,371,'',42,'GAL','2','Battapola Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1600','00:00:00');
INSERT INTO camps_camp VALUES (0,372,'',42,'GAL','2','Battapola Maha Vidhyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,373,'',42,'GAL','2','Kahatapitiya Praja Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,374,'',42,'GAL','2','Kirellagahawella Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,375,'',42,'GAL','2','Nindana Maha Vidhyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,376,'',42,'GAL','2','Nindana Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,377,'',42,'GAL','2','Apegama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,378,'',42,'GAL','2','Aluthwela Nandaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,379,'',42,'GAL','2','Yakatuwa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,380,'',42,'GAL','2','Battuwanhena College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,381,'',42,'GAL','2','Aluthwella Maha Vidhyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,382,'',42,'GAL','2','Kaluwadumulla Private House',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','35','00:00:00');
INSERT INTO camps_camp VALUES (0,383,'',43,'GAL','2','Dodanduwa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','325','00:00:00');
INSERT INTO camps_camp VALUES (0,384,'',43,'GAL','2','Pitiwella Jayawardenaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,385,'',43,'GAL','2','Kalupe Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,386,'',43,'GAL','2','Jayanthi Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,387,'',43,'GAL','2','Eluwila Kanda Malwenna Pushparamaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1128','00:00:00');
INSERT INTO camps_camp VALUES (0,388,'',43,'GAL','2','Hikkaduwa Jannandaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,389,'',43,'GAL','2','Thalagasdeniya Gangaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,390,'',43,'GAL','2','Sri Sumangala Vidiyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,391,'',43,'GAL','2','Seenigama Kusumarama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,392,'',43,'GAL','2','Thotagama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,393,'',43,'GAL','2','Dodanduwa Morakola Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','750','00:00:00');
INSERT INTO camps_camp VALUES (0,394,'',43,'GAL','2','Kumarakanda Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,395,'',43,'GAL','2','Rathna Udagama Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,396,'',43,'GAL','2','Bussa Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,397,'',43,'GAL','2','Galduwa Aranya Senasanaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,398,'',43,'GAL','2','Kiralagahawela College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,399,'',43,'GAL','2','Kekillamandiya Sumanaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,400,'',43,'GAL','2','Narigama Shailaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,401,'',43,'GAL','2','Galagoda College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','975','00:00:00');
INSERT INTO camps_camp VALUES (0,402,'',43,'GAL','2','Aluthwala Nandaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2000','00:00:00');
INSERT INTO camps_camp VALUES (0,403,'',43,'GAL','2','Aluthwala Maha Vikaraya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','500','00:00:00');
INSERT INTO camps_camp VALUES (0,404,'',44,'GAL','2','Gurullawala Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,405,'',44,'GAL','2','Ugallwala Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1200','00:00:00');
INSERT INTO camps_camp VALUES (0,406,'',44,'GAL','2','Angulugaha Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,407,'',44,'GAL','2','Paragoda Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,408,'',44,'GAL','2','Immaduwa Junior School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,409,'',45,'GAL','2','Haliwala Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,410,'',45,'GAL','2','Kalahe Sumangala College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,411,'',45,'GAL','2','Yattagala Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,412,'',45,'GAL','2','Anangoda Sudharshanaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','100','00:00:00');
INSERT INTO camps_camp VALUES (0,413,'',45,'GAL','2','Manavilla Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,414,'',45,'GAL','2','Akmeeman DS Office',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','50','00:00:00');
INSERT INTO camps_camp VALUES (0,415,'',45,'GAL','2','Dalupotha Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,416,'',45,'GAL','2','Yattagala Rajamaha Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,417,'',46,'GAL','2','Viharamahadevi Pirivena',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','140','00:00:00');
INSERT INTO camps_camp VALUES (0,418,'',46,'GAL','2','Vissuddharama Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','91','00:00:00');
INSERT INTO camps_camp VALUES (0,419,'',46,'GAL','2','Sudharmarama Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','89','00:00:00');
INSERT INTO camps_camp VALUES (0,420,'',46,'GAL','2','Indipelagoda Vissuddharama Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','40','00:00:00');
INSERT INTO camps_camp VALUES (0,421,'',46,'GAL','2','Bodhirajarama Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,422,'',46,'GAL','2','Pittuwala Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','15','00:00:00');
INSERT INTO camps_camp VALUES (0,423,'',46,'GAL','2','Pahalaommatta Home',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','32','00:00:00');
INSERT INTO camps_camp VALUES (0,424,'',46,'GAL','2','Palendagoda Home',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','23','00:00:00');
INSERT INTO camps_camp VALUES (0,425,'',47,'GAL','2','Ethkandura Seevali Maha Vidiyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','335','00:00:00');
INSERT INTO camps_camp VALUES (0,426,'',47,'GAL','2','Ampegama Maha Vidiyalaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','196','00:00:00');
INSERT INTO camps_camp VALUES (0,427,'',48,'GAL','2','Uragaha Boddhimalu Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','25','00:00:00');
INSERT INTO camps_camp VALUES (0,428,'',48,'GAL','2','Uragaha Siri Seelarathnaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,429,'',48,'GAL','2','Yattagala Boddhirajaramaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','600','00:00:00');
INSERT INTO camps_camp VALUES (0,430,'',48,'GAL','2','Halgangawella Temple',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','46','00:00:00');
INSERT INTO camps_camp VALUES (0,431,'',48,'GAL','2','Hippankanda Cultural Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','148','00:00:00');
INSERT INTO camps_camp VALUES (0,432,'',48,'GAL','2','Galagoda Viharaya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','300','00:00:00');
INSERT INTO camps_camp VALUES (0,433,'',48,'GAL','2','Kirimettiyawa Public Hall',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','41','00:00:00');
INSERT INTO camps_camp VALUES (0,434,'',48,'GAL','2','Jayabima Aranya Senasana',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,435,'',49,'TRIN','5','Jamaliya Community centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','400','00:00:00');
INSERT INTO camps_camp VALUES (0,436,'',49,'TRIN','5','Poompugar Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','382','00:00:00');
INSERT INTO camps_camp VALUES (0,437,'',49,'TRIN','5','Selvanayagapuram',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','4454','00:00:00');
INSERT INTO camps_camp VALUES (0,438,'',49,'TRIN','5','Abayapura School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','5000','00:00:00');
INSERT INTO camps_camp VALUES (0,439,'',49,'TRIN','5','Kalaimahal School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','900','00:00:00');
INSERT INTO camps_camp VALUES (0,440,'',49,'TRIN','5','Anu. Junction Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','75','00:00:00');
INSERT INTO camps_camp VALUES (0,441,'',49,'TRIN','5','China Bay',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1962','00:00:00');
INSERT INTO camps_camp VALUES (0,442,'',49,'TRIN','5','Pattanatheru',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','322','00:00:00');
INSERT INTO camps_camp VALUES (0,443,'',49,'TRIN','5','Manaiyaveli',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2882','00:00:00');
INSERT INTO camps_camp VALUES (0,444,'',49,'TRIN','5','Orr\'s Hill Virikananda Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1170','00:00:00');
INSERT INTO camps_camp VALUES (0,445,'',49,'TRIN','5','Thirukadaloor',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','','00:00:00');
INSERT INTO camps_camp VALUES (0,446,'',49,'TRIN','5','Kavathikudah',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','667','00:00:00');
INSERT INTO camps_camp VALUES (0,447,'',49,'TRIN','5','Vilundy',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','848','00:00:00');
INSERT INTO camps_camp VALUES (0,448,'',49,'TRIN','5','Lingangar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1375','00:00:00');
INSERT INTO camps_camp VALUES (0,449,'',49,'TRIN','5','Sambalthivu & Salli',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2808','00:00:00');
INSERT INTO camps_camp VALUES (0,450,'',49,'TRIN','5','Varothayanagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,451,'',49,'TRIN','5','Singapura',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','61','00:00:00');
INSERT INTO camps_camp VALUES (0,452,'',49,'TRIN','5','Madcove',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','517','00:00:00');
INSERT INTO camps_camp VALUES (0,453,'',50,'TRIN','5','Irakkakandy Al Humra',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','2200','00:00:00');
INSERT INTO camps_camp VALUES (0,454,'',50,'TRIN','5','Kumburupiddy School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','873','00:00:00');
INSERT INTO camps_camp VALUES (0,455,'',50,'TRIN','5','Kuchchaweli M.V.',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','890','00:00:00');
INSERT INTO camps_camp VALUES (0,456,'',50,'TRIN','5','Iranikeru School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','480','00:00:00');
INSERT INTO camps_camp VALUES (0,457,'',50,'TRIN','5','Al Nooriya Vid',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','70','00:00:00');
INSERT INTO camps_camp VALUES (0,458,'',50,'TRIN','5','Narasingsmalai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,459,'',50,'TRIN','5','Periyakulam Vid',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','512','00:00:00');
INSERT INTO camps_camp VALUES (0,460,'',50,'TRIN','5','Igbal Nagar Community Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','440','00:00:00');
INSERT INTO camps_camp VALUES (0,461,'',50,'TRIN','5','Adampodai Malai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1445','00:00:00');
INSERT INTO camps_camp VALUES (0,462,'',50,'TRIN','5','Nilaweli Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1800','00:00:00');
INSERT INTO camps_camp VALUES (0,463,'',50,'TRIN','5','Nilaweli RC Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','496','00:00:00');
INSERT INTO camps_camp VALUES (0,464,'',50,'TRIN','5','Gopalapuram Mosque',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1800','00:00:00');
INSERT INTO camps_camp VALUES (0,465,'',50,'TRIN','5','Gopalapuram School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1270','00:00:00');
INSERT INTO camps_camp VALUES (0,466,'',50,'TRIN','5','Valayoothu Community Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','532','00:00:00');
INSERT INTO camps_camp VALUES (0,467,'',50,'TRIN','5','Thiriyai M.V.',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','740','00:00:00');
INSERT INTO camps_camp VALUES (0,468,'',50,'TRIN','5','Pulmoddai M.V.',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','85','00:00:00');
INSERT INTO camps_camp VALUES (0,469,'',50,'TRIN','5','Nilaweli Maha Vid',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1200','00:00:00');
INSERT INTO camps_camp VALUES (0,470,'',50,'TRIN','5','Nilaweli Methadist Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','45','00:00:00');
INSERT INTO camps_camp VALUES (0,471,'',50,'TRIN','5','Valayoothu Petrol Shed',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','643','00:00:00');
INSERT INTO camps_camp VALUES (0,472,'',51,'TRIN','5','Faizal Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1013','00:00:00');
INSERT INTO camps_camp VALUES (0,473,'',51,'TRIN','5','Ahamainagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','991','00:00:00');
INSERT INTO camps_camp VALUES (0,474,'',51,'TRIN','5','Mancho',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1016','00:00:00');
INSERT INTO camps_camp VALUES (0,475,'',51,'TRIN','5','Mancholai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','595','00:00:00');
INSERT INTO camps_camp VALUES (0,476,'',51,'TRIN','5','Rahumiyanagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','525','00:00:00');
INSERT INTO camps_camp VALUES (0,477,'',51,'TRIN','5','Sungankulai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','521','00:00:00');
INSERT INTO camps_camp VALUES (0,478,'',51,'TRIN','5','Kathai Arru',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','302','00:00:00');
INSERT INTO camps_camp VALUES (0,479,'',51,'TRIN','5','Perriyakiniya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','436','00:00:00');
INSERT INTO camps_camp VALUES (0,480,'',51,'TRIN','5','Malindurai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','436','00:00:00');
INSERT INTO camps_camp VALUES (0,481,'',51,'TRIN','5','Mahruf Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','729','00:00:00');
INSERT INTO camps_camp VALUES (0,482,'',52,'TRIN','5','Thaqua Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','700','00:00:00');
INSERT INTO camps_camp VALUES (0,483,'',52,'TRIN','5','Naduthivu',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','525','00:00:00');
INSERT INTO camps_camp VALUES (0,484,'',52,'TRIN','5','Palanagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','450','00:00:00');
INSERT INTO camps_camp VALUES (0,485,'',52,'TRIN','5','Thaha Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','360','00:00:00');
INSERT INTO camps_camp VALUES (0,486,'',52,'TRIN','5','Muthur East',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','735','00:00:00');
INSERT INTO camps_camp VALUES (0,487,'',52,'TRIN','5','Annaichchenai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','200','00:00:00');
INSERT INTO camps_camp VALUES (0,488,'',52,'TRIN','5','Shafinagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','115','00:00:00');
INSERT INTO camps_camp VALUES (0,489,'',52,'TRIN','5','Periyapalam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','85','00:00:00');
INSERT INTO camps_camp VALUES (0,490,'',52,'TRIN','5','Jinnahnagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','135','00:00:00');
INSERT INTO camps_camp VALUES (0,491,'',52,'TRIN','5','Periyapalam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','85','00:00:00');
INSERT INTO camps_camp VALUES (0,492,'',52,'TRIN','5','Jinnahnagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','135','00:00:00');
INSERT INTO camps_camp VALUES (0,493,'',52,'TRIN','5','Alim Nagar (Part)',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','125','00:00:00');
INSERT INTO camps_camp VALUES (0,494,'',52,'TRIN','5','Ralkuli',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','210','00:00:00');
INSERT INTO camps_camp VALUES (0,495,'',52,'TRIN','5','Kaddaikarachenai',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','530','00:00:00');
INSERT INTO camps_camp VALUES (0,496,'',52,'TRIN','5','Sampoor',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','330','00:00:00');
INSERT INTO camps_camp VALUES (0,497,'',52,'TRIN','5','Kuniththevu',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','180','00:00:00');
INSERT INTO camps_camp VALUES (0,498,'',52,'TRIN','5','Navaratnapuram',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','115','00:00:00');
INSERT INTO camps_camp VALUES (0,499,'',52,'TRIN','5','Naloor',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','250','00:00:00');
INSERT INTO camps_camp VALUES (0,500,'',52,'TRIN','5','Patalaipuram Veeramanagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','175','00:00:00');
INSERT INTO camps_camp VALUES (0,501,'',52,'TRIN','5','Uppurai Seenanveli',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,502,'',52,'TRIN','5','Jaya Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','475','00:00:00');
INSERT INTO camps_camp VALUES (0,503,'',52,'TRIN','5','Neithai Nagar',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','350','00:00:00');
INSERT INTO camps_camp VALUES (0,504,'',53,'TRIN','5','Eachchilampththu M.V.',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','565','00:00:00');
INSERT INTO camps_camp VALUES (0,505,'',53,'TRIN','5','Poonagar Thiruvalluvar MV, Poomarathadichenai Scho',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','544','00:00:00');
INSERT INTO camps_camp VALUES (0,506,'',53,'TRIN','5','Mavadichenai GTMS, Malaiveethi Amman Temble',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','322','00:00:00');
INSERT INTO camps_camp VALUES (0,507,'',52,'TRIN','5','Adhi Koneshwara',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','212','00:00:00');
INSERT INTO camps_camp VALUES (0,508,'',52,'TRIN','5','Almadins',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','240','00:00:00');
INSERT INTO camps_camp VALUES (0,509,'',52,'TRIN','5','Sraj Nagar V',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','825','00:00:00');
INSERT INTO camps_camp VALUES (0,510,'',52,'TRIN','5','Al Hijira V',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','150','00:00:00');
INSERT INTO camps_camp VALUES (0,511,'',52,'TRIN','5','Meera Nagar S',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','160','00:00:00');
INSERT INTO camps_camp VALUES (0,512,'',55,'VAV','9','Vavuniya Tamil Maha Vidyalayam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','239','00:00:00');
INSERT INTO camps_camp VALUES (0,513,'',55,'VAV','9','Saivapiragasa Ladies College',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','237','00:00:00');
INSERT INTO camps_camp VALUES (0,514,'',55,'VAV','9','Poonthoddam Welfare Centre',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','98','00:00:00');
INSERT INTO camps_camp VALUES (0,515,'',55,'VAV','9','St. Antony\'s Church Rambaikulam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','265','00:00:00');
INSERT INTO camps_camp VALUES (0,516,'',55,'VAV','9','Paddanichoorpuliyankulam Muslim Maha Vidyalayam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','1249','00:00:00');
INSERT INTO camps_camp VALUES (0,517,'',55,'VAV','9','Ganeshapuram Vavuniya',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','19','00:00:00');
INSERT INTO camps_camp VALUES (0,518,'',56,'VAV','9','With F&R',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','252','00:00:00');
INSERT INTO camps_camp VALUES (0,519,'',56,'VAV','9','Mankulam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','303','00:00:00');
INSERT INTO camps_camp VALUES (0,520,'',56,'VAV','9','Iluppaikulam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','175','00:00:00');
INSERT INTO camps_camp VALUES (0,521,'',56,'VAV','9','Mudaliyarkulam School',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','64','00:00:00');
INSERT INTO camps_camp VALUES (0,522,'',56,'VAV','9','Periyakaddu Church',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','5','00:00:00');
INSERT INTO camps_camp VALUES (0,523,'',56,'VAV','9','Adappankulam',NULL,0,0,0,0,NULL,NULL,NULL,'2005-01-10','38','00:00:00');
INSERT INTO camps_camp VALUES (0,548,'Colombo',1,'CMB','1','Camp No 1','None',45,0,0,45,'None','Jaliya','111111','2005-01-10','None','00:00:00');
INSERT INTO camps_camp VALUES (0,563,'asdaa',1,'CMB','1','sdasdad','adas',0,0,0,22,'asdsad','adsas','adas','2005-01-25','adada','00:20:05');
INSERT INTO camps_camp VALUES (0,564,'xZ',4,'CMB','1','xZxzx','zxzx',0,0,0,22,'xZX','Zxx','z','2005-01-24','XZ','00:20:05');
INSERT INTO camps_camp VALUES (0,565,'xZ',4,'CMB','1','xZxzx','zxzx',0,0,0,300,'xZX','Zxx','z','2005-01-24','XZ','00:20:05');
INSERT INTO camps_camp VALUES (212,566,'2121',5,'CMB','1','1211','212',0,0,0,111,'1212','212','212','2005-01-25','212121','00:20:05');

--
-- Table structure for table `camps_district`
--

CREATE TABLE camps_district (
  DIST_CODE varchar(5) NOT NULL default '',
  DIST_NAME varchar(50) NOT NULL default '',
  PROV_CODE varchar(5) NOT NULL default '',
  PRIMARY KEY  (DIST_CODE),
  KEY PROV_CODE (PROV_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `camps_district`
--

INSERT INTO camps_district VALUES ('AMP','Ampara','5');
INSERT INTO camps_district VALUES ('ANU','Anuradhapura','8');
INSERT INTO camps_district VALUES ('BAD','Badulla','4');
INSERT INTO camps_district VALUES ('BAT','Batticaloa','5');
INSERT INTO camps_district VALUES ('CMB','Colombo','1');
INSERT INTO camps_district VALUES ('GAL','Galle','2');
INSERT INTO camps_district VALUES ('GMP','Gampaha','1');
INSERT INTO camps_district VALUES ('HAM','Hambantota','2');
INSERT INTO camps_district VALUES ('JAF','Jaffna','9');
INSERT INTO camps_district VALUES ('KAN','Kandy','6');
INSERT INTO camps_district VALUES ('KEG','Kegalle','3');
INSERT INTO camps_district VALUES ('KILL','Kilinochchi','9');
INSERT INTO camps_district VALUES ('KUL','Kalutara','1');
INSERT INTO camps_district VALUES ('KUR','Kurunegala','7');
INSERT INTO camps_district VALUES ('MAN','Mannar','9');
INSERT INTO camps_district VALUES ('MAR','Matara','2');
INSERT INTO camps_district VALUES ('MAT','Matale','6');
INSERT INTO camps_district VALUES ('MON','Monaragala','4');
INSERT INTO camps_district VALUES ('MUL','Mullaitivu','9');
INSERT INTO camps_district VALUES ('NUR','Nuwara Eliya','6');
INSERT INTO camps_district VALUES ('POL','Polonnaruwa','8');
INSERT INTO camps_district VALUES ('PUT','Puttalam','7');
INSERT INTO camps_district VALUES ('RAT','Ratnapura','3');
INSERT INTO camps_district VALUES ('TRIN','Trincomalee','5');
INSERT INTO camps_district VALUES ('VAV','Vavuniya','9');

--
-- Table structure for table `camps_division`
--

CREATE TABLE camps_division (
  DIV_ID int(5) NOT NULL default '0',
  DIV_NAME varchar(50) NOT NULL default '',
  DIST_CODE varchar(5) NOT NULL default '',
  PRIMARY KEY  (DIV_ID),
  KEY DIST_CODE (DIST_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `camps_division`
--

INSERT INTO camps_division VALUES (1,'Dehiwela','CMB');
INSERT INTO camps_division VALUES (2,'Thimbirigasya','CMB');
INSERT INTO camps_division VALUES (3,'Colombo','CMB');
INSERT INTO camps_division VALUES (4,'Moratuwa','CMB');
INSERT INTO camps_division VALUES (5,'Ratmalana','CMB');
INSERT INTO camps_division VALUES (6,'Kalutara','KUL');
INSERT INTO camps_division VALUES (7,'Panadura','KUL');
INSERT INTO camps_division VALUES (8,'Dodangoda','KUL');
INSERT INTO camps_division VALUES (9,'Bandaragama','KUL');
INSERT INTO camps_division VALUES (10,'Matugama','KUL');
INSERT INTO camps_division VALUES (11,'Matara','MAR');
INSERT INTO camps_division VALUES (12,'Malimbada','MAR');
INSERT INTO camps_division VALUES (13,'Thihagoda','MAR');
INSERT INTO camps_division VALUES (14,'Dickwella','MAR');
INSERT INTO camps_division VALUES (15,'Akuressa','MAR');
INSERT INTO camps_division VALUES (16,'Devinuwara','MAR');
INSERT INTO camps_division VALUES (17,'Athuraliya','MAR');
INSERT INTO camps_division VALUES (18,'Weligama','MAR');
INSERT INTO camps_division VALUES (19,'Welipitiya','MAR');
INSERT INTO camps_division VALUES (20,'Ampara','AMP');
INSERT INTO camps_division VALUES (21,'Uahana','AMP');
INSERT INTO camps_division VALUES (22,'Damana','AMP');
INSERT INTO camps_division VALUES (23,'Lahugala','AMP');
INSERT INTO camps_division VALUES (24,'Pothuvil','AMP');
INSERT INTO camps_division VALUES (25,'Addalachcheni','AMP');
INSERT INTO camps_division VALUES (26,'Akkaripattu','AMP');
INSERT INTO camps_division VALUES (27,'Aalaiadivermbu','AMP');
INSERT INTO camps_division VALUES (28,'Thirukovil','AMP');
INSERT INTO camps_division VALUES (29,'Navindanveli','AMP');
INSERT INTO camps_division VALUES (30,'Kalmunai','AMP');
INSERT INTO camps_division VALUES (31,'Ninthavur','AMP');
INSERT INTO camps_division VALUES (32,'Karaitivu','AMP');
INSERT INTO camps_division VALUES (33,'Sainthamaruthu','AMP');
INSERT INTO camps_division VALUES (34,'Sambanthuri','AMP');
INSERT INTO camps_division VALUES (35,'Eragama','AMP');
INSERT INTO camps_division VALUES (36,'Maritime Pattu','MUL');
INSERT INTO camps_division VALUES (37,'Oddusuddan','MUL');
INSERT INTO camps_division VALUES (38,'Puthukudiyiruppu','MUL');
INSERT INTO camps_division VALUES (39,'Negombo','GMP');
INSERT INTO camps_division VALUES (40,'Wattala','GMP');
INSERT INTO camps_division VALUES (41,'Habaraduwa','GAL');
INSERT INTO camps_division VALUES (42,'Ambalangoda','GAL');
INSERT INTO camps_division VALUES (43,'Hikkaduwa','GAL');
INSERT INTO camps_division VALUES (44,'Immaduwa','GAL');
INSERT INTO camps_division VALUES (45,'Akmeemana','GAL');
INSERT INTO camps_division VALUES (46,'Elpitiya','GAL');
INSERT INTO camps_division VALUES (47,'Weliweitiyadivitura','GAL');
INSERT INTO camps_division VALUES (48,'Karandeniya','GAL');
INSERT INTO camps_division VALUES (49,'Town and Gravets','TRIN');
INSERT INTO camps_division VALUES (50,'Kuchcheveli','TRIN');
INSERT INTO camps_division VALUES (51,'Kiniya','TRIN');
INSERT INTO camps_division VALUES (52,'Muthur','TRIN');
INSERT INTO camps_division VALUES (53,'Eachchilampththu','TRIN');
INSERT INTO camps_division VALUES (54,'Thambalagamuwa','TRIN');
INSERT INTO camps_division VALUES (55,'Vavuniya','VAV');
INSERT INTO camps_division VALUES (56,'Cheddikulam','VAV');

--
-- Table structure for table `camps_province`
--

CREATE TABLE camps_province (
  PROV_CODE varchar(5) NOT NULL default '',
  PROV_NAME varchar(50) NOT NULL default '',
  PRIMARY KEY  (PROV_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `camps_province`
--

INSERT INTO camps_province VALUES ('1','Western Province');
INSERT INTO camps_province VALUES ('2','Southern Province');
INSERT INTO camps_province VALUES ('3','Sabaragamuwa Province');
INSERT INTO camps_province VALUES ('4','Uva Province');
INSERT INTO camps_province VALUES ('5','Eastern Province');
INSERT INTO camps_province VALUES ('6','Central Province');
INSERT INTO camps_province VALUES ('7','North-Western Province');
INSERT INTO camps_province VALUES ('8','North-Central Province');
INSERT INTO camps_province VALUES ('9','Northern Province');

--
-- Table structure for table `category`
--

CREATE TABLE category (
  CatCode varchar(20) NOT NULL default '',
  CatDescription varchar(50) NOT NULL default '',
  PRIMARY KEY  (CatCode)
) TYPE=MyISAM;

--
-- Dumping data for table `category`
--

INSERT INTO category VALUES ('1','Dry Rations');
INSERT INTO category VALUES ('2','Milk Food');
INSERT INTO category VALUES ('3','Infant Food');
INSERT INTO category VALUES ('4','Water and Sanitation');
INSERT INTO category VALUES ('5','Tents');
INSERT INTO category VALUES ('6','Clothing');
INSERT INTO category VALUES ('7','Bedding');
INSERT INTO category VALUES ('8','Medical Goods');
INSERT INTO category VALUES ('9','Medical Services');
INSERT INTO category VALUES ('10','Volunteers');
INSERT INTO category VALUES ('11','Other Goods');
INSERT INTO category VALUES ('12','Other Services');
INSERT INTO category VALUES ('13','Transport');
INSERT INTO category VALUES ('14','Construction Material');
INSERT INTO category VALUES ('15','Construction Services');

--
-- Table structure for table `damage_affected_person`
--

CREATE TABLE damage_affected_person (
  PERSION_ID int(11) NOT NULL auto_increment,
  CASE_ID int(11) default '0',
  PROPERTY_ID int(11) default '0',
  NIC_NO varchar(50) default '',
  NAME varchar(100) default '',
  PHONE_NO varchar(20) default '',
  ADDRESS varchar(100) default '',
  LOCATION varchar(10) default '',
  REMARKS varchar(100) default '',
  PERSON_DIVISION_ID varchar(20) default '',
  PERSON_DISTRICT_ID varchar(20) default '',
  PERSON_PROVINCE_CODE varchar(20) default '',
  STATUS varchar(10) default '',
  PRIMARY KEY  (PERSION_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `damage_affected_person`
--


--
-- Table structure for table `damage_severities`
--

CREATE TABLE damage_severities (
  DAMAGED_SEVERITY_CODE varchar(100) NOT NULL default '',
  DAMAGE_SEVERITY_DESC varchar(100) default '',
  PRIMARY KEY  (DAMAGED_SEVERITY_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `damage_severities`
--

INSERT INTO damage_severities VALUES ('2','Affected');
INSERT INTO damage_severities VALUES ('1','Severe');

--
-- Table structure for table `damaged_case`
--

CREATE TABLE damaged_case (
  CASE_ID int(11) NOT NULL auto_increment,
  REPORTED_DATE date default '0000-00-00',
  REPORTER_ID varchar(20) default '',
  REPORTER_NAME varchar(30) default '',
  REPORTER_PHONE_NO varchar(20) default '',
  REPORTER_ADDRESS varchar(100) default '',
  REPORTER_LOCATION varchar(20) default '',
  AUTH_INSTITUTION varchar(30) default '',
  AUTH_OFFICER_NAME varchar(30) default '',
  CAUSE_OF_DAMAGE varchar(50) default '',
  DAMAGE_OCCURENCE_DATE date default '0000-00-00',
  CASE_DIVISION_ID varchar(20) default '',
  CASE_DISTRICT_ID varchar(100) default '',
  CASE_PROVINCE_ID varchar(100) default '',
  AUTH_REF_NO varchar(20) default '',
  PRIMARY KEY  (CASE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `damaged_case`
--

INSERT INTO damaged_case VALUES (306,'2005-01-28','111','tt','tt','','','deafult','','ttt','2005-01-28','-1','-1','2','');
INSERT INTO damaged_case VALUES (307,'2005-01-28','111','tt','tt','','','deafult','','ttt','2005-01-28','-1','-1','2','');
INSERT INTO damaged_case VALUES (308,'2005-01-28','','','','','','deafult','','dd','2005-01-28','-1','-1','-1','');
INSERT INTO damaged_case VALUES (309,'2005-01-28','','','','','','deafult','','','2005-01-28','-1','-1','-1','');
INSERT INTO damaged_case VALUES (310,'2005-01-31','','','','','','deafult','','','2005-01-31','-1','-1','-1','');
INSERT INTO damaged_case VALUES (311,'2005-01-31','','','','','','deafult','','','2005-01-31','-1','-1','-1','');
INSERT INTO damaged_case VALUES (312,'2005-01-31','','','','','','deafult','','','2005-01-31','-1','-1','-1','');

--
-- Table structure for table `damaged_property`
--

CREATE TABLE damaged_property (
  PROPERTY_ID int(11) NOT NULL auto_increment,
  CASE_ID int(11) default '0',
  PROPERTY_TYPE varchar(20) default '',
  NO_OF_PERSION_AFFECTED int(4) default '0',
  IS_MAIN_SOURCE_OF_LIVING varchar(10) default '',
  ESTIMATED_INCOME_VALUE double default '0',
  ESTIMATED_DAMAGE_VALUE double default '0',
  ESTIMATED_REPLACEMENT_COST double default '0',
  DAMAGE_SEVERITY varchar(10) default '',
  LOCATION varchar(20) default '',
  INSURENCE_COMPANY_NAME varchar(30) default '',
  INSURENCE_POLICY_NO varchar(20) default '',
  INSURED_VALUE double default '0',
  PROPERTY_DIVISION_ID varchar(20) default '',
  PROPERTY_DISTRICT_ID varchar(20) default '',
  PROPERTY_PROVINCE_CODE varchar(20) default '',
  APPROVED_CLAIM_VALUE double default '0',
  FLEX_FIELD_1 varchar(100) default '',
  PRIMARY KEY  (PROPERTY_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `damaged_property`
--

INSERT INTO damaged_property VALUES (1,311,'2',0,'',0,1000,0,'1','','deafult','',0,'-1','','',0,'');
INSERT INTO damaged_property VALUES (409,312,'deafult',0,'',0,111,0,'deafult','','deafult','',0,'-1','','',0,'');
INSERT INTO damaged_property VALUES (408,311,'1',0,'',0,5000,0,'2','','deafult','',0,'-1','','',0,'');

--
-- Table structure for table `damaged_property_types`
--

CREATE TABLE damaged_property_types (
  DAMAGED_PROPERTY_TYPE_ID varchar(10) NOT NULL default '',
  DAMAGED_PROPERTY_TYPE_NAME varchar(30) NOT NULL default '',
  PRIMARY KEY  (DAMAGED_PROPERTY_TYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `damaged_property_types`
--

INSERT INTO damaged_property_types VALUES ('2','Vehical');
INSERT INTO damaged_property_types VALUES ('1','House');

--
-- Table structure for table `district`
--

CREATE TABLE district (
  DistrictCode varchar(20) NOT NULL default '',
  Name varchar(20) NOT NULL default '',
  PRIMARY KEY  (DistrictCode)
) TYPE=MyISAM;

--
-- Dumping data for table `district`
--

INSERT INTO district VALUES ('CMB','Colombo');
INSERT INTO district VALUES ('GMP','Gampaha');
INSERT INTO district VALUES ('KUL','Kalutara');
INSERT INTO district VALUES ('KAN','Kandy');
INSERT INTO district VALUES ('MAT','Matale');
INSERT INTO district VALUES ('NUR','Nuwara_Eliya');
INSERT INTO district VALUES ('GAL','Galle');
INSERT INTO district VALUES ('MAR','Matara');
INSERT INTO district VALUES ('HAM','Hambantota');
INSERT INTO district VALUES ('JAF','Jaffna');
INSERT INTO district VALUES ('MAN','Mannar');
INSERT INTO district VALUES ('VAV','Vavuniya');
INSERT INTO district VALUES ('MUL','Mullaitivu');
INSERT INTO district VALUES ('KILL','Kilinochchi');
INSERT INTO district VALUES ('BAT','Batticaloa');
INSERT INTO district VALUES ('AMP','Ampara');
INSERT INTO district VALUES ('TRIN','Trincomalee');
INSERT INTO district VALUES ('KUR','Kurunegala');
INSERT INTO district VALUES ('PUT','Puttalam');
INSERT INTO district VALUES ('ANU','Anuradhapura');
INSERT INTO district VALUES ('POL','Polonnaruwa');
INSERT INTO district VALUES ('BAD','Badulla');
INSERT INTO district VALUES ('MON','Monaragala');
INSERT INTO district VALUES ('RAT','Ratnapura');
INSERT INTO district VALUES ('KEG','Kegalle');

--
-- Table structure for table `fulfillstatus`
--

CREATE TABLE fulfillstatus (
  status varchar(20) NOT NULL default '0',
  Description varchar(50) NOT NULL default '',
  PRIMARY KEY  (status)
) TYPE=MyISAM;

--
-- Dumping data for table `fulfillstatus`
--

INSERT INTO fulfillstatus VALUES ('1','Under Consideration');
INSERT INTO fulfillstatus VALUES ('2','On Route');
INSERT INTO fulfillstatus VALUES ('3','Delivered');
INSERT INTO fulfillstatus VALUES ('4','Withdrawn');

--
-- Table structure for table `house`
--

CREATE TABLE house (
  Id int(11) NOT NULL auto_increment,
  DistrictCode varchar(100) default '',
  Division varchar(100) default '',
  GSN varchar(100) default '',
  Owner varchar(100) default '',
  DistanceFromSea double default '0',
  City varchar(100) default '',
  NoAndStreet varchar(100) default '',
  CurrentAddress varchar(100) default '',
  FloorArea double default '0',
  NoOfStories int(11) default '0',
  TypeOfOwnership varchar(100) default '',
  NoOfResidents int(11) default '0',
  TypeOfConstruction varchar(100) default '',
  PropertyTaxNo varchar(100) default '',
  TotalDamageCost double default '0',
  LandArea double default '0',
  Relocate tinyint(4) default '0',
  Insured tinyint(4) default '0',
  DamageType varchar(100) default '',
  Comments varchar(250) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `house`
--

INSERT INTO house VALUES (1,NULL,NULL,NULL,NULL,NULL,'ss',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO house VALUES (2,'GMP','jhs','h','kj',NULL,'hk','kj','hj',98,2,'Encroched',2,'Thatched','23',12,43,0,0,'Roof Destroyed',NULL);
INSERT INTO house VALUES (3,'GMP','jhs','h','kj',NULL,'hk','kj','hj',98,2,'Encroched',2,'Thatched','23',12,43,0,0,'Roof Destroyed',NULL);
INSERT INTO house VALUES (4,'AMP','kshjs','s','as',NULL,'asd','asd','as',NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (5,'AMP','kshjs','s','as',NULL,'asd','asd','as',NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (6,'AMP','kshjs','s','as',NULL,'asd','asd','as',NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (7,'AMP','Jaliya','Jaliya','Jaliya',NULL,'Jaliya','Jaliya','Jaliya',78,5,'Leased/Rent',87,'Bricks','87544',87737363,65,0,0,'Structural Damage',NULL);
INSERT INTO house VALUES (8,'AMP','Jaliya','Jaliya','Jaliya',NULL,'Jaliya','Jaliya','Jaliya',78,5,'Leased/Rent',87,'Bricks','87544',87737363,65,0,0,'Structural Damage',NULL);
INSERT INTO house VALUES (9,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed','None');
INSERT INTO house VALUES (10,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed','None');
INSERT INTO house VALUES (11,'AMP','Chathura','Chathura','Chathura',1000,'Chathura','Chathura','Chathura',322,3,'Leased/Rent',32,'Thatched','Chathura',43222,233,0,0,'Structural Damage','Chathura');
INSERT INTO house VALUES (12,'AMP','Chathura','Chathura','Chathura',1000,'Chathura','Chathura','Chathura',322,3,'Leased/Rent',32,'Thatched','Chathura',43222,233,0,0,'Structural Damage','Chathura');
INSERT INTO house VALUES (13,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (14,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (15,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (16,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (17,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (18,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (19,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (20,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (21,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (22,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (23,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (24,'AMP',NULL,NULL,NULL,NULL,'eee',NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (25,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,0,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (26,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (27,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (28,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (29,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (30,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);
INSERT INTO house VALUES (31,'AMP',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,1,'Self Owned',NULL,'Bricks',NULL,NULL,NULL,1,0,'Completely Destroyed',NULL);

--
-- Table structure for table `house_damage_moreinfo`
--

CREATE TABLE house_damage_moreinfo (
  Id int(11) NOT NULL auto_increment,
  HouseId int(11) NOT NULL default '0',
  DamageInfo varchar(100) NOT NULL default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `house_damage_moreinfo`
--

INSERT INTO house_damage_moreinfo VALUES (1,1,'House is damaged');
INSERT INTO house_damage_moreinfo VALUES (2,1,'Wall is damaged');

--
-- Table structure for table `house_facility_info`
--

CREATE TABLE house_facility_info (
  Id int(11) NOT NULL auto_increment,
  HouseId int(11) NOT NULL default '0',
  FacilityName varchar(100) default '',
  Description varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `house_facility_info`
--

INSERT INTO house_facility_info VALUES (1,1,'house','New desccccr');
INSERT INTO house_facility_info VALUES (2,1,'hf2hf2hf2hf2hf2','DDDDDDDDDDDDDD');

--
-- Table structure for table `hr_deployment`
--

CREATE TABLE hr_deployment (
  Id int(11) NOT NULL auto_increment,
  OrgCode varchar(100) NOT NULL default '',
  AreaOfExpertise int(11) NOT NULL default '0',
  LevelOfExpertise int(11) default '0',
  Redeployed tinyint(1) default '0',
  Strength int(11) NOT NULL default '0',
  DateDeployed date NOT NULL default '0000-00-00',
  DateReleased date default '0000-00-00',
  Notes varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `hr_deployment`
--


--
-- Table structure for table `hr_deployment_issues`
--

CREATE TABLE hr_deployment_issues (
  HRDeploymentId int(11) NOT NULL default '0',
  IssueId int(11) NOT NULL default '0',
  PRIMARY KEY  (HRDeploymentId,IssueId)
) TYPE=MyISAM;

--
-- Dumping data for table `hr_deployment_issues`
--


--
-- Table structure for table `hr_deployment_sites`
--

CREATE TABLE hr_deployment_sites (
  HRDeploymentId int(11) NOT NULL default '0',
  SiteId int(11) NOT NULL default '0',
  PRIMARY KEY  (HRDeploymentId,SiteId)
) TYPE=MyISAM;

--
-- Dumping data for table `hr_deployment_sites`
--


--
-- Table structure for table `hr_deployment_tasks`
--

CREATE TABLE hr_deployment_tasks (
  HRDeploymentId int(11) NOT NULL default '0',
  TaskId int(11) NOT NULL default '0',
  PRIMARY KEY  (HRDeploymentId,TaskId)
) TYPE=MyISAM;

--
-- Dumping data for table `hr_deployment_tasks`
--


--
-- Table structure for table `hse_constructor_mst`
--

CREATE TABLE hse_constructor_mst (
  CONSTRUCTOR_ID int(5) NOT NULL default '0',
  CONSTRUCTOR_NAME varchar(50) NOT NULL default '',
  ADDRESS varchar(100) NOT NULL default '',
  TELEPHONE varchar(100) NOT NULL default '',
  CONTACT_PERSON varchar(100) NOT NULL default '',
  PRIMARY KEY  (CONSTRUCTOR_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_constructor_mst`
--


--
-- Table structure for table `hse_facility_budget_tx`
--

CREATE TABLE hse_facility_budget_tx (
  HOUSING_SCHEME_ID int(5) NOT NULL default '0',
  FACILITY_ID int(5) NOT NULL default '0',
  COST decimal(11,0) NOT NULL default '0',
  PRIMARY KEY  (FACILITY_ID,HOUSING_SCHEME_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_facility_budget_tx`
--


--
-- Table structure for table `hse_facility_mst`
--

CREATE TABLE hse_facility_mst (
  FACILITY_ID int(5) NOT NULL default '0',
  FACILITY_NAME varchar(50) NOT NULL default '',
  DISCRIPTION varchar(100) NOT NULL default '',
  PRIMARY KEY  (FACILITY_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_facility_mst`
--


--
-- Table structure for table `hse_house_mst`
--

CREATE TABLE hse_house_mst (
  HOUSE_ID int(5) NOT NULL default '0',
  HOUSING_SCHEME_ID int(5) NOT NULL default '0',
  PLOT_ID int(5) NOT NULL default '0',
  AREA_ID int(5) NOT NULL default '0',
  PRIMARY KEY  (HOUSE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_house_mst`
--


--
-- Table structure for table `hse_house_sponsor_mst`
--

CREATE TABLE hse_house_sponsor_mst (
  HOUSE_ID int(5) NOT NULL default '0',
  SPONSOR_ID int(5) NOT NULL default '0',
  PRIMARY KEY  (HOUSE_ID,SPONSOR_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_house_sponsor_mst`
--

INSERT INTO hse_house_sponsor_mst VALUES (1,22);
INSERT INTO hse_house_sponsor_mst VALUES (1,23);
INSERT INTO hse_house_sponsor_mst VALUES (2,3);

--
-- Table structure for table `hse_house_subtype_mst`
--

CREATE TABLE hse_house_subtype_mst (
  HOUSE_SUBTYPE_ID int(5) NOT NULL default '0',
  HOUSE_TYPE_ID int(5) NOT NULL default '0',
  HOUSE_SUBTYPE_NAME varchar(50) NOT NULL default '',
  COST decimal(11,0) NOT NULL default '0',
  PRIMARY KEY  (HOUSE_SUBTYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_house_subtype_mst`
--


--
-- Table structure for table `hse_house_type_mst`
--

CREATE TABLE hse_house_type_mst (
  HOUSE_TYPE_DESCRIPTION varchar(150) default '',
  HOUSE_TYPE_ID int(5) NOT NULL default '0',
  HOUSE_TYPE_NAME varchar(50) NOT NULL default '',
  PRIMARY KEY  (HOUSE_TYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_house_type_mst`
--


--
-- Table structure for table `hse_housing_scheme_mst`
--

CREATE TABLE hse_housing_scheme_mst (
  HOUSING_SCHEME_ID int(5) NOT NULL default '0',
  HOUSING_SCHEME_NAME varchar(100) NOT NULL default '',
  TOTAL_NO_OF_HOUSES int(11) NOT NULL default '0',
  LAND_ID int(5) NOT NULL default '0',
  CONSTRUCTOR_ID int(5) NOT NULL default '0',
  TOTAL_COST int(11) NOT NULL default '0',
  TOTAL_TIME varchar(100) NOT NULL default '',
  START_DATE date NOT NULL default '0000-00-00',
  END_DATE date NOT NULL default '0000-00-00',
  STATUS varchar(100) NOT NULL default 'Not Started',
  DISCRIPTION varchar(100) NOT NULL default '',
  PRIMARY KEY  (HOUSING_SCHEME_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_housing_scheme_mst`
--


--
-- Table structure for table `hse_land_mst`
--

CREATE TABLE hse_land_mst (
  AREA2 decimal(10,0) NOT NULL default '0',
  AREA1 decimal(10,0) NOT NULL default '0',
  MEASUREMENT_TYPE_ID1 int(11) NOT NULL default '0',
  INFRACTURE int(11) NOT NULL default '0',
  MEASUREMENT_TYPE_ID2 varchar(100) NOT NULL default '',
  LAND_TYPE int(11) NOT NULL default '0',
  PLAN_NO varchar(100) NOT NULL default '',
  LAND_ID int(5) NOT NULL auto_increment,
  LAND_NAME varchar(100) default '',
  SUB_DIVISION_ID int(5) NOT NULL default '0',
  MEASUREMENT_TYPE_ID int(5) NOT NULL default '0',
  DESCRIPTION varchar(100) default '""',
  GPS1 varchar(100) default '',
  GPS2 varchar(100) default '',
  GPS3 varchar(100) default '',
  GPS4 varchar(100) default '',
  TERM_ID int(5) NOT NULL default '0',
  AREA decimal(10,0) NOT NULL default '0',
  OWNED_BY_ID int(1) NOT NULL default '0',
  REMARKS varchar(100) default '',
  PROPOSED_USE_ASPERZONPLAN varchar(100) default '',
  OWNED_BY_COMMENT varchar(100) default '',
  PRIMARY KEY  (LAND_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_land_mst`
--

INSERT INTO hse_land_mst VALUES ('33343','6575',0,8,'',1,'plan001',107,'palan1111',1,0,'desc riptioo','North','222','West','34',1,'22',0,'remarks11','nithya zoning plan12',NULL);
INSERT INTO hse_land_mst VALUES ('0','33',0,8,'',1,'plan',108,'apalasm',1,0,'dkfjklfjdgklfjdkljdsfkljfkgj;sjg;lsj;gj','North','3','East','33',1,'22',1,'ddd jiffhd ddgdnd dfd','ddd','fffffffffffffffffffffffffffff');
INSERT INTO hse_land_mst VALUES ('0','0',0,8,'',1,'tttttt',109,'hjhhh',1,0,'ffffffffffffffffffffffffffffffffffffffff','North','55','East','66',2,'566',0,'66666666666666666666666','errrrrr',NULL);
INSERT INTO hse_land_mst VALUES ('33','12',0,8,'',1,'plan0101',110,'Live SRILANKA',1,0,'CHECKOUT','-1',NULL,'-1',NULL,2,'15',0,'remarks','proposed',NULL);

--
-- Table structure for table `hse_measurement_type_mst`
--

CREATE TABLE hse_measurement_type_mst (
  MEASUREMENT_TYPE_ID int(5) NOT NULL default '0',
  MEASUREMENT_TYPE_NAME varchar(30) NOT NULL default '0',
  PRIMARY KEY  (MEASUREMENT_TYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_measurement_type_mst`
--

INSERT INTO hse_measurement_type_mst VALUES (1,'Acres');
INSERT INTO hse_measurement_type_mst VALUES (2,'perches');
INSERT INTO hse_measurement_type_mst VALUES (0,'Rods');

--
-- Table structure for table `hse_owned_by_mst`
--

CREATE TABLE hse_owned_by_mst (
  OWNED_BY_ID varchar(100) NOT NULL default '',
  OWNED_BY_NAME varchar(100) NOT NULL default ''
) TYPE=MyISAM;

--
-- Dumping data for table `hse_owned_by_mst`
--

INSERT INTO hse_owned_by_mst VALUES ('0','Government');
INSERT INTO hse_owned_by_mst VALUES ('1','Private');

--
-- Table structure for table `hse_plot_mst`
--

CREATE TABLE hse_plot_mst (
  PLOT_ID int(5) NOT NULL default '0',
  LAND_ID int(5) NOT NULL default '0',
  DISCRIPTION varchar(100) NOT NULL default '',
  GPS1 varchar(100) NOT NULL default '',
  GPS2 varchar(100) NOT NULL default '',
  GPS3 varchar(100) NOT NULL default '',
  GPS4 varchar(100) NOT NULL default '',
  PRIMARY KEY  (PLOT_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_plot_mst`
--


--
-- Table structure for table `hse_scheme_house_tx`
--

CREATE TABLE hse_scheme_house_tx (
  HOUSING_SCHEME_ID int(5) NOT NULL default '0',
  HOUSE_SUBTYPE_ID int(5) NOT NULL default '0',
  NO_OF_HOUSES int(11) NOT NULL default '0',
  PRIMARY KEY  (HOUSING_SCHEME_ID,HOUSE_SUBTYPE_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_scheme_house_tx`
--


--
-- Table structure for table `hse_term_mst`
--

CREATE TABLE hse_term_mst (
  TERM_ID int(11) NOT NULL auto_increment,
  DESCRIPTION varchar(100) NOT NULL default '',
  PRIMARY KEY  (TERM_ID)
) TYPE=MyISAM;

--
-- Dumping data for table `hse_term_mst`
--

INSERT INTO hse_term_mst VALUES (1,'Leased');
INSERT INTO hse_term_mst VALUES (2,'Total Ownership');

--
-- Table structure for table `insurence_companies`
--

CREATE TABLE insurence_companies (
  INSURENCE_COMPANY_CODE varchar(20) NOT NULL default '',
  INSURENCE_COMPANY_NAME varchar(100) NOT NULL default '',
  PRIMARY KEY  (INSURENCE_COMPANY_CODE)
) TYPE=MyISAM;

--
-- Dumping data for table `insurence_companies`
--

INSERT INTO insurence_companies VALUES ('2','Jana Shakthi');
INSERT INTO insurence_companies VALUES ('1','Sri Lanka Insurence');

--
-- Table structure for table `issue`
--

CREATE TABLE issue (
  Id int(11) NOT NULL auto_increment,
  OrgCode varchar(100) NOT NULL default '',
  Date date NOT NULL default '0000-00-00',
  Type int(11) NOT NULL default '0',
  Description varchar(100) default '',
  AddressedTo varchar(100) default '',
  Status int(11) NOT NULL default '0',
  Notes varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `issue`
--


--
-- Table structure for table `need_assesment`
--

CREATE TABLE need_assesment (
  Id int(11) NOT NULL auto_increment,
  OrgCode varchar(100) NOT NULL default '',
  Status int(11) NOT NULL default '0',
  Description varchar(100) NOT NULL default '',
  DateStarted date NOT NULL default '0000-00-00',
  Conclusion varchar(100) default '',
  Notes varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `need_assesment`
--


--
-- Table structure for table `need_assesment_issues`
--

CREATE TABLE need_assesment_issues (
  NeedAssesmentId int(11) NOT NULL default '0',
  IssueID int(11) NOT NULL default '0',
  PRIMARY KEY  (IssueID,NeedAssesmentId)
) TYPE=MyISAM;

--
-- Dumping data for table `need_assesment_issues`
--


--
-- Table structure for table `offer`
--

CREATE TABLE offer (
  OfferID int(5) NOT NULL auto_increment,
  OfferingEntityType varchar(12) NOT NULL default '',
  OfferingOrgCode varchar(10) default '0',
  OfferingIndividual varchar(20) default '',
  OfferingIndContactNumber varchar(20) default '',
  OfferingIndContactAddress varchar(100) default '',
  OfferingIndEmail varchar(30) default '',
  Item varchar(100) NOT NULL default '',
  Category varchar(20) NOT NULL default '',
  Unit varchar(10) NOT NULL default '',
  TotalOfferQuantity int(11) default '0',
  Description varchar(100) default '',
  TimeFrame varchar(20) default '',
  EquivalentValue varchar(20) default '',
  PRIMARY KEY  (OfferID)
) TYPE=MyISAM;

--
-- Dumping data for table `offer`
--

INSERT INTO offer VALUES (1,'Organization','000009','',' fghjgf',' \r\ngfhgf','adsa@hfghgf.com','ddd','14','ddd',12,'ddd','ddd','ddd');
INSERT INTO offer VALUES (2,'Individual','','Sandun','   2222','  123','a@b.c','rice','1','kg',42,'rice','12','12');
INSERT INTO offer VALUES (4,'Organization','000019','',' srirha',' srirha','srirha@srirha.srirha','gauze','8','roll',240,'ddd','32','380');
INSERT INTO offer VALUES (5,'Organization','000019','',' srirha',' srirha','srirha@srirha.srirha','cement','14','pack',130,'sssss','144','1000');
INSERT INTO offer VALUES (6,'Individual','','damith','  111','  damith','damith','t','6','t',100,'damith','12','70');
INSERT INTO offer VALUES (7,'Organization','000026','',' 55555',' \r\nNone','None@None.com','None','15','None',24,'None','None','None');

--
-- Table structure for table `offer_area`
--

CREATE TABLE offer_area (
  OfferID int(5) NOT NULL default '0',
  TargetArea varchar(5) NOT NULL default '',
  QuantityPerTargetArea int(11) NOT NULL default '0',
  PRIMARY KEY  (OfferID,TargetArea)
) TYPE=MyISAM;

--
-- Dumping data for table `offer_area`
--

INSERT INTO offer_area VALUES (1,'POL',12);
INSERT INTO offer_area VALUES (2,'RAT',12);
INSERT INTO offer_area VALUES (2,'TRIN',30);
INSERT INTO offer_area VALUES (4,'MAT',120);
INSERT INTO offer_area VALUES (4,'TRIN',120);
INSERT INTO offer_area VALUES (5,'PUT',30);
INSERT INTO offer_area VALUES (5,'RAT',100);

--
-- Table structure for table `offer_log`
--

CREATE TABLE offer_log (
  UserName varchar(20) NOT NULL default '',
  Comment varchar(200) default '',
  Date varchar(20) NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (UserName,Date)
) TYPE=MyISAM;

--
-- Dumping data for table `offer_log`
--

INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 1 ) Successfully.','2005-01-21 21:39:18');
INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 2 ) Successfully.','2005-01-21 21:44:05');
INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 4 ) Successfully.','2005-01-21 21:49:53');
INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 5 ) Successfully.','2005-01-21 21:51:00');
INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 6 ) Successfully.','2005-01-21 21:56:35');
INSERT INTO offer_log VALUES ('user.getUserName()','Added Offer ID : ( 7 ) Successfully.','2005-01-21 21:57:29');

--
-- Table structure for table `offers`
--

CREATE TABLE offers (
  id int(10) unsigned NOT NULL auto_increment,
  agency varchar(10) NOT NULL default '',
  date date NOT NULL default '0000-00-00',
  sectors varchar(255) default NULL,
  partners varchar(255) default NULL,
  relief_committed_details text,
  relief_committed_total decimal(20,2) default NULL,
  relief_disbursed_details text,
  relief_disbursed_total decimal(20,2) default NULL,
  human_resources_committed text,
  needs_assessments text,
  other_activities text,
  planned_activities text,
  other_issues text,
  PRIMARY KEY  (id)
) TYPE=MyISAM;

--
-- Dumping data for table `offers`
--

INSERT INTO offers VALUES (38,'000001','0000-00-00',NULL,'CARE','When programming, the need for use of assembly language arises due to two main reasons. Low level tasks are often difficult if not impossible to implement in 3rd generation languages like C/C++, Pascal etc. It is also well known that C/C++ compilers in particular produce very efficient code. Still in instances where lot of things have to be done as quickly as possible like when doing animations for example, even this is not good enough. In graphics programming quite frequently we find that computer spends most of the time executing a fairly limited amount of code. Identifying that part of the program an converting it into assembly language can increase the efficiency of the program significantly. Hence programs that require the use of assembly language are seldom completely written in assembly language. Rather, only those portions of code which cannot be implemented in high level language will be done in assembly language.\r\n\r\n',NULL,NULL,NULL,'Sdaasd','asdasdad','asdasdsa','adasdas','adasdsasd');
INSERT INTO offers VALUES (6,'000002','0000-00-00',NULL,'sdf','sdf',NULL,'sdf',NULL,'sdf','ssdf','sdf','sdf','sdf');
INSERT INTO offers VALUES (7,'000005','0000-00-00',NULL,'ministry of health','medicine, hospotal supplies',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (32,'000002','0000-00-00',NULL,'sdfgdfg','dfbsdfbsdfbdfb',NULL,'bsdfbsdfbf',NULL,'55',NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (31,'000005','0000-00-00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (36,'000002','0000-00-00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (37,'000005','0000-00-00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (35,'000002','0000-00-00',NULL,'Lanka Software Foundation, ICTA','1000 computer labs','100000.00','asfga','12333.00','5','yrd',NULL,NULL,NULL);
INSERT INTO offers VALUES (34,'000002','0000-00-00',NULL,'sfgs','gsdfg','55666666.00','dfs','6666.00','dfgdf','dfgd','dfg','dfg','dfg');
INSERT INTO offers VALUES (33,'000001','0000-00-00',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (39,'000001','0000-00-00',NULL,'1','sW','2000.00','Deployed','344.00','23','None','None','None','None');
INSERT INTO offers VALUES (40,'000001','0000-00-00',NULL,NULL,'gsdfg','55666666.00','dfs','6666.00','dfgdf','dfgd','dfg','dfg','dfg');
INSERT INTO offers VALUES (41,'000001','0000-00-00',NULL,'5','None','2.00','None','3.00','Lot','None','None','None','None');
INSERT INTO offers VALUES (42,'000001','0000-00-00',NULL,NULL,'None','2.00','None','3.00','Lot and more','None','None','None','None');
INSERT INTO offers VALUES (43,'000001','0000-00-00',NULL,'hello',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (44,'000001','1998-10-09',NULL,'cvc','ccc','4.00','bgf','2.00','sd','sd','sd','sd','sd');
INSERT INTO offers VALUES (45,'000001','0000-00-00',NULL,'Helloooooooooooooooooo','Helloooooooooooooooooo','1232323232.00','Helloooooooooooooooooo','12.00','Hellooooooooooo0000000000 000000 0000 0  00000000  000000000  00000000 000  0000000j         l;l;l;;l; ;;;;            ;;;;;;;;;;;;; ooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (46,'000001','0000-00-00',NULL,'Helloooooooooooooooooooooooooooooo','Helloooooooooooooooooo','1232323232.00','Helloooooooooooooooooo','12.00','Hellooooooooooo0000000000 000000 0000 0  00000000  000000000  00000000 000  0000000j         l;l;l;;l; ;;;;            ;;;;;;;;;;;;; ooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (47,'000001','0000-00-00','sdfksdjfsjkdjf','Helloooooooooooooooooooooooooooooo','Helloooooooooooooooooo','1232323232.00','Helloooooooooooooooooo','12.00','Hellooooooooooo0000000000 000000 0000 0  00000000  000000000  00000000 000  0000000j         l;l;l;;l; ;;;;            ;;;;;;;;;;;;; ooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (48,'000001','0000-00-00','sdfksdjfsjkdjf','22222222 33333333','4444444444 555555555','1232323232.00','Helloooooooooooooooooo','12.00','A Software Process Improvement Network (SPIN) is an organization of software professionals involved in software process improvement within a geographic region. SPINs are all over the world; each started by its community, and then linked together through mutual contact and the SEI (Carnegie-Mellon University\'s Software TYPEering Institute) which helps the formation and existence of SPINs in many ways. \r\n\r\nA SPIN provides a practical forum for the interchange of ideas, information, and mutual support for membership. Each SPIN is slightly different, based on the vision of the founders and the needs of the community. Most operate on volunteered time and resources, and don\'t charge membership fees.  \r\n  \r\nHow did SPINs get started? \r\nIn 1988, several software professionals were working on process improvement in the Washington DC area. These professionals decided that they needed a practical forum for the exchange of ideas, information, and mutual support. \r\n\r\nRealizing that the Software TYPEering Institute (SEI) could not actively support all ongoing process improvement efforts, these professionals created a mechanism by which members of Software TYPEering Process Groups (SEPGs) could band together to provide mutual support and interaction not available through the SEI.  \r\n  \r\n','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (49,'000001','0000-00-00','sdfksdjfsjkdjf','Helloooooooooooooooooooooooooooooo','Helloooooooooooooooooo','1232323232.00','It is working!','12.00','A Software Process Improvement Network (SPIN) is an organization of software professionals involved in software process improvement within a geographic region. SPINs are all over the world; each started by its community, and then linked together through mutual contact and the SEI (Carnegie-Mellon University\'s Software TYPEering Institute) which helps the formation and existence of SPINs in many ways. \r\n\r\nA SPIN provides a practical forum for the interchange of ideas, information, and mutual support for membership. Each SPIN is slightly different, based on the vision of the founders and the needs of the community. Most operate on volunteered time and resources, and don\'t charge membership fees.  \r\n  \r\nHow did SPINs get started? \r\nIn 1988, several software professionals were working on process improvement in the Washington DC area. These professionals decided that they needed a practical forum for the exchange of ideas, information, and mutual support. \r\n\r\nRealizing that the Software TYPEering Institute (SEI) could not actively support all ongoing process improvement efforts, these professionals created a mechanism by which members of Software TYPEering Process Groups (SEPGs) could band together to provide mutual support and interaction not available through the SEI.  \r\n  \r\n','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (50,'000001','0000-00-00','sdfksdjfsjkdjf','Helloooooooooooooooooooooooooooooo','It is working!','1232323232.00',NULL,'12.00','A Software Process Improvement Network (SPIN) is an organization of software professionals involved in software process improvement within a geographic region. SPINs are all over the world; each started by its community, and then linked together through mutual contact and the SEI (Carnegie-Mellon University\'s Software TYPEering Institute) which helps the formation and existence of SPINs in many ways. \r\n\r\nA SPIN provides a practical forum for the interchange of ideas, information, and mutual support for membership. Each SPIN is slightly different, based on the vision of the founders and the needs of the community. Most operate on volunteered time and resources, and don\'t charge membership fees.  \r\n  \r\nHow did SPINs get started? \r\nIn 1988, several software professionals were working on process improvement in the Washington DC area. These professionals decided that they needed a practical forum for the exchange of ideas, information, and mutual support. \r\n\r\nRealizing that the Software TYPEering Institute (SEI) could not actively support all ongoing process improvement efforts, these professionals created a mechanism by which members of Software TYPEering Process Groups (SEPGs) could band together to provide mutual support and interaction not available through the SEI.  \r\n  \r\n','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo','Helloooooooooooooooooo');
INSERT INTO offers VALUES (51,'000001','0000-00-00','temp1234',NULL,NULL,'5555.00',NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (52,'000001','2005-01-05','Please let us go home!','We are so sooo sleepy.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (53,'000001','2005-01-05','He wants to go home!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
INSERT INTO offers VALUES (54,'000001','2005-01-07','This is it','This is it','This is it','12.00','This is it','54.00','This is it','This is it','This is it','This is it','This is it');

--
-- Table structure for table `organization`
--

CREATE TABLE organization (
  OrgType varchar(20) NOT NULL default '',
  OrgSubType varchar(20) default '',
  OrgCode varchar(10) NOT NULL default '0',
  ContactPerson varchar(100) NOT NULL default '',
  OrgName varchar(100) NOT NULL default '',
  Status tinyint(1) NOT NULL default '0',
  OrgAddress varchar(200) NOT NULL default '',
  ContactNumber varchar(255) NOT NULL default '',
  EmailAddress varchar(100) NOT NULL default '',
  CountryOfOrigin varchar(100) NOT NULL default '',
  FacilitiesAvailable varchar(255) default '',
  WorkingAreas varchar(255) default '',
  Comments varchar(255) default '',
  LastUpdate varchar(100) NOT NULL default '',
  IsSriLankan tinyint(4) NOT NULL default '0',
  UntilDate varchar(100) NOT NULL default '',
  PRIMARY KEY  (OrgCode)
) TYPE=MyISAM;

--
-- Dumping data for table `organization`
--

INSERT INTO organization VALUES ('Multilateral','','000001','dg','ICRC',0,'sdfgs','sdfg','sdgf','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-INGO','000002','John','CARE',0,'Colombo','+941','john@care.com','Suriname',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000003','FRC','FRC',0,'FRC - Colombo','+61','frc@frc.org','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Bilateral','','000004','hfh','Habitat for Humanity',0,'hfh - Negombo','+932','hfh@hfh.org','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Government','','000005','nccsl','NCCSL',0,'nccsl - Kandy','+947','nccsl@nccsl.org','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-NGO','000006','ygro','YGRO',0,'ygro - seeduwa','ygro','ygro@ygro.org','Nauru',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-NGO','000007','leads','LEADS',0,'leads - maharagama','+9411','LEADS@Leads.org','Uruguay',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000008','12345','ICRC 1',0,'asdasdsa','111222333444','cmendis@yahoo.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000011','gdfgdf','gdf',0,'\r\ngfhgf','gfff','1112@dd.com','Sri Lanka','fdgdf','gh','ghf','',0,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-NGO','000012','hemal','hemal',0,'12,rtrwegtre,Colombo\r\n','122432','hdealwis@virtusa.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Bilateral','','000013','Aruny','Aruny',0,'\r\n12,ghehgfdb,fdbfdvbd','32432432','a@a.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-NGO','000014','Kalpana','Kalpana',0,'ragfdgvdsgdsgvdvav\r\n','2132131','a@a.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000015','bvcvb','bv',0,'ccvb\r\n\r\n','cvbcvbcv','sdfsd@fdf.com','Sri Lanka','sdf','sdf','sdf','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000009','gfjgfh','gfdsfg',0,'\r\ngfhgf','fghjgf','adsa@hfghgf.com','Sri Lanka','fgfd','fgdf','dfgd','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000010','dfgd','fsdfsd',0,'\r\ngdf\r\n','fgd','dfg@cc.com','Sri Lanka','gfhgfq','fhdfq','fgd','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000016','dfg','dfg',0,'dfg','dgf','gfdf@cc.','Sri Lanka','sdf','sdf','sdf','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000017','sdf','sdfsd',0,'sdf','sdfsdfds','sdfsd@ccc.','Sri Lanka','sad','asd','asd','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000018','Ajith','Ajith',0,'Ajith\r\n\r\n\r\n','1111111','Ajith@Ajith.Ajith','Sri Lanka','sfsd','sdfs','sdfsd','Tue Jan 18 10:14:24 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000019','srirha','srirha',0,'srirha','srirha','srirha@srirha.srirha','Sri Lanka','sdfs','sdfs','sdf','',0,'2005-01-30');
INSERT INTO organization VALUES ('Bilateral','','000020','kema sagara','kema',0,'\r\n12,kuchgqchgwql\r\nwekuvcgwevfwe\r\newqihfewlifchewl\r\neihfiewlhclewic\r\newoifhewo\r\newligfew','214124321','a@a.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000021','niranjaa','nirnaja\'s organisation',0,'My address\r\n','Niranjaa','niranja@yahoo.com','Uzbekistan','all facilities','all areas','no comments','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000022','virtusa','Virtusa organisation',0,'virtusa address\r\n','1223445','virtusa@yahoo.com','Venezuela','all facilities','all areas.','no comments.','',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000023','fgfdgfdg','dfgfdg',0,'fdgfdgdsfg\r\n\r\n','46464','test@test.com','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000024','mghmghm','hmghmghmh',0,'\r\nndgfn','4646','fgfd@xg.org','Sri Lanka',NULL,NULL,NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000025','None','None',0,'\r\nNone','4545','none@none.com','Sri Lanka','None','',NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000026','EC','LSF 2',0,'\r\nNone','55555','None@None.com','Rwanda','None','',NULL,'',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000033','abc','abc',0,'\r\nabc\r\n\r\n\r\n','abc','aaa@aa.com','Sri Lanka','asdas','test datd','asdas','Wed Jan 19 09:40:47 LKT 2005',1,'2005-06-13');
INSERT INTO organization VALUES ('Multilateral','','000027','gsaga','adsg',0,'\r\nsdgad','4564','dgd@sdf.com','Sri Lanka',NULL,'','dfgfd','Fri Jan 07 15:34:30 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000028','dffdb','dsfg',0,'\r\ndsbdsb','454','dfgf@xg.com','Sri Lanka','fv','','df','Fri Jan 07 15:53:56 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000029','dffdb','bnbnbn',0,'\r\ndsbdsb','454','dfgf@xg.com','Sri Lanka','fv','','df','Fri Jan 07 15:55:05 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000030','dffdb','Colombo',0,'\r\ndsbdsb','454','dfgf@xg.com','Sri Lanka','fv','','df','Fri Jan 07 15:56:24 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000031','cvcvc','rgfgfb',0,'\r\nvcv','3434','dfd@dfd.com','Sri Lanka','fdf','',NULL,'Fri Jan 07 16:06:27 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000032','Dr Sanjiva','LSF',0,'Colombo University\r\n','2414154','sanjivaw@yahoo.com','Sri Lanka',NULL,'',NULL,'Tue Jan 11 11:47:30 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000034','Autho test','Autho test',0,'\r\nAutho test','56869869898','asdfasdf@vsdvg.com','Sri Lanka','sdfsdssdfsd','',NULL,'Thu Jan 13 16:40:14 LKT 2005',1,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000035','dump','dump',0,'\r\ndump','55555','asfa@adfas.com','Sri Lanka',NULL,'',NULL,'Thu Jan 13 16:42:53 LKT 2005',1,'2005-01-30');
INSERT INTO organization VALUES ('NGO','NGO-INGO','000036',' Untill','Org Untill',0,'\r\n Untill','855555555','asdas@asdas.com','Sri Lanka',NULL,'',NULL,'Mon Jan 17 19:37:18 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000037','asdfshf','Until 2',0,'\r\nsdfsd','sdfsd','sdfsd@sdfsd.com','Sri Lanka',NULL,'','sdfsd','Mon Jan 17 19:40:57 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000038','Until 3','Until 3',0,'\r\nUntil 3','56545454','adsa@asda.com','Sri Lanka',NULL,'','asdas','Mon Jan 17 19:42:43 LKT 2005',1,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000039','gfhgf','gfhfhf',0,'\r\nfhf','hfg','gfhfgf@xfgsdfg.com','Sri Lanka',NULL,'',NULL,'Mon Jan 17 19:44:06 LKT 2005',0,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000040','dump dta','dump dta',0,'dump dta\r\n','dump dta','sd@we.com','Sri Lanka',NULL,'',NULL,'Mon Jan 17 19:45:27 LKT 2005',1,'2005-01-30');
INSERT INTO organization VALUES ('Multilateral','','000041','xcvx','xcvxcv',0,'\r\nvxcvxcv','xcvxc','vxcvxc@sdgdfg.com','Sri Lanka','sdfsd','','sdfsd','Mon Jan 17 19:54:30 LKT 2005',1,'2005-01-30');
INSERT INTO organization VALUES ('Bilateral','','000042','dfd','test1234',0,'\r\nsdfsd\r\n','85232','dfd@we.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 09:50:54 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000043','deepal','error find',0,'\r\ndfsdfs\r\n','545454','asdas@asdas.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 10:32:40 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000044','not specify','new org',0,'\r\nasdasdas\r\n','556554','asdas@asdas.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 13:23:28 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000045','give me org','give me org',0,'\r\ngive me org','9898989989','asdas@sdfsd.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 13:26:47 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000046','deepal123','deepal123',0,'\r\ndeepal123','deepal123','asdas@adfas.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 13:49:39 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000047','Deepal','new Deepal',0,'Deepal\r\n','8522','mama@ccc.com','Sri Lanka',NULL,'',NULL,'Wed Jan 19 15:38:06 LKT 2005',0,'2005-01-19');
INSERT INTO organization VALUES ('Multilateral','','000048','Sanjiva','LSF 123',0,'\r\nasdas','ada','adas@asd.com','Sri Lanka','adas','asdas, asdasdas','asdas','Wed Jan 19 09:42:29 LKT 2005',0,'2005-01-19');

--
-- Table structure for table `organization_district`
--

CREATE TABLE organization_district (
  OrgCode varchar(100) NOT NULL default '',
  DistrictName varchar(100) NOT NULL default '',
  PRIMARY KEY  (DistrictName,OrgCode)
) TYPE=MyISAM;

--
-- Dumping data for table `organization_district`
--

INSERT INTO organization_district VALUES ('000026','Ampara');
INSERT INTO organization_district VALUES ('000028','Ampara');
INSERT INTO organization_district VALUES ('000029','Ampara');
INSERT INTO organization_district VALUES ('000030','Ampara');
INSERT INTO organization_district VALUES ('000041','Ampara');
INSERT INTO organization_district VALUES ('000046','Ampara');
INSERT INTO organization_district VALUES ('000026','Anuradhapura');
INSERT INTO organization_district VALUES ('000026','Badulla');
INSERT INTO organization_district VALUES ('000026','Batticaloa');
INSERT INTO organization_district VALUES ('000026','Colombo');
INSERT INTO organization_district VALUES ('000027','Colombo');
INSERT INTO organization_district VALUES ('000031','Colombo');
INSERT INTO organization_district VALUES ('000035','Colombo');
INSERT INTO organization_district VALUES ('000038','Colombo');
INSERT INTO organization_district VALUES ('000041','Colombo');
INSERT INTO organization_district VALUES ('000026','Galle');
INSERT INTO organization_district VALUES ('000026','Gampaha');
INSERT INTO organization_district VALUES ('000026','Hambantota');
INSERT INTO organization_district VALUES ('000026','Jaffna');
INSERT INTO organization_district VALUES ('000034','Jaffna');
INSERT INTO organization_district VALUES ('000037','Jaffna');
INSERT INTO organization_district VALUES ('000039','Jaffna');
INSERT INTO organization_district VALUES ('000045','Jaffna');
INSERT INTO organization_district VALUES ('000026','Kalutara');
INSERT INTO organization_district VALUES ('000026','Kandy');
INSERT INTO organization_district VALUES ('000026','Kegalle');
INSERT INTO organization_district VALUES ('000026','Kilinochchi');
INSERT INTO organization_district VALUES ('000027','Kilinochchi');
INSERT INTO organization_district VALUES ('000028','Kilinochchi');
INSERT INTO organization_district VALUES ('000029','Kilinochchi');
INSERT INTO organization_district VALUES ('000030','Kilinochchi');
INSERT INTO organization_district VALUES ('000036','Kilinochchi');
INSERT INTO organization_district VALUES ('000039','Kilinochchi');
INSERT INTO organization_district VALUES ('000040','Kilinochchi');
INSERT INTO organization_district VALUES ('000026','Kurunegala');
INSERT INTO organization_district VALUES ('000026','Mannar');
INSERT INTO organization_district VALUES ('000030','Mannar');
INSERT INTO organization_district VALUES ('000026','Matale');
INSERT INTO organization_district VALUES ('000026','Matara');
INSERT INTO organization_district VALUES ('000034','Matara');
INSERT INTO organization_district VALUES ('000026','Monaragala');
INSERT INTO organization_district VALUES ('000026','Mullaitivu');
INSERT INTO organization_district VALUES ('000026','Nuwara_Eliya');
INSERT INTO organization_district VALUES ('000026','Polonnaruwa');
INSERT INTO organization_district VALUES ('000026','Puttalam');
INSERT INTO organization_district VALUES ('000026','Ratnapura');
INSERT INTO organization_district VALUES ('000026','Trincomalee');
INSERT INTO organization_district VALUES ('000026','Vavuniya');
INSERT INTO organization_district VALUES ('000031','Vavuniya');
INSERT INTO organization_district VALUES ('000034','Vavuniya');

--
-- Table structure for table `organization_sector`
--

CREATE TABLE organization_sector (
  OrgCode varchar(100) NOT NULL default '',
  Sector varchar(100) NOT NULL default '',
  PRIMARY KEY  (OrgCode,Sector)
) TYPE=MyISAM;

--
-- Dumping data for table `organization_sector`
--

INSERT INTO organization_sector VALUES ('000032','Health');
INSERT INTO organization_sector VALUES ('000032','Medical');
INSERT INTO organization_sector VALUES ('000032','Transportation');
INSERT INTO organization_sector VALUES ('000033',' Infrastructure');
INSERT INTO organization_sector VALUES ('000034','Water and Sanitation');
INSERT INTO organization_sector VALUES ('000035','Water and Sanitation');
INSERT INTO organization_sector VALUES ('000036','Construction');
INSERT INTO organization_sector VALUES ('000036','Water and Sanitation');
INSERT INTO organization_sector VALUES ('000037','Water and Sanitation');
INSERT INTO organization_sector VALUES ('000038','Water and Sanitation');
INSERT INTO organization_sector VALUES ('000039','Shelter');
INSERT INTO organization_sector VALUES ('000040','Shelter');
INSERT INTO organization_sector VALUES ('000041','Construction');
INSERT INTO organization_sector VALUES ('000044','Water and Sanitation');

--
-- Table structure for table `orgsubtype`
--

CREATE TABLE orgsubtype (
  OrgSubType varchar(20) NOT NULL default '',
  Name varchar(50) NOT NULL default '',
  PRIMARY KEY  (OrgSubType)
) TYPE=MyISAM;

--
-- Dumping data for table `orgsubtype`
--


--
-- Table structure for table `orgtype`
--

CREATE TABLE orgtype (
  OrgType varchar(20) NOT NULL default '',
  Name varchar(50) NOT NULL default '',
  PRIMARY KEY  (OrgType)
) TYPE=MyISAM;

--
-- Dumping data for table `orgtype`
--


--
-- Table structure for table `priority`
--

CREATE TABLE priority (
  Priority varchar(10) NOT NULL default '0',
  Description varchar(20) NOT NULL default '',
  PRIMARY KEY  (Priority)
) TYPE=MyISAM;

--
-- Dumping data for table `priority`
--

INSERT INTO priority VALUES ('1','Immediate (<1 week)');
INSERT INTO priority VALUES ('2','Medium (< 1 mon)');
INSERT INTO priority VALUES ('3','Long Term (1-3 mon)');
INSERT INTO priority VALUES ('4','Long Term (> 3 mon)');

--
-- Table structure for table `relief_disbursement`
--

CREATE TABLE relief_disbursement (
  Id int(11) NOT NULL auto_increment,
  OrgCode varchar(100) NOT NULL default '',
  Category int(11) NOT NULL default '0',
  Quantity int(11) NOT NULL default '0',
  Value int(11) NOT NULL default '0',
  Status int(11) NOT NULL default '0',
  DateCommited date NOT NULL default '0000-00-00',
  DateCompleted date default '0000-00-00',
  Notes varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `relief_disbursement`
--


--
-- Table structure for table `relief_disbursement_issues`
--

CREATE TABLE relief_disbursement_issues (
  ReliefDisbursementId int(11) NOT NULL default '0',
  IssueId int(11) NOT NULL default '0',
  PRIMARY KEY  (ReliefDisbursementId,IssueId)
) TYPE=MyISAM;

--
-- Dumping data for table `relief_disbursement_issues`
--


--
-- Table structure for table `relief_disbursement_sites`
--

CREATE TABLE relief_disbursement_sites (
  ReliefDisbursementId int(11) NOT NULL default '0',
  SiteId int(11) NOT NULL default '0',
  PRIMARY KEY  (ReliefDisbursementId,SiteId)
) TYPE=MyISAM;

--
-- Dumping data for table `relief_disbursement_sites`
--


--
-- Table structure for table `requestdetail`
--

CREATE TABLE requestdetail (
  RequestDetailId int(11) NOT NULL auto_increment,
  RequestId int(11) NOT NULL default '0',
  Category varchar(5) NOT NULL default '',
  Item varchar(100) NOT NULL default '',
  Description varchar(100) default '',
  Unit varchar(10) NOT NULL default '',
  Quantity int(11) NOT NULL default '0',
  Priority varchar(20) NOT NULL default '0',
  Status varchar(10) NOT NULL default '',
  PRIMARY KEY  (RequestDetailId)
) TYPE=MyISAM;

--
-- Dumping data for table `requestdetail`
--

INSERT INTO requestdetail VALUES (96,45,'r','rr',NULL,'tree',100,'1','Closed');
INSERT INTO requestdetail VALUES (97,45,'14','Cement',NULL,'bags',100,'4','Closed');
INSERT INTO requestdetail VALUES (98,45,'1','Food',NULL,'ppl',1000,'1','Closed');
INSERT INTO requestdetail VALUES (99,46,'14','bgdh',NULL,'100',100,'1','Closed');
INSERT INTO requestdetail VALUES (101,47,'6','Night clothes',NULL,'Items',500,'1','Closed');
INSERT INTO requestdetail VALUES (102,48,'7','gwg',NULL,'gw',34,'3','Closed');
INSERT INTO requestdetail VALUES (103,49,'7','gw',NULL,'gw',35,'3','Closed');
INSERT INTO requestdetail VALUES (104,50,'6','A',NULL,'B',300,'2','InProgress');
INSERT INTO requestdetail VALUES (105,51,'3','bag',NULL,'packets',5000,'1','Closed');
INSERT INTO requestdetail VALUES (106,52,'1','value',NULL,'bags',1500,'1','Open');
INSERT INTO requestdetail VALUES (107,53,'15','It',NULL,'T',477,'3','Open');

--
-- Table structure for table `requestfulfill`
--

CREATE TABLE requestfulfill (
  FulfullId int(11) NOT NULL auto_increment,
  OrgCode varchar(10) NOT NULL default '',
  RequestDetailId int(11) NOT NULL default '0',
  ServiceQty int(11) NOT NULL default '0',
  Status varchar(20) NOT NULL default '',
  PRIMARY KEY  (FulfullId),
  KEY FK_RequestFulfill_RequestDetail (RequestDetailId)
) TYPE=MyISAM;

--
-- Dumping data for table `requestfulfill`
--

INSERT INTO requestfulfill VALUES (129,'000001',97,10,'Delivered');
INSERT INTO requestfulfill VALUES (130,'000001',97,10,'Delivered');
INSERT INTO requestfulfill VALUES (131,'000001',97,80,'Delivered');
INSERT INTO requestfulfill VALUES (132,'000001',97,1,'Delivered');
INSERT INTO requestfulfill VALUES (133,'000001',97,8,'Delivered');
INSERT INTO requestfulfill VALUES (134,'000001',98,450,'Delivered');
INSERT INTO requestfulfill VALUES (135,'000001',98,46,'Delivered');
INSERT INTO requestfulfill VALUES (136,'000001',98,36,'Delivered');
INSERT INTO requestfulfill VALUES (137,'000001',98,450,'Delivered');
INSERT INTO requestfulfill VALUES (138,'000001',98,18,'Delivered');
INSERT INTO requestfulfill VALUES (139,'000001',97,1,'Delivered');
INSERT INTO requestfulfill VALUES (140,'000001',99,50,'Delivered');
INSERT INTO requestfulfill VALUES (141,'000001',99,25,'Delivered');
INSERT INTO requestfulfill VALUES (142,'000001',99,15,'Delivered');
INSERT INTO requestfulfill VALUES (143,'000001',99,10,'Delivered');
INSERT INTO requestfulfill VALUES (144,'000001',96,100,'Delivered');
INSERT INTO requestfulfill VALUES (145,'000001',101,400,'Delivered');
INSERT INTO requestfulfill VALUES (146,'000001',101,100,'Delivered');
INSERT INTO requestfulfill VALUES (147,'000001',102,30,'Delivered');
INSERT INTO requestfulfill VALUES (148,'000001',102,3,'Under Consideration');
INSERT INTO requestfulfill VALUES (149,'000001',103,25,'Delivered');
INSERT INTO requestfulfill VALUES (150,'000001',103,10,'Under Consideration');
INSERT INTO requestfulfill VALUES (151,'000001',104,100,'On Route');
INSERT INTO requestfulfill VALUES (152,'000001',105,1000,'Delivered');
INSERT INTO requestfulfill VALUES (153,'000001',105,4000,'Delivered');

--
-- Table structure for table `requestheader`
--

CREATE TABLE requestheader (
  SiteContact varchar(50) default '',
  RequestId int(11) NOT NULL auto_increment,
  OrgCode varchar(10) NOT NULL default '',
  CreateDate date NOT NULL default '0000-00-00',
  RequestDate date NOT NULL default '0000-00-00',
  CallerName varchar(50) NOT NULL default '',
  CallerAddress varchar(100) NOT NULL default '',
  CallerContactNo varchar(50) default '',
  Description varchar(200) default '',
  SiteType varchar(20) NOT NULL default '',
  SiteDistrict varchar(5) NOT NULL default '',
  SiteArea varchar(50) default '',
  SiteName varchar(50) default '',
  PRIMARY KEY  (RequestId)
) TYPE=MyISAM;

--
-- Dumping data for table `requestheader`
--

INSERT INTO requestheader VALUES ('',45,'000001','2005-01-04','2005-01-04','Chandika','123123','123','','','AMP','','Amparamain');
INSERT INTO requestheader VALUES ('',46,'000001','2005-01-05','2005-01-05','Srinath','C','he','thrt','','GMP','','34');
INSERT INTO requestheader VALUES ('',47,'000001','2005-01-05','2005-01-05','test','test','test','test','','AMP','test','test');
INSERT INTO requestheader VALUES ('',48,'000001','2005-01-06','2005-01-06','geg','gegre','geg','gwgw','','CMB','gwegw','gerg');
INSERT INTO requestheader VALUES ('',49,'000001','2005-01-06','2005-01-06','ertre','gaegyr','eyhe','gwg','','BAD','gw','gwg');
INSERT INTO requestheader VALUES ('',50,'000001','2005-01-11','2005-01-11','Ajith','MT, Lavinia','2345675','','','GAL','N03, ABC Rd, CDF','Up2');
INSERT INTO requestheader VALUES ('',51,'000001','2005-01-11','2005-01-11','Deepal','Unv of Moratuwa','07773453635','ryujryjtyuty','4','AMP','ryur','unv');
INSERT INTO requestheader VALUES ('Contact',52,'000001','2005-01-11','2005-01-11','Ajith Ranabahu','Mt Lavinaia','01123456789','eger','4','AMP','AD','MT');
INSERT INTO requestheader VALUES ('564756788',53,'000001','2005-01-12','2005-01-12','Ajith Ranabahu','ABC','2436457567','AC','4','AMP','B','A');

--
-- Table structure for table `requeststatus`
--

CREATE TABLE requeststatus (
  Status varchar(10) NOT NULL default '',
  Description varchar(10) NOT NULL default ''
) TYPE=MyISAM;

--
-- Dumping data for table `requeststatus`
--

INSERT INTO requeststatus VALUES ('InProgress','Progress');
INSERT INTO requeststatus VALUES ('Closed','Closed');
INSERT INTO requeststatus VALUES ('Open','Open');

--
-- Table structure for table `requestunit`
--

CREATE TABLE requestunit (
  Unit varchar(10) NOT NULL default '0',
  PRIMARY KEY  (Unit)
) TYPE=MyISAM;

--
-- Dumping data for table `requestunit`
--


--
-- Table structure for table `school`
--

CREATE TABLE school (
  Id int(11) NOT NULL auto_increment,
  DistrictCode varchar(100) default '',
  Division varchar(100) default '',
  GSN varchar(100) default '',
  Name varchar(100) default '',
  PermanentAddress varchar(100) default '',
  CurrentAddress varchar(100) default '',
  NoOfStudents int(11) default '0',
  NoOfTeachers int(11) default '0',
  NoOfGrades int(11) default '0',
  NoOfClassRooms int(11) default '0',
  NoOfDamagedClassRooms int(11) default '0',
  OtherDamages varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `school`
--


--
-- Table structure for table `school_facility_info`
--

CREATE TABLE school_facility_info (
  Id int(11) NOT NULL auto_increment,
  SchoolId int(11) NOT NULL default '0',
  FacilityName varchar(100) default '',
  Description varchar(100) default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `school_facility_info`
--


--
-- Table structure for table `site`
--

CREATE TABLE site (
  Id int(11) NOT NULL auto_increment,
  DistrictCode varchar(100) NOT NULL default '',
  PRIMARY KEY  (Id)
) TYPE=MyISAM;

--
-- Dumping data for table `site`
--


--
-- Table structure for table `sitetype`
--

CREATE TABLE sitetype (
  SiteTypeCode varchar(10) NOT NULL default '',
  SiteType varchar(20) NOT NULL default '',
  PRIMARY KEY  (SiteTypeCode)
) TYPE=MyISAM;

--
-- Dumping data for table `sitetype`
--

INSERT INTO sitetype VALUES ('1','Hospital');
INSERT INTO sitetype VALUES ('2','Place of Worship');
INSERT INTO sitetype VALUES ('3','Camp');
INSERT INTO sitetype VALUES ('4','School');

--
-- Table structure for table `t1`
--

CREATE TABLE t1 (
  date datetime NOT NULL default '0000-00-00 00:00:00',
  f1 int(11) NOT NULL default '0',
  f2 int(11) NOT NULL auto_increment,
  f3 varchar(100) NOT NULL default '',
  PRIMARY KEY  (f1,f2)
) TYPE=MyISAM;

--
-- Dumping data for table `t1`
--

INSERT INTO t1 VALUES ('0000-00-00 00:00:00',2,1,'dfdf');
INSERT INTO t1 VALUES ('0000-00-00 00:00:00',2,2,'fdferfd');

--
-- Table structure for table `t2`
--

CREATE TABLE t2 (
  ff1 int(11) NOT NULL default '0',
  ff2 int(11) NOT NULL default '0',
  ff3 varchar(100) NOT NULL default ''
) TYPE=MyISAM;

--
-- Dumping data for table `t2`
--


--
-- Table structure for table `t3`
--

CREATE TABLE t3 (
  ff1 int(11) NOT NULL default '0',
  ff2 int(11) NOT NULL default '0',
  ff3 varchar(100) NOT NULL default '',
  KEY ff1 (ff1,ff2)
) TYPE=MyISAM;

--
-- Dumping data for table `t3`
--


--
-- Table structure for table `tblaccesslevels`
--

CREATE TABLE tblaccesslevels (
  AccessLevels varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccesslevels`
--

INSERT INTO tblaccesslevels VALUES ('PAGE');
INSERT INTO tblaccesslevels VALUES ('ADD');
INSERT INTO tblaccesslevels VALUES ('EDIT');
INSERT INTO tblaccesslevels VALUES ('DELETE');
INSERT INTO tblaccesslevels VALUES ('SEARCH');

--
-- Table structure for table `tblaccessmodules`
--

CREATE TABLE tblaccessmodules (
  ModuleId int(11) default NULL,
  ModuleName varchar(50) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccessmodules`
--

INSERT INTO tblaccessmodules VALUES (1,'Assistance Database');
INSERT INTO tblaccessmodules VALUES (2,'Request Management System');
INSERT INTO tblaccessmodules VALUES (6,'Users');
INSERT INTO tblaccessmodules VALUES (7,'Roles');
INSERT INTO tblaccessmodules VALUES (8,'Access Permissions');
INSERT INTO tblaccessmodules VALUES (3,'Camp Registration');
INSERT INTO tblaccessmodules VALUES (4,'Organizations');

--
-- Table structure for table `tblaccesspermissions`
--

CREATE TABLE tblaccesspermissions (
  ModuleId int(11) default NULL,
  AccessLevel varchar(20) default NULL,
  Permission char(1) default NULL,
  RoleId int(11) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblaccesspermissions`
--

INSERT INTO tblaccesspermissions VALUES (1,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (1,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (1,'SEARCH','Y',1);
INSERT INTO tblaccesspermissions VALUES (2,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (2,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (2,'SEARCH','Y',1);
INSERT INTO tblaccesspermissions VALUES (2,'EDIT','Y',1);
INSERT INTO tblaccesspermissions VALUES (8,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (8,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (6,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (6,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (6,'EDIT','Y',1);
INSERT INTO tblaccesspermissions VALUES (6,'DELETE','Y',1);
INSERT INTO tblaccesspermissions VALUES (3,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (3,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (3,'EDIT','Y',1);
INSERT INTO tblaccesspermissions VALUES (3,'SEARCH','Y',1);
INSERT INTO tblaccesspermissions VALUES (7,'PAGE','Y',1);
INSERT INTO tblaccesspermissions VALUES (7,'ADD','Y',1);
INSERT INTO tblaccesspermissions VALUES (7,'EDIT','Y',1);
INSERT INTO tblaccesspermissions VALUES (7,'DELETE','Y',1);
INSERT INTO tblaccesspermissions VALUES (4,'EDIT','Y',1);
INSERT INTO tblaccesspermissions VALUES (2,'PAGE','Y',2);
INSERT INTO tblaccesspermissions VALUES (2,'ADD','Y',2);
INSERT INTO tblaccesspermissions VALUES (2,'SEARCH','Y',2);
INSERT INTO tblaccesspermissions VALUES (2,'EDIT','Y',2);
INSERT INTO tblaccesspermissions VALUES (4,'EDIT','Y',2);

--
-- Table structure for table `tblauditlog`
--

CREATE TABLE tblauditlog (
  UserName varchar(100) NOT NULL default '',
  ModuleId int(11) NOT NULL default '0',
  AccessLevel varchar(100) NOT NULL default '',
  AccessDateTime varchar(100) NOT NULL default ''
) TYPE=MyISAM;

--
-- Dumping data for table `tblauditlog`
--

INSERT INTO tblauditlog VALUES ('HAL',4,'Login','19-01-2005 09:35');
INSERT INTO tblauditlog VALUES ('HAL',4,'EDIT','19-01-2005 09:35');
INSERT INTO tblauditlog VALUES ('HAL',4,'Login','19-01-2005 09:36');
INSERT INTO tblauditlog VALUES ('HAL',4,'EDIT','19-01-2005 09:36');
INSERT INTO tblauditlog VALUES ('HAL',4,'EDIT','19-01-2005 09:38');
INSERT INTO tblauditlog VALUES ('HAL',4,'Login','19-01-2005 09:40');
INSERT INTO tblauditlog VALUES ('HAL',4,'EDIT','19-01-2005 09:40');
INSERT INTO tblauditlog VALUES ('HAL',4,'Login','19-01-2005 09:40');
INSERT INTO tblauditlog VALUES ('HAL',4,'EDIT','19-01-2005 09:40');
INSERT INTO tblauditlog VALUES ('sanjiva',4,'Login','19-01-2005 09:42');
INSERT INTO tblauditlog VALUES ('sanjiva',4,'EDIT','19-01-2005 09:42');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 16:44');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 16:44');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 16:45');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 16:45');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 16:57');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 16:57');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 17:00');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 17:00');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 17:46');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 17:46');
INSERT INTO tblauditlog VALUES ('HAL',2,'ADD','27-01-2005 17:46');
INSERT INTO tblauditlog VALUES ('HAL',2,'SEARCH','27-01-2005 17:46');
INSERT INTO tblauditlog VALUES ('HAL',2,'SEARCH','27-01-2005 17:46');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 17:57');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 17:57');
INSERT INTO tblauditlog VALUES ('HAL',2,'ADD','27-01-2005 17:57');
INSERT INTO tblauditlog VALUES ('HAL',2,'Login','27-01-2005 17:59');
INSERT INTO tblauditlog VALUES ('HAL',2,'PAGE','27-01-2005 17:59');
INSERT INTO tblauditlog VALUES ('HAL',2,'ADD','27-01-2005 17:59');
INSERT INTO tblauditlog VALUES ('HAL',2,'SEARCH','27-01-2005 17:59');

--
-- Table structure for table `tblmoduleaccesslevels`
--

CREATE TABLE tblmoduleaccesslevels (
  ModuleId int(11) default NULL,
  AccessLevel varchar(20) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblmoduleaccesslevels`
--

INSERT INTO tblmoduleaccesslevels VALUES (1,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (1,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (1,'SEARCH');
INSERT INTO tblmoduleaccesslevels VALUES (2,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (2,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (2,'SEARCH');
INSERT INTO tblmoduleaccesslevels VALUES (6,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (6,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (6,'EDIT');
INSERT INTO tblmoduleaccesslevels VALUES (6,'DELETE');
INSERT INTO tblmoduleaccesslevels VALUES (7,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (7,'EDIT');
INSERT INTO tblmoduleaccesslevels VALUES (7,'DELETE');
INSERT INTO tblmoduleaccesslevels VALUES (7,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (8,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (8,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (2,'EDIT');
INSERT INTO tblmoduleaccesslevels VALUES (3,'PAGE');
INSERT INTO tblmoduleaccesslevels VALUES (3,'ADD');
INSERT INTO tblmoduleaccesslevels VALUES (3,'EDIT');
INSERT INTO tblmoduleaccesslevels VALUES (3,'SEARCH');
INSERT INTO tblmoduleaccesslevels VALUES (4,'EDIT');

--
-- Table structure for table `tblroles`
--

CREATE TABLE tblroles (
  RoleId int(11) default NULL,
  RoleName varchar(30) default NULL,
  Description varchar(100) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tblroles`
--

INSERT INTO tblroles VALUES (1,'Administrator','the boss');
INSERT INTO tblroles VALUES (2,'User','the average user');

--
-- Table structure for table `tbluserroles`
--

CREATE TABLE tbluserroles (
  RoleId int(11) default NULL,
  UserName varchar(30) default NULL
) TYPE=MyISAM;

--
-- Dumping data for table `tbluserroles`
--

INSERT INTO tbluserroles VALUES (2,'567');
INSERT INTO tbluserroles VALUES (2,'a');
INSERT INTO tbluserroles VALUES (2,'aa');
INSERT INTO tbluserroles VALUES (2,'adoado');
INSERT INTO tbluserroles VALUES (2,'Ajith');
INSERT INTO tbluserroles VALUES (2,'ampara');
INSERT INTO tbluserroles VALUES (2,'aruny');
INSERT INTO tbluserroles VALUES (2,'asd');
INSERT INTO tbluserroles VALUES (2,'asdfg');
INSERT INTO tbluserroles VALUES (2,'axsd');
INSERT INTO tbluserroles VALUES (2,'cmendis');
INSERT INTO tbluserroles VALUES (2,'d');
INSERT INTO tbluserroles VALUES (2,'ddd');
INSERT INTO tbluserroles VALUES (2,'dddddddddddddddddddd');
INSERT INTO tbluserroles VALUES (2,'ddfdsfsdfsd');
INSERT INTO tbluserroles VALUES (2,'deepal');
INSERT INTO tbluserroles VALUES (2,'deepal123');
INSERT INTO tbluserroles VALUES (2,'dump');
INSERT INTO tbluserroles VALUES (2,'err');
INSERT INTO tbluserroles VALUES (2,'fff');
INSERT INTO tbluserroles VALUES (2,'fffffffffffffff');
INSERT INTO tbluserroles VALUES (2,'frc');
INSERT INTO tbluserroles VALUES (2,'HAL');
INSERT INTO tbluserroles VALUES (2,'hemal');
INSERT INTO tbluserroles VALUES (2,'hemal1');
INSERT INTO tbluserroles VALUES (2,'hfh');
INSERT INTO tbluserroles VALUES (2,'jan');
INSERT INTO tbluserroles VALUES (2,'janagan');
INSERT INTO tbluserroles VALUES (2,'jdk');
INSERT INTO tbluserroles VALUES (2,'john');
INSERT INTO tbluserroles VALUES (2,'kalpana');
INSERT INTO tbluserroles VALUES (2,'kema');
INSERT INTO tbluserroles VALUES (2,'leads');
INSERT INTO tbluserroles VALUES (2,'ma');
INSERT INTO tbluserroles VALUES (2,'mama');
INSERT INTO tbluserroles VALUES (2,'nccsl');
INSERT INTO tbluserroles VALUES (2,'niranjaa');
INSERT INTO tbluserroles VALUES (2,'nithya');
INSERT INTO tbluserroles VALUES (2,'none');
INSERT INTO tbluserroles VALUES (2,'poiu');
INSERT INTO tbluserroles VALUES (2,'qqqq');
INSERT INTO tbluserroles VALUES (2,'qw');
INSERT INTO tbluserroles VALUES (2,'qwertyuiop1234567890');
INSERT INTO tbluserroles VALUES (2,'rr');
INSERT INTO tbluserroles VALUES (2,'rrrr');
INSERT INTO tbluserroles VALUES (2,'rrrrrrrr');
INSERT INTO tbluserroles VALUES (2,'s');
INSERT INTO tbluserroles VALUES (2,'sd');
INSERT INTO tbluserroles VALUES (2,'sdf');
INSERT INTO tbluserroles VALUES (2,'sdfsd');
INSERT INTO tbluserroles VALUES (2,'srirha');
INSERT INTO tbluserroles VALUES (2,'ss');
INSERT INTO tbluserroles VALUES (2,'ssdsds');
INSERT INTO tbluserroles VALUES (2,'ssff');
INSERT INTO tbluserroles VALUES (2,'ssssssssssssssss');
INSERT INTO tbluserroles VALUES (2,'test');
INSERT INTO tbluserroles VALUES (2,'Untill');
INSERT INTO tbluserroles VALUES (2,'virtusa');
INSERT INTO tbluserroles VALUES (2,'we');
INSERT INTO tbluserroles VALUES (2,'ww');
INSERT INTO tbluserroles VALUES (2,'ygro');
INSERT INTO tbluserroles VALUES (2,'YYY');
INSERT INTO tbluserroles VALUES (2,'sanjiva');

--
-- Table structure for table `user`
--

CREATE TABLE user (
  UserName varchar(20) NOT NULL default '',
  Password varchar(100) NOT NULL default '0',
  OrgCode varchar(20) NOT NULL default '',
  PRIMARY KEY  (UserName),
  KEY OrgCode (OrgCode)
) TYPE=MyISAM;

--
-- Dumping data for table `user`
--

INSERT INTO user VALUES ('HAL','123','000033');
INSERT INTO user VALUES ('john','C20AD4D76FE97759AA27A0C99BFF6710','000002');
INSERT INTO user VALUES ('frc','frc','000003');
INSERT INTO user VALUES ('hfh','hfh','000004');
INSERT INTO user VALUES ('nccsl','nccsl','000005');
INSERT INTO user VALUES ('ygro','ygro','000006');
INSERT INTO user VALUES ('leads','leads','000007');
INSERT INTO user VALUES ('cmendis','cmendis','000008');
INSERT INTO user VALUES ('test','test','000009');
INSERT INTO user VALUES ('janagan','a','000030');
INSERT INTO user VALUES ('sdfsd','qq','000011');
INSERT INTO user VALUES ('ww','w','000012');
INSERT INTO user VALUES ('ss','ss','000121');
INSERT INTO user VALUES ('ssssssssssssssss','ss','000122');
INSERT INTO user VALUES ('fffffffffffffff','ff','000123');
INSERT INTO user VALUES ('ddfdsfsdfsd','qq','000124');
INSERT INTO user VALUES ('qw','ww','000125');
INSERT INTO user VALUES ('jan','jan','000001');
INSERT INTO user VALUES ('rr','rr','000009');
INSERT INTO user VALUES ('dddddddddddddddddddd','d','000010');
INSERT INTO user VALUES ('ssff','ss','000011');
INSERT INTO user VALUES ('hemal','hemal','000012');
INSERT INTO user VALUES ('aruny','aruny','000013');
INSERT INTO user VALUES ('kalpana','kalpana','000014');
INSERT INTO user VALUES ('ssdsds','s','000015');
INSERT INTO user VALUES ('d','df','000016');
INSERT INTO user VALUES ('s','s','000017');
INSERT INTO user VALUES ('Ajith','12','000018');
INSERT INTO user VALUES ('srirha','srirha','000019');
INSERT INTO user VALUES ('aa','aa','000002');
INSERT INTO user VALUES ('asd','asd','000040');
INSERT INTO user VALUES ('kema','kema','000020');
INSERT INTO user VALUES ('niranjaa','niranjaa','000021');
INSERT INTO user VALUES ('virtusa','virtusa','000022');
INSERT INTO user VALUES ('hemal1','hemal1','000023');
INSERT INTO user VALUES ('qqqq','qqqq','000024');
INSERT INTO user VALUES ('qwertyuiop1234567890','1234567890qwertyuiopRegister your Orgnisation pageRegister your Orgnisation pageRegister your Orgnis','000025');
INSERT INTO user VALUES ('rrrr','ww','000023');
INSERT INTO user VALUES ('a','x','000024');
INSERT INTO user VALUES ('asdfg','w','000025');
INSERT INTO user VALUES ('axsd','a','000026');
INSERT INTO user VALUES ('ddd','s','000027');
INSERT INTO user VALUES ('fff','s','000028');
INSERT INTO user VALUES ('poiu','m','000029');
INSERT INTO user VALUES ('567','1234','000030');
INSERT INTO user VALUES ('rrrrrrrr','3','000031');
INSERT INTO user VALUES ('err','s','000032');
INSERT INTO user VALUES ('sdf','12','000039');
INSERT INTO user VALUES ('sd','sd','000038');
INSERT INTO user VALUES ('YYY','yyy','000013');
INSERT INTO user VALUES ('ma','ma','000037');
INSERT INTO user VALUES ('ampara','ampara','000034');
INSERT INTO user VALUES ('Untill','12','000036');
INSERT INTO user VALUES ('dump','dump','000035');
INSERT INTO user VALUES ('nithya','nithya','000011');
INSERT INTO user VALUES ('we','12','000041');
INSERT INTO user VALUES ('none','12','000042');
INSERT INTO user VALUES ('deepal','12','000043');
INSERT INTO user VALUES ('jdk','123','000044');
INSERT INTO user VALUES ('adoado','12','000045');
INSERT INTO user VALUES ('deepal123','12','000046');
INSERT INTO user VALUES ('mama','123','000047');
INSERT INTO user VALUES ('sanjiva','foo','000048');


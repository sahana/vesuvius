/**
* This file creates the database structure for the mpres module. The data stored in the one table is a log for what "persons" have been imported into MPR.
* Modules: MPRes
* Last changed: 20090601
*/

DROP TABLE IF EXISTS `mpres_log`;

CREATE table mpres_log (
	log_index       int          NOT NULL AUTO_INCREMENT,
	p_uuid          varchar(64)  NOT NULL,
	email_subject   varchar(256) NOT NULL,
	email_from      varchar(128) NOT NULL,
	email_date      varchar(64)  NOT NULL,
	update_time     datetime     NOT NULL,
	PRIMARY KEY(log_index)
);

DROP TABLE IF EXISTS `mpres_patient`;

CREATE table mpres_patient (
	p_uuid                  varchar(60),
	distributionId          varchar(128),
	sendId                  varchar(128),
	dateTimeSent            varchar(64),
	distributionStatus      varchar(128),
	distributionType        varchar(128),
	combinedConfidentiality varchar(128),
	keyword                 varchar(128),
	targetArea              varchar(128),
	contentDescription      varchar(128),
	version                 varchar(128),
	login                   varchar(128),
	personId                varchar(128),
	eventName               varchar(128),
	orgName                 varchar(128),
	orgId                   varchar(128),
	lastName                varchar(64),
	firstName               varchar(64),
	gender                  varchar(16),
	genderEnum              varchar(32),
	genderEnumDesc          varchar(64),
	peds                    varchar(8),
	pedsEnum                varchar(16),
	pedsEnumDesc            varchar(32),
	triageCategory          varchar(16),
	triageCategoryEnum      varchar(64),
	triageCategoryEnumDesc  varchar(1024),
	lpfFileXmlString        mediumtext,
	lpfArray                mediumblob,
	PRIMARY KEY(p_uuid)
) ENGINE=INNODB;


/*
CREATE table person_location (
	person_location_index   int          PRIMARY KEY   AUTO_INCREMENT   NOT NULL,
	p_uuid                  varchar(64)                                 NOT NULL,
	address_line_1          varchar(128),
	address_line_2          varchar(128),
	city                    varchar(64),
	state                   varchar(64),
	country                 varchar(64),
	postal_code             varchar(64),
	latitude                float(11,8),
	longitude               float(11,8),
)


CREATE TRIGGER person_location_timestamp
AFTER INSERT ON person_location
BEGIN
	UPDATE person_location SET eventtime = datetime('now','localtime') WHERE id = new. id;
END;
*/

/*
"Placemark": [ {
	"id": "p1",
	"address": "Bayside Rd, MD 20685, USA",
	"AddressDetails": {
		"Country": {
			"CountryNameCode": "US",
			"CountryName": "USA",
			"AdministrativeArea": {
				"AdministrativeAreaName": "MD",
				"SubAdministrativeArea": {
					"SubAdministrativeAreaName": "Calvert",
					"Thoroughfare":{
						"ThoroughfareName": "Bayside Rd"
					},
					"PostalCode": {
						"PostalCodeNumber": "20685"
					}
				}
			}
		},
		"Accuracy": 6
	},
	"ExtendedData": {
		"LatLonBox": {
			"north": 38.4653436,
			"south": 38.4590484,
			"east": -76.4665849,
			"west": -76.4728801
		}
	},
	"Point": {
		"coordinates": [ -76.4696180, 38.4622020, 0 ]
	}
} ]
*/


/*
CREATE TABLE "itums" (
	"id" 		INTEGER 	PRIMARY KEY  AUTOINCREMENT  	NOT NULL,
	"name" 		VARCHAR 					NOT NULL,
	"description" 	TEXT,
	"created" 	TIMESTAMP,
	"modified" 	TIMESTAMP
);


CREATE TABLE "priorities" (
	"priority" 	INTEGER 	PRIMARY KEY  AUTOINCREMENT  	NOT NULL,
	"id"	 	INTEGER 					NOT NULL
);


CREATE TABLE "tags" (
	"tag"	 	VARCHAR 	PRIMARY KEY  			NOT NULL,
	"color" 	VARCHAR
);


CREATE TABLE "tags2itums" (
	"id" 		INTEGER 					NOT NULL,
	"tag"	 	VARCHAR 					NOT NULL,
	PRIMARY KEY(id, tag)
);


CREATE TRIGGER createdInsert
AFTER INSERT ON itums
BEGIN
	UPDATE itums SET created = datetime('now','localtime') WHERE id = new. id;
END;


CREATE TRIGGER modifiedInsert
AFTER INSERT ON itums
BEGIN
	UPDATE itums SET modified = datetime('now','localtime') WHERE id = new. id;
END;


CREATE TRIGGER modifiedUpdate
AFTER UPDATE ON itums
BEGIN
	UPDATE itums SET modified = datetime('now','localtime') WHERE id = new. id;
END;
*/
/**
* This file creates the database structure for the mpr PFIF module. 
*
* RATIONALE:
* MPR's PFIF class stores imported records using mpr.add with a p_uuid = PFIF.person_record_identifer. The latest PFIF note
* is used to update the person's status in Sahana, but Sahana provides no mechanism to capture the PFIF note history, and
* some key PFIF data elements can not be bi-directionally mapped to corresponding Sahana elements.
* When internal records are exported to PFIF, certain mapping transformations and date-time stamps are
* generated in accordance with the PFIF specification. Rather than reconstruct the PFIF person and note records
* each time and export is requested, those records are also stored in these tables.
*
* Because there is not a 1:1 mapping between Sahana'a MPR tables and PFIF, the following tables are used
* to track records imported into, and exported from Sahana:
*
*   pfif_repository : identity and charachteristics of PFIF repositories to be harvested or updated
*
*   pfif_log : records collection/export status for PFIF import sources and export targets
*
*   pfif_person : stores the PFIF person element
*
*   pfif_note : stores the PFIF note element
*
* Modules: MPR(PFIF)
* Last changed: 20100303
*
* Revision History:
*    C.Cornwell/Aquilent, Inc., 06-Mar-2010  Incorporate recommended changes from G.Miernicki RE: primary and foreign keys
*                                            and character encoding
*    C.Cornwell/Aquilent, Inc., 03-Mar-2010  Incorporated review comments. Reworked repository and log tables.
*    C.Cornwell/Aquilent, Inc., 01-Mar-2010  Initial release
*
*/
/*
**
** - - - - - - - STRUCTURE - - - - - - - - 
**
*/

DROP TABLE IF EXISTS `pfif_note`;
DROP TABLE IF EXISTS `pfif_person`;
DROP TABLE IF EXISTS `pfif_xml`;
DROP TABLE IF EXISTS `pfif_export_log`;
DROP TABLE IF EXISTS `pfif_harvest_log`;
DROP TABLE IF EXISTS `pfif_repository`;

# Modeled on OAI-PMH Identify response. TODO: How is this info captured when *PL is harvested by an anonymous repository?
CREATE table pfif_repository (
    id              int(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
    name            varchar(100) NOT NULL,
    base_url        varchar(512) NOT NULL,
    role            varchar(6) NOT NULL,     # source or sink
    granularity     varchar(20) DEFAULT NULL,    # finest granularity supported by repository in format YYYY-MM-DD[Thh[:mm[:ss]]]Z
    deleted_record  varchar(10) DEFAULT 'no',    # how repository supports deleted records: no, persistent, transient
    params          varchar(1000) DEFAULT NULL,  # in-line XML <config>...</config> or file::///path to config file
    sched_interval_minutes int DEFAULT '60', # scheduling interval for import/export
    log_granularity varchar(20) DEFAULT NULL,    # granularity for harvest/export logs in format hh:mm:ss, ex: 00:30:00 (may span several import/export cycles.)
    first_entry     datetime  DEFAULT NULL,       # entry_date of first record harvested or exported
    last_entry      datetime  DEFAULT NULL,       # entry_date of last record harvested or exported
    total_persons   int(11) DEFAULT 0,  # count of person records harvested or exported
    total_notes     int(11) DEFAULT 0  # count of note records harvested or exported
) ENGINE=INNODB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE table pfif_export_log ( # An export is a one-time or periodic upload to another respository that is initiated by *PL 
	log_index       int(11)      NOT NULL AUTO_INCREMENT PRIMARY KEY,
	repository_id   int(11)      DEFAULT 0,
    status          varchar(10)  NOT NULL,  # started, error, completed
    start_mode      varchar(6)   NOT NULL,  # 'manual', 'scheduled' or 'test'
    start_time      datetime     DEFAULT NULL,
    end_time        datetime     DEFAULT NULL,
	first_entry     datetime     NOT NULL,
	last_entry      datetime     NOT NULL,
    person_count    int(11)      NOT NULL,
    note_count      int(11)      NOT NULL,
	KEY `repository_id` (`repository_id`),
    INDEX (`repository_id`),
    FOREIGN KEY (repository_id) REFERENCES `pfif_repository`(`id`) ON UPDATE CASCADE ON DELETE CASCADE
    ) ENGINE=INNODB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

# A harvest from another repository into *PL, or from *PL into another repository upon request
CREATE table pfif_harvest_log (
	log_index       int(11)     NOT NULL AUTO_INCREMENT PRIMARY KEY,
	repository_id   int(11)     DEFAULT '0',
    direction       varchar(3)  NOT NULL DEFAULT 'in',  # 'in' or 'out'
    status          varchar(10) NOT NULL,  # started, error, completed
    start_mode      varchar(10) NOT NULL,  # 'manual', 'scheduled' or 'test'
    start_time      datetime    DEFAULT NULL,
    end_time        datetime    DEFAULT NULL,
	first_entry     datetime    NOT NULL,
	last_entry      datetime    NOT NULL,
    last_count      int(11)     DEFAULT 0, # number of records with time = last_entry (used to set skip count), if 0 and direction = 'in' then last harvest failed since there must be at least 1 entry with time = last_entry
    person_count    int(11)     DEFAULT 0,
    note_count      int(11)     DEFAULT 0,
    person_updates  int(11)     DEFAULT 0,
    images_in       int(11)     DEFAULT 0, # number of images successfully imported (always 0 when direction is 'out')
    images_retried  int(11)     DEFAULT 0, # number of images imported after one or more retries (0 when direction is 'out')
    images_failed   int(11)     DEFAULT 0, # number of images not imported (always 0 when direction is 'out')
	KEY `repository_id` (`repository_id`),
    INDEX (`repository_id`),
    FOREIGN KEY (`repository_id`) REFERENCES `pfif_repository`(`id`) ON UPDATE CASCADE ON DELETE CASCADE
    ) ENGINE=INNODB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

CREATE TABLE IF NOT EXISTS `pfif_xml` (
  `xml_id` INT(11) NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid` varchar(60) NOT NULL,
  `type` varchar(6) NOT NULL default 'person',
  `pfif_version` varchar(3) NOT NULL default '1.2',
  `src_repository_id` int(11) NOT NULL,
  `entry_date` datetime NOT NULL,
  `document` mediumtext NOT NULL #,
  #KEY `src_repository_id` (`src_repository_id`),
  #KEY `p_uuid` (`p_uuid`),
  #INDEX(`src_repository_id`, `p_uuid`),
  #FOREIGN KEY(`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=latin1; # CHARSET=utf8; #AUTO_INCREMENT=1 ???

/*
 * REPLACING THESE TABLES WITh pfif_xml FOR THE TIME BEING (chc 03/10/2010)
CREATE table pfif_person (
    p_uuid              varchar(60)	PRIMARY KEY NOT NULL,
    source_version      varchar(10), # PFIF specification version number of the source document
    source_repository_id   int , # PFIF repository from which record was harvested (may be different from source_url)
    entry_date	        datetime,	
    author_name	        varchar(100),
    author_email	    varchar(100),	
    author_phone	    varchar(100),	
    source_name	        varchar(100),	
    source_date	        datetime,	
    source_url	        varchar(512),	
    first_name	        varchar(100),	
    last_name	        varchar(100),	
    home_city	        varchar(100),
    home_state	        varchar(15), # for PFIF 1.2 identifies a principal subdivision of the home country using an uppercase ISO 3166-2 code, for PFIF 1.1 limited to (US) postal abbreviations 
    home_country        varchar(2), # PFIF 1.2 only: two-letter ISO 3166-1 country code
    home_neighborhood	varchar(100),	
    home_street	        varchar(100),	
    home_postal_code    integer,	# emitted as home_zip for PFIF 1.1
    photo_url	        varchar(512),
    sex                 varchar(10), # PFIF 1.2 only : female, male, other, or NULL
    date_of_birth       date,        # PFIF 1.2 only : YYYY-MM-DD, YYYY-MM or YYYY
    age                 varchar(10), # PFIF 1.2 only : NN or NN-NN
    other	            text,
    export_author_info  boolean DEFAULT FALSE, # Indicates whether author wishes contact info to be shared with other respositories 
    /*
            *  Deleting a Person record will result in deleting all associated notes. 
            *  The Person record can NOT be modified once created. Any requested changes or correction must be made via a NOTE record. If the home repository 
            *  provides an upload service, locally changed content will be forwarded to that repository.            
            * /
    marked_for_delete   boolean,    # Indicates a request for deletion was received from the source repository 
    deleted_by          varchar(30),# Identification of entity requesting deletion (TBD) 
    delete_req_date     datetime,   # Date and time that deletion was reqiestion 
    delete_emit_date    datetime,	# Date delete notification was sent to subscribed repositories. Other requester's will receive an error document 
    FOREIGN KEY (source_repository_id) REFERENCES pfif_repository(id)
) ENGINE=INNODB;

CREATE table pfif_note (
    note_record_id	        varchar(60)	PRIMARY KEY NOT NULL,
    p_uuid                  varchar(60) NOT NULL, # Not emitted if PFIF 1.1 
    source_version          varchar(10), # PFIF specification version number of the source document
    source_repository_id    int ,
    linked_person_record_id	varchar(60) ,# Not emitted if PFIF 1.1 
    entry_date	            datetime,
    author_name	            varchar(100),
    author_email	        varchar(100),	
    author_phone	        varchar(100),	
    source_name	            varchar(100),	
    source_date	            datetime,	
    found	                boolean,
    status                  varchar(20), # PFIF 1.2: information_sought, is_note_author, believed_alive, believed_missing, believed_dead 
    email_of_found_person	varchar(100),
    phone_of_found_person	varchar(100),
    last_known_location	    text	   ,
    text	                text	   ,
    type                    int DEFAULT 0, # -1 = static detail change, 0 = imported, 1 = internal change 
    marked_for_delete       boolean,    # Indicates a request for deletion was received from the source repository 
    deleted_by              varchar(30),# Identification of entity requesting deletion (TBD) 
    delete_req_date         datetime,   # Date and time that deletion was reqiestion 
    delete_emit_date        datetime,	# Date delete notification was sent to subscribed repositories. Other requester's will receive an error document 
    FOREIGN KEY (linked_person_record_id) REFERENCES pfif_person(p_uuid),
    FOREIGN KEY (p_uuid) REFERENCES pfif_person(p_uuid),
    FOREIGN KEY (source_repository_id) REFERENCES pfif_repository(id) ON DELETE CASCADE
) ENGINE=INNODB;
*/

/*
** - - - - - - - DATA - - - - - - - - 
*/

/* USE THESE FOR HEPL AND CEPL*/
INSERT INTO `pfif_repository` (`id`, `name`, `base_url`, `role`, `granularity`, `deleted_record`, `params`, `sched_interval_minutes`, `log_granularity`, `first_entry`, `last_entry`, `total_persons`, `total_notes`) VALUES
(1,'Person Finder: Haiti Earthquake','http://haiticrisis.appspot.com','source','YYYY-MM-DDThh:mm:ssZ',
              'no','<config><service name="googlehaiti"><read><url>api/read</url><param><name>version</name><value>1.2</value></param><param><name>id</name><value>${Pfif_Person.person_record_id}</value></param></read><feed><url>feeds/person</url><param><name>min_entry_date</name><value>20090101T000000Z</value></param><param><name>skip</name><value>0</value></param><param><name>max_results</name><value>100</value></param></feed></service></config>','60','01:00:00', NULL, NULL, 0, 0),
(2,'Person Finder: Haiti Earthquake','http://haiticrisis.appspot.com','sink','YYYY-MM-DDThh:mm:ssZ',
              'no','<config><service name="googlehaiti"><export><url>api/write</url><method>post</method><param><name>auth_key</name><value>fn74g09chf6asa2m</value></param></export></service></config>','120','01:00:00', NULL, NULL, 0, 0),
(3, 'Person Finder: Chile Earthquake', 'http://chilepersonfinder.appspot.com', 'source', 'YYYY-MM-DDThh:mm:ssZ', 'no', '<config><service name="googlechile"><read><url>api/read</url><param><name>version</name><value>1.2</value></param><param><name>id</name><value>${Pfif_Person.person_record_id}</value></param></read><feed><url>feeds/person</url><param><name>min_entry_date</name><value>20100101T000000Z</value></param><param><name>skip</name><value>0</value></param><param><name>max_results</name><value>100</value></param></feed></service></config>', 0, '01:00:00', NULL, NULL, 0, 0),
(4, 'Person Finder: Chile Earthquake', 'http://chilepersonfinder.appspot.com', 'sink', 'YYYY-MM-DDThh:mm:ssZ', 'no', '<config><service name="googlechile"><export><url>api/write</url><method>post</method><param><name>auth_key</name><value>0xf28nsvSVho6L3h</value></param></export></service></config>', 0, '01:00:00', NULL, NULL, 0, 0);

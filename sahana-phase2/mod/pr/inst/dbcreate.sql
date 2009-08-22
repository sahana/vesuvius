
-- -----------------------------------------------------
-- Table pr_address
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_address ;

CREATE  TABLE IF NOT EXISTS pr_address (
  a_uuid VARCHAR(30) NOT NULL ,
  address_type VARCHAR(30) NOT NULL ,
  address VARCHAR(200) NOT NULL ,
  postal_code VARCHAR(30) NOT NULL ,
  location_id VARCHAR(30) NOT NULL ,
  description VARCHAR(100) NULL DEFAULT NULL ,
  PRIMARY KEY (a_uuid) ,
  FOREIGN KEY (address_type ) REFERENCES field_options (option_code )
);

-- -----------------------------------------------------
-- Table pr_address_contacts
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_address_contacts ;

CREATE  TABLE IF NOT EXISTS pr_address_contacts (
  ac_uuid VARCHAR(30) NOT NULL ,
  a_uuid VARCHAR(30) NULL DEFAULT NULL ,
  field_type VARCHAR(30) NULL DEFAULT NULL ,
  field_value VARCHAR(45) NULL DEFAULT NULL ,
  PRIMARY KEY (ac_uuid) ,
  FOREIGN KEY (a_uuid ) REFERENCES pr_address (a_uuid ) ON DELETE CASCADE ON UPDATE CASCADE
);


-- -----------------------------------------------------
-- Table pr_person_address
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_person_address ;

CREATE  TABLE IF NOT EXISTS pr_person_address(
  p_uuid VARCHAR(30) NOT NULL ,
  a_uuid VARCHAR(30) NOT NULL ,
  PRIMARY KEY (p_uuid, a_uuid) ,
  FOREIGN KEY (a_uuid ) REFERENCES pr_address (a_uuid ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (p_uuid ) REFERENCES pr_person (p_uuid ) ON DELETE CASCADE ON UPDATE CASCADE
);

-- -----------------------------------------------------
-- Table pr_person
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_person ;

CREATE  TABLE IF NOT EXISTS pr_person (
  p_uuid VARCHAR(30) NOT NULL ,
  first_name VARCHAR(100) NULL DEFAULT NULL ,
  last_name VARCHAR(100) NULL DEFAULT NULL ,
  middle_name VARCHAR(100) NULL DEFAULT NULL ,
  nick_name VARCHAR(75) NULL DEFAULT NULL ,
  title VARCHAR(30) NULL DEFAULT NULL ,
  birth_date DATE NULL DEFAULT NULL ,
  religion VARCHAR(30) NULL DEFAULT NULL ,
  race VARCHAR(30) NULL DEFAULT NULL ,
  martial_status VARCHAR(30) NULL DEFAULT NULL ,
  gender VARCHAR(30) NULL DEFAULT NULL ,
  occupation VARCHAR(30) NULL DEFAULT NULL ,
  image_id VARCHAR(30) NULL DEFAULT NULL ,
  description VARCHAR(200) NULL DEFAULT NULL ,
  PRIMARY KEY (p_uuid) ,
  FOREIGN KEY (image_id )  REFERENCES pr_image (image_id ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (title ) REFERENCES field_options (option_code ),
  FOREIGN KEY (religion ) REFERENCES field_options (option_code ),
  FOREIGN KEY (race ) REFERENCES field_options (option_code ),
  FOREIGN KEY (martial_status ) REFERENCES field_options (option_code ),
  FOREIGN KEY (gender ) REFERENCES field_options (option_code )
);

-- -----------------------------------------------------
-- Table pr_group
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_group ;

CREATE  TABLE IF NOT EXISTS pr_group (
  g_uuid VARCHAR(30) NOT NULL ,
  group_head_id VARCHAR(30) NOT NULL ,
  group_type VARCHAR(30) NOT NULL ,
  descripton VARCHAR(200) NOT NULL ,
  PRIMARY KEY (g_uuid) ,
  FOREIGN KEY (group_head_id ) REFERENCES pr_person (p_uuid ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (group_type ) REFERENCES field_options (option_code )
);

-- -----------------------------------------------------
-- Table pr_group_member
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_group_member ;

CREATE  TABLE IF NOT EXISTS pr_group_member (
  g_uuid VARCHAR(30) NOT NULL ,
  p_uuid VARCHAR(30) NOT NULL ,
  relationship_type VARCHAR(30) NULL DEFAULT NULL ,
  PRIMARY KEY (g_uuid, p_uuid) ,
  FOREIGN KEY (p_uuid ) REFERENCES pr_person (p_uuid ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (g_uuid ) REFERENCES pr_group (g_uuid ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (relationship_type ) REFERENCES field_options (option_code )
);

-- -----------------------------------------------------
-- Table pr_identity
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_identity ;

CREATE  TABLE IF NOT EXISTS pr_identity (
  i_uuid VARCHAR(30) NOT NULL ,
  identity_type VARCHAR(100) NOT NULL ,
  identity_value VARCHAR(100) NOT NULL ,
  PRIMARY KEY (i_uuid) ,  
  FOREIGN KEY (identity_type ) REFERENCES field_options (option_code )
);


-- -----------------------------------------------------
-- Table pr_identity_individual
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_identity_individual ;

CREATE  TABLE IF NOT EXISTS pr_identity_individual (
  p_uuid VARCHAR(30) NOT NULL ,
  i_uuid VARCHAR(30) NOT NULL ,
  PRIMARY KEY (p_uuid, i_uuid) ,
  FOREIGN KEY (p_uuid ) REFERENCES pr_person (p_uuid ) ON DELETE CASCADE ON UPDATE CASCADE,
  FOREIGN KEY (i_uuid ) REFERENCES pr_identity (i_uuid ) ON DELETE CASCADE ON UPDATE CASCADE
);

-- -----------------------------------------------------
-- Table pr_image
-- -----------------------------------------------------
DROP TABLE IF EXISTS pr_image ;

CREATE  TABLE IF NOT EXISTS pr_image (
  image_id VARCHAR(30) NOT NULL ,
  image MEDIUMBLOB NULL DEFAULT NULL ,
  image_type VARCHAR(10) NULL DEFAULT NULL ,
  height TINYINT(4) NULL DEFAULT NULL ,
  width TINYINT(4) NULL DEFAULT NULL ,
  description VARCHAR(100) NULL DEFAULT NULL ,
  PRIMARY KEY (image_id) 
);



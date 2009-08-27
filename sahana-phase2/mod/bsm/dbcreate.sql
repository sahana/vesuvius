SET storage_engine=InnoDB;


-- -----------------------------------------------------
-- Table `gis_feature`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `gis_feature` ;

CREATE  TABLE IF NOT EXISTS `gis_feature` (
  `feature_uuid` VARCHAR(60) NOT NULL ,
  `poc_uuid` VARCHAR(60) NOT NULL ,
  `feature_coords` GEOMETRY NOT NULL ,
  `entry_time` TIMESTAMP NOT NULL ,
  PRIMARY KEY (`feature_uuid`) )
  ENGINE=InnoDB;


-- -----------------------------------------------------
-- Table `bsm_address`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_address` ;

CREATE  TABLE IF NOT EXISTS `bsm_address` (
  `addr_uuid` VARCHAR(60) NOT NULL  ,
  `addr_type` VARCHAR(60) NULL DEFAULT NULL ,
  `addr_status` VARCHAR(60) NULL DEFAULT NULL ,
  `line_1` VARCHAR(200) NULL DEFAULT NULL ,
  `line_2` VARCHAR(200) NULL DEFAULT NULL ,
  `cty_twn_vil` VARCHAR(60) NULL DEFAULT NULL ,
  `post_code` VARCHAR(20) NULL DEFAULT NULL COMMENT 'zip code' ,
  `district` VARCHAR(60) NULL DEFAULT NULL ,
  `state_prov` VARCHAR(60) NULL DEFAULT NULL ,
  `country` VARCHAR(60) NULL DEFAULT NULL ,
  `loc_id` VARCHAR(60) NULL DEFAULT NULL ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(100) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  `gis_id` VARCHAR(60) NULL DEFAULT NULL ,
  PRIMARY KEY (`addr_uuid`) ,
  FOREIGN KEY (`gis_id` ) REFERENCES `gis_feature` (`feature_uuid` )
  )ENGINE=InnoDB;

-- -----------------------------------------------------
-- Table `bsm_addr_lukup_elmnt`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_addr_lukup_elmnt` ;

CREATE  TABLE IF NOT EXISTS `bsm_addr_lukup_elmnt` (
  `elmnt_uuid` VARCHAR(60) NOT NULL COMMENT 'record uuid' ,
  `elmnt_name` VARCHAR(60) NULL DEFAULT NULL COMMENT 'name of country, prov, or dist, ' ,
  `elmnt_prnt_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'id the parent e.g. country of a prov' ,
  `elmnt_code` VARCHAR(20) NULL DEFAULT NULL COMMENT 'ISO 2 cntry, state, or postal code or other' ,
  `elmnt_type` VARCHAR(60) NOT NULL COMMENT 'country, province, district, state' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`elmnt_uuid`) )
ENGINE=InnoDB
AUTO_INCREMENT = 6

COMMENT = 'Lookup table to hold address country dist prov names';


-- -----------------------------------------------------
-- Table `bsm_dis_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_dis_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_dis_type` (
  `dis_type` VARCHAR(60) NOT NULL ,
  `dis_type_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`dis_type`) )
ENGINE=InnoDB

COMMENT = 'define case types - maternal, perdiatric, cardiac, ent, '
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_disease`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_disease` ;

CREATE  TABLE IF NOT EXISTS `bsm_disease` (
  `disease` VARCHAR(60) NOT NULL ,
  `dis_enum` INT(10) NULL DEFAULT NULL ,
  `dis_type` VARCHAR(60) NULL DEFAULT NULL ,
  `dis_priority` VARCHAR(60) NULL DEFAULT NULL ,
  `icd_code` VARCHAR(10) NULL DEFAULT NULL ,
  `icd_desc` VARCHAR(200) NULL DEFAULT NULL COMMENT 'ICD code description' ,
  `notes` VARCHAR(200) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'set datetime to deactivate record not delete for referential integrity' ,
  PRIMARY KEY (`disease`) ,
  INDEX fk_bsm_disease_bsm_dis_type (`dis_type` ASC) ,
  CONSTRAINT `fk_bsm_disease_bsm_dis_type`
    FOREIGN KEY (`dis_type` )
    REFERENCES `bsm_dis_type` (`dis_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'list of diseases'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_loc_cate`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_loc_cate` ;

CREATE  TABLE IF NOT EXISTS `bsm_loc_cate` (
  `loc_cate` VARCHAR(60) NOT NULL ,
  `loc_cate_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `loc_cate_enum` INT(10) NULL DEFAULT NULL COMMENT 'enumeration to pass instead of name' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`loc_cate`) )
ENGINE=InnoDB

COMMENT = 'health system, governance system, etc'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_loc_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_loc_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_loc_type` (
  `loc_type` VARCHAR(60) NOT NULL ,
  `loc_cate` VARCHAR(60) NOT NULL ,
  `loc_type_prnt` VARCHAR(60) NULL DEFAULT NULL COMMENT 'parent of location type e.g. MOH division is parent of PHI area' ,
  `type_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `loc_type_enum` INT(10) NOT NULL ,
  `loc_type_shape` VARCHAR(100) NULL DEFAULT NULL COMMENT 'location type shape - point, line, circle, rectangle, polygon' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'deactivate record and not delete to avoid referential integrity' ,
  PRIMARY KEY (`loc_type`) ,
  INDEX fk_bsm_loc_type_bsm_loc_cate (`loc_cate` ASC) ,
  CONSTRAINT `fk_bsm_loc_type_bsm_loc_cate`
    FOREIGN KEY (`loc_cate` )
    REFERENCES `bsm_loc_cate` (`loc_cate` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'health or governance locations'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_location`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_location` ;

CREATE  TABLE IF NOT EXISTS `bsm_location` (
  `loc_uuid` VARCHAR(60) NOT NULL ,
  `loc_prnt_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `loc_name` VARCHAR(60) NOT NULL COMMENT 'location name is mandetory' ,
  `loc_type` VARCHAR(60) NULL DEFAULT NULL ,
  `loc_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `loc_iso_code` VARCHAR(20) NULL DEFAULT NULL COMMENT 'iso location definition' ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(100) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  `gis_id` VARCHAR(60) NULL DEFAULT NULL ,
  PRIMARY KEY (`loc_uuid`) ,
  INDEX fk_bsm_location_bsm_loc_type (`loc_type` ASC) ,
  INDEX fk_bsm_location_gis_feature (`gis_id` ASC) ,
  CONSTRAINT `fk_bsm_location_bsm_loc_type`
    FOREIGN KEY (`loc_type` )
    REFERENCES `bsm_loc_type` (`loc_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_location_gis_feature`
    FOREIGN KEY (`gis_id` )
    REFERENCES `gis_feature` (`feature_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB;


-- -----------------------------------------------------
-- Table `bsm_person`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_person` ;

CREATE  TABLE IF NOT EXISTS `bsm_person` (
  `p_uuid` VARCHAR(60) NOT NULL COMMENT 'unique id for indexing db' ,
  `passport` VARCHAR(60) NULL DEFAULT NULL COMMENT 'passport number or NIC' ,
  `natl_id` VARCHAR(60) NULL DEFAULT NULL ,
  `dr_lic` VARCHAR(60) NULL DEFAULT NULL COMMENT 'driver license' ,
  `empl_id` VARCHAR(60) NULL DEFAULT NULL COMMENT 'health worker employee id',
  `last_name` VARCHAR(100) NULL DEFAULT NULL COMMENT 'Surname or family name' ,
  `first_name` VARCHAR(100) NULL DEFAULT NULL COMMENT 'given first name' ,
  `mi_name` VARCHAR(100) NULL DEFAULT NULL COMMENT 'middle initial or name' ,
  `alias` VARCHAR(100) NULL DEFAULT NULL COMMENT 'other names or alias' ,
  `gender` VARCHAR(20) NULL DEFAULT 'Unknown' COMMENT 'sex = Male, Female, or Unknown' ,
  `desig` VARCHAR(100) NULL DEFAULT 'Unknown' COMMENT 'person designation' ,
  `dep_p_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'dependent person uuid' ,
  `age` INT(11) NULL DEFAULT NULL ,
  `age_grp` VARCHAR(60) NULL DEFAULT NULL COMMENT 'Infant Child Teen Adulacent Adult Elderly' ,
  `dob` DATE NULL DEFAULT NULL COMMENT 'Date of Birth' ,
  `height` DECIMAL(6,4) NULL DEFAULT NULL COMMENT 'meters' ,
  `ht_unit` VARCHAR(100) NULL DEFAULT 'meters' COMMENT 'specify unit of measure' ,
  `weight` DECIMAL(7,4) NULL DEFAULT NULL COMMENT 'kilograms' ,
  `wt_unit` VARCHAR(100) NULL DEFAULT 'kilograms' COMMENT 'weight unit of measure' ,
  `ethicity` VARCHAR(100) NULL DEFAULT 'Unknown' COMMENT 'combination of race and religion' ,
  `loc_id` VARCHAR(60) NULL DEFAULT NULL ,
  `country` VARCHAR(60) NULL DEFAULT 'Unknown' COMMENT 'country of birth or residence' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`p_uuid`) ,
  INDEX fk_bsm_person_bsm_location (`loc_id` ASC) ,
  CONSTRAINT `fk_bsm_person_bsm_location`
    FOREIGN KEY (`loc_id` )
    REFERENCES `bsm_location` (`loc_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB
AUTO_INCREMENT = 6

ROW_FORMAT = COMPACT;




-- -----------------------------------------------------
-- Table `bsm_cases`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_cases` ;

CREATE  TABLE IF NOT EXISTS `bsm_cases` (
  `case_uuid` VARCHAR(60) NOT NULL ,
  `case_dt` DATETIME NOT NULL COMMENT 'date time case was identified may differ from record create datetime' ,
  `pat_p_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'patient prsn_id where prsn_cate = Patient' ,
  `pat_full_name` VARCHAR(200) NULL DEFAULT NULL COMMENT 'patient name must be taken from person table this field is an alternate' ,
  `hwork_p_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'health care worker identifying case fk prsn id taken from person table' ,
  `hwork_full_name` VARCHAR(200) NULL DEFAULT NULL COMMENT 'health care worker such as doctor name must be obtained from person table' ,
  `fclty_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'indicate the facility the case was reported from' ,
  `fclty_name` VARCHAR(200) NULL DEFAULT NULL COMMENT 'facility name same as in table facility' ,
  `loc_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `loc_name` VARCHAR(200) NULL DEFAULT NULL ,
  `disease` VARCHAR(60) NULL DEFAULT NULL COMMENT 'disease name look up from disease table' ,
  `dis_dia_dt` DATETIME NULL DEFAULT NULL COMMENT 'disease diagnosed date time' ,
  `agent` VARCHAR(100) NULL DEFAULT NULL COMMENT 'carrier agent of the disease' ,
  `gender` VARCHAR(20) NULL DEFAULT NULL COMMENT 'patient gender same as in person table' ,
  `age` DECIMAL(5,2) NULL DEFAULT NULL COMMENT 'age of patient same as age defined in person table' ,
  `age_grp` VARCHAR(100) NULL DEFAULT NULL COMMENT 'patient age group same as in person table lookup prsn_age_grp table' ,
  `notes` VARCHAR(200) NULL DEFAULT NULL COMMENT 'keywords or notes' ,
  `mobile_dt` DATETIME NULL DEFAULT NULL COMMENT 'date when record was created on mobile phone',
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(200) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'set time to deactivate record and not delete for referential integrity' ,
  PRIMARY KEY (`case_uuid`) ,
  INDEX case_id (`case_uuid` ASC) ,
  INDEX fk_bsm_cases_bsm_disease (`disease` ASC) ,
  INDEX fk_bsm_cases_health_worker (`hwork_p_uuid` ASC) ,
  INDEX fk_bsm_cases_patient (`pat_p_uuid` ASC) ,
  CONSTRAINT `fk_bsm_cases_bsm_disease`
    FOREIGN KEY (`disease` )
    REFERENCES `bsm_disease` (`disease` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
 )
ENGINE=InnoDB
AUTO_INCREMENT = 4

COMMENT = 'a case is initiated when a patient reports symptoms'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_serv_state`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_serv_state` ;

CREATE  TABLE IF NOT EXISTS `bsm_serv_state` (
  `serv_state` VARCHAR(60) NOT NULL COMMENT 'provides the different states the serive transitions' ,
  `serv_state_seq` INT(5) NULL DEFAULT NULL COMMENT 'set a sequence number' ,
  `serv_status_enum` INT(10) NULL DEFAULT NULL ,
  `serv_status_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT '0000-00-00 00:00:00' ,
  PRIMARY KEY (`serv_state`) )
ENGINE=InnoDB

ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_serv_cate`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_serv_cate` ;

CREATE  TABLE IF NOT EXISTS `bsm_serv_cate` (
  `serv_cate` VARCHAR(100) NOT NULL ,
  `serv_cate_enum` INT(10) NOT NULL ,
  `serv_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`serv_cate`) )
ENGINE=InnoDB

COMMENT = 'service categories for person, cases, facilities'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_serv_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_serv_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_serv_type` (
  `serv_type_enum` INT(10) NOT NULL ,
  `serv_type` VARCHAR(100) NOT NULL ,
  `serv_cate` VARCHAR(100) NOT NULL ,
  `serv_type_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `serv_proc` VARCHAR(200) NULL DEFAULT NULL COMMENT 'description of how service must be carried out' ,
  `serv_prov_prsn_type` VARCHAR(60) NULL DEFAULT NULL ,
  `serv_recp_prsn_type` VARCHAR(60) NULL DEFAULT NULL ,
  `serv_exp_rslt` VARCHAR(200) NULL DEFAULT NULL COMMENT 'expected outcome of the service' ,
  `serv_exp_tm` INT(11) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'deactivate and not delete record for referential integrity' ,
  PRIMARY KEY (`serv_type`) ,
  INDEX fk_bsm_serv_type_bsm_serv_cate (`serv_cate` ASC) ,
  CONSTRAINT `fk_bsm_serv_type_bsm_serv_cate`
    FOREIGN KEY (`serv_cate` )
    REFERENCES `bsm_serv_cate` (`serv_cate` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_service`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_service` ;

CREATE  TABLE IF NOT EXISTS `bsm_service` (
  `serv_uuid` VARCHAR(60) NOT NULL ,
  `serv_type` VARCHAR(60) NULL DEFAULT NULL ,
  `serv_state` VARCHAR(60) NULL DEFAULT NULL ,
  `serv_state_dt` DATETIME NULL DEFAULT NULL ,
  `prov_p_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `recp_p_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `serv_start_dt` DATETIME NULL DEFAULT NULL COMMENT 'date time service was initiated' ,
  `serv_end_dt` DATETIME NULL DEFAULT NULL COMMENT 'date time service was terminated' ,
  `loc_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'location service is executer' ,
  `serv_notes` VARCHAR(200) NULL DEFAULT NULL COMMENT 'other notes in relation to service' ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(100) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'deactivate record and not delete to maintain referential integrity' ,
  PRIMARY KEY (`serv_uuid`) ,
  INDEX fk_bsm_service_bsm_serv_state (`serv_state` ASC) ,
  INDEX fk_bsm_service_bsm_serv_type (`serv_type` ASC) ,
  INDEX fk_bsm_service_bsm_serv_type1 (`serv_type` ASC) ,
  CONSTRAINT `fk_bsm_service_bsm_serv_state`
    FOREIGN KEY (`serv_state` )
    REFERENCES `bsm_serv_state` (`serv_state` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_service_bsm_serv_type`
    FOREIGN KEY (`serv_type` )
    REFERENCES `bsm_serv_type` (`serv_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB
AUTO_INCREMENT = 9

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_case_serv`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_case_serv` ;

CREATE  TABLE IF NOT EXISTS `bsm_case_serv` (
  `case_uuid` VARCHAR(60) NOT NULL ,
  `serv_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'deactivate and not delete record for referential integrity' ,
  UNIQUE INDEX bsm_case_serv_idx (`serv_uuid` ASC, `case_uuid` ASC) ,
  INDEX fk_bsm_case_serv_bsm_cases (`case_uuid` ASC) ,
  INDEX fk_bsm_case_serv_bsm_service (`serv_uuid` ASC) ,
  CONSTRAINT `fk_bsm_case_serv_bsm_cases`
    FOREIGN KEY (`case_uuid` )
    REFERENCES `bsm_cases` (`case_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_case_serv_bsm_service`
    FOREIGN KEY (`serv_uuid` )
    REFERENCES `bsm_service` (`serv_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relate case to services'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_sign`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_sign` ;

CREATE  TABLE IF NOT EXISTS `bsm_sign` (
  `sign` VARCHAR(60) NOT NULL ,
  `sign_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `sign_code` VARCHAR(60) NULL DEFAULT NULL ,
  `sign_priority` VARCHAR(60) NULL DEFAULT NULL ,
  `sign_enum` INT(10) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`sign`) )
ENGINE=InnoDB

COMMENT = 'list of signs'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_case_sign`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_case_sign` ;

CREATE  TABLE IF NOT EXISTS `bsm_case_sign` (
  `case_uuid` VARCHAR(60) NOT NULL ,
  `sign` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`case_uuid`, `sign`) ,
  INDEX fk_bsm_case_sign_bsm_cases (`case_uuid` ASC) ,
  INDEX fk_bsm_case_sign_bsm_sign (`sign` ASC) ,
  CONSTRAINT `fk_bsm_case_sign_bsm_cases`
    FOREIGN KEY (`case_uuid` )
    REFERENCES `bsm_cases` (`case_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_case_sign_bsm_sign`
    FOREIGN KEY (`sign` )
    REFERENCES `bsm_sign` (`sign` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relate signs for a given case'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_case_status`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_case_status` ;

CREATE  TABLE IF NOT EXISTS `bsm_case_status` (
  `case_status` VARCHAR(100) NOT NULL ,
  `case_status_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `case_status_enum` INT(11) NULL DEFAULT NULL COMMENT 'give a number to identify the sequence of status in list' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'to deactivate record insert datetime' ,
  PRIMARY KEY (`case_status`) )
ENGINE=InnoDB

ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_case_status_log`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_case_status_log` ;

CREATE  TABLE IF NOT EXISTS `bsm_case_status_log` (
  `case_uuid` VARCHAR(60) NOT NULL ,
  `case_status` VARCHAR(60) NOT NULL ,
  `auth_p_uuid` VARCHAR(60) NULL DEFAULT NULL COMMENT 'person authorizing the status change id from person table' ,
  `notes` VARCHAR(200) NULL DEFAULT NULL COMMENT 'remarks comments for each status' ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(100) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'deactivate and not delete to maintain referential integrity' ,
  PRIMARY KEY (`case_uuid`, `case_status`) ,
  INDEX fk_bsm_case_status_log_bsm_cases (`case_uuid` ASC) ,
  INDEX fk_bsm_case_status_log_bsm_case_status (`case_status` ASC) ,
  CONSTRAINT `fk_bsm_case_status_log_bsm_cases`
    FOREIGN KEY (`case_uuid` )
    REFERENCES `bsm_cases` (`case_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_case_status_log_bsm_case_status`
    FOREIGN KEY (`case_status` )
    REFERENCES `bsm_case_status` (`case_status` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'history of the status change of a cahse'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_symptom`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_symptom` ;

CREATE  TABLE IF NOT EXISTS `bsm_symptom` (
  `symptom` VARCHAR(60) NOT NULL ,
  `symp_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `symp_code` VARCHAR(60) NULL DEFAULT NULL ,
  `symp_priority` VARCHAR(60) NULL DEFAULT NULL ,
  `symp_enum` INT(10) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`symptom`) )
ENGINE=InnoDB

COMMENT = 'list of symptoms'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_case_symp`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_case_symp` ;

CREATE  TABLE IF NOT EXISTS `bsm_case_symp` (
  `case_uuid` VARCHAR(60) NOT NULL ,
  `symptom` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`case_uuid`, `symptom`) ,
  INDEX fk_bsm_case_symp_bsm_symptom (`symptom` ASC) ,
  INDEX fk_bsm_case_symp_bsm_cases (`case_uuid` ASC) ,
  CONSTRAINT `fk_bsm_case_symp_bsm_symptom`
    FOREIGN KEY (`symptom` )
    REFERENCES `bsm_symptom` (`symptom` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_case_symp_bsm_cases`
    FOREIGN KEY (`case_uuid` )
    REFERENCES `bsm_cases` (`case_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'set of symptoms for each case'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_caus_fact`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_caus_fact` ;

CREATE  TABLE IF NOT EXISTS `bsm_caus_fact` (
  `caus_fact` VARCHAR(60) NOT NULL ,
  `caus_fact_enum` INT(10) NULL DEFAULT NULL ,
  `caus_fact_priority` VARCHAR(60) NULL DEFAULT NULL ,
  `caus_fact_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `caus_fact_code` VARCHAR(60) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`caus_fact`) )
ENGINE=InnoDB

COMMENT = 'source of disease'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_contact`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_contact` ;

CREATE  TABLE IF NOT EXISTS `bsm_contact` (
  `cont_uuid` VARCHAR(60) NOT NULL ,
  `cont_mode` VARCHAR(60) NULL DEFAULT NULL ,
  `cont_val` VARCHAR(200) NULL DEFAULT NULL COMMENT 'corresponding value for particulat type; e.g. cont_type = \'mobile phone\' cont_val = \'5551212\' or cont_type = \'email\' cont_val = \'me@myaddress.domain\'' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`cont_uuid`, `cont_mode`, `cont_val`) )
ENGINE=InnoDB
AUTO_INCREMENT = 3

COMMENT = 'contact details of facilities, persons'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_dis_caus_fact`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_dis_caus_fact` ;

CREATE  TABLE IF NOT EXISTS `bsm_dis_caus_fact` (
  `disease` VARCHAR(60) NOT NULL ,
  `caus_fact` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'set date time to deactivate record do not delete for referential integrity' ,
  PRIMARY KEY (`disease`, `caus_fact`) ,
  INDEX dis_caus_fact (`disease` ASC) ,
  INDEX caus_fact_dis (`caus_fact` ASC) ,
  INDEX fk_bsm_dis_caus_fact_bsm_disease (`disease` ASC) ,
  INDEX fk_bsm_dis_caus_fact_bsm_caus_fact (`caus_fact` ASC) ,
  CONSTRAINT `fk_bsm_dis_caus_fact_bsm_disease`
    FOREIGN KEY (`disease` )
    REFERENCES `bsm_disease` (`disease` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_dis_caus_fact_bsm_caus_fact`
    FOREIGN KEY (`caus_fact` )
    REFERENCES `bsm_caus_fact` (`caus_fact` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relating diseases and causative factors'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_dis_sign`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_dis_sign` ;

CREATE  TABLE IF NOT EXISTS `bsm_dis_sign` (
  `disease` VARCHAR(60) NOT NULL ,
  `sign` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`disease`, `sign`) ,
  INDEX fk_bsm_dis_sign_bsm_disease (`disease` ASC) ,
  INDEX fk_bsm_dis_sign_bsm_sign (`sign` ASC) ,
  CONSTRAINT `fk_bsm_dis_sign_bsm_disease`
    FOREIGN KEY (`disease` )
    REFERENCES `bsm_disease` (`disease` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_dis_sign_bsm_sign`
    FOREIGN KEY (`sign` )
    REFERENCES `bsm_sign` (`sign` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relate diseases to signs from lookup tables'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_dis_symp`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_dis_symp` ;

CREATE  TABLE IF NOT EXISTS `bsm_dis_symp` (
  `disease` VARCHAR(60) NOT NULL ,
  `symptom` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`disease`, `symptom`) ,
  INDEX fk_bsm_dis_symp_bsm_disease (`disease` ASC) ,
  INDEX fk_bsm_dis_symp_bsm_symptom (`symptom` ASC) ,
  CONSTRAINT `fk_bsm_dis_symp_bsm_disease`
    FOREIGN KEY (`disease` )
    REFERENCES `bsm_disease` (`disease` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_dis_symp_bsm_symptom`
    FOREIGN KEY (`symptom` )
    REFERENCES `bsm_symptom` (`symptom` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relate diseases to symptoms, lookup table'
ROW_FORMAT = DYNAMIC;


-- -----------------------------------------------------
-- Table `bsm_fclty_cate`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_fclty_cate` ;

CREATE  TABLE IF NOT EXISTS `bsm_fclty_cate` (
  `fclty_cate` VARCHAR(60) NOT NULL ,
  `fctly_cate_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `fclty_cate_enum` INT(10) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`fclty_cate`) )
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_fclty_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_fclty_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_fclty_type` (
  `fclty_type` VARCHAR(100) NOT NULL ,
  `fclty_cate` VARCHAR(100) NOT NULL ,
  `fclty_type_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `fclty_type_enum` INT(10) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`fclty_type`, `fclty_cate`) ,
  INDEX fk_bsm_fclty_type_bsm_fclty_cate (`fclty_cate` ASC) ,
  CONSTRAINT `fk_bsm_fclty_type_bsm_fclty_cate`
    FOREIGN KEY (`fclty_cate` )
    REFERENCES `bsm_fclty_cate` (`fclty_cate` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_facility`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_facility` ;

CREATE  TABLE IF NOT EXISTS `bsm_facility` (
  `fclty_uuid` VARCHAR(60) NOT NULL ,
  `fclty_type` VARCHAR(60) NULL DEFAULT NULL ,
  `fclty_status` VARCHAR(60) NULL DEFAULT NULL ,
  `fclty_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `loc_uuid` VARCHAR(60) NULL DEFAULT NULL ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(100) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(100) NULL DEFAULT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`fclty_uuid`) ,
  INDEX fk_bsm_facility_bsm_fclty_type (`fclty_type` ASC) ,
  INDEX fk_bsm_facility_bsm_location (`loc_uuid` ASC) ,
  CONSTRAINT `fk_bsm_facility_bsm_fclty_type`
    FOREIGN KEY (`fclty_type` )
    REFERENCES `bsm_fclty_type` (`fclty_type` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_facility_bsm_location`
    FOREIGN KEY (`loc_uuid` )
    REFERENCES `bsm_location` (`loc_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB
AUTO_INCREMENT = 5

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_fclty_addr`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_fclty_addr` ;

CREATE  TABLE IF NOT EXISTS `bsm_fclty_addr` (
  `fclty_uuid` VARCHAR(60) NOT NULL ,
  `addr_uuid` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'to deactivate record insert datetime' ,
  PRIMARY KEY (`fclty_uuid`, `addr_uuid`) ,
  INDEX fk_bsm_fclty_addr_bsm_facility (`fclty_uuid` ASC) ,
  INDEX fk_bsm_fclty_addr_bsm_address (`addr_uuid` ASC) ,
  CONSTRAINT `fk_bsm_fclty_addr_bsm_facility`
    FOREIGN KEY (`fclty_uuid` )
    REFERENCES `bsm_facility` (`fclty_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_fclty_addr_bsm_address`
    FOREIGN KEY (`addr_uuid` )
    REFERENCES `bsm_address` (`addr_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_fclty_serv`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_fclty_serv` ;

CREATE  TABLE IF NOT EXISTS `bsm_fclty_serv` (
  `fclty_uuid` VARCHAR(60) NOT NULL ,
  `serv_uuid` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`fclty_uuid`, `serv_uuid`) ,
  INDEX fk_bsm_fclty_serv_bsm_facility (`fclty_uuid` ASC) ,
  INDEX fk_bsm_fclty_serv_bsm_service (`serv_uuid` ASC) ,
  CONSTRAINT `fk_bsm_fclty_serv_bsm_facility`
    FOREIGN KEY (`fclty_uuid` )
    REFERENCES `bsm_facility` (`fclty_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_fclty_serv_bsm_service`
    FOREIGN KEY (`serv_uuid` )
    REFERENCES `bsm_service` (`serv_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_prsn_addr`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_addr` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_addr` (
  `p_uuid` VARCHAR(60) NOT NULL ,
  `addr_uuid` VARCHAR(60) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`p_uuid`, `addr_uuid`) ,
  INDEX fk_bsm_prsn_addr_bsm_person (`p_uuid` ASC) ,
  INDEX fk_bsm_prsn_addr_bsm_address (`addr_uuid` ASC) ,
  CONSTRAINT `fk_bsm_prsn_addr_bsm_person`
    FOREIGN KEY (`p_uuid` )
    REFERENCES `bsm_person` (`p_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_prsn_addr_bsm_address`
    FOREIGN KEY (`addr_uuid` )
    REFERENCES `bsm_address` (`addr_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'relating table of address and person entities many-to-many'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_prsn_cont`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_cont` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_cont` (
  `p_uuid` VARCHAR(60) NOT NULL ,
  `cont_uuid` VARCHAR(60) NOT NULL ,
  `deactivate-dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`p_uuid`, `cont_uuid`) ,
  INDEX fk_bsm_prsn_cont_bsm_contact (`cont_uuid` ASC) ,
  INDEX fk_bsm_prsn_cont_bsm_person (`p_uuid` ASC) ,
  CONSTRAINT `fk_bsm_prsn_cont_bsm_contact`
    FOREIGN KEY (`cont_uuid` )
    REFERENCES `bsm_contact` (`cont_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_bsm_prsn_cont_bsm_person`
    FOREIGN KEY (`p_uuid` )
    REFERENCES `bsm_person` (`p_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_prsn_role`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_role` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_role` (
  `prsn_role` VARCHAR(60) NOT NULL ,
  `prsn_role_desc` VARCHAR(200) NULL DEFAULT NULL COMMENT 'additional field to describe the catefory' ,
  `prsn_role_enum` INT(10) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`prsn_role`) )
ENGINE=InnoDB

COMMENT = 'person = Healthcare Worker or Patient'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_prsn_state`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_state` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_state` (
  `prsn_state` VARCHAR(60) NOT NULL ,
  `prsn_role` VARCHAR(60) NOT NULL ,
  `prsn_state_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `prsn_state_enum` INT(10) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY ( `prsn_state`) ,
  INDEX fk_bsm_prsn_state_bsm_prsn_role (`prsn_role` ASC) ,
  CONSTRAINT `fk_bsm_prsn_state_bsm_prsn_role`
    FOREIGN KEY (`prsn_role` )
    REFERENCES `bsm_prsn_role` (`prsn_role` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE=InnoDB

COMMENT = 'defines the status of a person in a particular category'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_prsn_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_type` (
  `prsn_type` VARCHAR(60) NOT NULL ,
  `prsn_role` VARCHAR(60) NOT NULL ,
  `prsn_type_desc` VARCHAR(200) NULL DEFAULT NULL ,
  `prsn_type_enum` INT(11) NOT NULL ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL ,
  PRIMARY KEY (`prsn_type`) ,
    FOREIGN KEY (`prsn_role` )
    REFERENCES `bsm_prsn_role` (`prsn_role` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
COMMENT = 'Define a subcategory or type for persons in each category.'
ROW_FORMAT = COMPACT;


-- -----------------------------------------------------
-- Table `bsm_serv_type_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_serv_type_item` ;

CREATE  TABLE IF NOT EXISTS `bsm_serv_type_item` (
  `item_name` VARCHAR(60) NOT NULL COMMENT 'given name for item' ,
  `serv_cate` VARCHAR(60) NOT NULL ,
  `item_desc` VARCHAR(200) NULL DEFAULT NULL COMMENT 'additional descitption' ,
  `item_state` VARCHAR(20) NOT NULL COMMENT 'Input or Output to or of the service' ,
  `deactivate_dt` TIMESTAMP NULL DEFAULT NULL COMMENT 'to remove record but not delete from db' )
ENGINE=InnoDB

COMMENT = 'associate input and output items for a service';


-- -----------------------------------------------------
-- Table `bsm_serv_item`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_serv_item` ;

CREATE  TABLE IF NOT EXISTS `bsm_serv_item` (

  `serv_uuid` VARCHAR(60) NOT NULL COMMENT 'uuid from bsm_service table' ,
  `item_name` VARCHAR(60) NOT NULL COMMENT 'item name from bsm_serv_type_item' ,
  `item_state` VARCHAR(20) NOT NULL COMMENT 'Input or Output item' ,
  `deactivate_dt` DATETIME NULL DEFAULT NULL COMMENT 'remove active status of record but not delete from db' ,
  PRIMARY KEY (item_name),
  INDEX fk_bsm_serv_item_bsm_service (`serv_uuid` ASC) ,
  INDEX fk_bsm_serv_item_bsm_serv_type_item (`item_name` ASC) ,
  
  CONSTRAINT `fk_bsm_serv_item_bsm_service`
    FOREIGN KEY (`serv_uuid` )
    REFERENCES `bsm_service` (`serv_uuid` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION
    )
ENGINE=InnoDB

COMMENT = 'service item details related to bsm_service table';


-- -----------------------------------------------------
-- Table `field_options`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `field_options` ;

CREATE  TABLE IF NOT EXISTS `field_options` (
  `field_name` VARCHAR(100) NULL DEFAULT NULL ,
  `option_code` VARCHAR(20) NULL DEFAULT NULL ,
  `option_description` VARCHAR(50) NULL DEFAULT NULL )
ENGINE=InnoDB
;


-- -----------------------------------------------------
-- Table `bsm_management_data`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_management_data` ;

CREATE  TABLE IF NOT EXISTS `bsm_management_data` (
  `record_number` VARCHAR(60) NOT NULL ,
  `table_name` VARCHAR(100) NOT NULL ,
  `create_dt` TIMESTAMP NOT NULL ,
  `create_by` VARCHAR(100) NOT NULL ,
  `create_proc` VARCHAR(200) NOT NULL ,
  `modify_dt` DATETIME NULL DEFAULT NULL ,
  `modify_by` VARCHAR(100) NULL DEFAULT NULL ,
  `modify_proc` VARCHAR(200) NULL DEFAULT NULL ,
  PRIMARY KEY (`record_number`, `table_name`) );


-- -----------------------------------------------------
-- Table `bsm_prsn_link_type`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `bsm_prsn_link_type` ;

CREATE  TABLE IF NOT EXISTS `bsm_prsn_link_type` (
  `p_uuid` VARCHAR(60) NOT NULL ,
  `prsn_type` VARCHAR(60) NOT NULL ,
  `prsn_state` VARCHAR(60) NOT NULL ,
  PRIMARY KEY (`p_uuid`, `prsn_type`) ,
    FOREIGN KEY (`p_uuid` )     REFERENCES `bsm_person` (`p_uuid` ),
    FOREIGN KEY (`prsn_type` )     REFERENCES `bsm_prsn_type` (`prsn_type` ),
    FOREIGN KEY (`prsn_state` )     REFERENCES `bsm_prsn_state` (`prsn_state` )
    
    );




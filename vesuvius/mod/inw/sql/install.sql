-- 
-- This Query is used to load up SOLR's index -- preliminary filtering is done here.
--
CREATE ALGORITHM=UNDEFINED VIEW `person_search` 
AS select `pu`.`p_uuid` AS `p_uuid`,
`pu`.`full_name` AS `full_name`,
`pu`.`given_name` AS `given_name`,
`pu`.`family_name` AS `family_name`,
(CASE WHEN `ps`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk', 'fnd') OR `ps`.`opt_status` IS NULL THEN 'unk' ELSE `ps`.`opt_status` END) AS `opt_status`,
(CASE WHEN `ps`.`last_updated` < `upd`.`update_time` THEN `upd`.`update_time` ELSE `ps`.`last_updated` END) AS `updated`,
(CASE WHEN `pd`.`opt_gender` NOT IN ('mal', 'fml') OR `pd`.`opt_gender` IS NULL THEN 'unk' ELSE `pd`.`opt_gender` END) AS `opt_gender`,
(CASE WHEN CONVERT(`pd`.`years_old`, UNSIGNED INTEGER) IS NULL THEN -1 ELSE `pd`.`years_old` END) AS `years_old`,
`i`.`image_height` AS `image_height`,
`i`.`image_width` AS `image_width`,
`i`.`url_thumb` AS `url_thumb`,
(case when (`h`.`hospital_uuid` = -(1)) then NULL else `h`.`icon_url` end) AS `icon_url`,
`inc`.`shortname` AS `shortname`,
(CASE WHEN `h`.`short_name` NOT IN ('sh', 'nnmc') OR `h`.`short_name` IS NULL THEN 'public' ELSE `h`.`short_name` END) AS `hospital`,
`pd`.`other_comments` AS `comments`,
`pd`.`last_seen` AS `last_seen` 
from `person_uuid` `pu` join `person_status` `ps` on (`pu`.`p_uuid` = `ps`.`p_uuid` and `ps`.`isvictim` = 1 and (`pu`.`expiry_date` > NOW() OR `pu`.`expiry_date` IS NULL))
 left join `image` `i` on `pu`.`p_uuid` = `i`.`x_uuid`
 join `person_details` `pd` on `pu`.`p_uuid` = `pd`.`p_uuid`
 join `incident` `inc` on `inc`.`incident_id` = `pu`.`incident_id`
 left join `hospital` `h` on `h`.`hospital_uuid` = `pu`.`hospital_uuid`
 left join `person_updates` `upd` on `upd`.`p_uuid` = `pu`.`p_uuid`;

 --
 -- This stored procedure is the the SQL version of search.
 -- It's a very simple filtered search which can still be improved 
 -- at the cost of some performance which can be increased by increasing
 -- the minimum amount of characters required for the searchTerms variable.
 -- 
 
DELIMITER //
DROP PROCEDURE `PLSearch`//
DROP PROCEDURE `PLSearch`//
CREATE DEFINER=`sahanaPlStage`@`localhost` PROCEDURE `PLSearch`(
     IN searchTerms CHAR(255),
	 IN statusFilter VARCHAR(100),
	 IN genderFilter VARCHAR(100),
	 IN ageFilter VARCHAR(100),
	 IN hospitalFilter VARCHAR(100),
	 IN incidentName VARCHAR(100),
	 IN sortBy VARCHAR(100),
	 IN pageStart INT,
	 IN perPage INT
)
BEGIN

	DROP TABLE IF EXISTS tmp_names; 
    IF searchTerms = '' THEN 
            CREATE TEMPORARY TABLE tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
                  LIMIT 5000
         );
    
    ELSE
            CREATE TEMPORARY TABLE  tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
            WHERE full_name like CONCAT(searchTerms , '%') 
            LIMIT 5000
            );
     END IF;
    
    SET @sqlString = CONCAT("SELECT  SQL_NO_CACHE `tn`.`p_uuid`       AS `p_uuid`,
				`tn`.`full_name`    AS `full_name`,
				`tn`.`given_name`   AS `given_name`,
				`tn`.`family_name`  AS `family_name`,
				(CASE WHEN `ps`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR `ps`.`opt_status` IS NULL THEN 'unk' ELSE `ps`.`opt_status` END) AS `opt_status`,
				(CASE WHEN  DATE_FORMAT(ps.last_updated, '%Y-%m-%d %k:%i:%s') as updated,
                  
				(CASE WHEN `pd`.`opt_gender` NOT IN ('mal', 'fml') OR `pd`.`opt_gender` IS NULL THEN 'unk' ELSE `pd`.`opt_gender` END) AS `opt_gender`,
				(CASE WHEN `pd`.`years_old` < 18 THEN 'child' WHEN `pd`.`years_old` >= 18 THEN 'adult' ELSE 'unknown' END) as `age_group`,
                                `pd`.`years_old` as `years_old`,
				`i`.`image_height` AS `image_height`,
				`i`.`image_width`  AS `image_width`,
				`i`.`url_thumb`    AS `url_thumb`,
				(CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)  AS `hospital`,
				(CASE WHEN (`h`.`hospital_uuid` = -(1)) THEN NULL ELSE `h`.`icon_url` END) AS `icon_url`,
				`pd`.last_seen,
				`pd`.other_comments as comments
			 FROM tmp_names tn
             JOIN person_status ps  ON (tn.p_uuid = ps.p_uuid AND ps.isVictim = 1 AND tn.expiry_date > NOW() AND INSTR(?, 	(CASE WHEN ps.opt_status NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR ps.opt_status IS NULL THEN 'unk' ELSE  ps.opt_status END)))
             JOIN person_details pd ON (tn.p_uuid = pd.p_uuid AND INSTR(?, (CASE WHEN `opt_gender` NOT IN ('mal', 'fml') OR `opt_gender` IS NULL THEN 'unk' ELSE `opt_gender` END))
															  AND INSTR(?, (CASE WHEN CAST(`years_old` AS UNSIGNED) < 18 THEN 'child' WHEN CAST(`years_old` AS UNSIGNED) >= 18 THEN 'adult' ELSE 'unknown' END)))
			 LEFT 
			 JOIN hospital h        ON (tn.hospital_uuid = h.hospital_uuid AND INSTR(?, (CASE WHEN `h`.`short_name` NOT IN ('nnmc', 'suburban') OR `h`.`short_name` IS NULL THEN 'other' ELSE `h`.`short_name` END)))
             LEFT 
			 JOIN image i			ON (tn.p_uuid = i.x_uuid)
           ORDER BY ", sortBy, " LIMIT ?, ?;");

      PREPARE stmt FROM @sqlString;

      SET @statusFilter = statusFilter;
      SET @genderFilter = genderFilter;
      SET @ageFilter = ageFilter;
      SET @hospitalFilter = hospitalFilter;

      SET @pageStart = pageStart;
      SET @perPage = perPage;

      SET NAMES utf8;
      EXECUTE stmt USING @statusFilter, @genderFilter, @ageFilter, @hospitalFilter, 
                                                        @pageStart, @perPage;

      DEALLOCATE PREPARE stmt;
      DROP TABLE tmp_names;

   
   
END
DELIMITER ;


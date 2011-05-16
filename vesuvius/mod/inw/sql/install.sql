CREATE ALGORITHM=UNDEFINED VIEW `person_search` 
AS select `a`.`p_uuid` AS `p_uuid`,
`a`.`full_name` AS `full_name`,
`a`.`given_name` AS `given_name`,
`a`.`family_name` AS `family_name`,
(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk', 'fnd') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
`b`.`last_updated` AS `updated`,
(CASE WHEN `c`.`opt_gender` NOT IN ('mal', 'fml') OR `c`.`opt_gender` IS NULL THEN 'unk' ELSE `c`.`opt_gender` END) AS `opt_gender`,
(CASE WHEN CONVERT(`c`.`years_old`, UNSIGNED INTEGER) IS NULL THEN -1 ELSE `c`.`years_old` END) AS `years_old`,
`i`.`image_height` AS `image_height`,
`i`.`image_width` AS `image_width`,
`i`.`url_thumb` AS `url_thumb`,
(case when (`h`.`hospital_uuid` = -(1)) then NULL else `h`.`icon_url` end) AS `icon_url`,
`inc`.`shortname` AS `shortname`,
(CASE WHEN `h`.`short_name` NOT IN ('sh', 'nnmc') OR `h`.`short_name` IS NULL THEN 'public' ELSE `h`.`short_name` END) AS `hospital`,
`c`.`other_comments` AS `comments`,
`c`.`last_seen` AS `last_seen` 
from `person_uuid` `a` join `person_status` `b` on (`a`.`p_uuid` = `b`.`p_uuid` and `b`.`isvictim` = 1)
 left join `image` `i` on `a`.`p_uuid` = `i`.`x_uuid`
 join `person_details` `c` on `a`.`p_uuid` = `c`.`p_uuid`
 join `incident` `inc` on `inc`.`incident_id` = `a`.`incident_id`
 left join `hospital` `h` on `h`.`hospital_uuid` = `a`.`hospital_uuid`
 left join person_updates f on a.p_uuid = f.p_uuid;

DROP PROCEDURE `PLSearch`//
CREATE DEFINER=`mrodriguez`@`localhost` PROCEDURE `PLSearch`(
     IN searchTerms CHAR(255),
	 IN statusFilter VARCHAR(100),
	 IN genderFilter VARCHAR(100),
	 IN ageFilter VARCHAR(100),
	 IN hospitalFilter VARCHAR(100),
	 IN incidentName VARCHAR(100),
	 IN sortBy VARCHAR(100),
	 IN pageStart INT,
	 IN perPage INT,
    OUT totalRows INT

)
BEGIN

	DROP TABLE IF EXISTS tmp_names; 
    IF searchTerms = '' THEN 
            CREATE TEMPORARY TABLE tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
                  LIMIT 2000
         );
    
    ELSE
            CREATE TEMPORARY TABLE  tmp_names AS (
            SELECT SQL_NO_CACHE pu.*
                FROM person_uuid pu
                   JOIN incident i  ON (pu.incident_id = i.incident_id AND i.shortname = incidentName)
            WHERE full_name like CONCAT(searchTerms , '%') 
            LIMIT 2000
            );
     END IF;
    
    SET @sqlString = CONCAT("SELECT  SQL_NO_CACHE `tn`.`p_uuid`       AS `p_uuid`,
				`tn`.`full_name`    AS `full_name`,
				`tn`.`given_name`   AS `given_name`,
				`tn`.`family_name`  AS `family_name`,
				(CASE WHEN `ps`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR `ps`.`opt_status` IS NULL THEN 'unk' ELSE `ps`.`opt_status` END) AS `opt_status`,
				  DATE_FORMAT(ps.last_updated, '%Y-%m-%d %k:%i:%s') as updated,
                  
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
             JOIN person_status ps  ON (tn.p_uuid = ps.p_uuid AND ps.isVictim = 1 AND INSTR(?, 	(CASE WHEN ps.opt_status NOT IN ('ali', 'mis', 'inj', 'dec', 'fnd') OR ps.opt_status IS NULL THEN 'unk' ELSE  ps.opt_status END)))
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
    
    
      SELECT COUNT(p.p_uuid) INTO totalRows
          FROM person_uuid p
             JOIN incident i ON p.incident_id = i.incident_id
      WHERE i.shortname = incidentName;
   
   
END

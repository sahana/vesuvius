CREATE ALGORITHM=UNDEFINED VIEW `person_search` 
AS select `a`.`p_uuid` AS `p_uuid`,
`a`.`full_name` AS `full_name`,
`a`.`given_name` AS `given_name`,
`a`.`family_name` AS `family_name`,
(CASE WHEN `b`.`opt_status` NOT IN ('ali', 'mis', 'inj', 'dec', 'unk', 'fnd') OR `b`.`opt_status` IS NULL THEN 'unk' ELSE `b`.`opt_status` END) AS `opt_status`,
`b`.`last_updated` AS `updated`,
`c`.`opt_gender` AS `opt_gender`,
`c`.`years_old` AS `years_old`,
`i`.`image_height` AS `image_height`,
`i`.`image_width` AS `image_width`,
`i`.`url_thumb` AS `url_thumb`,
(case when (`h`.`hospital_uuid` = -(1)) then NULL else `h`.`icon_url` end) AS `icon_url`,
`inc`.`shortname` AS `shortname`,
`h`.`short_name` AS `hospital`,
`e`.`comments` AS `comments`,
`e`.`last_seen` AS `last_seen` 
from `person_uuid` `a` join `person_status` `b` on (`a`.`p_uuid` = `b`.`p_uuid` and `b`.`isvictim` = 1)
 left join `image` `i` on `a`.`p_uuid` = `i`.`x_uuid`
 join `person_details` `c` on `a`.`p_uuid` = `c`.`p_uuid`
 join `incident` `inc` on `inc`.`incident_id` = `a`.`incident_id`
 left join `hospital` `h` on `h`.`hospital_uuid` = `a`.`hospital_uuid`
 left join `person_missing` `e` on `a`.`p_uuid` = `e`.`p_uuid`
 left join person_updates f on a.p_uuid = f.p_uuid;
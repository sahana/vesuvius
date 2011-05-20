/**
 * @name         Edit A Person
 * @version      1.4
 * @package      eap
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0520
 */

CREATE TABLE `person_updates` (
  `update_index`      int(32)      NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid`            varchar(60)  NOT NULL,
  `update_time`       timestamp    NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `updated_table`     varchar(64)  NOT NULL,
  `updated_column`    varchar(64)  NOT NULL,
  `old_value`         varchar(512) NOT NULL,
  `new_value`         varchar(512) NOT NULL,
  `updated_by_p_uuid` varchar(60)  NOT NULL,
  INDEX(`p_uuid`),
  INDEX(`updated_by_p_uuid`),
  FOREIGN KEY(`p_uuid`)            REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY(`updated_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;



CREATE TABLE `person_notes` (
 `note_id`                int(11)       NOT NULL auto_increment PRIMARY KEY,
 `note_about_p_uuid`      varchar(60)   NOT NULL,
 `note_written_by_p_uuid` varchar(60)   NOT NULL,
 `note`                   varchar(1024) NOT NULL,
 `when`                   timestamp     NOT NULL DEFAULT CURRENT_TIMESTAMP,
 INDEX(`note_about_p_uuid`),
 INDEX(`note_written_by_p_uuid`),
 FOREIGN KEY (`note_about_p_uuid`)      REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE,
 FOREIGN KEY (`note_written_by_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;



CREATE TABLE `person_followers` (
  `id`               int(16)      NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid`           varchar(60)  NOT NULL,
  `follower_p_uuid`  varchar(60)  NOT NULL,
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`)          REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE,
  FOREIGN KEY(`follower_p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;


/**
 * @name         MPR Email Service
 * @version      1.7
 * @package      mpres
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine and the Sahana Foundation
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0324
 */

CREATE table mpres_log (
	log_index       int          NOT NULL AUTO_INCREMENT PRIMARY KEY,
	p_uuid          varchar(64)  NOT NULL,
	email_subject   varchar(256) NOT NULL,
	email_from      varchar(128) NOT NULL,
	email_date      varchar(64)  NOT NULL,
	update_time     datetime     NOT NULL,
	INDEX(`p_uuid`),
	FOREIGN KEY (`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


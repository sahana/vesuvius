/**
 * @name         Resources
 * @version      1.4
 * @package      rez
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0801
 */

DROP TABLE IF EXISTS `rez_pages`;

CREATE table rez_pages (
	rez_page_id        int          AUTO_INCREMENT NOT NULL,
	rez_menu_title     varchar(64)                 NOT NULL,
	rez_page_title     varchar(64)                 NOT NULL,
	rez_menu_order     int                         NOT NULL,
	rez_content        mediumtext                  NOT NULL,
	rez_description    varchar(128)                NOT NULL,
	rez_timestamp      timestamp                   NOT NULL,
	rez_visibility     varchar(16)                 NOT NULL,
	PRIMARY KEY(rez_page_id)
) ENGINE=INNODB;

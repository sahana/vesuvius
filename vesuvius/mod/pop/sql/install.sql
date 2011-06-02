/**
 * @name         Push Out Post
 * @version      1.0
 * @package      pop
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0308
 */


DROP TABLE IF EXISTS `pop_outlog`;

CREATE table pop_outlog (
	outlog_index     int          NOT NULL AUTO_INCREMENT,
	mod_accessed     varchar(8)   NOT NULL,
	time_sent        timestamp    NOT NULL,
	send_status      varchar(8)   NOT NULL,
	error_message    varchar(512) NOT NULL,
	email_subject    varchar(256) NOT NULL,
	email_from       varchar(128) NOT NULL,
	email_recipients varchar(256) NOT NULL,
	PRIMARY KEY(outlog_index)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


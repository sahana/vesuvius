/**
 * @name         PL User Services
 * @version      1.9.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0621
 */


CREATE TABLE `plus_access_log` (
  `access_id`   int(16)     NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `access_time` timestamp   NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `application` varchar(32) NULL,
  `version`     varchar(16) NULL,
  `ip`          varchar(16) NULL,
  `call`        varchar(64) NULL,
  INDEX(`api_key`),
  FOREIGN KEY(`api_key`) REFERENCES `ws_keys` (`api_key`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


CREATE TABLE `plus_report_log` (
  `report_id`   int(16)     NOT NULL AUTO_INCREMENT PRIMARY KEY,
  `p_uuid`      varchar(60) NOT NULL,
  `report_time` timestamp   NOT NULL DEFAULT CURRENT_TIMESTAMP,
  INDEX(`p_uuid`),
  FOREIGN KEY(`p_uuid`) REFERENCES `person_uuid` (`p_uuid`) ON UPDATE CASCADE ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;


INSERT INTO rez_pages (rez_page_id, rez_menu_title, rez_page_title, rez_menu_order, rez_content, rez_description, rez_timestamp, rez_visibility) VALUES
(-6, 'Password Reset.', 'Password Reset.', 8, '<div><br></div><div>Your password has been successfully reset and the new password emailed to you.</div>', 'Password Reset.', '2011-06-14 13:09:49', 'Hidden'),
(-5, 'Account activated.', 'Account activated.', 7, '<div><br></div><div>Your account has been successfully activated. You may now <a href="index.php?mod=pref&amp;act=loginForm" title="login" target="">login to the site</a> to begin using it.</div>', 'Account activated.', '2011-06-14 13:09:49', 'Hidden'),
(-4, 'Account already active.', 'Account already active.', 6, '<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>', 'Account already active.', '2011-06-14 13:06:55', 'Hidden');

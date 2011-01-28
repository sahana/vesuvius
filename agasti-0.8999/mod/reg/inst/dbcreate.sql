/**
* This file creates the database structure for the reg module. 
* The data stored here is for registrations that were performed using this module.
* Modules: REG
* Last changed: 20100709
*/

DROP TABLE IF EXISTS `reg`;

CREATE TABLE `reg` (
  `index` int(16) NOT NULL auto_increment PRIMARY KEY,
  `p_uuid` varchar(60) NOT NULL,
  `domain` varchar(200) NOT NULL,
  `API_KEY` varchar(60) NOT NULL,
  `PASSWORD` varchar(60) NOT NULL,
  `SECRET_CODE` varchar(60) NOT NULL,
  `EMAIL_ADDRESS` varchar(255) NOT NULL,
  `FULL_NAME` varchar(255) NOT NULL,
  `last_attempt` timestamp NOT NULL default CURRENT_TIMESTAMP,
  `is_active` int(8) NOT NULL default '0',
  `confirmation_code` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;




/* Insert MOD Rez Content Pages that accompany this module */
INSERT INTO rez_pages (rez_page_id, rez_menu_title, rez_page_title, rez_menu_order, rez_content, rez_description, rez_timestamp, rez_visibility) VALUES
(-6, 'Password Change Successful', 'Password Change Successful', 11, '<div><br></div><div>Your password has been changed and the new password emailed to you. Please use it for future logins.</div>', 'Password Change Successful', '2010-05-24 15:28:36', 'Hidden'),

(-5, 'Password Change Unsuccessful', 'Password Change Unsuccessful', 11, '<div><br></div><div>Your attempted password change was unsuccessful. It appears you used an invalid confirmation code.</div>', 'Password Change Unsuccessful', '2010-05-24 15:28:36', 'Hidden'),

(-4, 'Account Already Active', 'Account Already Active', 12, '<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>', 'Account Already Active', '2010-05-24 15:28:36', 'Hidden'),

(-3, 'Registration Unsuccessful', 'Registration Unsuccessful', 11, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm an invalid user. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-05-24 15:28:36', 'Hidden'),

(-2, 'Registration Unsuccessful', 'Registration Unsuccessful', 10, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm a user with an invalid confirmation code. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-05-24 15:28:48', 'Hidden'),

(-1, 'Registration Successful', 'Registration Successful', 9, '<div><br></div><div>Thank you for confirming your registration.&nbsp;</div><div><br></div><div>The device you registered can now utilize the Person Locator web services. (ie. Searching for and Reporting Persons on ReUnite)</div><div><br></div><div><meta http-equiv="content-type" content="text/html; charset=utf-8"><div>Additionally, your user account is now active and you may log into this site with the login/password that was supplied in the email you received. After logging in, you may change your password by going to User Preferences and navigating to "Change Password".</div></div><div><br></div>', 'Registration Successful', '2010-05-24 15:28:54', 'Hidden');



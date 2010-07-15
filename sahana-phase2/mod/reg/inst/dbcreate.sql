/**
* This file creates the database structure for the reg module. 
* The data stored here is for registrations that were performed using this module.
* Modules: REG
* Last changed: 20100709
*/

DROP TABLE IF EXISTS `reg`;

CREATE TABLE reg (
	`index`             INT(16)      NOT NULL AUTO_INCREMENT, 
	`p_uuid`            VARCHAR(60)  NOT NULL, 
	`domain`            VARCHAR(200) NOT NULL, 
	`API_KEY`           VARCHAR(60)  NOT NULL,
	`PASSWORD`          VARCHAR(60)  NOT NULL,
	`SECRET_CODE`       VARCHAR(60)  NOT NULL,
	`EMAIL_ADDRESS`     VARCHAR(255) NOT NULL, 
	`FULL_NAME`         VARCHAR(255) NOT NULL, 
	`last_attempt`      TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP, 
	`is_active`         INT(8)       NOT NULL DEFAULT '0', 
	`confirmation_code` VARCHAR(255) NOT NULL, 
	PRIMARY KEY (`index`)
) ENGINE = INNODB;



/* Insert MOD Rez Content Pages that accompany this module */
INSERT INTO rez_pages (rez_page_id, rez_menu_title, rez_page_title, rez_menu_order, rez_content, rez_description, rez_timestamp, rez_visibility) VALUES

(-4, 'Account Already Active', 'Account Already Active', 12, '<div><br></div><div>This confirmation link is no longer valid. The account attached to it is already active.</div>', 'Account Already Active', '2010-05-24 15:28:36', 'Hidden'),

(-3, 'Registration Unsuccessful', 'Registration Unsuccessful', 11, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm an invalid user. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-05-24 15:28:36', 'Hidden'),

(-2, 'Registration Unsuccessful', 'Registration Unsuccessful', 10, '<div><br></div><div>Your attempted registration confirmation was unsuccessful. It appears you attempted to confirm a user with an invalid confirmation code. Please re-initiate the registration process from your device to try again.</div>', 'Registration Unsuccessful', '2010-05-24 15:28:48', 'Hidden'),

(-1, 'Registration Successful', 'Registration Successful', 9, '<div><br></div><div>Thank you for confirming your registration.&nbsp;</div><div><br></div><div>The device you registered can now utilize the Person Locator web services. (ie. Searching for and Reporting Persons on ReUnite)</div><div><br></div><div><meta http-equiv="content-type" content="text/html; charset=utf-8"><div>Additionally, your user account is now active and you may log into this site with the login/password that was supplied in the email you received. After logging in, you may change your password by going to User Preferences and navigating to "Change Password".</div></div><div><br></div>', 'Registration Successful', '2010-05-24 15:28:54', 'Hidden');



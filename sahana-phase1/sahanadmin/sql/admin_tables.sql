/*
MySQL Backup
Source Host:           192.168.101.14
Source Server Version: 4.1.8-nt
Source Database:       erms
Date:                  2005/01/17 14:09:44
*/

SET FOREIGN_KEY_CHECKS=0;
use erms;
#----------------------------
# Table structure for tblAccessLevels
#----------------------------
CREATE TABLE `TBLACCESSLEVELS` (
  `AccessLevels` varchar(20) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tblAccessLevels
#----------------------------


insert  into TBLACCESSLEVELS values 
('PAGE'), 
('ADD'), 
('EDIT'), 
('DELETE'), 
('SEARCH');
#----------------------------
# Table structure for tblAccessModules
#----------------------------
CREATE TABLE `TBLACCESSMODULES` (
  `ModuleId` int(11) default NULL,
  `ModuleName` varchar(50) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tblAccessModules
#----------------------------


insert  into TBLACCESSMODULES values 
(1, 'Assistance Database'), 
(2, 'Request Management System'), 
(6, 'Users'), 
(7, 'Roles'), 
(8, 'Access Permissions'), 
(3, 'Camp Registration'), 
(4, 'Organizations');
#----------------------------
# Table structure for tblaccesspermissions
#----------------------------
CREATE TABLE `TBLACCESSPERMISSIONS` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL,
  `Permission` char(1) default NULL,
  `RoleId` int(11) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tblaccesspermissions
#----------------------------


insert  into TBLACCESSPERMISSIONS values 
(1, 'PAGE', 'Y', 0), 
(1, 'ADD', 'Y', 0), 
(1, 'SEARCH', 'Y', 0), 
(2, 'PAGE', 'Y', 0), 
(2, 'ADD', 'Y', 0), 
(2, 'SEARCH', 'Y', 0), 
(2, 'EDIT', 'Y', 0), 
(8, 'PAGE', 'Y', 0), 
(8, 'ADD', 'Y', 0), 
(6, 'ADD', 'Y', 0), 
(6, 'PAGE', 'Y', 0), 
(6, 'EDIT', 'Y', 0), 
(6, 'DELETE', 'Y', 0), 
(3, 'PAGE', 'Y', 0), 
(3, 'ADD', 'Y', 0), 
(3, 'EDIT', 'Y', 0), 
(3, 'SEARCH', 'Y', 0), 
(7, 'PAGE', 'Y', 0), 
(7, 'ADD', 'Y', 0), 
(7, 'EDIT', 'Y', 0), 
(7, 'DELETE', 'Y', 0), 
(4, 'EDIT', 'Y', 0); 

#----------------------------
# Table structure for tblAuditLog
#----------------------------
CREATE TABLE `TBLAUDITLOG` (
  `UserName` varchar(100) NOT NULL default '',
  `ModuleId` int(11) NOT NULL default '0',
  `AccessLevel` varchar(100) NOT NULL default '',
  `AccessDateTime` varchar(100) NOT NULL default ''
) TYPE=MyISAM ;
#----------------------------
# Records for table tblAuditLog
#----------------------------
#----------------------------
# Table structure for tblModuleAccessLevels
#----------------------------
CREATE TABLE `TBLMODULEACCESSLEVELS` (
  `ModuleId` int(11) default NULL,
  `AccessLevel` varchar(20) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tblModuleAccessLevels
#----------------------------


insert  into TBLMODULEACCESSLEVELS values 
(1, 'PAGE'), 
(1, 'ADD'), 
(1, 'SEARCH'), 
(2, 'PAGE'), 
(2, 'ADD'), 
(2, 'SEARCH'), 
(6, 'ADD'), 
(6, 'PAGE'), 
(6, 'EDIT'), 
(6, 'DELETE'), 
(7, 'PAGE'), 
(7, 'EDIT'), 
(7, 'DELETE'), 
(7, 'ADD'), 
(8, 'PAGE'), 
(8, 'ADD'), 
(2, 'EDIT'), 
(3, 'PAGE'), 
(3, 'ADD'), 
(3, 'EDIT'), 
(3, 'SEARCH'), 
(4, 'EDIT');
#----------------------------
# Table structure for tblRoles
#----------------------------
CREATE TABLE `TBLROLES` (
  `RoleId` int(11) default NULL,
  `RoleName` varchar(30) default NULL,
  `Description` varchar(100) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tblRoles
#----------------------------


insert  into TBLROLES values 
(0, 'Administrator', 'the boss'), 
(1, 'User', 'the average user');
#----------------------------
# Table structure for tbluserroles
#----------------------------
CREATE TABLE `TBLUSERROLES` (
  `RoleId` int(11) default NULL,
  `UserName` varchar(30) default NULL
) TYPE=MyISAM ;
#----------------------------
# Records for table tbluserroles
#----------------------------


insert  into TBLUSERROLES values 
(1, 'sanjiva');


CREATE TABLE sahana_daily_report (
  report_id int(11) NOT NULL auto_increment,
  created date default '0000-00-00',
  title varchar(250) default NULL,
  field_heading varchar(250) default NULL,
  PRIMARY KEY  (report_id)
) TYPE=MyISAM COMMENT='Daily report table';

#
# Table structure for table `sahana_dailyreport_data`
#

CREATE TABLE sahana_dailyreport_data (
  report_id int(11) NOT NULL default '0',
  field_data varchar(255) default NULL,
  KEY report_id (report_id)
) TYPE=MyISAM COMMENT='Daily report data table';

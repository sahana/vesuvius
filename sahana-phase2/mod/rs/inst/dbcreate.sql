DROP TABLE IF EXISTS `report_files`;
DROP TABLE IF EXISTS `report_keywords`;

create table report_files
	(rep_id varchar(100),
	file_name varchar(100),
	file_data longblob,
	t_stamp timestamp default current_timestamp on update current_timestamp,
	file_type varchar(10),
	file_size_kb double,
	title varchar(100));
create table report_keywords
	(rep_id varchar(100),
	keyword_key varchar(100),
	keyword varchar(100)	
	);

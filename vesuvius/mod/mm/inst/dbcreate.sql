
CREATE TABLE IF NOT EXISTS `mm_cache` (
  `id` int(200) NOT NULL AUTO_INCREMENT,
  `module_shortname` varchar(200) NOT NULL,
  `module_name` varchar(200) NOT NULL,
  `module_description` varchar(200) NOT NULL,
  `module_version` varchar(200) NOT NULL,
  `module_dependancy` varchar(200) NOT NULL,
  `module_node_id` int(200) NOT NULL,
  `module_filepath` varchar(200) NOT NULL,
  `module_imagepath` varchar(200) NOT NULL,
  `time_stamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `status` varchar(200) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `modules` (
 `module` varchar(20) NOT NULL,
 `status` varchar(50) NOT NULL,
 `extra` text NOT NULL,
 PRIMARY KEY  (`module`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
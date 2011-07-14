/*
** - - - - - - - DATA - - - - - - - -
*/

/* USE THESE FOR CHEPL AND PFPL*/
INSERT INTO `pfif_repository` (`id`, `name`, `base_url`, `role`, `granularity`, `deleted_record`, `params`, `sched_interval_minutes`, `log_granularity`, `first_entry`, `last_entry`, `total_persons`, `total_notes`) VALUES
(5,'Person Finder: China Earthquake','http://chinapersonfinder.appspot.com','source','YYYY-MM-DDThh:mm:ssZ',
              'no','<config><service name="googlechina"><read><url>api/read</url><param><name>version</name><value>1.2</value></param><param><name>id</name><value>${Pfif_Person.person_record_id}</value></param></read><feed><url>feeds/person</url><param><name>min_entry_date</name><value>20100401T000000Z</value></param><param><name>skip</name><value>0</value></param><param><name>max_results</name><value>200</value></param></feed></service></config>','2','01:00:00', NULL, NULL, 0, 0),
(6, 'Person Finder: Pakistan Flood', 'http://pakistan.person-finder.appspot.com', 'source', 'YYYY-MM-DDThh:mm:ssZ', 
              'no', '<config><service name="googlepakistan"><read><url>api/read</url><param><name>version</name><value>1.2</value></param><param><name>id</name><value>${Pfif_Person.person_record_id}</value></param></read><feed><url>feeds/person</url><param><name>min_entry_date</name><value>20100701T000000Z</value></param><param><name>skip</name><value>0</value></param><param><name>max_results</name><value>200</value></param></feed></service></config>', '0', '01:00:00', NULL, NULL, 0, 0)

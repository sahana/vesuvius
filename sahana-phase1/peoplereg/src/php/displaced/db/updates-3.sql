
use mambo;

update sahana_attributes set data_type = 0 where name = 'current_location';

insert into sahana_attribute_options (attribute_id, name, caption) select id, 'unknown', 'Unknown' from sahana_attributes where name='current_location';
insert into sahana_attribute_options (attribute_id, name, caption) select id, 'camp', 'Camp' from sahana_attributes where name='current_location';
insert into sahana_attribute_options (attribute_id, name, caption) select id, 'temporary_housing', 'Temporary housing' from sahana_attributes where name='current_location';
insert into sahana_attribute_options (attribute_id, name, caption) select id, 'friend_family', 'With friends / family' from sahana_attributes where name='current_location';
insert into sahana_attribute_options (attribute_id, name, caption) select id, 'home', 'Home' from sahana_attributes where name='current_location';


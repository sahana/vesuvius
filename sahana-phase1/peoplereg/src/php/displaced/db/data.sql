insert into sahana_location_types (name, caption)
	values ('country', 'Country');
insert into sahana_location_types (name, caption)
	values ('province', 'Province');
insert into sahana_location_types (name, caption)
	values ('district', 'District');

insert into sahana_locations (location_type, name, caption)
	select id, 'colombo', 'Colombo' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'gampaha', 'Gampaha' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'kalutara', 'Kalutara' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'kandy', 'Kandy' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'matale', 'Matale' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'nuwaraeliya', 'Nuwara Eliya' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'galle', 'Galle' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'matara', 'Matara' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'hambantota', 'Hambantota' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'jaffna', 'Jaffna' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'mannar', 'Mannar' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'vavuniya', 'Vavuniya' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'mullaitivu', 'Mullaitivu' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'kilinochchi', 'Kilinochchi' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'batticaloa', 'Batticaloa' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'ampara', 'Ampara' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'trincomalee', 'Trincomalee' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'kurunegala', 'Kurunegala' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'puttalam', 'Puttalam' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'anuradhapura', 'Anuradhapura' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'polonnaruwa', 'Polonnaruwa' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'badulla', 'Badulla' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'monaragala', 'Monaragala' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'ratnapura', 'Ratnapura' from sahana_location_types where name='district';
insert into sahana_locations (location_type, name, caption)
	select id, 'kegalle', 'Kegalle' from sahana_location_types where name='district';


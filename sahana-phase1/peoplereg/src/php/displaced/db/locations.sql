
drop table if exists sahana_locations;

create table sahana_locations (
		id integer auto_increment,
		name varchar(63) unique,
		caption text,
		parent integer,
		location_type integer,
		primary key (id)
);

drop table if exists sahana_location_types;

create table sahana_location_types (
		id integer auto_increment,
		name varchar(63) unique,
		caption text,
		primary key (id)
);



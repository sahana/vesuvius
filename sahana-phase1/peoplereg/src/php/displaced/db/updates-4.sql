
drop table if exists sahana_locations;

create table sahana_locations (
		id integer auto_increment,
		name varchar(63),
		code varchar(31),
		parent integer,
		location_type integer,
		primary key (id),
		unique (parent, name),
		unique (parent, code)
);

drop table if exists sahana_location_types;

create table sahana_location_types (
		id integer auto_increment,
		name varchar(63) unique,
		primary key (id)
);

insert into sahana_location_types (name) values ('Country');
insert into sahana_location_types (name) values ('Province');
insert into sahana_location_types (name) values ('District');
insert into sahana_location_types (name) values ('Division');
insert into sahana_location_types (name) values ('GS Division');



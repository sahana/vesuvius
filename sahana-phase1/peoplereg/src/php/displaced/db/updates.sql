
-- This is a quick hack to add entity_type column and an
-- entity types table

alter table sahana_entities add column entity_type integer;

create table sahana_entity_types (
		id integer auto_increment,
		name varchar(63) unique,
		caption text,
		primary key (id)
);


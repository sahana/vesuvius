
-- This is a quick hack to add entity_type column and an
-- entity types table

use mambo;

alter table sahana_entities add column entity_type integer;

create table sahana_entity_types (
		id integer auto_increment,
		name varchar(63) unique,
		caption text,
		primary key (id)
);

insert into sahana_entity_types (name, caption) values ('person', 'Person');
insert into sahana_entity_types (name, caption) values ('family', 'Family');

-- We assume entity_type 1 is 'person';
update sahana_entities set entity_type = 1;

create table sahana_entity_relationships (
		entity_id integer,
		related_id integer,
		relation_type integer,
		primary key (entity_id, related_id, relation_type)
);

create table sahana_entity_relationship_types (
		id integer auto_increment,
		name varchar(63) unique,
		caption text,
		primary key (id)
);

insert into sahana_entity_relationship_types (name, caption) values ('same', 'Same');
insert into sahana_entity_relationship_types (name, caption) values ('duplicate', 'Duplicate');
insert into sahana_entity_relationship_types (name, caption) values ('family member', 'Family member');
insert into sahana_entity_relationship_types (name, caption) values ('parent', 'Parent');
insert into sahana_entity_relationship_types (name, caption) values ('child', 'Child');
insert into sahana_entity_relationship_types (name, caption) values ('father', 'Father');
insert into sahana_entity_relationship_types (name, caption) values ('mother', 'Mother');
insert into sahana_entity_relationship_types (name, caption) values ('son', 'Son');
insert into sahana_entity_relationship_types (name, caption) values ('daughter', 'Daughter');
insert into sahana_entity_relationship_types (name, caption) values ('belongs to', 'Belongs to');


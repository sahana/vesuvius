USE sahana;
/*CATALOGUE SYSTEM TABLES*/
/*-----------------------*/

DROP TABLE IF EXISTS `ct_catalogue`;
DROP TABLE IF EXISTS `ct_unit`;
DROP TABLE IF EXISTS `ct_cat_unit`;
create table ct_catalogue (ct_uuid varchar(60) not null primary key, parentid varchar(60),name varchar(100),description varchar(100));


create table ct_unit(unit_uuid varchar(60) not null primary key,name varchar(100));

create table ct_cat_unit(ct_uuid varchar(60),unit_uuid varchar(60));

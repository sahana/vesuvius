\t \o test;

\qecho 'Removing old database';
DROP DATABASE skillsregister;
\qecho '... done';

\qecho 'Removing old entries in administrator database';
DELETE FROM DBObject
 WHERE DBName = 'skillsregister';
\qecho '... done';

\qecho 'Inserting table entries to administrator database';
\qecho '...';
INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Skill',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Organisation',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Address',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Volunteer',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Category',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Code',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'RelatedCode',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Opportunity',
	70
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'WorkProfile',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relVolunteerAddress',
	70
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relVolunteerSkill',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relOrganisationAddress',
	70
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relCategorySkill',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relOpportunityAddress',
	80
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relOpportunitySkill',
	80
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Match',
	90
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Person',
	60
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relVolunteerPerson',
	70
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relPersonAddress',
	70
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'ContactDetails',
	50
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'relPersonContactDetails',
	70
);

\qecho '... done';

\qecho 'Inserting stored procedure entries to administrator database';
\qecho '...';
INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'Automatch',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerSearchAuto',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerSearch',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'OrganisationSearchAuto',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'OrganisationSearch',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'GetVolunteerId',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'GetPersonId',
	'StoredProcedure',
	150
);
\qecho '... done';

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'OpportunityAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'OpportunityDelete',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'SkillAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerSkillAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerSkillDelete',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'CountryAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'StateAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'RegionAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'WorkProfileAdd',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'WorkProfileDelete',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerAddressDelete',
	'StoredProcedure',
	150
);

INSERT INTO DBObject
(
	DBName,
	ObjectName,
	ObjectType,
	CreateOrder
)
VALUES
(
	'skillsregister',
	'VolunteerAddressAdd',
	'StoredProcedure',
	150
);
\qecho '... done';

CREATE DATABASE skillsregister;

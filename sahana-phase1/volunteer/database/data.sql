-- INSERT CODES
-- 1
\qecho 'loading Code'
\qecho '------------'
\qecho '...'
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'MR',
	'Mister'
);

-- 2
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'MRS',
	'Missus'
);

-- 3
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'MASTER',
	'Master'
);

-- 4
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'MISS',
	'Miss'
);

-- 5
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'DR',
	'Doctor'
);

-- 6
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'TITL',
	'PROF',
	'Professor'
);

-- 7
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'612900AACT',
	'Australian Capital Territory'
);

-- 8
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'612102SCBD',
	'Sydney Central Business District'
);

-- 9
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'613102MCBD',
	'Melbourne Central Business District'
);

-- 10
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'911111BAMB',
	'Bambalapitiya'
);

-- 11
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'010001BEVH',
	'Beverly Hills'
);

-- 12
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'ADDT',
	'JOB',
	'Job Address'
);

-- 13
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'ADDT',
	'PHYSICAL',
	'Physical Address'
);

-- 14
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'ADDT',
	'POSTAL',
	'Postal Address'
);

-- 15
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'FPCT',
	'FT',
	'Full Time'
);

-- 16
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'FPCT',
	'PT',
	'Part Time'
);

-- 17
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'FPCT',
	'CASUAL',
	'Casual'
);

-- 18
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'FPCT',
	'ANY',
	'Any'
);


-- 19
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'PTFL',
	'PERMANENT',
	'Permanent'
);

-- 20
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'PTFL',
	'TEMPORARY',
	'Temporary'
);

-- 21
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'PTFL',
	'ANY',
	'Any'
);

-- 22
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'SKLT',
	'VOLUNTEER',
	'Volunteer Skill'
);

-- 23
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'SKLT',
	'OPPORTUNI',
	'Opportunity Skill'
);

-- 24
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'MTCH',
	'AUTOMATCH',
	'Automatch match'
);

-- 25
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'MTCH',
	'VOLUNTEER',
	'Volunteer using criteria to find opportunities'
);

-- 26
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'MTCH',
	'ORGANISAT',
	'Organisation using criteria to find volunteers'
);

-- 27
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'MTCH',
	'VOLAUTO',
	'Automated Volunteer Search'
);

-- 28
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'MTCH',
	'ORGAUTO',
	'Automated Organisation Search'
);

-- 29
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CNTC',
	'PAGE',
	'Post a message on my messages page'
);

-- 30
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CNTC',
	'EMAIL',
	'Contact by email'
);

-- 31
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CNTC',
	'PHONE',
	'Contact by phone'
);

-- 32
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CTRY',
	'61',
	'Australia'
);

-- 33
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CTRY',
	'91',
	'Sri Lanka'
);

-- 34
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'CTRY',
	'01',
	'United States of America'
);

-- 35
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'STAT',
	'612900',
	'Australian Capital Territory'
);

-- 36
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'612',
	'New South Wales'
);

-- 37
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'613',
	'Victoria'
);

-- 38
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'9111',
	'Colombo'
);

-- 39
INSERT INTO Code
(
	CodeType,
	Code,
	CodeDescription
)
VALUES
(
	'LOCT',
	'0100',
	'Los Angeles'
);
\qecho '... done'



\qecho 'loading RelatedCode'
\qecho '------------'
\qecho '...'
-- 1
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	32,
	35
);

-- 2
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	32,
	36
);

-- 3
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	32,
	37
);

-- 4
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	33,
	38
);

-- 5
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	34,
	39
);

-- 6
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'STRG',
	35,
	7
);

-- 7
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	36,
	8
);

-- 8
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	37,
	9
);

-- 9
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	38,
	10
);

-- 10
INSERT INTO RelatedCode
(
	Relationship,
	ParentCodeId,
	ChildCodeId
)
VALUES
(
	'CNST',
	39,
	11
);
\qecho '... done'



\qecho 'loading Skill'
\qecho '------------'
\qecho '...'

-- INSERT SKILL
-- 1
INSERT INTO Skill
(
	SkillName
)
VALUES
(
	'Cooking'
);

-- 2
INSERT INTO Skill
(
	SkillName
)
VALUES
(
	'Cleaning'
);

-- 3
INSERT INTO Skill
(
	SkillName
)
VALUES
(
	'Programming'
);

-- 4
INSERT INTO Skill
(
	SkillName
)
VALUES
(
	'Systems Analysis'
);
\qecho '... done'



\qecho 'loading Organisation'
\qecho '------------'
\qecho '...'

-- INSERT ORGANISATIONS
-- 1
INSERT INTO Organisation
(
	OrganisationName
)
VALUES
(
	'Flora'
);

-- 2
INSERT INTO Organisation
(
	OrganisationName
)
VALUES
(
	'Elephant House'
);

-- 3
INSERT INTO Organisation
(
	OrganisationName
)
VALUES
(
	'IBM'
);

-- 4
INSERT INTO Organisation
(
	OrganisationName
)
VALUES
(
	'Microsoft'
);
\qecho '... done'



\qecho 'loading Address'
\qecho '------------'
\qecho '...'

-- INSERT ADDRESSES
-- 1
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	7
);

-- 2
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	10
);

-- 3
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	7
);

-- 4
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	8
);

-- 5
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	9
);

-- 6
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'',
	'',
	'',
	'',
	'',
	'',
	'',
	11
);

-- 7
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'129 Boddington Crescent',
	'',
	'',
	'Kambah',
	'ACT',
	'2902',
	'Australia',
	7
);

-- 8
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'Unit 7',
	'5 Police Park Terrace',
	'',
	'Bambalapitiya',
	'COLOMBO',
	'7',
	'Sri Lanka',
	10
);

-- 9
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'131 Boddington Crescent',
	'',
	'',
	'Kambah',
	'ACT',
	'2902',
	'Australia',
	7
);

-- 10
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'55 High Street',
	'',
	'',
	'Sydney',
	'NSW',
	'2000',
	'Australia',
	8
);

-- 11
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'54 Collins Street',
	'',
	'',
	'Melbourne',
	'VIC',
	'3000',
	'Australia',
	9
);

-- 12
INSERT INTO Address
(
	AddressLine1,
	AddressLine2,
	AddressLine3,
	Location,
	State,
	Postcode,
	Country,
	LocationId
)
VALUES
(
	'10 Madison Park',
	'',
	'',
	'Beverly Hills',
	'LA',
	'90210',
	'United States',
	11
);
\qecho '... done'



\qecho 'loading Category'
\qecho '------------'
\qecho '...'
-- INSERT CATEGORIES
-- 1
INSERT INTO Category
(
	CategoryName
)
VALUES
(
	'Kitchen'
);

-- 2
INSERT INTO Category
(
	CategoryName
)
VALUES
(
	'Hospitality'
);

-- 3
INSERT INTO Category
(
	CategoryName
)
VALUES
(
	'Information Technology'
);

-- 4
INSERT INTO Category
(
	CategoryName
)
VALUES
(
	'Analytical'
);
\qecho '... done'



\qecho 'loading Volunteer'
\qecho '------------'
\qecho '...'
-- INSERT VOLUNTEERS
-- 1
INSERT INTO Volunteer VALUES (nextval('seq_Volunteer'::text));

INSERT INTO Person
(
	Title,
	FirstName,
	Surname,
	DateOfBirth,
	UserName,
	Password,
	ContactMethod
)
VALUES
(
	1,
	'Joseph',
	'Abhayaratna',
	'1978-03-17',
	'jabhay',
	md5('123456'),
	29
);

-- 2
INSERT INTO ContactDetails
(
	Email
)
VALUES
(
	'jabhay@actewagl.net.au'
);

INSERT INTO relPersonContactDetails
(
	PersonId,
	ContactDetailsId
)
VALUES
(
	1,
	1
);

INSERT INTO relVolunteerPerson
(
	VolunteerId,
	PersonId
)
VALUES
(
	1,
	1
);

INSERT INTO relPersonAddress
(
	PersonId,
	AddressId,
	AddressType
)
VALUES
(
	1,
	7,
	14
);

-- 2
INSERT INTO Volunteer VALUES (nextval('seq_Volunteer'::text));

INSERT INTO Person
(
	Title,
	FirstName,
	Surname,
	DateOfBirth,
	UserName,
	Password,
	ContactMethod
)
VALUES
(
	1,
	'Terry',
	'Johnson',
	'1948-05-20',
	'Terry',
	md5('123456'),
	30
);

INSERT INTO relVolunteerPerson
(
	VolunteerId,
	PersonId
)
VALUES
(
	2,
	2
);

INSERT INTO relPersonAddress
(
	PersonId,
	AddressId,
	AddressType
)
VALUES
(
	2,
	8,
	14
);

-- 3
INSERT INTO Volunteer VALUES (nextval('seq_Volunteer'::text));

INSERT INTO Person
(
	Title,
	FirstName,
	Surname,
	DateOfBirth,
	UserName,
	Password,
	ContactMethod
)
VALUES
(
	1,
	'Donald',
	'Trump',
	'1938-01-12',
	'Donald',
	md5('123456'),
	30
);

-- 2
INSERT INTO ContactDetails
(
	Email
)
VALUES
(
	'Donald.Trump@thedonald.com'
);

INSERT INTO relPersonContactDetails
(
	PersonId,
	ContactDetailsId
)
VALUES
(
	3,
	2
);

INSERT INTO relVolunteerPerson
(
	VolunteerId,
	PersonId
)
VALUES
(
	3,
	3
);

INSERT INTO relPersonAddress
(
	PersonId,
	AddressId,
	AddressType
)
VALUES
(
	3,
	12,
	14
);
\qecho '... done'



\qecho 'loading Opportunity'
\qecho '------------'
\qecho '...'
-- INSERT OPPORTUNITIES
-- 4
INSERT INTO Person
(
	Title,
	FirstName,
	Surname,
	DateOfBirth,
	UserName,
	Password,
	ContactMethod
)
VALUES
(
	1,
	'Bill',
	'Gates',
	'1958-01-01',
	'Bill',
	md5('123456'),
	31
);

-- 1
INSERT INTO Opportunity
(
	OrganisationId,
	OrganisationContact,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	1,
	3,
	18,
	21
);

-- 2
INSERT INTO Opportunity
(
	OrganisationId,
	OrganisationContact,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	2,
	3,
	18,
	21
);

INSERT INTO Opportunity
(
	OrganisationId,
	OrganisationContact,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	3,
	4,
	18,
	21
);

INSERT INTO Opportunity
(
	OrganisationId,
	OrganisationContact,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	4,
	4,
	18,
	21
);
\qecho '... done'



\qecho 'loading relOrganisationAddress'
\qecho '------------'
\qecho '...'
--- INSERT relOrganisationAddress
INSERT INTO relOrganisationAddress
(
	OrganisationId,
	AddressId,
	AddressType
)
VALUES
(
	3,
	10,
	14
);

INSERT INTO relOrganisationAddress
(
	OrganisationId,
	AddressId,
	AddressType
)
VALUES
(
	4,
	11,
	14
);
\qecho '... done'



\qecho 'loading relCategorySkill'
\qecho '------------'
\qecho '...'
-- INSERT relCategorySkill
INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	1,
	1
);

INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	2,
	1
);

INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	2,
	2
);

INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	3,
	3
);

INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	3,
	4
);

INSERT INTO relCategorySkill
(
	CategoryId,
	SkillId
)
VALUES
(
	4,
	4
);
\qecho '... done'



\qecho 'loading WorkProfiles'
\qecho '------------'
\qecho '...'
-- INSERT WORKPROFILES
INSERT INTO WorkProfile
(
	VolunteerId,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	1,
	16,
	20
);

INSERT INTO WorkProfile
(
	VolunteerId
)
VALUES
(
	1
);

INSERT INTO WorkProfile
(
	VolunteerId,
	FPC_Flag,
	PermTempFlag
)
VALUES
(
	2,
	18,
	21
);
\qecho '... done'




\qecho 'loading relVolunteerAddress'
\qecho '------------'
\qecho '...'
-- INSERT relVolunteerAddress.sql
INSERT INTO relVolunteerAddress
(
	VolunteerId,
	AddressId
)
VALUES
(
	1,
	1
);

INSERT INTO relVolunteerAddress
(
	VolunteerId,
	AddressId
)
VALUES
(
	2,
	3
);
\qecho '... done'



\qecho 'loading relVolunteerSkill'
\qecho '------------'
\qecho '...'
-- INSERT relVolunteerSkill
INSERT INTO relVolunteerSkill
(
	VolunteerId,
	SkillId
)
VALUES
(
	1,
	3
);

INSERT INTO relVolunteerSkill
(
	VolunteerId,
	SkillId
)
VALUES
(
	1,
	4
);

INSERT INTO relVolunteerSkill
(
	VolunteerId,
	SkillId
)
VALUES
(
	2,
	3
);
\qecho '... done'



\qecho 'loading relOpportunityAddress'
\qecho '------------'
\qecho '...'
-- INSERT relOpportunityAddress
INSERT INTO relOpportunityAddress
(
	OpportunityId,
	AddressId
)
VALUES
(
	1,
	7
);

INSERT INTO relOpportunityAddress
(
	OpportunityId,
	AddressId
)
VALUES
(
	2,
	8
);
\qecho '... done'

 

\qecho 'loading relOpportunitySkill'
\qecho '------------'
\qecho '...'
-- INSERT relOpportunitySkill
INSERT INTO relOpportunitySkill
(
	OpportunityId,
	SkillId
)
VALUES
(
	1,
	4
);

INSERT INTO relOpportunitySkill
(
	OpportunityId,
	SkillId
)
VALUES
(
	2,
	1
);
\qecho '... done'

<?php

/* Get personal details for a specified username and password id */
$success = pg_query($conn, "PREPARE GetPersonalDetails (varchar(10), varchar(128))
				 AS 
			     SELECT c.CodeDescription,
                                    p.FirstName,
                                    p.Surname
                               FROM Person p
                              INNER JOIN Code c
                                 ON p.Title = c.CodeId
                              WHERE p.UserName = $1
                                AND p.Password = $2");

if (!$success) {
  echo pg_last_error();
}

/* Get organisation of organisation contact */
$success = pg_query($conn, "PREPARE GetOrganisationOfContact (integer)
				 AS 
			     SELECT org.OrganisationName
			       FROM Person p
			      INNER JOIN Opportunity o
				 ON p.PersonId = o.OrganisationContact
			      INNER JOIN Organisation org
				 ON o.OrganisationId = org.OrganisationId
			      WHERE p.PersonId = $1
			      GROUP BY org.OrganisationName");

if (!$success) {
  echo pg_last_error();
}

/* Get codes for a specified code Id */
$success = pg_query($conn, "PREPARE GetCodesForCodeType (char(4))
                                 AS 
                             SELECT CodeId,
                                    CodeDescription
			       FROM Code
			      WHERE CodeType = $1");
if (!$success) {
  echo pg_last_error();
}

/* Get the child codes for a specified relationship type and parent Id */
$success = pg_query($conn, "PREPARE GetChildCodesForRelationship (char(4),integer)
				 AS
			     SELECT c2.CodeId,
			            c2.CodeDescription
			       FROM Code c1
			      INNER JOIN RelatedCode rc
				 ON c1.CodeId = rc.ParentCodeId
                              INNER JOIN Code c2
				 ON rc.ChildCodeId = c2.CodeId
                              WHERE rc.Relationship = $1
				AND c1.CodeId = $2");

if (!$success) {
  echo pg_last_error();
}

/* Get skill ids and names */
$success = pg_query($conn, "PREPARE GetSkills
				 AS
			     SELECT SkillId,
			    	    SkillName
			       FROM Skill");

if (!$success) {
  echo pg_last_error();
}

/* Get skill ids and names not already assigned to a specified volunteer id*/
$success = pg_query($conn, "PREPARE VolunteerGetRemainingSkills (integer)
				 AS
			     SELECT s.SkillId,
			    	    s.SkillName
			       FROM Skill s
			       LEFT OUTER JOIN relVolunteerSkill vs
			            INNER JOIN Volunteer v
				       ON vs.VolunteerId = v.VolunteerId
				      AND v.VolunteerId = $1
				 ON s.SkillId = vs.SkillId
			      WHERE v.VolunteerId ISNULL");

if (!$success) {
  echo pg_last_error();
}

/* Get skill ids and names not already assigned to a specified opportunity id*/
$success = pg_query($conn, "PREPARE OpportunityGetRemainingSkills (integer)
				 AS
			     SELECT s.SkillId,
			    	    s.SkillName
			       FROM Skill s
			       LEFT OUTER JOIN relOpportunitySkill os
			            INNER JOIN Opportunity o
				       ON os.OpportunityId = o.OpportunityId
				      AND o.OpportunityId = $1
				 ON s.SkillId = os.SkillId
			      WHERE o.OpportunityId ISNULL");

if (!$success) {
  echo pg_last_error();
}

/* Get the Messages for a specified volunteer Id */
$success = pg_query($conn, "PREPARE VolunteerGetMessages (integer)
				 AS
			     SELECT o.OpportunityId,
				    m.MatchIdentifier
			       FROM Match m
			      INNER JOIN relVolunteerSkill vs
				 ON m.VolunteerSkillId = vs.VolunteerSkillId
			      INNER JOIN relVolunteerAddress va
				 ON m.VolunteerAddressId = va.VolunteerAddressId
			      INNER JOIN Volunteer v
				 ON vs.VolunteerId = v.VolunteerId
				AND va.VolunteerId = v.VolunteerId
			      INNER JOIN relOpportunitySkill os
				 ON m.OpportunitySkillId = os.OpportunitySkillId
			      INNER JOIN relOpportunityAddress oa
				 ON m.OpportunityAddressId = oa.OpportunityAddressId
			      INNER JOIN Opportunity o
				 ON os.OpportunityId = o.OpportunityId
				AND oa.OpportunityId = o.OpportunityId
			      WHERE v.VolunteerId = $1
				AND ContactVolunteer = true
				AND VolunteerRead = false");

if (!$success) {
  echo pg_last_error();
}

$success = pg_query($conn, "PREPARE OpportunityGetMessages (integer)
				 AS
			     SELECT v.VolunteerId,
				    m.MatchIdentifier
			       FROM Match m
			      INNER JOIN relVolunteerSkill vs
				 ON m.VolunteerSkillId = vs.VolunteerSkillId
			      INNER JOIN relVolunteerAddress va
				 ON m.VolunteerAddressId = va.VolunteerAddressId
			      INNER JOIN Volunteer v
				 ON vs.VolunteerId = v.VolunteerId
				AND va.VolunteerId = v.VolunteerId
			      INNER JOIN relOpportunitySkill os
				 ON m.OpportunitySkillId = os.OpportunitySkillId
			      INNER JOIN relOpportunityAddress oa
				 ON m.OpportunityAddressId = oa.OpportunityAddressId
			      INNER JOIN Opportunity o
				 ON os.OpportunityId = o.OpportunityId
				AND oa.OpportunityId = o.OpportunityId
			      WHERE o.OrganisationContact = $1
				AND ContactOrganisation = true
				AND OrganisationRead = false");

if (!$success) {
  echo pg_last_error();
}

/* Get the opportunity Id for a specified match Id */
$success = pg_query($conn, "PREPARE VolunteerGetOpportunitiesForMatchId (integer)
				 AS
			     SELECT o.OpportunityId
			       FROM Match m
			      INNER JOIN relOpportunitySkill os
				 ON m.OpportunitySkillId = os.OpportunitySkillId
			      INNER JOIN relOpportunityAddress oa
				 ON m.OpportunityAddressId = oa.OpportunityAddressId
			      INNER JOIN Opportunity o
				 ON os.OpportunityId = o.OpportunityId
				AND oa.OpportunityId = o.OpportunityId
			      WHERE MatchId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the Volunteer Id for a specified match Id */
$success = pg_query($conn, "PREPARE OrganisationGetVolunteersForMatchId (integer)
				 AS
			     SELECT v.VolunteerId
			       FROM Match m
			      INNER JOIN relVolunteerSkill vs
				 ON m.VolunteerSkillId = vs.VolunteerSkillId
			      INNER JOIN relVolunteerAddress va
				 ON m.VolunteerAddressId = va.VolunteerAddressId
			      INNER JOIN Volunteer v
				 ON vs.VolunteerId = v.VolunteerId
				AND va.VolunteerId = v.VolunteerId
			      WHERE MatchId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the skills for a specified opportunity Id */
$success = pg_query($conn, "PREPARE GetSkillsForOpportunityId (integer)
				 AS
			     SELECT s.SkillName,
				    s.SkillId
			       FROM relOpportunitySkill os
			      INNER JOIN Skill s
				 ON os.SkillId = s.SkillId
			      WHERE os.OpportunityId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the skills for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetSkillsForVolunteerId (integer)
				 AS
			     SELECT s.SkillName,
				    s.SkillId
			       FROM relVolunteerSkill vs
			      INNER JOIN Skill s
				 ON vs.SkillId = s.SkillId
			      WHERE vs.VolunteerId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the personal details for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetPersonalDetailsForVolunteerId (integer)
				 AS
			     SELECT ctitle.CodeDescription AS Title,
				    p.FirstName,
				    p.Surname
			       FROM relVolunteerPerson vp
			      INNER JOIN Person p
				 ON vp.PersonId = p.PersonId
			      INNER JOIN Code ctitle
				 ON p.Title = ctitle.CodeId
			      WHERE vp.VolunteerId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the skills for a specified person Id */
$success = pg_query($conn, "PREPARE GetPersonalDetailsForOpportunityId (integer)
				 AS
			     SELECT ctitle.CodeDescription AS Title,
				    p.FirstName,
				    p.Surname
			       FROM Opportunity o
			      INNER JOIN Person p
				 ON o.OrganisationContact = p.PersonId
			      INNER JOIN Code ctitle
				 ON p.Title = ctitle.CodeId
			      WHERE o.OpportunityId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the skills for a specified person Id */
$success = pg_query($conn, "PREPARE GetPersonalDetailsForPersonId (integer)
				 AS
			     SELECT ctitle.CodeDescription AS Title,
				    p.FirstName,
				    p.Surname
			       FROM Person p
			      INNER JOIN Code ctitle
				 ON p.Title = ctitle.CodeId
			      WHERE p.PersonId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the Tenure and Basis for a specified opportunity Id */
$success = pg_query($conn, "PREPARE GetTenureAndBasisForOpportunityId (integer)
				 AS
			     SELECT c1.CodeDescription AS Basis,
				    c2.CodeDescription AS Tenure
			       FROM Opportunity o
			      INNER JOIN Code c1
				 ON o.FPC_Flag = c1.CodeId
			      INNER JOIN Code c2
				 ON o.PermTempFlag = c2.CodeId
			      WHERE OpportunityId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the Tenures for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetTenuresForVolunteerId (integer)
				 AS
			     SELECT c1.CodeDescription AS Tenure
			       FROM Volunteer v
			      INNER JOIN WorkProfile w
				 ON v.VolunteerId = w.VolunteerId
			      INNER JOIN Code c1
				 ON w.PermTempFlag = c1.CodeId
			      WHERE v.VolunteerId = $1
			      GROUP BY c1.CodeDescription");

if (!$success) {
  echo pg_last_error();
}

/* Get the Basis for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetBasisForVolunteerId (integer)
				 AS
			     SELECT c1.CodeDescription AS Basis
			       FROM Volunteer v
			      INNER JOIN WorkProfile w
				 ON v.VolunteerId = w.VolunteerId
			      INNER JOIN Code c1
				 ON w.FPC_Flag = c1.CodeId
			      WHERE v.VolunteerId = $1
			      GROUP BY c1.CodeDescription");

if (!$success) {
  echo pg_last_error();
}

/* Get contact method for a specified opportunity Id */
$success = pg_query($conn, "PREPARE GetContactMethodForOpportunityId (integer)
				 AS
			     SELECT c.CodeDescription AS ContactMethod
			       FROM Opportunity o
			      INNER JOIN Person p
				 ON o.OrganisationContact = p.PersonId
			      INNER JOIN Code c
				 ON p.ContactMethod = c.CodeId
			      WHERE o.OpportunityId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get contact method for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetContactMethodForVolunteerId (integer)
				 AS
			     SELECT c.CodeDescription AS ContactMethod
			       FROM relVolunteerPerson vp
			      INNER JOIN Person p
				 ON vp.PersonId = p.PersonId
			      INNER JOIN Code c
				 ON p.ContactMethod = c.CodeId
			      WHERE vp.VolunteerId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the locations for a specified opportunity Id */
$success = pg_query($conn, "PREPARE GetLocationsForOpportunityId (integer)
				 AS
			     SELECT c.CodeDescription AS Location
			       FROM relOpportunityAddress oa
			      INNER JOIN Address a
				 ON oa.AddressId = a.AddressId
			      INNER JOIN Code c
				 ON a.LocationId = c.CodeId
			      WHERE oa.OpportunityId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the locations for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetLocationsForVolunteerId (integer)
				 AS
			     SELECT c.CodeDescription AS Location,
				    c.CodeId AS LocationId
			       FROM relVolunteerAddress va
			      INNER JOIN Address a
				 ON va.AddressId = a.AddressId
			      INNER JOIN Code c
				 ON a.LocationId = c.CodeId
			      WHERE va.VolunteerId = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get the primary key for a specified match Id and opportunity Id combination*/
$success = pg_query($conn, "PREPARE VolGetMatchIdentifierForMatchId (integer, integer)
				 AS
			     SELECT MatchIdentifier
			       FROM Match m
			      INNER JOIN relOpportunitySkill os
				 ON m.OpportunitySkillId = os.OpportunitySkillId
			      INNER JOIN relOpportunityAddress oa
				 ON m.OpportunityAddressId = oa.OpportunityAddressId
			      INNER JOIN Opportunity o
				 ON os.OpportunityId = o.OpportunityId
				AND oa.OpportunityId = o.OpportunityId
			      WHERE m.MatchId = $1
				AND o.OpportunityId = $2");

if (!$success) {
  echo pg_last_error();
}

/* Get the primary key for a specified match Id and opportunity Id combination */
$success = pg_query($conn, "PREPARE OrgGetMatchIdentifierForMatchId (integer, integer)
				 AS
			     SELECT MatchIdentifier
			       FROM Match m
			      INNER JOIN relVolunteerSkill vs
				 ON m.VolunteerSkillId = vs.VolunteerSkillId
			      INNER JOIN relVolunteerAddress va
				 ON m.VolunteerAddressId = va.VolunteerAddressId
			      INNER JOIN Volunteer v
				 ON vs.VolunteerId = v.VolunteerId
				AND va.VolunteerId = v.VolunteerId
			      WHERE m.MatchId = $1
				AND v.VolunteerId = $2");

if (!$success) {
  echo pg_last_error();
}

/* Get result if opportunity has been contacted using a specified match Id */
$success = pg_query($conn, "PREPARE VolunteerCheckIfOrgContacted (integer)
				 AS
			     SELECT *
			       FROM Match
			      WHERE MatchIdentifier = $1
				AND ContactOrganisation = true");

if (!$success) {
  echo pg_last_error();
}

/* Get result if volunteer has been contacted using a specified match Id */
$success = pg_query($conn, "PREPARE OrgCheckIfVolunteerContacted (integer)
				 AS
			     SELECT *
			       FROM Match
			      WHERE MatchIdentifier = $1
				AND ContactVolunteer = true");

if (!$success) {
  echo pg_last_error();
}

/* Get opportunity ids for an organisation contact Id */
$success = pg_query($conn, "PREPARE GetOpportunitiesForPersonId (integer)
				 AS
			     SELECT o.OpportunityId
			       FROM Opportunity o
			      WHERE OrganisationContact = $1");

if (!$success) {
  echo pg_last_error();
}

/* Get profile ids for a specified volunteer Id */
$success = pg_query($conn, "PREPARE GetProfilesForVolunteerId (integer)
				 AS 
			     SELECT WorkProfileId
			       FROM WorkProfile
			      WHERE VolunteerId = $1");

/* Get tenure and basis for a specified profile id */
$success = pg_query($conn, "PREPARE GetTenureAndBasisForProfileId (integer)
				 AS
			     SELECT c1.CodeDescription AS Basis,
				    c2.CodeDescription AS Tenure
			       FROM WorkProfile w
			      INNER JOIN Code c1
				 ON w.FPC_Flag = c1.CodeId
			      INNER JOIN Code c2
				 ON w.PermTempFlag = c2.CodeId
			      WHERE WorkProfileId = $1");

?>

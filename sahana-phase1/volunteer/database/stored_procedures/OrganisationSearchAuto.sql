CREATE OR REPLACE FUNCTION OrganisationSearchAuto
(
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	OppId ALIAS FOR $1;
	IID Integer;

BEGIN

	IID := nextval(\'seq_Match\'::text);

	INSERT INTO Match
	(
		MatchId,
		MatchType,
		VolunteerSkillId,
		OpportunitySkillId,
		VolunteerAddressId,
		OpportunityAddressId
	)
	SELECT IID,
	       28,
	       vs.VolunteerSkillId,
	       os.OpportunitySkillId,
	       va.VolunteerAddressId,
	       oa.OpportunityAddressId
	  FROM Volunteer v
	 INNER JOIN WorkProfile w
	    ON v.VolunteerId = w.VolunteerId
	 INNER JOIN relVolunteerSkill vs
	    ON v.VolunteerId = vs.VolunteerId
	 INNER JOIN Skill s
	    ON vs.SkillId = s.SkillId
         INNER JOIN relVolunteerPerson vp
	    ON v.VolunteerId = vp.VolunteerId
         INNER JOIN Person p
 	    ON vp.PersonId = p.PersonId
	 INNER JOIN relVolunteerAddress va
	    ON v.VolunteerId = va.VolunteerId
	 INNER JOIN Address a
	    ON va.AddressId = a.AddressId
         INNER JOIN Address a2
            ON a.LocationId = a2.LocationId
	 INNER JOIN Code c
	    ON a2.LocationId = c.CodeId
	 INNER JOIN relOpportunityAddress oa
	    ON a2.AddressId = oa.AddressId
	 INNER JOIN relOpportunitySkill os
	    ON s.SkillId = os.SkillId
	 INNER JOIN Opportunity o
	    ON os.OpportunityId = o.OpportunityId
	   AND oa.OpportunityId = o.OpportunityId
	 WHERE o.OpportunityId = OppId
	   AND (w.FPC_Flag = o.FPC_Flag OR
	        w.FPC_Flag = 18 OR
		o.FPC_Flag = 18)
	   AND (w.PermTempFlag = o.PermTempFlag OR
		w.PermTempFlag = 21 OR
		o.PermTempFlag = 21)
	 GROUP BY
	       vs.VolunteerSkillId,
	       os.OpportunitySkillId,
	       va.VolunteerAddressId,
	       oa.OpportunityAddressId;

	RETURN currval(\'seq_Match\'::text);

END
' LANGUAGE 'plpgsql'
CREATE OR REPLACE FUNCTION OrganisationSearch
(
	integer,
	integer,
	integer,
	integer
)
RETURNS INTEGER
AS '

DECLARE -- variables
	FPC      ALIAS FOR $1;
	PermTemp ALIAS FOR $2;
        SkId     ALIAS FOR $3;
	LocId    ALIAS FOR $4;
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
	       26,
	       vs.VolunteerSkillId,
	       NULL,
	       va.VolunteerAddressId,
	       NULL
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
	 WHERE s.SkillId = SkId
           AND a.LocationId = LocId
           AND (w.PermTempFlag = PermTemp OR
                w.PermTempFlag = 21 OR
                PermTemp = 21)
           AND (w.FPC_Flag = FPC OR
	        w.FPC_Flag = 18 OR
                FPC = 18)
	 GROUP BY
	       vs.VolunteerSkillId,
	       va.VolunteerAddressId;

	RETURN currval(\'seq_Match\'::text);

END
' LANGUAGE 'plpgsql'
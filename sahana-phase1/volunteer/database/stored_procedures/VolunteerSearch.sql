CREATE OR REPLACE FUNCTION VolunteerSearch
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
	       25,
	       NULL,
	       os.OpportunitySkillId,
	       NULL,
	       oa.OpportunityAddressId
	  FROM Opportunity o
	 INNER JOIN relOpportunityAddress oa
	    ON o.OpportunityId = oa.OpportunityId
         INNER JOIN Address a
            ON oa.AddressId = a.AddressId
	 INNER JOIN relOpportunitySkill os
	    ON o.OpportunityId = os.OpportunityId
	 INNER JOIN Skill s
	    ON os.SkillId = s.SkillId
	 INNER JOIN Code c
	    ON a.LocationId = c.CodeId
	 WHERE s.SkillId = SkId
           AND a.LocationId = LocId
           AND (o.FPC_Flag = FPC OR
                o.FPC_Flag = 18 OR
                FPC = 18)
           AND (o.PermTempFlag = PermTemp OR
                o.PermTempFlag = 21 OR
                PermTemp = 21)
	 GROUP BY
	       os.OpportunitySkillId,
	       oa.OpportunityAddressId;

	RETURN currval(\'seq_Match\'::text);

END

' LANGUAGE 'plpgsql'
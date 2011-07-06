--
-- Delete a reported person and all related data and optionally also Notes.
-- Optional Note deletion needed since some deletions are simply for correcting erroneous data in the person record
-- and are NOT an attempt to expunge data.
-- Does not delete locally registered user data. 
--

CREATE PROCEDURE delete_reported_person(IN id VARCHAR(128),IN deleteNotes BOOLEAN)
BEGIN

-- Delete reporter from person_uuid (child tables: person_status)
DELETE p.* FROM person_uuid p, person_to_report pr WHERE pr.rep_uuid = p.p_uuid AND pr.p_uuid = id AND pr.rep_uuid NOT IN (SELECT p_uuid FROM users);

-- Delete person from person_uuid (child tables: person_status, person_to_report, person_details, person_physical)
DELETE person_uuid.* FROM person_uuid WHERE p_uuid = id;

-- Delete person from pfif_person
DELETE pfif_person.* FROM pfif_person WHERE p_uuid = id;

IF deleteNotes THEN
  -- Delete note from pfif_note 
  DELETE pfif_note.* FROM pfif_note WHERE p_uuid = id;

  -- Set to null linked records in pfif_note 
  UPDATE pfif_note SET linked_person_record_id = NULL WHERE linked_person_record_id = id;
END IF;

END

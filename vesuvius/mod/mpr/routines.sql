CREATE PROCEDURE delete_person(IN id VARCHAR(128))
BEGIN

-- Delete reporter from contact
DELETE c.* FROM contact c, person_to_report pr WHERE pr.rep_uuid = c.pgoc_uuid AND pr.p_uuid = id;

-- Delete reporter from location_details
DELETE ld.* FROM location_details ld, person_to_report pr WHERE pr.rep_uuid = ld.poc_uuid AND pr.p_uuid = id;

-- Delete reporter from person_uuid (child tables: person_status)
DELETE p.* FROM person_uuid p, person_to_report pr WHERE pr.rep_uuid = p.p_uuid AND pr.p_uuid = id AND pr.rep_uuid NOT IN (SELECT p_uuid FROM users);

-- Delete person from person_uuid (child tables: person_status, person_to_report, person_details, person_physical)
DELETE person_uuid.* FROM person_uuid WHERE p_uuid = id;

-- Delete person from pfif_person
DELETE pfif_person.* FROM pfif_person WHERE p_uuid = id;

-- Delete note from pfif_note 
DELETE pfif_note.* FROM pfif_note WHERE p_uuid = id;

-- Set to null linked records in pfif_note 
UPDATE pfif_note SET linked_person_record_id = NULL WHERE p_uuid = id;

-- Delete person from contact
DELETE contact.* FROM contact WHERE pgoc_uuid = id;

-- Delete person from image
DELETE image.* from image where x_uuid = id;

END

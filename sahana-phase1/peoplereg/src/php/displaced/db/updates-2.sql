
use mambo;

insert into sahana_attributes
	(name, caption, data_type, publicity, search) values
	('division', 'Division', 1, 0, 1),
	('gs_division', 'Grama Sevaka division', 1, 0, 1),
	('village', 'Village', 1, 0, 1),
	('family_serial_no', 'Family serial no', 1, 0, 1),
	('occupation', 'Occupation', 1, 0, 1),
	('property_owned', 'Nature of property owned', 1, 0, 0),
	('current_location', 'Current location', 1, 0, 1),
	('current_camp', 'Current camp', 1, 0, 1),
	('relief_period', 'Period for which relief is needed', 1, 0, 0),
	('remarks', 'Remarks', 1, 0, 1),

	('num_males', 'Number of males', 0, 0, 0),
	('num_females', 'Number of females', 0, 0, 0),
	('num_children', 'Number of children', 0, 0, 0),
	('income', 'Income', 0, 0, 0),
	('other_income', 'Income from other sources', 0, 0, 0),
	('property_value', 'Value of property owned', 0, 0, 0),
	('relief_adults', 'No of adults who need relief', 0, 0, 0),
	('relief_children', 'No of children who need relief', 0, 0, 0);


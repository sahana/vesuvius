# Connection: local # Host: localhost # Saved: 2004-12-31 08:25:08 #  # Connection: local # Host: localhost # Saved: 2004-12-31 05:18:36 #   # 'OrgCode','ContactPerson' , 'OrgName','Status', 'OrgAddress','ContactNumber',  'EmailAddress', 'CountryOfOrigin', 'FacilitiesAvailable' , 'WorkingAreas' , 'Comments' delete from Organization; 

delete from organization;
delete from category;  
delete from district; 
delete from priority; 
delete from fulfillstatus; 
delete from requeststatus; 
delete from sitetype; 
delete from user; 
DELETE FROM CAMPS_CAMP;
DELETE FROM CAMPS_AREA;
DELETE FROM CAMPS_DIVISION;
DELETE FROM CAMPS_DISTRICT;
DELETE FROM CAMPS_PROVINCE;


INSERT INTO category VALUES('1', 'Dry Rations');
INSERT INTO category VALUES('2', 'Milk Food');
INSERT INTO category VALUES('3', 'Infant Food');
INSERT INTO category VALUES('4', 'Water and Sanitation');
INSERT INTO category VALUES('5', 'Tents');
INSERT INTO category VALUES('6', 'Clothing');
INSERT INTO category VALUES('7', 'Bedding');
INSERT INTO category VALUES('8', 'Medical Goods');
INSERT INTO category VALUES('9', 'Medical Services');
INSERT INTO category VALUES('10', 'Volunteers');
INSERT INTO category VALUES('11', 'Other Goods');
INSERT INTO category VALUES('12', 'Other Services');


INSERT INTO district VALUES('CMB','Colombo');
INSERT INTO district VALUES('GMP','Gampaha');
INSERT INTO district VALUES('KUL','Kalutara');
INSERT INTO district VALUES('KAN','Kandy');
INSERT INTO district VALUES('MAT','Matale');
INSERT INTO district VALUES('NUR','Nuwara Eliya');
INSERT INTO district VALUES('GAL','Galle');
INSERT INTO district VALUES('MAR','Matara');
INSERT INTO district VALUES('HAM','Hambantota');
INSERT INTO district VALUES('JAF','Jaffna');
INSERT INTO district VALUES('MAN','Mannar');
INSERT INTO district VALUES('VAV','Vavuniya');
INSERT INTO district VALUES('MUL','Mullaitivu');
INSERT INTO district VALUES('KILL','Kilinochchi');
INSERT INTO district VALUES('BAT','Batticaloa');
INSERT INTO district VALUES('AMP','Ampara');
INSERT INTO district VALUES('TRIN','Trincomalee');
INSERT INTO district VALUES('KUR','Kurunegala');   
INSERT INTO district VALUES('PUT','Puttalam');  	  
INSERT INTO district VALUES('ANU','Anuradhapura');   
INSERT INTO district VALUES('POL','Polonnaruwa');  	  
INSERT INTO district VALUES('BAD','Badulla');  	  
INSERT INTO district VALUES('MON','Monaragala');   
INSERT INTO district VALUES('RAT','Ratnapura');   
INSERT INTO district VALUES('KEG','Kegalle');  	     


INSERT INTO priority VALUES('1', 'High'); 
INSERT INTO priority VALUES('2', 'Medium'); 
INSERT INTO priority VALUES('3', 'Low');  


INSERT INTO fulfillstatus VALUES('1', 'Under Consideration');
INSERT INTO fulfillstatus VALUES('2', 'On Route'); 
INSERT INTO fulfillstatus VALUES('3', 'Delivered');
INSERT INTO fulfillstatus VALUES('4', 'Withdrawn');


INSERT INTO requeststatus VALUES('Under Consideration','Under Consideration'); 
INSERT INTO requeststatus VALUES('Closed','Closed'); 
INSERT INTO requeststatus VALUES('Open', 'Closed');  


INSERT INTO sitetype VALUES('1', 'Hospital'); 
INSERT INTO sitetype VALUES('2', 'Place of Worship'); 
INSERT INTO sitetype VALUES('3', 'Camp');
INSERT INTO sitetype VALUES('4', 'School');


INSERT INTO organization(OrgType, OrgCode, OrgName) VALUES ('NGO','LSF','LSF');

INSERT INTO user VALUES('test', 'test123', 'LSF');


INSERT INTO CAMPS_DISTRICT VALUES('CMB','Colombo', '1');
INSERT INTO CAMPS_DISTRICT VALUES('GMP','Gampaha', '1');
INSERT INTO CAMPS_DISTRICT VALUES('KUL','Kalutara', '1');
INSERT INTO CAMPS_DISTRICT VALUES('KAN','Kandy', '6');
INSERT INTO CAMPS_DISTRICT VALUES('MAT','Matale', '6');
INSERT INTO CAMPS_DISTRICT VALUES('NUR','Nuwara Eliya', '6');
INSERT INTO CAMPS_DISTRICT VALUES('GAL','Galle', '2');
INSERT INTO CAMPS_DISTRICT VALUES('MAR','Matara', '2');
INSERT INTO CAMPS_DISTRICT VALUES('HAM','Hambantota', '2');
INSERT INTO CAMPS_DISTRICT VALUES('JAF','Jaffna', '9');
INSERT INTO CAMPS_DISTRICT VALUES('MAN','Mannar', '9');
INSERT INTO CAMPS_DISTRICT VALUES('VAV','Vavuniya', '9');
INSERT INTO CAMPS_DISTRICT VALUES('MUL','Mullaitivu', '9');
INSERT INTO CAMPS_DISTRICT VALUES('KILL','Kilinochchi', '9');
INSERT INTO CAMPS_DISTRICT VALUES('BAT','Batticaloa', '5');
INSERT INTO CAMPS_DISTRICT VALUES('AMP','Ampara', '5');
INSERT INTO CAMPS_DISTRICT VALUES('TRIN','Trincomalee', '5');
INSERT INTO CAMPS_DISTRICT VALUES('KUR','Kurunegala', '7');
INSERT INTO CAMPS_DISTRICT VALUES('PUT','Puttalam', '7');
INSERT INTO CAMPS_DISTRICT VALUES('ANU','Anuradhapura', '8');
INSERT INTO CAMPS_DISTRICT VALUES('POL','Polonnaruwa', '8');
INSERT INTO CAMPS_DISTRICT VALUES('BAD','Badulla', '4');
INSERT INTO CAMPS_DISTRICT VALUES('MON','Monaragala', '4');
INSERT INTO CAMPS_DISTRICT VALUES('RAT','Ratnapura', '3');
INSERT INTO CAMPS_DISTRICT VALUES('KEG','Kegalle', '3');


insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('1', 'Western Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('2', 'Southern Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('3', 'Sabaragamuwa Province');

insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('4', 'Uva Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('5', 'Eastern Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('6', 'Central Province');

insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('7', 'North-Western Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('8', 'North-Central Province');
insert into CAMPS_PROVINCE (PROV_CODE, PROV_NAME) values ('9', 'Northern Province'); 

--
-- Dumping data for table `bsm_sign`
--


INSERT INTO `bsm_sign` (`sign`, `sign_desc`, `sign_code`, `sign_priority`, `sign_enum`, `deactivate_dt`) VALUES
('Abdominal tenderness', 'Abdominal tenderness', NULL, NULL, 0, NULL),
('Ache', 'Ache', NULL, NULL, 0, NULL),
('Back stiffness', 'Back stiffness', NULL, NULL, 0, NULL),
('Buboes', 'Buboes', NULL, NULL, 0, NULL),
('Coma', 'Coma', NULL, NULL, 0, NULL),
('Cranial nerve palsy', 'Cranial Nerve palsy', NULL, NULL, 0, NULL),
('Dehydration', 'Dehydration', NULL, NULL, 0, NULL),
('Delirium', 'Delirium', NULL, NULL, 0, NULL),
('Distended abdomen', 'Distended abdomen', NULL, NULL, 0, NULL),
('Drowsiness', 'Drowsiness', NULL, NULL, 0, NULL),
('Eye signs', 'Eye signs', NULL, NULL, 0, NULL),
('Facial muscle paralysis', 'Facial muscle paralysis', NULL, NULL, 0, NULL),
('Features of bulbar palsy', 'Features of bulbar palsy', NULL, NULL, 0, NULL),
('Fever', 'Fever', NULL, NULL, 0, NULL),
('Gangeens', 'Gangeens', NULL, NULL, 0, NULL),
('Grey membrane covering throat', 'Grey membrane covering throat', NULL, NULL, 0, NULL),
('Heart arrythmias', 'Heart arrythmias', NULL, NULL, 0, NULL),
('High fever', 'High fever', NULL, NULL, 0, NULL),
('Hoarseness', 'Swollen glands', NULL, NULL, 0, NULL),
('Increase sensitivity to couch', 'Increase sensitivity to couch', NULL, NULL, 0, NULL),
('Kidney failure', 'Kidney failure', NULL, NULL, 0, NULL),
('Limb paralysis', 'Paralysis of the limbs', NULL, NULL, 0, NULL),
('Liver failure', 'Liver failure', NULL, NULL, 0, NULL),
('Mucosal tissue bleed', 'Bleeding from mucosal tissues', NULL, NULL, 0, NULL),
('Muscle spasms', 'Muscle spasms', NULL, NULL, 0, NULL),
('Neck stiffnes', 'Neck stiffnes', NULL, NULL, 0, NULL),
('Nose bleed', 'Bleeding from nose', NULL, NULL, 0, NULL),
('Paralysis of the limbs', 'Paralysis of the limbs', NULL, NULL, 0, NULL),
('Pneumonia', 'Pneumonia', NULL, NULL, 0, NULL),
('Rash', 'Rash', NULL, NULL, 0, NULL),
('Red eyes', 'Red eyes', NULL, NULL, 0, NULL),
('Red infected wound', 'Red infected wound', NULL, NULL, 0, NULL),
('Red toungue', 'Red toungue', NULL, NULL, 0, NULL),
('Seizures', 'Seizures', NULL, NULL, 0, NULL),
('Stomach', 'Stomach', NULL, NULL, 0, NULL),
('Swollen glands', 'Swollen glands', NULL, NULL, 0, NULL),
('Tachycardia', 'Tachycardia', NULL, NULL, 0, NULL),
('Touch sensitive', 'Increase sensitivity to couch', NULL, NULL, 0, NULL),
('Typhoid state', 'Typhoid state', NULL, NULL, 0, NULL),
('Vomitting', 'Vomitting', NULL, NULL, 0, NULL),
('Whooping', 'Whooping', NULL, NULL, 0, NULL),
('Wound with gray patchy material', 'Wound with gray patchy material', NULL, NULL, 0, NULL),
('Yellowing of sclera', 'Yellowing of sclera', NULL, NULL, 0, NULL),
('Yellowing of skin', 'Yellowing of skin', NULL, NULL, 0, NULL);





--
-- Dumping data for table `bsm_symptom`
--

INSERT INTO `bsm_symptom` (`symptom`, `symp_desc`, `symp_code`, `symp_priority`, `symp_enum`, `deactivate_dt`) VALUES
('Ache', NULL, '', '', 0, NULL),
('Watery Diarrhoea', NULL, '', '', 0, NULL),
('Nausea', NULL, '', '', 0, NULL),
('Vomitting', NULL, '', '', 0, NULL),
('Muscle Cramps', NULL, '', '', 0, NULL),
('Thirst', NULL, '', '', 0, NULL),
('Fever', NULL, '', '', 0, NULL),
('Headache', NULL, '', '', 0, NULL),
('Fatigue', NULL, '', '', 0, NULL),
('Diarrhea', NULL, '', '', 0, NULL),
('Chest pain', NULL, '', '', 0, NULL),
('Muscle aches', NULL, '', '', 0, NULL),
('Cough Blood', 'Cough with blood stained sputum', '', '', 0, NULL),
('Loss of appetite', NULL, '', '', 0, NULL),
('Dizziness', NULL, '', '', 0, NULL),
('Abdominal pain', NULL, '', '', 0, NULL),
('Constipation', NULL, '', '', 0, NULL),
('Difficult to swollow', NULL, '', '', 0, NULL),
('Difficulty in breathing', NULL, '', '', 0, NULL),
('Sore throat', NULL, '', '', 0, NULL),
('Stomach', NULL, '', '', 0, NULL),
('Painfull swollowing', NULL, '', '', 0, NULL),
('Chills', NULL, '', '', 0, NULL),
('Malaise', NULL, '', '', 0, NULL),
('Abdominal cramp', NULL, '', '', 0, NULL),
('Blood stained stools', NULL, '', '', 0, NULL),
('Mocous stained stools', NULL, '', '', 0, NULL),
('Runny nose', NULL, '', '', 0, NULL),
('Sneezing', NULL, '', '', 0, NULL),
('Mild cough', NULL, '', '', 0, NULL),
('Low-grade fever', NULL, '', '', 0, NULL),
('Dry Cough', NULL, '', '', 0, NULL);


--
-- Dumping data for table `bsm_serv_state`
--

/* INSERT INTO `bsm_serv_state` (`serv_state`, `serv_state_seq`, `serv_cate`, `serv_type`, `serv_status_enum`, `serv_status_desc`, `deactivate_dt`) VALUES
('To Do', NULL, 'Health Care Worker', 'Investigate', 0, 'service request has been received in to do list', NULL),
('Requested', NULL, 'Health Care Worker', 'Investigate', 0, NULL, NULL),
('Work in Progress', NULL, 'Health Care Worker', 'Investigate', 0, NULL, NULL),
('Canceled', NULL, 'Health Care Worker', 'Investigate', 0, 'Investigation canceled due to a reason, see notes', NULL),
('Completed', NULL, 'Health Care Worker', 'Investigate', 0, 'task completed', NULL),
('Closed', NULL, 'Health Care Worker', 'Investigate', 0, 'Investigation completed and cases is closed', NULL);
*/


INSERT INTO `bsm_serv_cate` (`serv_cate`, `serv_cate_enum`, `serv_desc`, `deactivate_dt`) VALUES
('Cases', 0, 'services to be carried out with respect to cases', NULL),
('Disease', 0, 'services to be carried out with respect to diseases', NULL),
('Health Care Worker', 0, 'services carried out by health care workers - doctors, nurses, etc', NULL),
('Health Facility', 0, 'services to be carried out by health facilities', NULL),
('Patient', 0, 'services to be carried out by patients -', NULL);
--
-- Dumping data for table `bsm_serv_type`
--



INSERT INTO `bsm_serv_type` (`serv_type_enum`, `serv_type`, `serv_cate`, `serv_type_desc`, `serv_proc`, `serv_prov_prsn_type`, `serv_recp_prsn_type`, `serv_exp_rslt`, `serv_exp_tm`, `deactivate_dt`) VALUES
(0, 'Cardiac', 'Health Facility', 'cardiac intensive care', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'FBC', 'Cases', 'patient should obtain full blood count', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Investigate', 'Health Care Worker', '', 'health care worker to visit patient to verify case', NULL, NULL, NULL, NULL, NULL),
(0, 'Maternity', 'Health Facility', 'pre and post maternity care', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Notify', 'Disease', 'notify specific disease', NULL, NULL, 'MOH', NULL, NULL, NULL),
(0, 'Quarantine', 'Cases', 'patinet must be quarantined', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Report H399', 'Health Care Worker', 'notify weekly notifiable diseases to regional epidemiological unit', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Report H544', 'Health Care Worker', 'notify divisional health care worker of notifiable disease', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'Urine Test', 'Cases', 'patient should obtain urine test', NULL, NULL, NULL, NULL, NULL, NULL),
(0, 'X-Ray', 'Cases', 'patient should obtain an X-Ray', NULL, NULL, NULL, NULL, NULL, NULL);


INSERT INTO `bsm_prsn_role` (`prsn_role`, `prsn_role_desc`, `prsn_role_enum`, `deactivate_dt`) VALUES
('Health Care Worker', 'Medical professional or person working in the health care fielf', 0, NULL),
('Patient', 'A person with a diagnosed or undiagnosed disease', 0, NULL),
('User', 'A person with rights to use the system', 0, NULL);

INSERT INTO `bsm_prsn_type` (`prsn_type`, `prsn_role`, `prsn_type_desc`, `prsn_type_enum`, `deactivate_dt`) VALUES
('HI', 'Health Care Worker', 'Health Inspector', 0, NULL),
('DDHS', 'Health Care Worker', 'Deputy Director of Health Services', 0, NULL),
('GP', 'Health Care Worker', 'General Practitioner', 0, NULL),
('MO', 'Health Care Worker', 'Medical Officer', 0, NULL),
('MOH', 'Health Care Worker', 'Medical Officer of Health', 0, NULL),
('PHI', 'Health Care Worker', 'Public Health Inspector', 0, NULL),
('SHN', 'Health Care Worker', '', 0, NULL),
('VHN', 'Health Care Worker', 'Village Health Care Worker', 0, NULL),
('Mental', 'Patient', 'Patient with Mental Disease', 0, NULL),
('Physical', 'Patient', 'Patient with Physical Disease', 0, NULL),
('Unknown', 'Health Care Worker', NULL, 0, NULL),
('Suwacevo', 'Health Care Worker', NULL, 0, NULL),
('Unknown', 'Patient', NULL, 0, NULL);

INSERT INTO `bsm_prsn_state` (`prsn_state`, `prsn_role`, `prsn_state_desc`, `prsn_state_enum`, `deactivate_dt`) VALUES
('Certified', 'Health Care Worker', NULL, 0, NULL),
('Intern', 'Health Care Worker', NULL, 0, NULL),
('Student', 'Health Care Worker', NULL, 0, NULL),
('In', 'Patient', NULL, 0, NULL),
('Out', 'Patient', NULL, 0, NULL),
('Unknown', 'Health Care Worker', NULL, 0, NULL);


INSERT INTO `bsm_loc_cate` (`loc_cate`, `loc_cate_desc`, `loc_cate_enum`, `deactivate_dt`) VALUES
('Health', 'location definition of the health system hierarchy', NULL, NULL),
('Governance', NULL, NULL, NULL);

INSERT INTO `bsm_loc_type` (`loc_type`, `loc_cate`, `loc_type_prnt`, `type_desc`, `loc_type_enum`, `loc_type_shape`, `deactivate_dt`) VALUES
('MOH', 'Health', 'District', 'Medical Officer of Health Division', 0, 'polygon', NULL),
('PHI', 'Health', 'MOH', 'Publich Health Inspector Area', 0, 'polygon', NULL),
('District', 'Health', 'Province', 'District health area', 0, 'polygon', NULL),
('Province', 'Health', 'Region', 'Provincial health area', 0, 'polygon', NULL),
('Region', 'Health', 'National', 'Regional Health area', 0, 'polygon', NULL),
('National', 'Health', NULL, 'National health geographic coverage', 0, 'polygon', NULL),
('DPDHS', 'Health', 'PHI', 'DPDHS', 0, 'polygon', NULL),
('Village', 'Health', 'DPDHS', 'Village', 0, 'polygon', NULL);




INSERT INTO `bsm_location` (`loc_uuid`, `loc_prnt_uuid`, `loc_name`, `loc_type`, `loc_desc`, `loc_iso_code`, `create_dt`, `create_by`, `create_proc`, `modify_dt`, `modify_by`, `modify_proc`, `deactivate_dt`) VALUES
(1, 18, 'Kuliyapitiya', 'MOH', 'Kuliyapitiya MOH Division', NULL, '2008-12-18 23:11:18', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(2, NULL, 'Kurunegala', 'DPDHS', 'Kurunegala DPDHS District', NULL, '2008-12-19 00:36:31', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(3, 4, 'Udugama', 'PHI', 'Udugama PHI areas', '1999', '2008-12-19 00:51:41', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(4, 18, 'Wariyapola', 'MOH', 'Wariyapola', NULL, '2008-12-19 10:04:15', 'admin', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(5, 13, 'Udubeddewa', 'MOH', 'Udubeddewa MOH Division', NULL, '2008-12-19 10:08:07', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(6, NULL, 'Sri Lanka', 'National', 'Sri Lanka national health care system', NULL, '2008-12-19 10:50:06', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(7, NULL, '', 'Village', 'Chembanur', NULL, '2008-12-19 12:07:33', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(9, NULL, 'Chembanur', 'PHI', 'Chembanur PHC area', NULL, '2008-12-20 17:05:40', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(10, NULL, 'Chembanur', 'Village', 'Chembanur VHN area', NULL, '2008-12-20 17:06:43', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(11, NULL, 'Kuliyapitiya', 'PHI', 'Kuliyapitiya PHI area', NULL, '2008-12-20 17:10:10', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(12, 4, 'Thambapanni', 'PHI', 'Thambapanni', NULL, '2008-12-20 17:33:05', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(13, 6, 'Nuwara', 'District', 'Nuwara', NULL, '2008-12-30 23:41:07', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(14, NULL, '', NULL, 'Colombo', NULL, '2009-01-09 09:48:33', 'admin', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(15, NULL, 'Colo', NULL, NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(16, 17, 'Colombo', 'MOH', NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(17, 6, 'Colombo', 'District', NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(18, NULL, 'Kurunegala', 'District', 'Kurunegala DPDHS District', NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL),
(19, 1, 'Maharagama', 'PHI', 'Maharagama PHI division', NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', '0000-00-00 00:00:00', 'user', NULL, NULL),
(20, NULL, 'Mahabalipuram', 'District', NULL, NULL, '0000-00-00 00:00:00', 'user', 'http://demo.sahana.lk/bsm', NULL, NULL, NULL, NULL);

INSERT INTO `bsm_fclty_cate` (`fclty_cate`, `fctly_cate_desc`, `fclty_cate_enum`, `deactivate_dt`) VALUES
('Medical', 'facility that provides medical services', 1, NULL),
('Administrative', 'facility that provides health admin services', 2, NULL),
('Legal', 'facility that provides health legal services', 3, NULL),
('Educational', 'facility that provides health professionals training services', 5, NULL),
('Dental', 'facility that provides dental services', 4, NULL);

INSERT INTO `bsm_fclty_type` (`fclty_type`, `fclty_cate`, `fclty_type_desc`, `fclty_type_enum`, `deactivate_dt`) VALUES
('General Hospital', 'Medical', NULL, 1, NULL),
('District Hospital', 'Medical', NULL, 2, NULL),
('Base Hospital', 'Medical', NULL, 3, NULL),
('Peripheral Unit', 'Medical', NULL, 4, NULL),
('Maternity Home', 'Medical', NULL, 5, NULL),
('MOH Officer', 'Administrative', 'Medical Officer of Health Office', 6, NULL);





INSERT INTO `bsm_dis_type` (`dis_type`, `dis_type_desc`, `deactivate_dt`) VALUES
('cardiac', 'heart diseases', NULL),
('Dermatological', 'skin diseases', NULL),
('ENT', 'ear nose and throat diseases', NULL),
('maternal', 'pre and post child birth', NULL),
('pediatric', 'child diseases', NULL),
('SDT', 'sexually transmitted diseases', NULL),
('Unknown', 'type of disease unknown', NULL);

INSERT INTO `bsm_disease` (`disease`, `dis_enum`, `dis_type`, `dis_priority`, `icd_code`, `icd_desc`, `notes`, `deactivate_dt`) VALUES
('Enteric Fever', 1, 'ENT', 'Medium', 'A01', 'Isolation of Salmonella typhi from blood, stool or other clinical specimen. Serological tests based on agglutination antibodies (SAT) are of little diagnostic value because of limited sensitivity and ', NULL, NULL),
('Pertussis', 2, 'ENT', 'Medium', '', '', NULL, NULL),
('Dysentery', 3, 'Unknown', 'Medium', '', '', NULL, NULL),
('Diphtheria', 4, 'ENT', 'Medium', '', '', NULL, NULL),
('Polio', 5, 'Unknown', 'Medium', '', '', NULL, NULL),
('Yellow Fever', 6, 'ENT', 'High', '', '', NULL, NULL),
('Plague', 7, 'Dermatological', 'High', '', '', NULL, NULL),
('Cholera', 8, 'ENT', 'High', NULL, NULL, NULL, NULL);



INSERT INTO `bsm_dis_symp` (`disease`, `symptom`, `deactivate_dt`) VALUES
('Cholera', 'Watery Diarrhoea', NULL),
('Cholera', 'Nausea', NULL),
('Cholera', 'Vomitting', NULL),
('Cholera', 'Muscle Cramps', NULL),
('Cholera', 'Thirst', NULL),
('Plague', 'Fever ', NULL),
('Plague', 'Chills', NULL),
('Plague', 'Headache', NULL),
('Plague', 'Fatigue', NULL),
('Plague', 'Diarrhea', NULL),
('Plague', 'Chest pain', NULL),
('Plague', 'Vomitting', NULL),
('Plague', 'Muscle aches', NULL),
('Plague', 'Cough Blood', NULL),
('Yellow Fever', 'Fever', NULL),
('Yellow Fever', 'Headache', NULL),
('Yellow Fever', 'Muscle aches', NULL),
('Yellow Fever', 'Nausea', NULL),
('Yellow Fever', 'Loss of appetite', NULL),
('Yellow Fever', 'Dizziness', NULL),
('Yellow Fever', 'Abdominal pain', NULL),
('Polio', 'Fever', NULL),
('Polio', 'Headache', NULL),
('Polio', 'Vomitting', NULL),
('Polio', 'Diarrhea', NULL),
('Polio', 'Fatigue', NULL),
('Polio', 'Constipation', NULL),
('Polio', 'Difficult to swollow', NULL),
('Polio', 'Difficulty in breathing', NULL),
('Diphtheria', 'Sore throat', NULL),
('Diphtheria', 'Painfull swollowing', NULL),
('Diphtheria', 'Difficulty in breathing', NULL),
('Diphtheria', 'Fever', NULL),
('Diphtheria', 'Chills', NULL),
('Diphtheria', 'Malaise', NULL),
('Dysentery', 'Abdominal cramp', NULL),
('Dysentery', 'Nausea', NULL),
('Dysentery', 'Vomitting', NULL),
('Dysentery', 'Fever', NULL),
('Dysentery', 'Diarrhea', NULL),
('Dysentery', 'Blood stained stools', NULL),
('Dysentery', 'Mocous stained stools', NULL),
('Pertussis', 'Runny nose', NULL),
('Pertussis', 'Sneezing', NULL),
('Pertussis', 'Mild cough', NULL),
('Pertussis', 'Low-grade fever', NULL),
('Pertussis', 'Dry cough', NULL),
('Enteric Fever', 'Fever', NULL),
('Enteric Fever', 'Headache', NULL),
('Enteric Fever', 'Fatigue', NULL),
('Enteric Fever', 'Sore throat', NULL),
('Enteric Fever', 'Abdominal pain', NULL),
('Enteric Fever', 'Diarrhea', NULL),
('Enteric Fever', 'Constipation', NULL),
('Diphtheria', 'Blood stained stools', NULL),
('Diphtheria', 'Constipation', NULL),
('Cholera', 'Chills', NULL),
('Cholera', 'Abdominal pain', NULL);



INSERT INTO `bsm_dis_sign` (`disease`, `sign`, `deactivate_dt`) VALUES
('Enteric Fever', 'Rash', NULL),
('Enteric Fever', 'High fever', NULL),
('Enteric Fever', 'Distended abdomen', NULL),
('Enteric Fever', 'Delirium', NULL),
('Enteric Fever', 'Typhoid state', NULL),
('Pertussis', 'Whooping', NULL),
('Dysentery', 'Abdominal tenderness', NULL),
('Diphtheria', 'Hoarseness', NULL),
('Diphtheria', 'Swollen glands', NULL),
('Diphtheria', 'Grey membrane covering throat', NULL),
('Diphtheria', 'Red infected wound', NULL),
('Diphtheria', 'Wound with gray patchy material', NULL),
('Diphtheria', 'Eye signs', NULL),
('Polio', 'Neck stiffnes', NULL),
('Polio', 'Back stiffness', NULL),
('Polio', 'Muscle spasms', NULL),
('Polio', 'Increase sensitivity to couch', NULL),
('Polio', 'Paralysis of the limbs', NULL),
('Polio', 'Cranial Nerve palsy', NULL),
('Polio', 'Facial muscle paralysis', NULL),
('Polio', 'Features of bulbar palsy', NULL),
('Yellow Fever', 'Red eyes', NULL),
('Yellow Fever', 'Red toungue', NULL),
('Yellow Fever', 'Yellowing of skin', NULL),
('Yellow Fever', 'Yellowing of sclera', NULL),
('Yellow Fever', 'Nose bleed', NULL),
('Yellow Fever', 'Heart arrythmias', NULL),
('Yellow Fever', 'Liver failure', NULL),
('Yellow Fever', 'Kidney failure', NULL),
('Yellow Fever', 'Delirium', NULL),
('Yellow Fever', 'Seizures', NULL),
('Yellow Fever', 'Coma', NULL),
('Plague', 'Buboes', NULL),
('Plague', 'Mucosal tissue bleed', NULL),
('Plague', 'Gangeens', NULL),
('Plague', 'Pneumonia', NULL),
('Plague', 'Coma', NULL),
('Cholera', 'Dehydration', NULL),
('Cholera', 'Tachycardia', NULL),
('Cholera', 'Drowsiness', NULL),
('Cholera', 'Back stiffness', NULL),
('Enteric Fever', 'Buboes', NULL),
('Dysentery', 'Back stiffness', NULL);


INSERT INTO `bsm_caus_fact` (`caus_fact`, `caus_fact_enum`, `caus_fact_priority`, `caus_fact_desc`, `caus_fact_code`, `deactivate_dt`) VALUES
('heavy rains', 1, NULL, 'heavy rains', NULL, NULL);


INSERT INTO `bsm_dis_caus_fact` (`disease`, `caus_fact`, `deactivate_dt`) VALUES
('Cholera', 'heavy rains', NULL),
('Enteric Fever', 'heavy rains', NULL);


INSERT INTO `bsm_cases` (`case_uuid`) VALUES
(0),
(1);

INSERT INTO `bsm_case_symp` (`case_uuid`, `symptom`, `deactivate_dt`) VALUES
(1, 'Ache', NULL),
(1, 'Fever', NULL),
(1, 'Stomach', NULL),
(1, 'Vomitting', NULL),
(0, 'Fever', NULL),
(1, 'Abdominal cramp', NULL);

INSERT INTO `bsm_case_status` (`case_status`, `case_status_desc`, `case_status_enum`, `deactivate_dt`) VALUES
('Closed', 'case is closed due to other reasons see remarks', 8, NULL),
('Cured', 'case has been treated and is cured', 7, NULL),
('Diagnosed', 'cased diagnosed', 4, NULL),
('Investigating', 'case is being investigated and results will be produced', 2, NULL),
('Open', 'case has been create remains to be investigated', 1, NULL),
('Referred', 'case has been refered to anothe facility or health care worker', 3, NULL),
('Treated', 'treatment has been initiated', 6, NULL),
('Untreated', 'case has been investigated and results produced but remains untreated', 5, NULL);

INSERT INTO `bsm_case_sign` (`case_uuid`, `sign`, `deactivate_dt`) VALUES
(1, 'Ache', NULL),
(1, 'Fever', NULL),
(1, 'Stomach', NULL),
(1, 'Vomitting', NULL),
(0, 'Rash', NULL),
(1, 'Coma', NULL);



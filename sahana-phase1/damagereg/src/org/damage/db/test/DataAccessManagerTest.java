/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.TestCase;
import org.damage.business.*;
import org.damage.db.persistence.DataAccessManager;

import java.util.HashSet;
import java.util.Set;

/**
 * Class to test DataAccessManagerread class
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DataAccessManagerTest extends TestCase {

    public DataAccessManagerTest(String name) {
        super(name);
        dao = new DataAccessManager();
    }

    public void testSaveCase() {

        DamageCase damageCase = new DamageCase();
        damageCase.setReporterName("Reporter1");
        Property prop1 = new Property();
        prop1.setOwnerName("PROP OWNER1");

        Property prop2 = new Property();
        prop2.setOwnerName("PROP OWNER2");

        DamageReportDetailHospital damageDetailHospital1 = new DamageReportDetailHospital();
        damageDetailHospital1.setSummaryFacility("SUMMARY1");

        DamageReportDetailHospital damageDetailHospital2 = new DamageReportDetailHospital();
        damageDetailHospital2.setSummaryFacility("SUMMARY2");

        Set damageDetailHospitalEstimatedCosts1 = new HashSet();
        DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost1 = new DamageDetailHospitalEstimatedCost();
        damageDetailHospitalEstimatedCost1.setBudgetDescription("BUDGET1");
        damageDetailHospitalEstimatedCosts1.add(damageDetailHospitalEstimatedCost1);

        Set damageDetailHospitalEstimatedCosts2 = new HashSet();
        DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost2 = new DamageDetailHospitalEstimatedCost();
        damageDetailHospitalEstimatedCost2.setBudgetDescription("BUDGET2");
        damageDetailHospitalEstimatedCosts2.add(damageDetailHospitalEstimatedCost2);

        Set damageReports = new HashSet();

        // Report 1
        DamageReport p1 = new DamageReport();
        p1.setProperty(prop1);
        p1.setNumberPersonsAffected(new Long(111));
        p1.setContactPersonName("CONTACTPERSON1");
        //p1.setDamageCase(damageCase);
        //xxxxxxxxxxxxxxxxxxxxxxxxxxx
        damageDetailHospital1.setDamageDetailHospitalEstimatedCosts(damageDetailHospitalEstimatedCosts1);
        p1.setDamageDetail(damageDetailHospital1);
        //xxxxxxxxxxxxxxxxxxxxxxxxxxx
        damageReports.add(p1);
        // Report 2
        DamageReport p2 = new DamageReport();
        p2.setProperty(prop2);
        p2.setNumberPersonsAffected(new Long(222));
        p2.setContactPersonName("CONTACTPERSON2");
        //p2.setDamageCase(damageCase);
        damageDetailHospital2.setDamageDetailHospitalEstimatedCosts(damageDetailHospitalEstimatedCosts2);
        p2.setDamageDetail(damageDetailHospital2);
        damageReports.add(p2);

        damageCase.setDamageReports(damageReports);
        try {
            dao.saveCase(damageCase);
        } catch (Exception e) {
            System.out.println(e.toString());
        }

    }

    private DataAccessManager dao;
}

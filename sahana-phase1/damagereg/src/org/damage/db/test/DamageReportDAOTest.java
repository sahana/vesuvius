/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.DamageReport;
import org.damage.business.Property;
import org.damage.db.persistence.DamageReportDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for DamageReportDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageReportDAOTest extends TestCase {

    public DamageReportDAOTest(String name) {
        super(name);
        dao = new DamageReportDAO();
    }

    /**
     * Inserts a new DamageReport object int othe database.
     * The test will fail if errors are encountered when
     * the DamageReport is inserted.
     */
    public void testSaveDamageReport() {
        DamageReport damageReport = new DamageReport();

        damageReport.setNumberPersonsAffected(new Long(6));
        Property property = new Property();
        property.setOwnerName("YY");
        damageReport.setProperty(property);
        damageReport.setCaseId(new Long(2));

        try {
            damageReport = dao.saveDamageReport(damageReport);

            if (damageReport.getDamageReportId() == null) {
                Assert.fail("The Damage Report object was not saved.");
            } else {
                log.info("Damage Report object saved successfully: " + damageReport.toString());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    /**
     * Selects all DamageReport from the database.  This test will
     * fail if there are no DamageReport int the database.
     */

    public void testSelectDamageReports() {
        try {
            List damageReports = dao.searchDamageReports(DamageReportDAO.SELECT_ALL, null);
            log.info("Number of Damage Reports retrieved from database: " + damageReports.size());

            if (damageReports.size() == 0) {
                Assert.fail("No Damage Reports were found in the database.");
            }

            for (Iterator i = damageReports.iterator(); i.hasNext();) {
                DamageReport damageReport = (DamageReport) i.next();
                log.info("Damage Report: " + damageReport.getNumberPersonsAffected() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private DamageReportDAO dao;
    static Log log = LogFactory.getLog(DamageReportDAOTest.class.getName());

}



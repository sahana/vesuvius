/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.DamageReportDetailHospital;
import org.damage.db.persistence.DamageDetailHospitalDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Case for Class DamageDetailHospitalDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageDetailHospitalDAOTest extends TestCase {

    public DamageDetailHospitalDAOTest(String name) {
        super(name);
        dao = new DamageDetailHospitalDAO();
    }

    /**
     * Inserts a new DamageReportDetailHospital object int othe database.
     * The test will fail if errors are encountered when
     * the DamageReportDetailHospital is inserted.
     */
    public void testSaveDamageDetailHospital() {
        DamageReportDetailHospital damageDetailHospital = new DamageReportDetailHospital();
        damageDetailHospital.setSummaryFacility("summery facility1");
        damageDetailHospital.setDamageReportId(new Long(3));
        try {
            damageDetailHospital = dao.saveDamageDetailHospital(damageDetailHospital);

            if (damageDetailHospital.getDamageDetailHospitalId() == null) {
                Assert.fail("The damageDetailHospital object was not saved.");
            } else {
                log.info("damageDetailHospital object saved successfully: ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    /**
     * Selects all DamageReportDetailHospital from the database.  This test will
     * fail if there are no DamageReportDetailHospital int the database.
     */
    public void testSelectPlayers() {
        try {

            List damageDetailHospitals = dao.searchDamageDetailHospital(DamageDetailHospitalDAO.SELECT_ALL, null);

            log.info("Number of damageDetailHospitals retrieved from database: " + damageDetailHospitals.size());

            if (damageDetailHospitals.size() == 0) {
                Assert.fail("No damageDetailHospitals were found in the database.");
            }

            for (Iterator i = damageDetailHospitals.iterator(); i.hasNext();) {
                DamageReportDetailHospital damageDetailHospital = (DamageReportDetailHospital) i.next();
                log.info("DamageReportDetailHospital: " + damageDetailHospital.getSummaryFacility() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private DamageDetailHospitalDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.DamageDetailHospitalDAOTest.class.getName());

}



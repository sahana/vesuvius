/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.DamageDetailHospitalEstimatedCost;
import org.damage.db.persistence.DamageDetailHospitalEstimatedCostDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for DamageDetailHospitalEstimatedCostDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageDetailHospitalEstimatedCostDAOTest extends TestCase {

    public DamageDetailHospitalEstimatedCostDAOTest(String name) {
        super(name);
        dao = new DamageDetailHospitalEstimatedCostDAO();
    }

    /**
     * Inserts a new DamageDetailHospitalEstimatedCost object int othe database.
     * The test will fail if errors are encountered when
     * the DamageDetailHospitalEstimatedCost is inserted.
     */
    public void testSaveDamageDetailHospital() {
        DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost = new DamageDetailHospitalEstimatedCost();
        damageDetailHospitalEstimatedCost.setBudgetDescription("test Budget description");
        damageDetailHospitalEstimatedCost.setDamageReportId(new Long(2));
        try {
            damageDetailHospitalEstimatedCost = dao.saveDamageDetailHospitalEstimatedCost(damageDetailHospitalEstimatedCost);

            if (damageDetailHospitalEstimatedCost.getBudgetDescription() == null) {
                Assert.fail("The damageDetailHospitalEstimatedCost object was not saved.");
            } else {
                log.info("damageDetailHospitalEstimatedCost object saved successfully: ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    /**
     * Selects all DamageDetailHospitalEstimatedCost from the database.  This test will
     * fail if there are no DamageDetailHospitalEstimatedCost int the database.
     */
    public void testListDamageDetailHospitalEstimatedCosts() {
        try {

            List damageDetailHospitalEstimatedCosts = dao.searchDamageDetailHospitalEstimatedCost(DamageDetailHospitalEstimatedCostDAO.SELECT_ALL, null);

            log.info("Number of damageDetailHospitalEstimatedCosts retrieved from database: " + damageDetailHospitalEstimatedCosts.size());

            if (damageDetailHospitalEstimatedCosts.size() == 0) {
                Assert.fail("No damageDetailHospitalEstimatedCosts were found in the database.");
            }

            for (Iterator i = damageDetailHospitalEstimatedCosts.iterator(); i.hasNext();) {
                DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost = (DamageDetailHospitalEstimatedCost) i.next();
                log.info("damageDetailHospitalEstimatedCosts: " + damageDetailHospitalEstimatedCost.getBudgetDescription() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private DamageDetailHospitalEstimatedCostDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.DamageDetailHospitalEstimatedCostDAOTest.class.getName());

}



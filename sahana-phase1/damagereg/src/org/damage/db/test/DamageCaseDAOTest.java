/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.DamageCase;
import org.damage.business.DamageReport;
import org.damage.db.persistence.DamageCaseDAO;

import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * Test Case for Class DamageCaseDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageCaseDAOTest extends TestCase {

    public DamageCaseDAOTest(String name) {
        super(name);
        dao = new DamageCaseDAO();
    }

    /**
     * Inserts a new DamageCase object int othe database.
     * The test will fail if errors are encountered when
     * the DamageCase is inserted.
     */
    public void testSaveDamageCase() {
        DamageCase damageCase = new DamageCase();
        damageCase.setReporterName("Reporter1");
        Set damageReports = new HashSet();

        DamageReport p0 = new DamageReport();
        p0.setNumberPersonsAffected(new Long(111));
        p0.setContactPersonName("person1");
        p0.setDamageCase(damageCase);
        damageReports.add(p0);


        DamageReport p1 = new DamageReport();
        p1.setNumberPersonsAffected(new Long(222));
        p1.setContactPersonName("person2");
        p1.setDamageCase(damageCase);

        damageReports.add(p1);

        damageCase.setDamageReports(damageReports);


        try {
            damageCase = dao.saveDamageCase(damageCase);

            if (damageCase.getCaseId() == null) {
                Assert.fail("The Damage Case object was not saved.");
            } else {
                log.info("Damage Case object saved successfully: ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    /**
     * Selects all DamageCases from the database.  This test will
     * fail if there are no DamageCase int the database.
     */
    public void testSelectDamageCase() {
        try {

            List dmgCases = dao.searchDamageCase(DamageCaseDAO.SELECT_ALL, null);

            log.info("Number of Damage Cases retrieved from database: " + dmgCases.size());

            if (dmgCases.size() == 0) {
                Assert.fail("No Damage Cases were found in the database.");
            }

            for (Iterator i = dmgCases.iterator(); i.hasNext();) {
                DamageCase dmgCase = (DamageCase) i.next();
                log.info("DamageCase: " + dmgCase.getReporterNicPassportId() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private DamageCaseDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.DamageCaseDAOTest.class.getName());

}



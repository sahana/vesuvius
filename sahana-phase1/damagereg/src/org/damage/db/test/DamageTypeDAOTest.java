/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.DamageType;
import org.damage.common.LabelValue;
import org.damage.db.persistence.DamageTypeDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for DamageTypeDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageTypeDAOTest extends TestCase {

    public DamageTypeDAOTest(String name) {
        super(name);
        dao = new DamageTypeDAO();
    }

    public void testSelectDamageTypes() {
        try {

            List damageTypes = dao.searchDamageType(DamageTypeDAO.SELECT_ALL, null);

            log.info("Number of damageType retrieved from database: " + damageTypes.size());

            if (damageTypes.size() == 0) {
                Assert.fail("No damageType were found in the database.");
            }

            for (Iterator i = damageTypes.iterator(); i.hasNext();) {
                DamageType damageType = (DamageType) i.next();
                log.info("damageType: " + damageType.getDamageDescription() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testlistAllDamageTypes() {
        try {

            List damageTypes;

            damageTypes = dao.listAllDamageType();

            log.info("Number of damageTypes retrieved from database: " + damageTypes.size());

            if (damageTypes.size() == 0) {
                Assert.fail("No damageTypes were found in the database.");
            }

            for (Iterator i = damageTypes.iterator(); i.hasNext();) {
                LabelValue damageType = (LabelValue) i.next();
                log.info("damageTypes Lable: " + damageType.getLabel() + " damageTypes Value: " + damageType.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    private DamageTypeDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.DamageTypeDAOTest.class.getName());
}

/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.Property;
import org.damage.db.persistence.PropertyDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for PropertyDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class PropertyDAOTest extends TestCase {

    public PropertyDAOTest(String name) {
        super(name);
        dao = new PropertyDAO();
    }

    public void testsaveProperty() {
        Property property = new Property();
        property.setOwnerName("Owner1");

        try {
            property = dao.saveProperty(property);

            if (property.getPropertyId() == null) {
                Assert.fail("The Property object was not saved.");
            } else {
                log.info("Property object saved successfully: " + property.toString());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    /**
     * Selects all players from the database.  This test will
     * fail if there are no players int the database.
     */
    public void testSelectDamageReports() {
        try {
            List properties = dao.searchProperty(PropertyDAO.SELECT_ALL, null);
            log.info("Number of Damage Properties retrieved from database: " + properties.size());

            if (properties.size() == 0) {
                Assert.fail("No Damage Properties were found in the database.");
            }

            for (Iterator i = properties.iterator(); i.hasNext();) {
                Property property = (Property) i.next();
                log.info("Property: " + property.getOwnerName() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private PropertyDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.PropertyDAOTest.class.getName());
}

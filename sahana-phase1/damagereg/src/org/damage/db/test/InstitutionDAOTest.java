/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.Institution;
import org.damage.common.LabelValue;
import org.damage.db.persistence.InstitutionDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for InstitutionDAO class
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class InstitutionDAOTest extends TestCase {

    public InstitutionDAOTest(String name) {
        super(name);
        dao = new InstitutionDAO();
    }

    public void testSelectInstitutions() {
        try {

            List institutions = dao.searchInstitution(InstitutionDAO.SELECT_ALL, null);

            log.info("Number of Institutions retrieved from database: " + institutions.size());

            if (institutions.size() == 0) {
                Assert.fail("No Institutions were found in the database.");
            }

            for (Iterator i = institutions.iterator(); i.hasNext();) {
                Institution institution = (Institution) i.next();
                log.info("Institution: " + institution.getInstitutionName() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testlistAllInstitutions() {
        try {

            List institutions;

            institutions = dao.listAllInstitutions();

            log.info("Number of institutions retrieved from database: " + institutions.size());

            if (institutions.size() == 0) {
                Assert.fail("No institutions were found in the database.");
            }

            for (Iterator i = institutions.iterator(); i.hasNext();) {
                LabelValue institution = (LabelValue) i.next();
                log.info("institution Lable: " + institution.getLabel() + " institutions Value: " + institution.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    private InstitutionDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.InstitutionDAOTest.class.getName());
}

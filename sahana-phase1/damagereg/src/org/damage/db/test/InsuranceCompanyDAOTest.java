/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.InsuranceCompany;
import org.damage.common.LabelValue;
import org.damage.db.persistence.InsuranceCompanyDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for InsuranceCompany class
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class InsuranceCompanyDAOTest extends TestCase {

    public InsuranceCompanyDAOTest(String name) {
        super(name);
        dao = new InsuranceCompanyDAO();
    }

    public void testSelectInsuranceCompany() {
        try {

            List insuranceCompanies = dao.searchInsuranceCompany(InsuranceCompanyDAO.SELECT_ALL, null);

            log.info("Number of Insurance Companies retrieved from database: " + insuranceCompanies.size());

            if (insuranceCompanies.size() == 0) {
                Assert.fail("No Insurance Companies were found in the database.");
            }

            for (Iterator i = insuranceCompanies.iterator(); i.hasNext();) {
                InsuranceCompany insuranceCompany = (InsuranceCompany) i.next();
                log.info("Insurance Companiy: " + insuranceCompany.getInsuranceCompanyName() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testListAllInsuranceCompany() {
        try {

            List insuranceCompanies;

            insuranceCompanies = dao.listAllInsuranceCompany();

            log.info("Number of insurance Companies retrieved from database: " + insuranceCompanies.size());

            if (insuranceCompanies.size() == 0) {
                Assert.fail("No insurance Companies were found in the database.");
            }

            for (Iterator i = insuranceCompanies.iterator(); i.hasNext();) {
                LabelValue insuranceCompany = (LabelValue) i.next();
                log.info("insurance Company Lable: " + insuranceCompany.getLabel() + " insurance Company Value: " + insuranceCompany.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private InsuranceCompanyDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.InsuranceCompanyDAOTest.class.getName());
}

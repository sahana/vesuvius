/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.InsuranceCompany;
import org.damage.common.LabelValue;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Class InsuranceCompanyDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class InsuranceCompanyDAO extends BaseDAO {

    public InsuranceCompany saveInsuranceCompany(InsuranceCompany t) throws DAOException {
        storeObj(t);
        return (InsuranceCompany) retrieveObj(InsuranceCompany.class, t.getInsuranceCompanyCode());
    }

    public InsuranceCompany getInsuranceCompany(Long id) throws DAOException {
        return (InsuranceCompany) retrieveObj(InsuranceCompany.class, id);
    }

    public void removeInsuranceCompany(InsuranceCompany t) throws DAOException {
        removeInsuranceCompany(t.getInsuranceCompanyCode());
    }

    public void removeInsuranceCompany(Long id) throws DAOException {
        removeObj(InsuranceCompany.class, id);
    }

    /**
     * Returns a list of <code>InsuranceCompany</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchInsuranceCompany(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    public List listAllInsuranceCompany() {
        try {
            List insuranceCompanies;
            insuranceCompanies = searchInsuranceCompany(InsuranceCompanyDAO.SELECT_ALL, null);
            List list = new ArrayList();
            for (Iterator i = insuranceCompanies.iterator(); i.hasNext();) {
                InsuranceCompany insuranceCompany = (InsuranceCompany) i.next();
                String label = insuranceCompany.getInsuranceCompanyName();
                String value = insuranceCompany.getInsuranceCompanyCode().toString();
                list.add(new LabelValue(label, value));
            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    /**
     * Retrieves all Insurance Companies from the database.
     */
    public static final String SELECT_ALL = "insuranceCompany.selectAll";

}

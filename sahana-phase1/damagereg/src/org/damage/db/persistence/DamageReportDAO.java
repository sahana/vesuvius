/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.DamageReport;

import java.util.List;

/**
 * Class DamageReportDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageReportDAO extends BaseDAO {

    public DamageReport saveDamageReport(DamageReport t) throws DAOException {
        storeObj(t);
        return (DamageReport) retrieveObj(DamageReport.class, t.getDamageReportId());
    }

    public DamageReport getDamageReport(Long id) throws DAOException {
        return (DamageReport) retrieveObj(DamageReport.class, id);
    }

    public void removeDamageReport(DamageReport t) throws DAOException {
        removeDamageReport(t.getDamageReportId());
    }

    public void removeDamageReport(Long id) throws DAOException {
        removeObj(DamageReport.class, id);
    }

    /**
     * Returns a list of <code>DamageReport</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchDamageReports(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    /**
     * Retrieves all DamageReports from the database.
     */
    public static final String SELECT_ALL = "damageReport.selectAll";

}

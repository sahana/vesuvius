/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.DamageReportDetailHospital;
import org.damage.business.DamageReportDetailType;

import java.util.List;

/**
 * Class DamageDetailHospitalDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageDetailHospitalDAO extends BaseDAO {

    public DamageReportDetailHospital saveDamageDetailHospital(DamageReportDetailHospital t) throws DAOException {
        storeObj(t);
        return (DamageReportDetailHospital) retrieveObj(DamageReportDetailHospital.class, t.getDamageDetailHospitalId());
    }

    public DamageReportDetailType getDamageDetailHospital(Long id) throws DAOException {
        return (DamageReportDetailType) retrieveObj(DamageReportDetailHospital.class, id);
    }

    public void removeDamageDetailHospital(DamageReportDetailHospital t) throws DAOException {
        removeDamageDetailHospital(t.getDamageDetailHospitalId());
    }

    public void removeDamageDetailHospital(Long id) throws DAOException {
        removeObj(DamageReportDetailHospital.class, id);
    }

    /**
     * Returns a list of <code>DamageReportDetailHospital</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchDamageDetailHospital(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    /**
     * Retrieves all DamageDetailHospitals from the database.
     */
    public static final String SELECT_ALL = "damageDetailHospital.selectAll";

}

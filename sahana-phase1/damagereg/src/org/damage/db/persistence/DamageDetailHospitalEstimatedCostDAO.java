/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.DamageDetailHospitalEstimatedCost;

import java.util.List;

/**
 * Class DamageDetailHospitalEstimatedCostDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageDetailHospitalEstimatedCostDAO extends BaseDAO {

    public DamageDetailHospitalEstimatedCost saveDamageDetailHospitalEstimatedCost(DamageDetailHospitalEstimatedCost t) throws DAOException {
        storeObj(t);
        return (DamageDetailHospitalEstimatedCost) retrieveObj(DamageDetailHospitalEstimatedCost.class, t.getDmgDetailEstimatedCostId());
    }

    public DamageDetailHospitalEstimatedCost getDamageDetailHospitalEstimatedCost(Long id) throws DAOException {
        return (DamageDetailHospitalEstimatedCost) retrieveObj(DamageDetailHospitalEstimatedCost.class, id);
    }

    public void removeDamageDetailHospitalEstimatedCost(DamageDetailHospitalEstimatedCost t) throws DAOException {
        removeDamageDetailHospitalEstimatedCost(t.getDmgDetailEstimatedCostId());
    }

    public void removeDamageDetailHospitalEstimatedCost(Long id) throws DAOException {
        removeObj(DamageDetailHospitalEstimatedCost.class, id);
    }

    /**
     * Returns a list of <code>DamageDetailHospitalEstimatedCost</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchDamageDetailHospitalEstimatedCost(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    /**
     * Retrieves all DamageDetailHospitalEstimatedCosts from the database.
     */
    public static final String SELECT_ALL = "damageDetailHospitalEstimatedCost.selectAll";

}

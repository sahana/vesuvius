/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.DamageCase;

import java.util.List;

/**
 * Class DamageCaseDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class DamageCaseDAO extends BaseDAO {

    public DamageCase saveDamageCase(DamageCase t) throws DAOException {
        storeObj(t);
        return (DamageCase) retrieveObj(DamageCase.class, t.getCaseId());
    }

    public DamageCase getDamageCase(Long id) throws DAOException {
        return (DamageCase) retrieveObj(DamageCase.class, id);
    }

    public void removeDamageCase(DamageCase t) throws DAOException {
        removeDamageCase(t.getCaseId());
    }

    public void removeDamageCase(Long id) throws DAOException {
        removeObj(DamageCase.class, id);
    }

    /**
     * Returns a list of <code>DamageCase</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchDamageCase(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    /**
     * Retrieves all DamageCases from the database.
     */
    public static final String SELECT_ALL = "DamageCase.selectAll";

}

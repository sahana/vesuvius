/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.DamageType;
import org.damage.common.LabelValue;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Class DamageTypeDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class DamageTypeDAO extends BaseDAO {

    public DamageType saveDamageType(DamageType t) throws DAOException {
        storeObj(t);
        return (DamageType) retrieveObj(DamageType.class, t.getDamageTypeCode());
    }

    public DamageType getDamageType(Long id) throws DAOException {
        return (DamageType) retrieveObj(DamageType.class, id);
    }

    public void removeDamageType(DamageType t) throws DAOException {
        removeDamageType(t.getDamageTypeCode());
    }

    public void removeDamageType(Long id) throws DAOException {
        removeObj(DamageType.class, id);
    }

    /**
     * Returns a list of <code>DamageType</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchDamageType(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    public List listAllDamageType() {
        try {
            List damageTypes;
            damageTypes = searchDamageType(DamageTypeDAO.SELECT_ALL, null);
            List list = new ArrayList();
            for (Iterator i = damageTypes.iterator(); i.hasNext();) {
                DamageType damageType = (DamageType) i.next();
                String label = damageType.getDamageDescription();
                String value = damageType.getDamageTypeCode().toString();
                list.add(new LabelValue(label, value));
            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    /**
     * Retrieves all DamageTypes from the database.
     */
    public static final String SELECT_ALL = "damageType.selectAll";

}


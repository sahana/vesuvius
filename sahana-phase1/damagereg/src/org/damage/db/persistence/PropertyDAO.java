/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.Property;

import java.util.List;

/**
 * Class InsuranceCompanyDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */
public class PropertyDAO extends BaseDAO {

    public Property saveProperty(Property t) throws DAOException {
        storeObj(t);
        return (Property) retrieveObj(Property.class, t.getPropertyId());
    }

    public Property getProperty(Long id) throws DAOException {
        return (Property) retrieveObj(Property.class, id);
    }

    public void removeProperty(Property t) throws DAOException {
        removeProperty(t.getPropertyId());
    }

    public void removeProperty(Long id) throws DAOException {
        removeObj(Property.class, id);
    }

    /**
     * Returns a list of <code>Property</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchProperty(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    /**
     * Retrieves all Propertys from the database.
     */
    public static final String SELECT_ALL = "property.selectAll";

}


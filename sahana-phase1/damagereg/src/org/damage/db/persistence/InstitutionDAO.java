/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import org.damage.business.Institution;
import org.damage.common.LabelValue;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Class InstitutionDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class InstitutionDAO extends BaseDAO {

    public Institution saveInstitution(Institution t) throws DAOException {
        storeObj(t);
        return (Institution) retrieveObj(Institution.class, t.getInstitutionCode());
    }

    public Institution getInstitution(Long id) throws DAOException {
        return (Institution) retrieveObj(Institution.class, id);
    }

    public void removeInstitution(Institution t) throws DAOException {
        removeInstitution(t.getInstitutionCode());
    }

    public void removeInstitution(Long id) throws DAOException {
        removeObj(Institution.class, id);
    }

    /**
     * Returns a list of <code>Institution</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchInstitution(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    public List listAllInstitutions() {
        try {
            List institutions;
            institutions = searchInstitution(InstitutionDAO.SELECT_ALL, null);
            List list = new ArrayList();
            for (Iterator i = institutions.iterator(); i.hasNext();) {
                Institution institution = (Institution) i.next();
                String label = institution.getInstitutionName();
                String value = institution.getInstitutionCode().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }


    /**
     * Retrieves all Institutions from the database.
     */
    public static final String SELECT_ALL = "institution.selectAll";

}

/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.persistence;

import net.sf.hibernate.Hibernate;
import net.sf.hibernate.type.Type;
import org.damage.business.SahanaLocation;
import org.damage.common.LabelValue;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Class SahanaLocationsDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */

public class SahanaLocationsDAO extends BaseDAO {

    public SahanaLocation saveSahanaLocation(SahanaLocation t) throws DAOException {
        storeObj(t);
        return (SahanaLocation) retrieveObj(SahanaLocation.class, t.getId());
    }

    public SahanaLocation getSahanaLocation(Long id) throws DAOException {
        return (SahanaLocation) retrieveObj(SahanaLocation.class, id);
    }

    public void removeSahanaLocation(SahanaLocation t) throws DAOException {
        removeSahanaLocation(t.getId());
    }

    public void removeSahanaLocation(Long id) throws DAOException {
        removeObj(SahanaLocation.class, id);
    }

    /**
     * Returns a list of <code>SahanaLocation</code>s using the query
     * specified by the <code>query</code> key.
     *
     * @param query the query key
     * @param value the value to put into the query statement.
     *              May be null
     * @return List
     * @throws DAOException
     */
    public List searchSahanaLocations(String query, String value) throws DAOException {
        return retrieveObjs(query, value);
    }


    public List searchSahanaLocations2(String query, String[] values) throws DAOException {
        Type[] types = new Type[values.length];
        for (int i = 0; i < types.length; i++) types[i] = Hibernate.STRING;
        return retrieveObjs(query, values, types);
    }


    public List listAllProvicences() {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_PROVINCES, null);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }


    public List listAllDistricts() {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_DISTRICTS, null);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    public List listAllDivisions() {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_DIVISIONS, null);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    public List listAllGNDivisions() {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_GN_DIVISIONS, null);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }


    public List listAllDistrictsByProvince(String provinceParentId) {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_DISTRICTS_BY_PROVINCE, provinceParentId);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    public List listAllDivisionsByDistrict(String districtParentId) {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_DIVISIONS_BY_DISTRICTS, districtParentId);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }

    public List listAllGNDivisionsByDivision(String divisionParentId) {
        try {
            List sahanaLocations;
            sahanaLocations = searchSahanaLocations(SahanaLocationsDAO.SELECT_ALL_GN_DIVISIONS_BY_DIVISION, divisionParentId);
            List list = new ArrayList();
            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                String label = sahanaLocation.getName();
                String value = sahanaLocation.getId().toString();
                list.add(new LabelValue(label, value));

            }
            return list;
        } catch (Exception e) {
            System.out.println(e.getMessage());
            return null;
        }

    }


    /**
     * Retrieves all SahanaLocation from the database.
     */
    public static final String SELECT_ALL = "sahanaLocations.selectAll";
    /**
     * Retrieves all SahanaLocation by locationTypes from the database
     */
    public static final String SELECT_BY_LOCATION_TYPE = "sahanaLocations.selectByLocationType";
    public static final String SELECT_BY_LOCATION_TYPE_AND_PARENT = "sahanaLocations.selectByLocationTypeAndParent";
    public static final String SELECT_ALL_PROVINCES = "sahanaLocations.selectAllProvinces";
    public static final String SELECT_ALL_DISTRICTS = "sahanaLocations.selectAllDistricts";
    public static final String SELECT_ALL_DIVISIONS = "sahanaLocations.selectAllDivisions";
    public static final String SELECT_ALL_GN_DIVISIONS = "sahanaLocations.selectAllGNDivisions";
    public static final String SELECT_ALL_DISTRICTS_BY_PROVINCE = "sahanaLocations.selectDistrictsByProvince";
    public static final String SELECT_ALL_DIVISIONS_BY_DISTRICTS = "sahanaLocations.selectDivisionsByDistricts";
    public static final String SELECT_ALL_GN_DIVISIONS_BY_DIVISION = "sahanaLocations.selectGNDivisionsByDivisions";

}

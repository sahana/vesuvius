/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.db.test;

import junit.framework.Assert;
import junit.framework.TestCase;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.damage.business.SahanaLocation;
import org.damage.common.LabelValue;
import org.damage.db.persistence.SahanaLocationsDAO;

import java.util.Iterator;
import java.util.List;

/**
 * Test Class for SahanaLocationsDAO
 *
 * @author Nalaka Gamage
 * @version 1.0
 */


public class SahanaLocationsDAOTest extends TestCase {

    public static final int LIST_BY_DIVISION = 0;

    public SahanaLocationsDAOTest(String name) {
        super(name);
        dao = new SahanaLocationsDAO();
    }


    public void testSelectSahanaLocationsByLocationTytpe() {
        try {

            List sahanaLocations = dao.searchSahanaLocations(SahanaLocationsDAO.SELECT_BY_LOCATION_TYPE, "2");

            log.info("Number of Sahana Locations retrieved from database: " + sahanaLocations.size());

            if (sahanaLocations.size() == 0) {
                Assert.fail("No Sahana Locations were found in the database.");
            }

            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                log.info("Location: " + sahanaLocation.getName() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    public void testSelectSahanaLocationsByLocationTytpeAndParent() {
        try {

            List sahanaLocations;
            sahanaLocations = dao.searchSahanaLocations2(SahanaLocationsDAO.SELECT_BY_LOCATION_TYPE_AND_PARENT, new String[]{"4", "4"});

            log.info("Number of Sahana Locations retrieved from database: " + sahanaLocations.size());

            if (sahanaLocations.size() == 0) {
                Assert.fail("No Sahana Locations were found in the database.");
            }

            for (Iterator i = sahanaLocations.iterator(); i.hasNext();) {
                SahanaLocation sahanaLocation = (SahanaLocation) i.next();
                log.info("Location: " + sahanaLocation.getName() + " ");
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    public void testListAllProvicences() {
        try {

            List sahanaLocationProvinces;

            sahanaLocationProvinces = dao.listAllProvicences();

            log.info("Number of Sahana Provinces retrieved from database: " + sahanaLocationProvinces.size());

            if (sahanaLocationProvinces.size() == 0) {
                Assert.fail("No Sahana Provinces were found in the database.");
            }

            for (Iterator i = sahanaLocationProvinces.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("Province Lable: " + SahanaLocation.getLabel() + " Province Value: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testListAllDistricts() {
        try {

            List sahanaLocationDistricts;

            sahanaLocationDistricts = dao.listAllDistricts();

            log.info("Number of Sahana Districts retrieved from database: " + sahanaLocationDistricts.size());

            if (sahanaLocationDistricts.size() == 0) {
                Assert.fail("No Sahana Districts were found in the database.");
            }

            for (Iterator i = sahanaLocationDistricts.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("Districts Lable: " + SahanaLocation.getLabel() + "  Districts Value: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testListAllDivisions() {
        try {

            List sahanaLocationDivisions;

            sahanaLocationDivisions = dao.listAllDivisions();

            log.info("Number of Sahana Divisions retrieved from database: " + sahanaLocationDivisions.size());

            if (sahanaLocationDivisions.size() == 0) {
                Assert.fail("No Sahana Divisions were found in the database.");
            }

            for (Iterator i = sahanaLocationDivisions.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("Divisions Lable: " + SahanaLocation.getLabel() + "  Divisions Value: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    public void testListAllGNDivisions() {
        try {

            List sahanaLocationGNDivisions;

            sahanaLocationGNDivisions = dao.listAllGNDivisions();

            log.info("Number of Sahana GN Divisions retrieved from database: " + sahanaLocationGNDivisions.size());

            if (sahanaLocationGNDivisions.size() == 0) {
                Assert.fail("No Sahana GN Divisions were found in the database.");
            }

            for (Iterator i = sahanaLocationGNDivisions.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("GN Divisions Lable: " + SahanaLocation.getLabel() + "  GN Divisions Value: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    public void testListAllDistrictsByProvince() {
        try {

            List sahanaLocationDistrictsByProvince;
            String provinceCode = "2";
            sahanaLocationDistrictsByProvince = dao.listAllDistrictsByProvince(provinceCode);

            log.info("Number of Sahana Districts for Province Code 2**: " + sahanaLocationDistrictsByProvince.size());

            if (sahanaLocationDistrictsByProvince.size() == 0) {
                Assert.fail("No Sahana GN Districts were found in the database.");
            }

            for (Iterator i = sahanaLocationDistrictsByProvince.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("GN Districts Lable*: " + SahanaLocation.getLabel() + "  GN Districts Value*: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    public void testListAllDivisionsByDistrict() {
        try {

            List sahanaLocationDistrictsByProvince;
            String districtCode = "5";
            sahanaLocationDistrictsByProvince = dao.listAllDistrictsByProvince(districtCode);

            log.info("Number of Sahana Divisions for District Code 3**: " + sahanaLocationDistrictsByProvince.size());

            if (sahanaLocationDistrictsByProvince.size() == 0) {
                Assert.fail("No Sahana Divisions were found in the database.");
            }

            for (Iterator i = sahanaLocationDistrictsByProvince.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("Divisions Lable3*: " + SahanaLocation.getLabel() + "  Divisions Value3*: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }

    public void testListAllGNDivisionsByDivision() {
        try {

            List sahanaLocationGNDivisionByDivision;
            String divisionCode = "4";
            sahanaLocationGNDivisionByDivision = dao.listAllGNDivisionsByDivision(divisionCode);

            log.info("Number of Sahana GNDivisions for Division Code 3**: " + sahanaLocationGNDivisionByDivision.size());

            if (sahanaLocationGNDivisionByDivision.size() == 0) {
                Assert.fail("No Sahana GNDivisions were found in the database.");
            }

            for (Iterator i = sahanaLocationGNDivisionByDivision.iterator(); i.hasNext();) {
                LabelValue SahanaLocation = (LabelValue) i.next();
                log.info("GNDivisions Lable3*: " + SahanaLocation.getLabel() + "  GNDivisions Value3*: " + SahanaLocation.getValue());
            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        }
    }


    private SahanaLocationsDAO dao;
    static Log log = LogFactory.getLog(org.damage.db.test.SahanaLocationsDAOTest.class.getName());

}



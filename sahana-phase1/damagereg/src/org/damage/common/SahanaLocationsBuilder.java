/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.common;

import org.damage.db.persistence.SahanaLocationsDAO;

import java.util.List;

/**
 * Populate sahana location data from backend
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class SahanaLocationsBuilder {

    private static StringBuffer listAllDistrictsByProvince;
    private static StringBuffer listAllDivisionsByDistrict;
    private static StringBuffer listAllGNDivisionsByDivision;

    static {

        SahanaLocationsDAO sahanaLocationsDAO = new SahanaLocationsDAO();

        listAllDistrictsByProvince = new StringBuffer();
        listAllDivisionsByDistrict = new StringBuffer();
        listAllGNDivisionsByDivision = new StringBuffer();

        List listcode;
        String provCode;
        List provinces = sahanaLocationsDAO.listAllProvicences();

        for (int j = 0; j < provinces.size(); j++) {
            provCode = ((LabelValue) provinces.get(j)).getValue();
            listAllDistrictsByProvince.append("var provCode" + provCode + " = new Array(");
            listcode = sahanaLocationsDAO.listAllDistrictsByProvince(provCode);
            for (int i = 0; i < listcode.size(); i++) {
                if (i == 0) {
                    listAllDistrictsByProvince.append("\"" + ((LabelValue) listcode.get(i)).getValue() + "\"");
                } else {
                    listAllDistrictsByProvince.append("," + "\"" + ((LabelValue) listcode.get(i)).getValue() + "\"");
                }
            }
            listAllDistrictsByProvince.append(");");
            listAllDistrictsByProvince.append("var prov" + provCode + " = new Array(");
            for (int i = 0; i < listcode.size(); i++) {
                if (i == 0) {
                    listAllDistrictsByProvince.append("\"" + ((LabelValue) listcode.get(i)).getLabel() + "\"");
                } else {
                    listAllDistrictsByProvince.append("," + "\"" + ((LabelValue) listcode.get(i)).getLabel() + "\"");
                }
            }
            listAllDistrictsByProvince.append(");\n");
            listcode.clear();
        }
        listAllDistrictsByProvince.append("\n");
        provinces.clear();


        List divlistCode;
        String dicCode;

        List alldisCode = sahanaLocationsDAO.listAllDistricts();

        for (int j = 0; j < alldisCode.size(); j++) {
            dicCode = ((LabelValue) alldisCode.get(j)).getValue();
            listAllDivisionsByDistrict.append("var districtCode" + dicCode + " = new Array(");
            divlistCode = sahanaLocationsDAO.listAllDivisionsByDistrict(dicCode);
            for (int i = 0; i < divlistCode.size(); i++) {
                if (i == 0) {
                    listAllDivisionsByDistrict.append("\"" + ((LabelValue) divlistCode.get(i)).getValue() + "\"");
                } else {
                    listAllDivisionsByDistrict.append("," + "\"" + ((LabelValue) divlistCode.get(i)).getValue() + "\"");
                }
            }
            listAllDivisionsByDistrict.append(");");
            listAllDivisionsByDistrict.append("var district" + dicCode + " = new Array(");
            for (int i = 0; i < divlistCode.size(); i++) {
                if (i == 0) {
                    listAllDivisionsByDistrict.append("\"" + ((LabelValue) divlistCode.get(i)).getLabel() + "\"");
                } else {
                    listAllDivisionsByDistrict.append("," + "\"" + ((LabelValue) divlistCode.get(i)).getLabel() + "\"");
                }
            }
            listAllDivisionsByDistrict.append(");\n");
            divlistCode.clear();
        }
        alldisCode.clear();

        List gsdivlistCode;
        String gsdicCode;

        List gsalldisCode = sahanaLocationsDAO.listAllDivisions();

        for (int j = 0; j < gsalldisCode.size(); j++) {
            gsdicCode = ((LabelValue) gsalldisCode.get(j)).getValue();
            listAllGNDivisionsByDivision.append("var divisionCode" + gsdicCode + " = new Array(");
            gsdivlistCode = sahanaLocationsDAO.listAllGNDivisionsByDivision(gsdicCode);
            for (int i = 0; i < gsdivlistCode.size(); i++) {
                if (i == 0) {
                    listAllGNDivisionsByDivision.append("\"" + ((LabelValue) gsdivlistCode.get(i)).getValue() + "\"");
                } else {
                    listAllGNDivisionsByDivision.append("," + "\"" + ((LabelValue) gsdivlistCode.get(i)).getValue() + "\"");
                }
            }
            listAllGNDivisionsByDivision.append(");");
            listAllGNDivisionsByDivision.append("var division" + gsdicCode + " = new Array(");
            for (int i = 0; i < gsdivlistCode.size(); i++) {
                if (i == 0) {
                    listAllGNDivisionsByDivision.append("\"" + ((LabelValue) gsdivlistCode.get(i)).getLabel() + "\"");
                } else {
                    listAllGNDivisionsByDivision.append("," + "\"" + ((LabelValue) gsdivlistCode.get(i)).getLabel() + "\"");
                }
            }
            listAllGNDivisionsByDivision.append(");\n");
            gsdivlistCode.clear();
        }
        gsalldisCode.clear();

    }

    public static String getListAllDistrictsByProvince() {
        return listAllDistrictsByProvince.toString();
    }

    public static String getListAllDivisionsByDistrict() {
        return listAllDivisionsByDistrict.toString();
    }

    public static String getListAllGNDivisionsByDivision() {
        return listAllGNDivisionsByDivision.toString();
    }
}

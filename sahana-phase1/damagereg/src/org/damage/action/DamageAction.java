/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action;

import org.apache.struts.action.Action;
import org.damage.business.*;
import org.damage.common.DamageReporter;
import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;
import org.damage.db.persistence.DAOException;
import org.damage.db.persistence.DamageTypeDAO;
import org.damage.db.persistence.SahanaLocationsDAO;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.*;

/**
 *
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class DamageAction extends Action {

    protected static final String ACTION_SUCCESS = "success";
    protected static final String ACTION_FAILURE = "failure";
    protected static final String FWD_ERROR = "error";

    protected void debugFormData(HttpServletRequest request, String actionName) {
        String name;

        System.out.println("----------------------- DEBUG <REQUEST>: " + actionName + " ----------------------------");
        try {
            for (Enumeration e = request.getParameterNames(); e.hasMoreElements();) {
                name = (String) e.nextElement();
                System.out.println(name + "=" + request.getParameter(name));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("----------------------- .");

    }

    protected void debugSessionData(HttpServletRequest request, String actionName) {
        String name;

        System.out.println("----------------------- DEBUG <SESSION>: " + actionName + " ----------------------------");
        try {
            HttpSession https = request.getSession();
            System.out.println("SESSION:");
            for (Enumeration e = https.getAttributeNames(); e.hasMoreElements();) {
                name = (String) e.nextElement();
                System.out.println(name + "=" + https.getAttribute(name));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        System.out.println("----------------------- .");

    }

    protected Long getLongObject(String dataValue) {
        try {
            return new Long(dataValue);
        } catch (Exception e) {
            return null;
        }
    }

    protected String getValidLocationCode(String locationGSDivisionId,
                                          String locationDivisionId,
                                          String locationDistrictId,
                                          String locationProvinceCode) {
        if (locationGSDivisionId != null && !locationGSDivisionId.equals("default"))
            return locationGSDivisionId;
        if (locationDivisionId != null && !locationDivisionId.equals("default"))
            return locationDivisionId;
        if (locationDistrictId != null && !locationDistrictId.equals("default"))
            return locationDistrictId;
        if (locationProvinceCode != null && !locationProvinceCode.equals("default"))
            return locationProvinceCode;

        return null;
    }

    protected DamageReporter generateDamageReportList(DamageCase damageCase) throws DAOException {
        Set damageReports;
        DamageReport damageReport;
        Property property;
        Hashtable htRow;
        TreeElement node;
        ArrayList list = new ArrayList();
        SahanaLocationsDAO locationDAO = new SahanaLocationsDAO();
        DamageTypeDAO damageTypeDAO = new DamageTypeDAO();
        SahanaLocation location;
        DamageType damageType = new DamageType();
        Long locationId;
        Long damageTypeId;

        damageReports = damageCase.getDamageReports();
        if (damageReports != null) {
            for (Iterator iterator = damageReports.iterator(); iterator.hasNext();) {
                damageReport = (DamageReport) iterator.next();
                property = damageReport.getProperty();
                node = ClassificationBrowser.getNodeByType(damageReport.getPropertyTypeCode());
                locationId = getLongObject(property.getLocationCode());
                location = (locationId != null) ? locationDAO.getSahanaLocation(locationId) : null;
                damageTypeId = getLongObject(damageReport.getDamageTypeCode());
                damageType = (damageTypeId != null) ? damageTypeDAO.getDamageType(damageTypeId) : null;

                htRow = new Hashtable();
                htRow.put("ReportId", String.valueOf(damageReport.getUniqueId()));
                htRow.put("Property Type", node.getLabel());
                htRow.put("Location", (location != null) ? location.getName() : "");
                htRow.put("Severity", (damageType != null) ? damageType.getDamageDescription() : "");
                htRow.put("Estimated Damage Value", damageReport.getEstimatedDamageValue());
                list.add(htRow);
            }
        }

        DamageReporter reporter = new DamageReporter();
        reporter.setCurrentReport(list);
        return reporter;
    }

    protected static DamageReport findDamageReport(DamageCase damageCase, DamageReport damageReport_search) {
        DamageReport damageReport;

        Set damageReports = damageCase.getDamageReports();
        if (damageReports != null) {
            Iterator reports = damageReports.iterator();
            while (reports.hasNext()) {
                damageReport = (DamageReport) reports.next();
                if (damageReport_search.equals(damageReport)) {
                    return damageReport;
                }
            }
        }
        return null;
    }
}

/*
 * (C) Copyright 2004 Valista Limited. All Rights Reserved.
 *
 * These materials are unpublished, proprietary, confidential source code of
 * Valista Limited and constitute a TRADE SECRET of Valista Limited.
 *
 * Valista Limited retains all title to and intellectual property rights
 * in these materials.
 */

package org.campdb.web;

import org.campdb.util.LabelValue;
import org.campdb.db.DataAccessManager;

import javax.servlet.http.HttpServlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import java.util.List;
import java.util.LinkedList;
import java.util.Vector;
import java.util.ArrayList;

public class CampDbInit extends HttpServlet {

    DataAccessManager dataAccessManager = new DataAccessManager();
    public void init(ServletConfig servletConfig) throws ServletException {
        super.init(servletConfig);
        try {
            servletConfig.getServletContext().setAttribute("areas", getAreaLabelValues());
            servletConfig.getServletContext().setAttribute("provinces", getProviceLabelValues());
            servletConfig.getServletContext().setAttribute("districts", getDistrictLabelValues());
            servletConfig.getServletContext().setAttribute("divisions", getDivisionLabelValues());
            servletConfig.getServletContext().setAttribute("divisionInfo", getDivisionInfo());
        } catch (Exception e) {
            e.printStackTrace(System.err);
            List emptyList = new LinkedList();
            servletConfig.getServletContext().setAttribute("areas", emptyList);
            servletConfig.getServletContext().setAttribute("provinces", emptyList);
            servletConfig.getServletContext().setAttribute("districts", emptyList);
            servletConfig.getServletContext().setAttribute("divisions", emptyList);
            servletConfig.getServletContext().setAttribute("divisionInfo", emptyList);

        }
    }

    public List getDivisionLabelValues() throws Exception {
        return dataAccessManager.listDivisions();
    }

    public List getAreaLabelValues() throws Exception {
        return dataAccessManager.listAreas();
    }

    public List getProviceLabelValues() throws Exception {
        return dataAccessManager.listProvicences();
    }

    public List getDistrictLabelValues() throws Exception {
        return dataAccessManager.listDistricts();
    }

    public ArrayList getDivisionInfo()throws Exception{
        return dataAccessManager.getDivisionRelatedInfo();
    }

}

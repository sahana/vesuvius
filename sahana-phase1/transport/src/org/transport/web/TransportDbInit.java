/*
 * (C) Copyright 2004 Valista Limited. All Rights Reserved.
 *
 * These materials are unpublished, proprietary, confidential source code of
 * Valista Limited and constitute a TRADE SECRET of Valista Limited.
 *
 * Valista Limited retains all title to and intellectual property rights
 * in these materials.
 */

package org.transport.web;

//import org.transport.util.LabelValue;
import org.transport.db.DataAccessManager;

import javax.servlet.http.HttpServlet;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import java.util.List;
import java.util.LinkedList;

public class TransportDbInit extends HttpServlet {

    DataAccessManager dataAccessManager = new DataAccessManager();
    public void init(ServletConfig servletConfig) throws ServletException {
        super.init(servletConfig);
        try {
/*            servletConfig.getServletContext().setAttribute("areas", getAreaLabelValues());
            servletConfig.getServletContext().setAttribute("provinces", getProviceLabelValues());
            servletConfig.getServletContext().setAttribute("districts", getDistrictLabelValues());
            servletConfig.getServletContext().setAttribute("divisions", getDivisionLabelValues());
*/
        } catch (Exception e) {
            e.printStackTrace(System.err);
            List emptyList = new LinkedList();
            servletConfig.getServletContext().setAttribute("areas", emptyList);
            servletConfig.getServletContext().setAttribute("provinces", emptyList);
            servletConfig.getServletContext().setAttribute("districts", emptyList);
            servletConfig.getServletContext().setAttribute("divisions", emptyList);

        }
    }

/*    public List getDivisionLabelValues() throws Exception {
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
*/
}

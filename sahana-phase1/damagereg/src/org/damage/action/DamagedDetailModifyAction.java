/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.damage.business.DamageCase;
import org.damage.business.DamageReport;
import org.damage.business.DamageReportDetailType;
import org.damage.common.DamageReporter;
import org.damage.common.Globals;
import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;
import org.damage.util.SessionUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Set;

/**
 * "Insert Appropriate Class Description."
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class DamagedDetailModifyAction extends DamageAction {

    /**
     * Action forward Method
     *
     * @param mapping    ActionMapping
     * @param actionForm ActionForm
     * @param request    HttpServletRequest
     * @param response   HttpServletResponse
     * @return ActionForward
     */
    public ActionForward execute(ActionMapping mapping,
                                 ActionForm actionForm,
                                 HttpServletRequest request,
                                 HttpServletResponse response) throws
            Exception {

        try {

            String parameter = mapping.getParameter();
            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);

            if (parameter.equals("edit")) {

                doEditReport(request, damageCase);

                TreeElement selectedNode = ClassificationBrowser.getNodeByType((String) SessionUtils.getObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY));
                if (selectedNode.getTableName().equals("NULL")) {
                    return mapping.findForward("DamagedReportBasic");
                } else {
                    return mapping.findForward(selectedNode.getTableName());
                }
            }

            if (parameter.equals("remove")) {
                doRemoveReport(request, damageCase);
                return mapping.findForward(ACTION_SUCCESS);
            }

            if (parameter.equals("cancel")) {
                doCancelReport(request);
                return mapping.findForward(ACTION_SUCCESS);
            }

            return mapping.findForward(FWD_ERROR);

        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }

    }


    private void doEditReport(HttpServletRequest request, DamageCase damageCase)
            throws Exception {

        DamageReport damageReport_search;
        DamageReport damageReport_find;

        long id = getLongObject(request.getParameter("ReportId")).longValue();
        damageReport_search = new DamageReport(id);
        damageReport_find = findDamageReport(damageCase, damageReport_search);

        SessionUtils.putObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY, damageReport_find.getPropertyTypeCode());
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT_ID, String.valueOf(damageReport_find.getUniqueId()));
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT, damageReport_find);
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_PROPERTY_OBJECT, damageReport_find.getProperty());

        DamageReportDetailType damageReportDetailObject = damageReport_find.getDamageDetail();
        if (damageReportDetailObject != null) {
            SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_DETAIL_OBJECT, damageReportDetailObject);
        }
    }

    private void doRemoveReport(HttpServletRequest request, DamageCase damageCase)
            throws Exception {

        DamageReport damageReport;

        // Get previously added reports collection
        Set damageReports = damageCase.getDamageReports();
        long id = getLongObject(request.getParameter("ReportId")).longValue();
        if (damageReports != null) {
            damageReport = new DamageReport(id);

            damageReports.remove(damageReport);
            damageCase.setDamageReports(damageReports);

            SessionUtils.putObject(request, Globals.MODIFIED_CASE_OBJECT, damageCase);

            //-- set display report with current data
            if (!damageReports.isEmpty()) {
                DamageReporter reporter = generateDamageReportList(damageCase);
                SessionUtils.putObject(request, Globals.REPORT_OBJECT, reporter);
            } else {
                SessionUtils.putObject(request, Globals.REPORT_OBJECT, null);
            }
        }
    }

    private void doCancelReport(HttpServletRequest request)
            throws Exception {

        SessionUtils.putObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY, null);
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT_ID, null);
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT, null);
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_PROPERTY_OBJECT, null);
        SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_DETAIL_OBJECT, null);

    }


}

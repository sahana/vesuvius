/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.damage.business.DamageCase;
import org.damage.common.Globals;
import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;
import org.damage.util.SessionUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Date;

/**
 * @author Viraj Samaranayaka
 * @version 1.0
 */
public class DamagedCaseInitAction extends DamageAction {

    /**
     * Action forward Method
     *
     * @param actionMapping ActionMapping
     * @param actionForm    ActionForm
     * @param request       HttpServletRequest
     * @param response      HttpServletResponse
     * @return ActionForward
     */
    public ActionForward execute(ActionMapping actionMapping,
                                 ActionForm actionForm,
                                 HttpServletRequest request,
                                 HttpServletResponse response) throws
            Exception {

        try {

            System.out.println("DamagedCaseInitAction  execute ");

            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);
            if (damageCase == null) damageCase = new DamageCase();

            String reportedDate = request.getParameter("reportedDate");
            String damagedDate = request.getParameter("damageDate");
            String causeOfDamage = request.getParameter("causeOfDamage");
            String reporterNicPassportId = request.getParameter("reporterNicPassportId");
            String reporterName = request.getParameter("reporterName");
            String reporterTelNo = request.getParameter("reporterTelNo");
            String reporterAddress = request.getParameter("reporterAddress");
            String authOfficerId = request.getParameter("authOfficerId");
            String institutionId = request.getParameter("institutionId");
            String referenceNumber = request.getParameter("referenceNumber");

            damageCase.setReportedDate(Date.valueOf(reportedDate));
            damageCase.setDamageDate(Date.valueOf(damagedDate));
            damageCase.setCauseOfDamage(causeOfDamage);

            damageCase.setReporterNicPassportId(reporterNicPassportId);
            damageCase.setReporterName(reporterName);
            damageCase.setReporterTelNo(reporterTelNo);
            damageCase.setReporterAddress(reporterAddress);

            damageCase.setAuthOfficerId(authOfficerId);
            damageCase.setInstitutionId(institutionId);
            damageCase.setReferenceNumber(referenceNumber);

            String locationProvinceCode = request.getParameter("caseProvinceCode");
            String locationDistrictId = request.getParameter("caseDistrictId");
            String locationDivisionId = request.getParameter("caseDivisionId");
            String locationGSDivisionId = request.getParameter("caseGSDivisionId");

            //-- non persistent fields
            damageCase.setReporterProvince(locationProvinceCode);
            damageCase.setReporterDistrict(locationDistrictId);
            damageCase.setReporterDivision(locationDivisionId);
            damageCase.setReporterGSDivision(locationGSDivisionId);

            String reporterLocation = getValidLocationCode(locationGSDivisionId,
                    locationDivisionId,
                    locationDistrictId,
                    locationProvinceCode);
            damageCase.setReporterLocation(reporterLocation);

            //-- Custom Category Input Forms Selection based on property type
            int nodeId = Integer.parseInt(request.getParameter("propertyTypeID"));
            TreeElement selectedNode = ClassificationBrowser.getNodeById(nodeId); // only leaf nodes are selected from UI

            damageCase.setCustomDataType(selectedNode.getTableName());

            SessionUtils.putObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY, selectedNode.getKey());
            SessionUtils.putObject(request, Globals.MODIFIED_CASE_OBJECT, damageCase);

            if (selectedNode.getTableName().equals("NULL")) {
                return actionMapping.findForward("DamagedReportBasic");
            } else {
                return actionMapping.findForward(selectedNode.getTableName());
            }

        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }

    }

}

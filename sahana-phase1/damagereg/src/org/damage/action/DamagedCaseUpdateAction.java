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
import org.damage.db.persistence.DataAccessManager;
import org.damage.util.SessionUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Date;

/**
 * @author Viraj Samaranayaka
 * @version 1.0
 */

public class DamagedCaseUpdateAction extends DamageAction {

    /**
     * @param actionMapping
     * @param actionForm
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ActionForward execute(ActionMapping actionMapping,
                                 ActionForm actionForm,
                                 HttpServletRequest request,
                                 HttpServletResponse response)
            throws Exception {

        try {

            debugFormData(request, "DamagedCaseUpdateAction");
            debugSessionData(request, "DamagedCaseUpdateAction");

            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);

            setRequestData(request, damageCase);

            DataAccessManager dataAccessManager = new DataAccessManager();
            dataAccessManager.saveCase(damageCase);

            // clear the reports and keep the standard case info for the
            // next case if user needs it repeatedly.
            damageCase = new DamageCase();
            setRequestData(request, damageCase);

            SessionUtils.putObject(request, Globals.MODIFIED_CASE_OBJECT, damageCase);
            SessionUtils.putObject(request, Globals.REPORT_OBJECT, null);

            return actionMapping.findForward(ACTION_SUCCESS);

        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }

    }


    private void setRequestData(HttpServletRequest request, DamageCase damageCase) {

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

        // -- get the most specific available location
        String reporterLocation = getValidLocationCode(locationGSDivisionId,
                locationDivisionId,
                locationDistrictId,
                locationProvinceCode);
        damageCase.setReporterLocation(reporterLocation);

    }
}

/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action.helpers;

import org.damage.business.DamageDetailHospitalEstimatedCost;
import org.damage.business.DamageReport;
import org.damage.business.DamageReportDetailHospital;

import javax.servlet.http.HttpServletRequest;
import java.util.HashSet;
import java.util.Set;

/**
 * code to capture hospital specific data from submitted form
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class HospitalUpdateHelper implements ActionUpdateHelper {

    public synchronized void Update(HttpServletRequest request, DamageReport damageReport) {

        DamageReportDetailHospital damageDetailHospital = new DamageReportDetailHospital();

        String summaryFacility = request.getParameter("summaryFacility");
        String summaryStatus = request.getParameter("summaryStatus");
        damageDetailHospital.setPropertyTypeCode(damageReport.getPropertyTypeCode());
        damageDetailHospital.setHospitalName(request.getParameter("hospitalName"));
        damageDetailHospital.setSummaryFacility(summaryFacility);
        damageDetailHospital.setSummaryStatus(summaryStatus);

        DamageDetailHospitalEstimatedCost damageDetailHospitalEstimatedCost;
        Set damageDetailHospitalEstimatedCosts = new HashSet();
        int i = 1;  // starts from 1..
        int j = 20; // check for unordered sequence starts from 1
        while (j > 0) {
            while (request.getParameter(("reconstructionFacilityName" + String.valueOf(i))) != null &&
                    !request.getParameter(("reconstructionFacilityName" + String.valueOf(i))).trim().equals("")) {
                damageDetailHospitalEstimatedCost = new DamageDetailHospitalEstimatedCost();
                damageDetailHospitalEstimatedCost.setBudgetDescription(request.getParameter("reconstructionFacilityName" + String.valueOf(i)));
                damageDetailHospitalEstimatedCost.setEstimatedValue(Double.valueOf(request.getParameter(("reconstructionEstimatedCost" + String.valueOf(i)))));
                damageDetailHospitalEstimatedCosts.add(damageDetailHospitalEstimatedCost);
                i++;
            }
            j--;
        }
        damageDetailHospital.setDamageDetailHospitalEstimatedCosts(damageDetailHospitalEstimatedCosts);

        damageReport.setDamageDetail(damageDetailHospital);

    }


}

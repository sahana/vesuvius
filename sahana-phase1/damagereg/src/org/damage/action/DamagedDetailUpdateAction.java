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
import org.damage.business.Property;
import org.damage.common.ConfigReader;
import org.damage.common.DamageReporter;
import org.damage.common.Globals;
import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;
import org.damage.util.SessionUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.lang.reflect.Method;
import java.util.HashSet;
import java.util.Set;

/**
 * @author Viraj Samaranayaka
 * @version 1.0
 */

public class DamagedDetailUpdateAction extends DamageAction {

    public ActionForward execute(ActionMapping actionMapping,
                                 ActionForm actionForm,
                                 HttpServletRequest request,
                                 HttpServletResponse response) throws
            Exception {

        try {

            debugFormData(request, "DamagedDetailUpdateAction");
            debugSessionData(request, "DamagedDetailUpdateAction");

            Property property = new Property();
            DamageReport damageReport = new DamageReport();

            //-- check if this is an edit operation
            String damageReportId = (String) SessionUtils.getObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT_ID);
            if (damageReportId != null) {
                damageReport = (DamageReport) SessionUtils.getObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT);
                property = (Property) SessionUtils.getObject(request, Globals.MODIFIED_DAMAGE_PROPERTY_OBJECT);
            }

            //-- Property Update --

            String propertyOwnerName = request.getParameter("ownerName");
            String propertyOwnerPersonRef = request.getParameter("ownerPersonRef");
            String propertyOwnerAddress = request.getParameter("ownerAddress");
            String propertyPropertyAddress = request.getParameter("propertyAddress");
            String propertyIsInsured = request.getParameter("isInsured") != null ? request.getParameter("isInsured") : "0";
            String propertyInsuranceCompany = request.getParameter("insuranceCompany");
            String propertyInsurencePolicy = request.getParameter("insurencePolicy");
            String propertyInsurenceValue = request.getParameter("insurenceValue");

            TreeElement selectedNode = ClassificationBrowser.getNodeByType((String) SessionUtils.getObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY)); // only leaf nodes are selected from UI
            String propertyTypeCode = selectedNode.getKey();
            String damageReportTable = selectedNode.getTableName();

            property.setPropertyTypeCode(propertyTypeCode);
            property.setOwnerName(propertyOwnerName);
            property.setOwnerPersonRef(propertyOwnerPersonRef);
            property.setOwnerAddress(propertyOwnerAddress);
            property.setPropertyAddress(propertyPropertyAddress);

            String locationProvinceCode = request.getParameter("caseProvinceCode");
            String locationDistrictId = request.getParameter("caseDistrictId");
            String locationDivisionId = request.getParameter("caseDivisionId");
            String locationGSDivisionId = request.getParameter("caseGSDivisionId");

            //-- non persistent fields
            property.setLocationProvince(locationProvinceCode);
            property.setLocationDistrict(locationDistrictId);
            property.setLocationDivision(locationDivisionId);
            property.setLocationGSDivision(locationGSDivisionId);

            // -- get the most specific available location
            String propertyLocation = getValidLocationCode(locationGSDivisionId,
                    locationDivisionId,
                    locationDistrictId,
                    locationProvinceCode);
            property.setLocationCode(propertyLocation);

            boolean blnIsInsured = (propertyIsInsured.trim().equals("1"));
            property.setIsInsured(new Boolean(blnIsInsured));

            property.setInsuranceCompany((blnIsInsured) ? propertyInsuranceCompany : "");
            property.setInsurencePolicy((blnIsInsured) ? propertyInsurencePolicy : "");

            if (propertyInsurenceValue != null && !propertyInsurenceValue.trim().equals("")) {
                property.setInsurenceValue(Double.valueOf(propertyInsurenceValue));
            } else {
                property.setInsurenceValue(new Double(0));
            }

            //-- Damage Report Update --

            damageReport.setProperty(property);

            String damageReportContactPersonName = request.getParameter("contactPersonName");
            String damageNumberPersonsAffected = request.getParameter("numberPersonsAffected");
            String damageContactPersonId = request.getParameter("contactPersonId");
            String damageDamageTypeCode = request.getParameter("damageTypeCode");
            String damageEstimatedDamageValue = request.getParameter("estimatedDamageValue");
            String damageIsRelocate = request.getParameter("isRelocate") != null ? request.getParameter("isRelocate") : "0";

            damageReport.setContactPersonName(damageReportContactPersonName);

            if (damageNumberPersonsAffected != null && !damageNumberPersonsAffected.trim().equals("")) {
                damageReport.setNumberPersonsAffected(Long.valueOf(damageNumberPersonsAffected));
            } else {
                damageReport.setNumberPersonsAffected(new Long(0));
            }

            damageReport.setPropertyTypeCode(propertyTypeCode);
            damageReport.setDamageReportTable(damageReportTable);
            damageReport.setContactPersonId(damageContactPersonId);
            damageReport.setDamageTypeCode(damageDamageTypeCode);

            if (damageEstimatedDamageValue != null && !damageEstimatedDamageValue.trim().equals("")) {
                damageReport.setEstimatedDamageValue(Double.valueOf(damageEstimatedDamageValue));
            }

            boolean blnIsRelocate = damageIsRelocate.trim().equals("1");
            damageReport.setIsRelocate(new Boolean(blnIsRelocate));

            //-- Load custom form data via reflection --
            String helperClassName = ConfigReader.getActionUpdateHelperClassName(damageReportTable);
            if (helperClassName != null) {
                Class updateHelperClass = Class.forName(helperClassName);
                Method updateMethod = updateHelperClass.getDeclaredMethod("Update",
                        new Class[]{HttpServletRequest.class, DamageReport.class});
                updateMethod.invoke(updateHelperClass.newInstance(), new Object[]{request, damageReport});
            }

            //-- Damage Case Update --
            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);

            // Get previously added reports collection
            Set damageReports = damageCase.getDamageReports();
            if (damageReports == null) damageReports = new HashSet();
            if (damageReportId != null) {
                //existing report
                DamageReport damageReport_search;
                DamageReport damageReport_find;

                long reportId = getLongObject(damageReportId).longValue();
                damageReport_search = new DamageReport(reportId);
                damageReport_find = findDamageReport(damageCase, damageReport_search);
                damageReports.remove(damageReport_find);
                damageReports.add(damageReport);
            } else {
                damageReports.add(damageReport);
            }
            damageCase.setDamageReports(damageReports);

            SessionUtils.putObject(request, Globals.MODIFIED_CASE_OBJECT, damageCase);

            //-- set display report with current data
            DamageReporter reporter = generateDamageReportList(damageCase);
            SessionUtils.putObject(request, Globals.REPORT_OBJECT, reporter);

            // remove session values no longer used
            SessionUtils.putObject(request, Globals.SELECTED_PROPERTY_TYPE_KEY, null);
            SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT_ID, null);
            SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_OBJECT, null);
            SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_REPORT_DETAIL_OBJECT, null);
            SessionUtils.putObject(request, Globals.MODIFIED_DAMAGE_PROPERTY_OBJECT, null);

            return actionMapping.findForward(ACTION_SUCCESS);

        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }

    }

}

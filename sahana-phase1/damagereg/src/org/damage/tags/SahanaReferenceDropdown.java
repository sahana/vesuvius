/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/

package org.damage.tags;

import org.damage.common.LabelValue;
import org.damage.db.persistence.DamageTypeDAO;
import org.damage.db.persistence.InstitutionDAO;
import org.damage.db.persistence.InsuranceCompanyDAO;
import org.damage.db.persistence.SahanaLocationsDAO;

import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;

/**
 * Tag class is used to display location dropdown for Provinces,
 * the remaining dropdowns are generated dynamically using javascript.
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */
public final class SahanaReferenceDropdown extends TagSupport {

    private String name;
    private String styleClass;
    private String onChangeJS;
    private String defaultValue;
    private boolean showLocations;
    private boolean showInstitutions;
    private boolean showInsuranceCompany;
    private boolean showDamageType;

    public void setName(String name) {
        this.name = name;
    }

    public void setStyleClass(String styleClass) {
        this.styleClass = styleClass;
    }

    public void setDefaultValue(String defaultValue) {
        this.defaultValue = defaultValue;
    }

    public void setOnChangeJS(String onChangeJS) {
        this.onChangeJS = onChangeJS;
    }

    public void setShowLocations(boolean showLocations) {
        this.showLocations = showLocations;
    }

    public void setShowInstitutions(boolean showInstitutions) {
        this.showInstitutions = showInstitutions;
    }

    public void setShowInsuranceCompany(boolean showInsuranceCompany) {
        this.showInsuranceCompany = showInsuranceCompany;
    }

    public void setShowDamageType(boolean showDamageType) {
        this.showDamageType = showDamageType;
    }

    /**
     * Process the end tag for this instance.
     * This method is invoked by the JSP page implementation object on
     * all Tag handlers.
     *
     * @return Return EVAL_PAGE.
     */
    public int doEndTag() {

        try {
            JspWriter out = super.pageContext.getOut();

            if (showLocations) doLocationsDropdown(out);
            if (showInstitutions) doInstitutionsDropdown(out);
            if (showInsuranceCompany) doInsuranceCompanyDropdown(out);
            if (showDamageType) doDamageTypeDropdown(out);

        } catch (Exception nos) {
        }

        return EVAL_PAGE;

    }

    /**
     * Called on a Tag handler to release state.
     */
    public void release() {
        super.release();

    }

    private void doLocationsDropdown(JspWriter out) throws IOException {

        SahanaLocationsDAO daProvience = new SahanaLocationsDAO();
        List provinces = (List) daProvience.listAllProvicences();

        createDropdown(out, provinces);
    }

    private void doInstitutionsDropdown(JspWriter out) throws IOException {

        InstitutionDAO instituteDAO = new InstitutionDAO();
        List institutes = (List) instituteDAO.listAllInstitutions();

        createDropdown(out, institutes);
    }

    private void doInsuranceCompanyDropdown(JspWriter out) throws IOException {

        InsuranceCompanyDAO insurenceDAO = new InsuranceCompanyDAO();
        List insurences = (List) insurenceDAO.listAllInsuranceCompany();

        createDropdown(out, insurences);
    }

    private void doDamageTypeDropdown(JspWriter out) throws IOException {

        DamageTypeDAO damageTypeDAO = new DamageTypeDAO();
        List damageTypes = (List) damageTypeDAO.listAllDamageType();

        createDropdown(out, damageTypes);
    }

    private void createDropdown(JspWriter out, List list) throws IOException {
        LabelValue labelValue;

        String onChangeTxt = (onChangeJS != null) ? (" onChange=\"" + onChangeJS + "\"") : "";
        out.print("<select name=\"" + name + "\" class=\"" + styleClass + "\"" + onChangeTxt + ">\n");
        out.print("<option value=\"" + defaultValue + "\">&lt;select&gt;</option>\n");
        for (Iterator iterator = list.iterator(); iterator.hasNext();) {
            labelValue = (LabelValue) iterator.next();
            out.print("<option value=\"" + labelValue.getValue() + "\">" + labelValue.getLabel() + "</option>\n");
        }
        out.print("</select>\n");
    }

}

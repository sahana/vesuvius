/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/

package org.damage.tags;

import org.damage.common.SahanaLocationsBuilder;

import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * Tag class is used to display javascript arrays used for location dropdowns
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */
public final class SahanaLocationsArray extends TagSupport {


    private boolean listAllDistrictsByProvince;
    private boolean listAllDivisionsByDistrict;
    private boolean listAllGNDivisionsByDivision;


    public void setListAllDistrictsByProvince(boolean listAllDistrictsByProvince) {
        this.listAllDistrictsByProvince = listAllDistrictsByProvince;
    }

    public void setListAllDivisionsByDistrict(boolean listAllDivisionsByDistrict) {
        this.listAllDivisionsByDistrict = listAllDivisionsByDistrict;
    }

    public void setListAllGNDivisionsByDivision(boolean listAllGNDivisionsByDivision) {
        this.listAllGNDivisionsByDivision = listAllGNDivisionsByDivision;
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

            if (listAllDistrictsByProvince)
                out.print(SahanaLocationsBuilder.getListAllDistrictsByProvince() + "\n");
            if (listAllDivisionsByDistrict)
                out.print(SahanaLocationsBuilder.getListAllDivisionsByDistrict() + "\n");
            if (listAllGNDivisionsByDivision)
                out.print(SahanaLocationsBuilder.getListAllGNDivisionsByDivision() + "\n");

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

}

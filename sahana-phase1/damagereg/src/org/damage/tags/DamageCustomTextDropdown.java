/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/

package org.damage.tags;

import org.damage.business.DamageCase;
import org.damage.common.CustomTextReader;
import org.damage.common.Globals;
import org.damage.common.LabelValue;
import org.damage.util.SessionUtils;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.util.Iterator;
import java.util.List;

/**
 * Tag class is used to display a custom text dropdown based on property type
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */
public final class DamageCustomTextDropdown extends TagSupport {

    private String customString;
    private String name;
    private String styleClass;
    private String onChangeJS;
    private String defaultValue;

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

            HttpServletRequest request = (HttpServletRequest) super.pageContext.getRequest();
            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);

            CustomTextReader customText = new CustomTextReader();
            List facilities = (List) customText.getCustomDropDownValues(damageCase.getCustomDataType(), customString);

            out.print("<select class=\"" + styleClass + "\" name=\"" + name + "\" onChange=\"" + onChangeJS + "\">");
            out.print("<option value=\"" + defaultValue + "\">&lt;select&gt;</option>");
            for (Iterator iterator = facilities.iterator(); iterator.hasNext();) {
                LabelValue facilitie = (LabelValue) iterator.next();
                out.print("<option value=\"" + facilitie.getLabel() + "\">" + facilitie.getLabel() + "</option>");

            }
            out.print("</select>");

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

    public void setCustomString(String customString) {
        this.customString = customString;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setStyleClass(String styleClass) {
        this.styleClass = styleClass;
    }

    public void setOnChangeJS(String onChangeJS) {
        this.onChangeJS = onChangeJS;
    }

    public void setDefaultValue(String defaultValue) {
        this.defaultValue = defaultValue;
    }
}

/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.tags;

import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * Drops the javascript tree structure for calssification.
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class DamageReportList extends TagSupport {

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

/*
            DamageReport damagedReport;
            TreeElement node1;
            DamageCase damageCase = (DamageCase) SessionUtils.getObject(request, Globals.MODIFIED_CASE_OBJECT);
            if (damageCase != null) {
                Set damageReports = damageCase.getDamageReports();
                if (damageReports !=null) {
                    for (Iterator iterator = damageReports.iterator(); iterator.hasNext();) {
                        damagedReport = (DamageReport) iterator.next();
                        node1 =ClassificationBrowser.getNodeByType(damagedReport.getPropertyTypeCode());
                        %><tr class="formText"><%
                        %><td height="20"><%= node1.getLabel() %></td><%
                        %><td height="20"><%= damagedReport.getEstimatedDamageValue() %></td><%
                        %><td height="20"><%= "" %></td><%
                        %>
                          <td height="20">
                            <a href="#">Edit</a>&nbsp;&nbsp;<a>|</a>&nbsp;&nbsp;
                            <a href="#">Remove</a>&nbsp;&nbsp;<a>|</a>&nbsp;&nbsp;
                            <a href="#">Image upload&#8230;</a>
                          </td>
                          </tr>
                        <%
                    }
                }
            }
*/

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

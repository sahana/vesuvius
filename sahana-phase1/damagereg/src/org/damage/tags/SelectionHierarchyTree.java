/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.tags;

import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;

import javax.servlet.jsp.JspWriter;
import javax.servlet.jsp.tagext.TagSupport;
import java.util.Iterator;
import java.util.Vector;

/**
 * Drops the javascript tree structure for calssification.
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class SelectionHierarchyTree extends TagSupport {

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

            out.print("var d = new dTree('d');\n");

            TreeElement node;
            Vector elements = ClassificationBrowser.getTreeElements();

            for (Iterator iterator = elements.iterator(); iterator.hasNext();) {
                node = (TreeElement) iterator.next();
                out.print("d.add(" + node.getId() + "," + node.getParentId() + ",'" + node.getLabel() + "','" +
                        ((node.isLeaf() && node.isEnabled()) ? "#" : "") + "','','');\n");
            }

            out.print("document.write(d);\n");
            out.print("resetTree();\n");

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

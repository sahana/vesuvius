/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.util;

import org.damage.common.Globals;
import org.damage.common.selectionhierarchy.ClassificationBrowser;
import org.damage.common.selectionhierarchy.TreeElement;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Stack;

/**
 * Collection of simple utility methods.
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public final class Tools {

    private Tools() {
    }

    /**
     * Utility method to create a <code>Date</code> class
     * from <code>dateString</code>.
     *
     * @param dateString
     * @return Date
     * @throws RuntimeException is dateString is invalid
     */
    public static Date parseDate(String dateString) {
        try {
            SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MMM-dd");
            return sdf.parse(dateString);
        } catch (ParseException pe) {
            throw new RuntimeException("Not a valid date: " + dateString +
                    ". Must be of YYYY-MMM-DD format.");
        }
    }

    public static String getCurrentClassificationPath(HttpServletRequest request) {

        HttpSession session = request.getSession();
        TreeElement selectedNode = ClassificationBrowser.getNodeByType((String) session.getAttribute(Globals.SELECTED_PROPERTY_TYPE_KEY));

        return getClassificationPath(selectedNode.getId());
    }

    public static String getClassificationPath(int nodeId) {
        StringBuffer tree = new StringBuffer();

        Stack parentTree = ClassificationBrowser.getParentHierarchy(nodeId);
        while (!parentTree.empty()) {
            tree.append(parentTree.pop());
            tree.append(!parentTree.empty() ? " -> " : "");
        }

        return tree.toString();
    }

}


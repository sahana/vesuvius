/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.util;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 *
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public final class SessionUtils {

    /**
     * Store the specified object in the Session
     *
     * @param request HttpServletRequest
     * @param key     String key to store the specified object with
     * @param obj     Object to store in the session
     * @throws Exception when session is not found or there is an exception
     *                   accessing the Session object.
     */
    public static void putObject(HttpServletRequest request, String key, Object obj)
            throws Exception {

        HttpSession https = request.getSession();
        if (https == null) {
            throw new Exception("Http Session Not Found");
        }
        // Store the object in Http Session
        https.setAttribute(key, obj);
    }


    /**
     * Gets the Object from the session, if one exists.
     *
     * @param request The HttpRequest to get the object from
     * @param key     Key to use to look up the object from the Session.
     * @return Object    Object if one is stored in the session.
     *         null if no Object exists or if no session exists.
     * @throws Exception Thrown if there is any exception getting the object from the session.
     */
    public static Object getObject(HttpServletRequest request, String key) throws Exception {

        HttpSession https = request.getSession();
        if (https == null) {
            throw new Exception("Http Session Not Found");
        }
        // Get the object from the Http Session
        return https.getAttribute(key);
    }


    public static String getRealPath(HttpServletRequest request, String filename) throws Exception {
        HttpSession https = request.getSession();
        if (https == null) {
            throw new Exception("Http Session Not Found");
        }
        return https.getServletContext().getRealPath(filename);
    }
}


/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.damage.common.selectionhierarchy.ClassificationBrowser;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * @author Chamath Edirisuriya
 * @version 1.0
 */

public class SystemInitAction extends DamageAction {

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
                                 HttpServletResponse response) throws
            Exception {

        try {

            ClassificationBrowser.load(request);
            return actionMapping.findForward(ACTION_SUCCESS);

        } catch (Exception e) {
            e.printStackTrace();
            throw e;
        }

    }

}

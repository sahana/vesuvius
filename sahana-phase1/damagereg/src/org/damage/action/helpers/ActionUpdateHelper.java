/*
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*/
package org.damage.action.helpers;

import org.damage.business.DamageReport;

import javax.servlet.http.HttpServletRequest;

/**
 * All custom code to capture custom form data should implement this interface
 *
 * @author Chamath Edirisuriya
 * @version 1.0
 * 
 */

public interface ActionUpdateHelper {

    void Update(HttpServletRequest request, DamageReport damageReport);

}

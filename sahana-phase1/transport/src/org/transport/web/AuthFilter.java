/*
 * (C) Copyright 2004 Valista Limited. All Rights Reserved.
 *
 * These materials are unpublished, proprietary, confidential source code of
 * Valista Limited and constitute a TRADE SECRET of Valista Limited.
 *
 * Valista Limited retains all title to and intellectual property rights
 * in these materials.
 */

package org.transport.web;

import org.transport.util.TRANSPORTConstants;

import javax.servlet.*;
import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class AuthFilter  implements Filter {
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    public void doFilter(ServletRequest request,
      ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest httpReq = (HttpServletRequest)request;
        HttpSession session = httpReq.getSession();

        if (isSessionValid(session)) {
            chain.doFilter(request, response);
            return;
        }

         if(httpReq.getRequestURL().indexOf("Index.jsp") < 0) {
            if (!isSessionValid(session)) {
                ((HttpServletResponse)response).sendRedirect("Index.jsp");
                return;
            }
        }
        chain.doFilter(request, response);


   }

    private boolean isSessionValid(HttpSession session) {
        return session.getAttribute(TRANSPORTConstants.IContextInfoConstants.USER_INFO) == null ? false : true;
    }

    public void destroy() {

    }

}

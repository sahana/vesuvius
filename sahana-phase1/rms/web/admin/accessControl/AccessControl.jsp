<%@ page import="tccsol.admin.accessControl.LoginBean"%>
<%
       LoginBean bean = null;
       session = request.getSession();
       String messages = "";
       String path = "";
       String modNo = "";
       String accessLvl = "";

       try
       {
        tccsol.admin.accessControl.AuditLog log = new tccsol.admin.accessControl.AuditLog();

      if (request.getAttribute("modNo") != null)
        modNo = (String)request.getAttribute("modNo");

      if (request.getAttribute("accessLvl") != null)
        accessLvl = (String)request.getAttribute("accessLvl");

          if (accessLvl.equalsIgnoreCase("PAGE"))
            session.removeAttribute("LoginBean");

          if (session.getAttribute("LoginBean") != null)
            bean = (LoginBean) session.getAttribute("LoginBean");

          if (bean == null)
            bean = new LoginBean();

          if (!bean.isValid())
          {
              if (request.getParameter("userName") != null)
                bean.setUserName(request.getParameter("userName").trim());

              if (request.getParameter("passwd") != null)
                bean.setPassword(request.getParameter("passwd").trim());

             if (bean.isValidUser()) {
               session.setAttribute("LoginBean", bean);
               request.setAttribute("isValidUsr", "Y");
               log.logEntry(bean.getUserName(), modNo, "Login");
             }
             else {
                 if (bean.getMessages().size() > 0)
                    messages = (String)bean.getMessages().elementAt(0);
             }
         }

    //Access permission check
    tccsol.admin.accessControl.AccessControl access = null;

//    if (request.getParameter("turl") != null)
//        path = request.getParameter("turl").trim();

    //Access Control implementation - START

           /*
    if (modNo.equals("0"))    //Sign out
    {
        session.removeAttribute("LoginBean");
        request.setAttribute("hasAccess", "");
        return;
    }
             */
    if (bean.isValid())
    {
        int mno = 0;
        try{
            mno = Integer.parseInt(modNo);
        }
        catch(Exception e)
        {

            messages = "Invalid Module Id for target page. Contact system administrator";
            request.setAttribute("turl", path);
            request.setAttribute("hasAccess", "N");
          //  return;
        }

        if (accessLvl.length() == 0)
        {
            accessLvl = "PAGE";
        }

        tccsol.admin.accessControl.LoginBean logb = (tccsol.admin.accessControl.LoginBean) session.getAttribute("LoginBean");

        byte st = 0;
        if (logb == null)
            st = 1;
        else {
            if (logb.getRoleId() == 0)
                st = 1;
        }

        if (st == 0)
            access = new tccsol.admin.accessControl.AccessControl();
        else {
            messages = "Please login before you proceed";
            request.setAttribute("turl", path);
            request.setAttribute("hasAccess", "N");
           // return;
        }

    //    if (modNo.equals("-1"))
    //    {
    //        request.getRequestDispatcher(path).forward(request,response);
    //        return;
    //    }

        if (access.hasAccess(mno, logb.getRoleId(), accessLvl.toUpperCase(), logb.getRoleName(), accessLvl, logb.getUserName()) == false)
        {
            if (access.getMessages().size() > 0)
                messages = (String)access.getMessages().elementAt(0);
            request.setAttribute("turl", path);
            request.setAttribute("hasAccess", "N");
        }
        else {
            request.setAttribute("hasAccess", "Y");
            log.logEntry(bean.getUserName(), modNo, accessLvl);
        }
             //Access Control implementation - END
    //
    }
    }
    catch(Throwable t)
    {
       messages = "Error: " + t.getMessage();
       request.setAttribute("hasAccess", "N");
    }

     if (!bean.isValid()) {
        request.getRequestDispatcher("AuthError.jsp?messages="+messages).forward(request, response);
        return;
     }
     else {
         String str = (String)request.getAttribute("hasAccess");
         if (str.equalsIgnoreCase("N"))
         {
             request.getRequestDispatcher("AuthError.jsp?messages="+messages).forward(request, response);
             return;
         }
     }

%>
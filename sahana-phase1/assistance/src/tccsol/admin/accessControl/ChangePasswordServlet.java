package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class ChangePasswordServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       ChangePasswordBean bean = null;
       HttpSession session = null;
       AccessControl access = null;

       String url = "";
       String addUrl = "";
       String cAct = "";

       try
       {
          bean = new ChangePasswordBean();
          session = request.getSession();

          url = request.getParameter("url").trim();
          cAct = request.getParameter("callAction").trim();

          addUrl = "/admin/accessControl/ChangePassword.jsp";

          if (request.getParameter("empId") != null)
            bean.setEmpId(request.getParameter("empId").trim().toUpperCase());

          if (request.getParameter("userName") != null)
            bean.setUserName(request.getParameter("userName").trim());

          if (request.getParameter("curPass") != null)
            bean.setOldPass(request.getParameter("curPass").trim());

          if (request.getParameter("pass1") != null)
            bean.setPass1(request.getParameter("pass1").trim());

          if (request.getParameter("pass2") != null)
            bean.setPass2(request.getParameter("pass2").trim());


          //Access Control implementation - START
          LoginBean logb = (LoginBean) session.getAttribute("LoginBean");

          byte st = 0;
          if (logb == null)
            st = 1;
          else {
            if (logb.getRoleId() == 0)
                st = 1;
          }

          if (st == 0)
            access = new AccessControl();
          else {
            bean.getMessages().add("Please login before you proceed");
            request.setAttribute("messages", bean.getMessages());
            request.setAttribute("ChangePasswordBean", bean);
            request.getRequestDispatcher(url).forward(request,response);
            return;
          }
          //Access Control implementation - END


          if (cAct.equals("Change Password"))
          {
              Vector v = new Vector();
              v = bean.validate();
              if (v.size()>0)
              {
                  request.setAttribute("messages", bean.getMessages());
                  request.setAttribute("ChangePasswordBean", bean);
                  request.getRequestDispatcher(addUrl).forward(request,response);
                  return;
               }

               if (bean.insert() == false)
                  request.setAttribute("ChangePasswordBean", bean);

               request.setAttribute("messages", bean.getMessages());
               request.getRequestDispatcher(addUrl).forward(request,response);
           }


           return;
        }//end try block
        catch(Throwable t)
        {
           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           request.setAttribute("ChangePasswordBean", bean);
           request.getRequestDispatcher(addUrl).forward(request,response);
           return;
        }
        finally
        {
            if(bean!=null)
            {
                bean.closeDBConn();
            }
        }
  }

  //Clean up resourcesx
  public void destroy()
  {
  }
}
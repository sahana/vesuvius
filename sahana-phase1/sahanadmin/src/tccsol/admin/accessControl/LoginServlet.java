package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class LoginServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       //catch all exceptions including runtime exeptions
       LoginBean bean = null;
       HttpSession session = request.getSession();

       String url = "";

       try
       {
         //populating the bean with request data
          bean = new LoginBean();
          url = request.getParameter("url").trim();

          if (request.getParameter("userName") != null)
            bean.setUserName(request.getParameter("userName").trim());

          if (request.getParameter("passwd") != null)
            bean.setPassword(request.getParameter("passwd").trim());

          if (request.getParameter("callAction").trim().equals("Login"))
          {
              if (url.equals("/admin/accessControl/Login1.jsp"))
              {
                 bean.isValidUser();
                 request.setAttribute("messages", bean.getMessages());
                 session.setAttribute("LoginBean", bean);

                 if (bean.getMessages().size() > 0)
                   request.getRequestDispatcher("/admin/accessControl/Login1.jsp").forward(request,response);
                 else
                   request.getRequestDispatcher("/admin/accessControl/welcome.jsp").forward(request,response);
              }
          }

          return;
        }//end try block
        catch(Throwable t)
        {
           String path = "/admin/accessControl/Login1.jsp";
           if (url.length() != 0)
              path = url;

           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           session.setAttribute("LoginBean", bean);
           request.getRequestDispatcher(path).forward(request,response);
           return;
        }
  }

  //Clean up resourcesx
  public void destroy()
  {
  }
}

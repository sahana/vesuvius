package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class AccessServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Get request
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       Vector messages = new Vector();
       AccessControl access = null;
       HttpSession session = null;

       String url = "";

       String path = "";
       String modNo = "";

       try
       {
          session = request.getSession();

          url = "/util/navigationError.jsp";

          if (request.getParameter("turl") != null)
              path = request.getParameter("turl").trim();

          if (request.getParameter("modNo") != null)
              modNo = request.getParameter("modNo").trim();

          //Access Control implementation - START

          if (modNo.equals("0"))    //Sign out
          {
            session.removeAttribute("LoginBean");
            request.getRequestDispatcher(path).forward(request,response);
            return;
          }


          int mno = 0;
          try{
            mno = Integer.parseInt(modNo);
          }
          catch(Exception e)
          {
            messages.add("Invalid Module Id for target page. Contact system administrator");
            request.setAttribute("messages", messages);
            request.getRequestDispatcher(url).forward(request,response);

            return;
          }


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
            messages.add("Please login before you proceed");
            request.setAttribute("messages", messages);
            request.getRequestDispatcher("admin/accessControl/Login1.jsp").forward(request,response);
            return;
          }

          if (modNo.equals("-1"))
          {
            request.getRequestDispatcher(path).forward(request,response);
            return;
          }

          if (access.hasAccess(mno, logb.getRoleId(), "PAGE", logb.getRoleName(), "Page Access") == false)
          {
             messages = access.getMessages();
             request.setAttribute("messages", messages);
             request.getRequestDispatcher(url).forward(request,response);
             return;
          }
          else {
             request.getRequestDispatcher(path).forward(request,response);
             return;
          }

          //Access Control implementation - END
        }
        catch(Throwable t)
        {
           messages.add("Error: " + t.getMessage());
           request.setAttribute("messages", messages);
           request.getRequestDispatcher(url).forward(request,response);
           return;
        }
  }

  //Clean up resourcesx
  public void destroy()
  {
  }
}

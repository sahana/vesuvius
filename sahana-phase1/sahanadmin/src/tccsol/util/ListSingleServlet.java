package tccsol.util;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class ListSingleServlet extends HttpServlet {
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       //catch all exceptions including runtime exeptions
       ListSingleBean bean = null;
       HttpSession session = request.getSession();
       String cAct = "";

       try
       {
          bean = new ListSingleBean();
          bean.setUrl(request.getParameter("url"));
          cAct = request.getParameter("callAction").trim();

          if (cAct.equals("Add"))
          {
              bean.setId("");
              bean.setName("");

              if (request.getParameter("lst") != null)
              {
                  Vector v = new Vector();
                  String str = request.getParameter("lst").trim();
                  v = Utility.splitString(str, '|');

                  if (v.size() >= 1)
                    bean.setId((String) v.elementAt(0));
                  if (v.size() >= 2)
                    bean.setName((String) v.elementAt(1));
                  if (v.size() >= 3)
                    bean.setCol3((String) v.elementAt(2));
                  if (v.size() >= 4)
                    bean.setCol4((String) v.elementAt(3));
                  if (v.size() >= 5)
                    bean.setCol5((String) v.elementAt(4));
              }

              if (request.getParameter("listType") != null)
              {
                  bean.setType(request.getParameter("listType").trim());
              }
              session.setAttribute("ListSBean", bean);
              request.setAttribute("messages", bean.getMessages());
              request.getRequestDispatcher(bean.getUrl()).forward(request,response);
          }

          if (cAct.equals("Back"))
          {
              request.setAttribute("messages", bean.getMessages());
              session.removeAttribute("ListSBean");
              request.getRequestDispatcher(bean.getUrl()).forward(request,response);
          }

          return;
        }//end try block
        catch(Throwable t)
        {
           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           session.setAttribute("ListSBean", bean);
           request.getRequestDispatcher(bean.getUrl()).forward(request,response);
           return;
        }
  }

  //Clean up resources
  public void destroy()
  {
  }
}

package tccsol.util;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class ListServlet extends HttpServlet {
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       //catch all exceptions including runtime exeptions
       ListBean bean = null;
       HttpSession session = request.getSession();
       String cAct = "";
       try
       {
          bean = new ListBean();
          bean.setUrl(request.getParameter("url"));
          cAct = request.getParameter("callAction").trim();

          if (request.getParameter("valIds") != null) {
            bean.setId(request.getParameter("valIds").trim());
          }

          if (request.getParameter("valNms") != null) {
            bean.setNm(request.getParameter("valNms").trim());
          }

          if (request.getParameter("ftype") != null)
            bean.setType(request.getParameter("ftype").trim());

          if (request.getParameter("page") == null)
            bean.setPageVal(1);
          else if (request.getParameter("page").length() == 0)
            bean.setPageVal(1);
          else
            bean.setPageVal(Integer.parseInt(request.getParameter("page")));

          if (request.getParameter("backUrl") != null) {
            bean.setBackUrl(request.getParameter("backUrl").trim());
          }

          if (cAct.equals("Back"))
          {
              bean.setMode("  "); //Leaving spaces is inmportant for logic in use
              session.setAttribute("ListBean", bean);
              request.setAttribute("messages", bean.getMessages());

              if (bean.getBackUrl().trim().length() > 0)
                request.getRequestDispatcher(bean.getBackUrl()).forward(request,response);
              else
                request.getRequestDispatcher(bean.getUrl()).forward(request,response);

              return;
          }
          else
          {
              //NumItems stores the total number of employees
              long num = Long.parseLong(request.getParameter("num").trim());
              bean.getIds().clear();
              bean.getNames().clear();
              Vector vid = new Vector();
              Vector vnm = new Vector();
              String str = "";

              if (bean.getId().trim().length() > 0) {
                vid = Utility.splitString(bean.getId().trim(), ',');
              }

              if (bean.getNm().trim().length() > 0) {
                vnm = Utility.splitString(bean.getNm().trim(), ',');
              }

              for(long i=0;i<num;i++)
              {
                  if (request.getParameter("lst" + String.valueOf(i)) != null)
                  {
                      str = request.getParameter("lst" + String.valueOf(i));

                      byte flg=0;
                      for (int m=0; m<vid.size(); m++) {
                        if (str.substring(0, str.indexOf("|")).equalsIgnoreCase((String) vid.elementAt(m)))
                        {
                          //If the item is already present, need not add.
                          flg = 1;
                        }
                      }

                      if (flg == 0) {
                        //Will retrieve the selected Ids
                        vid.add(str.substring(0, str.indexOf("|")));
                        bean.setId(bean.getId().trim() + str.substring(0, str.indexOf("|")) + ",");

                        //Will retrieve the selected names
                        vnm.add(str.substring(str.indexOf("|") + 1, str.length()));
                        bean.setNm(bean.getNm().trim() + str.substring(str.indexOf("|") + 1, str.length()) + ",");
                      }
                  }
              }

              bean.setIds(vid);
              bean.setNames(vnm);
              bean.setMode("readonly");

              if  (cAct.equalsIgnoreCase("Next"))
              {
                bean.setSqlStat(request.getParameter("sqls").trim());
                bean.setType(request.getParameter("ftype").trim());
                String tls = request.getParameter("titles").trim();
                bean.setTitles(Utility.splitString(tls, '|'));
              }

              session.setAttribute("ListBean", bean);
              request.setAttribute("messages", bean.getMessages());

              if (cAct.equals("Add"))
                request.getRequestDispatcher(bean.getUrl()).forward(request,response);
              else if (cAct.equals("Next"))
                request.getRequestDispatcher("/util/List.jsp?page="+bean.getPageVal()).forward(request,response);
          }

          return;
        }//end try block
        catch(Throwable t)
        {
           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           session.setAttribute("ListBean", bean);
           request.getRequestDispatcher(bean.getUrl()).forward(request,response);
           return;
        }
  }

  //Clean up resources
  public void destroy()
  {
  }
}

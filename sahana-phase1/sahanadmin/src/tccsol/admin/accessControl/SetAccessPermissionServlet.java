package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class SetAccessPermissionServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       SetAccessPermissionBean bean = null;
       HttpSession session = null;
       AccessControl access = null;

       String url = "";
       String addUrl1 = "";
       String addUrl2 = "";
       String cAct = "";
       String login = "/admin/accessControl/Login1.jsp";
       try
       {
         //populating the bean with request data
          bean = new SetAccessPermissionBean();
          session = request.getSession();

          url = request.getParameter("url").trim();
          cAct = request.getParameter("callAction").trim();

          addUrl1 = "/admin/accessControl/SetAccessPermission1.jsp";
          addUrl2 = "/admin/accessControl/SetAccessPermission2.jsp";


          if (request.getParameter("roleName") != null)
            bean.setRoleName(request.getParameter("roleName").trim());

          if (request.getParameter("moduleId") != null)
            bean.setModuleId(request.getParameter("moduleId").trim());

          if (cAct.equals("Insert"))
          {
              bean.setMode(request.getParameter("mode").trim());

              bean.setRoleId(request.getParameter("roleId").trim());

              int numL = 0;
              int numM = 0;
              if (request.getParameter("numPerms") != null)
                  numL = Integer.parseInt(request.getParameter("numPerms"));
              if (request.getParameter("numMods") != null)
                  numM = Integer.parseInt(request.getParameter("numMods"));

              bean.getPermissions().clear();
              bean.getLevels().clear();
              bean.getModIds().clear();
              bean.getModules().clear();
              bean.getTypes().clear();

              for (int i=0; i<numL; i++)
                  bean.getLevels().add(request.getParameter("lvl"+i));

              String pr = "";
              for (int j=0; j<numM; j++)
              {
                pr = "";

                for (int i=0; i<bean.getLevels().size(); i++)
                {
                    if (request.getParameter("perm"+j+"-"+i) != null)   //Checked levels
                      pr = pr + request.getParameter("perm"+j+"-"+i) + "|";
                    else if (request.getParameter("p"+j+"-"+i) != null) //Unchecked but applicable levels
                      pr = pr + "N|";
                    else                                                //Not applicable levels
                      pr = pr + "-|";
                }

                bean.getPermissions().add(pr);
                bean.getModIds().add(request.getParameter("moduleId"+j));
                bean.getModules().add(request.getParameter("moduleName"+j));
                bean.getTypes().add(request.getParameter("type"+j));
              }
          }

       //Access Control implementation - START
        //Modulue Id 8 - Access Permissions
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
            session.setAttribute("SetAccessPermissionBean", bean);
            request.getRequestDispatcher(login).forward(request,response);
            return;
          }

          String ptype = "";
          String pname = "";
          byte btstat = 0;

          if (cAct.equals("Insert") || cAct.equals("Select From List") || cAct.equals("Set Access Permission"))
          {
            ptype = "ADD";
            pname = "Add";
            btstat = 1;
          }

          if (btstat == 1)
          {
            if (access.hasAccess(8, logb.getRoleId(), ptype, logb.getRoleName(), pname) == false)
            {
               bean.setMessages(access.getMessages());
               request.setAttribute("messages", bean.getMessages());
               session.setAttribute("SetAccessPermissionBean", bean);
               request.getRequestDispatcher(url).forward(request,response);
               return;
            }
          }
          //Access Control implementation - END


          if (cAct.equals("Set Access Permission"))
          {
               bean.getRoleData();

               request.setAttribute("messages", bean.getMessages());
               session.setAttribute("SetAccessPermissionBean", bean);
               if (bean.getMessages().size() > 0)
                 request.getRequestDispatcher(addUrl1).forward(request,response);
               else
                 request.getRequestDispatcher(addUrl2).forward(request,response);
          }


          if (cAct.equals("Insert"))
          {
             if (bean.insert() == false)
             {
                session.setAttribute("SetAccessPermissionBean", bean);
                request.setAttribute("messages", bean.getMessages());
                request.getRequestDispatcher(addUrl2).forward(request,response);
             }
             else {
                bean.setModuleId("");
                session.setAttribute("SetAccessPermissionBean", bean);
                request.setAttribute("messages", bean.getMessages());
                request.getRequestDispatcher(addUrl1).forward(request,response);
             }
           }


          if (cAct.equals("Select From List"))
          {
                if (request.getParameter("selMode") != null)
                  bean.setSelMode(request.getParameter("selMode").trim());
                else
                {
                  bean.getMessages().add("Pick the option you wish to select from the list");
                  request.setAttribute("messages", bean.getMessages());
                  session.setAttribute("SetAccessPermissionBean", bean);
                  request.getRequestDispatcher(addUrl1).forward(request,response);
                  return;
                }

                Vector v = new Vector();
                v.clear();

                if (bean.getSelMode().equalsIgnoreCase("R"))
                {
                  tccsol.util.ListSingleBean lsbean = new tccsol.util.ListSingleBean();
                  lsbean.setUrl(url);

                  v.add("Role Name");
                  v.add("Description");
                  lsbean.setTitles(v);
                  lsbean.setSqlStat("select ROLENAME, DESCRIPTION "
                    + "from TBLROLES order by ROLENAME");
                  lsbean.setType("USER ROLE");

                  session.setAttribute("SetAccessPermissionBean", bean);
                  session.setAttribute("ListSBean", lsbean);
                  request.setAttribute("messages", bean.getMessages());

                  request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
                }
                else
                {
                  tccsol.util.ListBean lbean = new tccsol.util.ListBean();
                  lbean.setUrl(url);
                  v.add("Module Id");
                  v.add("Module Name");
                  lbean.setTitles(v);
                  lbean.setSqlStat("select MODULEID, MODULENAME from "
                    + "TBLACCESSMODULES order by MODULEID");
                  lbean.setType("System Modules");

                  session.setAttribute("SetAccessPermissionBean", bean);
                  session.setAttribute("ListBean", lbean);
                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher("/util/List.jsp?page=1").forward(request,response);
                }
           }


           if (cAct.equals("Back"))
           {
               request.setAttribute("messages", bean.getMessages());
               session.setAttribute("SetAccessPermissionBean", bean);

               request.getRequestDispatcher(addUrl1).forward(request, response);
           }

           return;
        }//end try block
        catch(Throwable t)
        {
           String path = addUrl1;
           if (url.length() != 0)
              path = url;

           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           session.setAttribute("SetAccessPermissionBean", bean);
           request.getRequestDispatcher(path).forward(request,response);
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

package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;

public class UsersServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       UsersBean bean = null;
       HttpSession session = null;
       AccessControl access = null;

       String url = "";
       String addUrl = "";
       String updDelUrl = "";
       String updUrl = "";
       String delUrl = "";
       String cAct = "";

       try
       {
         //populating the bean with request data
          bean = new UsersBean();
          session = request.getSession();

          url = request.getParameter("url").trim();

          cAct = request.getParameter("callAction").trim();

          addUrl = "/admin/accessControl/Users.jsp";
          updDelUrl = "/admin/accessControl/UsersUpdDel.jsp";
          updUrl = "/admin/accessControl/UsersUpdate.jsp";
          delUrl = "/admin/accessControl/UsersDelete.jsp";



          if (url.equals(addUrl) || url.equals(updUrl))
          {
              if (request.getParameter("empId") != null)
                bean.setEmpId(request.getParameter("empId").trim().toUpperCase());
              else
                bean.setEmpId("");

              if (request.getParameter("userName") != null)
                bean.setUserName(request.getParameter("userName").trim());
              else
                bean.setUserName("");

              if (request.getParameter("pass1") != null)
                bean.setPass1(request.getParameter("pass1").trim());
              else
                bean.setPass1("");

              if (request.getParameter("pass2") != null)
                bean.setPass2(request.getParameter("pass2").trim());
              else
                bean.setPass2("");

              if (request.getParameter("lIds") != null)
              {
                if (request.getParameter("lIds").trim().length() > 0)
                {
                    bean.getRoleIds().clear();
                    bean.setRoleIds(tccsol.util.Utility.splitString(request.getParameter("lIds").trim(), '|'));
                }
              }

              if (request.getParameter("lNms") != null)
              {
                if (request.getParameter("lNms").trim().length() > 0)
                {
                    bean.getRoles().clear();
                    bean.setRoles(tccsol.util.Utility.splitString(request.getParameter("lNms").trim(), '|'));
                }
              }

              if (request.getParameter("rIds") != null)
              {
                if (request.getParameter("rIds").trim().length() > 0)
                {
                    bean.getSelRoleIds().clear();
                    bean.setSelRoleIds(tccsol.util.Utility.splitString(request.getParameter("rIds").trim(), '|'));
                }
              }

              if (request.getParameter("rNms") != null)
              {
                if (request.getParameter("rNms").trim().length() > 0)
                {
                    bean.getSelRoles().clear();
                    bean.setSelRoles(tccsol.util.Utility.splitString(request.getParameter("rNms").trim(), '|'));
                }
              }
          }

          if (url.equals(updUrl))
          {
              if (request.getParameter("oldRoles") != null)
                bean.setOldRole(request.getParameter("oldRoles").trim());
              else
                bean.setOldRole("");

              if (request.getParameter("oldUserName") != null)
                  bean.setOldUserName(request.getParameter("oldUserName").trim());
              else
                  bean.setOldUserName("");
          }

          if (url.equals(delUrl))
          {
              if (request.getParameter("oldUserName") != null)
                  bean.setOldUserName(request.getParameter("oldUserName").trim());
              else
                  bean.setOldUserName("");

              if (request.getParameter("rol") != null)
              {
                  bean.setRoles(tccsol.util.Utility.splitString(request.getParameter("rol").trim(), '|'));
                  bean.setRoleIds(tccsol.util.Utility.splitString(request.getParameter("rolId").trim(), '|'));
              }
          }

          if (url.equals(updDelUrl))
          {
              if (request.getParameter("uuserName") != null)
                bean.setUserName(request.getParameter("uuserName").trim());
          }



          //Access Control implementation - START
          //Modulue Id 1 - System Users
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
            session.setAttribute("UsersBean", bean);
            request.getRequestDispatcher(url).forward(request,response);
            return;
          }

          String ptype = "";
          String pname = "";
          byte btstat = 0;

          if (cAct.equals("Update") || cAct.equals("Update Record"))
          {
            ptype = "UPDATE";
            pname = "Update";
            btstat = 1;
          }
          if (cAct.equals("Insert") || (cAct.equals("Select From List") && url.equals(addUrl)))
          {
            ptype = "INSERT";
            pname = "Insert";
            btstat = 1;
          }
          if (cAct.equals("Delete Record") || cAct.equals("Delete"))
          {
            ptype = "DELETE";
            pname = "Delete";
            btstat = 1;
          }

          if (cAct.equals("Select From List") && url.equals(updDelUrl))
          {
              if (access.hasAccess(1, logb.getRoleId(), "UPDATE", logb.getRoleName(), "Update/Delete") == false && access.hasAccess(1, logb.getRoleId(), "DELETE", logb.getRoleName(), "Update/Delete") == false)
              {
                 bean.setMessages(access.getMessages());
                 request.setAttribute("messages", bean.getMessages());
                 session.setAttribute("UsersBean", bean);
                 request.getRequestDispatcher(url).forward(request,response);
                 return;
              }
          }
          else if (btstat == 1)
          {
              if (access.hasAccess(1, logb.getRoleId(), ptype, logb.getRoleName(), pname) == false)
              {
                 bean.setMessages(access.getMessages());
                 request.setAttribute("messages", bean.getMessages());
                 session.setAttribute("UsersBean", bean);
                 request.getRequestDispatcher(url).forward(request,response);
                 return;
              }
          }
          //Access Control implementation - END


          if (cAct.equals("Insert"))
          {
              Vector v = new Vector();
              v = bean.validate("I");
              if (bean.getMessages().size()>0)
              {
                  request.setAttribute("messages", bean.getMessages());
                  session.setAttribute("UsersBean", bean);
                  request.getRequestDispatcher(addUrl).forward(request,response);
                  return;
               }

               if (bean.insert() == false)
                  session.setAttribute("UsersBean", bean);
               else
                  session.removeAttribute("UsersBean");

               request.setAttribute("messages", bean.getMessages());
               request.getRequestDispatcher(addUrl).forward(request,response);
           }



          if (cAct.equals("Select From List"))
          {
            if(url.equals(updDelUrl))          //For Update/Delete page
            {
              tccsol.util.ListSingleBean lsbean = new tccsol.util.ListSingleBean();
              lsbean.setUrl(url);
              Vector v = new Vector();
              v.clear();

              v.add("User Name");
              v.add("Employee Id");
              v.add("Employee Name");
              lsbean.setTitles(v);
              lsbean.setSqlStat("select UserName, EMPID, concat(concat(FIRSTNAME, ' '),LASTNAME) "
                + "from TBLPERSONALINFORMATION p, TBLUSERS u where p.EMPNIC = u.EMPNIC "
                + "and EMPSTATUS = 'ACTIVE' order by UserName");
              lsbean.setType("Users");

              session.setAttribute("UsersBean", bean);
              session.setAttribute("ListSBean", lsbean);
              request.setAttribute("messages", bean.getMessages());

              request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
              return;
            }
          }


          //Update button in Update/Delete form
          if (cAct.equals("Update") || cAct.equals("Delete"))
          {
              if (bean.getUserName().length() == 0)
              {
                bean.getMessages().add("User Name not entered");
                request.setAttribute("messages", bean.getMessages());
                session.setAttribute("UsersBean", bean);
                request.getRequestDispatcher(updDelUrl).forward(request,response);
                return;
              }

              if (cAct.equals("Update"))
                bean.getUserData("U");
              else if (cAct.equals("Delete"))
                bean.getUserData("D");

              session.setAttribute("UsersBean", bean);

              if (bean.getMessages().size() > 0) {
                  request.setAttribute("messages", bean.getMessages());
                  session.setAttribute("UsersBean", bean);
                  request.getRequestDispatcher(updDelUrl).forward(request,response);
                  return;
              }

              if (cAct.equals("Update"))
                  request.getRequestDispatcher(updUrl).forward(request,response);
              else
                  request.getRequestDispatcher(delUrl).forward(request,response);

              return;
          }


           if (cAct.equals("Back"))
           {
               request.setAttribute("messages", bean.getMessages());
               request.removeAttribute("UsersBean");

               request.getRequestDispatcher(updDelUrl).forward(request, response);

               return;
           }



          //Update Record button in Update form
          if (cAct.equals("Update Record"))
          {
               Vector v = new Vector();
               v = bean.validate("U");
               if (bean.getMessages().size()>0)
               {
                  request.setAttribute("messages", bean.getMessages());
                  session.setAttribute("UsersBean", bean);
                  request.getRequestDispatcher(updUrl).forward(request,response);
                  return;
               }

               if (bean.update() == false) {
                  session.setAttribute("UsersBean", bean);
                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher(updUrl).forward(request,response);
               }
               else {
                  session.removeAttribute("UsersBean");
                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher(updDelUrl).forward(request,response);
               }
          }


          //'Delete Record' button in Delete form
          if (cAct.equals("Delete Record"))
          {
                  if (bean.delete() == true){
                    session.removeAttribute("UsersBean");
                    request.setAttribute("messages", bean.getMessages());
                    request.getRequestDispatcher(updDelUrl).forward(request,response);
                  }
                  else {
                    session.setAttribute("UsersBean", bean);
                    request.setAttribute("messages", bean.getMessages());
                    request.getRequestDispatcher(delUrl).forward(request,response);
                  }
          }

           return;
        }//end try block
        catch(Throwable t)
        {
           String path = addUrl;
           if (url.length() != 0)
              path = url;

           bean.getMessages().add("Error: " + t.getMessage());
           request.setAttribute("messages", bean.getMessages());
           request.setAttribute("UsersBean", bean);
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
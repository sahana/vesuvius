package tccsol.admin.accessControl;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;
import java.util.*;
import tccsol.admin.accessControl.AccessControl;
import tccsol.admin.accessControl.LoginBean;


public class RolesServlet extends HttpServlet
{
  private static final String CONTENT_TYPE = "text/html";

  //Initialize global variables
  public void init() throws ServletException {
  }

  //Process the HTTP Post request
  public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
  {
       //catch all exceptions including runtime exeptions
       RolesBean bean = null;
       HttpSession session = null;
       AccessControl access = null;

       String url = "";
       String addUrl = "";
       String updDelUrl = "";
       String updUrl = "";
       String delUrl = "";
       String arUrl = "";
       String cAct = "";
       String login = "/admin/accessControl/Login1.jsp";
       try
       {
         //populating the bean with request data
          bean = new RolesBean();
          session = request.getSession();

          url = request.getParameter("url").trim();

          //The submit buttin
          cAct = request.getParameter("callAction").trim();

          addUrl = "/admin/accessControl/Roles.jsp";
          updDelUrl = "/admin/accessControl/RolesUpdDel.jsp";
          updUrl = "/admin/accessControl/RolesUpdate.jsp";
          delUrl = "/admin/accessControl/RolesDelete.jsp";
          arUrl = "/admin/accessControl/RolesAddRemUsers.jsp";

          if (!url.equals(addUrl))
          {
            if (request.getParameter("roleId") != null)
              bean.setRoleId(request.getParameter("roleId").trim());
          }

          if (request.getParameter("roleName") != null)
            bean.setRoleName(request.getParameter("roleName").trim());

          if (request.getParameter("description") != null)
            bean.setDescription(request.getParameter("description").trim());

          if (request.getParameter("users") != null)
          {
             String us = request.getParameter("users").trim();
             if (us.length() > 0)
               bean.setUsers(tccsol.util.Utility.splitString(us, ','));
          }

          if (request.getParameter("modeVal") != null)
            bean.setModeVal(request.getParameter("modeVal").trim());


          //Access Control implementation - START
          //Modulue Id 7 - User Roles
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
            if (url.equals(arUrl))
              session.setAttribute("RolesBean", bean);
            else
              request.setAttribute("RolesBean", bean);
            request.getRequestDispatcher(login).forward(request,response);
            return;
          }

          String ptype = "";
          String pname = "";
          byte btstat = 0;

          if (cAct.equals("Update") || cAct.equals("Update Record"))
          {
            ptype = "EDIT";
            pname = "Edit";
            btstat = 1;
          }
          if (cAct.equals("Insert") || (cAct.equals("Select From List") && (url.equals(arUrl))) || cAct.equals("Add Users") || cAct.equals("Remove Users") || cAct.equals("Clear Selection"))
          {
            ptype = "ADD";
            pname = "Add";
            btstat = 1;
          }
          if (cAct.equals("Delete Record") || cAct.equals("Delete"))
          {
            ptype = "DELETE";
            pname = "Delete";
            btstat = 1;
          }

          if (cAct.equals("Select From List") && (!url.equals(arUrl)))
          {
              if (access.hasAccess(7, logb.getRoleId(),"EDIT" , logb.getRoleName(), "Edit/Delete") == false && access.hasAccess(2, logb.getRoleId(), "DELETE", logb.getRoleName(), "Update/Delete") == false)
              {
                 bean.setMessages(access.getMessages());
                 request.setAttribute("messages", bean.getMessages());
                 if (url.equals(arUrl))
                    session.setAttribute("RolesBean", bean);
                 else
                    request.setAttribute("RolesBean", bean);
                 request.getRequestDispatcher(url).forward(request,response);
                 return;
              }
          }
          else if (btstat == 1)
          {
              if (access.hasAccess(7, logb.getRoleId(), ptype, logb.getRoleName(), pname) == false)
              {
                 bean.setMessages(access.getMessages());
                 request.setAttribute("messages", bean.getMessages());
                 if (url.equals(arUrl))
                   session.setAttribute("RolesBean", bean);
                 else
                   request.setAttribute("RolesBean", bean);
                 request.getRequestDispatcher(url).forward(request,response);
                 return;
              }
          }
          //Access Control implementation - END


          if (cAct.equals("Insert"))
          {
              //check for validation errors and set it request object
              //if validation fails sent it back to the source page
              Vector v = new Vector();
              v = bean.validate("I");
              if (bean.getMessages().size()>0)
              {
                  request.setAttribute("messages", bean.getMessages());
                  request.setAttribute("RolesBean", bean);
                  request.getRequestDispatcher(addUrl).forward(request,response);
                  return;
               }

               if (bean.insert() == false)
                  request.setAttribute("RolesBean", bean);

               request.setAttribute("messages", bean.getMessages());
               request.getRequestDispatcher(addUrl).forward(request,response);
           }


          //Update or Delete button in Update/Delete form
          if (cAct.equals("Update") || cAct.equals("Delete"))
          {
              bean.getRoleData(bean.getRoleName());

              request.setAttribute("RolesBean", bean);
              request.setAttribute("messages", bean.getMessages());

              if (bean.getMessages().size() > 0)
                request.getRequestDispatcher(updDelUrl).forward(request,response);
              else
              {
                if (cAct.equals("Delete"))
                  request.getRequestDispatcher(delUrl).forward(request,response);
                else
                  request.getRequestDispatcher(updUrl).forward(request,response);
              }
          }


          if (cAct.equals("Select From List"))
          {
              bean.getUsers().clear();
              tccsol.util.ListSingleBean lsbean = new tccsol.util.ListSingleBean();
              lsbean.setUrl(url);
              Vector v = new Vector();

              v.clear();
              v.add("Role Name");
              v.add("Description");
              lsbean.setTitles(v);
              lsbean.setSqlStat("select ROLENAME, DESCRIPTION "
                + "from TBLROLES order by ROLENAME");
              lsbean.setType("USER ROLE");

              if (url.equals(arUrl))
                session.setAttribute("RolesBean", bean);
              else
                request.setAttribute("RolesBean", bean);

              session.setAttribute("ListSBean", lsbean);
              request.setAttribute("messages", bean.getMessages());

              request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
          }


          if (cAct.equals("Clear Selection"))
          {
              bean.getUsers().clear();
              bean.setModeVal("");
              bean.setRoleId("");
              session.setAttribute("RolesBean", bean);
              request.getRequestDispatcher(arUrl).forward(request,response);
              return;
          }

          if (cAct.equals("Add Users"))
          {
              if (bean.getUsers().size() == 0)
              {
                  bean.setModeVal("A");
                  if (bean.getRoleId().trim().length() == 0)
                  {
                      if (bean.getSelectedRoleId() == false)
                      {
                        session.setAttribute("RolesBean", bean);
                        request.setAttribute("messages", bean.getMessages());
                        request.getRequestDispatcher(arUrl).forward(request,response);
                        return;
                      }
                  }

                  tccsol.util.ListBean lbean = new tccsol.util.ListBean();
                  lbean.setUrl(url);
                  Vector v = new Vector();
                  v.add("User Name");
                  v.add("Organization Name");
                  lbean.setTitles(v);
                  String sql= " select u.username,o.orgname from user u,organization o "
                  + " where u.orgcode=o.orgcode and UPPER(u.username) not in (select UPPER(username) from TBLUSERROLES "
                  + "where ROLEID = " + bean.getRoleId() + ") order by u.username ";
                  lbean.setSqlStat(sql);
                  lbean.setType("Users (Not having Role: "+bean.getRoleName()+")");

                  session.setAttribute("RolesBean", bean);
                  session.setAttribute("ListBean", lbean);
                  request.setAttribute("messages", bean.getMessages());

                  request.getRequestDispatcher("/util/List.jsp?page=1").forward(request,response);
              }
              else
              {
                  if (bean.getModeVal().equalsIgnoreCase("R"))
                  {
                      bean.getMessages().add("Users have bean selected for 'Removal' from Role. "
                        + "Click the 'Remove Users' button. <br>(To add users, clear the "
                        + "selected users and Start from the beggining)");

                      session.setAttribute("RolesBean", bean);
                  }
                  else
                  {
                      if (bean.addUsers() == false)
                        session.setAttribute("RolesBean", bean);
                      else
                        session.removeAttribute("RolesBean");
                  }

                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher(arUrl).forward(request,response);
              }
           }


           if (cAct.equals("Remove Users"))
           {
              if (bean.getUsers().size() == 0)
              {
                  bean.setModeVal("R");
                  if (bean.getRoleId().trim().length() == 0)
                  {
                      if (bean.getSelectedRoleId() == false)
                      {
                        session.setAttribute("RolesBean", bean);
                        request.setAttribute("messages", bean.getMessages());
                        request.getRequestDispatcher(arUrl).forward(request,response);
                        return;
                      }
                  }

                  tccsol.util.ListBean lbean = new tccsol.util.ListBean();
                  lbean.setUrl(url);
                  Vector v = new Vector();
                  v.add("User Name");
                  v.add("Organization Name");

                  lbean.setTitles(v);
                  String sql= " select u.username,o.orgname from user u,organization o "
                  + " where u.orgcode=o.orgcode and upper(u.username) in  (select upper(username) from TBLUSERROLES "
                  + "where ROLEID = " + bean.getRoleId() + ") order by u.username ";
                  lbean.setSqlStat(sql);


                  lbean.setType("Users (Having Role: "+bean.getRoleName()+")");

                  session.setAttribute("RolesBean", bean);
                  session.setAttribute("ListBean", lbean);
                  request.setAttribute("messages", bean.getMessages());

                  request.getRequestDispatcher("/util/List.jsp?page=1").forward(request,response);
              }
              else
              {
                  if (bean.getModeVal().equalsIgnoreCase("A"))
                  {
                      bean.getMessages().add("Users have bean selected to 'Add' to the Role. "
                        + "Click the 'Add Users' button. <br>(To remove users, clear the "
                        + "selected users and Start from the beggining)");

                      session.setAttribute("RolesBean", bean);
                  }
                  else
                  {
                      if (bean.removeUsers() == false)
                        session.setAttribute("RolesBean", bean);
                      else
                        session.removeAttribute("RolesBean");
                  }

                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher(arUrl).forward(request,response);
              }
           }


           if (cAct.equals("Back"))
           {
               request.setAttribute("messages", bean.getMessages());
               request.setAttribute("RolesBean", bean);

               request.getRequestDispatcher(updDelUrl).forward(request, response);
           }

          //Update Record button in Update form
          if (cAct.equals("Update Record"))
          {
                 Vector v = new Vector();
                 v = bean.validate("U");
                 if (bean.getMessages().size()>0)
                 {
                    request.setAttribute("messages", bean.getMessages());
                    request.setAttribute("RolesBean", bean);
                    request.getRequestDispatcher(updUrl).forward(request,response);
                    return;
                 }

                 if (bean.update() == false) {
                    request.setAttribute("RolesBean", bean);
                    request.setAttribute("messages", bean.getMessages());
                    request.getRequestDispatcher(updUrl).forward(request,response);
                 }
                 else {
                    request.setAttribute("messages", bean.getMessages());
                    request.getRequestDispatcher(updDelUrl).forward(request,response);
                 }
          }


          //'Delete Record' button in Delete form
          if (cAct.equals("Delete Record"))
          {
                if (bean.delete() == true){
                  request.setAttribute("messages", bean.getMessages());
                  request.getRequestDispatcher(updDelUrl).forward(request,response);
                }
                else {
                  request.setAttribute("RolesBean", bean);
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
           if (bean != null)
             request.setAttribute("RolesBean", bean);
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

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
       String login = "/admin/accessControl/Login1.jsp";
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
          delUrl = "/admin/accessControl/UsersUpdate.jsp";




          if (url.equals(addUrl) || url.equals(updUrl))
          {


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

              if (request.getParameter("roleId") != null)
                bean.setRoleId(request.getParameter("roleId").trim());
              else
                bean.setRoleId("");

            if (request.getParameter("orgId") != null)
               bean.setOrgId(request.getParameter("orgId").trim());
             else
               bean.setOrgId("");



            }


          if (url.equals(delUrl))
          {
              if (request.getParameter("userName") != null)
                  bean.setUserName(request.getParameter("userName").trim());
              else
                  bean.setUserName("");


          }

          if (url.equals(updDelUrl))
          {
              if (request.getParameter("uuserName") != null)
                bean.setUserName(request.getParameter("uuserName").trim());
          }



        //Access Control implementation - START
          //Modulue Id 6 - System Users
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
          if (cAct.equals("Insert") || (cAct.equals("Select From List") && url.equals(addUrl)))
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

          if (cAct.equals("Select From List") && url.equals(updDelUrl))
          {
              if (access.hasAccess(6, logb.getRoleId(), "EDIT", logb.getRoleName(), "Edit/Delete") == false && access.hasAccess(1, logb.getRoleId(), "DELETE", logb.getRoleName(), "Update/Delete") == false)
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
              if (access.hasAccess(6, logb.getRoleId(), ptype, logb.getRoleName(), pname) == false)
              {
                 bean.setMessages(access.getMessages());
                 request.setAttribute("messages", bean.getMessages());
                 session.setAttribute("UsersBean", bean);
                 request.getRequestDispatcher(url).forward(request,response);
                 return;
              }
          }
          //Access Control implementation - END

if (cAct.equals("Select Role"))
          {



                tccsol.util.ListSingleBean lbean = new tccsol.util.ListSingleBean();
                lbean.setUrl(url);

                Vector v = new Vector();
                v.add("Role Id");
                v.add("Role Name");
                v.add("Role Description");
                lbean.setTitles(v);
                String sql= "select roleid,rolename,description from TBLROLES order by rolename";
                lbean.setSqlStat(sql);

                lbean.setType("Roles");

                session.setAttribute("UsersBean", bean);
                session.setAttribute("ListSBean", lbean);
                request.setAttribute("messages", bean.getMessages());
                request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
                return;

          }else if(cAct.equals("Select Organization")){
            tccsol.util.ListSingleBean lbean = new tccsol.util.ListSingleBean();
                lbean.setUrl(url);
                Vector v = new Vector();
                v.add("Organization Id");
                v.add("Organization Name");

                lbean.setTitles(v);
                String sql= "select orgcode,orgname from organization order by orgname";
                lbean.setSqlStat(sql);
                lbean.setType("Organizations");
                session.setAttribute("UsersBean", bean);
                session.setAttribute("ListSBean", lbean);
                request.setAttribute("messages", bean.getMessages());
                request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
                return;


          }else if (cAct.equals("Select User")) {
            tccsol.util.ListSingleBean lbean = new tccsol.util.ListSingleBean();
            lbean.setUrl(url);
            Vector v = new Vector();
            v.add("User Name");
            v.add("Organization Name");

            lbean.setTitles(v);
            String sql= " select u.username,o.orgname from user u,organization o "
            + " where u.orgcode=o.orgcode "
            +" order by u.username ";
            lbean.setSqlStat(sql);
           lbean.setType("Users ");

            session.setAttribute("UsersBean", bean);
            session.setAttribute("ListSBean", lbean);
            request.setAttribute("messages", bean.getMessages());
            request.getRequestDispatcher("/util/ListSingle.jsp?page=1").forward(request,response);
            return;
          }

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

              bean.getUserData("");
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

<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="RolesBean" scope="session" class="tccsol.admin.accessControl.RolesBean"/>
<jsp:useBean id="ListSBean" scope="session" class="tccsol.util.ListSingleBean" />
<jsp:useBean id="ListBean" scope="session" class="tccsol.util.ListBean" />

<html>
<head>
<title>Access Control - Admin</title>
</head>
<body bgcolor="#FFFFFF">
<%
//Access Control implementation - START
//Modulue Id 8 - System Users
          tccsol.admin.accessControl.LoginBean logb = (tccsol.admin.accessControl.LoginBean) session.getAttribute("LoginBean");
	   boolean isVisible =false;
          byte st = 0;
          if (logb == null)
            st = 1;
          else {
            if (logb.getRoleId() == 0)
                st = 1;
          }
          if (st == 1){
            java.util.Vector v = new java.util.Vector();
            v.add("Please login before you proceed");
            request.setAttribute("messages", v);
            request.getRequestDispatcher("/admin/accessControl/Login1.jsp").forward(request,response);
            return;
          }
	 else{
          	tccsol.admin.accessControl.AccessControl access = new tccsol.admin.accessControl.AccessControl();

          	if (!access.hasAccess(7, logb.getRoleId(), "PAGE", logb.getRoleName(), "Page"))
              {
                 request.setAttribute("messages", access.getMessages());

               }
		else{
		isVisible = true;
		}
	 }

if (request.getAttribute("messages")!=null)
{
    java.util.Vector v = (java.util.Vector) request.getAttribute("messages");
    if (v.size() > 0)
    {
    for(int i=0;i<v.size();i++)
    {
%><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
    <%=v.elementAt(i)%></font></li>
<%
    }//end of for loop
    }
}//end of if
if(isVisible){
%>
<a href="/sahanaadmin/admin/accessControl/welcome.jsp">Home</a>
<form action="/sahanaadmin/rolesservlet" method="post" name="frmAddRemUsers">
  <br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
  System Roles - Add/Remove Users</u></strong></font></p>

  <table width="77%" border="0" align="center" cellpadding="0" cellspacing="3">
    <tr>
      <td colspan="3" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td width="30%" valign="top"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Role Name: </font></div></td>
      <td width="30%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <% if (ListSBean.getId() != null) {
            if (ListSBean.getId().trim().length() > 0) {
                RolesBean.setRoleName(ListSBean.getId());
                session.removeAttribute("ListSBean");
            }
         }
      %>
        <input name="roleName" size="25" <% if (RolesBean.getUsers().size() > 0) {
          out.print("readonly"); }%> type="text" id="roleName" value="<%=RolesBean.getRoleName()%>">
        <input name="roleId" size="25" type="hidden" id="roleId" value="<%=RolesBean.getRoleId()%>">
        </font></td>
      <td width="40%" valign="top">
     <input name="callAction" type="submit" id="callAction" value="Select From List"></td>
    </tr>
    <%
      if (ListBean.getIds() != null) {
          if (ListBean.getIds().size() > 0) {
              RolesBean.setUsers(ListBean.getIds());
              session.removeAttribute("ListBean");
          }
      }

    if (RolesBean.getUsers().size() > 0)
    {
        String users = "";
        for (int i=0; i<RolesBean.getUsers().size(); i++)
        {
          if (i == 0)
            users = (String)RolesBean.getUsers().elementAt(i);
          else
            users = users + ", " + RolesBean.getUsers().elementAt(i);
        }
    %>
    <tr>
      <td valign="top"> <div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Users <% if (RolesBean.getModeVal().equalsIgnoreCase("A")) {
            out.print("to be Added");
          } else if (RolesBean.getModeVal().equalsIgnoreCase("R")) {
            out.print("to be Removed"); } %>: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <textarea name="users" id="users" rows="3" readonly cols="40"><%=users%></textarea>
        </font></td>
    </tr>
    <tr>
      <td colspan="3" valign="top">&nbsp;</td>
    </tr>
    <% if (RolesBean.getModeVal().trim().length() > 0) {   %>
    <tr>
      <td colspan="3" valign="top"><ul><li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Click the <% if (RolesBean.getModeVal().equalsIgnoreCase("A")) {
            out.print("'Add Users'");
          } else if (RolesBean.getModeVal().equalsIgnoreCase("R")) {
            out.print("'Remove Users'"); } %> button once more, to <% if (RolesBean.getModeVal().equalsIgnoreCase("A")) {
            out.print("add the users to");
          } else if (RolesBean.getModeVal().equalsIgnoreCase("R")) {
            out.print("remove the users from"); } %> the selected role.
      </font></li>
      <li><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Click the 'Clear Selection' button to start from the beggining</font></li>
      </ul></td>
    </tr>
    <% }
    }%>
    <tr>
      <td colspan="3" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3" valign="top"><div align="center"><br>
        <% if (RolesBean.getUsers().size() > 0) { %>
          <input name="callAction" type="submit" id="callAction" value="Clear Selection">
        <% } %>
          <input name="callAction" type="submit" id="callAction" value="Add Users">
          <input name="callAction" type="submit" id="callAction" value="Remove Users">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          <input type="hidden" name="modeVal" id="modeVal" value="<%=RolesBean.getModeVal()%>">
        </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%}
  if (RolesBean != null)
    RolesBean.closeDBConn();

  session.removeAttribute("ListSBean");
  session.removeAttribute("ListBean");
%>
</body>
</html>

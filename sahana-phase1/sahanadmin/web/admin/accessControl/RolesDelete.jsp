<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="RolesBean" scope="request" class="tccsol.admin.accessControl.RolesBean"/>

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
<form action="/sahanaadmin/rolesservlet" method="post" name="frmRolesDelete">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
    User Roles - Delete</u></strong></font> </p>
  <p align="left"> <font size="2" face="Verdana, Arial, Helvetica, sans-serif">Details
    of record to be deleted ... </font> </p>
  <table width="87%" border="0" align="center" cellpadding="0" cellspacing="3">
    <tr>
      <td width="40%" valign="top"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <strong>Role Id:</strong> </font></div></td>
      <td width="2" >&nbsp;</td>
      <td width="60%" ><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=RolesBean.getRoleId()%>
        <input name="roleId" type="hidden" id="roleId" value="<%=RolesBean.getRoleId()%>">
        </font></td>
    </tr>
    <tr>
      <td valign="top"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <strong>Role Name:</strong> </font></div></td>
      <td width="2" >&nbsp;</td>
      <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=RolesBean.getRoleName()%>
        <input name="roleName" type="hidden" id="roleName" value="<%=RolesBean.getRoleName()%>">
        </font></td>
    </tr>
    <tr>
      <td valign="top"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <strong>Description: </strong> </font></div></td>
      <td width="2" >&nbsp;</td>
      <td ><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=RolesBean.getDescription()%>
        <input name="description" type="hidden" id="description" value="<%=RolesBean.getDescription()%>">
        </font></td>
    </tr>
    <tr>
      <td colspan="3" valign="top"><div align="center"> <br>
          <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Delete Record">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          </font> </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%}
if (RolesBean != null)
  RolesBean.closeDBConn();
%>
</body>
</html>

<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="RolesBean" scope="request" class="tccsol.admin.accessControl.RolesBean"/>

<html>
<head>
<title>Access Control - Admin</title>
</head>
<body bgcolor="#FFFFFF">
<%
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
%>

<form action="/hris/rolesservlet" name="frmRolesUpdate" method="post">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>User Roles - Update</u></strong></font></p>
    <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      The fields marked with * cannot be updated. Replace the old value with the new one to update the rest.</font></td>
    </tr>
    <tr>
      <td colspan="3">&nbsp;</td>
    </tr>
    <tr>
      <td width="45%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Role Id: </font></div></td>
      <td width="55%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" readonly name="roleId" id="roleId" value="<%=RolesBean.getRoleId()%>">&nbsp;*
        </font></td>
    </tr>
    <tr>
      <td><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      Role Name: </font></div></td>
      <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" name="roleName" id="roleName" value="<%=RolesBean.getRoleName()%>">
        </font></td>
    </tr>
    <tr>
      <td><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Description:</font></div></td>
      <td><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" size="40" name="description" id="description" value="<%=RolesBean.getDescription()%>">
        </font></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Update Record">
          <input name="Reset" type="reset" id="Reset" value="Reset">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
if (RolesBean != null)
  RolesBean.closeDBConn();
%>
</body>
</html>
<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="AccessPermissionBean" scope="session" class="tccsol.admin.accessControl.AccessPermissionBean"/>

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

<form action="/hris/accesspermissionservlet" name="frmAccessPerm2" method="post">
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>System Access Permission</u></strong></font></p>
    <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <tr>
      <td width="46%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Module Id: </font></div></td>
      <td width="54%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=AccessPermissionBean.getModuleId()%>
        <input type="hidden" name="moduleId" id="moduleId" value="<%=AccessPermissionBean.getModuleId()%>">
        </font></td>
    </tr>
    <tr>
      <td width="46%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Module Name: </font></div></td>
      <td width="54%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=AccessPermissionBean.getModuleName()%>
        <input type="hidden" name="moduleName" id="moduleName" value="<%=AccessPermissionBean.getModuleName()%>">
        </font></td>
    </tr>
    <tr>
      <td width="46%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          User Role Name: </font></div></td>
      <td width="54%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <%=AccessPermissionBean.getRoleName()%>
        <input type="hidden" name="roleName" id="roleName" value="<%=AccessPermissionBean.getRoleName()%>">
        <input type="hidden" name="roleId" id="roleId" value="<%=AccessPermissionBean.getRoleId()%>">
        </font></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <% if (AccessPermissionBean.getLevels().size() > 0) {  %>
    <tr>
      <td colspan="2"> <hr noshade color="#000000"> </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        [ If the role does not have permission for a particular Access Level Leave
        it unchecked ]</font></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2">
          <table width="50%" border="1" align="center" cellpadding="3" cellspacing="0">
          <tr> <%
          //To spread the column width evenly
          int cl = 100 / AccessPermissionBean.getLevels().size();

          for (int i=0; i<AccessPermissionBean.getLevels().size(); i++) {
            %><td width="<%=cl%>"><div align="center"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
            <%=AccessPermissionBean.getLevels().elementAt(i)%>
            <input type="hidden" name="lvl<%=i%>" id="lvl<%=i%>" value="<%=AccessPermissionBean.getLevels().elementAt(i)%>">
            </font></strong></div></td>
          <% } %>
          </tr>
          <tr>
            <td colspan="<%=AccessPermissionBean.getLevels().size()%>">
              <div align="center">
                <table width="100%" border="0" cellspacing="3" cellpadding="0">
                <tr> <%
                if (AccessPermissionBean.getMode().equalsIgnoreCase("U")) {
                for (int i=0; i<AccessPermissionBean.getPermissions().size(); i++) {
                  %><td width="<%=cl%>"><div align="center"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
                  <input type="checkbox" value="Y" name="perm<%=i%>" id="perm<%=i%>"
                   <% String p = (String) AccessPermissionBean.getPermissions().elementAt(i);
                   if (p.equalsIgnoreCase("Y")) {
                      out.print("checked");
                   } %>> </font></strong></div></td>
                <% }
                } else {
                for (int i=0; i<AccessPermissionBean.getLevels().size(); i++) {
                  %><td width="<%=cl%>"><div align="center"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
                  <input type="checkbox" value="Y" name="perm<%=i%>" id="perm<%=i%>"> </font></strong></div></td>
                <% }
                }
                %>
                </tr>
                </table></div>
              </td>
          </tr>
        </table>
      </td>
    </tr>
  <%  } %>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Insert">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          <input type="hidden" name="numPerms" id="numPerms" value="<%=AccessPermissionBean.getLevels().size()%>">
          <input type="hidden" name="mode" id="mode" value="<%=AccessPermissionBean.getMode()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
  if (AccessPermissionBean != null)
    AccessPermissionBean.closeDBConn();
%>
</body>
</html>
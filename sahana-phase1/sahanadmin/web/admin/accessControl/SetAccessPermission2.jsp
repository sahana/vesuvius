<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="SetAccessPermissionBean" scope="session" class="tccsol.admin.accessControl.SetAccessPermissionBean"/>

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

          	if (!access.hasAccess(8, logb.getRoleId(), "PAGE", logb.getRoleName(), "Page"))
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
<form action="/sahanaadmin/setaccesspermissionservlet" name="frmAccessPerm2" method="post">
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>System Access Permission</u></strong></font></p>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  User Role Name: <%=SetAccessPermissionBean.getRoleName()%></font></p>
    <input type="hidden" name="roleName" id="roleName" value="<%=SetAccessPermissionBean.getRoleName()%>">
    <input type="hidden" name="roleId" id="roleId" value="<%=SetAccessPermissionBean.getRoleId()%>">
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <% if (SetAccessPermissionBean.getLevels().size() > 0) {  %>
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
       <tr> <td width="2%">
       <strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
       Module Id</font></strong></td>
       <td width="13%"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
       Module Name</font></strong>
       </td>
          <%
          String p = "";
          java.util.Vector vp = new java.util.Vector();
          //To spread the column width evenly
          int cl = 85 / SetAccessPermissionBean.getLevels().size();

          for (int i=0; i<SetAccessPermissionBean.getLevels().size(); i++) {
            %><td width="<%=cl%>"><div align="center"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
            <% p = (String)SetAccessPermissionBean.getLevels().elementAt(i);
               p = p.replace('_', ' ');
               out.print(p);
            %>
            <input type="hidden" name="lvl<%=i%>" id="lvl<%=i%>" value="<%=SetAccessPermissionBean.getLevels().elementAt(i)%>">
            </font></strong></div></td>
          <% } %>
       </tr>
       <% /* End of heading row */ %>

       <% //rows of permission for each module
       int num = 0;
         for (int j=0; j<SetAccessPermissionBean.getModIds().size(); j++)
         {
         num = 0;
         %>
       <tr><td> <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
       <%=SetAccessPermissionBean.getModIds().elementAt(j)%></font>
        <input type="hidden" name="moduleId<%=j%>" id="moduleId<%=j%>" value="<%=SetAccessPermissionBean.getModIds().elementAt(j)%>">
       </td> <td> <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
       <%=SetAccessPermissionBean.getModules().elementAt(j)%></font>
       <input type="hidden" name="moduleName<%=j%>" id="moduleName<%=j%>" value="<%=SetAccessPermissionBean.getModules().elementAt(j)%>">
       <input type="hidden" name="type<%=j%>" id="type<%=j%>" value="<%=SetAccessPermissionBean.getTypes().elementAt(j)%>">
      <% vp.clear();
       vp = tccsol.util.Utility.splitString((String)SetAccessPermissionBean.getPermissions().elementAt(j), '|');
         for (int i=0; i<vp.size(); i++)
         { %>
         <td width="<%=cl%>%"><div align="center"><strong>
         <font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <% p = (String) vp.elementAt(i);
          if (p.equalsIgnoreCase("-")) {
            out.print(p);
          }
          else {
          num++;
          %>
         <input type="checkbox" value="Y" name="perm<%=j%>-<%=i%>" id="perm<%=j%>-<%=i%>"
           <% p = (String) vp.elementAt(i);
           if (p.equalsIgnoreCase("Y")) {
              out.print("checked");
           } %>>
         <input type="hidden" value="chk" name="p<%=j%>-<%=i%>" id="p<%=j%>-<%=i%>">
         <% } %>
           </font></strong></div></td>
        <% } %>
      </tr>
  <%  } %>
      </table>
     </td> </tr>
    <% } %>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan=2><div align="Left"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      The cells marked with '-' indicate access levels that are not
      applicable to the particular module. </font></div><br></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Insert">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          <input type="hidden" name="numPerms" id="numPerms" value="<%=SetAccessPermissionBean.getLevels().size()%>">
          <input type="hidden" name="numMods" id="numMods" value="<%=SetAccessPermissionBean.getModIds().size()%>">
          <input type="hidden" name="mode" id="mode" value="<%=SetAccessPermissionBean.getMode()%>">
          <input type="hidden" name="moduleId" id="moduleId" value="<%=SetAccessPermissionBean.getModuleId()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%}
  if (SetAccessPermissionBean != null)
    SetAccessPermissionBean.closeDBConn();
%>
</body>
</html>

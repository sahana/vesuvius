<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="UsersBean" scope="session" class="tccsol.admin.accessControl.UsersBean"/>
<jsp:useBean id="ListSBean" scope="session" class="tccsol.util.ListSingleBean"/>
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

          	if (!access.hasAccess(6, logb.getRoleId(), "PAGE", logb.getRoleName(), "Page"))
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

if(ListSBean.getId().length()>0){
if("Organizations".equals(ListSBean.getType())){
	UsersBean.setOrgId(ListSBean.getId());

}else if("Roles".equals(ListSBean.getType())){
  UsersBean.setRoleId(ListSBean.getId());
}
}
%>
<a href="/sahanaadmin/admin/accessControl/welcome.jsp">Home</a>
<form action="/sahanaadmin/usersservlet" name="frmUsers" method="post">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>System Users</u></strong></font></p>
    <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          User Name: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" name="userName" id="userName" value="<%=UsersBean.getUserName()%>">
        </font></td>
    </tr>
        <tr>
      <td align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Role</font></font></td>
      <td> <input type="text" name="roleId" value="<%=UsersBean.getRoleId()%>"></td>
      <td align="left">
        <input type="submit" name="callAction" value="Select Role"/>
      </td>
    </tr>

   <td align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Origanization</font></td>
      <td> <input type="text" name="orgId" value="<%=UsersBean.getOrgId()%>"></td>
      <td align="left"><input type="submit" name="callAction" value="Select Organization"/>
      </td>
   <tr>
      <td colspan="3">

</td>
    </tr>

    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass1" id="pass1" value="">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Confirm Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass2" id="pass2" value="">
        </font></td>
    </tr>
    <tr>
      <td colspan="3">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">

      </font></td>
    </tr>
    <tr>
      <td colspan="3">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Insert" >
          <input name="Reset" type="reset" id="Reset" value="Reset">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
}
if (UsersBean != null)
  UsersBean.closeDBConn();

%>
</body>
</html>

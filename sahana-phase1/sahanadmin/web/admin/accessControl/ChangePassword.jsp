<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="ChangePasswordBean" scope="request" class="tccsol.admin.accessControl.ChangePasswordBean"/>
<jsp:useBean id="LoginBean" scope="session" class="tccsol.admin.accessControl.LoginBean"/>

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
    <%=v.elementAt(i)%>
    </font></li>
<%
    }//end of for loop
    }
}//end of if
%>
<a href="/sahanaadmin/admin/accessControl/welcome.jsp">Home</a>
<form action="/sahanaadmin/changepasswordservlet" name="frmChangePass" method="post">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>Change Password</u></strong></font></p>
    <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
  <%
     ChangePasswordBean.setUserName(LoginBean.getUserName());
     %>

    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          User Name: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="text" name="userName" id="userName" value="<%=ChangePasswordBean.getUserName()%>">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
         Current Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="curPass" id="curPass" value="">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
         New Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass1" id="pass1" value="">
        </font></td>
    </tr>
    <tr>
      <td width="47%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Confirm New Password: </font></div></td>
      <td colspan="2"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input type="password" name="pass2" id="pass2" value="">
        </font></td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td colspan="2">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="3"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Change Password">
          <input name="Reset" type="reset" id="Reset" value="Reset">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
  <%
     if (ChangePasswordBean != null)
        ChangePasswordBean.closeDBConn();
  %>
</body>
</html>

<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
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
    <%=v.elementAt(i)%></font></li>
<%
    }//end of for loop
    }
}//end of if
%>

<form action="/sahanaadmin/loginservlet" method="post" name="frmLogin">
  <br><br>

  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
    </u></strong></font></p>

  <table width="45%" border="0" align="left" cellpadding="0" cellspacing="3">
    <tr>
      <td colspan="2" valign="top"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>Admin Login</u></strong></font></div></td>
    </tr>
    <tr>
      <td colspan="2" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td width="41%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          User Name: </font></div></td>
      <td width="59%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input name="userName" type="text" id="userName" value="<%=LoginBean.getUserName()%>">
        </font></td>
    </tr>
    <tr>
      <td> <div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Password: </font></div></td>
      <td width="59%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <input name="passwd" type="password" id="passwd">
        </font></td>
    </tr>
    <tr>
      <td colspan="2" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2" valign="top"><div align="center">
          <input name="callAction" type="submit" id="callAction" value="Login">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
        </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
</body>
</html>

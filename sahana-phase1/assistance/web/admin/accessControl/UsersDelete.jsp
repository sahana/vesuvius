<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="UsersBean" scope="session" class="tccsol.admin.accessControl.UsersBean"/>

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

<form action="/hris/usersservlet" name="frmUsersDel" method="post">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
  <strong><u>System Users - Delete</u></strong></font></p>
    <br>
  <p align="left"> <font size="2" face="Verdana, Arial, Helvetica, sans-serif">Details
    of record to be deleted ... </font> </p>
  <br>
  <table width="94%" border="0" cellspacing="4" cellpadding="0">
    <tr>
      <td width="46%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <strong>User Name:</strong> </font></div></td>
      <td width="54%"><%=UsersBean.getUserName()%>
        <input type="hidden" readonly name="userName" id="userName" value="<%=UsersBean.getUserName()%>">
      </td>
    </tr>
    <tr>
      <td width="46%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <strong>Employee Id: </strong></font></div></td>
      <td width="54%"><%=UsersBean.getEmpId()%>
        <input type="hidden" readonly name="empId" id="empId" value="<%=UsersBean.getEmpId()%>">
      </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"> <hr noshade color="#000000"> </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
    <td colspan="2">
    <table width="35%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="#000000">
    <tr>
     <td><div align="center"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
     User Role(S) </font></strong></div></td>
          </tr>
          <tr>
            <td><div align="left">
                <table width="100%" border="0" cellspacing="3" cellpadding="0">
        <% /*show all roles of user to be deleted */
            String roleIds = "";
            String roles = "";
        %>
            <% if (UsersBean.getRoles().size() > 0)
            {
            for (int j=0; j<UsersBean.getRoles().size(); j++) {
        %>
            <tr>
              <td> <li>&nbsp;</li> </td>
              <td><div align="Left"><%=(String)UsersBean.getRoles().elementAt(j)%></div>
              <% roleIds = roleIds + (String)UsersBean.getRoleIds().elementAt(j) + "|";
                 roles = roles + (String)UsersBean.getRoles().elementAt(j) + "|";
              %>
                <strong>
                </strong> </td>
            </tr>
            <% }
            } %>
            <input type="hidden" name="rol" id="rol" value="<%=roles%>">
            <input type="hidden" name="rolId" id="rolId" value="<%=roleIds%>">
          </table>
        </div></td>
          </tr>
        </table>
    </td>
    </tr>
    <tr>
      <td>&nbsp;</td>
      <td>&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2"><div align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          <input name="callAction" type="submit" id="callAction" value="Delete Record">
          <input name="callAction" type="submit" id="callAction" value="Back">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
          <input type="hidden" name="oldUserName" id="oldUserName" value="<%=UsersBean.getOldUserName()%>">
          </font></div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
if (UsersBean != null)
  UsersBean.closeDBConn();
%>
</body>
</html>
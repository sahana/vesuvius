<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="UsersBean" scope="session" class="tccsol.admin.accessControl.UsersBean"/>
<jsp:useBean id="ListSBean" scope="session" class="tccsol.util.ListSingleBean" />

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
<form action="/hris/usersservlet" method="post" name="frmUsersUpdDel">
<br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
  Users - Update/Delete</u></strong></font> </p>

  <table width="74%" border="0" align="center" cellpadding="0" cellspacing="2">
    <tr>
      <td colspan="2"> <table width="100%" border="0" cellspacing="3" cellpadding="0">
          <tr>
            <td width="36%" valign="top">
              <%  if (ListSBean.getId() != null) {
                        if (ListSBean.getId().length() > 0) {
                            UsersBean.setUserName(ListSBean.getId());
                            session.removeAttribute("ListSBean");
                        }
                      }
                  %>
              <div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">User
                Name: </font></div></td>
            <td width="64%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
              <input name="uuserName" type="text" id="uuserName" value="<%=UsersBean.getUserName()%>">
              </font></td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td colspan="2" >&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2" ><div align="center">
          <input name="callAction" type="submit" id="callAction" value="Select From List">
          <input name="callAction" type="submit" id="callAction" value="Update">
          <input name="callAction" type="submit" id="callAction" value="Delete">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
        </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%
if (UsersBean != null)
  UsersBean.closeDBConn();

session.removeAttribute("ListSBean");
session.removeAttribute("EmpListSBean");
%>
</body>
</html>
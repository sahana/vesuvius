<%@ page language="java" errorPage="/ErrorDetails.jsp" %>
<jsp:useBean id="SetAccessPermissionBean" scope="session" class="tccsol.admin.accessControl.SetAccessPermissionBean"/>
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
<form action="/sahanaadmin/setaccesspermissionservlet" method="post" name="frmAccessPerm1">
  <br><br>
  <p align="center"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong><u>
  Access Permission</u></strong></font></p>

  <table width="77%" border="0" align="center" cellpadding="0" cellspacing="3">
    <tr>
      <td colspan="2" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2" valign="top"><table width="101%" border="0" cellspacing="3" cellpadding="0">
          <tr>
            <td width="27%"><div align="right">
                <input type="radio" name="selMode" id="selMode" value="M">
              </div></td>
            <td width="73%"><strong><font size="2" face="Verdana, Arial, Helvetica, sans-serif">Select
              Module(s)</font></strong></td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td width="41%"><div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Module Id: </font></div></td>
      <td width="59%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
      <% if (ListBean.getIds() != null && SetAccessPermissionBean.getSelMode().equalsIgnoreCase("M")) {
            if (ListBean.getIds().size() > 0) {
                SetAccessPermissionBean.setModIds(ListBean.getIds());
                SetAccessPermissionBean.setModules(ListBean.getNames());
                session.removeAttribute("ListBean");
            }
            if (SetAccessPermissionBean.getModIds().size() > 0)
            {
              String ids = "";
              for (int i=0; i<SetAccessPermissionBean.getModIds().size(); i++)
              {
                if (i == (SetAccessPermissionBean.getModIds().size() - 1))
                  ids = ids + SetAccessPermissionBean.getModIds().elementAt(i);
                else
                  ids = ids + SetAccessPermissionBean.getModIds().elementAt(i) + ",";
              }
              SetAccessPermissionBean.setModuleId(ids);
            }
        }
      %>
        <textarea name="moduleId" cols="40" rows="2" id="moduleId"><%=SetAccessPermissionBean.getModuleId()%></textarea>
        </font></td>
    </tr>
    <tr>
      <td colspan=2><div align="Left"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          &nbsp;&nbsp;&nbsp;&nbsp;
          [Module Id (if more than 1) should be seperated by
          Commas (,) if entered manually] </font></div><br></td>
    </tr>
    <tr>
      <td colspan="2" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2" valign="top"><table width="100%" border="0" cellspacing="3" cellpadding="0">
          <tr>
            <td width="27%"><div align="right">
                <input type="radio" name="selMode" id="selMode" value="R">
              </div></td>
            <td width="73%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif"><strong>Select
              Role</strong></font></td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td> <div align="right"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
          Role Name: </font></div></td>
      <td width="59%"><font size="2" face="Verdana, Arial, Helvetica, sans-serif">
        <% if (ListSBean.getId() != null && SetAccessPermissionBean.getSelMode().equalsIgnoreCase("R")) {
            if (ListSBean.getId().trim().length() > 0) {
                SetAccessPermissionBean.setRoleName(ListSBean.getId());
                session.removeAttribute("ListSBean");
            }
         }
      %>
        <input name="roleName" type="text" id="roleName" value="<%=SetAccessPermissionBean.getRoleName()%>">
        </font></td>
    </tr>
    <tr>
      <td colspan="2" valign="top">&nbsp;</td>
    </tr>
    <tr>
      <td colspan="2" valign="top"><div align="center"><br>
          <input name="callAction" type="submit" id="callAction" value="Select From List">
          <input name="callAction" type="submit" id="callAction" value="Set Access Permission">
          <input type="hidden" name="url" id="url" value="<%=request.getServletPath()%>">
        </div></td>
    </tr>
  </table>
  <p>&nbsp;</p>
</form>
<%}
  if (SetAccessPermissionBean != null)
    SetAccessPermissionBean.closeDBConn();

  session.removeAttribute("ListSBean");
  session.removeAttribute("ListBean");
%>
</body>
</html>

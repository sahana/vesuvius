<%--Camp reg Welcome--%>

<%@ page import="org.campdb.business.User,
                 org.campdb.util.CAMPDBConstants"%><!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana ::</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<style type="text/css">
<!--
.style1 {color: #000000}
.style2 {color: #FF3300}
.style3 {color: #999999}
-->
</style>
<script>
//
</script>
</head>

<body topmargin="0" leftmargin="0">
<%
    request.setAttribute("turl", "index.jsp");
    request.setAttribute("modNo", "3");
    request.setAttribute("accessLvl", "PAGE");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>

   <%
      LoginBean lbean = (LoginBean)session.getAttribute("LoginBean");
      User user = new  User(lbean.getUserName(),lbean.getOrgId());
      user.setOrganization(lbean.getOrgName());
//       User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
      if(user == null){
        request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
      response.sendRedirect("error.jsp");
     }
   %>
<table width="100%" border="0">
    <tr>

    <td height="50" >
      <jsp:include page="comman/header.inc"></jsp:include>
    </td>

    </tr>
    <tr>
    <td  align="left" valign="top">
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
        <td class="border">
        <table width="100%" border="0" cellspacing="1" cellpadding="0">
        <tr>
        <td class="pageBg">
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
          <tr>
            <td>&nbsp;</td>
          </tr>
          <tr>
            <td>
            </td>
          </tr>
          <tr>
            <td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
              <tr>
                    <td width="134" valign="top"><img src="images/imgLogin.jpg" width="302" height="200" border="0"></td>
                    <td valign="top" bgcolor="#D8E9FD">
                      <table width="100%" border="0" cellpadding="0" cellspacing="0">

                  <tr>
                    <td>&nbsp;</td>
                    <td><table width="100%" border="0" cellspacing="1" cellpadding="0">
                        <br>
                        <br>
                        <tr>
                        <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                        <td  nowrap class="formText" align="left" ><strong><a href="SearchCamps.jsp" style="text-decoration:none"  class="style1">Search</a></strong> </td>
                        </tr>
                        <tr>
                        <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                        <td  nowrap class="formText" align="left"><strong><a href="InsertCamps.jsp" style="text-decoration:none"  class="style1">Insert Camps</a></strong></td>
                        </tr>
				<!--<tr>
                        <td  align="right" class="formText"><strong><span class="style2">&raquo;</span>&nbsp;</strong></td>
                        <td  nowrap class="formText" align="left"><strong><a href="/reports/sahana-report.vx?report=cmap-detail-report" style="text-decoration:none"  class="style1">Camps Details Report</a></strong></td>
                        </tr>-->
                         
                      <!-- end of register link -->
                        </table>                  <label>
                        </label></td>
                      </tr>
                    </table></td>
                  </tr>
                </table></td>
              </tr>
            </table></td>
          </tr>
        </table>
        </td>
        </tr>
        </table>


      </td>
      </tr>
      <tr>
      <td>
          <jsp:include page="comman/footer.inc"></jsp:include>
          </td>
      </tr>
      </table>
    </body>
    </html>

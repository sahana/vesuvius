<%@ page import="java.util.Collection,
                 org.assistance.model.User,
                 org.assistance.db.DataAccessManager,
                 org.assistance.Constants,
                 java.util.List,
                 org.assistance.business.AddOfferAssistanceTO,
                 java.util.Iterator"%>
 <%--<%@ page import="org.erms.db.DataAccessManager,--%>
<%--                 org.erms.util.ERMSConstants,--%>
<%--                 org.erms.business.User"%>--%>
<%--<%@ page contentType="text/html;charset=UTF-8" language="java" %>--%>
<html>
<head>
<title>:: Sahana ::</title>
<link href="common/style.css" rel="stylesheet" type="text/css">
<%
            DataAccessManager dam =  DataAccessManager.getInstance();
            //Is he authenticated
		   	User user = (User) request.getSession().getAttribute(Constants.USER_INFO);
		    if (user==null){
		    	//Nobody should come here without a user
		   	    request.getSession().setAttribute(Constants.ERROR_DESCRIPTION, "User not authenticated!");
		       	response.sendRedirect("error.jsp");
		    }
%>
</head>
<body>

<jsp:include page="common/header.inc"></jsp:include>
<%--    <table width="100%" border="0" cellspacing="2" cellpadding="0" bgcolor="#D8E9FD">--%>
<%--      <tr>--%>
<%--            <td width="134" valign="top"><img src="images/imgLoginAssistance.jpg" width="302" height="200" border="0"></td>--%>
<%--            <td valign="top" bgcolor="#D8E9FD">--%>
<%--      </tr>--%>
<%--    </table>--%>
<%--    <h2>Reports Goes Here</h2>--%>
<table width="100%">
       <tr><td>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left" background="images/BannerBG.jpg">
             <td class="statusBar" background="images/BannerBG.jpg" >
              <a href="AddOfferAssistance.jsp"><font color="#000000">&nbsp;&nbsp;Add Assitance Offers</font></a>&nbsp;&nbsp;
               <font color="#000000">Logged in as <%=user.getUserName()%> of <%=user.getOrganization()%></font></font>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
               <a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log off&nbsp;&nbsp;&nbsp;&nbsp;
             </td>
<%--                <td class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>--%>
<%--                <td class="statusBar"  background="images/BannerBG.jpg" bgcolor="#000099"><a href="AddOfferAssistance.jsp"><font color="#000000">&nbsp;&nbsp;Add Assitance Offers</font></a>&nbsp;&nbsp;</td>--%>
<%--                <td class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>--%>
<%----%>
<%--                <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar" > <font color="#000000">Logged in <%=user.getUserName()%> of <%=user.getOrganization()%></font></font></td>--%>
<%----%>
<%--                <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="Logoff.jsp" style="text-decoration:none"><font color="#000000">Log--%>
<%--                            off&nbsp;&nbsp;&nbsp;&nbsp;</font></a>--%>
<%--                </td>--%>
            </tr>
       </table>
       </td></tr>

        <!--- Banner is in ------>
       <tr><td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                 <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">View All Offers</td>
                </tr>
                <tr>
                    <td width="117">&nbsp;</td>
                    <td width="484">&nbsp;</td>
                </tr>
                <tr>
                    <td>&nbsp;</td>
                    <td>&nbsp;</td>
                </tr>
              </table>
          </td></tr>

              <%
                  List offers = dam.getAllOffers();
                  Iterator iterator = offers.iterator();
                  AddOfferAssistanceTO addOfferAssistanceTO =  null;
              %>
       <tr><td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr >
                    <td class="tableUp" align="center" width="7.5%">&nbsp;Agency</td>
                    <td class="tableUp" align="center" width="10%"> &nbsp;Date</td>
                    <td class="tableUp" align="center" width="10%"> &nbsp;Sectors</td>
                    <td class="tableUp" align="center" width="15%"> &nbsp;Partners</td>
                    <td class="tableUp" align="left" width="25%"> &nbsp;Relief Committed</td>
                    <td class="tableUp" align="center" width="25%"> &nbsp;Human Resources Committed</td>
                    <td class="tableUp" align="center" width="7.5%"> &nbsp;</td>

              </tr>

              <%
                  while (iterator.hasNext()) {
                      addOfferAssistanceTO =  (AddOfferAssistanceTO)iterator.next();
                 String s1= addOfferAssistanceTO.getReliefCommittedDetails();
                 if (s1 == null)
                    s1 = "&nbsp;";
                 else
                    if (s1.length() > 100)
                        s1= s1.subSequence(0, 100)+"...";
                  String s2= addOfferAssistanceTO.getHumanResourcesCommitted();
                 if (s2 == null)
                    s2 = "&nbsp;";
                 else
                    if (s2.length() > 100)
                        s2= s2.subSequence(0, 100)+"...";
              %>

                <tr>
                    <td class="tableDown" align="left"> <%=addOfferAssistanceTO.getAgency()==null?"&nbsp;": addOfferAssistanceTO.getOrgName()%></td>
                    <td class="tableDown" align="left"> <%=addOfferAssistanceTO.getDate()==null?"&nbsp;": addOfferAssistanceTO.getDate().toString()%></td>
                    <td class="tableDown" align="left"> <%=addOfferAssistanceTO.getSectors()==null?"&nbsp;":addOfferAssistanceTO.getSectors()%></td>
                    <td class="tableDown" align="left"> <%=addOfferAssistanceTO.getPartners()==null?"&nbsp;":addOfferAssistanceTO.getPartners()%></td>
                    <td class="tableDown" align="left"> <%=s1%></td>
                    <td class="tableDown" align="left"> <%=s2%></td>
                    <td class="tableDown" align="left">
                        <%
                            if(addOfferAssistanceTO.getAgency().equals(user.getOrgCode())){%>
                                <a href="AddOfferAssistance.jsp?<%=org.assistance.Constants.EDIT%>=<%=addOfferAssistanceTO.getId()%>" style="text-decoration:none"  class="style1">Edit</a>
                            <%}
                            else{ %>
                                <a href="AddOfferAssistance.jsp?<%=org.assistance.Constants.VIEW%>=<%=addOfferAssistanceTO.getId()%>" style="text-decoration:none"  class="style1">View</a>
                            <%}
                        %>

                    </td>
              </tr>

              <%
                  }
              %>

        </table>
        </td></tr>
<%--        <tr >--%>
<%--            <td>--%>
<%--                <table width="100%" border="0" cellspacing="0" cellpadding="0">--%>
<%--                    <tr>--%>
<%--                        <td class="statusBar">&nbsp;</td>--%>
<%--                    </tr>--%>
<%--                </table>--%>
<%----%>
<%--            </td>--%>
<%--      </tr>--%>
</table>
      <jsp:include page="common/welcomefooter.inc"></jsp:include>
      <jsp:include page="common/footer.inc"></jsp:include>

</body>
</html>
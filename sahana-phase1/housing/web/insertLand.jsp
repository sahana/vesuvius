
<%@ page import="java.util.LinkedList,
                 java.util.List,
                 java.text.SimpleDateFormat,
                 java.util.ArrayList,
                 java.util.Iterator,
                 org.housing.util.LabelValue,
                 org.housing.db.DataAccessManager"%>
<jsp:useBean id="newLand" scope="page" class="org.housing.business.LandTO" />
<jsp:setProperty name="newLand" property="*" />
<%
    boolean inserted = false;
    List errors = new LinkedList();
    if (request.getParameter("doInsert") != null) {
        DataAccessManager dataAccessManager = new DataAccessManager();
        // LAND errors.addAll(dataAccessManager.validateCampTOforInsert(newCamp));

        if(errors.size()<=0) {
            try {
                inserted=dataAccessManager.addLand(newLand);
                newLand.reset();
            } catch (Exception e) {
//                errors.add(e.getMessage());
            }
            if(inserted) {
            %>
              <jsp:include page="common/header.inc"></jsp:include>

             <p align="center" class="formText" >
               <h3 align="center" >You have successfully inserted a Housing Scheme to the system !!</h3>
             </p>
           <%
                session.invalidate();
          } else {
               response.sendRedirect("error.jsp");
            }
            %>
             </body>
                <jsp:include page="common/footer.inc"></jsp:include>
            </html>
          <%
            return;
        }

  } else {
        newLand.reset();
    }
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>


<title>:: Sahana :: Housing</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="common/style.css" rel="stylesheet" type="text/css">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script type="text/javascript">
</script>
</head>

<body topmargin="0" leftmargin="0">
   <%
//       User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
//      LoginBean lbean = (LoginBean)session.getAttribute("LoginBean");
      /*user = new  User(lbean.getUserName(),lbean.getOrgId());
      user.setOrganization(lbean.getOrgName());
       if(user == null){
           request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
           response.sendRedirect("error.jsp");
       }*/
   %>
        <table width="760" border="0" cellspacing="0" cellpadding="0">
        <td height="50" >
      <jsp:include page="common/header.inc"></jsp:include>
    </td>
        <tr>
        <td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left">
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchCamps.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
                    Housing Scheme</font></a>&nbsp;&nbsp;</td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="LogOff.jsp" style="text-decoration:none"><font color="#000000">Log
                    off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
            </tr>

            </table>

          </td>
          </tr>

        </table>
        <table width="760" border="0" cellspacing="0" cellpadding="0">
             <tr>
               <td background="images/HeaderBG.jpg" colspan="2" class="formTitle">Add Land  </td>
             </tr>
         </table>


<form name="newLand" action="insertLand.jsp">
    <table cellspacing="4"  >
        <%
            if(errors.size() > 0) {
                 %>
        <tr>
            <td colspan="3"class="formText" ><font color="red">Please correct the following errors</font><br></td>
        </tr>
        <%
                newLand.setNullValsToEmpty();
                for (Iterator iterator = errors.iterator(); iterator.hasNext();) {
                    String error = (String) iterator.next();

         %>
        <tr>
            <td colspan="3"class="formText" ><font color="red"><li><%=error%></li></font><br></td>
        </tr>
        <%      }
            }
        %>

<%--        <%--%>
<%--            if(inserted) {--%>
<%--        %>--%>
<%--            <tr>--%>
<%--                <td colspan="3" ><font color="blue" size="-1">Successfully inserted values to the database</font><br></td>--%>
<%--            </tr>--%>
<%--        <%--%>
<%--            }--%>
<%--        %>--%>


        <tr>
            <td align="right" valign="top"  class="formText"  >Land Name</td><td><input type="text" size="20" maxlength="49"  name="landName" class="textBox"  value="<jsp:getProperty name="newLand" property="landName" />">&nbsp;<small><font color="red">*</font></small></td>
        </tr>
        <tr>
            <td  align="right" valign="top"  class="formText" >Description&nbsp;</td>
               <td>
                 <input type="text" size="20" maxlength="49"  name="description" class="textBox"  value="<jsp:getProperty name="newLand" property="description" />">
               </td>
        </tr>

         <tr>
            <td  align="left" valign="top"   class="formText">Division&nbsp;</td>
                <td>
                <select name="divisionId" class="selectBoxes">
                    <option value="">&lt;Select&gt;</option>
                    <%
                     DataAccessManager da = new DataAccessManager();
                        // DataAccessManager da= new DataAccessManager();
                      List divisions = (List) da.listDivisions() ;
                        for (Iterator iterator = divisions.iterator(); iterator.hasNext();) {
                            LabelValue division = (LabelValue) iterator.next();
                    %>
                            <option value="<%=division.getValue()%>"><%=division.getLabel()%></option>
                    <%
                        }
                    %>
                </select>&nbsp;<small><font color="red">*</font></small>
                <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
            </td>

       </tr>


       <tr>


            <td  align="left" valign="top"   class="formText">Area&nbsp;</td>
            <td ><input type="text" size="10" maxlength="49"  name="measurement" class="textBox"  value="<jsp:getProperty name="newLand" property="measurement" />"> </td>
            <td>
                <select name="areaId" class="selectBoxes">
                    <option value="">&lt;Select&gt;</option>
                    <%
                     DataAccessManager dat1 = new DataAccessManager();
                        // DataAccessManager da= new DataAccessManager();
                      List areas = (List) dat1.listArea();
                        for (Iterator iterator = areas.iterator(); iterator.hasNext();) {
                            LabelValue area = (LabelValue) iterator.next();
                    %>
                            <option value="<%=area.getValue()%>"><%=area.getLabel()%></option>
                    <%
                        }
                    %>
                </select>&nbsp;<small><font color="red">*</font></small>
                <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
            </td>



       </tr>


       <tr>
                    <td  align="left" valign="top"   class="formText">Owned By &nbsp;</td>

                    <td>
                        <select name="ownedById" class="selectBoxes">
                            <option value="">&lt;Select&gt;</option>
                            <%
                             DataAccessManager dat4 = new DataAccessManager();
                                // DataAccessManager da= new DataAccessManager();
                              List ownedBys = (List) dat4.listOwnedBy();
                                for (Iterator iterator = ownedBys.iterator(); iterator.hasNext();) {
                                    LabelValue ownedBy = (LabelValue) iterator.next();
                            %>
                                    <option value="<%=ownedBy.getValue()%>"><%=ownedBy.getLabel()%></option>
                            <%
                                }
                            %>
                        </select>&nbsp;<small><font color="red">*</font></small>
                        <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
                    </td>

                    <td  align="left" valign="top"   class="formText">Comments&nbsp;</td>
                    <td ><input type="text" size="10" maxlength="49"  name="ownedByComment" class="textBox"  value="<jsp:getProperty name="newLand" property="ownedByComment" />"> </td>


       </tr>

       <tr>
            <td  align="left" valign="top"   class="formText">Terms&nbsp;</td>

            <td>

                <select name="termId" class="selectBoxes">
                    <option value="">&lt;Select&gt;</option>
                    <%
                     DataAccessManager dat3 = new DataAccessManager();
                        // DataAccessManager da= new DataAccessManager();
                      List terms = (List) dat3.listTerms();
                        for (Iterator iterator = terms.iterator(); iterator.hasNext();) {
                            LabelValue term = (LabelValue) iterator.next();
                    %>
                            <option value="<%=term.getValue()%>"><%=term.getLabel()%></option>
                    <%
                        }
                    %>
                </select>&nbsp;<small><font color="red">*</font></small>
                <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
            </td>

       </tr>

       <tr>

            <table>
              <tr>
                      <td  align="right" valign="top"  class="formText" >GPS Co-Ordinates&nbsp;</td>
                      <td>&nbsp;&nbsp;</td>
                      <td>
                         <input type="text" size="10" maxlength="49"  name="GPS1" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS1" />">
                       </td>
                       <td>&nbsp;&nbsp;</td>
                       <td>
                         <input type="text" size="10" maxlength="49"  name="GPS2" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS2" />">
                       </td>
                       <td>&nbsp;&nbsp;</td>
                       <td>
                         <input type="text" size="10" maxlength="49"  name="GPS3" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS3" />">
                       </td>
                       <td>&nbsp;&nbsp;</td>
                       <td>
                         <input type="text" size="10" maxlength="49"  name="GPS4" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS4" />">
                       </td>

                 </tr>
               </table>
        </tr>
        <tr>
           <td>
               <table>
                       <tr>
                          <td></td>
                          <td>
                            <input type="reset" name="reset" value="Clear" class="buttons"/>
                            <input type="submit" name="doInsert" value="Add" class="buttons"/>
                        </tr>
                 </table>
            </td>
        </tr>
        <tr>
         <td>

         </td>
        </tr>
    </table>

</form>

  <jsp:include page="common/footer.inc"></jsp:include>
</body>
</html>



<%@ page import="org.assistance.db.DataAccessManager,
                 java.math.BigDecimal
                 ,
                 java.util.Date,
                 org.assistance.Constants,
                 org.assistance.model.User,
                 org.assistance.business.AddOfferAssistanceTO"%>
<jsp:useBean id="addOffer" scope="request" class="org.assistance.business.AddOfferAssistanceTO" />

<jsp:setProperty name="addOffer" property="*" />

<html>

<header>

  <title>:: Sahana ::</title>

  <script>



  </script>

 <link href="common/style.css" rel="stylesheet" type="text/css">



</header>



<body>
 <%
    request.setAttribute("turl", "Welcome.jsp");
    request.setAttribute("modNo", "1");
    request.setAttribute("accessLvl", "ADD");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>

    <jsp:include page="common/header.inc"></jsp:include>

    <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
         <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Add offer of Assitance</td>
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


 <%
      boolean readOnly = false;
      LoginBean lbean = (LoginBean)session.getAttribute("LoginBean");
      User loginUser = new  User(lbean.getUserName(),lbean.getOrgId());
//      User loginUser = (User) request.getSession().getAttribute(Constants.USER_INFO);
          if (loginUser==null){
              request.getSession().setAttribute(Constants.ERROR_DESCRIPTION, "User not authenticated!");
              response.sendRedirect("error.jsp");
          }

     DataAccessManager dataAccessManager = DataAccessManager.getInstance();
     if (request.getParameter("submit") != null) {


         User user = (User)request.getSession().getAttribute(Constants.USER_INFO);
         if(user!= null){
           String orgCode =user.getOrgCode() ;
           addOffer.setAgency(orgCode);
         }
         boolean status;
         System.out.println(addOffer.isUnique());
         if (null != request.getSession().getAttribute(Constants.OFFER_ID)) {
            addOffer.setId(Integer.parseInt((String)request.getSession().getAttribute(Constants.OFFER_ID)));
            status = dataAccessManager.update(addOffer);
         }
         else {
            java.sql.Date sDate = new java.sql.Date(System.currentTimeMillis());
            addOffer.setDate(sDate);
            status = dataAccessManager.insert(addOffer);
         }
         if(status) {
         %>
         <p align="center" class="formText" >
               <h2>Your offer has been successfully added.!</h2>
         </p>
    <%
    // session.invalidate();
    } else {
      response.sendRedirect("error.jsp");
    }

   %>
     </body>
     <jsp:include page="common/welcomefooter.inc"></jsp:include>
  </html>
<%
            return;
    }
    else if(null != request.getQueryString()){ //this isnt the submit
        String queryString = request.getQueryString();
        String id = queryString.substring(5).trim();
        if(Constants.VIEW.equals(queryString.substring(0,4))){


              addOffer.read(Integer.parseInt(id));
            readOnly = true;

        }else if(Constants.EDIT.equals(queryString.substring(0,4))){
            addOffer.read(Integer.parseInt(id));
            request.getSession().setAttribute(Constants.OFFER_ID, id);
        }

     }
%>

    <form method="post" name="tsunamiAddOffer" action="AddOfferAssistance.jsp">
          <table border="0" width="100%" cellspacing="1" cellpadding="1">

           <tr>
               <td align="right" vAlign="top" class="formText">Date : </td>
               <td>
                   <%  java.sql.Date date ;
                       System.out.println(addOffer.getDate());
                       if(null ==addOffer.getDate()){
                        date = new java.sql.Date(System.currentTimeMillis());
                   }else{
                       date = addOffer.getDate();
                   }

                   %>
                   <%=date.toString()%>
                </td>
          </tr>

           <tr>
               <td align="right" vAlign="top" class="formText">Sector : </td>
               <td>
                   <textarea cols="50" name="sectors"
                    <%if(readOnly){%>
                        <%="readonly="+readOnly%>
                     <%}%>

                          rows="1" id="Facilities" class="textBox"><%= (addOffer.getSectors()==null) ? "" :addOffer.getSectors() %></textarea>
                </td>
          </tr>

           <tr>
               <td align="right" vAlign="top" class="formText">Partners : </td>
               <td>
                   <textarea cols="50" name="partners" rows="3"
                    <%if(readOnly){%>
                       <%="readonly="+readOnly%>
                    <%}%>


                    id="Facilities" class="textBox"><%= (addOffer.getPartners()==null) ? "" :addOffer.getPartners() %></textarea>
                </td>
          </tr>
          <tr>
           <td align="right" vAlign="top" class="formText">Relief Committed :</td>
                   <td>
                   <textarea cols="50" rows="3" name="reliefCommittedDetails"
                    <%if(readOnly){%>
                       <%="readonly="+readOnly%>
                    <%}%>


                    id="Facilities" class="textBox"><%=addOffer.getReliefCommittedDetails()==null?"":addOffer.getReliefCommittedDetails()%></textarea>
                  </td>

           </tr>
           <tr>
             <td align="right" vAlign="top" class="formText">Relief Committed Monetary Value($) :</td>
             <td>
                  <input name="reliefCommittedTotal" type="text" class="textBox"
                    <%if(readOnly){%>
                        <%="readonly="+readOnly%>
                     <%}%>


                   size="20" value="<%=addOffer.getReliefCommittedTotal()==null?"": addOffer.getReliefCommittedTotal()%>" >&nbsp;
             </td>
           </tr>
           <tr>
           <td align="right" vAlign="top" class="formText">Relief Disbursed :</td>
                   <td>
                   <textarea cols="50" name="reliefDisbursedDetails" rows="3"
                    <%if(readOnly){%>
                         <%="readonly="+readOnly%>
                    <%}%>


                    id="Facilities" class="textBox"><%=addOffer.getReliefDisbursedDetails()==null?"":addOffer.getReliefDisbursedDetails()%></textarea>
                   </td>
           </tr>
           <tr>
               <td align="right" vAlign="top" class="formText">Relief Disbursed Monetary Value($) :</td>
               <td>
                  <input name="reliefDisbursedTotal" type="text" class="textBox"
                    <%if(readOnly){%>
                        <%="readonly="+readOnly%>
                    <%}%>



                    value="<%=addOffer.getReliefDisbursedTotal()==null?"": addOffer.getReliefDisbursedTotal()%>"/>&nbsp;
               </td>
           </tr>
           <tr>
                   <td align="right" vAlign="top" class="formText">Human Resource Committed :</td>
                   <td>
                   <textarea cols="50" rows="3" name="humanResourcesCommitted"

                    <%if(readOnly){%>
                        <%="readonly="+readOnly%>
                    <%}%>


                    class="textBox" ><%=addOffer.getHumanResourcesCommitted()==null?"": addOffer.getHumanResourcesCommitted()%></textarea> &nbsp;
                   </td>
           </tr>
           <tr>
                   <td align="right" vAlign="top" class="formText">Need Assesments Underway  and Completed :</td>
                   <td>
                   <textarea cols="50" rows="3" name="needsAssessments"

                   <%if(readOnly){%>
                        <%="readonly="+readOnly%>
                   <%}%>


                    class="textBox" ><%=addOffer.getNeedsAssessments()==null?"": addOffer.getNeedsAssessments()%></textarea>&nbsp;
                   </td>
           </tr>
           <tr>
                   <td align="right" vAlign="top" class="formText">Other Activities :</td>
                   <td>
                   <textarea cols="50" rows="3" name="otherActivities"

                   <%if(readOnly){%>
                     <%="readonly="+readOnly%>
                   <%}%>


                    type="text" class="textBox" ><%=addOffer.getOtherActivities()==null?"": addOffer.getOtherActivities()%></textarea> &nbsp;
                   </td>
           </tr>
           <tr>
                   <td align="right" vAlign="top" class="formText">Planned Activities :</td>
                   <td>
                   <textarea cols="50" rows="3" name="plannedActivities"

                   <%if(readOnly){%>
                      <%="readonly="+readOnly%>
                    <%}%>


                    class="textBox" ><%=addOffer.getPlannedActivities()==null?"": addOffer.getPlannedActivities()%></textarea> &nbsp;
                   </td>
           </tr>
           <tr>
                   <td align="right" vAlign="top" class="formText">Other Issues Arising:</td>
                   <td>
                   <textarea cols="50" rows="3" name="otherIssues"

                    <%if(readOnly){%>
                      <%="readonly="+readOnly%>
                    <%}%>


                    class="textBox" ><%=addOffer.getOtherIssues()==null?"": addOffer.getOtherIssues()%></textarea>&nbsp;
                   </td>
           </tr>
          <tr>
            </tr>
            <tr>
              <td></td>
                 <td>
                  <input name="submit" type="submit"

                  <%if(readOnly){%>
                    <%="disabled="+readOnly%>
                   <%}%>


                   value=" Save " class="buttons" >
                   <input name="reset" type="reset"

                   <%if(readOnly){%>
                    <%="disabled="+readOnly%>
                   <%}%>

                    value=" Clear " class="buttons" >
                  </td>
               </tr>
             </table>
        </form>
        <jsp:include page="common/welcomefooter.inc"></jsp:include>
        <jsp:include page="common/footer.inc"></jsp:include>
        </body>

  </html>




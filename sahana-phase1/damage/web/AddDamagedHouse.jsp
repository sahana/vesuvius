<%@ page import="org.sahana.share.utils.KeyValueDTO,
                 java.util.ArrayList,
                 java.util.Iterator,
                 java.util.Collection"%>
 <%--
  Created by IntelliJ IDEA.
  User: Chathura
  Date: Jan 17, 2005
  Time: 3:36:55 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
  <head>
     <title>:: Sahana ::</title>

     <link href="common/style.css" rel="stylesheet" type="text/css">

     <%
//             DataAccessManager dataAccessManager = new DataAccessManager();
//              Collection allDistrictNamesCollection = dataAccessManager.getAllDistrictNames();

          %>

  </head>

  <body>

   <jsp:include page="common/header.inc"></jsp:include>


   <form method="post" name="tsunamiAddOffer" action="AddOfferAssistance.jsp">
             <table border="0" width="100%" cellspacing="1" cellpadding="1">

              <tr>
                  <td align="right" vAlign="top" class="formText">District : </td>
                  <td>
                        <select>
<%--                                 <%Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();--%>
<%--                                    ArrayList workingAreas = orgReg.getWorkingAreas();--%>
<%--                                    while (allDistricts.hasNext()) {--%>
<%--                                         KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();--%>
<%----%>
<%--                                  %>--%>

                        </select>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Divsion : </td>
                  <td>
                     <textarea ></textarea>
                   </td>
             </tr>

        </table>
    </form>


   <jsp:include page="common/welcomefooter.inc"></jsp:include>
   <jsp:include page="common/footer.inc"></jsp:include>

  </body>
</html>
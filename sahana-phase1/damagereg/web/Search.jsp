<%@ page import="java.util.Iterator,
                 org.sahana.share.utils.KeyValueDTO,
                 org.damage.db.DataAccessManager,
                 java.util.List,
                 org.damage.business.DamagedHouseTO"%>
 <%--
  Created by IntelliJ IDEA.
  User: srinath
  Date: Jan 17, 2005
  Time: 6:20:56 PM
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<jsp:useBean id="search" scope="request" class="org.damage.business.SearchHouseTO" />
<jsp:setProperty name="search" property="*" />


<html>
  <head>
       <title>:: Sahana ::</title>
       <link href="common/style.css" rel="stylesheet" type="text/css">
            <%
                    DataAccessManager dataAccessManager = new DataAccessManager();
                    boolean firstTime = false;
                    Object obj = request.getSession().getAttribute("VISITED");
                    if(obj == null){
                         firstTime = true;
                         request.getSession().setAttribute("VISITED","Hello");
                    }

             %>

  </head>
  <body>
  <jsp:include page="common/header.inc"></jsp:include>
    <table>
        <tr>
            <td>
            <form method="post" name="tsunamiAddDamagedHouse" action="Search.jsp">
               <table>
                    <tr><td>districtCode</td><td>

                     <select name="orgType" class="selectBoxes">
                                 <%Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                                    String option= null;
                                    while (allDistricts.hasNext()) {
                                         KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();
                                         if(keyValueDTO.getDbTableCode().equals(search.getDistrictCode())){
                                            option  = "<option selected=\"true\" value=\""+keyValueDTO.getDbTableCode()+"\">"+keyValueDTO.getDisplayValue()+"</option>";
                                         }
                                            option  = "<option value=\""+keyValueDTO.getDbTableCode()+"\">"+keyValueDTO.getDisplayValue()+"</option>";
                                        %><%=option%><%

                                    }
                                  %>

                    </td></tr>
                    <%
                        String districtCode  =   search.getDistrictCode();
                        String gsn = search.getGsn();
                        String owner = search.getOwner();

                        if(districtCode == null){
                             districtCode = "";
                        }
                        if(gsn == null){
                            gsn = "";
                        }
                        if(owner == null){
                            owner = "";
                        }

                    %>
                    <tr><td>division</td><td><input name="division" value="<%=districtCode%>"/> </td></tr>
                    <tr><td>gsn</td><td><input name="gsn" value="<%=gsn%>"/> </td></tr>
                    <tr><td>owner</td><td><input name="owner" value="<%=owner%>"/> </td></tr>

                    <tr><td><input type="submit" ></td></tr>
               </table>
               </form>
            </td>
        </tr>

        <%
            if(!firstTime){
            List searchReasult = dataAccessManager.searchRequests(search);
        %>
        <tr class="tableUp">
            <td>DistrictCode</td>
            <td>Division</td>
            <td>GSN</td>
            <td>distanceFromSea</td>
            <td>City</td>
            <td>FloorArea</td>
        </tr>
             <%
               Iterator it = searchReasult.iterator();
               while(it.hasNext()){
               DamagedHouseTO to = (DamagedHouseTO)it.next();
             %>
                <tr>
                    <td><%=to.getDistrictCode()%></td>
                    <td><%=to.getDivision()%></td>
                    <td><%=to.getGSN()%></td>
                    <td><%=to.getDistanceFromSea()%></td>
                    <td><%=to.getCity()%></td>
                    <td><%=to.getFloorArea()%></td>
                </tr>
                <% }
            }
                %>

    </table>


  </body>
</html>
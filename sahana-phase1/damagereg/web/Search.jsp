<%@ page import="java.util.Iterator,
                 org.sahana.share.utils.KeyValueDTO,
                 org.damage.db.DataAccessManager"%>
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
             %>

  </head>
  <body>
  <jsp:include page="common/header.inc"></jsp:include>
    <table>
        <tr><td>Header</td></tr>
        <tr><td>Header2</td></tr>
        <tr>
            <td>
               <table>
                    <tr><td>districtCode</td><td>
                     <select name="orgType" class="selectBoxes">
                                 <%Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                                    String option= null;
                                    while (allDistricts.hasNext()) {
                                         KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();
                                         if(keyValueDTO.getDbTableCode().equals(search.getDistrictCode())){
                                            option  = "<option selected=\"true\" id=\""+keyValueDTO.getDbTableCode()+"\">"+keyValueDTO.getDisplayValue()+"</option>";                                             
                                         }
                                            option  = "<option id=\""+keyValueDTO.getDbTableCode()+"\">"+keyValueDTO.getDisplayValue()+"</option>";
                                        %><%=option%><%

                                    }
                                  %>

                    </td></tr>
                    <tr><td>division</td><td><input name="division" value="<%=search.getDistrictCode()%>"/> </td></tr>
                    <tr><td>gsn</td><td><input name="gsn" value="<%=search.getDistrictCode()%>"/> </td></tr>
                    <tr><td>owner</td><td><input name="owner" value="<%=search.getOwner()%>"/> </td></tr>
               </table>
            </td>
        </tr>

    </table>


  </body>
</html>
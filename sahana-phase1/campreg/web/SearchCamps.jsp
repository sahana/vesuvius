<%@ page import="org.campdb.db.DataAccessManager,
                 org.campdb.util.CAMPDBConstants,
                 org.campdb.business.User,
                 java.util.List,
                 java.util.LinkedList,
                 java.util.Iterator,
                 org.campdb.util.LabelValue,
                 org.campdb.business.CampTO,
                 org.campdb.util.StringUtil,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 java.util.ArrayList"%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>

<html>
<header>
  <title>:: Sahana ::</title>
  <script>

   <%
       User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
       if(user == null){
       request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
       response.sendRedirect("error.jsp");
     }
  %>
  
 <% DataAccessManager dm = new DataAccessManager(); %>

 <%List listcode;
     for (int j = 1;j < 10; j++) {
         %>var provCode<%=j%> = new Array( <%
        listcode = dm.listDistrictwithProvince(""+j);
         for (int i = 0; i <listcode.size(); i++) {
           if (i==0){
               out.print("\"" + ((LabelValue)listcode.get(i)).getValue() +"\"");
           }else{
              out.print("," + "\""+((LabelValue)listcode.get(i)).getValue() +"\"" );
         }
          }
             %>);
        var prov<%=j%> = new Array( <%
        for (int i = 0; i <listcode.size(); i++) {
          if (i==0){
           out.print("\"" + ((LabelValue)listcode.get(i)).getLabel() +"\"");
         }else{
          out.print("," + "\""+((LabelValue)listcode.get(i)).getLabel() +"\"" );
        }
       }
         %>);
         <%}
             out.println();
 %>
 <%List divlistCode;
     List alldisCode = dm.listDistrictsOrderbyProvince();
     String disNameCode;
     for (int j = 0 ;j < alldisCode.size(); j++) {
             %>var districtCode<%=j%> = new Array( <%
                 disNameCode =((LabelValue)alldisCode.get(j)).getLabel();
               divlistCode = dm.listDivisionsforDistrcit(disNameCode);
             for (int i = 0; i <divlistCode.size(); i++) {
               if (i==0){
                   out.print("\"" + ((LabelValue)divlistCode.get(i)).getValue() +"\"");
               }else{
                  out.print("," + "\""+((LabelValue)divlistCode.get(i)).getValue() +"\"" );
             }
           }
                 %>);
          var district<%=j%> = new Array( <%
          for (int i = 0; i <divlistCode.size(); i++) {
           if (i==0){
               out.print("\"" + ((LabelValue)divlistCode.get(i)).getLabel() +"\"");
           }else{
               out.print("," + "\""+((LabelValue)divlistCode.get(i)).getLabel() +"\"" );
          }
        }
         %>);
         <%
     }
             out.println();
 %>

  function listDistrict(){
     var provincecode = document.searchCamps.provinceCode.value;
     var optionList = document.searchCamps.districtId.options;
     optionList.length = 0;
     var divisionList = document.searchCamps.divisionId.options;
     divisionList.length = 0;
     var prov = eval("prov"+provincecode);
     var tempproveCode = eval("provCode"+provincecode);
     for (i=0;i< prov.length ;i++){
      var option = new Option(prov[i],tempproveCode[i]);
      optionList.add(option,i);

<%--      optionList.options[i] = new Option(prov[i],tempproveCode[i]);--%>
     }
   }

 function listDivisions(){
      var provincecode = document.searchCamps.provinceCode.value;
      var distrcictCode = document.searchCamps.districtId.selectedIndex ;
      var divisionList = document.searchCamps.divisionId.options;
      divisionList.length =0;
      var divCode = 0;
      for(j=0 ; j < provincecode-1 ; j++){
         switch (parseInt(j)) {
                  case 0:  divCode = divCode + prov1.length ; break;
                  case 1:  divCode = divCode + prov2.length ; break;
                  case 2:  divCode = divCode + prov3.length ; break;
                  case 3:  divCode = divCode + prov4.length ; break;
                  case 4:  divCode = divCode + prov5.length ; break;
                  case 5:  divCode = divCode + prov6.length ; break;
                  case 6:  divCode = divCode + prov7.length ; break;
                  case 7:  divCode = divCode + prov8.length ; break;
                  case 8:  divCode = divCode + prov9.length ; break;

              }
      }
      divCode = divCode + parseInt(distrcictCode);

      var divisions =eval("district" + divCode);
      var tempdivisionCode =eval("districtCode" + divCode);
      for (i=0;i< divisions.length ;i++){
          var option = new Option(divisions[i],tempdivisionCode[i]);
          divisionList.add(option,i);
<%--          divisionList.options[i] = new Option(divisions[i],tempdivisionCode[i]);--%>
      }
    }


  </script>
 <link href="comman/style.css" rel="stylesheet" type="text/css">

</header>


<body topmargin="0" leftmargin="0">

        <jsp:include page="comman/header.inc"></jsp:include>

   <%
      List  districts = null;


//       = (List) application.getAttribute("districts");
  %>



        <table width="100%" border="0" cellspacing="0" cellpadding="0">
        <tr>
        <td>

        <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left">
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="InsertCamps.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add
                    Camp</font></a>&nbsp;&nbsp;</td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td width="100%" height="23" align="right" background="images/BannerBG.jpg" bgcolor="#000099" class="statusBar"><a href="LogOff.jsp" style="text-decoration:none"><font color="#000000">Log
                    off&nbsp;&nbsp;&nbsp;&nbsp;</font></a></td>
            </tr>
            </table>

          </td>
          </tr>
        </table>
<%--  <tr>--%>
<%--    <td>--%>
        <table width="100%" border="0" cellspacing="0" cellpadding="0">
             <tr>
               <td background="images/HeaderBG.jpg" height="25" colspan="2" class="formTitle">Search Camps  </td>
             </tr>
         </table>


<table width="100%" border="0" cellspacing="0" cellpadding="0">
    <tr>
    <td width="117">&nbsp;</td>
    <td width="484">&nbsp;</td>
    </tr>
    <tr>
    <td colspan="2">
    <table width="100%" border="0" cellspacing="0" cellpadding="0">

    <tr>

    </tr>
<!-- -->
</table>

<table width="100%" width="100%" border="0">
  <tr>
  <td height="100%" width="100%" align="left" valign="top">

     <table>
        <form method="post" name="searchCamps" action="SearchCamps.jsp">
            <tr>
              <td align="right" class="formText">Camp Name :</td>
             <td vAlign="top" >
                 <input name="campName" size="16" maxlength="20" type="text" id="Code" class="textBox"  />
               </td>
            </tr>
            <tr>
              <td align="right" class="formText" type="submit">Province :</td>
              <td vAlign="top" >
                <select name="provinceCode"  class="selectBoxes" onchange="listDistrict();"  >
                    <option value="">&lt;Select&gt;</option>
                    <%
                      List provinces = (List) application.getAttribute("provinces");
                        for (Iterator iterator = provinces.iterator(); iterator.hasNext();) {
                            LabelValue province = (LabelValue) iterator.next();
                    %>
                            <option value="<%=province.getValue()%>"><%=province.getLabel()%></option>
                    <%
                        }
                    %>
                </select>
               </td>
            </tr>
            <tr>
              <td  align="right" class="formText">District :</td>
              <td vAlign="top" >
                <select name="districtId" class="selectBoxes" onchange="listDivisions();" >
                    <option value="">&lt;Select&gt;</option>
<%--                    <%--%>
<%--//                     List districts = (List) application.getAttribute("districts");--%>
<%--                        if(districts != null){--%>
<%--                          for (Iterator iterator = districts.iterator(); iterator.hasNext();) {--%>
<%--                              LabelValue district = (LabelValue) iterator.next();--%>
<%--                    %>--%>
<%--                            <option value="<%=district.getValue()%>"><%=district.getLabel()%></option>--%>
<%--                    <%--%>
<%--                          }--%>
<%--                        }--%>
<%--                    %>--%>
                </select>
               </td>
            </tr>
            <tr>
              <td  align="right" class="formText" >Division :</td>
              <td vAlign="top" >
                <select name="divisionId" class="selectBoxes" >
                    <option value="-1">&lt;Select&gt;</option>
<%--                    <%--%>
<%--                      List divisions = (List) application.getAttribute("divisions");--%>
<%--                        for (Iterator iterator = divisions.iterator(); iterator.hasNext();) {--%>
<%--                            LabelValue division = (LabelValue) iterator.next();--%>
<%--                    %>--%>
<%--                            <option value="<%=division.getValue()%>"><%=division.getLabel()%></option>--%>
<%--                    <%--%>
<%--                        }--%>
<%--                    %>--%>
                </select>
               </td>
            </tr>

            <tr>
              <td colspan="2" align="right" vAlign="top">&nbsp;</td>
            </tr>
            <tr>
              <td></td>
              <td>
                <input type="reset" name="clear" class="buttons" value="Clear"/>
                <input type="submit" class="buttons" name="doSearch" value="Search"/>
                </td>
            </tr>
     </table>
     </form>
<%
     if (request.getParameter("doSearch") != null) {
        DataAccessManager dataAccessManager = new DataAccessManager();
        String campName = request.getParameter("campName");
        String provinceCode = request.getParameter("provinceCode").length() <=0 ? null: request.getParameter("provinceCode");
        String districtId = request.getParameter("districtId").length() <= 0 ? null : request.getParameter("districtId");

        String divIdString = request.getParameter("divisionId");
        int divisionId = divIdString == null ? -1 : Integer.parseInt(divIdString);

        List result = dataAccessManager.searchCamps(campName, provinceCode, districtId, divisionId);
        if (result.size() > 0) {
%>

    <table>
    <tr>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    <td>&nbsp;</td>
    </tr>
    </table>
    <table width="100%" align="left" height="80%">
        <table cellspacing="4" >
            <tr>
                <td class="tableUp">Camp Name</td>
                <td class="tableUp">Area</td>
                <td class="tableUp">Province</td>
                <td class="tableUp">District</td>
                <td class="tableUp">Comment </td>
                <td class="tableUp">Edit </td>
            </tr>
            <%
                for (Iterator iterator = result.iterator(); iterator.hasNext();) {
                    CampTO campTO = (CampTO) iterator.next();
            %>
             <tr>
                <td class="tableDown"><a href="ViewCampDetails.jsp?campId=<%=campTO.getCampId()%>"><%=StringUtil.returnEmptyForNull(campTO.getCampName())%></a></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(campTO.getAreaName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(campTO.getProvienceName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(campTO.getDistrictName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(campTO.getCampComment())%> </td>
                <td class="tableDown"><a href="UpdateCamp.jsp?campId=<%=campTO.getCampId()%>">Edit&nbsp;<%=StringUtil.returnEmptyForNull(campTO.getCampName())%></a></td>
            </tr>
            <%

                }
            %>
        </table>
    </table>

<%      }
    }
%>

     </td>
   </tr>
   </table>
   <table width="100%" >

            <tr>
                <td class="formText" align="center">
                        <a href="Welcome.jsp">Camp Registry Home</a>
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




<%@ page import="java.util.LinkedList,
                 java.util.List,
                 java.text.SimpleDateFormat,
                 java.util.ArrayList,
                 java.util.Iterator,
                 org.housing.landreg.util.LabelValue,
                 org.housing.landreg.db.DataAccessManager,
                 org.sahana.share.db.DBConstants,
                 org.housing.landreg.business.LandTO,
                 org.housing.landreg.util.StringUtil"%>
<jsp:useBean id="newLand" scope="page" class="org.housing.landreg.business.LandTO" />
<jsp:setProperty name="newLand" property="*" />

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>


<title>:: Sahana :: Housing Scheme - Add Land</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="common/style.css" rel="stylesheet" type="text/css">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>

<script type="text/javascript">

<% DataAccessManager dm = new DataAccessManager(); %>

<%
     List listcode;
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
     List alldisCode = dm.listDistrict();
     String disNameCode;
     String dicCode;
     for (int j = 0 ;j < alldisCode.size(); j++) {
            disNameCode =((LabelValue)alldisCode.get(j)).getLabel();
            dicCode = ((LabelValue)alldisCode.get(j)).getValue();
             %>var districtCode<%=dicCode%> = new Array( <%
               divlistCode = dm.listDivisionsforDistrcit(disNameCode);
             for (int i = 0; i <divlistCode.size(); i++) {
               if (i==0){
                   out.print("\"" + ((LabelValue)divlistCode.get(i)).getValue() +"\"");
               }else{
                  out.print("," + "\""+((LabelValue)divlistCode.get(i)).getValue() +"\"" );
             }
           }
                 %>);
          var district<%=dicCode%> = new Array( <%
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
     var provincecode = document.newLand.provinceCode.value;
     var optionList = document.newLand.districtId.options;
     optionList.length = 0;
     var divisionList = document.newLand.divisionId.options;
     divisionList.length = 0;
     var prov = eval("prov"+provincecode);
     var tempproveCode = eval("provCode"+provincecode);
     for (i=0;i< prov.length ;i++){
      var option = new Option(prov[i],tempproveCode[i]);
      optionList.add(option,i);
     }
   }

 function listDivisions(){
      var provincecode = document.newLand.provinceCode.value;
      var distrcictCode = document.newLand.districtId.selectedIndex ;
      var divisionList = document.newLand.divisionId.options;
      divisionList.length =0;
<%--      var divCode = 0;--%>
      var divisionCode = document.newLand.districtId.value;
<%--      alert(divisionCode);--%>
<%--      for(j=0 ; j < provincecode-1 ; j++){--%>
<%--         switch (parseInt(j)) {--%>
<%--                  case 0:  divCode = divCode + prov1.length ; break;--%>
<%--                  case 1:  divCode = divCode + prov2.length ; break;--%>
<%--                  case 2:  divCode = divCode + prov3.length ; break;--%>
<%--                  case 3:  divCode = divCode + prov4.length ; break;--%>
<%--                  case 4:  divCode = divCode + prov5.length ; break;--%>
<%--                  case 5:  divCode = divCode + prov6.length ; break;--%>
<%--                  case 6:  divCode = divCode + prov7.length ; break;--%>
<%--                  case 7:  divCode = divCode + prov8.length ; break;--%>
<%--                  case 8:  divCode = divCode + prov9.length ; break;--%>
<%----%>
<%--              }--%>
<%--      }--%>
<%--      divCode = divCode + parseInt(distrcictCode);--%>

<%--      var divisions =eval("district" + divCode);--%>
<%--      var tempdivisionCode =eval("districtCode" + divCode);--%>
      var divisions =eval("district" + divisionCode);
      var tempdivisionCode =eval("districtCode" + divisionCode);
      for (i=0;i< divisions.length ;i++){
          var option = new Option(divisions[i],tempdivisionCode[i]);
          divisionList.add(option,i);
      }
    }

</script>
</head>

<body topmargin="0" leftmargin="0" onload="listDistrict();listDivisions()" >
    <table width="760" border="0" cellspacing="0" cellpadding="0">
        <td height="50" >
            <jsp:include page="../common/header.inc"></jsp:include>
        </td>
        <tr>
        <td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left">
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchLand.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search
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


<table>
     <tr>
        <form name="newLand" action="SearchLands.jsp"  >
            <table cellspacing="4"  >

                <tr>
                    <td align="right" valign="top"  class="formText"  >Land Name</td><td><input type="text" size="20" maxlength="49"  name="landName" class="textBox"  value="<jsp:getProperty name="newLand" property="landName" />">&nbsp;<small><font color="red">*</font></small></td>
                </tr>

                 <tr>
                      <td align="left" class="formText" type="submit">Province :</td>
                      <td vAlign="top" >
                        <select name="provinceCode"  class="selectBoxes" onchange="listDistrict();listDivisions()"   >
                            <option value="">&lt;Select&gt;</option>
                            <%
                              DataAccessManager daProvience =new DataAccessManager();
                              List provinces = (List) daProvience.listProvicences();
                              for (Iterator iterator = provinces.iterator(); iterator.hasNext();) {
                                    LabelValue province = (LabelValue) iterator.next();

                                   if(newLand.getProvinceCode()!= null){
                                                if(newLand.getProvinceCode().equals(province.getValue())) {
                                    %>
                                                    <option selected  value="<%=province.getValue()%>"><%=province.getLabel()%></option>
                                    <%
                                                    continue;
                                                }
                                            }
                            %>
                                    <option value="<%=province.getValue()%>"><%=province.getLabel()%></option>
                            <%
                                }
                            %>
                        </select>
                       </td>
                 </tr>

                    <tr>
                      <td  align="left" class="formText" type="submit">District :</td>
                      <td vAlign="top" >
                        <select name="districtId" class="selectBoxes" onchange="listDivisions();" >
                            <option value="">&lt;Select&gt;</option>
                        </select>
                       </td>
                    </tr>
                    <tr>
                      <td  align="left" class="formText" type="submit">Division :</td>
                      <td vAlign="top" >
                        <select name="divisionId" class="selectBoxes" >
                            <option value="-1">&lt;Select&gt;</option>
                      </select>
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

                                            if(newLand.getOwnedById()!= null){
                                                if(newLand.getOwnedById().equals(ownedBy.getValue())) {
                                    %>
                                                    <option selected  value="<%=ownedBy.getValue()%>"><%=ownedBy.getLabel()%></option>
                                    <%
                                                    continue;
                                                }
                                            }
                                    %>
                                            <option value="<%=ownedBy.getValue()%>"><%=ownedBy.getLabel()%></option>
                                    <%
                                        }
                                    %>
                                </select>
                                <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
                            </td>

                            <td  align="left" valign="top"   class="formText">Comments&nbsp;</td>
                            <td ><input type="text" size="50" maxlength="49"  name="ownedByComment" class="textBox"  value="<jsp:getProperty name="newLand" property="ownedByComment" />"> </td>


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

                                    if(newLand.getTermId()!= null){
                                                if(newLand.getTermId().equals(term.getValue())) {
                                    %>
                                                    <option selected  value="<%=term.getValue()%>"><%=term.getLabel()%></option>
                                    <%
                                                    continue;
                                                }
                                            }

                            %>
                                    <option value="<%=term.getValue()%>"><%=term.getLabel()%></option>
                            <%
                                }
                            %>
                        </select>
                        <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
                    </td>

               </tr>

                <tr>
                       <td  align="left" valign="top"   class="formText">Area Atleast&nbsp;</td>
                       <td ><input type="text" size="20" name="area" class="textBox"  value="<jsp:getProperty name="newLand" property="area" />"></td>
                       <td>
                           <select name="measurementTypeId" class="selectBoxes">
                               <option value="">&lt;Select&gt;</option>
                               <%
                                DataAccessManager dat1 = new DataAccessManager();
                                   // DataAccessManager da= new DataAccessManager();
                                 List measurementTypes = (List) dat1.listMeasurementTypes();
                                   for (Iterator iterator = measurementTypes.iterator(); iterator.hasNext();) {
                                       LabelValue measurementType = (LabelValue) iterator.next();

                                       if(newLand.getMeasurementTypeId()!= null){
                                             if(newLand.getMeasurementTypeId().equals(measurementType.getValue())) {
                                       %>
                                                  <option selected value="<%=measurementType.getValue()%>"><%=measurementType.getLabel()%></option>
                                       <%
                                                  continue;
                                             }
                                       }
                                       %>
                                       <option value="<%=measurementType.getValue()%>"><%=measurementType.getLabel()%></option>
                               <%
                                   }
                               %>
                           </select>
                           <!--<input size="100" type="text" name="divInfo" readonly="true" style="border:none;" class="textBox"></input>-->
                       </td>

                </tr>

                <tr>
                   <td>
                       <table>
                               <tr>
                                  <td></td>
                                  <td>
                                    <input type="reset" name="reset" value="Clear" class="buttons"/>
                                    <input type="submit" name="doSearch" value="Search" class="buttons" />
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
     </tr>

 </table>

 <%
     if (request.getParameter("doSearch") != null) {
        DataAccessManager dataAccessManager = new DataAccessManager();
        String landName =newLand.getLandName();//request.getParameter("landName");


//        String provinceCode = request.getParameter().length() <=0 ? null: request.getParameter("provinceCode");
//        String districtId = request.getParameter("districtId").length() <= 0 ? null : request.getParameter("districtId");

        String divisionId =newLand.getDivisionId();// request.getParameter("divisionId");
//        int divisionId = divIdString == null ? -1 : Integer.parseInt(divIdString);

        String ownedById= newLand.getOwnedById();
         String termId= newLand.getTermId();
        String area = newLand.getArea();
         String measurementTypeId = newLand.getMeasurementTypeId();


        List result = dataAccessManager.searchLands(landName, divisionId, ownedById,termId, area,measurementTypeId);
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
        <table cellspacing="2" >
            <tr>
                <td class="tableUp">Land Name</td>
                <td class="tableUp">Description</td>
                 <td class="tableUp">Province</td>
                <td class="tableUp">District</td>
                 <td class="tableUp">Division</td>
                 <td class="tableUp">Area</td>
                 <td class="tableUp">Unit</td>
                <td class="tableUp">Owned By</td>
                 <td class="tableUp">Term</td>
                <td class="tableUp">GPS Co-ordinates</td>
                <td class="tableUp">Edit </td>
            </tr>
            <%
                for (Iterator iterator = result.iterator(); iterator.hasNext();) {
                    LandTO landTO = (LandTO) iterator.next();
            %>
             <tr>
                <td class="tableDown"><a href="ViewCampDetails.jsp?campId=<%=landTO.getLandId()%>"><%=StringUtil.returnEmptyForNull(landTO.getLandName())%></a></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getDescription())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getprovinceName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getDistrictName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getdivisionName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getArea())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getMeasurementTypeName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getOwnedByName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getTermName())%></td>
                <td class="tableDown"><%=StringUtil.returnEmptyForNull(landTO.getGPS1())%>:&nbsp;
                                      <%=StringUtil.returnEmptyForNull(landTO.getGPS2())%>&nbsp;&nbsp;
                                      <%=StringUtil.returnEmptyForNull(landTO.getGPS3())%>:&nbsp;
                                      <%=StringUtil.returnEmptyForNull(landTO.getGPS4())%></td>

                <td class="tableDown"><a href="UpdateLand.jsp?campId=<%=landTO.getLandId()%>">Edit&nbsp;<%=StringUtil.returnEmptyForNull(landTO.getLandName())%></a></td>
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



  <jsp:include page="../common/footer.inc"></jsp:include>

</body>
</html>



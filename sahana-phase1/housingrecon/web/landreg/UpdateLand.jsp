
<%@ page import="java.util.LinkedList,
                 java.util.List,
                 java.text.SimpleDateFormat,
                 java.util.ArrayList,
                 java.util.Iterator,
                 org.housing.landreg.util.LabelValue,
                 org.housing.landreg.db.DataAccessManager,
                 org.housing.landreg.util.StringUtil,
                 org.housing.landreg.business.LandTO"%>
<jsp:useBean id="newLand" scope="page" class="org.housing.landreg.business.LandTO" />
<jsp:setProperty name="newLand" property="*" />
<%

    if (request.getParameter("reset") != null) {
       newLand.reset();
    }

    DataAccessManager dataAccessManager = new DataAccessManager();
    String Infracture_Ids="";
     List errors = new LinkedList();
    if (request.getParameter("doUpdate") == null) {  //data comes from the database
        if (request.getParameter("landId") == null) {
            response.sendRedirect("SearchLands.jsp");
            return;
        }
        int landID = 0;
        try {
            landID = Integer.parseInt(request.getParameter("landId"));
        } catch (NumberFormatException e) {
            e.printStackTrace();
            response.sendRedirect("SearchLands.jsp");
            return;
        }


        LandTO land = dataAccessManager.searchLand(landID);
        newLand.copyFrom(land);

        //reset the date
//        newLand.setUpdateDate(new java.util.Date());

        session.setAttribute("LAND_ID",new Integer(newLand.getLandId()));


    }

    // to retrieve values from Infracture list
    List InfracturesIds = (List) dataAccessManager.listAllInfractureNameForLandIds(newLand.getLandId());
    for (Iterator iterator = InfracturesIds.iterator(); iterator.hasNext();) {
    LabelValue Infracture = (LabelValue) iterator.next();
           Infracture_Ids =Infracture_Ids+"_"+Infracture.getLabel();
    }

    if (request.getParameter("doUpdate") != null) {
        errors.addAll(dataAccessManager.validateLandTOforInsert(newLand));

        int Id = ((Integer)session.getAttribute("LAND_ID")).intValue();
        if(errors.size()<=0) {
            try {
                newLand.setLandId(String.valueOf(Id));
                dataAccessManager.editLand(newLand);
                response.sendRedirect("ViewLand.jsp?landId=" + Id);
                return;
            } catch (Exception e) {
                errors.add(e.getMessage());
            }
        }
    }
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>


<title>:: Sahana :: Housing Scheme - Add Land</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="../common/style.css" rel="stylesheet" type="text/css">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script type="text/javascript" language="javascript" src="stringTokenizer.js"></script>
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

     if(provincecode!=""){
         var prov = eval("prov"+provincecode);
         var tempproveCode = eval("provCode"+provincecode);
         for (i=0;i< prov.length ;i++){
              var option = new Option(prov[i],tempproveCode[i]);
              optionList.add(option,i);
         }
     }
     document.newLand.districtId.value ="<%=newLand.getDistrictId()%>";
   }

 function listDivisions(){
      var provincecode = document.newLand.provinceCode.value;
      var distrcictCode = document.newLand.districtId.selectedIndex ;
      var divisionList = document.newLand.divisionId.options;
      divisionList.length =0;

      var divisionCode = document.newLand.districtId.value;

      if(divisionCode!=""){
          var divisions =eval("district" + divisionCode);
          var tempdivisionCode =eval("districtCode" + divisionCode);
          for (i=0;i< divisions.length ;i++){
              var option = new Option(divisions[i],tempdivisionCode[i]);
              divisionList.add(option,i);
          }
       }
       document.newLand.divisionId.value ="<%=newLand.getDivisionId()%>";
    }

      <%List subdivlistCode;
                   List suballdisCode = dm.listDivisions();
              //     String subdisNameCode;
                   String subdicCode;
                   for (int j = 0 ;j < suballdisCode.size(); j++) {
              //            subdisNameCode =((LabelValue)suballdisCode.get(j)).getLabel();
                          subdicCode = ((LabelValue)suballdisCode.get(j)).getValue();
                           %>var subDivCode<%=subdicCode%> = new Array( <%
                             subdivlistCode = dm.listGNDforDivisions(subdicCode);
                           for (int i = 0; i <subdivlistCode.size(); i++) {
                             if (i==0){
                                 out.print("\"" + ((LabelValue)subdivlistCode.get(i)).getValue() +"\"");
                             }else{
                                out.print("," + "\""+((LabelValue)subdivlistCode.get(i)).getValue() +"\"" );
                           }
                         }
                               %>);
                        var subDiv<%=subdicCode%> = new Array( <%
                        for (int i = 0; i <subdivlistCode.size(); i++) {
                         if (i==0){
                             out.print("\"" + ((LabelValue)subdivlistCode.get(i)).getLabel() +"\"");
                         }else{
                             out.print("," + "\""+((LabelValue)subdivlistCode.get(i)).getLabel() +"\"" );
                        }
                      }
                       %>);
                       <%
                   }
                           out.println();
               %>


    function listSubDivisions(){
        var subdivisionList = document.newLand.subDivisionId.options;
        subdivisionList.length =0;

        var subdivisionCode = document.newLand.divisionId.value;

        if(subdivisionCode!=""){
            var subdivisions =eval("subDiv" + subdivisionCode);
            var tempsubdivisionCode =eval("subDivCode" + subdivisionCode);
            for (i=0;i< subdivisions.length ;i++){
                var option = new Option(subdivisions[i],tempsubdivisionCode[i]);
                subdivisionList.add(option,i);
            }
         }
         document.newLand.subDivisionId.value ="<%=newLand.getSubDivisionId()%>";
      }


      function modify_boxes(to_be_checked,total_boxes){
        for ( i=0 ; i < total_boxes ; i++ ){
          if (to_be_checked){
             document.forms[0].infractureId[i].checked=true;
         }
         else{
            document.forms[0].infractureId[i].checked=false;
          }
        }
       }


     function setInfractureIds(total_boxes){
               var InfractureIds ="";
               var flag ="true";
               for ( i=0 ; i < total_boxes ; i++ ){
               if (document.forms[0].infractureId[i].checked==true){
               if (flag=="true")
               {
                  InfractureIds =InfractureIds+document.forms[0].infractureId[i].value;
                  flag ="false"
                }else{
                   InfractureIds =InfractureIds+ "_" +document.forms[0].infractureId[i].value;
                }
                }

              }
              document.newLand.InfractureIds.value =InfractureIds;
     }

     function ClickInfractureId()
     {

        var infractureIds = "<%=Infracture_Ids%>" ;
        var tokenizer = new StringTokenizer (infractureIds,"_");
         while (tokenizer.hasMoreTokens())
         {
            var id =tokenizer.nextToken();

            for ( i=0 ; i < 5 ; i++ )
            {
                if (id==document.forms[0].infractureId[i].value)
                {
                   document.forms[0].infractureId[i].checked=true;
                }
            }
      }
  }

</script>
</head>

<body topmargin="0" leftmargin="0" onload="listDistrict();listDivisions();listSubDivisions();ClickInfractureId();" >
    <table width="760" border="0" cellspacing="0" cellpadding="0">
        <td height="50" >
            <jsp:include page="../common/header.inc"></jsp:include>
        </td>
        <tr>
        <td>
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
            <tr align="left">
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><img src="images/Tab.gif" width="2" height="15"></td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="SearchLands.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Search Lands</font></a>&nbsp;&nbsp;</td>
                    <td nowrap background="images/BannerBG.jpg" class="statusBar"><a href="InsertLand.jsp" style="text-decoration:none"><font color="#000000">&nbsp;&nbsp;Add Land</font></a>&nbsp;&nbsp;</td>
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
               <td background="images/HeaderBG.jpg" colspan="2" class="formTitle">Update Land  </td>
             </tr>
         </table>


<table>
     <tr>
        <form name="newLand" action="UpdateLand.jsp"  >
            <table cellspacing="4"  >
                <%
                    if(errors.size() > 0) {
                         %>
                <tr>
                    <td colspan="3"class="formText" ><font color="red">Please correct the following errors</font><br></td>
                </tr>
                <%
                        //newLand.setNullValsToEmpty();
                        for (Iterator iterator = errors.iterator(); iterator.hasNext();) {
                            String error = (String) iterator.next();

                 %>
                <tr>
                    <td colspan="3"class="formText" ><font color="red"><li><%=error%></li></font><br></td>
                </tr>
                <%      }
                    }
                %>
<tr>
                   <td align="left" valign="center"  class="formText">Plan No &nbsp;<small><font color="red">*</font></small></td>
                   <td>
                   <table>
                       <tr>
                            <td><input type="text" size="10" maxlength="49"  name="planId" class="textBox"  value="<jsp:getProperty name="newLand" property="planId" />"><!--&nbsp;<small><font color="red">*</font></small> --></td>
                            <td align="left" valign="top"  class="formText"  >Land Name </td><td><input type="text" size="50" maxlength="49"  name="landName" class="textBox"  value="<jsp:getProperty name="newLand" property="landName" />"></td>
                       </tr>
                    </table>
                  </td>
                </tr>

                <tr>
                    <td  align="left" valign="center"  class="formText" >Description </td>
                       <td>

                         <input type="text"size=80 maxlength="150" name="description" class="textBox"  value="<jsp:getProperty name="newLand" property="description" />">
                       </td>
                </tr>

                 <tr>
                      <td align="left" class="formText" type="submit">Province &nbsp;<small><font color="red">*</font></small></td>
                      <td vAlign="top" >
                        <select name="provinceCode"  class="selectBoxes" onchange="listDistrict();listDivisions()" >
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
                       </select>&nbsp;<small><!--<font color="red">*</font></small>-->
                       </td>
                 </tr>

                <tr>
                      <td  align="left" class="formText" type="submit">District &nbsp;<small><font color="red">*</font></small></td>
                      <td vAlign="top" >
                        <select name="districtId" class="selectBoxes" onchange="listDivisions();" >
                            <option value="">&lt;Select&gt;</option>
                        </select> <!--&nbsp;<small><font color="red">*</font></small>-->
                       </td>
                    </tr>
                    <tr>
                      <td  align="left" class="formText" type="submit">Local Authority &nbsp;<small><font color="red">*</font></small></td>
                      <td vAlign="top" >
                        <select name="divisionId" class="selectBoxes" onchange="listSubDivisions();" >
                            <option value="-1">&lt;Select&gt;</option>
                      </select>&nbsp;<!--<small><font color="red">*</font></small>-->
                      </td>
               </tr>

                <tr>
                      <td  align="left" class="formText" type="submit">G N Division &nbsp;<small><font color="red">*</font></small></td>
                      <td vAlign="top" >
                        <select name="subDivisionId" class="selectBoxes" >
                            <option value="-1">&lt;Select&gt;</option>
                      </select>&nbsp;<!--<small><font color="red">*</font></small>-->
                       </td>

               </tr>

              <tr>
                           <td  align="left" valign="center"   class="formText">Land Type &nbsp;<small><font color="red">*</font></small></td>
                           <td>
                                             <!-- <select name="landTypeId" class="selectBoxes">

                                               <option value="">&lt;Select&gt;</option> -->
                                               <%
                                                DataAccessManager dat5 = new DataAccessManager();

                                                 List landTypeIds = (List) dat5.listLandType();
                                                   for (Iterator iterator = landTypeIds.iterator(); iterator.hasNext();) {
                                                       LabelValue landTypeId = (LabelValue) iterator.next();

                                                        if(newLand.getLandTypeId()!= null){
                                                           if(newLand.getLandTypeId().equals(landTypeId.getValue())) {
                                               %>
                                                         <!--      <option selected  value="<=landTypeId.getValue()%>"><=landTypeId.getLabel()%></option> -->
                                                         <input type="radio"  CHECKED name="landTypeId" value="<%=landTypeId.getValue()%>"> <%=landTypeId.getLabel()%>
                                               <%
                                                               continue;
                                                           }
                                                       }
                                               %>
                                                    <!--   <option value="<=landTypeId.getValue()%>"><=landTypeId.getLabel()%></option>  -->
                                                    <input type="radio" name="landTypeId" value="<%=landTypeId.getValue()%>"> <%=landTypeId.getLabel()%>
                                               <%
                                                   }
                                               %>
                                           <!--</select>&nbsp;<small><font color="red">*</font></small>-->


                            </td>
                            <!--<td><small><font color="red">*</font></small></td>-->
              </tr>

              <tr>
                           <td  align="left" valign="center"   class="formText">Infrastructure &nbsp;<small><font color="red">*</font></small></td>
                           <td>
                                             <!-- <select name="infractureId" class="selectBoxes">

                                               <option value="">&lt;Select&gt;</option>-->
                                               <%
                                                DataAccessManager dat6 = new DataAccessManager();

                                                 List Infractures = (List) dat6.listInfrastructures();
                                                   for (Iterator iterator = Infractures.iterator(); iterator.hasNext();) {
                                                       LabelValue Infracture = (LabelValue) iterator.next();
                                                       if(newLand.getInfractureId()!= null){
                                                           if(newLand.getInfractureId().equals(Infracture.getValue())) {
                                               %>
                                                               <!--<option selected  value="<=Infracture.getValue()%>"><=Infracture.getLabel()%></option>-->

<%--                                                               <input type="checkbox" CHECKED name="infractureId" value="<%=Infracture.getValue()%>" onclick="check('+ <%=Infracture.getValue()%>+',this )"> <%=Infracture.getLabel()%>--%>
                                                                    <input type="checkbox" CHECKED name="infractureId" value="<%=Infracture.getValue()%>"> <%=Infracture.getLabel()%>

                                               <%
                                                               continue;
                                                           }
                                                       }
                                               %>
                                                          <input type="checkbox" name="infractureId" value="<%=Infracture.getValue()%>" > <%=Infracture.getLabel()%>
<%--                                                       <input type="checkbox" name="infractureId" value="<%=Infracture.getValue()%>" onclick="check('+ <%=Infracture.getValue()%>+',this )"> <%=Infracture.getLabel()%>--%>
                                                       <!--<option value="<=Infracture.getValue()%>"><=Infracture.getLabel()%></option>-->
                                                       <!--<input type="radio" name="infractureId" value="<=Infracture.getValue()%>"><=Infracture.getLabel()%>-->

                                               <%
                                                   }
                                               %>
                           <INPUT TYPE=button NAME="CheckAll" VALUE="Check All" class="buttons" onClick="modify_boxes(true,5)">
                           <INPUT TYPE=button NAME="UnCheckAll" VALUE="UnCheck All" class="buttons" onClick="modify_boxes(false,5)">

                           </td>
                       <!--<td><small><font color="red">*</font></small></td>-->
              </tr>

              <tr>
                    <td  align="left" valign="center"   class="formText">Extent </td>

                    <td>

                    <table>
                       <tr>

                         <td> Acres &nbsp;
                         <input type="text" size="10" maxlength="49"  name="area" class="textBox"  value="<jsp:getProperty name="newLand" property="area" />">
                         &nbsp;&nbsp;&nbsp; Roods &nbsp;
                         <input type="text" size="10" maxlength="49"  name="area1" class="textBox"  value="<jsp:getProperty name="newLand" property="area1" />">
                         &nbsp;&nbsp;&nbsp; Perches &nbsp;
                         <input type="text" size="10" maxlength="49"  name="area2" class="textBox"  value="<jsp:getProperty name="newLand" property="area2" />">
                         </td>

                      </tr>
                    </table>

                    </td>

               </tr>

               <tr>
                            <td  align="left" valign="center"   class="formText">Ownership &nbsp;<small><font color="red">*</font></small> </td>
                            <td>
                              <table>
                                  <tr>
                                        <td>
                                              <table>
                                                          <tr>
                                                                <td>
                                                            <!--   <select name="ownedById" class="selectBoxes">

                                                                <option value="">&lt;Select&gt;</option> -->
                                                                <%
                                                                 DataAccessManager dat4 = new DataAccessManager();
                                                                    // DataAccessManager da= new DataAccessManager();
                                                                  List ownedBys = (List) dat4.listOwnedBy();
                                                                    for (Iterator iterator = ownedBys.iterator(); iterator.hasNext();) {
                                                                        LabelValue ownedBy = (LabelValue) iterator.next();

                                                                        if(newLand.getOwnedById()!= null){
                                                                            if(newLand.getOwnedById().equals(ownedBy.getValue())) {
                                                                %>
                                                                              <!--  <option selected  value="<=ownedBy.getValue()%>"><=ownedBy.getLabel()%></option> -->
                                                                                <input type="radio" CHECKED name="ownedById" value="<%=ownedBy.getValue()%>"> <%=ownedBy.getLabel()%>

                                                                <%
                                                                                continue;
                                                                            }
                                                                        }
                                                                %>
                                                                       <!-- <option value="<=ownedBy.getValue()%>"><=ownedBy.getLabel()%></option> -->
                                                                       <input type="radio" name="ownedById" value="<%=ownedBy.getValue()%>"> <%=ownedBy.getLabel()%>
                                                                <%
                                                                    }
                                                                %>
                                                           <!-- </select>&nbsp;<small><font color="red">*</font></small> -->

                                                                  </td>
                                                               </tr>
                                                        </table>

                                                        </td>
                       <!--                                 <td><small><font color="red">*</font></small></td> -->
                                                        <td  align="left" valign="center"   class="formText">Comments </td>
                                                        <td ><input type="text"  size=80 maxlength="150"  name="ownedByComment" class="textBox"  value="<jsp:getProperty name="newLand" property="ownedByComment" />"> </td>

                                     </tr>
                           </table>
                    </td>

               </tr>

               <tr>
                    <td  align="left" valign="top" class="formText">Terms &nbsp;<small><font color="red">*</font></small></td>

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

                    </td>

               </tr>

               <tr>
                    <td  align="left" valign="center"  class="formText" >GPS Coordinates </td>

                              <td>
                                <!-- <input type="text" size="10" maxlength="49"  name="GPS1" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS1" />">-->
                                 <select name="GPS1" class="selectBoxes" >
                                    <option value="-1">&lt;Select&gt;</option>
                                 <%
                                     if(newLand.getGPS1().equals("North")){
                                 %>
                                    <option Selected value="North">North</option>
                                    <option value="South">South</option>
                                 <%
                                     } else if(newLand.getGPS1().equals("South")){

                                 %>

                                    <option value="North">North</option>
                                    <option Selected value="South">South</option>
                                 <%
                                     } else {
                                 %>
                                     <option value="North">North</option>
                                     <option value="South">South</option>
                                 <%
                                     }
                                 %>
                                </select> &nbsp;

                                <input type="text" size="10" maxlength="49"  name="GPS2" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS2" />">

                               <!--  <input type="text" size="10" maxlength="49"  name="GPS3" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS3" />">-->
                               &nbsp;&nbsp;<select name="GPS3" class="selectBoxes" >
                                        <option value="-1">&lt;Select&gt;</option>
                                    <%
                                     if(newLand.getGPS3().equals("East")){
                                    %>
                                        <option Selected value="East">East</option>
                                        <option value="West">West</option>
                                    <%
                                     }
                                      else if(newLand.getGPS3().equals("West")){
                                    %>
                                        <option value="East">East</option>
                                        <option Selected value="West">West</option>
                                    <%
                                     } else {
                                    %>
                                         <option value="East">East</option>
                                         <option value="West">West</option>
                                    <%
                                     }
                                    %>
                                </select>&nbsp;
                                 <input type="text" size="10" maxlength="49"  name="GPS4" class="textBox"  value="<jsp:getProperty name="newLand" property="GPS4" />">
                               </td>

               </tr>


                <tr>
                     <td align="left" valign="center"  class="formText">Proposed use as per zoning plan </td>
                       <td>
                         <input type="text" size=80 maxlength="150" name="proposedUseAsPerZonPlan" class="textBox"  value="<jsp:getProperty name="newLand" property="proposedUseAsPerZonPlan" />">
                       </td>
                </tr>

                <tr>
                    <td  align="left" valign="center"  class="formText" >Remarks </td>
                       <td>
                         <input type="text"  size=80 maxlength="150"  name="remarks" class="textBox"  value="<jsp:getProperty name="newLand" property="remarks" />">
                       </td>
                </tr>


            </table>

            <table align =center>

                 <tr>
                       <td align =center> <input type="reset" name="reset" value="Clear" class="buttons"/>

                           <input type="submit" name="doUpdate" value="Update" class="buttons" onClick="setInfractureIds(5)">
                           <input type ="hidden" name ="infractureIds" id ="InfractureIds" value="<jsp:getProperty name="newLand" property="infractureIds" />">
                       </td>
                </tr>
            </table>


        </form>
     </tr>

 </table>

  <jsp:include page="../common/footer.inc"></jsp:include>

</body>
</html>



<%@ page import="java.math.BigDecimal,
                 org.burial.db.DataAccessManager,
                 org.burial.util.Constants,
                 org.burial.business.BurialSiteDetailTO,
                 org.burial.business.KeyValueDTO,
                 java.util.*"%>
<jsp:useBean id="addBurialDetailTO" scope="page" class="org.burial.business.BurialSiteDetailTO" />
<jsp:setProperty name="addBurialDetailTO" property="*" />
<html>
<header>
  <title>:: Sahana ::</title>
  <link href="common/style.css" rel="stylesheet" type="text/css">

 <%
     //we are good to go here
     DataAccessManager dataAccessManager = DataAccessManager.getInstance();
     ArrayList errorList = new ArrayList();

     Collection provinces =  dataAccessManager.getAllProvinces();
     KeyValueDTO provinceTO;
     boolean status = false;

     if (request.getSession()==null){
         throw new Exception("Session expired!");
     }else if(request.getSession().getAttribute(Constants.USER_INFO)==null){
         throw new Exception("This page needs Authentication!!!");
     }

     //do in submit
     if (request.getParameter("submit") != null) {
         //validate
         if (addBurialDetailTO.getDistrictCode()==null || (addBurialDetailTO.getDistrictCode().trim().length()<=0))
             errorList.add("District is required");
         if (addBurialDetailTO.getProvinceCode()==null || (addBurialDetailTO.getProvinceCode().trim().length()<=0) && !addBurialDetailTO.getProvinceCode().trim().equals("-1"))
             errorList.add("Province is required");
         if (addBurialDetailTO.getDivisionCode()==null || (addBurialDetailTO.getDivisionCode().trim().length()<=0))
             errorList.add("Division is required");
         if (addBurialDetailTO.getArea()==null || (addBurialDetailTO.getArea().trim().length()<=0) )
             errorList.add("Area is required");
         if (addBurialDetailTO.getSitedescription()==null || (addBurialDetailTO.getSitedescription().trim().length()<=0) )
             errorList.add("Site Description is required");
         if (addBurialDetailTO.getBurialdetail()==null || (addBurialDetailTO.getBurialdetail().trim().length()<=0) )
             errorList.add("Burial Details are required");
         if (addBurialDetailTO.getAuthorityName()==null || (addBurialDetailTO.getAuthorityName().trim().length()<=0) )
             errorList.add("Authority Name is required");
         if (addBurialDetailTO.getAuthorityPersonName()==null || (addBurialDetailTO.getAuthorityPersonName().trim().length()<=0) )
             errorList.add("Authority Person Name is required");
         if (addBurialDetailTO.getAuthorityPersonRank()==null || (addBurialDetailTO.getAuthorityPersonRank().trim().length()<=0) )
             errorList.add("Authority Persons Rank is required");

         //check for either the body count or the women,men,children count
         if (addBurialDetailTO.getBodyCountTotal()==0){
             //Todo put the check here
         }

          if (errorList.isEmpty()){
              status = dataAccessManager.insertSite(addBurialDetailTO);
          }
     }
        %>

 <script>
<%----%>
<%   List listcode;
     for (int j = 1;j < 10; j++) {
        %>var provCode<%=j%> = new Array( <%
        listcode = dataAccessManager.listDistrictwithProvince(""+j);
         for (int i = 0; i <listcode.size(); i++) {
           if (i==0){
               out.print("\"" + ((KeyValueDTO)listcode.get(i)).getDbTableCode() +"\"");
           }else{
              out.print("," + "\""+((KeyValueDTO)listcode.get(i)).getDbTableCode() +"\"" );
         }
          }
             %>);
          var prov<%=j%> = new Array( <%
        for (int i = 0; i <listcode.size(); i++) {
          if (i==0){
           out.print("\"" + ((KeyValueDTO)listcode.get(i)).getDisplayValue() +"\"");
         }else{
          out.print("," + "\""+((KeyValueDTO)listcode.get(i)).getDisplayValue() +"\"" );
        }
       }
         %>);
         <%}
             out.println();
 %>
 <%
         List divlistCode;
         List alldisCode = dataAccessManager.listDistrictsOrderbyProvince();
         String disNameCode;
         for (int j = 0 ;j < alldisCode.size(); j++) {
          %>var districtCode<%=j%> = new Array( <%
             disNameCode =((KeyValueDTO)alldisCode.get(j)).getDisplayValue();
             divlistCode = dataAccessManager.listDivisionsforDistrict(disNameCode);
             for (int i = 0; i <divlistCode.size(); i++) {
                 if (i==0){
                     out.print("\"" + ((KeyValueDTO)divlistCode.get(i)).getDbTableCode() +"\"");
                 }else{
                     out.print("," + "\""+((KeyValueDTO)divlistCode.get(i)).getDbTableCode() +"\"" );
                 }
             }
 %>);
            var district<%=j%> = new Array( <%
              for (int i = 0; i <divlistCode.size(); i++) {
               if (i==0){
                   out.print("\"" + ((KeyValueDTO)divlistCode.get(i)).getDisplayValue() +"\"");
                 }else{
                   out.print("," + "\""+((KeyValueDTO)divlistCode.get(i)).getDisplayValue() +"\"" );
                 }
             }
 %>);
         <%
         }
         out.println();

 %>





<%----%>
   function listDistrict(){
      var provincecode = document.burialDetail.provinceCode.value;
      var optionList = document.burialDetail.districtCode.options;
      var divisionList = document.burialDetail.divisionCode.options;
      optionList.length = 0;
      divisionList.length = 0;
      var provName = eval("prov"+provincecode);
      var proveCode = eval("provCode"+provincecode);
      for (i=0;i< provName.length ;i++){
       var option = new Option(provName[i],proveCode[i]);
       optionList.add(option,i);
      }
    }

  function listDivisions(){
       var provincecode = document.burialDetail.provinceCode.value;
       var distrcictCode = document.burialDetail.districtCode.selectedIndex ;
       var divisionList = document.burialDetail.divisionCode.options;
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
       }
     }

     function clearTextBox(txtBoxId){
            var obj = document.getElementById(txtBoxId);
            obj.value = "";
         }

     function showObject(id){
            var obj = document.getElementById(id);
            obj.style.display = "";
     }

     function hideObject(id){
            var obj = document.getElementById(id);
            obj.style.display = "none";
     }


     function clearTextBox(txtBoxId){
            var obj = document.getElementById(txtBoxId);
            obj.value = "";
     }

     function disableTextBox(txtBoxId){
           var obj = document.getElementById(txtBoxId);
            obj.disabled = true;
     }

     function clearAll(){
            clearTextBox("bodyCountTotal");
            clearTextBox("bodyCountMmen");
            clearTextBox("bodyCountWomen");
            clearTextBox("bodyCountChildren");

         }

     function totalSelected(){
            showObject("totalRow");
            hideObject("menRow");
            hideObject("womenRow");
            hideObject("childRow");
     }

         function breakDownSelected(){
                hideObject("totalRow");
                showObject("menRow");
                showObject("womenRow");
                showObject("childRow");
         }

         function changeTextBoxStatus(){
            var selectedValue = document.burialDetail.countSelect;

            if (selectedValue[0].checked){
              totalSelected();
            }else{
               breakDownSelected();
            }

            clearAll();
         }

         function validateTotal()
         {
            if(isNaN(document.burialDetail.bodyCountTotal.value))
            {
                alert("Please enter integer value");
                document.burialDetail.bodyCountTotal.focus();
            }

         }

         function validateChildren()
         {
            if(isNaN(document.burialDetail.bodyCountChildren.value))
            {
                alert("Please enter integer value");
                document.burialDetail.bodyCountChildren.focus();
                return;
            }
            calcTotal();
         }

         function validateMen()
         {
            if(isNaN(document.burialDetail.bodyCountMmen.value))
            {
                alert("Please enter integer value");
                document.burialDetail.bodyCountMmen.focus();
                return;
            }
            calcTotal();
         }

         function validateWomen()
         {
            if(isNaN(document.burialDetail.bodyCountWomen.value))
            {
                alert("Please enter integer value");
                document.burialDetail.bodyCountWomen.focus();
                return;
            }
            calcTotal();
         }

         function calcTotal(){
             var menCount =0;
             var womenCount =0;
             var childrenCount =0;
             menCount = parseInt(document.burialDetail.bodyCountMmen.value);

            womenCount = parseInt(document.burialDetail.bodyCountWomen.value);
            childrenCount = parseInt(document.burialDetail.bodyCountChildren.value);
            document.burialDetail.bodyCountTotal.value= menCount+womenCount+childrenCount;

         }



   </script>
 </script>
</header>
<body>
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

 <%  if (errorList.isEmpty()){
        if(status) {
 %>
         <p align="center" class="formText" >
               <h2>Your offer has been successfully added.!</h2>
         </p>
         </body>
            <jsp:include page="common/welcomefooter.inc"></jsp:include>
          </html>

            <%  return;
            }
        }else{
             %>

           <tr>
                <td align="left" vAlign="top" class="formText" colspan="2">Please correct the Following Errors
             <%
            //todo write the errors here
             for (int i = 0; i < errorList.size(); i++) {
                 %>
                   <li class="formText" ><font color="red"><%=errorList.get(i).toString()%></font></li>
                 <%
             }
           %></td>
            </tr> <%
        }

   %>
       <form method="post" name="burialDetail" action="AddBurialGround.jsp">
       <table border="0" width="100%" cellspacing="1" cellpadding="1">
            <tr>
               <td  align="right" vAlign="top" class="formText">Province : </td>
               <td  >
                   <select name="provinceCode" class="selectBoxes" onchange="listDistrict();listDivisions();">
                         <option value="-1">&lt;select&gt;</option>
                        <%
                            if (addBurialDetailTO.getProvinceCode()!=null){
                                 for (Iterator iterator = provinces.iterator(); iterator.hasNext();) {
                                    provinceTO = (KeyValueDTO)iterator.next();
                                    if (addBurialDetailTO.getProvinceCode().equals(provinceTO.getDbTableCode())) {
                                        %><option selected="true" value="<%=provinceTO.getDbTableCode()%>" ><%=provinceTO.getDisplayValue()%></option>  <%
                                    } else{
                                        %><option value="<%=provinceTO.getDbTableCode()%>" ><%=provinceTO.getDisplayValue()%></option>  <%
                                    }
                                }
                            } else{
                                for (Iterator iterator = provinces.iterator(); iterator.hasNext();) {
                                    provinceTO = (KeyValueDTO)iterator.next();
                                        %><option value="<%=provinceTO.getDbTableCode()%>" ><%=provinceTO.getDisplayValue()%></option>  <%
                                }
                            }
                           %>
                   </select>&nbsp;<small><font color="red">*</font></small>
                </td>
          </tr>
          <tr>
           <td align="right" vAlign="top" class="formText">District :</td>
                   <td>
                    <select name="districtCode" class="selectBoxes" onchange="listDivisions();" >
                    <%
                     if (addBurialDetailTO.getProvinceCode()!=null && addBurialDetailTO.getDistrictCode()!=null){
                            //load the specific district list. By this time it is assumed that the province is also loaded
                            List districtList = dataAccessManager.listDistrictwithProvince(addBurialDetailTO.getProvinceCode());
                            for (int i = 0; i < districtList.size(); i++) {
                                String dbTableCode = ((KeyValueDTO)districtList.get(i)).getDbTableCode();
                                String dbTableName = ((KeyValueDTO)districtList.get(i)).getDisplayValue();
                    %><option value="<%=dbTableCode%>" <% if (addBurialDetailTO.getDistrictCode().equals(dbTableCode)) out.print("selected=\"true\"");%>><%=dbTableName%></option>
                     <%  }
                        }else{
                    %>
                      <option value="-1">&lt;select&gt;</option>
                    <%
                        }
                    %>
                   </select>&nbsp;<small><font color="red">*</font></small>
                  </td>

           </tr>
           <tr>
           <td align="right" vAlign="top" class="formText">Division :</td>
                   <td >
                    <select name="divisionCode" class="selectBoxes">
                           <%
                               if (addBurialDetailTO.getProvinceCode()!=null && addBurialDetailTO.getDistrictCode()!=null && addBurialDetailTO.getDivisionCode()!=null){
                            //load the specific district list. By this time it is assumed that the province is also loaded
                            List divisionList = dataAccessManager.listDivisionsforDistrict(addBurialDetailTO.getDistrictCode());
                            for (int i = 0; i < divisionList.size(); i++) {
                                String dbTableCode = ((KeyValueDTO)divisionList.get(i)).getDbTableCode();
                                String dbTableName = ((KeyValueDTO)divisionList.get(i)).getDisplayValue();
                    %><option value="<%=dbTableCode%>" <% if (addBurialDetailTO.getDistrictCode().equals(dbTableCode)) out.print("selected=\"true\"");%>><%=dbTableName%></option>
                     <%  }
                        }else{
                    %>
                      <option value="-1">&lt;select&gt;</option>
                    <%
                        }
                         %>
                   </select>&nbsp;<small><font color="red">*</font></small>
                  </td>

           </tr>
           <tr>
             <td align="right" vAlign="top" class="formText">Area :</td>
             <td >
                  <textarea cols="50" name="area" rows="3" class="textBox"><%=addBurialDetailTO.getArea()==null?"":addBurialDetailTO.getArea()%></textarea>&nbsp;<small><font color="red">*</font></small>
             </td>
           </tr>

           <tr>
             <td align="right" vAlign="top" class="formText">Site Description :</td>
             <td>
                  <textarea cols="50" name="sitedescription" rows="3" class="textBox"><%=addBurialDetailTO.getSitedescription()==null?"":addBurialDetailTO.getSitedescription()%></textarea>&nbsp;<small><font color="red">*</font></small>
             </td>
           </tr>

           <tr>
             <td align="right" vAlign="top" class="formText">Burial Details :</td>
             <td >
                  <textarea cols="50" name="burialdetail" rows="3" class="textBox"><%=addBurialDetailTO.getBurialdetail()==null?"":addBurialDetailTO.getBurialdetail()%></textarea>&nbsp;<small><font color="red">*</font></small>
             </td>
           </tr>

           <tr>
           <td align="right" vAlign="top" class="formText">GPS Coordinates :</td>
           <td class="formText" align="left" >
            Longitude &nbsp; <input type="text" name="gpsLongitude" class="textBox" value="<%=addBurialDetailTO.getGpsLongitude()==null?"":addBurialDetailTO.getGpsLongitude()%>"/>&nbsp;&nbsp;Lattitude &nbsp; <input type="text" name="gpsLattitude" class="textBox" value="<%=addBurialDetailTO.getGpsLattitude()==null?"":addBurialDetailTO.getGpsLattitude()%>"/>
           </td>
           <td class="formText" align="left" >
                 &nbsp;
           </td>
           </tr>


           <tr>
           <td align="right" vAlign="top" class="formText">Count :</td>
             <td align="left" >

             </td>
           </tr>
     <tr>
                    <td  align="right" vAlign="top" class="formText"> Total </td><td><input type="radio" name="countSelect" class="formText" onclick="changeTextBoxStatus();" value="1"/></td>
                    </tr>
                    <tr>
                        <td  align="right" vAlign="top" class="formText">  Break Down </td><td><input type="radio" name="countSelect" class="formText" onclick="changeTextBoxStatus();" value="2"/></td>
                    </tr>
                    <tr id="totalRow" style="display:none" >
                        <td align="right" >Total</td><td align="left" vAlign="top" class="formText" ><input type="text" name="bodyCountTotal" class="textBox"  onChange="validateTotal();" value="<%=addBurialDetailTO.getBodyCountTotal()%>" ></input>&nbsp;<small><font color="red">*</font></small></td>
                    </tr>
                    <tr id="menRow" style="display:none">
                        <td align="right" >Men :</td><td  align="left" vAlign="top" class="formText"><input type="text" name="bodyCountMmen" class="textBox" onchange="validateMen();"  value="<%=addBurialDetailTO.getBodyCountMmen()%>"></input>&nbsp;<small><font color="red">*</font></small></td>
                    </tr>
                    <tr id="womenRow" style="display:none">
                        <td align="right" >Women :</td><td align="left" vAlign="top" class="formText"><input type="text" name="bodyCountWomen" class="textBox" onchange="validateWomen();"  value="<%=addBurialDetailTO.getBodyCountWomen()%>"></input>&nbsp;<small><font color="red">*</font></small></td>
                    </tr>
                    <tr id="childRow" style="display:none">
                         <td align="right" >Children :</td><td align="left" vAlign="top" class="formText"><input type="text" name="bodyCountChildren" class="textBox" onchange="validateChildren();"  value="<%=addBurialDetailTO.getBodyCountChildren()%>">&nbsp;<small><font color="red">*</font></small></input></td>
                    </tr>

<%----%>
<%----%>
           <tr>
           <td align="right" vAlign="top" class="formText" colspan="2" ><hr/></td>
           </tr>
           <tr>
           <td align="left" vAlign="top" class="formText"><strong>Authority Detail</strong></td>
           </tr>

           <tr>
           <td align="right" vAlign="top" class="formText">Person name :</td>
           <td>
                <input type="text" name="authorityPersonName" class="textBox" value="<%=addBurialDetailTO.getAuthorityPersonName()==null?"":addBurialDetailTO.getAuthorityPersonName()%>"/>&nbsp;<small><font color="red">*</font></small>
           </td>
           </tr>

            <tr>
           <td align="right" vAlign="top" class="formText">Authority Name :</td>
           <td>
                <input type="text" name="authorityName" class="textBox" value="<%=addBurialDetailTO.getAuthorityName()==null?"":addBurialDetailTO.getAuthorityName()%>"/>&nbsp;<small><font color="red">*</font></small>
           </td>
           </tr>

           <tr>
           <td align="right" vAlign="top" class="formText">Rank :</td>
           <td>
                <input type="text" name="authorityPersonRank" class="textBox" value="<%=addBurialDetailTO.getAuthorityPersonRank()==null?"":addBurialDetailTO.getAuthorityPersonRank()%>"/>&nbsp;<small><font color="red">*</font></small>
           </td>
           </tr>

           <tr>
           <td align="right" vAlign="top" class="formText">Reference :</td>
           <td>
                <input type="text" name="authorityReference" class="textBox" value="<%=addBurialDetailTO.getAuthorityReference()==null?"":addBurialDetailTO.getAuthorityReference()%>"/>&nbsp;
           </td>
           </tr>
<tr>
            </tr>
            <tr>
              <td></td>
                 <td>
                  <input name="submit" type="submit" value=" Save " class="buttons" >
                  <input name="reset" type="reset" value=" Clear " class="buttons" >
                  </td>
               </tr>
             </table>
        </form>
        <jsp:include page="common/welcomefooter.inc"></jsp:include>
        <jsp:include page="common/footer.inc"></jsp:include>
        </body>

  </html>




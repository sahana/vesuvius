<%@ page import="org.sahana.share.utils.KeyValueDTO,
                 java.util.ArrayList,
                 java.util.Iterator,
                 java.util.Collection,
                 org.damage.db.DataAccessManager,
                 org.damage.db.DBConstants"%>


<jsp:useBean id="house" scope="request" class="org.damage.business.DamagedHouseTO" />
<jsp:setProperty name="house" property="*" />
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

     <script>

     function add()
    {
        if(document.tsunamiAddDamagedHouse.inputVal.value != ""  ){

            document.tsunamiAddDamagedHouse.damageType.value += document.tsunamiAddDamagedHouse.inputVal.value+",";
            document.tsunamiAddDamagedHouse.inputVal.value = "";
        }else {
            for (var i = 0; i < document.tsunamiAddDamagedHouse.choiseList.length; i++) {
                if(document.tsunamiAddDamagedHouse.choiseList.options[i].selected){
                	var newValue = document.tsunamiAddDamagedHouse.choiseList.options[i].value;
                    if((document.tsunamiAddDamagedHouse.damageType.value.indexOf(newValue+",")) != -1){
                        var confirm = window.confirm("You have already added "+newValue + ". Do you still want to add it again ?");
                        if(confirm){
                        	document.tsunamiAddDamagedHouse.damageType.value += newValue+",";
                        }
                    }else {
                   document.tsunamiAddDamagedHouse.damageType.value += document.tsunamiAddDamagedHouse.choiseList.options[i].value+",";
                   }
                }
            }
        }
    }



    function minus()
    {
          var inValue;
        if(document.tsunamiAddDamagedHouse.inputVal.value != ""){
            inValue = document.tsunamiAddDamagedHouse.inputVal.value+","  ;
        }else {
            for (var i = 0; i < document.tsunamiAddDamagedHouse.choiseList.length; i++) {

                if(document.tsunamiAddDamagedHouse.choiseList.options[i].selected){

                   inValue =  document.tsunamiAddDamagedHouse.choiseList.options[i].value;
                }
            }
        }
        var outValue = document.tsunamiAddDamagedHouse.damageType.value;
        var startIndex = outValue.indexOf (inValue);
        if(outValue.indexOf (inValue,0) != -1){
        var endIndex = startIndex + inValue.length+1;
        outValue = outValue.substring (0,startIndex) + outValue.substring(endIndex,outValue.length);
        document.tsunamiAddDamagedHouse.damageType.value = outValue;
        document.tsunamiAddDamagedHouse.inputVal.value="";
        }

    }


  </script>


     <link href="common/style.css" rel="stylesheet" type="text/css">





  </head>

  <body>

   <jsp:include page="common/header.inc"></jsp:include>
     <%
                 DataAccessManager dataAccessManager = new DataAccessManager();

                   boolean status = false;
                   String  message  = null;

             /**
              * This is where the form will be saved.
              */
                if (request.getParameter("submit") != null) {

                    String districtString = request.getParameter("district");
                    Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                    while(allDistricts.hasNext()){
                        KeyValueDTO dto = (KeyValueDTO)allDistricts.next();
                        if(dto.getDisplayValue().equalsIgnoreCase(districtString))
                            house.setDistrictCode((String)dto.getDbTableCode());
                    }

                    status = dataAccessManager.addDamagedHouse(house);
                     message = "Your oraganizations information updated successfully !!";
                      System.out.println("ddd"+house.getInsured());




        if(status) {

        %>
        <p align="center" class="formText" >
               <h2>You have been successfully registered.!</h2>
         </p>
  <%
 session.invalidate();
 } else {
      response.sendRedirect("error.jsp");
 }
%>
     </body>
      <jsp:include page="common/welcomefooter.inc"></jsp:include>
     <jsp:include page="common/footer.inc"></jsp:include>
  </html>
<%
            return;
            }
    
%>

   <form method="post" name="tsunamiAddDamagedHouse" action="AddDamagedHouse.jsp">
             <table border="0" width="100%" cellspacing="1" cellpadding="1">

              <tr>
                  <td align="right" vAlign="top" class="formText">District : </td>
                  <td>
                        <select name="district" class="selectBoxes">
                                 <%Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                                    String option= null;
                                    while (allDistricts.hasNext()) {
                                         KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();
                                         option  = "<option id=\""+keyValueDTO.getDbTableCode()+"\">"+keyValueDTO.getDisplayValue()+"</option>";
                                        %><%=option%><%

                                    }
                                  %>

                        </select>&nbsp;<small><font color="red">*</font></small>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Divsion : </td>
                  <td>
                     <input class="textBox" name="division" maxlength="99" size="38" type="text" id="division">&nbsp;<small><font color="red">*</font></small>

                   </td>
             </tr>
             <tr>
                  <td align="right" vAlign="top" class="formText">GSN : </td>
                  <td>
                     <input class="textBox" name="gsn" maxlength="99" size="38" type="text" id="gsn">&nbsp;<small><font color="red">*</font></small>
                   </td>
             </tr>
             <tr>
                  <td align="right" vAlign="top" class="formText">Name of The House Owner : </td>
                  <td>
                     <input class="textBox" name="owner" maxlength="99" size="38" type="text" id="owner">
                   </td>
             </tr>


             <tr>
                  <td align="right" vAlign="top" class="formText">Address : </td>
                  <td>
                     <input class="textBox" name="address"  type="text" id="city">
                   </td>
             </tr>

             <tr>
                            <td align="right" vAlign="top" class="formText">Distance From Sea : </td>
                                     <td>
                                        <input class="textBox" name="distanceFromSea"  type="text" id="distanceFromSea">&nbsp;<small><font color="red">*</font></small>
                                      </td>
             </tr>


             <tr>
                  <td align="right" vAlign="top" class="formText">Floor Area : </td>
                  <td>
                     <input class="textBox" name="floorArea" type="text" id="floorArea">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Number of Stories : </td>
                  <td>
                     <select name="noOfStories" class="selectBoxes">
                        <option>1</option>
                        <option>2</option>
                        <option>3</option>
                        <option>4</option>
                        <option>5</option>
                     </select>
                   </td>
             </tr>

              <tr>
                  <td align="right" vAlign="top" class="formText">Type of Ownership : </td>
                  <td>
                  <select name="typeOfOwnership" class="selectBoxes">
                  <%
                      String[] type = DBConstants.OWNERSHIP_TYPE;
                      for(int i=0; i<type.length; i++){
                        %><option><%=type[i]%></option>

                          <%
                      }
                  %>

                  </select>
                  </td>
             </tr>

              <tr>
                  <td align="right" vAlign="top" class="formText">Number of Residents : </td>
                  <td>
                     <input class="textBox" name="noOfResidents" type="text" id="noOfResidents">
                   </td>
             </tr>

              <tr>
                  <td align="right" vAlign="top" class="formText">Type of Construction : </td>
                  <td>
                  <select name="typeOfConstruction" class="selectBoxes">
                  <%
                      String[] construction = DBConstants.CONSTRUCTION_TYPE;
                      for(int i=0; i<construction.length; i++){
                        %><option><%=construction[i]%></option>

                          <%
                      }
                  %>

                  </select>
                  </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText"> House Tax Number (Varipanam) : </td>
                  <td>
                     <input class="textBox" name="propertyTaxNo" type="text" id="propertyTaxNo">
                   </td>
             </tr>


             <tr>
                  <td align="right" vAlign="top" class="formText">Estimated Value of House in Rupees (Before the Damage) : </td>
                  <td>
                     <input class="textBox" name="totalValue" type="text" id="totalDamagedCost">
                   </td>
             </tr>
            <tr>
                  <td align="right" vAlign="top" class="formText">Estimated Damage in Rupees : </td>
                  <td>
                     <input class="textBox" name="totalDamagedCost" type="text" id="totalDamagedCost">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Floor area of the House : </td>
                  <td>
                     <input class="textBox" name="floorArea" type="text" id="landArea">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">If your house got damaged, do you want to be relocated ? : </td>
                  <td>
                     <input type="radio" name="relocate" class="formText"  value="true"
                     <%="checked=\"true\""

                     %>
                    >yes</input>


                    <input type="radio" name="relocate" class="formText"  value="false"
                     <%

                     %>
                     >no</input>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Is house Insured? : </td>
                  <td>
                     <input type="radio" name="insured" class="formText"  value="true"
                     <%

                     %>
                    >yes</input>


                    <input type="radio" name="insured" class="formText"  value="false"
                     <%="checked=\"true\""

                     %>
                    >no</input>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Type of Damage : </td>
                <td>
                    <table  border="0"  cellspacing="0" cellpadding="0">
                        <tr>

                            <td vAlign="top" align="left" >
<%--                                <input type="formText"  col="5" style="width: 150px;" name="inputVal" value="">--%>
                                <textarea cols="15"  name="inputVal" rows="3"></textarea>
                            </td>
                            <td vAlign="top" align="left">
                                <INPUT  type = "button" name="click" onClick="add();" value="Add      -->   " class="buttons" >
                            </td>
                            <td vAlign="top" align="left" >
                               <textarea cols="15" readonly="true" name="damageType" rows="3"></textarea>
                            </td>

                        </tr>
                        <tr>
                            <td vAlign="top" align="left">
                                <select  name="choiseList" size="5"  style="width: 140px;">
                                    <%
                                        String[] damage = DBConstants.DAMAGE_TYPE;
                                        for(int i=0; i<damage.length; i++){
                                    %>
                                        <option value="<%=damage[i]%>"><%=damage[i]%></option>
                                    <%
                                      }
                                    %>
                                </select>
                            </td>
                            <td vAlign="top" align="left">
                                <INPUT   type = "button"  name="click" onClick="minus();" value="<--  Remove" class="buttons">
                            </td>
                        </tr>
                    </table>

                </td>
            </tr>

            <tr>
                  <td align="right" vAlign="top" class="formText">Comments </td>
                  <td>
                     <textarea  cols="38"  name="comments" rows="5"></textarea>
                   </td>
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
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




     <link href="common/style.css" rel="stylesheet" type="text/css">

     <%
             DataAccessManager dataAccessManager = new DataAccessManager();

               boolean status = false;
               String  message  = null;
                     
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
                  System.out.println("ddd"+status);

            }

          %>




  </head>

  <body>

   <jsp:include page="common/header.inc"></jsp:include>


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
                  <td align="right" vAlign="top" class="formText">Distance From Sea : </td>
                  <td>
                     <input class="textBox" name="distance"  type="text" id="distance">&nbsp;<small><font color="red">*</font></small>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Number and Street : </td>
                  <td>
                     <input class="textBox" name="noAndStreet" maxlength="99" size="38" type="text" id="noAndStreet">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">City : </td>
                  <td>
                     <input class="textBox" name="city"  type="text" id="city">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Current Address : </td>
                  <td>
                     <input class="textBox" name="currentAddress" maxlength="99" size="38" type="text" id="currentAddress">
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
                  <td align="right" vAlign="top" class="formText">Resident Incometax Number : </td>
                  <td>
                     <input class="textBox" name="propertyTaxNo" type="text" id="propertyTaxNo">
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
                     <input class="textBox" name="landArea" type="text" id="landArea">
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Do you like to get relocated : </td>
                  <td>
                     <input type="radio" name="relocate" class="formText"  value="yes"
                     <%="checked=\"true\""

                     %>
                    >yes</input>


                    <input type="radio" name="relocate" class="formText"  value="no"
                     <%

                     %>
                     >no</input>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Is house Insured : </td>
                  <td>
                     <input type="radio" name="insured" class="formText"  value="yes"
                     <%

                     %>
                    >yes</input>


                    <input type="radio" name="insured" class="formText"  value="no"
                     <%="checked=\"true\""

                     %>
                    >no</input>
                   </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Type of Construction : </td>
                  <td>
                  <select name="damageType" class="selectBoxes">
                  <%
                      String[] damage = DBConstants.DAMAGE_TYPE;
                      for(int i=0; i<damage.length; i++){
                        %><option><%=damage[i]%></option>

                          <%
                      }
                  %>

                  </select>
                  </td>
             </tr>

             <tr>
                  <td align="right" vAlign="top" class="formText">Estimated Damage in Rupees : </td>
                  <td>
                     <textarea  cols="38" readonly="true" name="comments" rows="5"></textarea>
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
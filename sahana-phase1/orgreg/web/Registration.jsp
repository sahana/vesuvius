<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.*,
                 java.util.*"%>
<jsp:useBean id="orgReg" scope="request" class="org.erms.business.OrganizationRegistrationTO" />
<jsp:setProperty name="orgReg" property="*" />
<html>
<header>
  <title>:: Sahana ::</title>
  <script>
  function displayRow(){
    var orgvalue = document.tsunamiOrgReg.orgType.value;
    if(orgvalue=='NGO'){
         document.getElementById('hiddenRow').style.display = '';
     }else{
         document.getElementById('hiddenRow').style.display = 'none';
     }
   }

   function setAllCheckBoxes(check) {
     <%
        DataAccessManager dataAccessManager = new DataAccessManager();
         Collection allDistrictNamesCollection = dataAccessManager.getAllDistrictNames();
         Iterator districtNameIter = allDistrictNamesCollection.iterator();
     %>
   for (i=0;i<<%=allDistrictNamesCollection.size()%>;i++) {
         <%
             while (districtNameIter.hasNext()) {
                 String districtName = (String) districtNameIter.next();
              %>
              document.tsunamiOrgReg.<%=districtName%>.checked = check;

              <%
             }
         %>
          }

   }



    function add()
    {
        if(document.tsunamiOrgReg.inputVal.value != ""  ){

            document.tsunamiOrgReg.sectors.value += document.tsunamiOrgReg.inputVal.value+",";
            document.tsunamiOrgReg.inputVal.value = "";
        }else {
            for (var i = 0; i < document.tsunamiOrgReg.choiseList.length; i++) {
                if(document.tsunamiOrgReg.choiseList.options[i].selected){
                   document.tsunamiOrgReg.sectors.value += document.tsunamiOrgReg.choiseList.options[i].value+",";
                }
            }
        }
    }



    function minus()
    {
          var inValue;
        if(document.tsunamiOrgReg.inputVal.value != ""){
            inValue = document.tsunamiOrgReg.inputVal.value+","  ;
        }else {
            for (var i = 0; i < document.tsunamiOrgReg.choiseList.length; i++) {

                if(document.tsunamiOrgReg.choiseList.options[i].selected){

                   inValue =  document.tsunamiOrgReg.choiseList.options[i].value;
                }
            }
        }
        var outValue = document.tsunamiOrgReg.sectors.value;
        var startIndex = outValue.indexOf (inValue);
        if(outValue.indexOf (inValue,0) != -1){
        var endIndex = startIndex + inValue.length+1;
        outValue = outValue.substring (0,startIndex) + outValue.substring(endIndex,outValue.length);
        document.tsunamiOrgReg.sectors.value = outValue;
        document.tsunamiOrgReg.inputVal.value="";
        }

    }


  </script>
 <link href="comman/style.css" rel="stylesheet" type="text/css">

</header>

<body>

    <jsp:include page="comman/header.inc"></jsp:include>


<%
    List  messages = new LinkedList();
    if (request.getParameter("submit") != null) {
        orgReg.setStatus("false");

        boolean isSriLankan = "yes".equalsIgnoreCase(request.getParameter("isSriLankan")) ? true : false;
        orgReg.setIsSriLankan(isSriLankan);

        //messages.addAll(orgReg.validate());
        // get the selected working areas
        Iterator allDistrictNames = dataAccessManager.getAllDistrictNames().iterator();

       while (allDistrictNames.hasNext()) {
           String districtName =  (String) allDistrictNames.next();
           if ("on".equals(request.getParameter(districtName))) {
               orgReg.addWorkingArea(districtName);
           }

       }

        String sectorString = (String)request.getParameter("sectors");
        System.out.println(sectorString);
        while(sectorString.indexOf(',') != -1){
            String sector =sectorString.substring(0, sectorString.indexOf(','));
            sectorString =  sectorString.substring(sectorString.indexOf(','));
            orgReg.AddSectors(sector);
            sectorString =  sectorString.substring(1);

        }


        if (messages.size() <= 0) {
           boolean status =dataAccessManager.addOrganization(orgReg);


%>
<%
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
     <jsp:include page="comman/footer.inc"></jsp:include>
  </html>
<%
            return;
  }
    }
%>



    <form method="post" name="tsunamiOrgReg" action="Registration.jsp">
          <table border="0" width="100%" cellspacing="1" cellpadding="1">
   <tr>
              <td align="center" vAlign="top" colspan="2" class="formTitle" background="images/HeaderBG.jpg"  >Register Your Organization</td>

            </tr>
<% if (messages.size() > 0) { %>
            <tr>
              <td>&nbsp;</td>
              <td vAlign="top" align="right" class="formText" ><font size="2" color="red" >Please Correct Following Errors :</font><br/>

                    <%
                        for (Iterator iterator = messages.iterator(); iterator.hasNext();) {
                            String s = (String) iterator.next();
                    %>
                        <li><font size="1" color="red"><%=s%></font><br/></li>
                    <%
                        }
                    %>
                </td>
            </tr>
            <% } %>
            <tr>
             <td vAlign="top" class="formText" align="right" >Organization
                  Type :</td>
              <td>
              <!--    -->
                 <select  name="orgType" onchange="displayRow();" class="selectBoxes"  >
                 <%
                   String[] values={"Multilateral","Bilateral","NGO","Government","Private"};
                     for (int i = 0; i < values.length; i++) {
                        %> <option value="<%=values[i]%>"><%=values[i]%></option>
                        <%
                     }
                 %>

                 </select> &nbsp;<small><font color="red">*</font></small>
              <!--   -->
<%--                <input name="orgType" size="38" maxlength="10" type="text" id="Code" value="<jsp:getProperty name="orgReg" property="orgType" />">--%>
                </font>
                </td>
            </tr>

            <tr>
                <td>


                </td>
            </tr>
            <!--  -->
            <tr style="display:none" id="hiddenRow" >
              <td vAlign="top" class="formText" align="right">NGO Type :
                  </td>
              <td>
                 <select  name="ngoType" class="selectBoxes">
                 <%
                   String[] Ngovalues={"NGO","INGO","CBU"};
                     for (int i = 0; i < Ngovalues.length; i++) {
                        %> <option><%=Ngovalues[i]%></option>
                        <%
                     }
                 %>

                 </select>

                </td>
            </tr>

            <%--            --%>
<%--            <tr>--%>
<%--              <td vAlign="top" align="right" class="formText" >Organization--%>
<%--                  Code :</td>--%>
<%--              <td>--%>
<%--                <input class="textBox" name="orgCode" size="38" maxlength="10" type="text" id="Code" value="<jsp:getProperty name="orgReg" property="orgCode" />">&nbsp;<small><font color="red">*</font></small>--%>
<%--                </td>--%>
<%--            </tr>--%>
            <tr>
              <td vAlign="top" align="right" class="formText">Organization
                  Name :</td>
              <td>
                <input name="orgName" maxlength="99" size="38" type="text" id="Name" class="textBox" value="<%= (orgReg.getOrgName()==null)?"":orgReg.getOrgName()%>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td vAlign="top" class="formText" align="right" >Contact
                  Person :</td>
              <td>
                <input class="textBox" name="contactPerson" maxlength="99" size="38" type="text" id="contactperson" value="<%= (orgReg.getContactPerson()==null) ? "" : orgReg.getContactPerson() %>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td vAlign="top" class="formText" align="right" >Address :</td>
              <td>
                <textarea cols="38" name="orgAddress" rows="5" id="contact">
<%= (orgReg.getOrgAddress()==null) ? "" : orgReg.getOrgAddress() %>
</textarea>&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
            <td vAlign="top" class="formText" align="right" >Sector(s)</td>

            <td vAlign="top">
                <textarea cols="38" readonly="true" name="sectors" rows="1"></textarea>
            </td>



            </tr>
            <tr>
            <td align="right"></td>
            <td vAlign="top" >

                <input type="formText"  style="width: 100px;" name="inputVal" value="">
            </td>
<%--            <td >--%>
<%--                <INPUT type="button" name="click" onClick="add();" value="Add">--%>
<%--            </td>--%>
            </tr>
            <tr>
            <td align="right"></td>
            <td>
                <select name="choiseList" size="5"  style="width: 150px;">
                          <%
                              String[] sectorList = ERMSConstants.ERMSSectorNameConstants.SECTORS;
                              String selectStmt= null;
                              for(int i=0; i< sectorList.length; i++){

                                 selectStmt="<option value=\""+ sectorList[i]+"\">"+sectorList[i]+"</option>";
                                  %>
                                  <%=selectStmt%>
                                  <%
                              }

                          %>


                       </select>
                       <INPUT type = "button" name="click" onClick="add();" value="Add" class="buttons" >
                    <INPUT  type = "button" name="click" onClick="minus();" value="Remove" class="buttons">
                </td>
<%--                <td>--%>

<%--                </td>--%>

            </tr>

            <tr>
              <td align="right" vAlign="top" class="formText">Contact
                No :</td>
              <td>
                <input class="textBox" name="contactNumber" maxlength="99" size="38" type="text" id="contactno" value="<%= (orgReg.getContactNumber()==null) ? "" : orgReg.getContactNumber()%>">&nbsp;<small><font color="red">*</font></small>
               </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Email
                Address :</td>
              <td>
                <input name="emailAddress" maxlength="99" size="38" type="text" class="textBox" id="email" value="<%= (orgReg.getEmailAddress()==null) ? "" : orgReg.getEmailAddress() %>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Country
                of Origin :</td>
              <td>
              <select name="countryOfOrigin" class="selectBox">
	<option >Afghanistan</option>
	<option >Albania</option>
	<option >Algeria</option>
	<option >American Samoa</option>
	<option >Andorra</option>
	<option >Angola</option>
	<option >Anguilla</option>
	<option >Antigua and Barbuda</option>
	<option >Argentina</option>
	<option >Armenia</option>
	<option >Aruba</option>
	<option >Australia</option>
	<option >Austria</option>
	<option >Azerbaijan</option>
	<option >Bahamas</option>
	<option >Bahrain</option>
	<option >Bangladesh</option>
	<option >Barbados</option>
	<option >Belarus</option>
	<option >Belgium</option>
	<option >Belize</option>
	<option >Benin</option>
	<option >Bermuda</option>
	<option >Bhutan</option>
	<option >Bolivia</option>
	<option >Bosnia and Herzegowina</option>
	<option >Botswana</option>
	<option >Brazil</option>
	<option >Brunei Darussalam</option>
	<option >Bulgaria</option>
	<option >Burkina Faso</option>
	<option >Burundi</option>
	<option >Cambodia</option>
	<option >Cameroon</option>
    <option >Canada (Eastern)</option>
	<option >Canada (Western)</option>
    <option >Cape Verde</option>
	<option >Cayman Islands</option>
	<option >Central African Republic</option>
	<option >Chad</option>
	<option >Chile</option>
	<option >China</option>
	<option >Christmas Island</option>
	<option >Cocos (Keeling) Islands</option>
	<option >Colombia</option>
	<option >Comoros</option>
	<option >Congo</option>
	<option >Cook Islands</option>
	<option >Costa Rica</option>
	<option >Cote D Ivoire</option>
	<option >Croatia (Hrvatska)</option>
	<option >Cuba</option>
	<option >Cyprus</option>
	<option >Czech Republic</option>
    <option >Denmark</option>
	<option >Djibouti</option>
	<option >Dominica</option>
	<option >Dominican Republic</option>
	<option >Ecuador</option>
	<option >Egypt</option>
	<option >El Salvador</option>
	<option >Equatorial Guinea</option>
	<option > Eritrea</option>
	<option >Estonia</option>
	<option >Ethiopia</option>
	<option >Falkland (Malvinas) Islands</option>
	<option >Faroe Islands</option>
	<option >Fiji</option>
    <option >Finland</option>
    <option>France</option>
	<option >French Guiana</option>
	<option >French Polynesia</option>
	<option >Gabon</option>
	<option >Gambia</option>
	<option >Georgia</option>
    <option >Germany</option>
	<option >Ghana</option>
	<option >Gibraltar</option>
	<option >Greece</option>
	<option >Greenland</option>
	<option >Grenada</option>
	<option >Guadeloupe</option>
	<option >GUAM</option>
	<option >Guatemala</option>
	<option >Guinea</option>
	<option >Guinea-Bissau</option>
	<option >Guyana</option>
	<option >Haiti</option>
	<option >Holy See (Vatican city state)</option>
	<option >Honduras</option>
	<option >Hong Kong</option>
	<option >Hungary</option>
	<option >Iceland</option>
	<option >India</option>
	<option >Indonesia</option>
	<option >Iran</option>
	<option >Iraq</option>
	<option >Ireland</option>
	<option >Israel</option>
    <option >Italy</option>
    <option >Japan</option>
    <option >Jamaica</option>
	<option >Jordan</option>
	<option >Kazakhstan</option>
	<option >Kenya</option>
	<option >Kiribati</option>
	<option >North korea</option>
	<option >South korea</option>
	<option >Kuwait</option>
	<option >Kyrgyzstan</option>
	<option >Laos</option>
	<option >Latvia</option>
	<option >Lebanon</option>
	<option >Lesotho</option>
	<option >Liberia</option>
	<option >Libya</option>
	<option >Liechtenstein</option>
	<option >Lithuania</option>
	<option >Luxembourg</option>
	<option >Macau</option>
	<option >Macedonia</option>
	<option >Madagascar</option>
	<option >Malawi</option>
	<option >Malaysia</option>
	<option >Maldives</option>
	<option >Mali</option>
	<option >Malta</option>
	<option >Marshall Islands</option>
	<option >Martinique</option>
	<option >Mauritania</option>
	<option >Mauritius</option>
	<option >Mayotte</option>
	<option >Mexico</option>
	<option >Federated States of Micronesia</option>
	<option >Moldova</option>
	<option >Monaco</option>
	<option >Mongolia</option>
	<option >Montserrat</option>
	<option >Morocco</option>
	<option >Mozambique</option>
	<option >Myanmar</option>
	<option >Namibia</option>
	<option >Nauru</option>
	<option >Nepal</option>
    <option >Netherlands</option>
	<option >Netherlands Antilles</option>
	<option >New Caledonia</option>
	<option >New Zealand</option>
	<option >Nicaragua</option>
	<option >Niger</option>
	<option >Nigeria</option>
	<option >Niue</option>
	<option >Norfolk Island</option>
	<option >Northern Mariana Islands</option>
    <option >Norway</option>
	<option >Oman</option>
	<option >Pakistan</option>
	<option >Palau</option>
	<option >Panama</option>
	<option >Papua New Guinea</option>
	<option >Paraguay</option>
	<option >Peru</option>
	<option >Philippines</option>
	<option >Poland</option>
	<option >Portugal</option>
	<option >Puerto Rico</option>
	<option >Qatar</option>
	<option >Reunion</option>
	<option >Romania</option>
	<option >Russia</option>
	<option >Rwanda</option>
	<option >Saint Kitts and Nevis</option>
	<option >Saint Lucia</option>
	<option >Saint Vincent and Grenadines</option>
	<option >Samoa</option>
	<option >San Marino</option>
	<option >Sao Tome and Principe</option>
	<option >Saudi Arabia</option>
	<option >Senegal</option>
	<option >Seychelles</option>
	<option >Sierra leone</option>
	<option >Singapore</option>
	<option >Slovakia</option>
	<option >Slovenia</option>
	<option >Solomon Islands</option>
	<option >Somalia</option>
	<option >South Africa</option>
    <option >Spain</option>
	<option selected="true" >Sri Lanka</option>
	<option >St. Helena</option>
	<option >St. Pierre and Miquelon</option>
	<option >Sudan</option>
	<option >Suriname</option>
	<option >Svalbard and Jan Mayen Islands</option>
	<option >Swaziland</option>
    <option >Sweden</option>
	<option >Switzerland</option>
	<option >Syria</option>
	<option >Taiwan</option>
	<option >Tajikistan</option>
	<option >Tanzania, United Republic of</option>
	<option >Thailand</option>
	<option >Togo</option>
	<option >Tonga</option>
	<option >Trinidad and Tobago</option>
	<option >Tunisia</option>
	<option >Turkey</option>
	<option >Turkmenistan</option>
	<option >Turks and Caicos Islands</option>
	<option >Tuvalu</option>
	<option >Uganda</option>
	<option >Ukraine</option>
	<option >United Arab Emirates</option>
    <option>United Kingdom</option>
    <option >United States</option>
	<option >Uruguay</option>
	<option >Uzbekistan</option>
	<option >Vanuatu</option>
	<option >Venezuela</option>
	<option >Viet Nam</option>
	<option >Virgin Islands (British)</option>
	<option >Virgin Islands (U.S.)</option>
	<option >Wallis and Futuna Islands</option>
	<option >Western Sahara</option>
	<option >Yemen</option>
	<option >Yugoslavia</option>
	<option >Zaire</option>
	<option >Zambia</option>
	<option >Zimbabwe</option>
              </select>
                <font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Facilities
                Available :</td>
              <td>
                <textarea cols="38" name="facilitiesAvailable" rows="5" id="Facilities"><%= (orgReg.getFacilitiesAvailable()==null) ? "" : orgReg.getFacilitiesAvailable() %></textarea>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Operational Districts :</td>
              <td>
          <table border="0" width="100%" cellspacing="1" cellpadding="1">
                <%
                    Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                    int i=0;
                    while (allDistricts.hasNext()) {
                        KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();
                        if((i % 4)==0){
                %>
                <tr>
                    <td>
                        <input type="checkbox" name="<%=keyValueDTO.getDisplayValue()%>"><%=keyValueDTO.getDisplayValue()%></input>
                    </td>
                <%
                    }else {
                %>

                    <td>
                        <input type="checkbox" name="<%=keyValueDTO.getDisplayValue()%>"><%=keyValueDTO.getDisplayValue()%></input>
                    </td>

                <% }
                    if((i % 4)==3){
                %>
                    </tr>
                <%
                    }
                        i++;
                   }
                %>


                    <td>
                        <input name="checkAll" type="button" value=" Select All " class="buttons" onclick="setAllCheckBoxes(true);" ></input>
                        <input name="clearAll" type="button" value=" Clear All " class="buttons" onclick="setAllCheckBoxes(false);" ></input>
                    </td>


            </table>

                </td>

<%--                <td>--%>
<%--                 <button onClick="showDiv();">Add Areas</button>--%>
<%--                </td>--%>




            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Are you registered in Sri Lanka ? :</td>
              <td>
                <input name="isSriLankan" type="radio" value="yes">Yes</input>
                <input name="isSriLankan" type="radio" value="no">No</input>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Comments :</td>
              <td>
                <textarea name="comments" cols="38" rows="5" id="comments" ><%= (orgReg.getComments()==null) ? "" : orgReg.getComments() %></textarea>
                </td>
            </tr>
                 <tr>
<%--              <td align="center" vAlign="top" colspan="2" class="formText" ><strong>User Registration</strong></td>--%>

            </tr>

            <br/>
            <br/>

            <tr>
                   <td align="right" vAlign="top" class="formText">User Name :</td>
                   <td>
                   <input name="username" type="text" class="textBox" size="20" value="<%=orgReg.getUsername()==null?"":orgReg.getUsername()%>" >&nbsp;<small><font color="red">*</font></small>
                   </td>
            </tr>
            <tr>
                   <td align="right" vAlign="top" class="formText">Password :</td>
                   <td>
                   <input name="password" type="password" class="textBox" size="20" value="<%=orgReg.getPassword()==null?"":orgReg.getPassword()%>">&nbsp;<small><font color="red">*</font></small>
                  </td>
            </tr>
             <tr>
                   <td align="right" vAlign="top" class="formText" >Re Enter Password :</td>
                   <td>
                   <input name="passwordRe" type="password" class="textBox" size="20"  value="<%=orgReg.getPasswordRe()==null?"":orgReg.getPasswordRe()%>">&nbsp;<small><font color="red">*</font></small>
                  </td>
            </tr>
             <tr>
              <td colspan="2" align="right" vAlign="top">&nbsp;</td>
            </tr>
            <tr>
              <td></td>
              <td>
                <input name="submit" type="submit" value=" Save " class="buttons" >

                <input name="reset" type="reset" value=" Clear " class="buttons" >
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top">&nbsp;</td>
              <td align="center" ><small><font color="red">*</font></small> - Required field</td>
            </tr>
            <tr>
                 <td class="formText" align="center" colspan="2" ><a href="Index.jsp">Organization Registry Home</a></td>
            </tr>
             </table>
        </form>
       </body>

       <jsp:include page="comman/footer.inc"></jsp:include>

  </html>



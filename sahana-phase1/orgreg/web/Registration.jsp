<%@ page import="org.erms.db.DataAccessManager,
                 org.erms.util.ERMSConstants,
                 org.erms.business.*,
                 java.util.*,
                 org.erms.util.OrganizationPageHelper"%>
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
                	var newValue = document.tsunamiOrgReg.choiseList.options[i].value;
                    if((document.tsunamiOrgReg.sectors.value.indexOf(newValue+",")) != -1){
                        var confirm = window.confirm("You have already added "+newValue + ". Do you still want to add it again ?");
                        if(confirm){
                        	document.tsunamiOrgReg.sectors.value += newValue+",";
                        }
                    }else {
                   document.tsunamiOrgReg.sectors.value += document.tsunamiOrgReg.choiseList.options[i].value+",";
                   }
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
    String action = "";
    boolean globalControlDisable = false;

    if (request.getParameter("submit") != null) {
        orgReg.setStatus("false");

        boolean isSriLankan = "yes".equalsIgnoreCase(request.getParameter("isSriLankan")) ? true : false;
        orgReg.setIsSriLankan(isSriLankan);

        messages.addAll(orgReg.validate());
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
    } else if (request.getParameter("action") != null) {
            action = request.getParameter("action");
            globalControlDisable = ERMSConstants.IContextInfoConstants.ACTION_VIEW.equalsIgnoreCase(action);
    }

%>



    <form method="post" name="tsunamiOrgReg" action="Registration.jsp">
          <table border="0" width="100%" cellspacing="1" cellpadding="1">
          <%
              OrganizationPageHelper helper = new OrganizationPageHelper();
          %>
            <tr>
              <td align="center" vAlign="top" colspan="2" class="formTitle" background="images/HeaderBG.jpg"><%=helper.getHeaderMessage(action)%></td>
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
                 <select name="ngoType" class="selectBoxes">
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
              <%
                  String [] contry = {"Afghanistan",
	"Albania",
	"Algeria",
	"American Samoa",
	"Andorra",
	"Angola",
	"Anguilla",
	"Antigua and Barbuda",
	"Argentina",
	"Armenia",
	"Aruba",
	"Australia",
	"Austria",
	"Azerbaijan",
	"Bahamas",
	"Bahrain",
	"Bangladesh",
	"Barbados",
	"Belarus",
	"Belgium",
	"Belize",
	"Benin",
	"Bermuda",
	"Bhutan",
	"Bolivia",
	"Bosnia and Herzegowina",
	"Botswana",
	"Brazil",
	"Brunei Darussalam",
	"Bulgaria",
	"Burkina Faso",
	"Burundi",
	"Cambodia",
	"Cameroon",
    "Canada (Eastern)",
	"Canada (Western)",
    "Cape Verde",
	"Cayman Islands",
	"Central African Republic",
	"Chad",
	"Chile",
	"China",
	"Christmas Island",
	"Cocos (Keeling) Islands",
	"Colombia",
	"Comoros",
	"Congo",
	"Cook Islands",
	"Costa Rica",
	"Cote D Ivoire",
	"Croatia (Hrvatska)",
	"Cuba",
	"Cyprus",
	"Czech Republic",
    "Denmark",
	"Djibouti",
	"Dominica",
	"Dominican Republic",
	"Ecuador",
	"Egypt",
	"El Salvador",
	"Equatorial Guinea",
	" Eritrea",
	"Estonia",
	"Ethiopia",
	"Falkland (Malvinas) Islands",
	"Faroe Islands",
	"Fiji",
    "Finland",
    "France",
	"French Guiana",
	"French Polynesia",
	"Gabon",
	"Gambia",
	"Georgia",
    "Germany",
	"Ghana",
	"Gibraltar",
	"Greece",
	"Greenland",
	"Grenada",
	"Guadeloupe",
	"GUAM",
	"Guatemala",
	"Guinea",
	"Guinea-Bissau",
	"Guyana",
	"Haiti",
	"Holy See (Vatican city state)",
	"Honduras",
	"Hong Kong",
	"Hungary",
	"Iceland",
	"India",
	"Indonesia",
	"Iran",
	"Iraq",
	"Ireland",
	"Israel",
    "Italy",
    "Japan",
    "Jamaica",
	"Jordan",
	"Kazakhstan",
	"Kenya",
	"Kiribati",
	"North korea",
	"South korea",
	"Kuwait",
	"Kyrgyzstan",
	"Laos",
	"Latvia",
	"Lebanon",
	"Lesotho",
	"Liberia",
	"Libya",
	"Liechtenstein",
	"Lithuania",
	"Luxembourg",
	"Macau",
	"Macedonia",
	"Madagascar",
	"Malawi",
	"Malaysia",
	"Maldives",
	"Mali",
	"Malta",
	"Marshall Islands",
	"Martinique",
	"Mauritania",
	"Mauritius",
	"Mayotte",
	"Mexico",
	"Federated States of Micronesia",
	"Moldova",
	"Monaco",
	"Mongolia",
	"Montserrat",
	"Morocco",
	"Mozambique",
	"Myanmar",
	"Namibia",
	"Nauru",
	"Nepal",
    "Netherlands",
	"Netherlands Antilles",
	"New Caledonia",
	"New Zealand",
	"Nicaragua",
	"Niger",
	"Nigeria",
	"Niue",
	"Norfolk Island",
	"Northern Mariana Islands",
    "Norway",
	"Oman",
	"Pakistan",
	"Palau",
	"Panama",
	"Papua New Guinea",
	"Paraguay",
	"Peru",
	"Philippines",
	"Poland",
	"Portugal",
	"Puerto Rico",
	"Qatar",
	"Reunion",
	"Romania",
	"Russia",
	"Rwanda",
	"Saint Kitts and Nevis",
	"Saint Lucia",
	"Saint Vincent and Grenadines",
	"Samoa",
	"San Marino",
	"Sao Tome and Principe",
	"Saudi Arabia",
	"Senegal",
	"Seychelles",
	"Sierra leone",
	"Singapore",
	"Slovakia",
	"Slovenia",
	"Solomon Islands",
	"Somalia",
	"South Africa",
    "Spain",
	"Sri Lanka",
	"St. Helena",
	"St. Pierre and Miquelon",
	"Sudan",
	"Suriname",
	"Svalbard and Jan Mayen Islands",
	"Swaziland",
    "Sweden",
	"Switzerland",
	"Syria",
	"Taiwan",
	"Tajikistan",
	"Tanzania, United Republic of",
	"Thailand",
	"Togo",
	"Tonga",
	"Trinidad and Tobago",
	"Tunisia",
	"Turkey",
	"Turkmenistan",
	"Turks and Caicos Islands",
	"Tuvalu",
	"Uganda",
	"Ukraine",
	"United Arab Emirates",
    "United Kingdom",
    "United States",
	"Uruguay",
	"Uzbekistan",
	"Vanuatu",
	"Venezuela",
	"Viet Nam",
	"Virgin Islands (British)",
	"Virgin Islands (U.S.)",
	"Wallis and Futuna Islands",
	"Western Sahara",
	"Yemen",
	"Yugoslavia",
	"Zaire",
	"Zambia",
	"Zimbabwe"};
	          for (int i = 0; i < contry.length; i++) {
                  if(contry[i].equals("Sri Lanka")){
                    %> <option selected="true" ><%=contry[i]%></option>
                    <%
                  }else {
                        %> <option><%=contry[i]%></option>
                        <%
                  }
              }
         %>
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



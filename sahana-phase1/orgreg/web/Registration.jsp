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
  <script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
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
 <%
  if (request.getParameter("isEdit") != null) {
    if (request.getParameter("isEdit").equalsIgnoreCase("Y"))
    {
        request.setAttribute("turl", "Welcome.jsp");
        request.setAttribute("modNo", "4");
        request.setAttribute("accessLvl", "EDIT");
%>
<%@include file="/admin/accessControl/AccessControl.jsp" %>
<%
    }
  }
%>


    <jsp:include page="comman/header.inc"></jsp:include>


<%
    List  messages = new LinkedList();
    String action = request.getParameter("action");
    boolean globalControlDisable = false;

    if (request.getParameter("submit") != null) {
        orgReg.setStatus("false");
        String fromAction = request.getParameter("fromAction");

        boolean isSriLankan = "yes".equalsIgnoreCase(request.getParameter("isSriLankan")) ? true : false;
        orgReg.setIsSriLankan(isSriLankan);

        messages.addAll(orgReg.validate(false));
        // get the selected working areas
        Iterator allDistrictNames = dataAccessManager.getAllDistrictNames().iterator();

        orgReg.getWorkingAreas().clear();
       while (allDistrictNames.hasNext()) {
           String districtName =  (String) allDistrictNames.next();
           if ("on".equals(request.getParameter(districtName))) {
               orgReg.addWorkingArea(districtName);
           }

       }

        orgReg.getSectors().clear();
        String sectorString = (String)request.getParameter("sectors");
        while(sectorString.indexOf(',') != -1){
            String sector =sectorString.substring(0, sectorString.indexOf(','));
            sectorString =  sectorString.substring(sectorString.indexOf(','));
            orgReg.addSectors(sector);
            sectorString =  sectorString.substring(1);

        }


        if (messages.size() <= 0) {
            boolean status = false;
            String message = "";
            if(ERMSConstants.IContextInfoConstants.ACTION_ADD.equalsIgnoreCase(fromAction)){
                String requestDateParameter = request.getParameter("periodenddate");
                String[] dateValues = requestDateParameter.split("-");
                Calendar cal = new GregorianCalendar(Integer.parseInt(dateValues[0]),
                    Integer.parseInt(dateValues[1])-1,
                    Integer.parseInt(dateValues[2])
                );
                java.sql.Date periodDateObj = new java.sql.Date(cal.getTime().getTime());
                orgReg.setPeriodEndDate(periodDateObj);
                status =dataAccessManager.addOrganization(orgReg);
                message = "You have been successfully registered.!";
            }else if(ERMSConstants.IContextInfoConstants.ACTION_EDIT.equalsIgnoreCase(fromAction)){
                OrganizationRegistrationTO sessionOrgReg = (OrganizationRegistrationTO) session.getAttribute(ERMSConstants.IContextInfoConstants.ORGANIZATION_TO);
                orgReg.setOrgCode(sessionOrgReg.getOrgCode());
                String requestDateParameter = request.getParameter("periodenddate");
                String[] dateValues = requestDateParameter.split("-");
                Calendar cal = new GregorianCalendar(Integer.parseInt(dateValues[0]),
                    Integer.parseInt(dateValues[1])-1,
                    Integer.parseInt(dateValues[2])
                );
                java.sql.Date periodDateObj = new java.sql.Date(cal.getTime().getTime());
                orgReg.setPeriodEndDate(periodDateObj);
                status =dataAccessManager.updateOrganization(orgReg);
                message = "Your oraganizations information updated successfully !!";

            }


%>
<%
 if(status) {
        %>
        <p align="center" class="formText" >
               <h2><%=message%></h2>
         </p>
         <tr>
                 <td class="formText" align="center" colspan="2" ><a href="Index.jsp">Organization Registry Home</a></td>
            </tr>
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

            globalControlDisable = ERMSConstants.IContextInfoConstants.ACTION_VIEW.equalsIgnoreCase(action);

        if(request.getParameter("orgCode") != null){
            orgReg = dataAccessManager.getOrgTO(request.getParameter("orgCode"));
            request.getSession().setAttribute(ERMSConstants.IContextInfoConstants.ORGANIZATION_TO, orgReg);

       }

        // for testing only
//        if(action.equalsIgnoreCase(ERMSConstants.IContextInfoConstants.ACTION_EDIT) || action.equalsIgnoreCase(ERMSConstants.IContextInfoConstants.ACTION_VIEW)){
//            orgReg.setContactPerson("Chinthaka");
//            orgReg.setEmailAddress("chinthaka@apache.org");
//            orgReg.addWorkingArea("Ampara");
//            orgReg.addWorkingArea("Badulla");
//            orgReg.addWorkingArea("Galle");
//            orgReg.setCountryOfOrigin("Sri Lanka");
//            orgReg.setIsSriLankan(false);
//        }
    }

%>



    <form method="post" name="tsunamiOrgReg" action="Registration.jsp?fromAction=<%=action%>">
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

                 <select <%if(globalControlDisable){ %>disabled="true" <%}%>  name="orgType" onchange="displayRow();" class="selectBoxes" >
                 <%
                   String[] values={"Multilateral","Bilateral","NGO","Government","Private"};
                     boolean selected;
                     for (int i = 0; i < values.length; i++) {
                         selected = values[i].equalsIgnoreCase(orgReg.getOrgType());
                        %> <option <% if(selected){%> selected="true" <%}%> value="<%=values[i]%>"><%=values[i]%></option>
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
            <%
                boolean shouldBeDisplayedNow = "NGO".equalsIgnoreCase(orgReg.getOrgType());
                String ngoSubType = null;
                if (orgReg.getNgoType() != null) {
                    if(orgReg.getNgoType().indexOf("-") != -1){
                        ngoSubType = orgReg.getNgoType().split("-")[1];
                    }else {
                        ngoSubType = orgReg.getNgoType();
                    }
                }

            %>
            <tr <% if(!shouldBeDisplayedNow){%>style="display:none" <%}%> id="hiddenRow" >
              <td vAlign="top" class="formText" align="right">NGO Type :
                  </td>
              <td>
                 <select <%if(globalControlDisable){ %>disabled="true" <%}%>name="ngoType" class="selectBoxes" >
                 <%
                   String[] Ngovalues={"NGO","INGO","CBU"};
                     for (int i = 0; i < Ngovalues.length; i++) {
                           selected = Ngovalues[i].equalsIgnoreCase(ngoSubType);
                        %> <option <% if(selected){%> selected="true" <%}%>><%=Ngovalues[i]%></option>
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
                <input <%if(globalControlDisable){ %>disabled="true" <%}%> name="orgName" maxlength="99" size="38" type="text" id="Name" class="textBox" value="<%= (orgReg.getOrgName()==null)?"":orgReg.getOrgName()%>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td vAlign="top" class="formText" align="right" >Contact
                  Person :</td>
              <td>
                <input <%if(globalControlDisable){ %>disabled="true" <%}%> class="textBox" name="contactPerson" maxlength="99" size="38" type="text" id="contactperson" value="<%= (orgReg.getContactPerson()==null) ? "" : orgReg.getContactPerson() %>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td vAlign="top" class="formText" align="right" >Address :</td>
              <td>
                <textarea <%if(globalControlDisable){ %>disabled="true" <%}%> cols="38" name="orgAddress" rows="5" id="contact">
<%= (orgReg.getOrgAddress()==null) ? "" : orgReg.getOrgAddress() %>
</textarea>&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
            <td vAlign="top" class="formText" align="right" >Sector(s)</td>

            <td vAlign="top">
                <%
                    String sectors = "";
                    if(orgReg.getSectors() != null){
                     StringBuffer buffer = new StringBuffer(orgReg.getSectors().toString());
                     buffer.deleteCharAt(buffer.indexOf("["));
                     buffer.deleteCharAt(buffer.indexOf("]"));
                     sectors = buffer.toString();
                    }
                %>
                <textarea <%if(globalControlDisable){ %>disabled="true" <%}%> cols="38" readonly="true" name="sectors" rows="1"><%=sectors%></textarea>
            </td>



            </tr>
            <tr>
            <td align="right"></td>
            <td <%if(globalControlDisable){ %>style="display:none" <%}%> vAlign="top" >

                <input type="formText"  style="width: 100px;" name="inputVal" value="">
            </td>
<%--            <td >--%>
<%--                <INPUT type="button" name="click" onClick="add();" value="Add">--%>
<%--            </td>--%>
            </tr>
            <tr>
            <td align="right"></td>
            <td <%if(globalControlDisable){ %>style="display:none" <%}%>>
                <select  name="choiseList" size="5"  style="width: 150px;">
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
                       <INPUT <%if(globalControlDisable){ %>disabled="true" <%}%> type = "button" name="click" onClick="add();" value="Add" class="buttons" >
                    <INPUT  <%if(globalControlDisable){ %>disabled="true" <%}%> type = "button" name="click" onClick="minus();" value="Remove" class="buttons">
                </td>
<%--                <td>--%>

<%--                </td>--%>

            </tr>

            <tr>
              <td align="right" vAlign="top" class="formText">Contact
                No :</td>
              <td>
                <input <%if(globalControlDisable){ %>disabled="true" <%}%> class="textBox" name="contactNumber" maxlength="99" size="38" type="text" id="contactno" value="<%= (orgReg.getContactNumber()==null) ? "" : orgReg.getContactNumber()%>">&nbsp;<small><font color="red">*</font></small>
               </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Email
                Address :</td>
              <td>
                <input <%if(globalControlDisable){ %>disabled="true" <%}%> name="emailAddress" maxlength="99" size="38" type="text" class="textBox" id="email" value="<%= (orgReg.getEmailAddress()==null) ? "" : orgReg.getEmailAddress() %>">&nbsp;<small><font color="red">*</font></small>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Country
                of Origin :</td>
              <td>
                <% if(globalControlDisable){
                %>
                    <input disabled="true" name="countryOfOrigin" maxlength="99" size="38" type="text" class="textBox" id="countryOfOrigin" value="<%= (orgReg.getCountryOfOrigin()==null) ? "" : orgReg.getCountryOfOrigin() %>">
                <%
                }else {
                %> <select name="countryOfOrigin" class="selectBox">
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
                <%
                }
                %>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Facilities
                Available :</td>
              <td>
                <textarea <%if(globalControlDisable){ %>disabled="true" <%}%> cols="38" name="facilitiesAvailable" rows="5" id="Facilities"><%= (orgReg.getFacilitiesAvailable()==null) ? "" : orgReg.getFacilitiesAvailable() %></textarea>
                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Operational Districts :</td>
              <td>
          <table border="0" width="100%" cellspacing="1" cellpadding="1">
                <%
                    Iterator allDistricts = dataAccessManager.getAllDistricts().iterator();
                    ArrayList workingAreas = orgReg.getWorkingAreas();

                    // check whether this is EDIT action or VIEW action.
                    boolean correctView = action.equalsIgnoreCase(ERMSConstants.IContextInfoConstants.ACTION_EDIT) || action.equalsIgnoreCase(ERMSConstants.IContextInfoConstants.ACTION_VIEW);
                    boolean checked = false;
                    int i=0;
                    while (allDistricts.hasNext()) {
                        KeyValueDTO keyValueDTO = (KeyValueDTO) allDistricts.next();

                        // check whether this is an area of the existing organization
                        checked = correctView && workingAreas.contains(keyValueDTO.getDisplayValue());
                        if((i % 4)==0){
                %>
                <tr>
                    <td>
                        <input <%if(checked){ %>checked="true" <%}%> <%if(globalControlDisable){ %>disabled="true" <%}%> type="checkbox" name="<%=keyValueDTO.getDisplayValue()%>"><%=keyValueDTO.getDisplayValue()%></input>
                    </td>
                <%
                    }else {
                %>

                    <td>
                        <input <%if(checked){ %>checked="true" <%}%> <%if(globalControlDisable){ %>disabled="true" <%}%> type="checkbox" name="<%=keyValueDTO.getDisplayValue()%>"><%=keyValueDTO.getDisplayValue()%></input>
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


                    <td <%if(globalControlDisable){ %>style="display:none" <%}%>>
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

                   <%
                      boolean isSriLankanChecked = orgReg.isSriLankan();
                  %>
                <input <%if(isSriLankanChecked){ %>checked <%}%> <%if(globalControlDisable){ %>disabled="true" <%}%> name="isSriLankan" type="radio" value="yes">Yes</input>
                <input <%if(!isSriLankanChecked){ %>checked <%}%> <%if(globalControlDisable){ %>disabled="true" <%}%> name="isSriLankan" type="radio" value="no">No</input>

                </td>
            </tr>
            <tr>
              <td align="right" vAlign="top" class="formText">Comments :</td>
              <td>
                <textarea <%if(globalControlDisable){ %>disabled="true" <%}%> name="comments" cols="38" rows="5" id="comments" ><%= (orgReg.getComments()==null) ? "" : orgReg.getComments() %></textarea>
                </td>
            </tr>
                 <tr>
<%--              <td align="center" vAlign="top" colspan="2" class="formText" ><strong>User Registration</strong></td>--%>

            </tr>

            <br/>
            <br/>
                <%
                    boolean disable = false;
                    if(ERMSConstants.IContextInfoConstants.ACTION_EDIT.equalsIgnoreCase(action) || ERMSConstants.IContextInfoConstants.ACTION_VIEW.equalsIgnoreCase(action)){
                        disable = true;
                    }

                %>
            <td align="right" width="20%" class="formText">&nbsp;Period End Date</td>
                <td colspan="4">
                <table>
                    <tr>
                    <td width="16%">
                       <input type="text" name="periodenddate" class="textBox" readonly="true" id="txtMDate1" value="<%=orgReg.getPeriodEndDate()%>" />&nbsp;<small><font color="red">*</font></small>
                    </td>
                        <td width="82%"><img src="images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('txtMDate1'), 'yyyy-mm-dd')" width="18" height="17"/></td>
                    </tr>
            </table>
            <tr <%if(disable){ %>style="display:none" <%}%>>
                   <td align="right" vAlign="top" class="formText">User Name :</td>
                   <td>
                   <input <%if(globalControlDisable){ %>disabled="true" <%}%> name="username" type="text" class="textBox" size="20" value="<%=orgReg.getUsername()==null?"":orgReg.getUsername()%>" >&nbsp;<small><font color="red">*</font></small>
                   </td>
            </tr>

            <tr <%if(disable){ %>style="display:none" <%}%>>
                   <td align="right" vAlign="top" class="formText">Password :</td>
                   <td>
                   <input name="password" type="password" class="textBox" size="20" value="<%=orgReg.getPassword()==null?"":orgReg.getPassword()%>">&nbsp;<small><font color="red">*</font></small>
                  </td>
            </tr>
             <tr <%if(disable){ %>style="display:none" <%}%>>
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
                <td <%if(globalControlDisable){ %>style="display:none" <%}%>>

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



<%@ page import="org.campdb.business.CampTO,
                 org.campdb.db.DataAccessManager,
                 org.campdb.util.StringUtil,
                 org.campdb.util.LabelValue,
                 org.campdb.business.User,
                 org.campdb.util.CAMPDBConstants,
                 java.text.Format,
                 java.text.SimpleDateFormat,
                 java.util.*"%>
<jsp:useBean id="newCamp" scope="request" class="org.campdb.business.CampTO" />
     <jsp:setProperty name="newCamp" property="campId" />
     <jsp:setProperty name="newCamp" property="areadId" />
     <jsp:setProperty name="newCamp" property="divisionId" />
     <jsp:setProperty name="newCamp" property="districtCode" />
     <jsp:setProperty name="newCamp" property="provienceCode" />
     <jsp:setProperty name="newCamp" property="campName" />
     <jsp:setProperty name="newCamp" property="campAccesability" />
     <jsp:setProperty name="newCamp" property="campMen" />
     <jsp:setProperty name="newCamp" property="campWomen" />
     <jsp:setProperty name="newCamp" property="campChildren" />
     <jsp:setProperty name="newCamp" property="campTotal" />
     <jsp:setProperty name="newCamp" property="campCapability" />
     <jsp:setProperty name="newCamp" property="campContactPerson" />
     <jsp:setProperty name="newCamp" property="campContactNumber" />
     <jsp:setProperty name="newCamp" property="campComment" />
     <jsp:setProperty name="newCamp" property="provienceName" />
     <jsp:setProperty name="newCamp" property="districtName" />
     <jsp:setProperty name="newCamp" property="divionName" />
     <jsp:setProperty name="newCamp" property="areaName" />
     <jsp:setProperty name="newCamp" property="campFamily" />
     <jsp:setProperty name="newCamp" property="countSelect" />

<%
    DataAccessManager dataAccessManager = new DataAccessManager();
    List errors = new LinkedList();

    //add the date variable manually
    String updatedDateParameter = request.getParameter("updateDate");
    if (updatedDateParameter!=null && updatedDateParameter.trim().length()>0){
        //Date is in yyyy-mm-dd format
        String[] dateValues = updatedDateParameter.split("-");
        Calendar cal = new GregorianCalendar(Integer.parseInt(dateValues[0]),
                Integer.parseInt(dateValues[1])-1,
                Integer.parseInt(dateValues[2])
        );
        newCamp.setUpdateDate(cal.getTime());

    }


    if (request.getParameter("doUpdate") == null) {  //data comes from the database
        if (request.getParameter("campId") == null) {
            System.out.println(" i am in camp id null");
            response.sendRedirect("SearchCamps.jsp");
            return;
        }
        int campID = 0;
        try {
            campID = Integer.parseInt(request.getParameter("campId"));
        } catch (NumberFormatException e) {
            e.printStackTrace();
            response.sendRedirect("SearchCamps.jsp");
            return;
        }

        CampTO camp = dataAccessManager.searchCamp(campID);
        newCamp.copyFrom(camp);

        //reset the date
        newCamp.setUpdateDate(new java.util.Date());

        session.setAttribute("CAMP_ID",new Integer(newCamp.getCampId()));
    }

    if (request.getParameter("doUpdate") != null) {
        errors.addAll(dataAccessManager.validateCampTOforInsert(newCamp));

        int Id = ((Integer)session.getAttribute("CAMP_ID")).intValue();
        if(errors.size()<=0) {
            try {
                newCamp.setCampId(String.valueOf(Id));
                dataAccessManager.editCamp(newCamp);
                response.sendRedirect("ViewCampDetails.jsp?campId=" + Id);
                return;
            } catch (Exception e) {
                errors.add(e.getMessage());
            }
        }
    }
%>

<%
    Format formatter = new SimpleDateFormat("yyyy-MM-dd");

%>



<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana :: Camp Database</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script language='javascript' src='commonControls/popupcal/popcalendar.js'></script>
<script>

   function validateTotal()
    {
        var answer = confirm("Changes may affect the break down\n Continue?")
        if (answer){
            document.editCamp.campMen.value = 0;
            document.editCamp.campWomen.value = 0;
            document.editCamp.campChildren.value = 0;
            document.editCamp.campTotal.focus();
        }
        else{
            document.editCamp.campTotal.value= parseInt(document.editCamp.campMen.value) +
                parseInt(document.editCamp.campWomen.value) +
                parseInt(document.editCamp.campChildren.value);
            return;
       }
       if(isNaN(document.editCamp.campTotal.value))
       {
           alert("Please enter integer value");
           document.editCamp.campTotal.focus();
           return;
       }
    }

    function validateChildren()
    {
       if(isNaN(document.editCamp.campChildren.value))
       {
           alert("Please enter integer value");
           document.editCamp.campChildren.focus();
           return;
       }
       calcTotal();
    }

    function validateMen()
    {
       if(isNaN(document.editCamp.campMen.value))
       {
           alert("Please enter integer value");
           document.editCamp.campMen.focus();
           return;
       }
       calcTotal();
    }

    function validateWomen()
    {
       if(isNaN(document.editCamp.campWomen.value))
       {
           alert("Please enter integer value");
           document.editCamp.campWomen.focus();
           return;
       }
       calcTotal();
    }

 function calcTotal(){
        var menCount =0;
        var womenCount =0;
        var childrenCount =0;
        menCount = parseInt(document.editCamp.campMen.value);

       womenCount = parseInt(document.editCamp.campWomen.value);
       childrenCount = parseInt(document.editCamp.campChildren.value);


       if(isNaN(menCount)) menCount=0;
       if(isNaN(womenCount)) womenCount=0;
       if(isNaN(childrenCount)) childrenCount=0;

       document.editCamp.campTotal.value= menCount+womenCount+childrenCount;

    }

    function checkTotal(){

        var sure = confirm("Changing the total will affect the breakup figures. Are you sure you want to change the total only ?");
        if (sure == true)
         {
            document.editCamp.campMen.value = 0;
            document.editCamp.campWomen.value = 0;
            document.editCamp.campChildren.value = 0;
         }
    }

</script>
</head>

<body topmargin="0" leftmargin="0">
   <%  User user = (User) session.getAttribute(CAMPDBConstants.IContextInfoConstants.USER_INFO);
        if(user == null){
            request.getSession().setAttribute(CAMPDBConstants.IContextInfoConstants.ERROR_DESCRIPTION, "User has not been authenticated. Please login  !!");
            response.sendRedirect("error.jsp");
       }
                               %>

 <table width="100%" height="100%" border="0">
  <tr>
  <td height="50" >
    <jsp:include page="comman/header.inc"></jsp:include>
  </td>
  </tr>

  <tr>
  <td height="100%" align="left" valign="top">
        <form name="editCamp" action="UpdateCamp.jsp">
            <table cellspacing="4"  >
                <%
                    if(errors.size() > 0) {
                        newCamp.setNullValsToEmpty();
                        for (Iterator iterator = errors.iterator(); iterator.hasNext();) {
                            String error = (String) iterator.next();

                 %>
                <tr>
                    <td colspan="3" ><font color="red" size="-2"><%=error%></font><br></td>
                </tr>
                <%      }
                    }
                %>


                <tr>
                    <td align="right" valign="top"  >Camp Name</td><td><input type="text" class="textBox" name="campName" value="<jsp:getProperty name="newCamp" property="campName" />"></td>
                </tr>

                <tr>
                    <td  align="right" valign="top"  >Division&nbsp;
                        <td>
                        <select name="divisionId" class="selectBoxes">
                            <%
                            List divisions = (List) application.getAttribute("divisions");
                                for (Iterator iterator = divisions.iterator(); iterator.hasNext();) {
                                    LabelValue division = (LabelValue) iterator.next();
                            %>
                            <%
                                    if(division.getValue().equals(newCamp.getDivisionId())) {
                            %>
                                      <option selected value="<%=division.getValue()%>"><%=division.getLabel()%></option>
                            <%
                              } else {
                            %>
                                    <option value="<%=division.getValue()%>"><%=division.getLabel()%></option>

                            <%
                                    }
                                }
                            %>
                        </select>
                    </td>
               </tr>

                <tr>
                    <td  align="right" valign="top"  >Area&nbsp;
                       <td>
                         <input type="text" class="textBox"  size="20" maxlength="49"  name="areaName" value="<jsp:getProperty name="newCamp" property="areaName" />">
                    </td>
               </tr>

               <tr>
                    <td align="right" valign="top"  >Conatct Person</td><td><input type="text" class="textBox" name="campContactPerson" value="<jsp:getProperty name="newCamp" property="campContactPerson"/>" /></td>
                </tr>
               <tr>
                    <td align="right" valign="top"  >Contact Number</td><td><input type="text" class="textBox"  name="campContactNumber" value="<jsp:getProperty name="newCamp" property="campContactNumber" />"/></td>
                </tr>
                <br>
               <tr>
                    <td align="right" valign="top"  >Accesability</td><td align="left" valign="top">
                        <textarea name="campAccesability"  class="textBox" cols="50" rows="3" ><jsp:getProperty name="newCamp" property="campAccesability" /></textarea>
                    </td>
                </tr>
               <tr>
                    <td align="right" valign="top"  >Capability</td>
                    <td>
                        <textarea name="campCapability"  class="textBox" cols="50" rows="3"><jsp:getProperty name="newCamp" property="campCapability" /></textarea>
                    </td>
                </tr>

                <!--  seperator -->
               <tr>
                  <td align="right" valign="top" colspan="2"><hr/></td>
               </tr>
               <!-- seperator -->
               <tr>
                    <td align="right">
                        Effective from
                </td>
                <td><input type="text" name="updateDate" class="textBox" readonly="true" id="txtMDate1" value="<%=formatter.format(newCamp.getUpdateDate())%>" />&nbsp;<small><font color="red">*</font></small>
                    <img src="images/calendar.gif" onClick="popUpCalendar(this, document.getElementById('txtMDate1'), 'yyyy-mm-dd')" width="18" height="17"/></td>
                </tr>
                <tr>
               <td  align="right" vAlign="top" class="formText"> Family Count</td><td><input type="text" name="campFamily" class="textBox"/></td>
           </tr>
               <tr>
                    <td align="right" valign="top"  >Comment </td>
                    <td>
                        <textarea name="campComment" class="textBox" cols="50" rows="3" ><jsp:getProperty name="newCamp" property="campComment" /></textarea>
                    </td>
                </tr>
                <tr>
                    <td colspan="3" >&nbsp;</td>
                </tr>

                <tr>
                    <td align="right" valign="top"  >Men</td><td><input type="text" class="textBox" name="campMen" onchange="validateMen();"  value="<jsp:getProperty name="newCamp" property="campMen" />"/></td>

                </tr>

                <tr>
                    <td align="right" valign="top"  >Women</td><td><input type="text" class="textBox"  name="campWomen"  onchange="validateWomen();" value="<jsp:getProperty name="newCamp" property="campWomen" />"/></td>

                </tr>

                <tr>
                    <td align="right" valign="top"  >Children</td><td><input type="text" class="textBox"  name="campChildren"  onchange="validateChildren();" value="<jsp:getProperty name="newCamp" property="campChildren" />"/></td>

                </tr>

                <tr>
                    <td align="right" valign="top"  >Total</td>
                    <td><input type="text" class="textBox"  name="campTotal" onChange="validateTotal();" value="<jsp:getProperty name="newCamp" property="campTotal" />"/></td>

                </tr>

               <!--  seperator -->
               <tr>
                  <td align="right" valign="top" colspan="2"><hr/></td>
               </tr>
               <!-- seperator -->

                <tr>
                    <td align="right" ><input type="reset" name="reset" value="Clear" align="right" class="buttons" /></td>
                    <td align="left" ><input type="submit" name="doUpdate" value="Update" align="left" class="buttons"/></td>
                </tr>
            </table>

        </form>
       </td>
    </tr>
    <tr>
       <tr>
         <td class="formText" align="center">
                     <a href="Welcome.jsp">Camp Registry Home</a>
         </td>
       </tr>
    <td>
        <jsp:include page="comman/footer.inc"></jsp:include>
        </td>
    </tr>
    </table>
</body>
</html>


<%@ page import="org.campdb.business.CampTO,
                 org.campdb.db.DataAccessManager,
                 org.campdb.util.StringUtil,
                 java.util.List,
                 java.util.Iterator,
                 org.campdb.util.LabelValue,
                 java.util.LinkedList,
                 org.campdb.business.User,
                 org.campdb.util.CAMPDBConstants"%>
<jsp:useBean id="newCamp" scope="request" class="org.campdb.business.CampTO" />
<jsp:setProperty name="newCamp" property="*" />
<%
    DataAccessManager dataAccessManager = new DataAccessManager();

    List errors = new LinkedList();

    if (request.getParameter("doUpdate") == null) {  //data comes from the database
        if (request.getParameter("campId") == null) {
            response.sendRedirect("SearchCamps.jsp");
            return;
        }
        int campID = 0;
        try {
            campID = Integer.parseInt(request.getParameter("campId"));
        } catch (NumberFormatException e) {
            response.sendRedirect("SearchCamps.jsp");
            return;
        }
        CampTO camp = dataAccessManager.searchCamp(campID);
        newCamp.copyFrom(camp);
        session.setAttribute("CAMP_ID",new Integer(newCamp.getCampId()));
    }

    if (request.getParameter("doUpdate") != null) {
        errors.addAll(dataAccessManager.validateCampTOforInsert(newCamp));
        System.out.println("error size" +errors.size() );
        int Id = ((Integer)session.getAttribute("CAMP_ID")).intValue();
        if(errors.size()<=0) {
            try {
                newCamp.setCampId(String.valueOf(Id));
                dataAccessManager.editCamp(newCamp);
                response.sendRedirect("ViewCampDetails.jsp?campId=" + Id);
            } catch (Exception e) {
                errors.add(e.getMessage());
            }
        }
    }
%>




<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
<title>:: Sahana :: Camp Database</title>
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
<link href="comman/style.css" rel="stylesheet" type="text/css">
<script>
function validateform()
    {
    if(document.editCamp.campName.value == "")
    {
        alert("Camp Name must have a value");
        document.editCamp.campName.focus();
        return false;
    }

    if(document.editCamp.divisionId.value == "")
    {
        alert("Division Id must be selected");
        document.editCamp.divisionId.focus();
        return false;
    }
    if(isNaN(document.editCamp.campChildren.value))
    {
        alert("Please enter integer value");
        document.editCamp.campChildren.focus();
        return;
    }
    if(isNaN(document.editCamp.campMen.value))
    {
       alert("Please enter integer value");
       document.editCamp.campMen.focus();
       return;
    }
    if(isNaN(document.editCamp.campWomen.value))
    {
       alert("Please enter integer value");
       document.editCamp.campWomen.focus();
       return;
    }

    if(isNaN(document.editCamp.campTotal.value))
    {
       alert("Please enter integer value");
       document.editCamp.campTotal.focus();
       return;
    }

    //document.editCamp.doInsert.value="doInsert";
    document.editCamp.submit();
}

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
                <%--<tr>
                    <td align="right" valign="top"  >Province</td><td>&nbsp;</td>
                    <td>
                        <select name="provienceCode">
                            <%
                              List provinces = (List) application.getAttribute("provinces");
                                for (Iterator iterator = provinces.iterator(); iterator.hasNext();) {
                                    LabelValue province = (LabelValue) iterator.next();
                            %>
                            <%
                                    if(province.getValue().equals(newCamp.getProvienceCode())) {
                            %>
                                      <option selected value="<%=province.getValue()%>"><%=province.getLabel()%></option>
                            <%
                              } else {
                            %>
                                    <option value="<%=province.getValue()%>"><%=province.getLabel()%></option>

                            <%
                                    }
                                }
                            %>
                        </select>
                    </td>
                </tr>--%>
                <%--<tr>
                    <td align="right" valign="top"  >District</td><td>&nbsp;</td>
                    <td>
                        <select name="districtCode">

                        <%
                          List districts = (List) application.getAttribute("districts");
                            for (Iterator iterator = districts.iterator(); iterator.hasNext();) {
                                LabelValue district = (LabelValue) iterator.next();
                        %>
                        <%
                                if(district.getValue().equals(newCamp.getDistrictCode())) {
                        %>
                                  <option selected value="<%=district.getValue()%>"><%=district.getLabel()%></option>
                        <%
                          } else {
                        %>
                                <option value="<%=district.getValue()%>"><%=district.getLabel()%></option>

                        <%
                                }
                            }
                        %>

                        </select>
                    </td>
                </tr>--%>
                <tr>
                    <td  align="right" valign="top"  >Division&nbsp;
                        <td>
                        <select name="divisionId" class="selectBox">
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
               <%--<tr>
                    <td  align="right" valign="top"  >Area&nbsp;<td>&nbsp;</td>
                       <td>
                        <select name="areadId">
                            <%
                              List areas = (List) application.getAttribute("areas");
                                for (Iterator iterator = areas.iterator(); iterator.hasNext();) {
                                    LabelValue area = (LabelValue) iterator.next();
                            %>
                            <%
                                    if(area.getValue().equals(newCamp.getAreadId())) {
                            %>
                                      <option selected value="<%=area.getValue()%>"><%=area.getLabel()%></option>
                            <%
                              } else {
                            %>
                                    <option value="<%=area.getValue()%>"><%=area.getLabel()%></option>

                            <%
                                    }
                                }
                            %>

                        </select>
                    </td>
                </tr>--%>

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

                <tr>
                    <td align="right" ><input type="reset" name="reset" value="Clear" align="right" class="buttons" /></td>
                    <td align="left" ><input type="button" name="doUpdate" onClick="validateform();" value="Update" align="left" class="buttons"/></td>
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


<!--
* Copyright (c) 2005 Sahana Project.
* Contributed by Virtusa Corporation.
*
* Authors: multiple sources
-->
<%@ page import="org.damage.db.persistence.SahanaLocationsDAO,
                 java.util.List,
                 org.damage.common.LabelValue"%>
<%@ taglib uri="/WEB-INF/sahana.tld" prefix="sahana" %>

<script language="JavaScript" type="text/JavaScript">

    <!-- This tag will load sahana locations data into javascript arrays -->
    <sahana:SahanaLocationsArray listAllDistrictsByProvince="true"
                                 listAllDivisionsByDistrict="true"
                                 listAllGNDivisionsByDivision="true" />

	function listDistrict(){

       resetChildLocation(document.form1.caseDistrictId);
       resetChildLocation(document.form1.caseDivisionId);
       resetChildLocation(document.form1.caseGSDivisionId);

       if (!validChildLocation(document.form1.caseProvinceCode,
                                document.form1.caseDistrictId))
           return false;

        var caseProvinceCode = document.form1.caseProvinceCode.value;
		var districtList = document.form1.caseDistrictId.options;
   		districtList.length = 0;
		if(caseProvinceCode!=""){
			var prov = eval("prov"+caseProvinceCode);
			var tempproveCode = eval("provCode"+caseProvinceCode);
    	    var option = new Option("<select>","default",true);
			districtList.add(option,0);
			for (i=0;i< prov.length ;i++){
				 var option = new Option(prov[i],tempproveCode[i]);
				 districtList.add(option,i+1);
			}
		}

	  }

	function listDivisions(){

         resetChildLocation(document.form1.caseDivisionId);
         resetChildLocation(document.form1.caseGSDivisionId);

         if (!validChildLocation(document.form1.caseDistrictId,
                                document.form1.caseDivisionId))
             return false;

		 var divisionCode = document.form1.caseDistrictId.value;
		 var divisionList = document.form1.caseDivisionId.options;
   		 divisionList.length =0;
		 if (divisionCode!="") {
			 var divisions =eval("district" + divisionCode);
			 var tempdivisionCode =eval("districtCode" + divisionCode);
    	     var option = new Option("<select>","default",true);
			 divisionList.add(option,0);
			 for (i=0;i< divisions.length ;i++){
				 option = new Option(divisions[i],tempdivisionCode[i]);
				 divisionList.add(option,i+1);
			 }
		  }

    }

    function listGSDivisions(){

         resetChildLocation(document.form1.caseGSDivisionId);

         if (!validChildLocation(document.form1.caseDivisionId,
                                document.form1.caseGSDivisionId))
            return false;

		 var gsdivisionCode = document.form1.caseDivisionId.value;
		 var gsdivisionList = document.form1.caseGSDivisionId.options;
   		 gsdivisionList.length =0;
		 if(gsdivisionCode!=""){
			 var gsdivisions =eval("division" + gsdivisionCode);
			 var tempgsdivisionCode =eval("divisionCode" + gsdivisionCode);
    	     var option = new Option("<select>","default",true);
			 gsdivisionList.add(option,0);
			 for (i=0;i< gsdivisions.length ;i++){
				 var option = new Option(gsdivisions[i],tempgsdivisionCode[i]);
				 gsdivisionList.add(option,i+1);
			 }
		  }

    }

    function validChildLocation(selectObj, nextSelectObj)
    {
        if (selectObj.options[selectObj.selectedIndex].value == "default") {
            return false;
        }
        else {
            nextSelectObj.disabled=false;
        }
        return true;
    }

    function resetChildLocation(selectObj)
    {
   		selectObj.options.length = 1;
    	selectObj.options[0] = new Option("<select>","default",true);
        selectObj.disabled=true;
    }

</script>


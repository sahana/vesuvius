function testNumber(src) {
     var emailReg = "[0-9]+";
     var regex = new RegExp(emailReg);
     return regex.test(src);
}


//type=1 is full submit
//type = 2 is save
function validate(type){
var quantitiyStr = document.form1.quantity.value;

    if (type==1){
        document.form1.submitType.value = "Save";
        if(document.form1.districts.value == "deafult"){
            alert("Please Select a value for District");
            return;
        }
        if(document.form1.siteType.value == "deafult"){
            alert("Please Select a value for Site Type");
            return;
        }
    }else if (type==2){
        document.form1.submitType.value = "AddList";
        if(document.form1.catogories.value == "deafult"){
            alert("Please Select a value for Catogories");
            return;
        }
        if(document.form1.priorities.value == "deafult"){
            alert("Please Select a value for Priorities");
            return;
        }
    }else if (type==3){
        document.form1.submitType.value = "Clear";
    }

    if (type==2){
        if (!testNumber(quantitiyStr)){
            alert("please put in a number for quantity");
            return;
        }
    }
    document.form1.submit();
}





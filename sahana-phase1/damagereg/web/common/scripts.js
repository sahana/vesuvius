
    function isNumeric(elem) {
        var nonums =/^[0-9]*\.?\d{0,2}$/;
        return (nonums.test(elem.value) && (elem.value.length>0));
    }

    function setSelectStatus(selObj, val)
    {
        if (selObj.options.length>0) {
    		for (i=0; i< selObj.options.length; i++)
                if (selObj.options(i).value==val) {
                    selObj.selectedIndex=i;
                    break;
                }
        }
    }




var xmlHttp

function shn_gis_narrow_feature_classes(layer_)
{
    if (layer_.length == 0 ){ 
        return;
    }
                
    xmlHttp = GetXmlHttpObject();
    if (xmlHttp==null){
        alert ("Your browser does not support AJAX!");
        return;
    }
    
    var url="index.php?act=gis_search_layer&mod=xst&stream=text&layer=" + layer_;
    //url=url+"&sid="+Math.random();
    xmlHttp.onreadystatechange = stateChanged;
    xmlHttp.open("GET", url, true);
    xmlHttp.send(null);
} 

function stateChanged()
{ 
    if (xmlHttp.readyState==4){ 
        document.getElementById("gis_feature_class_select_form").innerHTML = xmlHttp.responseText;
    }
}

function GetXmlHttpObject(){
    var xmlHttp=null;
    try{
        // Firefox, Opera 8.0+, Safari
        xmlHttp=new XMLHttpRequest();
    }
    catch (e){
        // Internet Explorer
        try{
            xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
        }
        catch (e){
            xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
    }
    return xmlHttp;
}       
            
            
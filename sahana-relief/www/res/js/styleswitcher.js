function setActiveStyleSheet(name) {
  var i, a, main;
  for(i=0; (a = document.getElementsByTagName("link")[i]); i++) {
    if(a.getAttribute("rel").indexOf("style") != -1 && a.getAttribute("href")) {
      a.disabled = true;
      if(a.getAttribute("href").indexOf("theme/"+name+"/") == 0){ a.disabled = false;}
    }
  }
}

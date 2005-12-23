<!--
var CalendarPopup_curCalendar = '';
var CalendarPopup_curCalendarID = '';
var CalendarPopup_curMonthYear = '';
var CalendarPopup_selMonth = '';
var CalendarPopup_selYear = '';
if (navigator.appName == 'Netscape') { document.captureEvents(Event.CLICK); }

function scrivi_data_odierna(tipo){
//con tipo=2 scrive la data in formato gg/mm/yyyy 
//con tipo=1 scrive in formato mm/dd/yyyy 
	var oggi = new Date(); 
	var data = ""; 
	if (tipo==2) 
    {
			data+=oggi.getDate()<10?"0"+oggi.getDate()+" ":oggi.getDate()+"/"; 
			data+=(oggi.getMonth()+1)+"/"; 
			data+=oggi.getFullYear(); 
		} else {
			data+=(oggi.getMonth()+1)+"/"; 
			data+=oggi.getDate()<10?"0"+oggi.getDate()+" ":oggi.getDate()+"/"; 
			data+=oggi.getFullYear(); 
		}
	return data;
}

function CalendarPopup_Up_LostFocus(e) { CalendarPopup_Up_HideNonCurrentCalendar('', ''); }

function CalendarPopup_Up_Holiday(month, day, year, span) {
	this.Month = month;
	this.Day = day;
	this.Year = year;
	this.Span = span;
}

function CalendarPopup_Up_IsHoliday(month, day, year, dateArray) {
	var returnVal = false;
	
	if(dateArray == null) {
		returnVal = false;
	} else {
		for(var i=0; i<dateArray.length; i++) 
          {
			if(dateArray[i].Month == (month + 1) && dateArray[i].Day == day && (dateArray[i].Year == year || dateArray[i].Span)) {
				returnVal = true;
				i = dateArray.length;
			} else {
				returnVal = false;
			}
		}
	}
	
	return returnVal;
}

function CalendarPopup_Up_GiornoLinkabile(month, day, year,valori) {
//stabilisce se una data è riferita ad un giorno della settimana che l'utente vuole sia linkabile
//restituisce vero o falso
	var returnVal = false;
	var giorno=new Date(year,month,day);
	result=giorno.getDay();

     for(var i=0; i<valori.length; i++) 
     {
          if(result==valori[i]) 
          {
          	returnVal = true;
          } 
     }
	return returnVal;
}


function CalendarPopup_Up_GiornoLinkabile2(month, day, year,valori) {
//stabilisce se una data è riferita ad un giorno della settimana che l'utente vuole sia linkabile
//restituisce vero o falso
     month_lang=new Array('january','february','march','april','may','june','july','august','september','october','november','december');
	var returnVal = false;
	//alert (month_lang[month-1]);
	stringa=month_lang[month-1]+ " "+ day+", "+ year;
	var giorno=new Date(stringa);
	result=giorno.getDay();
	//alert(stringa+"--->"+giorno.getDay());
	for(var i=0; i<valori.length; i++) 
     {
          if(result==valori[i]) 
          {
          	returnVal = true;
          } 
     }
     //alert(stringa+"--->"+returnVal);
	return returnVal;
	//return giorno.getDay();
}

function CalendarPopup_Up_findPosX(obj)
{
	var curleft = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curleft += obj.offsetLeft;
			obj = obj.offsetParent;
		}
	}
	else if (obj.x) {
		curleft += obj.x;
	}
	return curleft;
}

function CalendarPopup_Up_findPosY(obj)
{
	var curtop = 0;
	if (obj.offsetParent)
	{
		while (obj.offsetParent)
		{
			curtop += obj.offsetTop;
			obj = obj.offsetParent;
		}
	}
	else if (obj.y)
		curtop += obj.y;
	return curtop;
}

function CalendarPopup_Up_DisplayCalendar(giorni,calIdFlag, tbName, lblName, lblTemp, divName, myName, funcName, myFuncName, wdStyle, weStyle, omStyle, sdStyle, mhStyle, dhStyle, cdStyle, tdStyle, gttStyle, holStyle, formatNum, monthnames, daynames, fdweek, sunNum, satNum, enableHide, includeYears, lBound, uBound, btnName, locQuad, pad, postbackFunc, offsetX, offsetY, showClear, clearText, showGoToToday, goToTodayText, arrowUrl, customFunc, calWidth, visibleKey, nullText, dateArray, nextMonthImgUrl, prevMonthImgUrl, nextYearImgUrl, prevYearImgUrl) {
	var div, tb;
	CalendarPopup_curCalendarID = calIdFlag;
	div = document.getElementById(divName);
	tb = document.getElementById(tbName);
	if(div.style.visibility != 'hidden') {
		div.style.visibility = 'hidden';
		if(enableHide)
			CalendarPopup_Up_ShowHideDDL('visible');
	} else {
		var todayDate = CalendarPopup_Up_GetDate(tbName, formatNum);
		eval('var stringDate = ' + visibleKey + ';');
		CalendarPopup_Up_HideNonCurrentCalendar(divName, myName)
		if(enableHide)
			CalendarPopup_Up_ShowHideDDL('hidden');
		div.style.position = 'absolute';
		var obj;
		if(lblTemp != '')
			obj = document.getElementById(lblTemp);
		else if(lblName != '')
			obj = document.getElementById(lblName);
		else
			obj = tb;
		var y = CalendarPopup_Up_findPosY(obj);
		var x = CalendarPopup_Up_findPosX(obj);
		switch(locQuad) {
			case 1:
				y += (obj.offsetHeight + 1);
				break;
			case 2:
				x -= (div.offsetWidth - 2);
				break;
			case 3:
				x += (obj.offsetWidth + 1);
				break;
			case 4:
				y -= (div.offsetHeight - 1);
				break;
			default:
				y = CalendarPopup_Up_findPosY(document.getElementById(btnName));
				x = CalendarPopup_Up_findPosX(document.getElementById(btnName)) - 3;
				break;
		}
		div.style.top = y + offsetY + 'px';
		div.style.left = x + offsetX + 'px';
		CalendarPopup_Up_DisplayCalendarByDate(giorni,tbName, lblName, divName, myName, funcName, myFuncName, stringDate, wdStyle, weStyle, omStyle, sdStyle, mhStyle, dhStyle, cdStyle, tdStyle, gttStyle, holStyle, formatNum, monthnames, daynames, fdweek, sunNum, satNum, enableHide, includeYears, lBound, uBound, pad, postbackFunc, showClear, clearText, showGoToToday, goToTodayText, arrowUrl, customFunc, calWidth, visibleKey, nullText, dateArray, nextMonthImgUrl, prevMonthImgUrl, nextYearImgUrl, prevYearImgUrl);
		div.style.visibility = 'visible';
	}
}

function CalendarPopup_Up_ChangeMonth(selMonth, lbDate, ubDate) {
	if(document.getElementById('CalendarPopup_monthname' + selMonth).style.color == 'black') {
		for(var i=0; i<12; i++) {
			if(i != selMonth)
				document.getElementById('CalendarPopup_monthname' + i).style.background='white';
			else
				document.getElementById('CalendarPopup_monthname' + i).style.background='lightgrey';
		}
		CalendarPopup_selMonth = selMonth++;
	}
}

function CalendarPopup_Up_ChangeYear(selYear, yearNum, lbDate, ubDate) {
	var lowerDate = new Date(lbDate);
	var upperDate = new Date(ubDate);
	lowerDate = new Date((lowerDate.getMonth() + 1) + '/1/' + lowerDate.getFullYear());
	for(var i=0; i<10; i++) {
		if(i != selYear)
			document.getElementById('CalendarPopup_yearname' + i).style.background='white';
		else
			document.getElementById('CalendarPopup_yearname' + i).style.background='lightgrey';
	}
	for(var i=0; i<12; i++) {
		var curDate = new Date((i + 1) + '/1/' + yearNum);
		if(curDate < lowerDate || curDate > upperDate)
			document.getElementById('CalendarPopup_monthname' + i).style.color = 'gray';
		else
			document.getElementById('CalendarPopup_monthname' + i).style.color = 'black';
		document.getElementById('CalendarPopup_monthname' + i).style.background = 'white';
	}
	var curDate = new Date((CalendarPopup_selMonth + 1) + '/1/' + yearNum);
	if(curDate <= lowerDate)
		CalendarPopup_selMonth = lowerDate.getMonth();
	else if(curDate >= upperDate)
		CalendarPopup_selMonth = upperDate.getMonth();
	document.getElementById('CalendarPopup_monthname' + CalendarPopup_selMonth).style.background = 'lightgrey';
	CalendarPopup_selYear = yearNum;
}

function CalendarPopup_Up_ChangeMonthYear(divName, funcName, isCancel) {
	if(!isCancel) {
		eval(funcName + "('" + (CalendarPopup_selMonth + 1) + "/1/" + CalendarPopup_selYear + "');");
	}
	document.getElementById(divName).style.visibility = 'hidden';
	document.getElementById(divName).innerHTML = '';
	document.onmousedown = CalendarPopup_Up_LostFocus;
}

function CalendarPopup_Up_DisplayMonthYear(calDivName, myDivName, funcName, myFuncName, monthnames, theDate, applyText, cancelText, lbDate, ubDate) {
	var calDIV = document.getElementById(calDivName);
	var myDIV = document.getElementById(myDivName);
	var curDate = new Date(theDate);
	var lowerDate = new Date(lbDate);
	var upperDate = new Date(ubDate);
	lowerDate = new Date((lowerDate.getMonth() + 1) + '/1/' + lowerDate.getFullYear());
		
	CalendarPopup_selMonth = curDate.getMonth();
	if(curDate < lowerDate)
		CalendarPopup_selMonth = lowerDate.getMonth();
	else if(curDate > upperDate)
		CalendarPopup_selMonth = upperDate.getMonth();
	CalendarPopup_selYear = curDate.getFullYear();
	
	outputString = '<table style=\"border: black 1px solid;background: white;\" border=0 cellspacing=0 cellpadding=0>';
	outputString = outputString + '<tr><td width=50% valign=top><table border=0 cellspacing=0 cellpadding=2>';
	//stampa i mesi
     for(var i=0; i<12; i++) {
		if(i % 2 == 0)
			outputString = outputString + '<tr>';
		var tempDate = new Date((i + 1) + '/1/' + CalendarPopup_selYear);
		if(tempDate >= lowerDate  && tempDate <= upperDate) {
			if(i == CalendarPopup_selMonth)
				outputString = outputString + "<td id=\"CalendarPopup_monthname" + i + "\" onclick=\"CalendarPopup_Up_ChangeMonth(" + i + ", '" + lbDate + "', '" + ubDate + "')\" align=left nowrap style=\"font-family:verdana; font-size:xx-small; color: black;background:lightgrey; cursor:hand;\">" + monthnames[i] + "</td>";
			else
				outputString = outputString + "<td id=\"CalendarPopup_monthname" + i + "\" onclick=\"CalendarPopup_Up_ChangeMonth(" + i + ", '" + lbDate + "', '" + ubDate + "')\" align=left nowrap style=\"font-family:verdana; font-size:xx-small; color: black; cursor:hand;\">" + monthnames[i] + "</td>";
		} else {
			outputString = outputString + "<td id=\"CalendarPopup_monthname" + i + "\" onclick=\"CalendarPopup_Up_ChangeMonth(" + i + ", '" + i + lbDate + "', '" + ubDate + "')\" align=left nowrap style=\"font-family:verdana; font-size:xx-small; color: gray; cursor:hand;\">" + monthnames[i] + "</td>";
		}
		if(i % 2 != 0)
			outputString = outputString + '</tr>';
	}
	outputString = outputString + '</table></td><td width=50% valign=top><table border=0 cellspacing=0 cellpadding=2 width=100%>';
	var j = 0;
	for(var i=(curDate.getFullYear() - 5); i<(curDate.getFullYear() + 5); i++) {
		if(j % 2 == 0)
			outputString = outputString + '<tr>';
		if(i >= lowerDate.getFullYear() && i <= upperDate.getFullYear()) {
			if(i == curDate.getFullYear())
				outputString = outputString + "<td id=\"CalendarPopup_yearname" + j + "\" onclick=\"CalendarPopup_Up_ChangeYear(" + j + ", " + i + ", '" + lbDate + "', '" + ubDate + "')\" align=left nowrap style=\"font-family:verdana; font-size:xx-small;color: black;background: lightgrey; cursor:hand;\">" + i + "</td>";
			else
				outputString = outputString + "<td id=\"CalendarPopup_yearname" + j + "\" onclick=\"CalendarPopup_Up_ChangeYear(" + j + ", " + i + ", '" + lbDate + "', '" + ubDate + "')\" align=left nowrap style=\"font-family:verdana; font-size:xx-small;color: black; cursor:hand;\">" + i + "</td>";
		} else {
			outputString = outputString + "<td id=\"CalendarPopup_yearname" + j + "\" align=left nowrap style=\"font-family:verdana; font-size:xx-small;color: gray; cursor:hand;\">" + i + "</td>";
		}
		if(j % 2 != 0)
			outputString = outputString + '</tr>';
		j++;
	}
	outputString = outputString + "<tr><td align=left><a style=\"font-family:verdana; font-size:xx-small; color: black;\" href=\"javascript:" + myFuncName + "((CalendarPopup_selMonth + 1) + '/" + curDate.getDate() + "/" + (curDate.getFullYear() - 10) + "')\">&lt;&lt;</a></td>";
	outputString = outputString + "<td align=right><a style=\"font-family:verdana; font-size:xx-small; color: black;\" href=\"javascript:" + myFuncName + "((CalendarPopup_selMonth + 1) + '/" + curDate.getDate() + "/" + (curDate.getFullYear() + 10) + "')\">&gt;&gt;</a></td></tr>";
	outputString = outputString + '</table></td></tr>';
	outputString = outputString + "<tr><td colspan=2 align=right nowrap><input onclick=\"CalendarPopup_Up_ChangeMonthYear('" + myDivName + "', '" + funcName + "', false);\" type=button value=\"" + applyText + "\" style=\"font-family:verdana; font-size:xx-small\"><input onclick=\"CalendarPopup_Up_ChangeMonthYear('" + myDivName + "', '" + funcName + "', true);\" type=button value=\"" + cancelText + "\" style=\"font-family:verdana; font-size:xx-small\"></td></tr>";
	
	myDIV.style.position = 'absolute';
	myDIV.style.top = parseInt(calDIV.style.top.replace('px', '')) + 2;
	myDIV.style.left = parseInt(calDIV.style.left.replace('px', '')) + 2;
	myDIV.innerHTML = outputString;
	myDIV.style.visibility = 'visible';
}

function CalendarPopup_Up_HideNonCurrentCalendar(divName, myName) {
	if(CalendarPopup_curMonthYear != '') {
		document.getElementById(CalendarPopup_curMonthYear).style.visibility = 'hidden';
		document.getElementById(CalendarPopup_curMonthYear).innerHTML = '';
	}
	if(CalendarPopup_curCalendar != '') {
		document.getElementById(CalendarPopup_curCalendar).style.visibility = 'hidden';
		document.getElementById(CalendarPopup_curCalendar).innerHTML = '';
		if(eval(CalendarPopup_curCalendarID) == true)
			CalendarPopup_Up_ShowHideDDL('visible');
	}
	if(divName != '')
		CalendarPopup_curCalendar = divName;
	if(myName != '')
		CalendarPopup_curMonthYear = myName;
}

function CalendarPopup_Up_GetDate(tbName, formatNum) {
	var todayDate;
	if(document.getElementById(tbName).value != '') {
		var theDate;
		var theDateArr = document.getElementById(tbName).value.split("/");
		if(theDateArr.length != 3) {
			theDateArr = document.getElementById(tbName).value.split(".");
			if(theDateArr.length != 3)
				theDateArr = document.getElementById(tbName).value.split("-");
		}
		if(theDateArr.length == 3) {
			switch(formatNum) {
				case 1: // In: MM/DD/YYYY Out: MM/DD/YYYY
					theDate = theDateArr[0].concat("/").concat(theDateArr[1]).concat("/").concat(theDateArr[2]);
					break;
				case 2: // In: DD/MM/YYYY Out: MM/DD/YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[0]).concat("/").concat(theDateArr[2]);
					break;
				case 3: // In: YYYY/MM/DD Out: MM/DD/YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[2]).concat("/").concat(theDateArr[0]);
					break;
				case 4: // In MM.DD.YYYY Out: MM.DD.YYYY
					theDate = theDateArr[0].concat("/").concat(theDateArr[1]).concat("/").concat(theDateArr[2]);
					break;
				case 5: // In DD.MM.YYYY Out: MM.DD.YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[0]).concat("/").concat(theDateArr[2]);
					break;
				case 6: // In YYYY.MM.DD Out: MM.DD.YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[2]).concat("/").concat(theDateArr[0]);
					break;
				case 7: // In MM-DD-YYYY Out: MM-DD-YYYY
					theDate = theDateArr[0].concat("/").concat(theDateArr[1]).concat("/").concat(theDateArr[2]);
					break;
				case 8: // In DD-MM-YYYY Out: MM-DD-YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[0]).concat("/").concat(theDateArr[2]);
					break;
				case 9: // In YYYY-MM-DD Out: MM-DD-YYYY
					theDate = theDateArr[1].concat("/").concat(theDateArr[2]).concat("/").concat(theDateArr[0]);
					break;
			}
			todayDate = new Date(theDate);
			if(todayDate == NaN)
				todayDate = new Date();
		} else
			todayDate = new Date();
	} else
		todayDate = new Date();
	return todayDate;
}

function CalendarPopup_Up_ShowHideDDL(visibility) {
	for(j=0;j<document.forms.length; j++) {
		for(i=0;i<document.forms[j].elements.length;i++) {
			if(document.forms[j].elements[i].type != null) {
				if(document.forms[j].elements[i].type.indexOf('select') == 0)
					document.forms[j].elements[i].style.visibility = visibility;
			}
		}
	}
}

function CalendarPopup_Up_DisplayCalendarByDate(giorni,tbName, lblName, divName, myName, funcName, myFuncName, stringDate, wdStyle, weStyle, omStyle, sdStyle, mhStyle, dhStyle, cdStyle, tdStyle, gttStyle, holStyle, formatNum, monthnames, daynames, fdweek, sunNum, satNum, enableHide, includeYears, lBound, uBound, pad, postbackFunc, showClear, clearText, showGoToToday, goToTodayText, arrowUrl, customFunc, calWidth, visibleKey, nullText, dateArray, nextMonthImgUrl, prevMonthImgUrl, nextYearImgUrl, prevYearImgUrl) {
     //MODIFICATO PESANTEMENTE
     // this function of core is edit for link not all days of weeks
     var dateToday = new Date();
	var lowerDate = new Date(lBound);
	var upperDate = new Date(uBound);
	var todayDate = new Date(stringDate);
	var curDate = new Date(CalendarPopup_Up_GetDate(tbName, formatNum));
	var curMonth = curDate.getMonth();
	var curYear = curDate.getFullYear();
	var monthdays = new Array(31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31);
	thisday=todayDate.getDay();
	thismonth=todayDate.getMonth();
	thisdate=todayDate.getDate();
	thisyear=todayDate.getFullYear();
	if (((thisyear % 4 == 0) && !(thisyear % 100 == 0)) ||(thisyear % 400 == 0))
		monthdays[1]++;
	var outputString = '';
	startspaces=thisdate;
	var prevMonth = thismonth;
	var prevDay = thisdate;
	var prevYear = thisyear;
	var thisPreviousYear = thisyear - 1;
	var thisNextYear = thisyear + 1;
	if(prevMonth < 1) {
		prevMonth = 12;
		prevYear = prevYear - 1;
	}
	if(thisdate > monthdays[prevMonth - 1])
		prevDay = monthdays[prevMonth - 1];
	var nextMonth = thismonth + 2;
	var nextDay = thisdate;
	var nextYear = thisyear;
	if(nextMonth > 12) {
		nextMonth = 1;
		nextYear = nextYear + 1;
	}
	if(thisdate > monthdays[nextMonth - 1])
		nextDay = monthdays[nextMonth - 1];
	while (startspaces > 7)
		startspaces-=7;
	startspaces = thisday - startspaces + 1;
	startspaces = startspaces - fdweek;
	if (startspaces < 0)
		startspaces+=7;
	outputString = outputString + '<table';
	if(calWidth > 0)
		outputString = outputString + ' width=\"' + calWidth + 'px\"';
	outputString = outputString + ' style=\"border: black 1px solid;\" border=0 cellspacing=0px cellpadding=2px>';
	if (includeYears == false) {
		if(prevMonthImgUrl == '')
			outputString = outputString + "<tr " + mhStyle + "><td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + prevMonth + "/" + prevDay + "/" + prevYear + "')\">&lt;</a></td>";
		else
			outputString = outputString + "<tr " + mhStyle + "><td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + prevMonth + "/" + prevDay + "/" + prevYear + "')\"><img src=\"" + prevMonthImgUrl + "\" border=0></a></td>";
	} else {
		if(prevMonthImgUrl == '')
			outputString = outputString + "<tr " + mhStyle + "><td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + prevMonth + "/" + prevDay+ "/" + prevYear + "')\">&lt;</a><br>";
		else
			outputString = outputString + "<tr " + mhStyle + "><td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + prevMonth + "/" + prevDay+ "/" + prevYear + "')\"><img src=\"" + prevMonthImgUrl + "\" border=0></a><br>";
		
		if(prevYearImgUrl == '')
			outputString = outputString + "<a " + mhStyle + " href=\"javascript:" + funcName + "('" + (thismonth + 1) + "/" + thisdate + "/" + thisPreviousYear + "')\">&lt;&lt;</a></td>";
		else
			outputString = outputString + "<a " + mhStyle + " href=\"javascript:" + funcName + "('" + (thismonth + 1) + "/" + thisdate + "/" + thisPreviousYear + "')\"><img src=\"" + prevYearImgUrl + "\" border=0></a></td>";
	}
	outputString = outputString + '<td colspan=5 nowrap align=center ' +mhStyle + "><a " + mhStyle + " href=\"javascript:" + myFuncName + "('" + (thismonth + 1) + "/1/" + thisyear + "')\">" + monthnames[thismonth] + ' ' + thisyear;
	if(arrowUrl != "")
		outputString = outputString + ' <img src=\"' + arrowUrl + '\" border=0>';
	outputString = outputString + '</a></td>';
	if (includeYears == false) {
		if(nextMonthImgUrl == '')
			outputString = outputString + "<td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + nextMonth + "/" + nextDay + "/" + nextYear + "')\">&gt;</a></td></tr>";
		else
			outputString = outputString + "<td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + nextMonth + "/" + nextDay + "/" + nextYear + "')\"><img src=\"" + nextMonthImgUrl + "\" border=0></a></td></tr>";
	} else {
		if(nextMonthImgUrl == '')
			outputString = outputString + "<td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + nextMonth + "/" + nextDay+ "/" + nextYear + "')\">&gt;</a><br>";
		else
			outputString = outputString + "<td align=center><a " + mhStyle + " href=\"javascript:" + funcName + "('" + nextMonth + "/" + nextDay+ "/" + nextYear + "')\"><img src=\"" + nextMonthImgUrl + "\" border=0></a><br>";
		
		if(nextYearImgUrl == '')
			outputString = outputString + "<a " + mhStyle + " href=\"javascript:" + funcName + "('" + (thismonth + 1) + "/" + thisdate + "/" + thisNextYear + "')\">&gt;&gt;</a></td></tr>";
		else
			outputString = outputString + "<a " + mhStyle + " href=\"javascript:" + funcName + "('" + (thismonth + 1) + "/" + thisdate + "/" + thisNextYear + "')\"><img src=\"" + nextYearImgUrl + "\" border=0></a></td></tr>";
	}
	//stampa i nomi dei giorni
	outputString = outputString + '<tr>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[0] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[1] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[2] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[3] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[4] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[5] + '</td>';
	outputString = outputString + '<td ' + dhStyle + ' align=center>' + daynames[6] + '</td>';
	outputString = outputString + '</tr>';
	//stampa i giorni cioè i numeri dei mesi prima e dopo
     for (s=0;s<startspaces;s++) 
     {
		var theDate, month, year;
		if(thismonth == 0) {
			theDate = monthdays[11] - (startspaces - (s + 1));
			month = 12;
			year = thisyear - 1;
		} else {
			theDate = monthdays[thismonth - 1] - (startspaces - (s + 1));
			month = thismonth;
			year = thisyear;
		}
		var theCurDate = new Date(month + "/" + theDate + "/" + year);
		var lowerAmount = (lowerDate - theCurDate);
		var upperAmount = (theCurDate - upperDate);	
		if(s == 0)
			outputString = outputString + '<tr>';
		if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0)){
			//stampa i giorni del mese prima PRIMA DELL'intervallo voluto
               outputString = outputString + "<td align=center " + omStyle + "\">" + theDate + "</td>";
		}else if(s!=sunNum && s!=satNum){
		   //stampa i giorni FERIALI del mese prima ALL'INTERNO dell'intervallo voluto
		   //##################################################################
		    if (CalendarPopup_Up_GiornoLinkabile2(thismonth, theDate, thisyear,giorni)) {
                    outputString = outputString + "<td align=center " + omStyle + "><a " + omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + theDate + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + theDate + "</a></td>";
               } else {
                     outputString = outputString + "<td align=center " + omStyle + ">" + theDate + "</td>";
               }
               //outputString = outputString + "<td align=center " + omStyle + "><a " + omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + theDate + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + theDate + "</a></td>";
			//outputString = outputString + "<td align=center " + omStyle + ">" + theDate + "</td>";
			//##################################################################
		}else{
		   //stampa i giorni FESTIVI del mese prima ALL'INTERNO l'intervallo voluto
		   	if (CalendarPopup_Up_GiornoLinkabile2(thismonth, theDate, thisyear,giorni)) {
                    outputString = outputString + "<td align=center " + omStyle + "><a " + omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + theDate + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + theDate + "</a></td>";
               } else {
                     outputString = outputString + "<td align=center " + omStyle + ">" + theDate + "</td>";
               }
             //outputString = outputString + "<td align=center " + omStyle + "><a " + omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + theDate + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + theDate + "</a></td>";
		}
	}
	count=1;
	//stampa i giorni della settimana nel mese
	while (count <= monthdays[thismonth]) {
		for (b = startspaces;b<7;b++) {
			if(b == 0)
				outputString = outputString + '<tr>';
			if((thismonth == dateToday.getMonth() && count == dateToday.getDate() && thisyear == dateToday.getFullYear()) || (count==curDate.getDate() && thismonth == curMonth && thisyear == curYear && document.getElementById(tbName).value != '')) {
				if (count==curDate.getDate() && thismonth == curMonth && thisyear == curYear && document.getElementById(tbName).value != '')
					//stampa data selezionata
                         outputString = outputString + '<td align=center ' + sdStyle + '>';
				else if(CalendarPopup_Up_IsHoliday(thismonth, count, thisyear, dateArray))
					outputString = outputString + '<td align=center ' + holStyle + '>';
				else if(thismonth == dateToday.getMonth() && count == dateToday.getDate() && thisyear == dateToday.getFullYear())
					outputString = outputString + '<td align=center ' + tdStyle + '>';
			} else {
				if (count <= monthdays[thismonth]) {
					if(CalendarPopup_Up_IsHoliday(thismonth, count, thisyear, dateArray)) {
						outputString = outputString + '<td align=center ' + holStyle + '>';
					} else {
						if(b!=sunNum && b!=satNum) {
						    //giorni non del week end
							outputString = outputString + '<td align=center ' + wdStyle + '>';
						} else {
					     	//giorni  del week end
							outputString = outputString + '<td align=center ' + weStyle + '>';
						}
					}
				} else {
				      //giorni del week end DENTRO il mese dopo NELL'INTERVALLO VOLUTO
					outputString = outputString + '<td align=center ' + omStyle + '>';
				}
			}
			if (count <= monthdays[thismonth]) {
				var theCurDate = new Date((thismonth + 1) + "/" + count + "/" + thisyear);
				var lowerAmount = (lowerDate - theCurDate);
				var upperAmount = (theCurDate - upperDate);	
				
				if((thismonth == dateToday.getMonth() && count == dateToday.getDate() && thisyear == dateToday.getFullYear()) || (count==curDate.getDate() && thismonth == curMonth && thisyear == curYear && document.getElementById(tbName).value != '')) {
					if (count==curDate.getDate() && thismonth == curMonth && thisyear == curYear && document.getElementById(tbName).value != '') {							
						if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
							outputString = outputString + "<span " + sdStyle + ">" + count + "</span>"; 
						else
							//CREA LINK PER LA DATA SELEZIONATA
							//##################################################################
                                   //a=;
                                   if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
                                        outputString = outputString + "<a " + sdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                                   } else {
                                         outputString = outputString +  count ;
                                   }
                                   //outputString = outputString + "X<a " + sdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                                   //##################################################################
					} else if(CalendarPopup_Up_IsHoliday(thismonth, count, thisyear, dateArray)) {
						if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
							outputString = outputString + "<span " + holStyle + ">" + count + "</span>"; 
						else
							outputString = outputString + "<a " + holStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
					} else if(thismonth == dateToday.getMonth() && count == dateToday.getDate() && thisyear == dateToday.getFullYear()) {
						if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
							outputString = outputString + "<span " + tdStyle + ">" + count + "</span>"; 
						else
						     //CREA LINK PER LA DATA ODIERNA SE NON GIA' ATTIVATA
						     //##################################################################
							if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
						         outputString = outputString + "<a " + tdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                                   }else{
                                         outputString = outputString + count ;
                                   }
                                   //outputString = outputString + "X<a " + tdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
							//##################################################################
					}
				} else if(CalendarPopup_Up_IsHoliday(thismonth, count, thisyear, dateArray)) {
					if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
						outputString = outputString + "<span " + holStyle + ">" + count + "</span>"; 
					else
						outputString = outputString + "<a " + holStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
				} else if(b!=sunNum && b!=satNum && count != thisdate) {
					if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
						outputString = outputString + "<span " + wdStyle + ">" + count + "</span>"; 
					else
					     //LINK GIORNI FERIALI SETTIMANA DEL MESE IN CORSO
					     //##################################################################
						if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
						    outputString = outputString + "<a " + wdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                              }else{
                                   outputString = outputString + count ;
                              }
                              //outputString = outputString + "X<a " + wdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
						//##################################################################
				} else if(b!=sunNum && b!=satNum) {
					if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
						outputString = outputString + "<span " + wdStyle + ">" + count + "</span>"; 
					else
						if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
					          outputString = outputString + "<a " + wdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                              }else{
                                    outputString = outputString + count ;
                              }
                             // outputString = outputString + "§<a " + wdStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
				} else {
					if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
						outputString = outputString + "<span " + weStyle + ">" + count + "</span>"; 
					else
					     //LINK GIORNI WEEK END SETTIMANA DEL MESE IN CORSO
					     //##################################################################
						if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
					         outputString = outputString + "<a " + weStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
                              }else{
                                    outputString = outputString + count ;
                              }
                              //outputString = outputString + "X<a " + weStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + (thismonth + 1) + "/" + count + "/" + thisyear + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + count + "</a>";
						//##################################################################
				}
			} else {
				var month, year;
				if(thismonth == 11) {
					month = 1;
					year = thisyear + 1;
				} else {
					month = thismonth + 2;
					year = thisyear;
				}
				var theCurDate = new Date(month + "/" + (count - monthdays[thismonth]) + "/" + year);
				var lowerAmount = (lowerDate - theCurDate);
				var upperAmount = (theCurDate - upperDate);	
				if((lowerAmount > 0 && upperAmount < 0) || (upperAmount > 0 && lowerAmount < 0))
					outputString = outputString + "<span " + omStyle + ">" + (count - monthdays[thismonth]) + "</span>";
				else
				      //LINK DEI GIORNI DEL MESE DOPO
				      //##################################################################
					if (CalendarPopup_Up_GiornoLinkabile(thismonth, count, thisyear,giorni)) {
				         outputString = outputString + "<a " +omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + (count - monthdays[thismonth]) + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + (count - monthdays[thismonth]) + "</a>";
                         }else{
                               outputString = outputString + count ;
                         }
                         //outputString = outputString + "X<a " +omStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + month + "/" + (count - monthdays[thismonth]) + "/" + year + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + (count - monthdays[thismonth]) + "</a>";
					//##################################################################
			}
			outputString = outputString + '</td>';
			count++;
		}
		outputString = outputString + '</tr>';
		startspaces=0;
	}
	if(showGoToToday) {
		var shortDate = (dateToday.getMonth() + 1) + "/" + dateToday.getDate() + "/" + dateToday.getFullYear();
		outputString = outputString + "<tr><td " + gttStyle + " colspan=\"7\" align=\"center\">" + goToTodayText + " <a " + gttStyle + " href=\"javascript:CalendarPopup_Up_SelectDate('" + tbName + "','" + lblName + "','" + divName + "','" + myName + "','" + shortDate + "', " + formatNum + ", " + enableHide + ", " + pad + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "')\">" + CalendarPopup_Up_DetermineDate(shortDate, formatNum, pad) + "</a>";
	}
	if(showClear)
		outputString = outputString + "<tr><td " + cdStyle + " colspan=\"7\" align=\"center\"><a " + cdStyle + " href=\"javascript:CalendarPopup_Up_ClearDate('" + tbName + "','" + lblName + "','" + divName + "', '" + myName + "', " + enableHide + ", '" + postbackFunc + "', '" + customFunc + "', '" + visibleKey + "', '" + nullText + "');\">" + clearText + "</a></td></tr>";
	outputString = outputString + '</table>';
	document.getElementById(divName).innerHTML = outputString;
}

function CalendarPopup_Up_DetermineDate(inDate, formatNum, pad) {
	var theDateArr = inDate.split("/");
	if(theDateArr.length != 3) {
		theDateArr = document.getElementById(tbName).value.split(".");
		if(theDateArr.length != 3) {
			theDateArr = document.getElementById(tbName).value.split("-");
		}		
	}	
	if(pad) {
		if(parseInt(theDateArr[0]) < 10 && theDateArr[0].length == 1)
			theDateArr[0] = '0' + theDateArr[0];
		if(parseInt(theDateArr[1]) < 10 && theDateArr[1].length == 1)
			theDateArr[1] = '0' + theDateArr[1];
		if(parseInt(theDateArr[2]) < 10 && theDateArr[2].length == 1)
			theDateArr[2] = '0' + theDateArr[2];
	}
	var theDate;
	switch(formatNum) {
		case 1: // In: MM/DD/YYYY Out: MM/DD/YYYY
			theDate = theDateArr[0].concat("/").concat(theDateArr[1]).concat("/").concat(theDateArr[2]);
			break;
		case 2: // In: MM/DD/YYYY Out: DD/MM/YYYY
			theDate = theDateArr[1].concat("/").concat(theDateArr[0]).concat("/").concat(theDateArr[2]);
			break;
		case 3: // In: MM/DD/YYYY Out: YYYY/MM/DD
			theDate = theDateArr[2].concat("/").concat(theDateArr[0]).concat("/").concat(theDateArr[1]);
			break;
		case 4: // In MM.DD.YYYY Out: MM.DD.YYYY
			theDate = theDateArr[0].concat(".").concat(theDateArr[1]).concat(".").concat(theDateArr[2]);
			break;
		case 5: // In MM.DD.YYYY Out: DD.MM.YYYY
			theDate = theDateArr[1].concat(".").concat(theDateArr[0]).concat(".").concat(theDateArr[2]);
			break;
		case 6: // In MM.DD.YYYY Out: YYYY.MM.DD
			theDate = theDateArr[2].concat(".").concat(theDateArr[0]).concat(".").concat(theDateArr[1]);
			break;
		case 7: // In MM-DD-YYYY Out: MM-DD-YYYY
			theDate = theDateArr[0].concat("-").concat(theDateArr[1]).concat("-").concat(theDateArr[2]);
			break;
			case 8: // In MM-DD-YYYY Out: DD-MM-YYYY
			theDate = theDateArr[1].concat("-").concat(theDateArr[0]).concat("-").concat(theDateArr[2]);
			break;
		case 9: // In MM-DD-YYYY Out: YYYY-MM-DD
			theDate = theDateArr[2].concat("-").concat(theDateArr[0]).concat("-").concat(theDateArr[1]);
			break;
	}
	return theDate;
}

function CalendarPopup_Up_SelectDate(tbName, lblName, divName, myName, theDate, formatNum, enableHide, pad, postbackFunc, customFunc, visibleKey) {
	document.getElementById(tbName).value = CalendarPopup_Up_DetermineDate(theDate, formatNum, pad);
	if(lblName != '')
		document.getElementById(lblName).innerHTML = CalendarPopup_Up_DetermineDate(theDate, formatNum, pad);
	document.getElementById(divName).style.visibility = 'hidden';
	document.getElementById(myName).style.visibility = 'hidden';
	if(enableHide)
		CalendarPopup_Up_ShowHideDDL('visible');
	eval(postbackFunc + "();");
	if(customFunc != "")
		eval(customFunc + "('" + theDate + "', '" + tbName + "');");
	eval(visibleKey + ' = \"' + theDate + '\";');
}

function CalendarPopup_Up_ClearDate(tbName, lblName, divName, myName, enableHide, postbackFunc, customFunc, visibleKey, nullText) {
	var todayDate = new Date();
	document.getElementById(tbName).value = '';
	if(lblName != '')
		document.getElementById(lblName).innerHTML = nullText;
	document.getElementById(divName).style.visibility = 'hidden';
	document.getElementById(myName).style.visibility = 'hidden';
	if(enableHide)
		CalendarPopup_Up_ShowHideDDL('visible');
	eval(postbackFunc + "();");
	if(customFunc != "")
		eval(customFunc + "('', '" + tbName + "');");
	eval(visibleKey + ' = \"' + (todayDate.getMonth() + 1) + '/' + todayDate.getDate() + '/' + todayDate.getFullYear() + '\";');
}
// -->

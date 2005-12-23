<?php
/*
This new version of the little toy, at 19 november 2005, let you to set as link not all days of the week
NB: THERE IS A LITTLE BUG IN THE CORE JAVASCRIPT: SOMETIME , in the previous month, the days linkable are not
active;

please report any other bug or problem at andreabersi@gmail.com

Ciao

Andrea Bersi
AOSTA (ITALY)
http://abmcr.altervista.org

*/
class Calendar
{
  //localisation variable
  var $day_lang;
  var $month_lang;
  var $short_month_lang;
  // layout variable
  //variable needed by the graphic output
  var $sfondo_day_selected="Green"; //background of the day today
  var $grandezza_carattere="XX-Small"; //size of the text
  var $sfondo_mese="Blue"; //background of the month at the top
  var $testo_mese="White"; //color of the text of Month
  var $sfondo_settimana="Green"; //background of the week at the top
  var $testo_settimana="Green";//color of the text of the days of Week
  var $colore_oggi="Yellow";//background of the day selected
  var $sfondo_giorniNonDelMese="AntiqueWhite";//background of the daysof next and previous month
  var $sfondo_giorniWeekEnd="LightGray"; //background of the days of week end
  var $giorni_settimana_linkabili="0,1,2,3,4,5,6";// set the day of the week as linkable; 0--> s to 6-->s

  //constructor of class
  function Calendar($lang)
  {
    switch ($lang)
    {
      case "it":
        $this->day_lang="'l','m','m','g','v','s','d'";
        $this->month_lang="'gennaio','febbraio','marzo','aprile','maggio','giugno','luglio','agosto','settembre','ottobre','novembre','dicembre'";
        $this->short_month_lang="'gen','feb','mar','apr','mag','giu','lug','ago','set','ott','nov','dic'";
        break;
      case "en":
        $this->day_lang="'m','t','w','t','f','s','s'";
        $this->month_lang="'january','february','march','april','may','june','july','august','september','october','november','december'";
        $this->short_month_lang="'jan','feb','mar','apr','may','jun','jul','aug','sep','oct','nov','dec'";
        break;
      //create your day_lang
    }
  }
  
  //the function start with a defualt italian format of the date
	function CreateCalendar($date_initial,$name,$link_back,$link_next,$date_format="2")
  {
    //date initial is the date visible in the textbox
    //name is the name of textbox containing the data selected: it is useful to set in for insert data into db
    //$link_back is the data in mm/dd/yyyy format of the date prev link
    //$link_next is the data in mm/dd/yyyy format of the date  link
    //date_format=1 then format date is mm/dd/yyyy
    //date_format=2 then format date is dd/mm/yyyy
        $link_back="'$link_back'"; $link_next="'$link_next'";
		static $num=0;
		$num++;
		$calendario="";
		$calendario.= "
	    <!-- INIZIO CALENDARIO -->
	    <span id='calendario_outer$num' style='font-family:Arial;'>
	    <input name='$name' type='text' value='$date_initial' readonly='readonly' id='calendario$num' style='font-family:Arial;font-size:X-Small;'/>
	    </span>
	    <input type='button' name='calendario".$num."_calbutton' value=' ... ' id='calendario".$num."_calbutton' />
	    <script language='javascript'>
	    calendario".$num."_outer_EnableHideDropDownFlag = false;
	    calendario".$num."_outer_VisibleDate = scrivi_data_odierna(1);
	    function calendario".$num."_Up_SetClick(addClickTo)
	    {
	      if(addClickTo != '') document.getElementById(addClickTo).onclick = calendario".$num."_Up_CallClick;
	      document.onmousedown = CalendarPopup_Up_LostFocus;
	      document.getElementById('calendario".$num."').onclick = calendario".$num."_Up_CallClick;
	    }
	    function calendario".$num."_Up_CallClick(e)
	    {
		var monthnames = new Array(".$this->month_lang.");
		var daynames = new Array(".$this->day_lang.");
		var day_week_link=new Array(".$this->giorni_settimana_linkabili.");
		CalendarPopup_Up_DisplayCalendar(day_week_link,'calendario".$num."_outer_EnableHideDropDownFlag', 'calendario".$num."','','','calendario".$num."_div', 'calendario".$num."_monthYear', 'calendario".$num."_Up_PreDisplayCalendar', 'calendario".$num."_Up_PreMonthYear', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->sfondo_giorniWeekEnd.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Gray;background-color:".$this->sfondo_giorniNonDelMese.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->colore_oggi.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:".$this->testo_mese.";background-color:".$this->sfondo_mese.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->sfondo_settimana.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:".$this->sfondo_day_selected.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', $date_format, monthnames, daynames, 1, 6, 5, false, false, $link_back, $link_next,'calendario".$num."_calbutton',1, false, 'calendario".$num."_Up_PostBack', 0, 0, false, 'Annulla', false, 'Data oggi:', '', '', -1, 'calendario".$num."_outer_VisibleDate', 'Seleziona una data', CalendarPopup_Array_calendario".$num."_outer, '', '', '', '');
	    }
	    function calendario".$num."_Up_PreDisplayCalendar(theDate)
	    {
	      var monthnames = new Array(".$this->month_lang.");
	      var daynames = new Array(".$this->day_lang.");
	      var day_week_link=new Array(".$this->giorni_settimana_linkabili.");
	      CalendarPopup_Up_DisplayCalendarByDate(day_week_link,'calendario".$num."','','calendario".$num."_div', 'calendario".$num."_monthYear', 'calendario".$num."_Up_PreDisplayCalendar', 'calendario".$num."_Up_PreMonthYear', theDate, 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->sfondo_giorniWeekEnd.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Gray;background-color:".$this->sfondo_giorniNonDelMese.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->sfondo_day_selected.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:White;background-color:".$this->sfondo_mese.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"','style=\"color:Black;background-color:".$this->sfondo_settimana.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:".$this->sfondo_day_selected.";font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', 'style=\"color:Black;background-color:White;font-family:Verdana,Helvetica,Tahoma,Arial;font-size:".$this->grandezza_carattere.";\"', $date_format, monthnames, daynames, 1, 6, 5, false, false, $link_back, $link_next, false, 'calendario".$num."_Up_PostBack', false, 'Annulla', false, 'Data oggi:', '', '', -1, 'calendario".$num."_outer_VisibleDate', 'Seleziona una data', CalendarPopup_Array_calendario".$num."_outer, '', '', '', '');
	    }
	    calendario".$num."_Up_SetClick('calendario".$num."_calbutton');
	    function calendario".$num."_Up_PreMonthYear(theDate)
	    {
		var monthnames = new Array(".$this->short_month_lang.");
		CalendarPopup_Up_DisplayMonthYear('calendario".$num."_div', 'calendario".$num."_monthYear', 'calendario".$num."_Up_PreDisplayCalendar', 'calendario".$num."_Up_PreMonthYear', monthnames, theDate, 'Applica', 'Annulla', $link_back, $link_next);
	    }
	    function calendario".$num."_Up_PostBack() {
	    }
	    var CalendarPopup_Array_calendario".$num."_outer = null;
	    </script>
	    <div id='calendario".$num."_div' onmouseover='document.onmousedown = null;' onmouseout='document.onmousedown = CalendarPopup_Up_LostFocus;' style='visibility:hidden;z-index:5000;position:absolute;'></div>
	    <div id='calendario".$num."_monthYear' onmouseover='document.onmousedown = null;' onmouseout='document.onmousedown = CalendarPopup_Up_LostFocus;' style='visibility:hidden;z-index:5001;position:absolute;'></div>
	    <!-- FINE CALENDARIO -->
	    ";
	    echo $calendario;
	    return ;
	} // End function CreateCalendar
} // End class
?>

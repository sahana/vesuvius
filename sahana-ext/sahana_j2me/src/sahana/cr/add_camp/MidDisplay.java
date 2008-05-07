/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  MidDisplay.java
 * @date       24 July 2006
 */

package sahana.cr.add_camp;

import javax.microedition.midlet.MIDlet;
import javax.microedition.lcdui.*;
import java.lang.String;
import sahana.mpr.send.*;
import sahana.mpr.message.*;

/* Author : Pradeep Senanayaka
 */

public class MidDisplay implements CommandListener {

    public StringItem str,str1,str2,str3,str_NEXT;
    public Form formShow,form_back;
    public Display display;
    public String st17,st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16;
    public StringItem stritem;
    public String[] showarray;
    public Command commandBack, commandNext;
    public Alert alert;
    String url,output,data;

	public MidDisplay(Display disp , String[] input_array , Form form) {

        commandBack = new Command("BACK", Command.BACK, 1);
        commandNext = new Command("Send", Command.SCREEN, 1);
        form_back = form;
        display = disp;
        showarray = input_array;
        formShow = new Form("The Information Entered");

        st1 = showarray[0];
        st2 = showarray[1];
        st3 = showarray[2];
        st4 = showarray[3];
        st5 = showarray[4];
        st6 = showarray[5];
        st7 = showarray[6];
        st8 = showarray[7];
        st9 = showarray[8];
        st10 = showarray[9];
        st11 = showarray[10];
        st12 = showarray[11];
        st13 = showarray[12];
        st14 = showarray[13];
        st15 = showarray[14];
        st16 = showarray[15];


                       if(st1.equals(""))
		                   st1=null;
		               if(st2.equals(""))
		                   st2=null;
		               if(st3.equals(""))
				           st3=null;
				       if(st4.equals(""))
				           st4=null;
				       if(st5.equals(""))
				           st5=null;
				       if(st6.equals(""))
				           st6=null;
				       if(st7.equals(""))
				           st7=null;
				       if(st8.equals(""))
				           st8=null;
				       if(st9.equals(""))
				           st9=null;
				       if(st10.equals(""))
				           st10=null;
				       if(st11.equals(""))
				           st11=null;
				       if(st12.equals(""))
				           st12=null;
				       if(st13.equals(""))
				           st13=null;
				       if(st14.equals(""))
				           st14=null;
				       if(st15.equals(""))
				           st15=null;
				       if(st16.equals(""))
				           st16=null;








        url = "http://localhost:8080/sahana_php/cr/get.php";
        data = "campName="+st1+"&campType="+st2+"&Address="+st3+"&Country="+st4+"&Region="+st5+"&province="+st6+"&city="+st7+"&firstName="+st8+"&phoneNumber="+st9+"&mobileNumber="+st10+"&occupation="+st11+"&family="+st12+"&total="+st13+"&men="+st14+"&women="+st15+"&children="+st16;

        str = new StringItem("***General Details***","");
        formShow.append(str);
        formShow.append(new StringItem("Camp Name    ",st1));
        formShow.append(new StringItem("Camp Type     ",st2));
        formShow.append(new StringItem("Camp Address ",st3));

        str1 = new StringItem("***Base Location***","");
        formShow.append(str1);
        formShow.append(new StringItem("Country  ",st4));
        formShow.append(new StringItem("Region   ",st5));
        formShow.append(new StringItem("Province ",st6));
        formShow.append(new StringItem("City        ",st7));

        str2 = new StringItem("***Contact Person Details***","");
        formShow.append(str2);
        formShow.append(new StringItem("Full Name         ",st8));
        formShow.append(new StringItem("Phone Number  ",st9));
        formShow.append(new StringItem("Mobile Number ",st10));
        formShow.append(new StringItem("Occupation        ",st11));

        str3 = new StringItem("***Camp Population***","");
        formShow.append(str3);
        formShow.append(new StringItem("Familly Count ",st12));
        formShow.append(new StringItem("Total Count    ",st13));
        formShow.append(new StringItem("Men               ",st14));
        formShow.append(new StringItem("Women           ",st15));
        formShow.append(new StringItem("Children         ",st16));
        formShow.append(new StringItem("Index         ",st17));

        formShow.addCommand(commandBack);
        formShow.setCommandListener(this);
        formShow.addCommand(commandNext);
        formShow.setCommandListener(this);

        display.setCurrent(formShow);
    }




   	public void commandAction(Command c, Displayable displayable) {

        if(c == commandBack) {
            display.setCurrent(form_back);
        }
            if(c == commandNext) {

				new Thread(new Runnable() {
	                public void run() {

                        send msend = new send();

                        String output = msend.send_Data(url,data);
                        message msg = new message(display, formShow, output);
                    }}).start();
            }
    }
}


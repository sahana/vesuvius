/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  form_2.java
 * @date       24 July 2006
 */


package sahana.mpr.forms;

import java.io.*;
import javax.microedition.io.*;
import javax.microedition.midlet.MIDlet;
import javax.microedition.lcdui.*;
import java.util.*;
import java.lang.String;
import javax.microedition.rms.*;

import sahana.mpr.rms.*;
import sahana.mpr.message.*;
import sahana.mpr.send.*;

/* Author : Sahan C Priyadarshana
 */

public class form_2  implements CommandListener {

    public Display display;
    public final static Command CMD_BACK = new Command("Back", Command.BACK, 1);
    public final static Command CMD_SEND = new Command("Send", Command.ITEM, 1);
    public final static Command CMD_WRITE = new Command("Save", Command.ITEM, 1);
    public final static Command CMD_VIEW = new Command("View", Command.ITEM, 1);
    public TextBox TXT_AREA;
    TemplateRecordStore dbs=null;
    Image icon=null;
    public TextField R_name,R_phone,R_address,R_reported;
	StringBuffer stringBuffer = new StringBuffer();
	String url, send_data;
	String form_1_url,output,form_1_data,form_2_data,S_f_Name,S_R_name,S_R_phone,S_R_address,S_R_reported;
	public ChoiceGroup status;
 	public Form second_Form,backscreen;


    public form_2(Display display, Form backscreen, String parameters,String url) {

        this.display=display;
        this.backscreen=backscreen;
        this.form_1_data = parameters;
        this.form_1_url = url;

        second_Form = new Form("Reporter's Details");
        display.setCurrent(second_Form);

        try {
            dbs = new TemplateRecordStore("Templates");
        }
        catch(Exception e) {
        }
    }

    public void createForm() {

        R_name = new TextField("Reporter's Name", "", 40, TextField.ANY);
        R_phone = new TextField("Reporter's Phone", "", 13, TextField.PHONENUMBER);
        R_address = new TextField("Reporter's Address", "", 100, TextField.ANY);
        status = new ChoiceGroup("Have You Reported before", Choice.POPUP);
	    int sex_Index = status.append("No", null);
	    status.append("Yes", null);
        status.setSelectedIndex(sex_Index, true);

        second_Form.append(R_name);
        second_Form.append(R_phone);
        second_Form.append(R_address);
        second_Form.append(status);
	    second_Form.addCommand(CMD_BACK);
        second_Form.setCommandListener(this);
        second_Form.addCommand(CMD_SEND);
        second_Form.addCommand(CMD_WRITE);
        second_Form.addCommand(CMD_VIEW);
        second_Form.setCommandListener(this);
    }

    public void valiDate() {

       S_R_name = R_name.getString();
       S_R_phone = R_phone.getString();
       S_R_address = R_address.getString();

       if(S_R_name.equals(""))
           S_R_name=null;
       if(S_R_phone.equals(""))
           S_R_phone=null;
       if(S_R_address.equals(""))
           S_R_address=null;
    }

    public void commandAction(Command c, Displayable s ) {

	    if(c == CMD_BACK) {
            display.setCurrent(backscreen);
        }

	    if(c == CMD_WRITE) {
            int rid=0;
  	        boolean add=false;
            valiDate();
		    S_R_reported = status.getString(status.getSelectedIndex());
		    form_2_data =S_R_name+","+S_R_phone+","+S_R_address+","+S_R_reported+",";

	        if(rid==0) {
	 	        add=true;

	    	    try {
	    	        rid=dbs.getRid();
	    	    }
	    	    catch(Exception e) {
			    }

	            String record= form_1_data + form_2_data +"|"+rid;

	            if(add) {
	                dbs.addTemplate(record);
	            }

            }
	        message msg = new message(display, second_Form," ");
	    }


        if(c == CMD_SEND) {

	        valiDate();
	        S_R_reported = status.getString(status.getSelectedIndex());

		    new Thread(new Runnable() {
	            public void run() {
	 		        S_R_name = R_name.getString();
			        S_R_phone = R_phone.getString();
   				    S_R_address = R_address.getString();
   				    valiDate();
				    url = "http://localhost:8080/sahana_php/mpr/get.php";
	 			    send_data = form_1_url+"&rep_full_name="+S_R_name+"&rep_phone="+S_R_phone+"&rep_address="+S_R_address+"&rep_reported="+S_R_reported;
	                send send_obj = new send();
	 		        String value = send_obj.send_Data(url, send_data);
	 		        message msg = new message(display, second_Form, value);

	                           }}).start();

        }

        if(c == CMD_VIEW) {

            TemplateManage tm=new TemplateManage(display,second_Form);
        }

    }
}

/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  TemplateManage.java
 * @date       24 July 2006
 */


package sahana.mpr.rms;

import javax.microedition.rms.*;
import javax.microedition.lcdui.*;
import java.lang.String;
import java.util.*;
import sahana.mpr.send.*;

/* Author : Thayalan Gugathashan
 */

public class TemplateManage implements CommandListener {

    Display display = null;
    static final Command CMD_BACK = new Command("Back", Command.BACK, 0);
    static final Command CMD_OPTIONS = new Command("Options",Command.SCREEN,1);
    String currentDisplay = null;
    List main_menu,choose,delete_list,view_list= null;
    String name,SelectedValue = "";
    TemplateRecordStore dbs = null;
    Form fm = null;
    Image icon,icon1= null;

    public TemplateManage(Display display, Form fm) {

        this.display = display;
        this.fm = fm;

            try {
                dbs = new TemplateRecordStore("Templates");
                icon = Image.createImage("/Icon.png");
                icon1 = Image.createImage("/mainIcon.png");
            }
            catch (Exception e) {
            }
        mainmenu();
    }

    void mainmenu() {
        listTemplate();
        display.setCurrent(view_list);
        currentDisplay = "view_list";
    }

    public void listTemplate() {
        view_list = new List("All Records", Choice.IMPLICIT);
            try {
                RecordEnumeration re = dbs.enumerate();

                while (re.hasNextElement())
                    {
                        String s = dbs.readRecords(re.nextRecord());
                        view_list.append(TemplateRecord.getTemplate(s), icon);
				    }
            }
            catch (Exception ex) {
			}

        view_list.addCommand(CMD_BACK);
        view_list.setCommandListener(this);
        view_list.addCommand(CMD_OPTIONS);
        view_list.setCommandListener(this);
        display.setCurrent(view_list);
        currentDisplay = "view_list";
    }

    public void deleteTemplate() {

        int i = 0;
        String name = SelectedValue;

            try {
                RecordEnumeration re = dbs.enumerate();

                    while (re.hasNextElement()) {
                        String curTemplate = dbs.readRecords(re.nextRecord());

                            if (name.equals(TemplateRecord.getTemplate(curTemplate))) {
                                i = TemplateRecord.getRecordid(curTemplate);
                                break;
                            }
                    }

             dbs.deleteContact(i);
             }
             catch (Exception e) {
                 e.printStackTrace();
             }
        mainmenu();
    }

    public void sendtemplate() {

        int i,count;
        String name = SelectedValue;
        String str, cur = null;
	    String[] val=new String[19];

            try {
                RecordEnumeration re = dbs.enumerate();

                while (re.hasNextElement()) {

                     String curTemplate = dbs.readRecords(re.nextRecord());

                     if (name.equals(TemplateRecord.getTemplate(curTemplate))) {
                         i = TemplateRecord.getRecordid(curTemplate);
                         cur = TemplateRecord.getTemplate(curTemplate);
                         break;
                     }
                }

			    for(i=0;i<19;i++) {
			        count = cur.indexOf(",");
			        str = cur.substring(0,count);
			        val[i]=str;
			        System.out.println(val[i]);
			        cur = cur.substring(++count,cur.length());
                }

		        String url = "http://localhost:8080/sahana_php/mpr/get.php";
	            String data ="full_name="+val[0]+"&idcard="+val[1]+"&drv_license="+val[2]+"&passport="+val[3]+"&dob="+val[4]+"&opt_age_group="+val[5]+"&opt_gender="+val[6]+"&phone="+val[7]+"&address="+val[8]+"&country="+val[9]+"&province="+val[10]+"&district="+val[11]+"&village="+val[12]+"&last_seen="+val[13]+"&last_cloth="+val[14]+"&rep_full_name="+val[15]+"&rep_phone="+val[16]+"&rep_address="+val[17]+"&rep_reported="+val[18];
		        send send_now = new send();
		        String output = send_now.send_Data(url,data);

            }
            catch (Exception e) {
                e.printStackTrace();
            }

            deleteTemplate();
            mainmenu();

    }

    public void viewTemplate(String name) {

        SelectedValue = name;
        main_menu = new List("Select Operation", Choice.IMPLICIT);
        main_menu.append("Send Record", null);
        main_menu.append("Delete Record", null);
        main_menu.setCommandListener(this);

        display.setCurrent(main_menu);
        currentDisplay = "main_menu";
    }

    public void commandAction(Command c, Displayable d) {

        String label = c.getLabel();

        if (label.equals("Back")) {

            if (currentDisplay.equals("view_list")) {
                display.setCurrent(fm);
            } else {
               mainmenu();
              }
        } else {
            if (currentDisplay.equals("main_menu")) {
                switch (main_menu.getSelectedIndex())
                {

                case 0:
              	new Thread(new Runnable() {
	                public void run() {
					    sendtemplate();

					               }}).start();
                break;

                case 1 :
                deleteTemplate();
                break;
            }
         } else if (currentDisplay.equals("view_list")) {
             viewTemplate(view_list.getString(view_list.getSelectedIndex()));
           }
        }
    }
}



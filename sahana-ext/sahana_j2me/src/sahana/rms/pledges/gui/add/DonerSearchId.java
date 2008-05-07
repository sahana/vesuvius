/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  DonerSearchId.java
 * @date       24 July 2006
 */


package sahana.rms.pledges.gui.add;

import sahana.rms.db.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.util.*;
import java.io.*;
import javax.microedition.io.*;
import sahana.mpr.send.*;

/* Authors : Michelle Narangoda
 */

public class DonerSearchId implements CommandListener {
    private Display display;
    private Form screen;
    private List backscreen;
    private TextField donerId;
    private StringItem contactInfoHeading,pledgeInfoHeading,emptyString1,emptyString2;
    private Command backCommand,submitCommand,newCommand;
    private String networkData,data,url;

    public DonerSearchId(Display dis , List main) {
        display=dis;
        backscreen=main;
        
        /*Initialize commands*/
        backCommand=new Command("Back",Command.BACK,2);
        submitCommand=new Command("Submit",Command.OK,2);
        newCommand=new Command("New",Command.SCREEN,2);
        
        /*Initializing the screen*/
        screen=new Form("Add Pledgs");
        contactInfoHeading=new StringItem("","Donor Id");

        screen.append(contactInfoHeading);

        /*Adding and initializing GUI components*/
        donerId = new TextField("Doner ID","",50,TextField.ANY);
        screen.append(donerId);

        /*Adding commands*/
        screen.addCommand(backCommand);
        screen.addCommand(submitCommand);
        screen.addCommand(newCommand);
        
        /*Adding Listeners to the formidDonerInfo*/
        screen.setCommandListener(this);
        display.setCurrent(screen);
    }

    public void commandAction(Command c,Displayable s) {  
        String donerInfoString="";
        String pledgeInfoString="";

        if (c==backCommand) {
      	    display.setCurrent(backscreen);
        }
        
        if (c==submitCommand) {
            /*Variables for store data in data store*/
            String strPledgeId = donerId.getString();
		    url = "http://localhost:8080/date/today.jsp";
		    data="donerId="+strPledgeId+"&requestId=0";

		        new Thread(new Runnable() {
				    public void run() {
					    try {
							send send_obj = new send();
							networkData = send_obj.send_Data(url,data);
							System.out.println(networkData);
						} catch(Exception e) {						
						}
					}}).start();

            if(networkData.length()==2) {
		        System.out.println("your User Id is invalied."+networkData);
			    AddPledgs addPledgs = new AddPledgs(display , screen,"User Id is Invalied. Register as new User");
            } else {
            	AddPledgs addPledgs = new AddPledgs(display , screen,networkData,"true");
            }
        }

        if (c==newCommand) {
        	/*Variables for store data in data store*/
        	AddPledgs addPledgs = new AddPledgs(display , screen, "Fill the Deatils Bellow for Registration");
        }
    }
}
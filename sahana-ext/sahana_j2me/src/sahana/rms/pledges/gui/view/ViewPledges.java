/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  ViewPledges.java
 * @date       24 July 2006
 */


package sahana.rms.pledges.gui.view;

import sahana.rms.db.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.util.*;
import java.io.*;
import javax.microedition.io.*;
import sahana.mpr.send.*;

/* Authors : Michelle Narangoda
 */

public class ViewPledges implements CommandListener {
    private Display display;
    private List backscreen;
	private StringItem pledgeIDHeading;
	private TextField pledgeID ;
	private Form screen;
	private Command backCommand,submitCommand;
	private String networkData,data,url;

	public ViewPledges(Display dis, List main) {
	    display=dis;
        backscreen=main;
		screen=new Form("View Pledge");
		pledgeIDHeading=new StringItem("","Pledge ID");
		screen.append(pledgeIDHeading);
		pledgeID=new TextField("PledgeID","",10,TextField.ANY);
		screen.append(pledgeID);
		backCommand=new Command("Back",Command.BACK,2);
		screen.addCommand(backCommand);
		submitCommand= new Command("Submit",Command.OK,2);
		screen.addCommand(submitCommand);
		screen.setCommandListener(this);
		display.setCurrent(screen);
	}

	public void commandAction(Command c,Displayable s) {
	    if (c==backCommand)	{
		    display.setCurrent(backscreen);
		}
        
	    if(c==submitCommand) {
	    	String strPledgeId = pledgeID.getString();
	    	url = "http://localhost:8080/date/viewPledge.jsp";
			data="donerId="+strPledgeId+"&requestId=0";

			new Thread(new Runnable() {
				public void run() {
					try {
						send send_obj = new send();
						networkData = send_obj.send_Data(url,data);
						System.out.println(networkData);
					}catch(Exception e) {						
					}
				}}).start();
				
			if(networkData.length()==2) {
				System.out.println("your User Id is invalied."+networkData);
			} else {
				ViewPledgesResults vpr = new ViewPledgesResults (display ,screen ,networkData );
			}
        }
	}
}

/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  ListPledges.java
 * @date       24 July 2006
 */


package sahana.rms.pledges.gui.search;

import sahana.rms.db.*;
import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import sahana.mpr.send.*;

/* Authors : Michelle Narangoda
 */

public class ListPledges implements CommandListener {
    private Command backCommand,submitCommand;
	private Display display;
    private List backscreen;
	private Form screen;
	private ChoiceGroup statusGroup,donerGroup;
	private TextField pledgeName ;
	private String networkData,data,url;

	public ListPledges(Display dis , List main) {
        backscreen=main;
        display =dis;
        backCommand=new Command("Back",Command.BACK,2);
        submitCommand=new Command("Submit",Command.OK,2);
        screen=new Form("List Pledges");
        String [] statusArray = {"All","Confirmed","Not Confirmed","Delivered","Discaded"};
        statusGroup=new ChoiceGroup("Select Status",Choice.POPUP,statusArray,null);
        pledgeName=new TextField("PledgeID","",150,TextField.ANY);
        String [] donerArray = {"Sahan","Michelle","Kasun","Pradeep","Thayalan","Muguntha"};
        donerGroup=new ChoiceGroup("Select Doner Name",Choice.POPUP,donerArray,null);
        screen.append(pledgeName);
        screen.append(statusGroup);
        screen.addCommand(backCommand);
        screen.addCommand(submitCommand);
        screen.setCommandListener(this);
        display.setCurrent(screen);
	}

	public void commandAction(Command c,Displayable s) { 
		
		if(c==backCommand) {
			display.setCurrent(backscreen);
		}
	  
		if(c==submitCommand) {
			String strDonerName=pledgeName.getString();
			String strstatus=statusGroup.getString(statusGroup.getSelectedIndex());
			url = "http://localhost:8080/date/listPledge.jsp";
			data="donerName="+strDonerName+"&status="+strstatus;
		
			new Thread(new Runnable() {
				public void run() {
					try {
						send send_obj = new send();
						networkData = send_obj.send_Data(url,data);
						System.out.println(networkData);
					}catch(Exception e){}
				}}).start();

			if(networkData.length()==2) {
				System.out.println("Pledge Not Found."+networkData);
			} else {
				DisplayPledges displayPledgs = new DisplayPledges(display, screen, networkData);
			}
		}
    }
}
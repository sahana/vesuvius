/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  AddPledgeItem.java
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

public class AddPledgeItem implements CommandListener {
    //AddPledgs class
    private StringItem contactInfoHeading,pledgeInfoHeading,emptyString1,emptyString2;
    private Command backCommand,submitCommand;
    private Display display;
    private Form screen;
    private Form backscreen;
    private TextField catagory,quentity,item;
    private ChoiceGroup catagoryGroup;
    private int catagoryGroupIndex,idPledgeDetails = 0,idDonerInfo=0;
    private RecordStore rsPledgeDetails;
    private RecordEnumeration record;
    private byte[] ArrayPledgeDetails;
    private String donerInfoString;
    private String networkData,data,url;

    public AddPledgeItem(Display dis , Form main,int donerId) {	
        //Get the display object for the MIDLet
        display=dis;
        backscreen=main;
        idDonerInfo=donerId;
        
        //Initialize commands
        backCommand=new Command("Back",Command.BACK,2);
        submitCommand=new Command("Submit",Command.OK,2);
        
        //Initializing the screen
        screen=new Form("Add Pledgs");

        pledgeInfoHeading=new StringItem("","idDonerInfoPledge Details");
        screen.append(pledgeInfoHeading);

        catagory=new TextField("Catagory","",50,TextField.ANY);
	    screen.append(catagory);
        item=new TextField("Item","",50,TextField.ANY);
        screen.append(item);

        //Adding commands
        screen.addCommand(backCommand);
        screen.addCommand(submitCommand);
        
        //Adding Listeners to the formidDonerInfo
        screen.setCommandListener(this);
        //screen.setItemStateListener(this);
        display.setCurrent(screen);

    }//end constructor

    public void itemStateChanged(Item item) {
        if(item==catagoryGroup) { 
            String [] catagoryArray = {"Foods and Nutritions","Blankets/Shelter","MedicalDrugs","Other"};
                if(3==catagoryGroup.getSelectedIndex()) {
                    screen.insert(catagoryGroupIndex+1,catagory);
                }
        }
    }

    public void commandAction(Command c,Displayable s) {  
        String donerInfoString="";
        String pledgeInfoString="";

            if (c==backCommand) {
		        display.setCurrent(backscreen);
            }
            if (c==submitCommand) {
			    RecordStoreHandler rsh=new RecordStoreHandler();
			    //Variables from read data store
			    String readStringDonerInfo="";
			    String readStringPledgeInfo="";
			    String varItem=item.getString();
			    String varCatagory=catagory.getString();
			 
			    pledgeInfoString=varCatagory+"#"+varItem;
			    Alert displayDataAlert=new Alert("Error","Wade harigiye naa.",null,AlertType.INFO);
			    displayDataAlert.setTimeout(Alert.FOREVER);
			
			    	try {
			    		pledgeInfoString="&catagory="+varCatagory+"&item="+varItem;
			    		rsh.openRecordStore("primayRecordStore","secondaryRecordStore");
			    		idPledgeDetails =rsh.addSecondaryRecord(idDonerInfo,pledgeInfoString);
			    		displayDataAlert=new Alert("Name","Record Sucssfully saved" + idPledgeDetails,null,AlertType.INFO);
			    		displayDataAlert.setTimeout(Alert.FOREVER);
			    		display.setCurrent(displayDataAlert);
			    	} catch (Exception e) {
			    		e.printStackTrace();
			    		displayDataAlert=new Alert("Error",e.toString(),null,AlertType.INFO);
			    		displayDataAlert.setTimeout(Alert.FOREVER);
			    		//display.setCurrent(displayDataAlert);
			    	}

			    url = "http://localhost:8080/date/today.jsp";
			    data="&catagory="+varCatagory+"&mobile="+varItem;
			    
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
			    } else {
			    	System.out.println("you are Registered user.."+networkData);
			    }
            }
    }
}

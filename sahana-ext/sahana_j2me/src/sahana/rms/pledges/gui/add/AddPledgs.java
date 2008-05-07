/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  AddPledgs.java
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

public class AddPledgs implements CommandListener {
    /*AddPledgs class*/
    private StringItem contactInfoHeading,statusInfoHeading,pledgeInfoHeading,emptyString1,emptyString2;
    private Command backCommand,submitCommand;
    private Display display;
    private Form screen;
    private Form backscreen;
    private TextField name,contact,address,comment,catagory,item;
    private ChoiceGroup catagoryGroup;
    private int catagoryGroupIndex,idDonerInfo,idPledgeDetails = 0;
    private RecordStore rsDonerInfo,rsPledgeDetails;
    private RecordEnumeration record;
    private byte[] ArrayDonerInfo;
    private String networkData,data,url;
    private String donerInfoString="";

    public AddPledgs(Display dis , Form main,String strStatus) {
        /*Get the display object for the MIDLet*/
        display=dis;
        backscreen=main;

        /*Initialize commands*/
        backCommand=new Command("Back",Command.BACK,2);
        submitCommand=new Command("Submit",Command.OK,2);
        /*Initializing the screen*/
        screen=new Form("Add Pledgs");
        contactInfoHeading=new StringItem("","Donor Contact Information");
        emptyString1=new StringItem("","         \n");
        statusInfoHeading=new StringItem("",strStatus);
        emptyString2=new StringItem("","         \n");
        screen.append(contactInfoHeading);
        screen.append(statusInfoHeading);

        /*Adding and initializing GUI components*/
        name = new TextField("Name","",50,TextField.ANY);
        screen.append(name);
        contact = new TextField("Contact","",50,TextField.ANY);
        screen.append(contact);
        address = new TextField("Address","",50,TextField.ANY);
        screen.append(address);
        comment = new TextField("Comment","",50,TextField.ANY);
        screen.append(comment);

        /*Adding commands*/
        screen.addCommand(backCommand);
        screen.addCommand(submitCommand);
        
        /*Adding Listeners to the formidDonerInfo*/
        screen.setCommandListener(this);

        display.setCurrent(screen);
    }

    public AddPledgs(Display dis , Form main, String s,String str) {
    	/*Get the display object for the MIDLet*/
        String strResult=s;
        String strTextFieldContents="";
        int indexResultFieldPointer=0;
        
        /*System.out.println("I Got this"+s.toString());*/
        display=dis;
        backscreen=main;
        
        /*Initialize commands*/
        backCommand=new Command("Back",Command.BACK,2);
        submitCommand=new Command("Submit",Command.OK,2);
        
        /*Initializing the screen*/
        screen=new Form("Add Pledgs");
        contactInfoHeading=new StringItem("","Donor Contact Information");
        emptyString1=new StringItem("","         \n");
        emptyString2=new StringItem("","         \n");
        
        screen.append(contactInfoHeading);

        /*Adding and initializing GUI components*/
        indexResultFieldPointer = strResult.indexOf("#");
        strTextFieldContents=strResult.substring(0,indexResultFieldPointer);
        strResult=strResult.substring(indexResultFieldPointer+1,strResult.length());
        
        /*System.out.println("String Part : "+strTextFieldContents);*/
        name = new TextField("Name",strTextFieldContents,50,TextField.ANY);
        screen.append(name);

        indexResultFieldPointer = strResult.indexOf("#");
        strTextFieldContents=strResult.substring(0,indexResultFieldPointer);
        strResult=strResult.substring(indexResultFieldPointer+1,strResult.length());
	    /*System.out.println("String Part : "+strTextFieldContents);*/

        contact = new TextField("Contact",strTextFieldContents,50,TextField.ANY);
        screen.append(contact);

        indexResultFieldPointer = strResult.indexOf("#");
        strTextFieldContents=strResult.substring(0,indexResultFieldPointer);
        strResult=strResult.substring(indexResultFieldPointer+1,strResult.length());
        /*System.out.println("String Part : "+strTextFieldContents);*/

        address = new TextField("Address",strTextFieldContents,50,TextField.ANY);
        screen.append(address);
        indexResultFieldPointer = strResult.indexOf("#");
        strTextFieldContents=strResult.substring(0,indexResultFieldPointer);
        comment = new TextField("Comment",strTextFieldContents,150,TextField.ANY);
        screen.append(comment);

        /*Adding commands*/
        screen.addCommand(backCommand);
        screen.addCommand(submitCommand);
        
        /*Adding Listeners to the formidDonerInfo*/
        screen.setCommandListener(this);
        display.setCurrent(screen);
    }

    public void commandAction(Command c,Displayable s) {
        if (c==backCommand) {
		    display.setCurrent(backscreen);
        }
        
        if (c==submitCommand) {
        	/*Variables for store data in data store*/
            String varName = name.getString();
            String varContact=contact.getString();
            String varAddress=address.getString();
            String varComment=comment.getString();
            RecordStoreHandler rsh=new RecordStoreHandler();
            String readStringDonerInfo="";

            donerInfoString=varName+"#"+varContact+"#"+varAddress+"#"+varComment;
	 	    Alert displayDataAlert=new Alert("Error","Error",null,AlertType.INFO);
            displayDataAlert.setTimeout(Alert.FOREVER);

                try {
			        rsh.openRecordStore("primayRecordStore");
			        idDonerInfo= rsh.searchRecords(donerInfoString);
			        System.out.println(idDonerInfo);
			        idDonerInfo=rsh.addPrimaryRecord(idDonerInfo,donerInfoString);
			        rsh.colseRecordStore();

			        if (idDonerInfo==-1) {
				        displayDataAlert=new Alert("Saving..","Record already exists in local DB.",null,AlertType.INFO);
				        System.out.println("Saving.. Record already exists in local DB.");
				    } else {
				        displayDataAlert=new Alert("Saving..","New Record Saved....\n Record id is : "+ idDonerInfo,null,AlertType.INFO);
				        System.out.println("Saving..New Record Saved....\n Record id is : "+ idDonerInfo);
				    }

			            displayDataAlert.setTimeout(Alert.FOREVER);
			            /*display.setCurrent(displayDataAlert);*/
                        url = "http:/*localhost:8080/date/today.jsp";
			            data=donerInfoString;
			    
			            new Thread(new Runnable() {
				            public void run() {
					            try {
							         send send_obj = new send();
							         networkData = send_obj.send_Data(url,data);
							         System.out.println(networkData);
					            } catch(Exception e) {
					    	
					            }
				            }}).start();

			            AddPledgeItem addPledgeItem = new AddPledgeItem(display , screen,idDonerInfo);
                } catch (Exception e) {
                    e.printStackTrace();
                    displayDataAlert=new Alert("Error",e.toString(),null,AlertType.INFO);
                    displayDataAlert.setTimeout(Alert.FOREVER);
                    display.setCurrent(displayDataAlert);
                }
        }
    }
}

/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  NewRequest.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import sahana.rms.*;
import sahana.mpr.send.*;
import sahana.rms.db.*;

/* Authors : Kasun T Karunanayake
 */

public class NewRequest implements CommandListener {
    private Display display;
    private Form form;
    private TextField requesterId;
    private List backscreen;
    private Command next;
    private Command newrequester;
    private Command back;
    private String networkData,searchKeyWord,url;
    private int primaryId;

    public NewRequest(Display dis , List main) {
        this.display = dis;
        networkData="";
     	backscreen = main;
     	form  = new Form("Request Manangement System");
     	String name = new String("Existing Requester");
     	requesterId  = new TextField("Requester ID" , "" , 50 , TextField.ANY);
     	form.append(name);
     	form.append(requesterId);
     	next  = new Command("Next" , Command.SCREEN , 2);
     	newrequester  = new Command("New Requester" , Command.OK , 2);
     	back  = new Command("Back" , Command.BACK , 2);
     	form.addCommand(next);
     	form.addCommand(newrequester);
     	form.addCommand(back);
     	form.setCommandListener(this);
     	display.setCurrent(form);
    }

    public void commandAction(Command command , Displayable displayable){
        if (command == next) {
        	String reqId = requesterId.getString();
        	/*GetHttp gh = new GetHttp("http://localhost:8080/date/requester.jsp?Id="+reqId,this);
        	gh.start();*/
        	searchKeyWord="Id="+reqId;
        	url = "http://localhost:8080/date/requester.jsp" ;
		
        	new Thread(new Runnable() {
        		public void run() {
        			try{
        				send snd = new send();
        				networkData = snd.send_Data(url , searchKeyWord);
        				System.out.println(networkData);
        			} catch(Exception e) { 
        				System.out.println(e);
        			}
        		}}).start();
		
        	if (networkData.length()>2) {
        		try {
        			RecordStoreHandler rsh=new RecordStoreHandler();
        			rsh.openRecordStore("RequestPrimayRecordStore");
					primaryId= rsh.searchRecords(networkData);
					System.out.println(primaryId);
					primaryId=rsh.addPrimaryRecord(primaryId,networkData);
					rsh.colseRecordStore();
        		} catch (Exception e) {        			
        		}

        		RequesterInfo ri = new RequesterInfo(display,networkData, form,primaryId);
        		System.out.println("Exsisting Requester");
        	}
        }

        if (command == newrequester) {
            NewRequester nr = new NewRequester( display ,form);
        }

        if (command == back) { 
        	display.setCurrent(backscreen);
        }
    }
}
/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  NewRequester.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import javax.microedition.rms.*;
import java.io.*;
import sahana.mpr.send.*;
import sahana.rms.db.*;

/* Authors : Kasun T Karunanayake
 */

public class NewRequester  implements CommandListener {
    private Form form;
	private Display display;
	private TextField fullname;
	private TextField mobile;
	private TextField email;
	private TextField telephone;
	private TextField address;
	private Form backscreen;
	private Command next;
	private Command back;
	private String networkData,fullString,url;
	private int primaryId;

	public NewRequester(Display dis , Form frm) {
		this.display = dis;
		networkData="";
		this.backscreen = frm;
		form  = new Form("New Requester");
		fullname	= new TextField("Full Name" , "" , 100 , TextField.ANY);
		mobile	= new TextField("Mobile" , "" , 100 , TextField.ANY);
		email		= new TextField("Email" , "" , 100 , TextField.ANY);
		telephone	= new TextField("Telephone" , "" , 100 , TextField.ANY);
		address	= new TextField("Address" , "" , 100 , TextField.ANY);
		next  = new Command("Next" , Command.SCREEN , 1);
		back  = new Command("Back" , Command.BACK , 1);

		form.append(fullname);
		form.append(mobile);
		form.append(email);
		form.append(telephone);
		form.append(address);

		form.addCommand(next);
		form.addCommand(back);

		form.setCommandListener(this);
		display.setCurrent(form);
	}

	public void commandAction(Command command , Displayable displayable) {
		if ( command == next ) {
			/*GetHttp gh = new GetHttp("http://localhost:8080/date/index.jsp",this);
			gh.start();*/
			String name = fullname.getString();
	        String mobile = this.mobile.getString();
	        String email = this.email.getString();
	        String tel  = telephone.getString();
	        String add  = address.getString();

	        if ( name.equals("") && mobile.equals("") && email.equals("") && tel.equals("") && add.equals("")) {
	        	Alert alert = new Alert("ERROR" , "         OOOOPS !! PLEASE ENTER ALL THE\n         DETAILS !!" , null ,AlertType.ERROR );
	            display.setCurrent(alert);
	        } else {
	        	try {
	        		RecordStoreHandler rsh=new RecordStoreHandler();
	        		rsh.openRecordStore("RequestPrimayRecordStore");
	  				fullString="name="+name+"&mobile="+mobile+"&email"+email+"&telephone"+tel+"&address"+add;
	  				int searchId= rsh.searchRecords(fullString);
	  				System.out.println(searchId);
	  				primaryId=rsh.addPrimaryRecord(searchId,fullString);
	  				rsh.colseRecordStore();
	        	} catch (Exception e) {	        		
	        	}

	  		url = "http://localhost:8080/date/next.jsp?"; //+fullString;
	  			new Thread(new Runnable() {
	  				public void run() {
	  					try {
	  						send snd = new send();
	  						String networkData = snd.send_Data(url , fullString);
	  						System.out.println(networkData);
	  					} catch(Exception e) {	  						
	  					}
	  				}}).start();

				RequestId ri = new RequestId(display, networkData);
      		}
		}

		if ( command == back ) {
			display.setCurrent(backscreen);
		}
   	}
}
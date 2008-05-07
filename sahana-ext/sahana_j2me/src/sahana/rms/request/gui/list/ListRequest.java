/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  ListRequest.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.list;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import sahana.mpr.send.*;

/* Authors : Kasun T Karunanayake
 */

public class ListRequest implements CommandListener {

    private Display display;
    private Form form;
    private ChoiceGroup status;
    private ChoiceGroup location;
    private ChoiceGroup requester;
    private List backscreen;
    private Command ok;
    private Command back;
    private String networkData,searchKeyWord,url;

    public ListRequest(Display dis , List main) {
        display = dis;
        backscreen = main;
	    networkData="";
        form = new Form("List All Requests");
        status   = new ChoiceGroup        ("Status             :   " ,Choice.POPUP);
        status.append("Open-Requests" , null);
        status.append("Closed-Requests" , null);
        status.append("All-Requests" , null);

        location	= new ChoiceGroup("Location  :   " ,Choice.POPUP);
        location.append("Colombo" , null);
        location.append("Kandy" , null);

        requester	= new ChoiceGroup("Location  :   " ,Choice.POPUP);
        requester.append("John" , null);
        requester.append("Kasun" , null);

        ok    = new Command("OK" , Command.SCREEN , 1);
        back  = new Command("BACK" , Command.BACK , 2);

        form.append(status);
        form.append(location);
        form.append(requester);
        form.addCommand(ok);
        form.addCommand(back);
        form.setCommandListener(this);

        display.setCurrent(form);
    }

    public void commandAction(Command command , Displayable displayable) {
        if (command == ok) {
            String stat = status.getString(status.getSelectedIndex());
            String loc = location.getString(location.getSelectedIndex());
            String req = requester.getString(requester.getSelectedIndex());

            System.out.println(stat+loc+req);

      		searchKeyWord="status="+stat+"&location="+loc+"&requester="+req;
	  		url = "http://localhost:8080/date/list.jsp" ;

	  		new Thread(new Runnable() {
	  		    public void run() {
	  			    try {
	  				    send snd = new send();
	  				    networkData = snd.send_Data(url , searchKeyWord);
	  				    System.out.println(networkData);
	  			    } catch(Exception e) {
						System.out.println(e);
	  				}
	  		    }}).start();

	  	    ListInfo li = new ListInfo(display,networkData, form);
        } else if (command == back) {
            display.setCurrent(backscreen);
        }
    }//end method
}
/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Search.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.search;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import sahana.rms.request.gui.newr.RequesterInfo;
import sahana.mpr.send.*;

/* Authors : Kasun T Karunanayake
 */

public class Search implements CommandListener {

    private Display display;
    private Form form;
    private List backscreen;
    private TextField searchId;
    private Command search;
    private Command back;
    private String networkData,searchKeyWord,url;

    public Search(Display dis , List main) {

        this.display = dis;
        backscreen = main;
        form  = new Form("Search");

        String name = new String("Search for Requesters , Location and Requests");
        searchId  = new TextField("Search Keywords" , "" , 50 , TextField.ANY);

        form.append(name);
        form.append(searchId);

        search  = new Command("Next" , Command.SCREEN , 1);
        back  = new Command("Back" , Command.BACK , 1);

        form.addCommand(search);
        form.addCommand(back);

        form.setCommandListener(this);
        display.setCurrent(form);
    }

    public void commandAction(Command command , Displayable displayable) {
        if (command == search) {
		   /*searchKeyWord = "name="+searchId.getString();
           url = "http://localhost:8080/date/next.jsp" ;*/

		   searchKeyWord="donerId="+searchId.getString()+"&requestId=0";
		   url = "http://localhost:8080/date/today.jsp" ;
		   networkData="";

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

		   SearchInfo ri = new SearchInfo(display,networkData, form);
        }

        if (command == back) {
            display.setCurrent(backscreen);
        }
    }
}
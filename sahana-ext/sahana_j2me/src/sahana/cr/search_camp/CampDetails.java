/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  CampDetails.java
 * @date       24 July 2006
 */

package sahana.cr.search_camp;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import java.lang.String;
import sahana.mpr.send.*;

/* Author : Muguntha Ramachandran
 */

public class CampDetails implements CommandListener {
    public final static Command CMD_BACK =new Command("Back", Command.BACK, 1);
    public Display display;
    public String array;
    public List allcamps,bylocation,admindetails,byname,mainList,backscreen;

    public CampDetails(Display d, List l) {
        display = d;
		backscreen = l;

    }

    public void create() {
        mainList = new List("Camp Reports", Choice.IMPLICIT);
        mainList.append("1. View All Camps",null);
	    mainList.append("2. View By Location",null);
	    mainList.append("3. View Admin Details",null);
        mainList.append("4. View By Camp Name",null);

        mainList.addCommand(CMD_BACK);
        mainList.setCommandListener(this);

        display.setCurrent(mainList);

    }

    public void commandAction(Command c, Displayable d) {
        if (c == mainList.SELECT_COMMAND) {
            if (d.equals(mainList)) {
                switch (((List)d).getSelectedIndex()) {
                    case 0:
                        new Thread(new Runnable() {
						    public void run() {
                                String url = "http://localhost:8080/sahana_php/cr/get_key.php";
                                String key="key=all";
								send send_obj = new send();
								String value = send_obj.send_Data(url,key);
								Result ft = new Result(display, mainList, value);

							}
						}).start();

                                break;

                   case 1:

						new Thread(new Runnable() {
						    public void run() {
					            view_by v_b = new view_by(display,mainList);
							}
						}).start();

						break;

				  case 2:


						new Thread(new Runnable() {
						    public void run() {
								String url = "http://localhost:8080/sahana_php/cr/get_key.php";
								String key="key=admin_all";
								send send_obj = new send();
								String value = send_obj.send_Data(url,key);
								Result ft = new Result(display, mainList, value);
							}
						}).start();

                        break;

                  case 3:


						new Thread(new Runnable() {
                            public void run() {
                                 search_by_name s_b = new search_by_name(display,mainList);

							}
						}).start();
                 }
             }
         }

        		if (c == CMD_BACK)
        		{
            	display.setCurrent(backscreen);
        		}
    }
}







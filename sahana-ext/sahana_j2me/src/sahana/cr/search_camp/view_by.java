/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  view_by.java
 * @date       24 July 2006
 */

package sahana.cr.search_camp;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import java.lang.String;
import sahana.mpr.send.*;

/* Author : Muguntha Ramachandran
 */

public class view_by implements CommandListener {

    public Display display;
    public List by_List,back;
	public final static Command cmd_Back = new Command("Back", Command.BACK, 1);

    public view_by(Display dis, List l) {
        this.display = dis;
 		this.back = l;

        by_List = new List("View By Location", Choice.IMPLICIT);
        by_List.append("1. Northern",null);
		by_List.append("2. Eastern",null);
		by_List.append("3. Southern",null);
		by_List.append("4. Western",null);

        by_List.addCommand(cmd_Back);
        by_List.setCommandListener(this);

		display.setCurrent(by_List);

    }

     public void commandAction(Command c, Displayable s) {
        if (c == cmd_Back) {
	        display.setCurrent(back);
	    }
            if (c == List.SELECT_COMMAND) {
	            if (s.equals(by_List)) {
	                switch ( ( (List) s).getSelectedIndex()) {
	                    case 0:

					        new Thread(new Runnable() {
		                        public void run() {
							        String url = "http://localhost:8080/sahana_php/cr/get_key.php";
							        String key="key=northern";
								    send send_obj = new send();
								    String value = send_obj.send_Data(url,key);
								    Result ft = new Result(display, by_List, value);
				    		    }
				    	    }).start();
	              		   break;

	                   case 1:

					       new Thread(new Runnable() {
						       public void run() {
							       String url = "http://localhost:8080/sahana_php/cr/get_key.php";
							       String key="key=eastern";
								   send send_obj = new send();
								   String value = send_obj.send_Data(url,key);
								   Result ft = new Result(display, by_List, value);
							   }

						   }).start();
	              		   break;

	                  case 2:

	            	      new Thread(new Runnable() {
						      public void run() {
							      String url = "http://localhost:8080/sahana_php/cr/get_key.php";
							      String key="key=southern";
								  send send_obj = new send();
								  String value = send_obj.send_Data(url,key);
								  Result ft = new Result(display, by_List, value);
							  }
					      }).start();
	              		  break;

	                 case 3:
				 	      new Thread(new Runnable() {
				 	          public void run() {
							      String url = "http://localhost:8080/sahana_php/cr/get_key.php";
							      String key="key=western";
								  send send_obj = new send();
								  String value = send_obj.send_Data(url,key);
								  Result ft = new Result(display, by_List, value);
				 			  }
				 		 }).start();
				         break;
	            }
	        }
	    }
    }
}









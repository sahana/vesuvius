/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  search_by_name.java
 * @date       24 July 2006
 */

package sahana.cr.search_camp;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import java.lang.String;
import sahana.mpr.send.*;
import sahana.mpr.message.*;

/* Author : Muguntha Ramachandran
 */

public class search_by_name  implements CommandListener {
    public final static  Command CMD_OK = new Command("OK", Command.OK, 1);
	public final static Command CMD_BACK = new Command("Back", Command.BACK, 1);

	public Display display;
	public TextField c_name;
    public String c_n;
    List back;
    public TextBox textbox;
	public StringItem campname;
	public Form form;

    public search_by_name(Display dis, List list) {
	    this.back = list;
	    this.display=dis;

	    form = new Form("View By Camp Name");
	    StringItem campname = null;

	    c_name=new TextField("Camp Name", "", 15, TextField.ANY);
	    form.append(c_name);
	    form.addCommand(CMD_BACK);
	    form.setCommandListener(this);
	    form.addCommand(CMD_OK);
	    form.setCommandListener(this);

        display.setCurrent(form);
    }


    public void commandAction(Command c, Displayable d) {
        if (c == CMD_OK) {
            c_n = c_name.getString();
			    new Thread(new Runnable() {
			        public void run() {
				        String url = "http://localhost:8080/sahana_php/cr/get_key.php";
				        String key="key"+c_n;
				        send send_obj = new send();
					    String value = send_obj.send_Data(url,key);
					    message msg = new message(display, form, value);

				    }
			    }).start();
		}

	    if (c == CMD_BACK) {
		    display.setCurrent(back);
        }
    }
}
/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  RequestId.java
 * @date       24 July 2006
 */


package sahana.rms.request.gui.newr;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

/* Authors : Kasun T Karunanayake
 */

public class RequestId implements CommandListener {
    private Display display;
    private Form form;
    private Command next;
    private String id;

    public RequestId(Display dis , String id) {
    	display = dis;
    	this.id = id;
    	form  = new Form("Request ID");
    	String ide = new String(id);
    	form.append(id);
    	next  = new Command("Next" , Command.SCREEN , 1);
    	form.addCommand(next);
    	form.setCommandListener(this);
    	display.setCurrent(form);
    }

    public void commandAction(Command command , Displayable displayable) {
    	if (command == next) {
    		NewLocation nl = new NewLocation(display,-1);
    	}
    }
}
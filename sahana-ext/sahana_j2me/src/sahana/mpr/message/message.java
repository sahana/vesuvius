/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  message.java
 * @date       24 July 2006
 */


package sahana.mpr.message;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;

/* Author : Sahan C Priyadarshana
 */

public class message implements CommandListener {

    public TextBox txt_area;
    public Form form;
    public Display display;
    public String str;

    public final static Command CMD_BACK = new Command("Back", Command.BACK, 1);

    public message(Display dis,Form fm, String para) {

        this.display=dis;
        this.form=fm;
        this.str=para;

        if(str.equals(" ")) {
	        txt_area = new TextBox("Result", "Successfully Saved!" , 1024, TextField.ANY);
        }  else {
	        txt_area = new TextBox("Result", str , 1024, TextField.ANY);
           }

            txt_area.addCommand(CMD_BACK);
            txt_area.setCommandListener(this);
            display.setCurrent(txt_area);
    }

    public void commandAction(Command c, Displayable s ) {

	    if(c == CMD_BACK){
            display.setCurrent(form);
        }
    }
}

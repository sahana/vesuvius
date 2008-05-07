/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  search_Form.java
 * @date       24 July 2006
 */


package sahana.mpr.forms;

import javax.microedition.midlet.MIDlet;
import javax.microedition.lcdui.*;
import sahana.mpr.search.*;

/* Author : Sahan C Priyadarshana
 */

public class search_Form implements CommandListener, ItemCommandListener {

    Display display;
    Form form;
    List back;
    public final static Command cmd_Back = new Command("Back", Command.BACK, 1);
    public final static Command cmd_Ok1 = new Command("Ok", Command.ITEM, 1);
    public final static Command cmd_Ok2 = new Command("Ok", Command.ITEM, 1);
    StringItem name,id;

    public search_Form(Display display, List list) {

	    this.back = list;
	    this.display=display;

        form = new Form("Search Options");
        display.setCurrent(form);
    }

    public void create() {

	    name = new StringItem("Search By Any Name","");
	    id = new StringItem("Search By Any Card No","");
	    name.setDefaultCommand(cmd_Ok1);
	    name.setItemCommandListener(this);

	    id.setDefaultCommand(cmd_Ok2);
	    id.setItemCommandListener(this);

	    form.append(name);
	    form.append(id);
	    form.addCommand(cmd_Back);
	    form.setCommandListener(this);
    }

    public void commandAction(Command c, Item item) {

	    if (c == cmd_Ok1) {
	  	    by_name name_obj = new by_name(display,form);
	  	    name_obj.create();
	    }

	    if (c == cmd_Ok2) {
	  	    by_id id_obj = new by_id(display,form);
	  	    id_obj.create();
	    }
    }

    public void commandAction(Command c, Displayable d) {

 	    if (c == cmd_Back) {
 		    display.setCurrent(back);
 	    }
    }
}
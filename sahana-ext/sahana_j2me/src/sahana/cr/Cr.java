/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Cr.java
 * @date       24 July 2006
 */

package sahana.cr;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;
import sahana.cr.add_camp.*;
import sahana.cr.search_camp.*;

/* Authors : Pradeep Senanayaka
 *           Muguntha Ramachandran
 */

public class Cr implements CommandListener {

    public Command backCommand = new Command("Back", Command.BACK, 1);
    public Display display;
    public List first,backscreen;
    public Cr(Display d, List l) {

    display = d;
	backscreen = l;
    first = new List("Camps Registry", Choice.IMPLICIT);
    first.append("Add a Camp",null); //form
    first.append("Search a Camp",null);
    first.setCommandListener(this);
    first.addCommand(backCommand);
    first.setCommandListener(this);
    display.setCurrent(first);

    }

    public void commandAction(Command c, Displayable s) {
        try {
            if (c == List.SELECT_COMMAND) {
                if (s.equals(first)) {
                    switch ( ( (List) s).getSelectedIndex()) {
                        case 0:
		                    Midclass mc = new Midclass(display,first);
		                    mc.create_form();
              	        break;

                        case 1:
            	            CampDetails cd = new CampDetails(display,first);
            	            cd.create();
                        break;

                    }
                }
            }
        }
        catch (Exception e) {
        }

       if(c == backCommand) {
	       display.setCurrent(backscreen);
       }
   }
}


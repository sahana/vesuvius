/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Rms.java
 * @date       24 July 2006
 */


package sahana.rms;

import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;
import sahana.rms.request.gui.newr.*;
import sahana.rms.request.gui.search.*;
import sahana.rms.request.gui.list.*;
import sahana.rms.pledges.gui.add.*;
import sahana.rms.pledges.gui.search.*;
import sahana.rms.pledges.gui.view.*;

/* Authors : Kasun T Karunanayake
 *           Michelle Narangoda
 */

public class Rms implements CommandListener {

   public Display display;
   public List mainscreen,backscreen;
   public Command back;


   public Rms(Display dis , List bs) {
      backscreen=bs;
      display = dis;

      /*requests*/

      mainscreen = new List("Request Management System" , Choice.IMPLICIT);
      mainscreen.append("Requests",null);
      mainscreen.append("      1. New Request",null);
      mainscreen.append("      2. List All Requests",null);
      mainscreen.append("      3. Search Requests",null);

      /*pledges*/
      mainscreen.append("Pledges",null);
      mainscreen.append("      1. New Pledges ", null);
      mainscreen.append("      2. List All Pledges",null);
      mainscreen.append("      3. Search Pledges",null);

      back = new Command("Back" , Command.BACK , 1);
      mainscreen.addCommand(back);
      mainscreen.setCommandListener(this);
      display.setCurrent(mainscreen);
   }

   public void commandAction(Command command , Displayable dis) {

      if ( command == mainscreen.SELECT_COMMAND ) {

           int index = mainscreen.getSelectedIndex();

           if ( index == 1 ) {
               NewRequest request = new NewRequest(display , mainscreen);
            } else if ( index == 2) {
                ListRequest list = new ListRequest(display , mainscreen);
            } else if ( index == 3 ) {
                Search search = new Search(display , mainscreen);
            } else if ( index == 5) {
                DonerSearchId addPledgs = new DonerSearchId(display , mainscreen);
            } else if ( index == 6) {
                ListPledges listPledges = new ListPledges(display , mainscreen);
            } else if ( index == 7) {
                ViewPledges viewPledges = new ViewPledges(display , mainscreen);
            }

      } else if ( command == back ) {
          display.setCurrent(backscreen);
      }
   }
}




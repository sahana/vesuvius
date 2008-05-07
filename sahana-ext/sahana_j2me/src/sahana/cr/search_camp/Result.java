/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Result.java
 * @date       24 July 2006
 */

package sahana.cr.search_camp;

import javax.microedition.lcdui.*;
import javax.microedition.midlet.*;

/* Author : Muguntha Ramachandran
 */

public class Result implements CommandListener {

    public TextBox txt_area;
    public List lt;
    public Display display;
    public String out;

    public final static Command CMD_BACK = new Command("Back", Command.BACK, 1);


    public Result(Display dis,List lts,String str) {
        this.display=dis;
        this.lt=lts;
        this.out=str;

        txt_area = new TextBox("View Camp Details - Result", out , 1024, TextField.ANY);
        txt_area.addCommand(CMD_BACK);
        txt_area.setCommandListener(this);
        display.setCurrent(txt_area);

    }

    public void commandAction(Command c, Displayable s ) {

        if(c == CMD_BACK) {
            display.setCurrent(lt);
        }
    }
}
/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Network.java
 * @date       24 July 2006
 */


package sahana.rms.net;

import java.io.*;
import javax.microedition.io.*;

/* Authors : Kasun T Karunanayake
 */

public abstract class Network {
    public abstract void getData(StringBuffer s);
	public void displayData(StringBuffer s)	{
	    System.out.println(s.toString());
	}	
}
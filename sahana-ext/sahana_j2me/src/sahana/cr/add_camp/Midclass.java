/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  Midclass.java
 * @date       24 July 2006
 */

package sahana.cr.add_camp;

import javax.microedition.midlet.MIDlet;
import javax.microedition.lcdui.*;
import java.lang.String;

/* Author : Pradeep Senanayaka
 */

public class Midclass implements CommandListener {

    public Command backCommand   = new Command("Back", Command.BACK, 1);
    public Command sendCommand   = new Command("Send Record", Command.SCREEN, 5);
    public Command nextCommand   = new Command("Next", Command.SCREEN, 1);
    public Command viewCommand   = new Command("View Records", Command.SCREEN, 3);
    public Command deleteCommand = new Command("Delete Records", Command.SCREEN, 4);
    public Command saveCommand   = new Command("Save Records", Command.SCREEN, 2);
    public Display display;
    public MidDisplay md;
    public TextField campName,campType,address,country,region,province,city,fullName,phoneNumber,mobileNumber,occupation,familyCount,totalCount,men,women,children,index_rec;
    public String st17,st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16;
    String[] array = {st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16,st17};
    public TextBox textbox;
    public boolean firstTime;
    public StringItem str;
    public Form mainForm;
    public List backscreen;

    public Midclass(Display d, List l) {

	    this.backscreen = l;
	    this.display=d;
        mainForm = new Form("Add Camp");
        StringItem str = null;
    }

    public void create_form() {

        str = new StringItem("Register New Camp","");
        mainForm.append(str);
        mainForm.append("General Details");
        campName=new TextField("Camp Name", "", 15, TextField.ANY);
        mainForm.append(campName);
        campType=new TextField("Camp Type", "", 15, TextField.ANY);
        mainForm.append(campType);
        address=new TextField("Address", "", 20, TextField.ANY);
        mainForm.append(address);
        mainForm.append("Base Location");
        country=new TextField("Country", "", 15, TextField.ANY);
        mainForm.append(country);
        region=new TextField("Region", "", 15, TextField.ANY);
        mainForm.append(region);
        province=new TextField("Province", "", 15, TextField.ANY);
        mainForm.append(province);
        city=new TextField("City ", "", 15, TextField.ANY);
        mainForm.append(city);
        mainForm.append("Contact Person Details");
        fullName=new TextField("Full Name","",15,TextField.ANY);
        mainForm.append(fullName);
        phoneNumber=new TextField("Phone Number","",15,TextField.PHONENUMBER);
        mainForm.append(phoneNumber);
        mobileNumber=new TextField("Mobile Number","",15,TextField.PHONENUMBER);
        mainForm.append(mobileNumber);
        occupation=new TextField("Occupation","",15,TextField.ANY);
        mainForm.append(occupation);
        mainForm.append("Camp Population");
        familyCount=new TextField("Family Count","",4,TextField.NUMERIC);
        mainForm.append(familyCount);
        totalCount=new TextField("Total Count","",4,TextField.NUMERIC);
        mainForm.append(totalCount);
        men=new TextField("Men","",4,TextField.NUMERIC);
        mainForm.append(men);
        women=new TextField("Women","",4,TextField.NUMERIC);
        mainForm.append(women);
        children=new TextField("Children","",4,TextField.NUMERIC);
        mainForm.append(children);

        mainForm.addCommand(backCommand);
        mainForm.setCommandListener(this);
        mainForm.addCommand(sendCommand);
        mainForm.setCommandListener(this);
        mainForm.addCommand(nextCommand);
        mainForm.setCommandListener(this);
        mainForm.addCommand(viewCommand);
	    mainForm.setCommandListener(this);
	    mainForm.addCommand(deleteCommand);
        mainForm.setCommandListener(this);
        mainForm.addCommand(saveCommand);
        mainForm.setCommandListener(this);

        display.setCurrent(mainForm);

    }

    public void commandAction(Command c, Displayable displayable) {

        if (c == nextCommand) {
            st1 = campName.getString();
            st2 = campType.getString();
            st3 = address.getString();
            st4 = country.getString();
            st5 = region.getString();
            st6 = province.getString();
            st7 = city.getString();
            st8 = fullName.getString();
            st9 = phoneNumber.getString();
            st10= mobileNumber.getString();
            st11= occupation.getString();
            st12= familyCount.getString();
            st13= totalCount.getString();
            st14= men.getString();
            st15= women.getString();
            st16= children.getString();

            String[] array = {st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16};

            MidDisplay md = new MidDisplay(display, array, mainForm);
        }

        if (c == backCommand) {

	        display.setCurrent(backscreen);
	    }

        if(c == viewCommand) {

            MidRecords midRec = new MidRecords(display , mainForm);
            midRec.viewRecords();
	    }

        if(c == deleteCommand) {

            MidRecords midRec = new MidRecords(display , mainForm);
            midRec.delRec();
	    }

        if(c == sendCommand) {

            MidRecords midrec = new MidRecords(display , mainForm);
            midrec.sendRec();
	    }

        if(c == saveCommand) {
            st1 = campName.getString();
		    st2 = campType.getString();
		    st3 = address.getString();
		    st4 = country.getString();
		    st5 = region.getString();
		    st6 = province.getString();
		    st7 = city.getString();
		    st8 = fullName.getString();
		    st9 = phoneNumber.getString();
		    st10= mobileNumber.getString();
		    st11= occupation.getString();
		    st12= familyCount.getString();
		    st13= totalCount.getString();
		    st14= men.getString();
		    st15= women.getString();
		    st16= children.getString();


            String[] array = {st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16};

            MidRecords midRec = new MidRecords(display , mainForm);

            midRec.saveRec(array);
        }
    }
}

/**
 * Sahana J2ME Client
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    Sahana J2ME
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @classname  form_1.java
 * @date       24 July 2006
 */


package sahana.mpr.forms;

import java.io.*;
import javax.microedition.io.*;
import javax.microedition.midlet.MIDlet;
import javax.microedition.lcdui.*;
import java.util.*;
import java.lang.String;
import sahana.mpr.*;

/* Author : Sahan C Priyadarshana
 */

public class form_1  implements CommandListener {

    public Display display;
    public final static Command CMD_BACK = new Command("Back", Command.BACK, 1);
    public final static Command CMD_NEXT = new Command("Next", Command.ITEM, 1);
    public String form_url,form_data,S_f_Name,S_id,S_driving_Lisence,S_passport,S_birthday,S_age_group,S_gender,S_phone,S_country,S_province,S_district,S_village,S_address,S_last_Seen,S_last_Clothing;
    List backscreen;
    Image icon=null;
    public TextField f_Name,id,passport,driving_Lisence,birthday,address,phone,province,district,village,last_Seen,last_Clothing;
 	public ChoiceGroup age_choice,sex_choice,country_choice;
 	public Form mainForm;

    public form_1(Display display, List backscreen) {

        this.display=display;
        this.backscreen=backscreen;

        mainForm = new Form("Report a Missing Person");
        display.setCurrent(mainForm);
        mainForm.addCommand(CMD_BACK);
        mainForm.setCommandListener(this);
        mainForm.addCommand(CMD_NEXT);
        mainForm.setCommandListener(this);

    }

    public void CreateForm() {

        f_Name = new TextField("Name", "", 40, TextField.ANY);
	    id = new TextField("NIC", "", 15, TextField.ANY);
        passport = new TextField("Passport No", "", 10, TextField.ANY);
	    driving_Lisence = new TextField("Driving Lisence","", 10, TextField.ANY);
	    birthday = new TextField("Birth Day", "yyyy-mm-dd", 10, TextField.ANY);
	    phone = new TextField("Phone", "", 13, TextField.PHONENUMBER);
	    phone.setMaxSize(13);
	    province = new TextField("Province", "", 15, TextField.ANY);
	    district = new TextField("District", "", 15, TextField.ANY);
	    village = new TextField("Village", "", 15, TextField.ANY);
	    address = new TextField("Address","",30,TextField.ANY);
	    last_Seen = new TextField("Last Seen","",20,TextField.ANY);
	    last_Clothing = new TextField("Last Clothing","",20,TextField.ANY);

	    sex_choice = new ChoiceGroup("Sex", Choice.POPUP);
	    int sex_Index = sex_choice.append("Unknown", null);
	    sex_choice.append("Male", null);
	    sex_choice.append("Female", null);
        sex_choice.setSelectedIndex(sex_Index, true);

	    country_choice = new ChoiceGroup("Country", Choice.POPUP);
	    int country_Index = country_choice.append("Unknown", null);
	    country_choice.append("Sri Lanka", null);
	    country_choice.append("Indonesia", null);
	    country_choice.append("USA", null);
        country_choice.setSelectedIndex(country_Index, true);

	    age_choice = new ChoiceGroup("Age Group", Choice.POPUP);
	    int age_Index = age_choice.append("Unknown", null);
	    age_choice.append("Infant(0-1)", null);
	    age_choice.append("Child(1-15)", null);
	    age_choice.append("Young_adult(16-21)", null);
	    age_choice.append("Adult(22-50)", null);
	    age_choice.append("Senior_citizen(50)", null);
        age_choice.setSelectedIndex(age_Index, true);


        mainForm.append(f_Name);
        mainForm.append(id);
        mainForm.append(driving_Lisence);
        mainForm.append(passport);
        mainForm.append(birthday);
	    mainForm.append(age_choice);
	    mainForm.append(sex_choice);
	    mainForm.append(address);
	    mainForm.append(phone);
	    mainForm.append(country_choice);
	    mainForm.append(province);
	    mainForm.append(district);
	    mainForm.append(village);
	    mainForm.append(last_Seen);
	    mainForm.append(last_Clothing);

    }


    public void valiDate() {

       S_f_Name = f_Name.getString();
       S_id = id.getString();
       S_driving_Lisence = driving_Lisence.getString();
       S_passport = passport.getString();
       S_birthday = birthday.getString();
       S_phone = phone.getString();
       S_province = province.getString();
       S_district = district.getString();
       S_village = village.getString();
       S_address = address.getString();
       S_last_Seen = last_Seen.getString();
       S_last_Clothing = last_Clothing.getString();


       if(S_f_Name.equals(""))
           S_f_Name=null;
       if(S_id.equals(""))
           S_id=null;
       if(S_driving_Lisence.equals(""))
           S_driving_Lisence=null;
       if(S_passport.equals(""))
           S_passport=null;
       if(S_birthday.equals(""))
           S_birthday=null;
       if(S_phone.equals(""))
           S_phone=null;
       if(S_province.equals(""))
           S_province=null;
       if(S_district.equals(""))
           S_district=null;
       if(S_village.equals(""))
           S_village=null;
       if(S_address.equals(""))
           S_address=null;
       if(S_last_Seen.equals(""))
           S_last_Seen=null;
       if( S_last_Clothing.equals(""))
           S_last_Clothing=null;

    }

    public void commandAction(Command c, Displayable s ) {

	    if(c == CMD_BACK) {
            display.setCurrent(backscreen);
        }

	    if(c == CMD_NEXT) {
            int rid=0;
  	        boolean add=false;
            valiDate();

		    S_country = age_choice.getString(age_choice.getSelectedIndex());
	 	    S_age_group = sex_choice.getString(sex_choice.getSelectedIndex());
	 	    S_gender = country_choice.getString(country_choice.getSelectedIndex());

 		    form_data=S_f_Name+"," +S_id+ "," +S_driving_Lisence+","+S_passport+","+S_birthday+","+S_age_group+","+S_gender+","+S_phone+ "," +S_country+","+S_province+","+S_district+","+S_village+","+S_address+","+S_last_Seen+ "," +S_last_Clothing+",";
		    form_url = "full_name="+S_f_Name+"&idcard="+S_id+"&drv_license="+S_driving_Lisence+"&passport="+S_passport+"&dob="+S_birthday+"&opt_age_group="+S_age_group+"&opt_gender="+S_gender+"&phone="+S_phone+"&address="+S_address+"&country="+S_country+"&province="+S_province+"&district="+S_district+"&village="+S_village+"&last_seen="+S_last_Seen+"&last_cloth="+S_last_Clothing;
	 	    form_2 f_2 = new form_2(display,mainForm,form_data,form_url);
	 	    f_2.createForm();

	    }
    }
}

package sahana.algo.associations;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.Reader;
import java.util.Enumeration;

import sahana.DMAlgorithm;
import weka.core.Instances;
import weka.core.Option;
import weka.core.Utils;

public class Apriori extends weka.associations.Apriori implements DMAlgorithm
{

	public String mine(String[] options)
	{
		for(int i=0;i<options.length;++i)
            System.out.println(options[i]);
        
        String trainFileString;
        StringBuffer text = new StringBuffer();
        Apriori apriori = new Apriori();
        Reader reader;
        
        try
        {
            text.append("\n\nApriori options:\n\n");
            text.append("-t <training file>\n");
            text.append("\tThe name of the training file.\n");
            Enumeration enu = apriori.listOptions();
            while (enu.hasMoreElements())
            {
                Option option = (Option)enu.nextElement();
                text.append(option.synopsis()+'\n');
                text.append(option.description()+'\n');
            }
            trainFileString = Utils.getOption('t', options);
            if (trainFileString.length() == 0)
                throw new Exception("No training file given!");
            apriori.setOptions(options);
            reader = new BufferedReader(new FileReader(trainFileString));
            apriori.buildAssociations(new Instances(reader));
            return apriori.toString();
        }
        catch(Exception e)
        {
            e.printStackTrace();
            System.out.println("\n"+e.getMessage()+text);
            return e.toString();
            
        }
        //return null;
	}

}

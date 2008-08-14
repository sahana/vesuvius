package sahana.algo.associations;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.Reader;
import java.util.Enumeration;

import sahana.DMAlgorithm;
import weka.core.Instances;
import weka.core.Option;
import weka.core.Utils;

public class Tertius extends weka.associations.Tertius implements DMAlgorithm
{

	@Override
	public String mine(String[] options)throws Exception
	{
		String trainFileString;
		Reader reader;
		Instances instances;
		Tertius tertius = new Tertius();
		StringBuffer text = new StringBuffer();

		try
		{
			/* Help string giving all the command line options. */
			text.append("\n\nTertius options:\n\n");
			text.append("-t <name of training file>\n");
			text.append("\tSet training file.\n");
			Enumeration enu = tertius.listOptions();
			while (enu.hasMoreElements())
			{
				Option option = (Option) enu.nextElement();
				text.append(option.synopsis() + "\n");
				text.append(option.description() + "\n");
			}

			/* Training file. */
			trainFileString = Utils.getOption('t', options);
			if (trainFileString.length() == 0)
			{
				throw new Exception("No training file given!");
			}
			try
			{
				reader = new BufferedReader(new FileReader(trainFileString));
			} catch (Exception e)
			{
				throw new Exception("Can't open file " + e.getMessage() + ".");
			}

			instances = new Instances(reader);

			/* Tertius options. */
			tertius.setOptions(options);
			Utils.checkForRemainingOptions(options);

			/* Build the rules and output the results. */
			tertius.buildAssociations(instances);
			return tertius.toString();

		} catch (Exception e)
		{
			System.err.println("\nWeka exception: " + e.getMessage() + text);
			throw e;
		}
		//return null;
	}

}

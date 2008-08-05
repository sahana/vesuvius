package sahana.algo.associations;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.Reader;
import java.util.Enumeration;
import sahana.DMAlgorithm;
import weka.core.Instances;
import weka.core.Option;
import weka.core.Utils;

public class PredictiveApriori extends weka.associations.PredictiveApriori
		implements DMAlgorithm
{

	@Override
	public String mine(String[] options)
	{
		String trainFileString;
		StringBuffer text = new StringBuffer();
		PredictiveApriori apriori = new PredictiveApriori();
		Reader reader;

		try
		{
			text.append("\n\nPredictiveApriori options:\n\n");
			text.append("-t <training file>\n");
			text.append("\tThe name of the training file.\n");
			Enumeration enu = apriori.listOptions();
			while (enu.hasMoreElements())
			{
				Option option = (Option) enu.nextElement();
				text.append(option.synopsis() + '\n');
				text.append(option.description() + '\n');
			}
			trainFileString = Utils.getOption('t', options);
			if (trainFileString.length() == 0)
				throw new Exception("No training file given!");
			apriori.setOptions(options);
			reader = new BufferedReader(new FileReader(trainFileString));
			apriori.buildAssociations(new Instances(reader));
			return apriori.toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.out.println("\n" + e.getMessage() + text);
		}
		return null;
	}

}

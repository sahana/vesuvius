package sahana;

import java.util.StringTokenizer;

/*
 * Miner.java
 *
 * Created on June 9, 2008, 10:10 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 * 
 * @author miyuru
 */
public class Miner
{

	/** Creates a new instance of Miner */
	public Miner()
	{
	}

	public static String mineData(String algo, String[] input)
	{
		StringTokenizer token = new StringTokenizer(algo);
		String type = token.nextToken();
		String variant = token.nextToken();
		String ret = null;

		/*if (type.equalsIgnoreCase("classifiers"))// classification selection
		{
			if (variant.equalsIgnoreCase("bayes.AODE"))
			{
				ret = new sahana.algo.classifiers.bayes.AODE().mine(input);
			} else if (variant.equalsIgnoreCase("bayes.BayesNet"))
			{
				ret = weka.classifiers.bayes.BayesNet.main(input);
			} else if (variant.equalsIgnoreCase("bayes.ComplementNaiveBayes"))
			{
				ret = weka.classifiers.bayes.ComplementNaiveBayes.main(input);
			} else if (variant.equalsIgnoreCase("bayes.NaiveBayes"))
			{
				ret = weka.classifiers.bayes.NaiveBayes.main(input);
			} else if (variant.equalsIgnoreCase("bayes.NaiveBayesMultinomial"))
			{
				ret = weka.classifiers.bayes.NaiveBayesMultinomial.main(input);
			} else if (variant.equalsIgnoreCase("bayes.NaiveBayesSimple"))
			{
				ret = weka.classifiers.bayes.NaiveBayesSimple.main(input);
			} else if (variant.equalsIgnoreCase("bayes.NaiveBayesUpdateable"))
			{
				ret = weka.classifiers.bayes.NaiveBayesUpdateable.main(input);
			}
		} else */if (type.equalsIgnoreCase("associations"))
		{
			if (variant.equalsIgnoreCase("Apriori"))
			{
				ret = new sahana.algo.associations.Apriori().mine(input);
			}
		}/* else if (type.equalsIgnoreCase("clusterers"))
		{
			if (variant.equalsIgnoreCase("em"))
			{
				ret = weka.clusterers.EM.main(input);
			}
		}*/
		return ret;
	}
}
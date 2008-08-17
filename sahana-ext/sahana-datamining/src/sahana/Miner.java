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

	public static String mineData(String algo, String[] input) throws Exception
	{
		StringTokenizer token = new StringTokenizer(algo);
		String type = token.nextToken();
		String variant = token.nextToken();
		String ret = null;

		if (type.equalsIgnoreCase("classifiers"))// classification selection
		{
			if (variant.equalsIgnoreCase("bayes.AODE"))
			{
				ret = new sahana.algo.classifiers.bayes.AODE().mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.BayesNet"))
			{
				ret = new sahana.algo.classifiers.bayes.BayesNet().mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.ComplementNaiveBayes"))
			{
				ret = new sahana.algo.classifiers.bayes.ComplementNaiveBayes()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.NaiveBayes"))
			{
				ret = new sahana.algo.classifiers.bayes.NaiveBayes()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.NaiveBayesMultinomial"))
			{
				ret = new sahana.algo.classifiers.bayes.NaiveBayesMultinomial()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.NaiveBayesSimple"))
			{
				ret = new sahana.algo.classifiers.bayes.NaiveBayesSimple()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("bayes.NaiveBayesUpdateable"))
			{
				ret = new sahana.algo.classifiers.bayes.NaiveBayesUpdateable()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.LeastMedSq"))
			{
				ret = new sahana.algo.classifiers.functions.LeastMedSq()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.LinearRegression"))
			{
				ret = new sahana.algo.classifiers.functions.LinearRegression()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.Logistic"))
			{
				ret = new sahana.algo.classifiers.functions.Logistic()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.MultilayerPerceptron"))
			{
				ret = new sahana.algo.classifiers.functions.MultilayerPerceptron()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.PaceRegression"))
			{
				ret = new sahana.algo.classifiers.functions.PaceRegression()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.RBFNetwork"))
			{
				ret = new sahana.algo.classifiers.functions.RBFNetwork()
						.mine(input);
			}
			else if (variant
					.equalsIgnoreCase("functions.SimpleLinearRegression"))
			{
				ret = new sahana.algo.classifiers.functions.SimpleLinearRegression()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.SimpleLogistic"))
			{
				ret = new sahana.algo.classifiers.functions.SimpleLogistic()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.SMO"))
			{
				ret = new sahana.algo.classifiers.functions.SMO().mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.SMO"))
			{
				ret = new sahana.algo.classifiers.functions.LeastMedSq()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.SMOreg"))
			{
				ret = new sahana.algo.classifiers.functions.LeastMedSq()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.VotedPerceptron"))
			{
				ret = new sahana.algo.classifiers.functions.LeastMedSq()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("functions.Winnow"))
			{
				ret = new sahana.algo.classifiers.functions.LeastMedSq()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("lazy.IB1"))
			{
				ret = new sahana.algo.classifiers.lazy.IB1().mine(input);
			}
			else if (variant.equalsIgnoreCase("lazy.IBk"))
			{
				ret = new sahana.algo.classifiers.lazy.IBk().mine(input);
			}
			else if (variant.equalsIgnoreCase("lazy.KStar"))
			{
				ret = new sahana.algo.classifiers.lazy.KStar().mine(input);
			}
			else if (variant.equalsIgnoreCase("lazy.LBR"))
			{
				ret = new sahana.algo.classifiers.lazy.LBR().mine(input);
			}
			else if (variant.equalsIgnoreCase("lazy.LWL"))
			{
				ret = new sahana.algo.classifiers.lazy.LWL().mine(input);
			}
			else if (variant.equalsIgnoreCase("misc.HyperPipes"))
			{
				ret = new sahana.algo.classifiers.misc.HyperPipes().mine(input);
			}
			else if (variant.equalsIgnoreCase("misc.VFI"))
			{
				ret = new sahana.algo.classifiers.misc.VFI().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.ConjunctiveRule"))
			{
				ret = new sahana.algo.classifiers.rules.ConjunctiveRule()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.DecisionTable"))
			{
				ret = new sahana.algo.classifiers.rules.DecisionTable()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.JRip"))
			{
				ret = new sahana.algo.classifiers.rules.JRip().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.M5Rules"))
			{
				ret = new sahana.algo.classifiers.rules.M5Rules().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.NNge"))
			{
				ret = new sahana.algo.classifiers.rules.NNge().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.OneR"))
			{
				ret = new sahana.algo.classifiers.rules.OneR().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.PART"))
			{
				ret = new sahana.algo.classifiers.rules.PART().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.Prism"))
			{
				ret = new sahana.algo.classifiers.rules.Prism().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.Ridor"))
			{
				ret = new sahana.algo.classifiers.rules.Ridor().mine(input);
			}
			else if (variant.equalsIgnoreCase("rules.ZeroR"))
			{
				ret = new sahana.algo.classifiers.rules.ZeroR().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.ADTree"))
			{
				ret = new sahana.algo.classifiers.trees.ADTree().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.DecisionStump"))
			{
				ret = new sahana.algo.classifiers.trees.DecisionStump()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.Id3"))
			{
				ret = new sahana.algo.classifiers.trees.Id3().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.J48"))
			{
				ret = new sahana.algo.classifiers.trees.J48().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.LMT"))
			{
				ret = new sahana.algo.classifiers.trees.LMT().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.M5P"))
			{
				ret = new sahana.algo.classifiers.trees.M5P().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.NBTree"))
			{
				ret = new sahana.algo.classifiers.trees.NBTree().mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.RandomForest"))
			{
				ret = new sahana.algo.classifiers.trees.RandomForest()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.RandomTree"))
			{
				ret = new sahana.algo.classifiers.trees.RandomTree()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("trees.REPTree"))
			{
				ret = new sahana.algo.classifiers.trees.REPTree().mine(input);
			}
		}
		else if (type.equalsIgnoreCase("associations"))
		{
			if (variant.equalsIgnoreCase("Apriori"))
			{
				ret = new sahana.algo.associations.Apriori().mine(input);
			}
			else if (variant.equalsIgnoreCase("PredictiveApriori"))
			{
				ret = new sahana.algo.associations.PredictiveApriori()
						.mine(input);
			}
			else if (variant.equalsIgnoreCase("Tertius"))
			{
				ret = new sahana.algo.associations.Tertius().mine(input);
			}
		}
		else if (type.equalsIgnoreCase("clusterers"))
		{
			if (variant.equalsIgnoreCase("Cobweb"))
			{
				ret = new sahana.algo.clusterers.Cobweb().mine(input);
			}
			if (variant.equalsIgnoreCase("EM"))
			{
				ret = new sahana.algo.clusterers.EM().mine(input);
			}
			if (variant.equalsIgnoreCase("FarthestFirst"))
			{
				ret = new sahana.algo.clusterers.FarthestFirst().mine(input);
			}
			if (variant.equalsIgnoreCase("SimpleKMeans"))
			{
				ret = new sahana.algo.clusterers.SimpleKMeans().mine(input);
			}
		}
		else
		{
			throw new Exception("No such mining algorithem\n " + algo);
		}
		return ret;
	}
}
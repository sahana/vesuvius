package sahana.algo.classifiers.bayes;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class BayesNet extends weka.classifiers.bayes.BayesNet implements
		DMAlgorithm
{

	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new BayesNet(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		return null;

	}

}

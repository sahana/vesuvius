package sahana.algo.classifiers.bayes;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class NaiveBayesUpdateable extends
		weka.classifiers.bayes.NaiveBayesUpdateable implements DMAlgorithm
{

	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(
					new NaiveBayesUpdateable(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
		//return null;
	}

}

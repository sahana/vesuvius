package sahana.algo.classifiers.bayes;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class NaiveBayes extends weka.classifiers.bayes.NaiveBayes implements
		DMAlgorithm
{

	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new NaiveBayes(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
	}

}

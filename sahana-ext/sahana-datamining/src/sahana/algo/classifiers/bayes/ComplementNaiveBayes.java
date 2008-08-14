package sahana.algo.classifiers.bayes;

import sahana.DMAlgorithm;

public class ComplementNaiveBayes extends
		weka.classifiers.bayes.ComplementNaiveBayes implements DMAlgorithm
{

	public String mine(String[] args)throws Exception
	{
		try
		{
			return weka.classifiers.Evaluation.evaluateModel(
					new ComplementNaiveBayes(), args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			throw e;
		}
	}

}

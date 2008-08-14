package sahana.algo.classifiers.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class PaceRegression extends weka.classifiers.functions.PaceRegression
		implements DMAlgorithm
{

	@Override
	public String mine(String[] args)throws Exception
	{
		Classifier scheme;
		try
		{
			scheme = new PaceRegression();
			return Evaluation.evaluateModel(scheme, args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			// System.out.println(e.getMessage());
			throw e;
		}
	}

}

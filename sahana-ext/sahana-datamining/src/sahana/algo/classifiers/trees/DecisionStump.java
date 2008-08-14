package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class DecisionStump extends weka.classifiers.trees.DecisionStump
		implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		Classifier scheme;

		try
		{
			scheme = new DecisionStump();
			return Evaluation.evaluateModel(scheme, args).toString();
		}
		catch (Exception e)
		{
			System.err.println(e.getMessage());
			throw e;
		}
	}

}

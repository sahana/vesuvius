package sahana.algo.classifiers.rules;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class DecisionTable extends weka.classifiers.rules.DecisionTable
		implements DMAlgorithm
{

	public String mine(String[] args)
	{
		Classifier scheme;
		try
		{
			scheme = new DecisionTable();
			return Evaluation.evaluateModel(scheme, args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.out.println(e.getMessage());
		}
		return null;
	}

}

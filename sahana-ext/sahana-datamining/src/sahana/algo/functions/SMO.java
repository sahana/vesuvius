package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class SMO extends weka.classifiers.functions.SMO implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		Classifier scheme;

		try
		{
			scheme = new SMO();
			return Evaluation.evaluateModel(scheme, args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}

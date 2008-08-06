package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class SMOreg extends weka.classifiers.functions.SMOreg implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		Classifier scheme;
		try
		{
			scheme = new SMOreg();
			return Evaluation.evaluateModel(scheme, args).toString();
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}

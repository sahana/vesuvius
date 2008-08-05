package sahana.algo.classifiers.lazy;

import sahana.DMAlgorithm;
import weka.classifiers.Classifier;
import weka.classifiers.Evaluation;

public class LBR extends weka.classifiers.lazy.LBR implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		Classifier scheme;

		try
		{
			scheme = new LBR();
			return Evaluation.evaluateModel(scheme, args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}

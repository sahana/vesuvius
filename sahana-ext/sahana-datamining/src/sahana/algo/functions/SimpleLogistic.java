package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class SimpleLogistic extends weka.classifiers.functions.SimpleLogistic
		implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new SimpleLogistic(), args);
		} catch (Exception e)
		{
			e.printStackTrace();
			System.err.println(e.getMessage());
			return e.toString();
		}
	}

}

package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class SimpleLinearRegression extends
		weka.classifiers.functions.SimpleLinearRegression implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new SimpleLinearRegression(), args).toString();
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
			e.printStackTrace();
			return e.toString();
		}
	}

}

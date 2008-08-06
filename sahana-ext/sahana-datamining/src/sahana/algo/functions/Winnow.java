package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class Winnow extends weka.classifiers.functions.Winnow implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new Winnow(), args).toString();
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
			return e.toString();
			
		}
	}

}

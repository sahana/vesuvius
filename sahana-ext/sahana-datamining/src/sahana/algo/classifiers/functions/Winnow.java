package sahana.algo.classifiers.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class Winnow extends weka.classifiers.functions.Winnow implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new Winnow(), args).toString();
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
			throw e;
			
		}
	}

}

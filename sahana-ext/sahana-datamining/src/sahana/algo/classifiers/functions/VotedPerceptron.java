package sahana.algo.classifiers.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class VotedPerceptron extends weka.classifiers.functions.VotedPerceptron
		implements DMAlgorithm
{

	@Override
	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new VotedPerceptron(), args);
		} catch (Exception e)
		{
			System.out.println(e.getMessage());
			throw e;
		}
	}

}

package sahana.algo.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class MultilayerPerceptron extends
		weka.classifiers.functions.MultilayerPerceptron implements DMAlgorithm
{

	@Override
	public String mine(String[] args)
	{
		try
		{
			return Evaluation.evaluateModel(new MultilayerPerceptron(), args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			e.printStackTrace();
			return e.toString();
		}
	}

}

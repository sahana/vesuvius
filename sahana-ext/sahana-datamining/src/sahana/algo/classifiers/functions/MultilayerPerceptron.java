package sahana.algo.classifiers.functions;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class MultilayerPerceptron extends
		weka.classifiers.functions.MultilayerPerceptron implements DMAlgorithm
{

	@Override
	public String mine(String[] args)throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new MultilayerPerceptron(), args).toString();
		} catch (Exception e)
		{
			System.err.println(e.getMessage());
			e.printStackTrace();
			throw e;
		}
	}

}

package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class LMT extends weka.classifiers.trees.LMT implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return Evaluation.evaluateModel(new LMT(), args).toString();
	}

}

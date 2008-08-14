package sahana.algo.classifiers.trees;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class NBTree extends weka.classifiers.trees.NBTree implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return Evaluation.evaluateModel(new NBTree(), args).toString();
	}

}

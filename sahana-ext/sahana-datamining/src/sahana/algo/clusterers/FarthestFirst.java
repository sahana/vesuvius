package sahana.algo.clusterers;

import sahana.DMAlgorithm;
import weka.clusterers.ClusterEvaluation;

public class FarthestFirst extends weka.clusterers.FarthestFirst implements
		DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return ClusterEvaluation.evaluateClusterer(new FarthestFirst(), args).toString();
	}

}

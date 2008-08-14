package sahana.algo.clusterers;

import sahana.DMAlgorithm;
import weka.clusterers.ClusterEvaluation;

public class EM extends weka.clusterers.EM implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		return ClusterEvaluation.evaluateClusterer(new EM(), args).toString();
	}
}

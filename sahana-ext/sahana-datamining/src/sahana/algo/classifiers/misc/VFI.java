package sahana.algo.classifiers.misc;

import sahana.DMAlgorithm;
import weka.classifiers.Evaluation;

public class VFI extends weka.classifiers.misc.VFI implements DMAlgorithm
{

	@Override
	public String mine(String[] args) throws Exception
	{
		try
		{
			return Evaluation.evaluateModel(new VFI(), args).toString();
		}
		catch (Exception e)
		{
			e.printStackTrace();
			throw e;
		}
	}

}

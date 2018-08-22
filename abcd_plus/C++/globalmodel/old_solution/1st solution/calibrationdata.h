#pragma once
/*This class should be an inner class of CalibratedModel and it allows
to gather all the inputs for the calibrate method*/

class CalibratedModel::CalibrationData {
public:
	//some common methods
	virtual const std::vector < boost::shared_ptr<RateHelper>> rateHelper()= 0;
	virtual OptimizationMethod method()= 0;
	virtual const EndCriteria endCriteria() = 0;
	virtual const std::vector<Real> weights() = 0;
	virtual const std::vector<bool> fixParameters()) = 0;
	virtual int globalParameter(int innerErrorNumber) = 0;
	virtual void globalParameterOrdering(std::vector<int> globalParameter)= 0;
	virtual Real globalErrorWeight() = 0;

	//attributes
protected:
	const std::vector<boost::shared_ptr<RateHelper> > helpers_,
	OptimizationMethod method_,
	const EndCriteria endCriteria_,
	const std::vector<Real> weights_,
	const std::vector<bool> fixParameters_;
	std::vector<int> globalParameter_;
	Real globalErrorWeight_;
};
#pragma once
/*This class should be an inner class of CalibratedModel and it allows
to gather all the input for the calibrate method*/

class CalibratedModel::CalibrationData {
public:
	//some common methods
	virtual const std::vector < boost::shared_ptr<RateHelper> rateHelper()const = 0;
	virtual OptimizationMethod method()const = 0;
	virtual const EndCriteria endCriteria()const = 0;
	virtual const std::vector<Real> weights()const = 0;
	virtual const std::vector<bool> fixParameters())const = 0;
	virtual int globalParameter(int innerErrorNumber)const = 0;
	virtual void globalParameterOrdering(std::vector<int> globalParameter)= 0;
	virtual Real globalErrorWeight()const = 0;

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
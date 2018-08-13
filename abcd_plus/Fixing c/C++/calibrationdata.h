#pragma once
/*This class should be an inner class of CalibratedModel and it allows
to gather all the input for the calibrate method
 this object stores all the inputs for the nested calibration*/

class CalibratedModel::CalibrationData {
public:

	const std::vector < boost::shared_ptr<RateHelper> rateHelper()const = 0;
	OptimizationMethod method()const = 0;
	const EndCriteria endCriteria()const = 0;
	const std::vector<Real> weights()const = 0;
	const std::vector<bool> fixParameters())const = 0;
	const int globalParameter()const = 0;
	Real globalErrorWeight()const = 0;

private:
	const std::vector<boost::shared_ptr<RateHelper> > helpers_,
	OptimizationMethod method_,
	const EndCriteria endCriteria_,
	const std::vector<Real> weights_,
	const std::vector<bool> fixParameters_;
	const int globalParameter_;
	Real globalErrorWeight_;
};
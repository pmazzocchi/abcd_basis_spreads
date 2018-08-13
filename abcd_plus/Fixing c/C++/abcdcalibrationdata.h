#pragma once
// this object stores all the inputs for the nested calibration
class AbcdCalibrationData:public CalibratedModel::CalibrationData {
public:
	AbcdCalibrationData(const int & globalParameter;
					Real globalErrorWeight;
					const std::vector<boost::shared_ptr<RateHelper> >& helpers,
					OptimizationMethod& method,
					const EndCriteria& endCriteria,
					const std::vector<Real>& weights,
					const std::vector<bool>& fixParameters);

	const std::vector < boost::shared_ptr<RateHelper> rateHelper();
	OptimizationMethod method();
	const EndCriteria endCriteria();
	const std::vector<Real> weights();
	const std::vector<bool> fixParameters());
	const int globalParameter();
	Real globalErrorWeight();

};
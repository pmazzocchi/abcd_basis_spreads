#include <calibarationdata.h>

/* Specific implementation of calibrationdata for the abcd
in order to use the mthod: calibrate*/

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
	const std::vector<bool> fixParameters();
	const int globalParameter();
	Real globalErrorWeight();
private:
	const std::vector < boost::shared_ptr<RateHelper> rateHelper_;
	OptimizationMethod method_;
	const EndCriteria endCriteria_;
	const std::vector<Real> weights_;
	const std::vector<bool> fixParameters_;
	const int globalParameter_;
	Real globalErrorWeight_;
};
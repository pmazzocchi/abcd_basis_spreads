#include <calibarationdata.h>

/* Specific implementation of calibrationdata for the abcd
in order to use the method: calibrate */

class AbcdCalibrationData:public CalibratedModel::CalibrationData {
public:
	AbcdCalibrationData(const std::vector<int> & globalParameter;
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
	const int globalParameter(int innerErrorNumber);
	Real globalErrorWeight();
};
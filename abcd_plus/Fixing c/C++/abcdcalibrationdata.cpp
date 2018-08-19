#include <abcdcalibarationdata.h>

AbcdTenorBasis::AbcdCalibrationData(const int & globalParameter;
					Real globalErrorWeight;
					const std::vector<boost::shared_ptr<RateHelper> >& helpers,
					OptimizationMethod& method,
					const EndCriteria& endCriteria,
					const std::vector<Real>& weights,
					const std::vector<bool>& fixParameters)
:globalParameter_(globalParameter), globalErrorWeight_(globalErrorWeight)
helpers_(helpers), method_(method), endCriteria_(endCriteria), weights_(weights), fixParameters_(fixParameters) {}

const std::vector < boost::shared_ptr<RateHelper> AbcdTenorBasis::AbcdCalibrationData rateHelper() const{
	return rateHelper_;
};
OptimizationMethod AbcdTenorBasis::AbcdCalibrationData  method() const {
	return method_;
};
const EndCriteria  AbcdTenorBasis::AbcdCalibrationData  endCriteria()const {
	return endCriteria_;
};
const std::vector<Real>  AbcdTenorBasis::AbcdCalibrationData weights() const {
	return weights_;
};
const std::vector<bool>  AbcdTenorBasis::AbcdCalibrationData fixParameters()const {
return fixParameters_;
};
const int AbcdTenorBasis::AbcdCalibrationData  globalParameter() const {
	return globalParameter_;
};
Real AbcdTenorBasis::AbcdCalibrationData  globalErrorWeight() const {
	return globalErrorWeight_;
};
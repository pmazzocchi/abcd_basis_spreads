#include <abcdcalibarationdata.h>

AbcdTenorBasis::AbcdCalibrationData(std::vector<int> & globalParameter;
					Real globalErrorWeight;
					const std::vector<boost::shared_ptr<RateHelper> >& helpers,
					OptimizationMethod& method,
					const EndCriteria& endCriteria,
					const std::vector<Real>& weights,
					const std::vector<bool>& fixParameters)
: globalErrorWeight_(globalErrorWeight),helpers_(helpers), method_(method), 
  endCriteria_(endCriteria), weights_(weights), fixParameters_(fixParameters) {

	globalParameterOrdering(std::vector<int> globalParameter);

}

// It allows to reorder the global parameter vector in order to use inner errors
// so the final user does not have to insert the fixed parameters in opposite order



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
const std::vector<int> AbcdTenorBasis::AbcdCalibrationData  globalParameter(int innerErrorNumber) const {
	return globalParameter_[innerErrorNumber];
};
Real AbcdTenorBasis::AbcdCalibrationData  globalErrorWeight() const {
	return globalErrorWeight_;
};

void globalParameterOrdering(std::vector<int> globalParameter) {

	int j = globalParameter.end();

	globalParameter_.resize(globalParameter.size());

	for (std::vector<int>::iterator i = globalParameter.begin();i != globalParameter.end();++i)
	{
		globalParameter_[i] = globalParameter[j];
		j--;
	}
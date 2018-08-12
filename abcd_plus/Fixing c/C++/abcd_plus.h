#pragma once

#include <ql/models/model.hpp>
#include <ql/experimental/tenorbasis/tenorbasis.hpp>

void TenorBasis::calibrate(
	std::vector<boost::shared_ptr<TenorBasis>>&
	std::vector<boost::shared_ptr<CalibrationData>>&,
	Real accuracy&,
	Real guess &,
	Real min &,
	Real max &);
	

	class TenorBasis::GlobalError {
	public:
		GlobalError(
			std::vector<boost::shared_ptr<TenorBasis>>&,
			std::vector<boost::shared_ptr<CalibrationData>>&);
			Real GlobalError::operator()(Real guess) const;
	private:
		std::vector<boost::shared_ptr<TenorBasis>> tenorBasis_;
		std::vector<boost::shared_ptr<CalibrationData>> calibrationData_;
		Real error_;
	};


	class TenorBasis::CalibrationData {
	public:
		CalibrationData(const int & globalParameter;
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
	private:
		const std::vector<boost::shared_ptr<RateHelper> > helpers_,
		OptimizationMethod method_,
		const EndCriteria endCriteria_,
		const std::vector<Real> weights_,
		const std::vector<bool> fixParameters_;
		const int globalParameter_;
		Real globalErrorWeight_;
	};


}
 
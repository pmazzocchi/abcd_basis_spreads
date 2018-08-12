#include <ql/experimental/tenorbasis/abcd_plus.hpp>

TenorBasis::GlobalError(std::vector<boost::shared_ptr<TenorBasis>>& tenorBasis,
	                    std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	                    :tenorBasis_(tenorBasis),calibrationData_(calibrationData) {}



void TenorBasis::calibrate(
	std::vector<boost::shared_ptr<TenorBasis>>& tenorBasis,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
	Solver1D solver,
	Real & accuracy,
	Real & guess,
	Real & min,
	Real & max) {

	//Idea from IterativeBootstrap:Brent firstSolver_;FiniteDifferenceNewtonSafe solver_;
	solver_ = solver;

	//create the error
	GlobalError globalError_(tenorBasis,calibrationData);
	
	//solve
	solver_.solve(*globalError_, accuracy, guess, min, max);
	//firstSolver_.solve(*errors_[i], accuracy, guess, min, max);

    //return global error
	return globalError->error_;
    }


Real TenorBasis::GlobalError::operator()(Real guess) const {

	//put the global guess in the global parameter position ( that has to be fixed in calibrate.)
	for (std::vector<int>::iterator i = tenorBasis_.begin();i != tenorBasis_.end();++i)
	{
		if (abcd[i]->isSimple_)
		{
			abcd_[i]->basis_->abcd[calibrationData_[i].globalParameter()] = guess
		}
		else
		{
			abcd_[i]->instBasis_->abcd[calibrationData_[i].globalParameter()] = guess;
		}
	}

	//set the calibration data and calibrate
	for (std::vector<int>::iterator i = tenorBasis_.begin();i != tenorBasis_.end();++i)
	{
		abcd_[i]->calibrate(calibrationData_[i].rateHelper(),
							calibrationData_[i].method(),
							calibrationData_[i].endCriteria(),
							calibrationData_[i].weights(),
							calibrationData_[i].fixParameters())
	}

	//get the global error
	error = 0;
	for (std::vector<int>::iterator i = calibrationData_.begin();i != calibrationData_.end();++i)
	{
		error++ = calibrationData_.globalErrorWeight()*abcd_[i]->value(abcd[i]->instbasis_->coefficients);
	}


	return error;
}
// non mi ricordo se la sintassi per TenorBasis::CalibrationData è nell'ordine giusto, ma il succo non cambia, domani verifico (12/8)
const std::vector < boost::shared_ptr<RateHelper> TenorBasis::CalibrationData rateHelper() {
	return rateHelper_;
};
OptimizationMethod TenorBasis::CalibrationData  method() {
	return method_;
};
const EndCriteria  TenorBasis::CalibrationData  endCriteria() {
	return endCriteria_;
};
const std::vector<Real>  TenorBasis::CalibrationData weights() {
	return weights_;
};
const std::vector<bool>  TenorBasis::CalibrationData fixParameters()){
return fixParameters_;
};
const int TenorBasis::CalibrationData  globalParameter() {
	return globalParameter_;
};
Real TenorBasis::CalibrationData  globalErrorWeight() {
	return globalErrorWeight_;
};
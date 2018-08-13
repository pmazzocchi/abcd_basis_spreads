#include <abcdglobalerror.h>

AbcdGlobalError::AbcdGlobalError(std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	:GlobalError(calibratedModel,calibrationData) {}

void AbcdGlobalError::updateGuess( Real guess) const {

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		//calibrate change argument_, therefore it makes sense to fix the global parameter, changing it externally.
		calibratedModel_[i]->arguments_[calibrationData_[i].globalParameter()](0.0) = guess;
	
}

void AbcdGlobalError::loadCalibrationData() const{

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
	calibratedModel_[i]->calibrate(calibrationData_[i]->rateHelper(),
		calibrationData_[i]->method(),
		calibrationData_[i]->endCriteria(),
		calibrationData_[i]->weights(),
		calibrationData_[i]->fixParameters())
}


void AbcdGlobalError::error() {

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		error_++ = calibrationData_[i]->globalErrorWeight()*calibratedModel_[i]->value(calibratedModel_[i]->params(), calibrationData_.rateHelper());
	}
}
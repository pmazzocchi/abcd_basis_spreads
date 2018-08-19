#include <abcdglobalerror.h>

//specific the function in order to use the operator ()

AbcdGlobalError::AbcdGlobalError(int &innerErrorNumber, std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	:GlobalError(innerErrorNumber,calibratedModel,calibrationData) {};

void AbcdGlobalError::updateGuess( Real guess) const {

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		/*the calibrate method works on  arguments_, therefore it makes sense 
		to fix the global parameter with the boollean value changing it externally ( with the guess).*/
		calibratedModel_[i]->arguments_[calibrationData_[i].globalParameter()](0.0) = guess;
	
}

// maybe not the perfect name, because it loads and calibrates. Anyway, by construction
// in calibrate if you load then calibrate, so maybe it can work

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
		error_++ = calibrationData_[i]->globalErrorWeight()*calibratedModel_[i]->value(calibratedModel_[i]->params(), calibrationData_[i].rateHelper());
	}
}

void innerError(CalibrationData & calibrationData) {
	//There I may use both this-> or a get function, is it the same?Yes, beacuse the attribute are protected
	AbcdGlobalError Error(this->innerErrorNumber_-1,getCalibratedModel, getCalibrationData);
	calibrate(calibrationData);

}
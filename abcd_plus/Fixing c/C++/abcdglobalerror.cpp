#include <abcdglobalerror.h>

//specific the function in order to use the operator ()

AbcdGlobalError::AbcdGlobalError(int &innerErrorNumber,
								std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
								std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
								std::vector<boost::shared_ptr<CalibrateData>>& calibrateData)
	:GlobalError(innerErrorNumber,calibratedModel,calibrationData,calibrateData) {
	calibrateDataOrdering(calibrateData)
};


//it updates the  global parameter guess
void AbcdGlobalError::updateGuess( Real guess) const {

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		/*the calibrate method works on  arguments_, therefore it makes sense 
		to fix the global parameter with the boolean value changing it externally ( with the guess).*/

		/*Mind the globalParameter: if there is just one innerErrorNumber_ it goes for loadCalibrationData and it'all okay.
		If there are two innerErrorNumber_ the outer error takes the last entry of const std::vector<int> globalParameter_:globalParameter_[1]
		and the inner cycle will manage the globalParameter_[0]
		So, based on the innerErrorNumber_ it is possible to fix for each level of error the corresponding parameter that has to be fixed*/
		calibratedModel_[i]->arguments_[calibrationData_[i].globalParameter(this->innerErrorNumber_)](0.0) = guess;
	
}

/*Maybe not the perfect name, because it loads and calibrates. Anyway, by construction
in calibrate if you load then calibrate, so maybe it can work.
Anyway, this function loads the claibrate method for each method and then it calibrates them*/

void AbcdGlobalError::loadCalibrationData() const{

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		//here the model is AbcdtenorBasis therefore it uses AbcdTenorBasis::calibrate
		calibratedModel_[i]->calibrate(calibrationData_[i]->rateHelper(),
		calibrationData_[i]->method(),
		calibrationData_[i]->endCriteria(),
		calibrationData_[i]->weights(),
		calibrationData_[i]->fixParameters())
}

/*It retrieves the error for each model*/

void AbcdGlobalError::error() {

	for (std::vector<int>::iterator i = calibratedModel_.begin();i != calibratedModel_.end();++i)
	{
		error_++ = calibrationData_[i]->globalErrorWeight()*calibratedModel_[i]->value(calibratedModel_[i]->params(), calibrationData_[i].rateHelper());
	}
}

void innerError() {
	//There I may use both this-> or a get function, is it the same? Yes, beacuse the attribute are protected
	int innerErrorNumberCounter = this->innerErrorNumber_ - 1;
	//it is necessary to pass all the calibrateData because in the 2+ inner error will be ask its data and so on.
	AbcdGlobalError Error(innerErrorNumberCounter,this->calibratedModel_, this->calibrationData_,this->calibrateData_);
	calibrate(Error);

}
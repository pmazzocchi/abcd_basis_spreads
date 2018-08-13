#include <globalerror.h>

CalibratedModel::GlobalError(std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	:calibratedModel_(calibratedModel), calibrationData_(calibrationData) {}

Real CalibratedModel::GlobalError::operator()(Real guess) const {

	//put the global guess in the global parameter position ( that has to be fixed in calibrate.)
	this->updateGuess(guess);

	//set the calibration data and calibrate
	this->loadCalibrationData();

	//get the global error
	error_ = 0;

	this->error()

	return error_;
}
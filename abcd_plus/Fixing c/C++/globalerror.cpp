#include <globalerror.h>

// constructor which forwards inputs to the GlobalError attributes
CalibratedModel::GlobalError(std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	:calibratedModel_(calibratedModel), calibrationData_(calibrationData) {}

//operator that designs a fram to get the global error with a flexibility in implementing
// the different method

Real CalibratedModel::GlobalError::operator()(Real guess) const {

	//put the global guess in the global parameter position ( that has to be fixed in calibrate.)
	this->updateGuess(guess);

	//decide whether to generate another global error or directly calibrate
	errorFork();

	//get the global error
	error_ = 0;

	this->error()

	return error_;
}

void errorFork() {

	if innerErrorNumber_ > 1{
		innerError(CalibrationData & calibrationData);
	}
	else
	{
		loadCalibrationData();
	}

};

GlobalError(int &innerErrorNumber,
	std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData)
	:innerErrorNumber_(innerErrorNumber), calibratedModel(calibratedModel_), calibrationData(calibrationData_) {};

std::vector<boost::shared_ptr<CalibratedModel>> getCalibratedModel() {
	return calibratedModel_;
};

std::vector<boost::shared_ptr<CalibrationData>> getCalibrationData() {
	return calibrationData_;
};
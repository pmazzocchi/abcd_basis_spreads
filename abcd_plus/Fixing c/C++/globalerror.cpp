#include <globalerror.h>

// constructor which forwards inputs to the GlobalError attributes
CalibratedModel::GlobalError(int &innerErrorNumber,
							std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
							std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
							std::vector<boost::shared_ptr<CalibrateData>>& calibrateData)
	:innerErrorNumber_(innerErrorNumber), calibratedModel_(calibratedModel), calibrationData_(calibrationData), calibrateData_(calibrateData){};

//operator that designs a frame to get the global error with a flexibility in implementing
// the different requested method

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
//The case: in order to fix more parameters with more than one nested calibration, it is possible creating an innerError loop which mimics the outer one
void errorFork() const {

	if innerErrorNumber_ > 1{
		innerError();
	}
	else
	{
		loadCalibrationData();
	}

};

//get method
std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel()const {
	return calibratedModel_;
};

std::vector<boost::shared_ptr<CalibrationData>> calibrationData() const {
	return calibrationData_;
};

std::vector<boost::shared_ptr<CalibrateData>> calibrateData() const {
	return calibrateData_;
};

void calibrateDataOrdering(std::vector<boost::shared_ptr<CalibrateData>> calibrateData);
{

	int j = calibrateData.end();

	calibrateData_.resize(calibrateData.size());

	for (std::vector<int>::iterator i = calibrateData.begin();i != calibrateData.end();++i)
	{
		calibrateData_[i] = calibrateData[j];
		j--;
	}

}


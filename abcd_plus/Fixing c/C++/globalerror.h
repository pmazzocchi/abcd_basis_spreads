
/*This class should be an inner class of CalibratedModel and it allows
to manipulate the errors that comes from a series of model*/

class CalibratedModel::GlobalError {

public:
	GlobalError(
		//innerErrorNumber plays it's fundamental because helps to select data according to the referred global error
		int & innerErrorNumber,
		//it needed a vector of CalibratedModel, because we are retrieving the error from more than one
				std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
		//different CalibratedModel need different calibration data
				std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
		//if there is more than one global error: more error needs more calibrate and therefore more claibrate data
				std::vector<boost::shared_ptr<CalibrateData>>& calibrateData)
	//methods

	virtual void error()= 0;
	virtual void updateGuess(Real guess) const = 0;
	virtual void loadCalibrationData() const = 0;
	virtual void innerError()= 0;
	void errorFork()const;
	void calibrationDataOrdering(std::vector<boost::shared_ptr<CalibrateData>> calibrateData);
	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel()const;
	std::vector<boost::shared_ptr<CalibrationData>> calibrationData()const;
	std::vector<boost::shared_ptr<CalibrateData>> calibrateData()const;

	Real GlobalError::operator()(Real guess);

private:
	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel_;
	std::vector<boost::shared_ptr<CalibrationData>> calibrationData_;
	std::vector<boost::shared_ptr<CalibrateData>> calibrateData_;
	/*if calibrationData_ makes sense as wrapped in GlobalError, I think that calibrateData_ is more a shortcut
	rather than the right approach, anyway.. it should work*/
	Real error_;
	int innerErrorNumber_ ;
};
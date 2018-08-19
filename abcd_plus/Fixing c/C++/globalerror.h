
/*This class should be an inner class of CalibratedModel and it allows
to manipulate the errors that comes from more than one model*/

class CalibratedModel::GlobalError {

public:
	GlobalError(int &innerErrorNumber,
				std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
				std::vector<boost::shared_ptr<CalibrationData>>& calibrationData);
	virtual void error()= 0;
	virtual void updateGuess(Real guess) const = 0;
	virtual void loadCalibrationData() const = 0;
	virtual void innerError(CalibrationData & calibrationData)= 0;
	void errorFork();
	std::vector<boost::shared_ptr<CalibratedModel>> getCalibratedModel();
	std::vector<boost::shared_ptr<CalibrationData>> getCalibrationData();
	Real GlobalError::operator()(Real guess);

private:
	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel_;
	std::vector<boost::shared_ptr<CalibrationData>> calibrationData_;
	Real error_;
	int innerErrorNumber_ ;
};
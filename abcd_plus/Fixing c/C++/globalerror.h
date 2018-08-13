#pragma once
class CalibratedModel::GlobalError {
public:
	GlobalError(
		std::vector<boost::shared_ptr<CalibratedModel>>&,
		std::vector<boost::shared_ptr<CalibrationData>>&);
	virtual void error() const = 0;
	virtual void updateGuess(Real guess) const = 0;
	virtual void loadCalibrationData() const = 0;
	Real GlobalError::operator()(Real guess) const;
private:
	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel_;
	std::vector<boost::shared_ptr<CalibrationData>> calibrationData_;
	Real error_;
};
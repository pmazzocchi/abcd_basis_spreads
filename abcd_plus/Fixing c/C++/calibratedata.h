#pragma once

class CalibrateData :public CalibratedModel::CalibrationData {
public:
	CalibrateData(std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel;
		std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
		Real & accuracy,
		Real & guess,
		Real & min,
		Real & max);

	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel();
	std::vector<boost::shared_ptr<CalibrationData>> calibrationData();
	Real accuracy();
	Real guess();
	Real min();
	Real max();
private:
	std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel_;
	std::vector<boost::shared_ptr<CalibrationData>>& calibrationData_;
	Real & accuracy_;
	Real & guess_;
	Real & min_;
	Real & max_;
};
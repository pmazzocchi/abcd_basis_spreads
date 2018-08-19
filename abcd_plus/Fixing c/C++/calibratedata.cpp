
CalibrateData::CalibrateData(std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel;
							std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
							Real & accuracy,
							Real & guess,
							Real & min,
							Real & max)
	:


std::vector<boost::shared_ptr<CalibratedModel>> CalibrateData::calibratedModel(); {
	return calibratedModel_;
}
std::vector<boost::shared_ptr<CalibrationData>> CalibrateData::calibrationData() {
	return calibrationData_;
};
Real CalibrateData::accuracy() {
	return accuracy_;
};
Real CalibrateData::guess() {
	return guess_;
};
Real CalibrateData::min() {
	return min_;
};
Real CalibrateData::max() {
	return max_;
};
#pragma once

class CalibratedModel::CalibrateData {
public:
	CalibrateData(
		/*std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel;
		//std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,*/
		boost::shared_ptr<Solver1D> solver,
		Real & accuracy,
		Real & guess,
		Real & min,
		Real & max);

	/*std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel()const;
	//std::vector<boost::shared_ptr<CalibrationData>> calibrationData()const;*/
	//std::vector<boost::shared_ptr<CalibrationData>>& calibrationData_;*/
	boost::shared_ptr<Solver1D> solver()const;
	Real accuracy()const;
	Real guess()const;
	Real min()const;
	Real max()const;

	//void solverOrdering(std::vector<boost::shared_ptr<Solver1D>> solver);
private:
	/*std::vector<boost::shared_ptr<CalibratedModel>> calibratedModel_;
	//std::vector<boost::shared_ptr<CalibrationData>>& calibrationData_;*/
	boost::shared_ptr<Solver1D> solver_;
	Real accuracy_;
	Real guess_;
	Real min_;
	Real max_;
};

CalibrateData::CalibrateData(
								/*std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel;
							std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,*/
							boost::shared_ptr<Solver1D> & solver,
							Real & accuracy,
							Real & guess,
							Real & min,
							Real & max)
	:solver_(solver), accuracy_(accuracy),guess_(guess), min_(min), max_(max) {

	/*calibrationDataOrdering(calibrationData);

	solverOrdering(solver);*/

}


/*std::vector<boost::shared_ptr<CalibratedModel>> CalibrateData::calibratedModel()const {
	return calibratedModel_;
}
std::vector<boost::shared_ptr<CalibrationData>> CalibrateData::calibrationData() const {
	return calibrationData_;
};*/

boost::shared_ptr<Solver1D> solver()const {
	return solver_;
};

Real CalibrateData::accuracy()const {
	return accuracy_;
};
Real CalibrateData::guess() const {
	return guess_;
};
Real CalibrateData::min() const {
	return min_;
};
Real CalibrateData::max() const {
	return max_;
};

/*


void solverOrdering(std::vector<boost::shared_ptr<Solver1D>> solver); {

	int j = solver.end();

	solver_.resize(solver.size());

	for (std::vector<int>::iterator i = solver.begin();i != solver.end();++i)
	{
		solver_[i] = solver[j];
		j--;
	}

}
*/
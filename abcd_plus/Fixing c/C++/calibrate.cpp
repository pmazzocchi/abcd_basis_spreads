#include <ql/experimental/tenorbasis/abcd_plus.hpp>

//Idea from IterativeBootstrap
void CalibratedModel::calibrate(
	//std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
	//std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
	boost::shared_ptr<GlobalError> globalError;
	boost::shared_ptr<Solver1D> solver,
	Real & accuracy,
	Real & guess,
	Real & min,
	Real & max) {

	//create the error
	//GlobalError globalError_(calibratedModel,calibrationData);
	
	//solve
	solver->solve(globalError_, accuracy, guess, min, max);
	//firstSolver_.solve(*errors_[i], accuracy, guess, min, max);
    }






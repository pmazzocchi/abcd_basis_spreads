#include <globalerror.h>

//implement GlobalError methods
AbcdGlobalError:public GlobalError{
public:
	AbcdGlobalError(int & innerErrorNumber,
		std::vector<boost::shared_ptr<CalibratedModel>>& calibratedModel,
		std::vector<boost::shared_ptr<CalibrationData>>& calibrationData,
		std::vector<boost::shared_ptr<CalibrateData>>& calibrateData);

	void updateGuess(Real guess)const;

	void error();

	void loadCalibrationData()const;

	void innerError(CalibrationData & calibrationData);

}
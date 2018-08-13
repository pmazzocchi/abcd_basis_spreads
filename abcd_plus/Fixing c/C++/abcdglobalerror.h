#pragma once
//implement GlobalError methods
AbcdGlobalError:public GlobalError{
public:
	AbcdGlobalError();

	void updateGuess(Real guess);

	void error();

	void loadCalibrationData();

}
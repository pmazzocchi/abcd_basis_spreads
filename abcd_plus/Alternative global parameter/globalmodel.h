#pragma once
class GlobalModel : public CalibratedModel {

public:
	GlobalModel(Size nArguments,
		const Real& coeff,
		std::vector<int> & position,
		int  & innerErrorNumber_);

	void generateArguments();
	void calibrate(std::vector<shared_ptr<CalibrationHelperBase> >& h);
protected:
	std::vector<int> position_;
	int innerErrorNumber_;
	std::vector<shared_ptr<CalibrationHelperBase>> h_;
	OptimizationMethod method_;
	EndCriteria endCriteria_;
	Constraint additionalConstraint_;
	std::vector<Real> w_;
	std::vector<bool> fixParameters_;
};

class GlobalHelper : public CalibrationHelperBase {

public:
	GlobalHelper(boost:shared_ptr<CalibratedModel>& calibratedModel,
		std::vector<boost::shared_ptr<CalibrationHelperBase> >& h,
		OptimizationMethod& method,
		EndCriteria& endCriteria,
		Constraint& additionalConstraint,
		vector<Real>& w,
		vector<bool>& fixParameters);

	void calibrationError();

protected:
	std::vector<shared_ptr<CalibrationHelperBase> > h_;
	OptimizationMethod method_;
	const EndCriteria endCriteria_;
	const Constraint additionalConstraint_;
	const vector<Real> w_;
	const vector<bool> fixParameters_;
	boost:shared_ptr<CalibratedModel> calibratedModel_;
};
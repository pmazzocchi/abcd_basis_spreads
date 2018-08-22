//global model
GlobalModel::GlobalModel(Size nArguments,
						const Real& coeff,
						std::vector<int> & position,
						int  & innerErrorNumber_)
	: CalibratedModel(nArguments)
	position_(position),
	innerErrorNumber__(innerErrorNumber_)
	//It indicates what is the position of the parameter that should be fixed{
	}

	Real y = coeff;
	arguments_[0] = ConstantParameter(y, NoConstraint());
	//generateArguments();
}

void GlobalModel::generateArguments() {

	Real x;
	x[0] = arguments_[0](0.0);
	Real y = x;
	int index=position_.size() - innerErrorNumber_;

	if (innerErrorNumber_ = 1) {
		innerErrorNumber_--;
		for (std::vector<int>::iterator i = h_.begin();i != h_.end();++i)
		{
			h_[i]->calibratedModel_->arguments_[position_[index_]](0.0) = x;//?
		}
	}
	else
	{
		innerErrorNumber_--;
		Size size = 1;
		index = position_.size() - innerErrorNumber_;
		Real coeff = h_[0]->calibratedModel_->arguments_[position_[index_]](0.0);// the guess is incorporated in the current parameters ( not optimal)
		GlobalModel globalModel(size,
								coeff[index],
								position_,
								innerErrorNumber_);
		globalModel.calibrate(h_,
								OptimizationMethod& method,
								EndCriteria& endCriteria,
								Constraint& additionalConstraint,
								vector<Real>& w,
								vector<bool>& fixParameters);
	}


}

void GlobalModel::calibrate(std::vector<shared_ptr<CalibrationHelperBase> >& h,
							OptimizationMethod& method,
							EndCriteria& endCriteria,
							Constraint& additionalConstraint,
							std::vector<Real>& w,
							std::vector<bool>& fixParameters) {

	h_ = h;// ......... :P
	method_ = method;
	endCriteria_ = endCriteria;
	additionalConstraint_ = additionalConstraint;
	w_ = w;
	fixParameters_ = fixParameters;
	
	CalibratedModel::calibrate( h_,
								method_,
								endCriteria_,
								additionalConstraint_,
								w_,
								fixParameters_)

};


GlobalHelper::GlobalHelper(boost:shared_ptr<CalibratedModel>& calibratedModel,
	const vector<shared_ptr<CalibrationHelperBase> >& h,
	OptimizationMethod& method,
	const EndCriteria& endCriteria,
	const Constraint& additionalConstraint,
	const vector<Real>& w,
	const vector<bool>& fixParameters)
	:calibratedModel_(calibratedModel), h_(h), method_(method), endCriteria_(endCriteria),
	additionalConstraint_(additionalConstraint), w_(w), fixParameters_(fixParameters) {};

void GlobalHelper::calibrationError()
{
	calibratedModel_->calibrate(h_, method_, endCriteria_,additionalConstraint_, w_, fixParameters_);
	return calibratedModel_->value(calibratedModel_->params(),h_);
};

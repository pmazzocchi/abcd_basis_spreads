//global model
GlobalModel::GlobalModel(Size nArguments,
	const Real& coeff,
	std::vector<int> & position,
	int  & innerErrorNumber_)
	: CalibratedModel(nArguments)
	position_(position),
	innerErrorNumber__(innerErrorNumber_)
							}

							Real y = coeff;
							arguments_[0] = ConstantParameter(y, NoConstraint());
							//generateArguments();
}

void GlobalModel::generateArguments() {

	Real x;
	x[0] = arguments_[0](0.0);
	Real y = x;
	int index = position_.size() - innerErrorNumber_;// for understanding with which error is currently considered

													 //if there is only one global error
	if (innerErrorNumber_ = 1) {
		for (std::vector<int>::iterator i = h_.begin();i != h_.end();++i)
		{
			h_[i]->calibratedModel_->arguments_[position_[index_]](0.0) = x;//?
		}
	}
	//If there are mone the one global error-> nested calibration in nested calibration
	else
	{
		//diminishing the error indicator
		innerErrorNumber_--;
		Size size = 1;
		/*comunicate the position of the global parameter. Given that the size of position equals the number of inner error ( at the beginning),
		considering that the user passes before the outer parameter and then the other, if for instance there are 2 error then postion_.size()=2
		if we are considering the outer global parameter the  index is 2-2 , it is correct because takes position_[0], while with the second takes
		2-1 ( because innerErrorNumber_ has been diminished)  and therefore correctly it takes postion_[1]*/
		index = position_.size() - innerErrorNumber_;
		/*takes the guess from its value in the first model. It's right because in order to global calibrate this value has been fixed
		so we are using the original guess ( set by user)*/
		Real coeff = h_[0]->calibratedModel_->arguments_[position_[index_]](0.0);// the guess is incorporated in the current parameters ( not optimal)
																				 //Therefore, create an inner model
		GlobalModel globalModel(size,
			coeff[index],
			position_,
			innerErrorNumber_);
		/*calibrate the inner model, reusing the calibrate of the outer global calibration
		the assumption here is that the method and its friends are not depending on the error
		It should be okay reuse h_ because they are all pointer therefore we are always change all the inputs also out of
		the inner calibraton (I think)*/
		globalModel.calibrate(h_,
			method_,
			endCriteria_,
			additionalConstraint_,
			w_,
			fixParameters_);
	}


}

void GlobalModel::calibrate(std::vector<shared_ptr<CalibrationHelperBase> >& h,
	LevenbergMarquardt& method,
	EndCriteria& endCriteria,
	Constraint& additionalConstraint,
	std::vector<Real>& w,
	std::vector<bool>& fixParameters) {
	//It stores the inputs in order to use GlobalModel::calibrate for calibrating the inner GlobalModel
	h_ = h;// ......... :P
	method_ = method;
	endCriteria_ = endCriteria;
	additionalConstraint_ = additionalConstraint;
	w_ = w;
	fixParameters_ = fixParameters;

	CalibratedModel::calibrate(h_,
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
	/*it asks its calibratedModel_ to calibrate itself and then asks the error*/
	calibratedModel_->calibrate(h_, method_, endCriteria_, additionalConstraint_, w_, fixParameters_);
	return calibratedModel_->value(calibratedModel_->params(), h_);
};

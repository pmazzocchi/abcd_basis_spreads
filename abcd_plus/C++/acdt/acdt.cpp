
AcdtTenorBasis::AcdtTenorBasis(boost::shared_ptr<IborIndex> iborIndex,
	boost::shared_ptr<IborIndex> baseIborIndex,
	Date referenceDate,
	bool isSimple,
	const std::vector<Real>& coeff)
	: TenorBasis(4, iborIndex, baseIborIndex, referenceDate) {
	//std::vector<Real> y = inverse(coeff);
	std::vector<Real> y = coeff;

	arguments_[0] = ConstantParameter(y[0], NoConstraint());
	arguments_[1] = ConstantParameter(y[1], NoConstraint()); //this is t_max, it can be also the fourth parameter, probably it would make more sense
	arguments_[2] = ConstantParameter(y[2], NoConstraint());
	arguments_[3] = ConstantParameter(y[3], NoConstraint());
	isSimple_ = isSimple;
	generateArguments();
}

//pratically the same of AbcdTenorBasis::generateArguments()
void AcdtTenorBasis::generateArguments() {
	std::vector<Real> x(4);
	x[0] = arguments_[0](0.0);//a
							  //fulfilling b with its funcitonal form. 
	x[1] = b(std::vector<Parameter> arguments_)
		x[2] = arguments_[2](0.0);//c
	x[3] = arguments_[3](0.0);//t
							  //std::vector<Real> y = direct(x);
	std::vector<Real> y = x;
	if (isSimple_) {
		basis_ = shared_ptr<AbcdMathFunction>(
			new AbcdMathFunction(y[0], y[1], y[2], y[3]));
		vector<Real> c = basis_->definiteDerivativeCoefficients(0.0, tau_);
		c[0] *= tau_;
		c[1] *= tau_;
		// unaltered c[2] (the c in abcd)
		c[3] *= tau_;
		instBasis_ = shared_ptr<AbcdMathFunction>(new AbcdMathFunction(c));
	}
	else {
		instBasis_ = shared_ptr<AbcdMathFunction>(
			new AbcdMathFunction(y[0], y[1], y[2], y[3]));
		vector<Real> c =
			instBasis_->definiteIntegralCoefficients(0.0, tau_);
		c[0] /= tau_;
		c[1] /= tau_;
		// unaltered c[2] (the c in abcd)
		c[3] /= tau_;
		basis_ = shared_ptr<AbcdMathFunction>(new AbcdMathFunction(c));
	}
}

Real AcdtTenorBasis::b(std::vector<Parameter> arguments)
{
	Real b;
	return b = (arguments_[0](0.0)*arguments_[2](0.0)) / (1 - arguments_[1](0.0)*arguments_[2](0.0));
};


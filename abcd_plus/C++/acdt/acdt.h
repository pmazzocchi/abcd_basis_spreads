class AcdtTenorBasis : public AbcdTenorBasis {
public:
	AcdtTenorBasis(boost::shared_ptr<IborIndex> iborIndex,
		boost::shared_ptr<IborIndex> baseIborIndex,
		Date referenceDate,
		bool isSimple,
		const std::vector<Real>& coeff);

	void generateArguments();
	Real b(std::vector<Parameter> param);
};
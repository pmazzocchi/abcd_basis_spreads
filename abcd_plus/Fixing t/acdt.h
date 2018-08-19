
class AcdtTenorBasis : public AbcdTenorBasis {
public:
	AcdtTenorBasis(shared_ptr<IborIndex> iborIndex,
		boost::shared_ptr<IborIndex> baseIborIndex,
		Date referenceDate,
		bool isSimple,
		const std::vector<Real>& coeff)
		: TenorBasis(4, iborIndex, baseIborIndex, referenceDate)

	void generateArguments();
	Real b(std::vector<Parameter> param);
};

	/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */



	/*!

	Copyright (C) 2000, 2001, 2002, 2003 RiskMap srl

	Copyright (C) 2003, 2004, 2005, 2006, 2007 StatPro Italia srl

	Copyright (C) 2004 Ferdinando Ametrano



	This file is part of QuantLib, a free-software/open-source library

	for financial quantitative analysts and developers - http://quantlib.org/



	QuantLib is free software: you can redistribute it and/or modify it

	under the terms of the QuantLib license.  You should have received a

	copy of the license along with this program; if not, please email

	<quantlib-dev@lists.sf.net>. The license is also available online at

	<http://quantlib.org/license.shtml>.



	This program is distributed in the hope that it will be useful, but WITHOUT

	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS

	FOR A PARTICULAR PURPOSE.  See the license for more details.

	*/



	/*  This example shows how to set up a Term Structure and then price a simple

	swap.

	*/



	// the only header you need to use QuantLib

#include <ql/quantlib.hpp>



#ifdef BOOST_MSVC

	/* Uncomment the following lines to unmask floating-point

	exceptions. Warning: unpredictable results can arise...



	See http://www.wilmott.com/messageview.cfm?catid=10&threadid=9481

	Is there anyone with a definitive word about this?

	*/

	// #include <float.h>

	// namespace { unsigned int u = _controlfp(_EM_INEXACT, _MCW_EM); }

#endif



#include <boost/timer.hpp>

#include <iostream>

#include <iomanip>



	using namespace QuantLib;



#ifdef BOOST_MSVC

#  ifdef QL_ENABLE_THREAD_SAFE_OBSERVER_PATTERN

#    include <ql/auto_link.hpp>

#    define BOOST_LIB_NAME boost_system

#    include <boost/config/auto_link.hpp>

#    undef BOOST_LIB_NAME

#    define BOOST_LIB_NAME boost_thread

#    include <boost/config/auto_link.hpp>

#    undef BOOST_LIB_NAME

#  endif

#endif



#if defined(QL_ENABLE_SESSIONS)

namespace QuantLib {



	Integer sessionId() { return 0; }



}

#endif





int main(int, char*[]) {




		boost::timer timer;

		std::cout << std::endl;



		/*********************

		***  MARKET DATA  ***

		*********************/



		Calendar calendar = TARGET();

		Date settlementDate(22, September, 2004);

		// must be a business day

		settlementDate = calendar.adjust(settlementDate);



		Integer fixingDays = 2;

		Date todaysDate = calendar.advance(settlementDate, -fixingDays, Days);
		// nothing to do with Date::todaysDate

		Settings::instance().evaluationDate() = todaysDate;





		todaysDate = Settings::instance().evaluationDate();

		std::cout << "Today: " << todaysDate.weekday()

			<< ", " << todaysDate << std::endl;

	

		std::cout << "Settlement date: " << settlementDate.weekday()

			<< ", " << settlementDate << std::endl;



		// deposits

		Rate d1wQuote = 0.0382;

		Rate d1mQuote = 0.0372;

		Rate d3mQuote = 0.0363;

		Rate d6mQuote = 0.0353;

		Rate d9mQuote = 0.0348;

		Rate d1yQuote = 0.0345;

		// FRAs

		Rate fra3x6Quote = 0.037125;

		Rate fra6x9Quote = 0.037125;

		Rate fra6x12Quote = 0.037125;

		// futures

		Real fut1Quote = 96.2875;

		Real fut2Quote = 96.7875;

		Real fut3Quote = 96.9875;

		Real fut4Quote = 96.6875;

		Real fut5Quote = 96.4875;

		Real fut6Quote = 96.3875;

		Real fut7Quote = 96.2875;

		Real fut8Quote = 96.0875;

		// swaps

		Rate s2yQuote = 0.037125;

		Rate s3yQuote = 0.0398;

		Rate s5yQuote = 0.0443;

		Rate s10yQuote = 0.05165;

		Rate s15yQuote = 0.055175;

		// OIS

		Rate ois1wQuote = 0.0382;

		Rate ois1mQuote = 0.0372;

		Rate ois3mQuote = 0.0363;

		Rate ois6mQuote = 0.0353;

		Rate ois9mQuote = 0.0348;

		Rate ois1yQuote = 0.0345;

		Rate ois2yQuote = 0.037125;

		Rate ois3yQuote = 0.0398;

		Rate ois5yQuote = 0.0443;

		Rate ois10yQuote = 0.05165;

		Rate ois15yQuote = 0.055175;





		/********************

		***    QUOTES    ***

		********************/



		// SimpleQuote stores a value which can be manually changed;

		// other Quote subclasses could read the value from a database

		// or some kind of data feed.



		// deposits

		boost::shared_ptr<Quote> d1wRate(new SimpleQuote(d1wQuote));

		boost::shared_ptr<Quote> d1mRate(new SimpleQuote(d1mQuote));

		boost::shared_ptr<Quote> d3mRate(new SimpleQuote(d3mQuote));

		boost::shared_ptr<Quote> d6mRate(new SimpleQuote(d6mQuote));

		boost::shared_ptr<Quote> d9mRate(new SimpleQuote(d9mQuote));

		boost::shared_ptr<Quote> d1yRate(new SimpleQuote(d1yQuote));

		// FRAs

		boost::shared_ptr<Quote> fra3x6Rate(new SimpleQuote(fra3x6Quote));

		boost::shared_ptr<Quote> fra6x9Rate(new SimpleQuote(fra6x9Quote));

		boost::shared_ptr<Quote> fra9x12Rate(new SimpleQuote(fra6x12Quote));

		// futures

		boost::shared_ptr<Quote> fut1Price(new SimpleQuote(fut1Quote));

		boost::shared_ptr<Quote> fut2Price(new SimpleQuote(fut2Quote));

		boost::shared_ptr<Quote> fut3Price(new SimpleQuote(fut3Quote));

		boost::shared_ptr<Quote> fut4Price(new SimpleQuote(fut4Quote));

		boost::shared_ptr<Quote> fut5Price(new SimpleQuote(fut5Quote));

		boost::shared_ptr<Quote> fut6Price(new SimpleQuote(fut6Quote));

		boost::shared_ptr<Quote> fut7Price(new SimpleQuote(fut7Quote));

		boost::shared_ptr<Quote> fut8Price(new SimpleQuote(fut8Quote));

		// swaps

		boost::shared_ptr<Quote> s2yRate(new SimpleQuote(s2yQuote));

		boost::shared_ptr<Quote> s3yRate(new SimpleQuote(s3yQuote));

		boost::shared_ptr<Quote> s5yRate(new SimpleQuote(s5yQuote));

		boost::shared_ptr<Quote> s10yRate(new SimpleQuote(s10yQuote));

		boost::shared_ptr<Quote> s15yRate(new SimpleQuote(s15yQuote));

		// ois

		boost::shared_ptr<Quote> ois1wRate(new SimpleQuote(ois1wQuote));

		boost::shared_ptr<Quote> ois1mRate(new SimpleQuote(ois1mQuote));

		boost::shared_ptr<Quote> ois3mRate(new SimpleQuote(ois3mQuote));

		boost::shared_ptr<Quote> ois6mRate(new SimpleQuote(ois6mQuote));

		boost::shared_ptr<Quote> ois9mRate(new SimpleQuote(ois9mQuote));

		boost::shared_ptr<Quote> ois1yRate(new SimpleQuote(ois1yQuote));

		boost::shared_ptr<Quote> ois2yRate(new SimpleQuote(ois2yQuote));

		boost::shared_ptr<Quote> ois3yRate(new SimpleQuote(ois3yQuote));

		boost::shared_ptr<Quote> ois5yRate(new SimpleQuote(ois5yQuote));

		boost::shared_ptr<Quote> ois10yRate(new SimpleQuote(ois10yQuote));

		boost::shared_ptr<Quote> ois15yRate(new SimpleQuote(ois15yQuote));

		/*********************

		***  FORWARD HELPERS ***

		*********************/



		// RateHelpers are built from the above quotes together with

		// other instrument dependant infos.  Quotes are passed in

		// relinkable handles which could be relinked to some other

		// data source later.



		// deposits

		DayCounter depositDayCounter = Actual360();



		// setup ois

		boost::shared_ptr<Eonia> eonia(new Eonia);



		boost::shared_ptr<RateHelper> ois1w(new OISRateHelper(

			2, 1 * Weeks, Handle<Quote>(ois1wRate), eonia));

		boost::shared_ptr<RateHelper> ois1m(new OISRateHelper(

			2, 1 * Months, Handle<Quote>(ois1mRate), eonia));

		boost::shared_ptr<RateHelper> ois3m(new OISRateHelper(

			2, 3 * Months, Handle<Quote>(ois3mRate), eonia));

		boost::shared_ptr<RateHelper> ois6m(new OISRateHelper(

			2, 6 * Months, Handle<Quote>(ois6mRate), eonia));

		boost::shared_ptr<RateHelper> ois9m(new OISRateHelper(

			2, 9 * Months, Handle<Quote>(ois9mRate), eonia));

		boost::shared_ptr<RateHelper> ois1y(new OISRateHelper(

			2, 1 * Years, Handle<Quote>(ois1yRate), eonia));

		boost::shared_ptr<RateHelper> ois2y(new OISRateHelper(

			2, 2 * Years, Handle<Quote>(ois2yRate), eonia));

		boost::shared_ptr<RateHelper> ois3y(new OISRateHelper(

			2, 3 * Years, Handle<Quote>(ois3yRate), eonia));

		boost::shared_ptr<RateHelper> ois5y(new OISRateHelper(

			2, 5 * Years, Handle<Quote>(ois5yRate), eonia));

		boost::shared_ptr<RateHelper> ois10y(new OISRateHelper(

			2, 10 * Years, Handle<Quote>(ois10yRate), eonia));

		boost::shared_ptr<RateHelper> ois15y(new OISRateHelper(

			2, 15 * Years, Handle<Quote>(ois15yRate), eonia));



		/*********************

		**  CURVE BUILDING **

		*********************/



		double tolerance = 1.0e-15;



		// A ois curve

		std::vector<boost::shared_ptr<RateHelper> > oisInstruments;

		oisInstruments.push_back(ois1w);

		oisInstruments.push_back(ois1m);

		oisInstruments.push_back(ois3m);

		oisInstruments.push_back(ois6m);

		oisInstruments.push_back(ois9m);

		oisInstruments.push_back(ois1y);

		oisInstruments.push_back(ois2y);

		oisInstruments.push_back(ois3y);

		oisInstruments.push_back(ois5y);

		oisInstruments.push_back(ois10y);

		oisInstruments.push_back(ois15y);

		// Any DayCounter would be fine.

		// ActualActual::ISDA ensures that 30 years is 30.0

		DayCounter termStructureDayCounter =

			ActualActual(ActualActual::ISDA);



		boost::shared_ptr<YieldTermStructure> OisTermStructure(

			new PiecewiseYieldCurve<Discount, LogLinear>(

				todaysDate,

				oisInstruments,

				termStructureDayCounter,

				tolerance));



		// Term structures that will be used for pricing:

		// the one used for discounting cash flows

		RelinkableHandle<YieldTermStructure> discountingTermStructure;

		discountingTermStructure.linkTo(OisTermStructure);


		boost::shared_ptr<RateHelper> d3m(new DepositRateHelper(

			Handle<Quote>(d3mRate),

			3 * Months, fixingDays,

			calendar, ModifiedFollowing,

			true, depositDayCounter));



		// setup FRAs

		boost::shared_ptr<RateHelper> fra3x6(new FraRateHelper(

			Handle<Quote>(fra3x6Rate),

			3, 6, fixingDays, calendar, ModifiedFollowing,

			true, depositDayCounter));

		boost::shared_ptr<RateHelper> fra6x9(new FraRateHelper(

			Handle<Quote>(fra6x9Rate),

			6, 9, fixingDays, calendar, ModifiedFollowing,

			true, depositDayCounter));

		boost::shared_ptr<RateHelper> fra6x12(new FraRateHelper(

			Handle<Quote>(fra9x12Rate),

			9, 12, fixingDays, calendar, ModifiedFollowing,

			true, depositDayCounter));





		// setup futures

		// Rate convexityAdjustment = 0.0;

		Integer futMonths = 3;

		Date imm = IMM::nextDate(settlementDate);

		boost::shared_ptr<RateHelper> fut1(new FuturesRateHelper(

			Handle<Quote>(fut1Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut2(new FuturesRateHelper(

			Handle<Quote>(fut2Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut3(new FuturesRateHelper(

			Handle<Quote>(fut3Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut4(new FuturesRateHelper(

			Handle<Quote>(fut4Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut5(new FuturesRateHelper(

			Handle<Quote>(fut5Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut6(new FuturesRateHelper(

			Handle<Quote>(fut6Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut7(new FuturesRateHelper(

			Handle<Quote>(fut7Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));

		imm = IMM::nextDate(imm + 1);

		boost::shared_ptr<RateHelper> fut8(new FuturesRateHelper(

			Handle<Quote>(fut8Price),

			imm,

			futMonths, calendar, ModifiedFollowing,

			true, depositDayCounter));





		// setup swaps

		Frequency swFixedLegFrequency = Annual;

		BusinessDayConvention swFixedLegConvention = Unadjusted;

		DayCounter swFixedLegDayCounter = Thirty360(Thirty360::European);

		boost::shared_ptr<ForwardIborIndex> swFloatingLegIndex(new

			ForwardIborIndex("ibor", 3 * Months, 2, EURCurrency(),

				calendar, ModifiedFollowing, true,

				depositDayCounter));



		boost::shared_ptr<RateHelper> s2y(new SwapRateHelper(

			Handle<Quote>(s2yRate), 2 * Years,

			calendar, swFixedLegFrequency,

			swFixedLegConvention, swFixedLegDayCounter,

			swFloatingLegIndex, Handle<Quote>(), 0 * Days, discountingTermStructure));

		boost::shared_ptr<RateHelper> s3y(new SwapRateHelper(

			Handle<Quote>(s3yRate), 3 * Years,

			calendar, swFixedLegFrequency,

			swFixedLegConvention, swFixedLegDayCounter,

			swFloatingLegIndex, Handle<Quote>(), 0 * Days, discountingTermStructure));

		boost::shared_ptr<RateHelper> s5y(new SwapRateHelper(

			Handle<Quote>(s5yRate), 5 * Years,

			calendar, swFixedLegFrequency,

			swFixedLegConvention, swFixedLegDayCounter,

			swFloatingLegIndex, Handle<Quote>(), 0 * Days, discountingTermStructure));

		boost::shared_ptr<RateHelper> s10y(new SwapRateHelper(

			Handle<Quote>(s10yRate), 10 * Years,

			calendar, swFixedLegFrequency,

			swFixedLegConvention, swFixedLegDayCounter,

			swFloatingLegIndex, Handle<Quote>(), 0 * Days, discountingTermStructure));

		boost::shared_ptr<RateHelper> s15y(new SwapRateHelper(

			Handle<Quote>(s15yRate), 15 * Years,

			calendar, swFixedLegFrequency,

			swFixedLegConvention, swFixedLegDayCounter,

			swFloatingLegIndex, Handle<Quote>(), 0 * Days, discountingTermStructure));



		/*********************

		**  CURVE BUILDING **

		*********************/



		// Any DayCounter would be fine.

		// ActualActual::ISDA ensures that 30 years is 30.0

		//DayCounter termStructureDayCounter =

		//    ActualActual(ActualActual::ISDA);



		// A depo-swap curve

		std::vector<boost::shared_ptr<RateHelper> > depoSwapInstruments;

		//depoSwapInstruments.push_back(d1w);

		//depoSwapInstruments.push_back(d1m);

		depoSwapInstruments.push_back(d3m);

		//depoSwapInstruments.push_back(d6m);

		//depoSwapInstruments.push_back(d9m);

		//depoSwapInstruments.push_back(d1y);

		depoSwapInstruments.push_back(s2y);

		depoSwapInstruments.push_back(s3y);

		depoSwapInstruments.push_back(s5y);

		depoSwapInstruments.push_back(s10y);

		depoSwapInstruments.push_back(s15y);

		/*
		boost::shared_ptr<ForwardRateCurve> depoSwapTermStructure(

			new FwdRateCurve<Linear>("ibor",

				3 * Months,

				2,

				EURCurrency(),

				calendar,

				ModifiedFollowing,

				true,

				depositDayCounter,

				depoSwapInstruments,

				tolerance));


*/


		// A depo-futures-swap curve

		std::vector<boost::shared_ptr<RateHelper> > depoFutSwapInstruments;

		//depoFutSwapInstruments.push_back(d1w);

		//depoFutSwapInstruments.push_back(d1m);

		depoFutSwapInstruments.push_back(fut1);

		depoFutSwapInstruments.push_back(fut2);

		depoFutSwapInstruments.push_back(fut3);

		depoFutSwapInstruments.push_back(fut4);

		depoFutSwapInstruments.push_back(fut5);

		depoFutSwapInstruments.push_back(fut6);

		depoFutSwapInstruments.push_back(fut7);

		depoFutSwapInstruments.push_back(fut8);

		depoFutSwapInstruments.push_back(s3y);

		depoFutSwapInstruments.push_back(s5y);

		depoFutSwapInstruments.push_back(s10y);

		depoFutSwapInstruments.push_back(s15y);

		/*
		boost::shared_ptr<ForwardRateCurve> depoFutSwapTermStructure(

			new FwdRateCurve<Linear>("ibor",

				3 * Months,

				2,

				EURCurrency(),

				calendar,

				ModifiedFollowing,

				true,

				depositDayCounter,

				depoFutSwapInstruments,

				tolerance));
*/




		// A depo-FRA-swap curve

		std::vector<boost::shared_ptr<RateHelper> > depoFRASwapInstruments;

		//depoFRASwapInstruments.push_back(d1w);

		//depoFRASwapInstruments.push_back(d1m);

		depoFRASwapInstruments.push_back(d3m);

		depoFRASwapInstruments.push_back(fra3x6);

		depoFRASwapInstruments.push_back(fra6x9);

		depoFRASwapInstruments.push_back(fra6x12);

		depoFRASwapInstruments.push_back(s2y);

		depoFRASwapInstruments.push_back(s3y);

		depoFRASwapInstruments.push_back(s5y);

		depoFRASwapInstruments.push_back(s10y);

		depoFRASwapInstruments.push_back(s15y);
		/*
		boost::shared_ptr<ForwardRateCurve> depoFRASwapTermStructure(

			new FwdRateCurve<Linear>("ibor",

				3 * Months,

				2,

				EURCurrency(),

				calendar,

				ModifiedFollowing,

				true,

				depositDayCounter,

				depoFRASwapInstruments,

				tolerance));





		// the one used for forward rate forecasting

		RelinkableHandle<ForwardRateCurve> forecastingTermStructure;

*/



		/*********************

		* SWAPS TO BE PRICED *

		**********************/

/*

		// constant nominal 1,000,000 Euro

		Real nominal = 1000000.0;

		// fixed leg

		Frequency fixedLegFrequency = Annual;

		BusinessDayConvention fixedLegConvention = Unadjusted;

		BusinessDayConvention floatingLegConvention = ModifiedFollowing;

		DayCounter fixedLegDayCounter = Thirty360(Thirty360::European);

		Rate fixedRate = 0.04;

		DayCounter floatingLegDayCounter = Actual360();



		// floating leg

		Frequency floatingLegFrequency = Quarterly;

		boost::shared_ptr<ForwardIborIndex> euriborIndex(

			new ForwardIborIndex("ibor", 3 * Months, 2, EURCurrency(),

				calendar, ModifiedFollowing, true,

				depositDayCounter,

				forecastingTermStructure));

		Spread spread = 0.0;



		Integer lenghtInYears = 5;

		VanillaSwap::Type swapType = VanillaSwap::Payer;



		Date maturity = settlementDate + lenghtInYears * Years;

		Schedule fixedSchedule(settlementDate, maturity,

			Period(fixedLegFrequency),

			calendar, fixedLegConvention,

			fixedLegConvention,

			DateGeneration::Forward, false);

		Schedule floatSchedule(settlementDate, maturity,

			Period(floatingLegFrequency),

			calendar, floatingLegConvention,

			floatingLegConvention,

			DateGeneration::Forward, false);

		VanillaSwap spot5YearSwap(swapType, nominal,

			fixedSchedule, fixedRate, fixedLegDayCounter,

			floatSchedule, euriborIndex, spread,

			floatingLegDayCounter);



		Date fwdStart = calendar.advance(settlementDate, 1, Years);

		Date fwdMaturity = fwdStart + lenghtInYears * Years;

		Schedule fwdFixedSchedule(fwdStart, fwdMaturity,

			Period(fixedLegFrequency),

			calendar, fixedLegConvention,

			fixedLegConvention,

			DateGeneration::Forward, false);

		Schedule fwdFloatSchedule(fwdStart, fwdMaturity,

			Period(floatingLegFrequency),

			calendar, floatingLegConvention,

			floatingLegConvention,

			DateGeneration::Forward, false);

		VanillaSwap oneYearForward5YearSwap(swapType, nominal,

			fwdFixedSchedule, fixedRate, fixedLegDayCounter,

			fwdFloatSchedule, euriborIndex, spread,

			floatingLegDayCounter);
*/


RelinkableHandle<YieldTermStructure> euriborTermStructure;
boost::shared_ptr<IborIndex> euriborIndex(
	new Euribor3M(euriborTermStructure));

		//ACDT-ABCD Test

		//////////////////////   ACDT1

		//acdt1 coefficients
		std::vector<Real> coeffsacdt1(4);

		coeffsacdt1[0] = 0.001;

		coeffsacdt1[1] = 0.0019;

		coeffsacdt1[2] = 0.002;

		coeffsacdt1[3] = 2;


		Real Implied_b = (coeffsacdt1[0] * coeffsacdt1[1]) / (1 - coeffsacdt1[3] * coeffsacdt1[1]);
		
		//Levenberg
		boost::shared_ptr<OptimizationMethod> Lev(new LevenbergMarquardt());
		
		//acdt building with and without pointer
		boost::shared_ptr<TenorBasis> tenorBasisAcdt1(
			new AcdtTenorBasis(euriborIndex,

				boost::shared_ptr<Eonia>(

					new Eonia(discountingTermStructure)),

				settlementDate,

				false,

				coeffsacdt1));

		AcdtTenorBasis tenorBasisAcdt1_(euriborIndex,

				boost::shared_ptr<Eonia>(

					new Eonia(discountingTermStructure)),

				settlementDate,

				false,

				coeffsacdt1);

		//calibration parameters

		//weights
		std::vector<QuantLib::Real> w;
		int size = depoFRASwapInstruments.size();
		w.resize(size);
		for (int i = 0;i < size;i++) {
			w[i] = 1.0;
		}

		//EndCriteria
		Size maxIterations = 1000;
		Size maxStationaryStateIterations = 100;
		Real rootEpsilon = 0.0001;
		Real functionEpsilon = 0.00001;
		Real gradientNormEpsilon = 0.00001;
		EndCriteria endCriteria(maxIterations,
			maxStationaryStateIterations,
			rootEpsilon,
			functionEpsilon,
			gradientNormEpsilon);


		//boolean
		std::vector<bool> fixParaAcdt;
		fixParaAcdt.push_back(false);
		fixParaAcdt.push_back(false);
		fixParaAcdt.push_back(false);
		fixParaAcdt.push_back(false);
		

		//calibrate acdt object
		tenorBasisAcdt1_.calibrate(depoFRASwapInstruments, *Lev, endCriteria, w, fixParaAcdt);
		tenorBasisAcdt1->calibrate(depoFRASwapInstruments, *Lev, endCriteria, w, fixParaAcdt);
		////////////////////////////////////////////   Acdt2			

			std::vector<Real> coeffsacdt2(4);

			coeffsacdt2[0] = coeffsacdt1[0];

			coeffsacdt2[1] = coeffsacdt1[1];//equal guess

			coeffsacdt2[2] = coeffsacdt1[2];

			coeffsacdt2[3] = 2;





			boost::shared_ptr<TenorBasis> tenorBasisAcdt2(
				new AcdtTenorBasis(euriborIndex,

					boost::shared_ptr<Eonia>(

						new Eonia(discountingTermStructure)),

					settlementDate,

					false,

					coeffsacdt2));


			tenorBasisAcdt2->calibrate(depoFRASwapInstruments, *Lev, endCriteria, w, fixParaAcdt);
		
		//ABCD

		//abcd coefficients

		std::vector<Real> coeffs(4);

		coeffs[0] = coeffsacdt1[0];

		coeffs[1] = Implied_b;//equal guess

		coeffs[2] = coeffsacdt1[1];

		coeffs[3] = coeffsacdt1[2];


		//Abcd building w & wo pointer
		boost::shared_ptr<TenorBasis> tenorBasisAbcd(
			new AbcdTenorBasis(euriborIndex,

				boost::shared_ptr<Eonia>(

					new Eonia(discountingTermStructure)),

				settlementDate,

				false,

				coeffs));

		AbcdTenorBasis tenorBasisAbcd_(euriborIndex,

				boost::shared_ptr<Eonia>(

					new Eonia(discountingTermStructure)),

				settlementDate,

				false,

				coeffs);

		//calibration parameters
		std::vector<bool> fixParaAbcd;
		fixParaAbcd.push_back(false);
		fixParaAbcd.push_back(false);
		fixParaAbcd.push_back(false);
		fixParaAbcd.push_back(false);

		//calibrate
		tenorBasisAbcd->calibrate(depoFRASwapInstruments, *Lev, endCriteria, w, fixParaAbcd);
		tenorBasisAbcd_.calibrate(depoFRASwapInstruments, *Lev, endCriteria, w, fixParaAbcd);

		//consistency test

		std::vector<Real> acdt;
		std::vector<Real> abcd;
		std::vector<Real> acdt_P;

		//inst basis coefficients
		acdt = tenorBasisAcdt1_.instCoefficients();
		abcd = tenorBasisAbcd->instCoefficients();
		acdt_P = tenorBasisAcdt1->instCoefficients();

		// retrieving t_max
		Real t_1= 1 / acdt[2] - acdt[0] / acdt[1];
		Real t_2= 1 / abcd[2] - abcd[0] / abcd[1]; 
		Real t_3 = 1 / acdt_P[2] - acdt_P[0] / acdt_P[1];

		Date d1 = tenorBasisAcdt1_.maximumLocation();
		Date d2 = tenorBasisAbcd_.maximumLocation();
		Real t_1_ = tenorBasisAcdt1_.timeFromReference(d1);
		Real t_2_ = tenorBasisAbcd_.timeFromReference(d2);

		std::cout << "Test consistency abcd VS acdt" << std::endl;std::cout << std::endl;

		std::cout << "Guesses acdt"<< std::endl;std::cout << std::endl;

		std::cout << "a=" << coeffsacdt1[0] << std::endl;
		std::cout << "c=" << coeffsacdt1[1] << std::endl;
		std::cout << "d=" << coeffsacdt1[2] << std::endl;
		std::cout << "t=" << coeffsacdt1[3] << std::endl;
		std::cout << "Implied b=" <<Implied_b << std::endl;std::cout << std::endl;

		std::cout << "Calibrated acdt" << std::endl;std::cout << std::endl;
		std::cout << "a=" << acdt[0] << std::endl;
		std::cout << "b=" << acdt[1] << std::endl;
		std::cout << "c=" << acdt[2] << std::endl;
		std::cout << "d=" << acdt[3] << std::endl;
		std::cout << "Implied t=" << t_1 << std::endl;
		std::cout << "Model t=" << t_1_ << std::endl;

		std::cout << std::endl;

		std::cout << "Calibrated pointer acdt" << std::endl;std::cout << std::endl;

		std::cout << "a=" << acdt_P[0] << std::endl;
		std::cout << "b=" << acdt_P[1] << std::endl;
		std::cout << "c=" << acdt_P[2] << std::endl;
		std::cout << "d=" << acdt_P[3] << std::endl;
		std::cout << "Implied t=" << t_3 << std::endl;
		std::cout << "Model t=" << "Not available, beacuse Tenor basis has no maximumLocation()"<< std::endl;

		std::cout << std::endl;

		std::cout << "Guesses abcd" << std::endl;std::cout << std::endl;

		std::cout << "a=" << coeffs[0] << std::endl;
		std::cout << "b=" << coeffs[1] << std::endl;
		std::cout << "c=" << coeffs[2] << std::endl;
		std::cout << "d=" << coeffs[3] << std::endl;
		std::cout << "Implied t=" << 1/ coeffs[2]- coeffs[0]/ coeffs[1] << std::endl;std::cout << std::endl;


		std::cout << "Calibrated abcd" << std::endl;std::cout << std::endl;

		std::cout << "a=" << abcd[0] << std::endl;
		std::cout << "b=" << abcd[1] << std::endl;
		std::cout << "c=" << abcd[2] << std::endl;
		std::cout << "d=" << abcd[3] << std::endl;
		std::cout << "Implied t=" << t_2 << std::endl;
		std::cout << "Model t=" << t_2_ << std::endl;

		system("pause");



/*
		{

			///////////GLOBAL MODEL TEST

			//weights
			std::vector<QuantLib::Real> weights;
			size = depoFRASwapInstruments.size();
			weights.resize(size);
			for (int i = 0;i < size;i++) {
				weights[i] = 1.0;
			}
			//fixpara for helper calibration
			std::vector<bool> fixParaAcdt1;
			std::vector<bool> fixParaAcdt2;
			fixParaAcdt1.push_back(false);
			fixParaAcdt1.push_back(false);
			fixParaAcdt1.push_back(false);
			fixParaAcdt1.push_back(true);

			fixParaAcdt2.push_back(false);
			fixParaAcdt2.push_back(false);
			fixParaAcdt2.push_back(false);
			fixParaAcdt2.push_back(true);
			//Global Helper
			boost::shared_ptr<GlobalHelper> globalHelper1(new GlobalHelper(tenorBasisAcdt1, depoFRASwapInstruments, Lev, endCriteria, weights, fixParaAcdt1));
			boost::shared_ptr<GlobalHelper> globalHelper2(new GlobalHelper(tenorBasisAcdt2, depoFRASwapInstruments, Lev, endCriteria, weights, fixParaAcdt2));
			std::vector<boost::shared_ptr<GlobalHelper>> helperVec;
			helperVec.push_back(globalHelper1);
			helperVec.push_back(globalHelper2);
			//global model parameters
			std::vector<QuantLib::Real> we;//weights
			int size1 = helperVec.size();
			we.push_back(1.0);
			we.push_back(1.0);
			QuantLib::Size s; //Number of parameters
			s = 1;
			QuantLib::Real coef = 2;//coeff time
			std::vector<QuantLib::Integer> position;
			position.push_back(3);//time
			int innerError = 1;//just one global error
			std::vector<bool> fixPara;
			fixPara.push_back(false);
			GlobalModel GM(s, coef, position, innerError, Lev, endCriteria, we, fixPara);

			GM.calibrate(helperVec, *Lev, endCriteria, we, fixPara);
			acdt = tenorBasisAcdt1->instCoefficients();
			abcd = tenorBasisAcdt2->instCoefficients();
			std::cout << "acdt" << acdt[0] << std::endl;
			std::cout << "abcd" << abcd[0] << std::endl;
			system("pause");
		}*/
		return 0;
};


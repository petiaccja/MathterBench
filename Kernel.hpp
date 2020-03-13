#pragma once

#include <chrono>
#include <vector>
#include <algorithm>


#ifdef _MSC_VER
#include <intrin.h>
#define USE_RDTSC
#elif __GNUC__
#include <x86intrin.h>
#define USE_RDTSC
#endif


struct Timing {
	std::chrono::nanoseconds timeTotal;
	unsigned long long cyclesTotal;
	double timePerOpNs;
	double cyclesPerOp;
};

struct Measurement {
	double minTimePerOpNs;
	double maxTimePerOpNs;
	double avgTimePerOpNs;
	double minCyclesPerOp;
	double maxCyclesPerOp;
	double avgCyclesPerOp;
	int numTimesRun;
	int size;
	int rep;
};

uint64_t ReadTSC() {
#ifdef USE_RDTSC
	return (uint64_t)__rdtsc();
#else
	return 0;
#endif
}


template <class Lhs, class Rhs, class Result, class InitLhs, class InitRhs>
Timing BinaryKernel(Result (*binaryOp)(const Lhs&, const Rhs&), const InitLhs& initLhs, const InitRhs& initRhs, size_t size, size_t repeat) {
	std::vector<Lhs> lhs(size);
	std::vector<Rhs> rhs(size);
	for (size_t i = 0; i < size; ++i) {
		initLhs(lhs[i]);
		initRhs(rhs[i]);
	}

	std::chrono::high_resolution_clock::time_point start, end;
	uint64_t startClk, endClk;

	if constexpr (!std::is_void_v<Result>) {
		std::vector<Result> result(size);

		start = std::chrono::high_resolution_clock::now();
		startClk = ReadTSC();
		for (size_t rep = 0; rep < repeat; ++rep) {
			for (size_t i = 0; i < size; ++i) {
				result[i] = binaryOp(lhs[i], rhs[i]);
			}
		}
		endClk = ReadTSC();
		end = std::chrono::high_resolution_clock::now();
	}
	else {
		start = std::chrono::high_resolution_clock::now();
		startClk = ReadTSC();
		for (size_t rep = 0; rep < repeat; ++rep) {
			for (size_t i = 0; i < size; ++i) {
				binaryOp(lhs[i], rhs[i]);
			}
		}
		endClk = ReadTSC();
		end = std::chrono::high_resolution_clock::now();
	}

	std::chrono::nanoseconds timeTotal = end - start;
	uint64_t cyclesTotal = endClk - startClk;
	size_t opsTotal = size * repeat;

	return Timing{ .timeTotal = timeTotal,
				   .cyclesTotal = cyclesTotal,
				   .timePerOpNs = double(timeTotal.count()) / double(opsTotal),
				   .cyclesPerOp = double(cyclesTotal) / double(opsTotal) };
}

template <class Arg, class Result, class Init>
Timing UnaryKernel(Result (*unaryOp)(const Arg&), const Init& init, size_t size, size_t repeat) {
	std::vector<Arg> arg(size);
	for (size_t i = 0; i < size; ++i) {
		init(arg[i]);
	}

	std::chrono::high_resolution_clock::time_point start, end;
	uint64_t startClk, endClk;

	if constexpr (!std::is_void_v<Result>) {
		std::vector<Result> result(size);

		start = std::chrono::high_resolution_clock::now();
		startClk = ReadTSC();
		for (size_t rep = 0; rep < repeat; ++rep) {
			for (size_t i = 0; i < size; ++i) {
				result[i] = unaryOp(arg[i]);
			}
		}
		endClk = ReadTSC();
		end = std::chrono::high_resolution_clock::now();
	}
	else {
		auto start = std::chrono::high_resolution_clock::now();
		startClk = ReadTSC();
		for (size_t rep = 0; rep < repeat; ++rep) {
			for (size_t i = 0; i < size; ++i) {
				unaryOp(arg[i]);
			}
		}
		endClk = ReadTSC();
		end = std::chrono::high_resolution_clock::now();
	}

	std::chrono::nanoseconds timeTotal = end - start;
	uint64_t cyclesTotal = endClk - startClk;
	size_t opsTotal = size * repeat;

	return Timing{ .timeTotal = timeTotal,
				   .cyclesTotal = cyclesTotal,
				   .timePerOpNs = double(timeTotal.count()) / double(opsTotal),
				   .cyclesPerOp = double(cyclesTotal) / double(opsTotal) };
}


template <class Func>
Measurement Measure(Func func) {
	try {
		using namespace std::chrono_literals;

		const int initialSize = 750;
		const int initialRep = 100;
		int samplesDesired = 500;
		double timeTotalDesired = 0.10f; // 100 ms
		double timeSampleDesired = timeTotalDesired / samplesDesired;
		Timing initial = func(initialSize, initialRep);
		double timeInitial = std::chrono::nanoseconds(initial.timeTotal).count() / 1e9;
		double scaling = timeSampleDesired / timeInitial;

		const int size = std::min(1000, std::max(200, int(initialSize * scaling)));
		const int rep = initialRep;

		Timing sum = { 0ns, 0, 0, 0 };
		Timing min = { 100000000000000000ns, 1000000000000000000ull, 1e20, 1e20 };
		Timing max = { 0ns, 0, 0, 0 };
		for (int i = 0; i < samplesDesired; ++i) {
			Timing timing = func(size, rep);

			sum.timeTotal += timing.timeTotal;
			sum.cyclesTotal += timing.cyclesTotal;
			sum.cyclesPerOp += timing.cyclesPerOp;
			sum.timePerOpNs += timing.timePerOpNs;

			min.timeTotal = std::min(min.timeTotal, timing.timeTotal);
			min.cyclesTotal = std::min(min.cyclesTotal, timing.cyclesTotal);
			min.cyclesPerOp = std::min(min.cyclesPerOp, timing.cyclesPerOp);
			min.timePerOpNs = std::min(min.timePerOpNs, timing.timePerOpNs);

			max.timeTotal = std::max(max.timeTotal, timing.timeTotal);
			max.cyclesTotal = std::max(max.cyclesTotal, timing.cyclesTotal);
			max.cyclesPerOp = std::max(max.cyclesPerOp, timing.cyclesPerOp);
			max.timePerOpNs = std::max(max.timePerOpNs, timing.timePerOpNs);
		}

		Measurement meas;
		meas.minCyclesPerOp = min.cyclesPerOp;
		meas.maxCyclesPerOp = max.cyclesPerOp;
		meas.avgCyclesPerOp = sum.cyclesPerOp / samplesDesired;

		meas.minTimePerOpNs = min.timePerOpNs;
		meas.maxTimePerOpNs = max.timePerOpNs;
		meas.avgTimePerOpNs = sum.timePerOpNs / samplesDesired;

		meas.numTimesRun = samplesDesired;
		meas.rep = rep;
		meas.size = size;

		return meas;
	}
	catch (...) {
		return Measurement{ 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}
}


template <class Lhs, class Rhs, class Result, class InitLhs, class InitRhs>
Measurement MeasureBinaryKernel(Result (*binaryOp)(const Lhs&, const Rhs&), const InitLhs& initLhs, const InitRhs& initRhs) {
	return Measure([&](size_t size, size_t reps) {
		return BinaryKernel(binaryOp, initLhs, initRhs, size, reps);
	});
}

template <class Arg, class Result, class Init>
Measurement MeasureUnaryKernel(Result (*unaryOp)(const Arg&), const Init& init) {
	return Measure([&](size_t size, size_t reps) {
		return UnaryKernel(unaryOp, init, size, reps);
	});
}
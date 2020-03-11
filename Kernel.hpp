#pragma once

#include <chrono>
#include <vector>


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
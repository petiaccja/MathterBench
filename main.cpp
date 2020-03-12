#include "Config.hpp"
#include "Process.hpp"
#include "Wrappers/EigenWrapper.hpp"
#include "Wrappers/MathterWrapper.hpp"

#include <iostream>
#include <iomanip>


std::string MakeCSV(const std::vector<std::string>& libNames, const std::vector<std::vector<Result>>& results) {
	const size_t numClasses = results[0].size();
	const size_t numLibraries = results.size();

	std::stringstream csvText;

	csvText << ",";
	for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
		csvText << "," << libNames[libIndex];
	}
	csvText << std::endl;

	for (size_t classIndex = 0; classIndex < numClasses; ++classIndex) {
		csvText << results[0][classIndex].name;
		for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
			csvText << "," << std::fixed << std::setprecision(3) << results[libIndex][classIndex].timing.minCyclesPerOp;
		}
		csvText << std::endl;
	}

	return csvText.str();
}


std::string MakeMarkdown(const std::vector<std::string>& libNames, const std::vector<std::vector<Result>>& results) {
	const size_t numClasses = results[0].size();
	const size_t numLibraries = results.size();

	std::stringstream markdownText;

	markdownText << "| ";
	for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
		markdownText << "|" << libNames[libIndex];
	}
	markdownText << "|" << std::endl;
	markdownText << "|:---|";
	for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
		markdownText << "---:|";
	}
	markdownText << "\n";

	for (size_t classIndex = 0; classIndex < numClasses; ++classIndex) {
		markdownText << "|" << results[0][classIndex].name;
		for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
			markdownText << "|" << std::fixed << std::setprecision(3) << results[libIndex][classIndex].timing.minCyclesPerOp;
		}
		markdownText << "|" << std::endl;
	}

	return markdownText.str();
}


std::vector<std::vector<Result>> NormalizeTimes(std::vector<std::vector<Result>> results) {
	const size_t numClasses = results[0].size();
	const size_t numLibraries = results.size();

	for (size_t classIndex = 0; classIndex < numClasses; ++classIndex) {
		double minCycles = 1e+100;
		for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
			double cycles = results[libIndex][classIndex].timing.minCyclesPerOp;
			minCycles = std::min(cycles, minCycles);
		}
		for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
			double& cycles = results[libIndex][classIndex].timing.minCyclesPerOp;
			cycles /= minCycles;
		}
	}

	return results;
}


int main() {
	std::cout << "[[ Initialize ]]" << std::endl;
	SetPriority();
	SetAffinity();
	std::cout << "\n\n";
	;
	std::vector<std::vector<Result>> results(2);

	std::cout << "[[ Mathter... ]]";
	results[0] = Config<MathterWrapper>();
	std::cout << std::endl;

	for (auto v : results[0]) {
		std::cout << v.timing.numTimesRun << ", " << v.timing.size << ", " << v.timing.rep << "\n";
	}
	std::cout << std::endl;

	std::cout << "[[ Eigen... ]]";
	results[1] = Config<EigenWrapper>();
	std::cout << std::endl << "\n";

	// Make a markdown
	std::vector<std::string> libNames = {
		"Mathter",
		"Eigen",
	};
	std::cout << MakeMarkdown(libNames, results) << std::endl;

	// Normalized results
	auto normedResults = NormalizeTimes(results);
	std::cout << MakeMarkdown(libNames, normedResults) << std::endl;

	return 0;
}

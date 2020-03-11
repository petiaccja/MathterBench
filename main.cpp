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
			csvText << "," << std::fixed << std::setprecision(3) << results[libIndex][classIndex].timing.cyclesPerOp;
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
			markdownText << "|" << std::fixed << std::setprecision(3) << results[libIndex][classIndex].timing.cyclesPerOp;
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
			double cycles = results[libIndex][classIndex].timing.cyclesPerOp;
			minCycles = std::min(cycles, minCycles);
		}
		for (size_t libIndex = 0; libIndex < numLibraries; ++libIndex) {
			double& cycles = results[libIndex][classIndex].timing.cyclesPerOp;
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

	std::cout << "[[ Mathter ]]\n\n";
	results[0] = Config<MathterWrapper>();

	for (const auto& result : results[0]) {
		std::cout << result.name << "\t" << result.timing.cyclesPerOp << " cycles/op" << std::endl;
	}
	std::cout << "\n\n";

	std::cout << "[[ Eigen ]]\n\n";
	results[1] = Config<EigenWrapper>();

	for (const auto& result : results[0]) {
		std::cout << result.name << "\t" << result.timing.cyclesPerOp << " cycles/op" << std::endl;
	}
	std::cout << "\n\n";

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

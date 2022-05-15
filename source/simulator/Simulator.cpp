
#include <simulator/Simulator.hpp>
#include <simulator/function/FunctionFactory.hpp>

#include <iostream>
#include <random>



namespace simulator {

void Simulator::simulate(const std::string &path, int numberOfRuns, int dimension, int fes,
						 function::FunctionEnum functionType, AlgorithmType algoType) {
	function_ = function::FunctionFactory::makeFunction(functionType);
	fes_ = fes;
	dimension_ = dimension;
	outputFile_.open(path + ".csv");
	numberOfRuns_ = numberOfRuns;
	writeHeader();



	//todo algorithm should be class on its own
	for(actualRun_ = 0; actualRun_ < numberOfRuns_; actualRun_++) {
		Run run;
		run.runNumber = actualRun_;
		results_.push_back(run);
		switch(algoType) {
			case AlgorithmType::RANDOM_SEARCH:
				randomSearch();
				break;
			case AlgorithmType::HILL_CLIMBING:
				hillClimbing();
				break;
		}
	}

	writeRuns();
	results_.clear();

	outputFile_.close();
}

void Simulator::randomSearch() {
	structure::Point bestPosition { dimension_ };
	structure::Point actualPosition(dimension_);
	double bestFitness, actualFitness;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> gen(-function_->getBoundary(), function_->getBoundary());

	for(int i = 0; i < dimension_; i++) {
		actualPosition[i] = gen(mt);
	}

	bestPosition = actualPosition;
	bestFitness = function_->calculateFitness(bestPosition);

	for(int step = 0; step < fes_; step++) {
		///generate new point
		for(int i = 0; i < dimension_; i++) {
			actualPosition[i] = gen(mt);
		}

		if(!function_->isWithinBoundary(actualPosition)) {
			throw std::out_of_range("Somehow I ended up outside of the range");
		}

		actualFitness = function_->calculateFitness(actualPosition);
		if(actualFitness < bestFitness) {
			bestPosition = actualPosition;
			bestFitness = actualFitness;
		}
		results_.at(actualRun_).costFunctionValues.push_back(bestFitness);
	}

}

void Simulator::hillClimbing() {
	double maxStep = function_->getBoundary()/10; /// max 10 % step allowed
	structure::Point bestPosition { dimension_ };
	structure::Point actualPosition(dimension_);
	double bestFitness, actualFitness;

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> gen(-function_->getBoundary(), function_->getBoundary());

	for(int i = 0; i < dimension_; i++) {
		actualPosition[i] = gen(mt);
	}

	bestPosition = actualPosition;
	bestFitness = function_->calculateFitness(bestPosition);




}

Simulator::~Simulator() {
	if(outputFile_.is_open()) {
		outputFile_.close();
	}
}

void Simulator::writeRuns() {
	for(int i = 0; i < fes_; i++) {
		double average = 0;
		for(int j = 0; j < numberOfRuns_; j++) {
			outputFile_ << results_[j].costFunctionValues[i] << ",";
			average += results_[j].costFunctionValues[i];
		}
		outputFile_ << average/numberOfRuns_;
		outputFile_ << "\n";
	}
}

void Simulator::writeHeader() {
	for(int i = 1; i <= numberOfRuns_; i++) {
		outputFile_ << "run" << std::to_string(i) << ",";
	}
	outputFile_ << "average";
	outputFile_ << std::endl;
}


}
#include <iostream>

#include <simulator/Simulator.hpp>

int main() {
	using namespace simulator;


	try{
		Simulator sim;
/*		sim.simulate("../output/converg_random_schweffel_5dim",30, 5,10000,function::FunctionEnum::SCHWEFFEL, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_schweffel_10dim",30, 10,10000,function::FunctionEnum::SCHWEFFEL, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_schweffel_20dim",30, 20,10000,function::FunctionEnum::SCHWEFFEL, AlgorithmType::RANDOM_SEARCH);

		sim.simulate("../output/converg_random_dejong1_5dim",30, 5,10000,function::FunctionEnum::DEJONG_1, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_dejong1_10dim",30, 10,10000,function::FunctionEnum::DEJONG_1, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_dejong1_20dim",30, 20,10000,function::FunctionEnum::DEJONG_1, AlgorithmType::RANDOM_SEARCH);

		sim.simulate("../output/converg_random_dejong2_5dim",30, 5,10000,function::FunctionEnum::DEJONG_2, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_dejong2_10dim",30, 10,10000,function::FunctionEnum::DEJONG_2, AlgorithmType::RANDOM_SEARCH);
		sim.simulate("../output/converg_random_dejong2_20dim",30, 20,10000,function::FunctionEnum::DEJONG_2, AlgorithmType::RANDOM_SEARCH);*/

		sim.simulate("../output/converg_hillclimb_schweffel_5dim",30, 5,10000,function::FunctionEnum::SCHWEFFEL, AlgorithmType::HILL_CLIMBING);
	}catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	}catch(...){
		std::cerr << "Unknown exception" << std::endl;
	}
	return 0;
}

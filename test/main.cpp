#include <iostream>
#include "InputInterface.h"
#include "Scanner.h"
#include "Log.h"
#include "Regex.h"

using namespace std;

int main(){
    cout<<"Hello, World!"<<endl;
	MSSL::Input::InputInterface input;
	input.setStream("mostafa");
	input.push("saadp");

	MSSL::Scan::Scanner scn;

	scn.addScanMachine(std::regex("saad"), MSSL::Scan::make_tag("lastname"));
	scn.addScanMachine(std::regex("mostafa"), MSSL::Scan::make_tag("firstname"));
	

	auto result = scn.scan(input);
	for (auto r : result)
	{
		std::cout << std::get<0>(r) <<", "<< std::get<1>(r)->name << std::endl;
	}

	std::cout << MSSL::Log::getLogText();


	std::cout << "test regex" << std::endl;
	auto regex_instance = MSSL::Automata::Regex::Create("mostafa");
	std::string name = "mostafax";
	for (auto c : name) 
	{
		auto state = regex_instance->consume(c);
		std::cout << static_cast<int>(state) << std::endl;
		if (state == MSSL::Automata::ConsumptionState::ACCEPT)
			std::cout << "accept" << std::endl;
		else if (state == MSSL::Automata::ConsumptionState::DEADEND)
			std::cout << "deadend" << std::endl;
		else if (state == MSSL::Automata::ConsumptionState::NONE)
		{
			std::cout << "NONE" << std::endl;
			break;
		}
	}
    return 0;
}

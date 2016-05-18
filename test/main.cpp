#include <iostream>
#include "InputInterface.h"
#include "Scanner.h"
#include "Log.h"

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


    return 0;
}

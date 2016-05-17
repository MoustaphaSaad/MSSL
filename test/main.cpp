#include <iostream>
#include "InputInterface.h"
#include "Scanner.h"

using namespace std;

int main(){
    cout<<"Hello, World!"<<endl;
	MSSL::Input::InputInterface input;
	input.setStream("mostafa");
	input.push("saad");

	MSSL::Scan::Scanner scn;

	MSSL::Scan::Tag* tag = new MSSL::Scan::Tag();
	tag->isValid = true;
	tag->name = "firstname";
	scn.addScanMachine(std::regex("mostafa"), tag);

	tag = new MSSL::Scan::Tag();
	tag->isValid = true;
	tag->name = "lastname";
	scn.addScanMachine(std::regex("saad"), tag);

	auto result = scn.scan(input);
	for (auto r : result)
	{
		std::cout << std::get<0>(r) <<", "<< std::get<1>(r)->name << std::endl;
	}


    return 0;
}

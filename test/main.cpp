#include <iostream>
#include "InputInterface.h"
using namespace std;

int main(){
    cout<<"Hello, World!"<<endl;
	MSSL::Input::InputInterface input;
	input.setStream("mostafa");
	input.push("saad");
	while (!input.eof())
		cout << input.consume();
	cout << endl;

	MSSL::Input::IInputInterface ii(std::cin);
	
	std::string line;
	while (std::getline(ii.m_stream, line))
		cout << line << endl;

    return 0;
}

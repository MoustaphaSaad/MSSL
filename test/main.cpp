#include <iostream>
#include "InputInterface.h"
#include "Scanner.h"
#include "Log.h"
#include "NFA.h"

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

	MSSL::Automata::NFA<char> nfa;
	auto s = std::make_shared<MSSL::Automata::State<char>>();
	auto ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('m', ns);
	nfa.addState(s);
	nfa.setStartState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('o', ns);
	nfa.addState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('s', ns);
	nfa.addState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('t', ns);
	nfa.addState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('a', ns);
	nfa.addState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>();
	s->addTransition('f', ns);
	nfa.addState(s);

	s = ns;
	ns = std::make_shared<MSSL::Automata::State<char>>(true);
	s->addTransition('a', ns);
	nfa.addState(s);
	nfa.addState(ns);

	string word = "mostafa";
	nfa.reset();
	for (auto c : word)
		std::cout << (int) nfa.consume(c) << std::endl;

    return 0;
}

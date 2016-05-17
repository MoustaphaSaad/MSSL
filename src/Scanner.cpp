#include "Scanner.h"
#include <iostream>
#include <tuple>
using namespace MSSL::Scan;

Scanner::Scanner()
{
	
}

Scanner::~Scanner()
{
	m_scanMachines.clear();
}

std::vector<std::tuple<std::regex, const Tag*>> Scanner::getScanMachines() const
{
	return m_scanMachines;
}

std::vector<std::tuple<std::string, const Tag*>> Scanner::scan(MSSL::Input::InputInterface& inputStream)
{
	std::vector<std::tuple<std::string, const Tag*>> result;
	std::string cut = inputStream.delimiterCut();
	
	if (cut.empty())
		return result;

	while (!cut.empty()) {
		bool match = false;
		for (auto scanMachine : m_scanMachines)
		{
			std::smatch match_object;
			bool matched = std::regex_search(cut, match_object, std::get<0>(scanMachine));
			if (matched)
			{
				match = true;
				std::cout << match_object.position() << ", " << match_object.length() << std::endl;
				auto startIndex = match_object.position() + match_object.length();
				result.push_back(std::make_tuple(match_object.str(), std::get<1>(scanMachine)));
				cut = cut.substr(startIndex, cut.size() - startIndex);
				break;
			}
		}
		if(!match)
		{
			std::cout << "Error with: " << cut <<std::endl;
			break;
		}
	}

	return result;
}

void Scanner::addScanMachine(const std::regex& scanMachine, const Tag* tag)
{
	m_scanMachines.push_back(std::make_tuple(scanMachine, tag));
}
#include "Scanner.h"
#include "Log.h"
#include <iostream>
#include <tuple>
using namespace MSSL::Scan;

Tag* MSSL::Scan::make_tag(std::string name, std::function<bool(Input::InputInterface&)> function)
{
	Tag* result = new Tag();
	result->isValid = true;
	result->name = name;
	result->tagFunction = function;
	return result;
}

bool MSSL::Scan::scan_error(std::string input, Input::Position position)
{
	Log::log(LOG_LEVEL::ERROR, "cannot scan '" + input + "'", position);
	return true;
}

Scanner::Scanner()
{
	
}

Scanner::~Scanner()
{
	for (auto& scanMachine : m_scanMachines)
		delete std::get<1>(scanMachine);
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

				if(std::get<1>(scanMachine)->tagFunction != nullptr)
				{
					bool tagFuncResult = std::get<1>(scanMachine)->tagFunction(inputStream);
					if(!tagFuncResult)
					{
						Log::log(LOG_LEVEL::LOG,
							"tag function '" + std::get<1>(scanMachine)->name + "' problem with input '"+cut+"'",
							inputStream.getCurrentPosition());
					}
				}

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
			if(scan_error(cut,inputStream.getCurrentPosition()) == true)
				break;
			//else
				//throw exception
		}
	}

	return result;
}

void Scanner::addScanMachine(const std::regex& scanMachine, const Tag* tag)
{
	m_scanMachines.push_back(std::make_tuple(scanMachine, tag));
}

Tag::Tag()
{
	isValid = true;
	name = "";
	tagFunction = nullptr;
}
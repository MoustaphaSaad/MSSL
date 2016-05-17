#pragma once

#include "Globals.h"
#include "InputInterface.h"
#include <regex>
#include <vector>
#include <string>
#include <tuple>

namespace MSSL
{
	namespace Scan
	{
		struct Tag
		{
			bool isValid;
			std::string name;
		};

		class MSSL_API Scanner
		{
		protected:
			std::vector<std::tuple<std::regex, const Tag*>> m_scanMachines;

		public:
			Scanner();
			virtual ~Scanner();

			std::vector<std::tuple<std::regex, const Tag*>> getScanMachines() const;

			virtual std::vector<std::tuple<std::string, const Tag*>> scan(Input::InputInterface& inputStream);

			void addScanMachine(const std::regex& scanMachine, const Tag* tag);
		};
	}
}

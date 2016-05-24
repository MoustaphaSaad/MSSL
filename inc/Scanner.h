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
		struct MSSL_API Tag
		{
			bool isValid;
			std::string name;
			std::function<bool(Input::InputInterface&)> tagFunction;

			Tag();
		};

		MSSL_API Tag* make_tag(std::string name, std::function<bool(Input::InputInterface&)> function = nullptr);

		MSSL_API bool scan_error(std::string input, Input::Position position);

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

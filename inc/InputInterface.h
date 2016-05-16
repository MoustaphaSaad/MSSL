#pragma once

#include "Globals.h"
#include <sstream>

namespace MSSL
{
	namespace Input
	{
		class MSSL_API IInputInterface
		{
		public:
			std::istream& m_stream;

			IInputInterface(std::istream& stream);

		};

		class MSSL_API InputInterface
		{
		protected:
			std::stringstream m_stream;

		public:
			explicit InputInterface(const std::string& text);
			InputInterface();

			void setStream(const std::string& text);

			void push(const std::string& text);

			char peek();
			char consume();

			bool eof();
		};
	}
}
#pragma once

#include "Globals.h"
#include <string>

namespace MSSL
{
	namespace Input
	{
		class MSSL_API InputInterface
		{
		protected:
			std::string m_stream;
			std::size_t m_currentChar;

		public:
			virtual ~InputInterface()
			{
			}

			explicit InputInterface(const std::string& text);
			InputInterface();

			void setStream(const std::string& text);

			void push(const std::string& text);

			char peek();
			char consume();

			bool eof();

			std::string getString() const;

			virtual std::string delimiterCut();
		};
	}
}
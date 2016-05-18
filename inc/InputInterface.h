#pragma once

#include "Globals.h"
#include <string>
#include <functional>

namespace MSSL
{
	namespace Input
	{

		struct MSSL_API Position
		{
		private:
			static Position invalidPosition();

		public:
			std::size_t row, col;
			bool isValid;

			static const Position NO_POSITION;

			Position();
		};

		MSSL_API Position make_position(std::size_t row, std::size_t col);
		MSSL_API bool isDelimiter(char c);

		class MSSL_API InputInterface
		{
		protected:
			std::string m_stream;
			std::size_t m_currentChar;
			Position m_position;
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

			virtual std::string delimiterCut(std::function<bool(char)> isDelimiterFunc = isDelimiter);

			Position getCurrentPosition();
		};
	}
}
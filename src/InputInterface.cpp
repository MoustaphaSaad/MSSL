#include "InputInterface.h"
using namespace MSSL;
using namespace MSSL::Input;

InputInterface::InputInterface(const std::string& text)
	: m_stream(text)
{
	m_currentChar = 0;
}

InputInterface::InputInterface()
{
	m_currentChar = 0;
	m_stream = "";
}

void InputInterface::setStream(const std::string& text)
{
	m_stream = text;
}

void InputInterface::push(const std::string& text)
{
	m_stream += text;
}

char InputInterface::peek()
{
	return m_stream[m_currentChar];
}

char InputInterface::consume()
{
	return m_stream[m_currentChar++];
}

bool InputInterface::eof()
{
	return m_currentChar >= m_stream.size();
}

std::string InputInterface::getString() const
{
	return m_stream;
}

std::string InputInterface::delimiterCut()
{
	std::string cut = "";
	while(!this->eof())
	{
		char c = this->peek();
		if(c == ' ' || c == '\r' || c == '\n' || c == '\t')
		{
			this->consume();
			if (!cut.empty())
				return cut;
		}else
		{
			cut.push_back(c);
			this->consume();
		}
	}

	return cut;
}
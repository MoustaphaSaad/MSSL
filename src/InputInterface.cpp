#include "InputInterface.h"
using namespace MSSL;
using namespace MSSL::Input;

const Position Position::NO_POSITION = Position::invalidPosition();

bool Input::isDelimiter(char c)
{
	if (c == ' ' || c == '\r' || c == '\n' || c == '\t')
		return true;
	return false;
}

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
	m_position.col++;
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

std::string InputInterface::delimiterCut(std::function<bool(char)> isDelimiterFunc)
{
	std::string cut = "";
	while(!this->eof())
	{
		char c = this->peek();
		if(isDelimiterFunc(c))
		{
			//newline
			if(c == '\n')
			{
				m_position.row += 1;
				m_position.col = 0;
			}

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

Position InputInterface::getCurrentPosition()
{
	return m_position;
}

Position Position::invalidPosition()
{
	Position result;
	result.isValid = false;
	return result;
}

Position::Position()
{
	row = 0;
	col = 0;
	isValid = true;
}

Position Input::make_position(std::size_t row, std::size_t col)
{
	Position result;
	result.row = row;
	result.col = col;
	return result;
}
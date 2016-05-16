#include "InputInterface.h"
using namespace MSSL;
using namespace MSSL::Input;

InputInterface::InputInterface( const std::string& text)
	: m_stream(std::stringstream(text))
{
	
}

InputInterface::InputInterface()
{

}

void InputInterface::setStream(const std::string& text)
{
	m_stream = std::stringstream(text);
}

void InputInterface::push(const std::string& text)
{
	auto updated_str = m_stream.str() + text;
	m_stream = std::stringstream(updated_str);
}

char InputInterface::peek()
{
	return m_stream.peek();
}

char InputInterface::consume()
{
	char c;
	m_stream >> c;
	return c;
}

bool InputInterface::eof()
{
	return m_stream.eof();
}

IInputInterface::IInputInterface(std::istream& stream)
	:m_stream(stream)
{

}
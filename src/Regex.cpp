#include "Regex.h"
using namespace MSSL::Automata;

Regex::Regex()
{
	m_currentState = INIT_STATE;
}

Regex::~Regex()
{
	this->INIT_STATE = nullptr;
	this->m_currentState = nullptr;

	for (auto state : this->m_memberStates)
		state = nullptr;
	this->m_memberStates.clear();

	while (!this->m_operandStack.empty())
		this->m_operandStack.pop();

	while (!this->m_operatorStack.empty())
		this->m_operatorStack.pop();

}

ConsumptionState Regex::consume(char c)
{
	auto result = this->m_currentState->consume(c);
	if (result.expired())
		return ConsumptionState::DEADEND;
	else
	{
		if (result.lock()->isAcceptState())
			return ConsumptionState::ACCEPT;
		else
			return ConsumptionState::OK;
	}
	return ConsumptionState::NONE;
}

void Regex::reset()
{
	this->m_currentState = this->INIT_STATE;
}

std::shared_ptr<Regex> Regex::Create(std::string exp)
{
	std::shared_ptr<Regex> result = std::make_shared<Regex>();
	for(auto c : exp)
	{
		
	}
	return result;
}
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
	if (this->m_currentState == nullptr)
		return ConsumptionState::NONE;

	auto result = this->m_currentState->consume(c);
	this->m_currentState = result.lock();

	if (result.expired()) {
		return ConsumptionState::DEADEND;
	}

	if (result.lock()->isAccept)
	{
		return ConsumptionState::ACCEPT;
	}

	return ConsumptionState::OK;
}

void Regex::reset()
{
	this->m_currentState = this->INIT_STATE;
}

std::shared_ptr<Regex> Regex::Create(std::string exp)
{
	std::shared_ptr<Regex> result = std::make_shared<Regex>();
	auto previous_state = result->INIT_STATE;
	for(auto c : exp)
	{
		if(previous_state == nullptr)
		{
			previous_state = std::make_shared<State>();
			result->m_memberStates.insert(previous_state);
			result->INIT_STATE = previous_state;
		}
		auto new_state = std::make_shared<State>();
		result->m_memberStates.insert(new_state);
		previous_state->addTransition(c, new_state);
		previous_state = new_state;
	}
	previous_state->isAccept = true;
	result->reset();
	return result;
}
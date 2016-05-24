#include "State.h"
using namespace MSSL::Automata;

State::State()
{
	this->m_id = -1;
	this->m_accept = false;
}

State::State(int id, bool accept)
{
	this->m_id = id;
	this->m_accept = accept;
}

State::~State()
{
	this->m_transition.clear();
}

void State::addTransition(char input, std::weak_ptr<State> state)
{
	this->m_transition.insert(std::make_pair(input, state));
}

std::weak_ptr<State> State::consume(char c)
{
	auto lower_bound = this->m_transition.lower_bound(c);
	auto upper_bound = this->m_transition.upper_bound(c);

	while(lower_bound != upper_bound)
	{
		return lower_bound->second;
	}
	return std::weak_ptr<State>();
}

bool State::isAcceptState()
{
	return this->m_accept;
}

void State::getTransition(char input, std::vector<std::weak_ptr<State>>& states)
{
	states.clear();
	auto lower_bound = this->m_transition.lower_bound(input);
	auto upper_bound = this->m_transition.upper_bound(input);
	while(lower_bound != upper_bound)
	{
		states.push_back(lower_bound->second);
		++lower_bound;
	}
}
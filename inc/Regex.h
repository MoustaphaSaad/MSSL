#pragma once
#include "Globals.h"
#include "State.h"
#include <set>
#include <stack>

namespace MSSL
{
	namespace Automata {
		enum class ConsumptionState{NONE, ACCEPT, OK, DEADEND};
		class MSSL_API Regex
		{
		protected:
			std::shared_ptr<State> INIT_STATE, m_currentState;

			std::set<std::shared_ptr<State>> m_memberStates;

			std::stack<std::deque<std::weak_ptr<State>>> m_operandStack;
			std::stack<char> m_operatorStack;
		public:
			Regex();
			~Regex();

			ConsumptionState consume(char c);

			void reset();

			static std::shared_ptr<Regex> Create(std::string exp);
		};
	}
}
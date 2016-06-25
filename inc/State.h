#pragma once
#include "Globals.h"
#include <unordered_map>
#include <memory>

namespace MSSL
{
	namespace Automata
	{
		/*
		 * represents a state in a machine
		 * it has a transitions to other states but it doesn't own the states to just weak_ptrs to them
		 * also it can accept arbitrary input as T
		 */
		template<typename T>
		class State
		{
		protected:
			//transitions to other states that accept a T and go to states [a, b, c ...]
			std::unordered_multimap<T, std::weak_ptr<State<T>>> m_transitions;
		public:
			//to indicate if this state is an accept state
			bool isAccept;

			State() 
			{
				this->isAccept = false;
			}

			//accept constructor
			State(bool accept): isAccept(accept)
			{}

			~State() 
			{
				this->m_transitions.clear();
			}
			
			/*
				adds a transition when the input is "input" then there's a transition to state "state"
			*/
			void 
			addTransition(T input, std::weak_ptr<State<T>> state)
			{
				this->m_transitions.insert(std::make_pair(input, state));
			}

			/*
				consumes an input "input" and returns the first state that accepts this input
			*/
			std::weak_ptr<State>
			consume(T input) 
			{
				auto lower_bound = this->m_transitions.lower_bound(input);
				auto upper_bound = this->m_transitions.upper_bound(input);

				while (lower_bound != upper_bound)
				{
					return lower_bound->second;
				}
				return std::weak_ptr<State>();
			}

			/*
				consumes an input "input" and returns all the states that accept this input
			*/
			void
			getTransitions(T input, std::vector<std::weak_ptr<State>> &states)
			{
				states.clear();
				auto lower_bound = this->m_transitions.lower_bound(input);
				auto upper_bound = this->m_transitions.upper_bound(input);
				while (lower_bound != upper_bound)
				{
					states.push_back(lower_bound->second);
					++lower_bound;
				}
			}
		};
	}
}
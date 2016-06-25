#pragma once

#include "Globals.h"
#include "State.h"
#include <stack>
#include <set>
#include <deque>
#include <vector>

namespace MSSL 
{
	namespace Automata
	{
		enum class MachineState {NONE = 0, ACCEPT, OK, DEADEND};

		//template type of the state input typename
		template<typename T>
		class NFA 
		{
		protected:
			//the machine owns it's states so all pointers are shared
			std::shared_ptr<State<T>> START_STATE; //start state of the NFA
			std::vector<std::weak_ptr<State<T>>> m_currentStates; //current states that's active in current moment

			std::set<std::shared_ptr<State<T>>> m_states; //states of the machine
		public:
			using INPUT_TYPE = T;

			NFA() 
			{
				this->START_STATE = nullptr;
			}

			~NFA() 
			{
				this->START_STATE = nullptr;
				this->m_currentStates.clear();
				this->m_states.clear();
			}

			void
			setStartState(std::shared_ptr<State<T>> state)
			{
				this->START_STATE = state;
			}

			std::shared_ptr<State<T>>
			getStartState()
			{
				return START_STATE;
			}

			MachineState
			consume(T input)
			{
				std::vector<std::weak_ptr<State<T>>> newCurrentStates, outStates;

				bool foundTransition = false, foundAcceptState = false;

				//find the next states of this input
				for (auto& state : m_currentStates)
				{
					if (!state.expired())
					{
						state.lock()->getTransitions(input, outStates);
						newCurrentStates.insert(newCurrentStates.end(), outStates.begin(), outStates.end());
						foundTransition = true;
					}
				}
				
				//check if anyone of them has accept state
				for (auto& state : newCurrentStates)
					if (!state.expired() && state.lock()->isAccept)
						foundAcceptState = true;

				//set the new current states
				m_currentStates = newCurrentStates;

				//find proper response
				if (foundTransition && foundAcceptState)
					return MachineState::ACCEPT;
				else if (foundTransition)
					return MachineState::OK;
				else
					return MachineState::DEADEND;
			}

			void
			addState(std::shared_ptr<State<T>> state)
			{
				m_states.insert(state);
			}

			//resets the state of the NFA REMEMBER TO RESET BEFORE STARTING IT
			void
			reset()
			{
				m_currentStates.clear();
				m_currentStates.push_back(START_STATE);
			}
		};
	}
}
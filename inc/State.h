#pragma once
#include "Globals.h"
#include <unordered_map>
#include <memory>

namespace MSSL
{
	namespace Automata
	{
		class MSSL_API State
		{
		protected:
			std::unordered_multimap<char, std::weak_ptr<State>> m_transition;
		public:

			bool isAccept;

			State();
			State(bool accept);

			~State();
			
			void addTransition(char input, std::weak_ptr<State> state);

			std::weak_ptr<State> consume(char c);

			void getTransition(char input, std::vector<std::weak_ptr<State>> &states);
		};
	}
}
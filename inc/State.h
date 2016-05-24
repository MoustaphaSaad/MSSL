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

			int m_id;
			bool m_accept;

		public:
			State();
			State(int id, bool accept);

			~State();
			
			void addTransition(char input, std::weak_ptr<State> state);

			std::weak_ptr<State> consume(char c);

			bool isAcceptState();

			void getTransition(char input, std::vector<std::weak_ptr<State>> &states);
		};
	}
}
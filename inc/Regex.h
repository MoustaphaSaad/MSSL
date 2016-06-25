#pragma once

#include "Globals.h"
#include "NFA.h"

namespace MSSL
{
	template<typename FSM = Automata::NFA<char>>
	class MSSL_API Regex {
	protected:
		FSM m_fsm;

	public:

		Regex();

		setFSM(FSM fsm);

		Automata::MachineState consume(typename FSM::INPUT_TYPE input);


	};
}
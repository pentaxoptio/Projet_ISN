#include "State.h"
#include "StateStack.h"

State::State(StateStack &stack, Context context) :
	m_stack(&stack)
	, m_context(context)
{
	
}

State::~State()
{

}

//protected :

void State::requestStackPush(StateId id)
{
	m_stack->pushState(id);
}

void State::requestStackPop()
{
	m_stack->popState();
}

void State::requestStackClear()
{
	m_stack->clearStates();
}

Context State::getContext() const
{
	return m_context;
}

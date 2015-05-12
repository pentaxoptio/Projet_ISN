#include "StateStack.h"

#include <exception>

StateStack::StateStack(Context context) :
	m_globalSettings({Normal, 0, 0}) ,
	m_stack() ,
	m_changes() ,
	m_context(context) ,
	m_stateMakers()
{
	
}

StateStack::~StateStack()
{
	for (State* state : m_stack)
		delete state;
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = m_stack.rbegin(); itr < m_stack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
			break;
	}
	applyChanges();
}

void StateStack::handleEvent(sf::Event const& event)
{
	for (auto itr = m_stack.rbegin(); itr < m_stack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
			break;
	}
	applyChanges();
}

void StateStack::render()
{
	for (State* state : m_stack)
		state->render();
}

void StateStack::pushState(StateId id)
{
	m_changes.push_back(Change(Push, id));
}

void StateStack::popState()
{
	m_changes.push_back(Change(Pop));
}

void StateStack::clearStates()
{
	m_changes.push_back(Change(Clear));
}

bool StateStack::isEmpty() const
{
	return m_stack.empty();
}

GlobalSettings StateStack::getGlobalSettings() const
{
	return m_globalSettings;
}

GlobalSettings& StateStack::accessGlobalSettings()
{
	return m_globalSettings;
}

//Private : -----------------------------

StateStack::Change::Change(Action act, StateId sId) :
	action(act)
	, id(sId)
{
	
}

State* StateStack::createState(StateId id)
{
	//std::map<StateId, std::function<State*()>>::iterator
	auto found = m_stateMakers.find(id);
	if (found == m_stateMakers.end())
		throw std::logic_error("StateStack::createState(StateId id) : ERROR : state not found (not registered ?)");

	return found->second();
}

void StateStack::applyChanges()
{
	for (Change change : m_changes)
	{
		switch (change.action)
		{
			case Push :
				m_stack.push_back(createState(change.id));
				break;
			case Pop :
				delete m_stack[m_stack.size()-1];
				m_stack.pop_back();
				break;
			case Clear :
				for (State* state : m_stack)
					delete state;
				m_stack.clear();
				break;
		}
	}

	m_changes.clear();
}

#ifndef STATESTACK_H
#define STATESTACK_H 

#include <vector>
#include <map>
#include <functional>

#include "State.h"
#include "Utils.h"

class StateStack
{
	public :
		enum Action
		{
			Push,
			Pop,
			Clear
		};

	public :
		explicit StateStack(Context context);
		~StateStack();

		template<typename T>
		void registerState(StateId stateId);

		void update(sf::Time dt);
		void render();
		void handleEvent(sf::Event const& event);

		void pushState(StateId id);
		void popState();
		void clearStates();

		bool isEmpty() const;
		GlobalSettings getGlobalSettings() const;
		GlobalSettings& accessGlobalSettings();

	private :
		struct Change
		{
			explicit Change(Action action, StateId id = NoState);
			Action action;
			StateId id;
		};

	private :
		State* createState(StateId id);
		void applyChanges();

	private :
		GlobalSettings m_globalSettings;
		std::vector<State*> m_stack;
		std::vector<Change> m_changes;
		Context m_context;
		std::map<StateId, std::function<State*()>> m_stateMakers;
};

//Comme c'est une fonction <template> on est obligée de la définir dans le .h
template<typename T>
void StateStack::registerState(StateId id)
{
	m_stateMakers[id] = [this] ()
	{
		return new T(*this, m_context);
	};
}

#endif

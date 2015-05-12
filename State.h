#ifndef STATE_H
#define STATE_H 

#include <SFML/Graphics.hpp>

#include "Utils.h"

class StateStack;

enum StateId
{
	Opening,
	MainMenu,
	PlayMenu,
	Game,
	Win,
	NoState
};

class State
{
	public :
		State(StateStack& stack, Context context);
		virtual ~State();
		
		virtual void render() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(sf::Event const &event) = 0;

	protected :
		void requestStackPush(StateId id);
		void requestStackPop();
		void requestStackClear();

		Context getContext() const;
		GlobalSettings getGlobalSettings() const;
		GlobalSettings& accessGlobalSettings();

	private :
		StateStack* m_stack;
		Context m_context;
};

#endif

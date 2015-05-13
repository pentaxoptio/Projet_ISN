#ifndef STATE_H
#define STATE_H 

#include <SFML/Graphics.hpp>

#include "Utils.h"

class StateStack;

//Cet enum permet de caractériser chaque State et sont nécessaires pour le StateStack (cf. StateStack.h)
enum StateId
{
	Opening,
	MainMenu,
	PlayMenu,
	Game,
	Win,
	NoState
};

//Classe State
//* Cette classe représente un State, un "état" du jeu qui peut être par exemple un menu ou le jeu en lui-même. Il s'agit d'une réplique de l'App (en effet, on retrouve les 3 fonctions principales) encapsulée dans le StateStack.
class State
{
	public :
		//Cette classe prend en paramètre de son constructeur une référence vers le stack car elle a parfois besoin de faire des appels comme "requestStackPop()" ou "getGlobalSettings()".
		State(StateStack& stack, Context context);
		virtual ~State();
		
		//Les 3 fonctions principales. Notez que update et handleEvents revoie un booléen. En effet, si le State revoie false, alors la fonction (update ou handleEvent) ne sera pas transmise aux State inférieurs. C'est le cas par exemple en cas de victoire, la State "WinState" est affichée en transparence au dessus de GameState, alors qu'il est impossible d'interragir avec le jeu.
		virtual void render() = 0;
		virtual bool update(sf::Time dt) = 0;
		virtual bool handleEvent(sf::Event const &event) = 0;

	protected :
		//Toutes ces fonctions "protected" permettent d'accèder au StateStack et à le modifier.
		void requestStackPush(StateId id);
		void requestStackPop();
		void requestStackClear();

		Context getContext() const;
		GlobalSettings getGlobalSettings() const;
		GlobalSettings& accessGlobalSettings();

	private :
		//Pointeur vers le stack
		StateStack* m_stack;
		//Le contexte  (cf. Utils.h)
		Context m_context;
};

#endif

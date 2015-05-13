#ifndef STATESTACK_H
#define STATESTACK_H 

#include <vector>
#include <map>
#include <functional>

#include "State.h"
#include "Utils.h"

//Classe StateStack
//* Cette classe représente une pile de State, soit des "états" du jeu différents. On compte par exemple les MenuStates qui représentent des menus ou le GameState qui symbolise le jeu en lui-même.
class StateStack
{
	public :
		//Cet enum représente différentes actions possibles du StateStack. En effet, il n'applique les changements qu'après avoir mis à jour et traité les évènements, il doti donc stocker temporairement les actions en cours.
		enum Action
		{
			Push,
			Pop,
			Clear
		};

	public :
		//Le StateStack prend en paramètre le Context, qui sera nécessaire aux States pour utiliser des Textures et des polices.
		explicit StateStack(Context context);
		//Le StateStack doit détruire les States qui sont alloués dynamiquement pour éviter des fuites de mémoire. On a donc un destructeur.
		~StateStack();

		//Cette fonction template doit pouvoir prendre en charge n'importe quel type de State, il faut donc une fonction générique. Elle créée une fonction qui construira, au moment du Push, le State indiqué dans le template.
		template<typename T>
		void registerState(StateId stateId);

		//Les trois fonctions principales. Update et handleEvent ont la particularité de ne pas être forcément appliquées à tous les States actifs : en effet, chaque State peut décider de "bloquer" l'update ou les évènements aux States inférieurs dans la Pile. (cf. State.h)
		void update(sf::Time dt);
		void render();
		void handleEvent(sf::Event const& event);

		//Ces trois fonctions ne font qu'ajouter à la liste des changements en cours les actions correspondantes.
		void pushState(StateId id);
		void popState();
		void clearStates();

		//Renvoie true si il n'y a aucun State actif
		bool isEmpty() const;
		//Ces deux fonctions permettent de donner accès pour les States aux GlobalSettings et ainsi s'échanger des informations. La première fonction est un accès en lecture seule alors que la seconde autorise la modification.
		GlobalSettings getGlobalSettings() const;
		GlobalSettings& accessGlobalSettings();

	private :
		//Cette structure représente un changement. Il s'agit tout simplement de l'association d'une action (Push, Pop, Clear) et de l'id d'un State. Notez que l'id du State ne sert que pour Push...
		struct Change
		{
			explicit Change(Action action, StateId id = NoState);
			Action action;
			StateId id;
		};

	private :
		//Cette fonction est appelée lorsqu'on a besoin de créer un State : elle va cherche dans la liste des fonctions créatrices celle qui correspond au StateId demandé pour créer un pointeur sur le State.
		State* createState(StateId id);
		//Cette fonction applique tous les changements en cours dans l'ordre demandé.
		void applyChanges();

	private :
		//Les paramètres globaux accessibles à tous les States (cf. Utils.h)
		GlobalSettings m_globalSettings;
		//La pile de State actifs
		std::vector<State*> m_stack;
		//La liste des changements pas encore effectués
		std::vector<Change> m_changes;
		//Le contexte (cf. Utils.h)
		Context m_context;
		//La liste des fonctions créatrices en association avec l'id du State concerné.
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

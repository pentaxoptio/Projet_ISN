#ifndef PLAYMENUSTATE_H
#define PLAYMENUSTATE_H 

#include "State.h"
#include "Gui.h"
#include "Button.h"
#include "Label.h"
#include "Utils.h"
 
//Classe PlayMenuState
//* Ce State est un menu intermédiaire entre le menu principal et le jeu; il demande au joueur la difficulté voulue
class PlayMenuState : public State
{
	public :
		//Ce constructeur initialise les boutons, notamment le bouton qui change la difficulté. Il contient une fonction qui le modifie lui-même. Lorsqu'on appuie sur Play, le State appelle "accessGlobalSettings" pour changer la difficulté
		PlayMenuState(StateStack &stack, Context context);

		//Les fonctions héritées de State
		virtual bool handleEvent(sf::Event const& event);
		virtual bool update(sf::Time dt);
		virtual void render();

	private :
		sf::Sprite m_bg;
		gui::Container m_container;
		//On conserve un pointeur vers le bouton (normalement on le laisse au Container) pour pouvoir modifier son texte
		gui::Button* m_difficultyButton;
		//La difficulté choisie
		Difficulty m_difficulty;
};

#endif

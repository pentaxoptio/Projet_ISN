#ifndef APP_H
#define APP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "StateStack.h"
#include "GameState.h"
#include "MainMenuState.h"
#include "PlayMenuState.h"
#include "OpeningState.h"
#include "WinState.h"

#include "Textures.h"
#include "Fonts.h"

//Classe App
//* cette classe est la classe principale du jeu : elle possède la fenêtre ainsi que le StateStack et le gestionnaire de ressources. C'est elle qui fait la boucle principale.
class App
{
    public :
        App();
		//La méthode run est celel qui contient la boucle principale : à chaque tour de boucle, elle récupère le temps écoulé depuis la dernière boucle (en sf::Time) et le passe en paramètre de update(). Elle appelle également les fonctions handleEvents() et en dernier, render(). Elle tourne tant que la fenêtre est ouverte.
        void run();

    private :
		//La méthode handleEvents récupère les évènements depuis la fenêtre grâce à pollEvent(sf::Event). Elle traite ensuite deux évènements : le redimensionnement et la fermeture. Si ce n'est pas un de ces cas-là, elle délègue au StateStack.
        void handleEvents();
		//update permet de transmettre le temps écoulé depuis la dernière boucle au StateStack. C'est utile dans certains case, comme par exemple pour le DungeonRenderer qui réalise une animation qui se répète à durée fixe.
        void update(sf::Time dt);
		//render efface le contenu de la fenêtre et le redessine, puis la mets à jour.
        void render();

		//registerStates regroupe tous les appels à la fonction StateStack::registerState<State>(StateId) pour des raisons de lisibilité. 
		void registerStates();
		//De même, registerTextures regroupe tous les appels aux fonctions TextureHolder::registerTexture(TextureId, std::string) et TextureHolder::registerRect(RectId, sf::IntRect).
		void registerTextures();

    private :
		//La fenêtre SFML qui permet de dessiner mais aussi de récupérer les évènements.
        sf::RenderWindow m_w;
		//Le gestionnaire de textures permet de... gérer les textures !
        TextureHolder m_textures;
		//Le gestionnaire de polices... qu'ajouter ?
		FontHolder m_fonts;
		//Le StateStack, ou la pile de States. cf. StateStack.h
		StateStack m_stack;
        //La musique jouée
        sf::Music m_music;
};

#endif

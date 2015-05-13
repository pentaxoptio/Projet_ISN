#ifndef GUI_H
#define GUI_H 

#include <SFML/Graphics.hpp>
#include <exception>

//Ici est défini ce qui a un rapport avec les interfaces graphiques
namespace gui
{
	//Classe Component
	//* Cette classe représente un composant d'interface graphique. Sa principale particularité est d'avoir deux états : selectionné et activé. Il possède différentes fonctions permettant d'agir sur ces états.
	//* Les composants comme les boutons héritent de cette classe
	class Component : public sf::Drawable, public sf::Transformable
	{
		public :
			Component();

			//Les fonctions qui suivent permettre d'agir sur les deux états possibles du composant.
			virtual bool isSelectable() const = 0;
			bool isSelected() const;
			virtual void select();
			virtual void deselect();
			virtual bool isActive() const;
			virtual void activate();
			virtual void deactivate();
			//Le composant peut également gérer des évènements
			virtual void handleEvent(sf::Event const &event) = 0;
			virtual sf::Vector2f getSize() const = 0;

		private :
			bool m_selected;
			bool m_activate;
	};

	//Classe Container
	//* Le Container est un élément important de l'interface graphique car il permet de regrouper et de faire fonctionner plusieurs Component. C'est lui qui va les sélectionner et les activer selon ce que l'utilisateur fait.
	class Container : public Component
	{
		public :
			Container();
			//Le Container contient des pointeurs vers les Component et se charge de les détruire.
			virtual ~Container();

			//Il hérite de la classe Component et doit donc redéfinir ces méthodes pour être instanciable
			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			virtual sf::Vector2f getSize() const;

			//La méthode pack permet au Container d'enregister le Component. Il pourra alors le sélectionner et l'activer.
			void pack(Component* child);
			//Cette méthode renvoie true si un des composants du Container est selectionné.
			bool hasSelection() const;
			Component const& getSelection();
			void deselectAll();

		private :
			void selectChild(int childId);
			//Cette fonction permet d'activer le composant selectionné.
			void activateSelectedChild();

		private :
			//La liste des "enfants" du container, soit les différents Component dont il a la charge.
			std::vector<Component*> m_children;
			//L'index du composant selectionné dans le tableau des Component.
			int m_selectedChild;
	};

	//Cette exception est lancée quand on tente d'activer un Composant alors qu'aucun n'est selectionné.
	class NoChildSelectedException : public std::exception
	{
		
	};
}

#endif

#ifndef GUI_H
#define GUI_H 

#include <SFML/Graphics.hpp>
#include <exception>

namespace gui
{
	class Component : public sf::Drawable, public sf::Transformable
	{
		public :
			Component();

			virtual bool isSelectable() const = 0;
			bool isSelected() const;
			virtual void select();
			virtual void deselect();
			virtual bool isActive() const;
			virtual void activate();
			virtual void deactivate();
			virtual void handleEvent(sf::Event const &event) = 0;
			virtual sf::Vector2f getSize() const = 0;

		private :
			bool m_selected;
			bool m_activate;
	};

	class Container : public Component
	{
		public :
			Container();
			virtual ~Container();

			virtual bool isSelectable() const;
			virtual void handleEvent(sf::Event const &event);
			virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
			virtual sf::Vector2f getSize() const;

			void pack(Component* child);
			bool hasSelection() const;
			Component const& getSelection();
			void deselectAll();

		private :
			void selectChild(int childId);
			void activateSelectedChild();

		private :
			std::vector<Component*> m_children;
			int m_selectedChild;
	};

	class NoChildSelectedException : public std::exception
	{
		
	};
}

#endif

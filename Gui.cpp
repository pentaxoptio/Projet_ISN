#include "Gui.h"
#include <iostream>

using namespace gui;

Component::Component() :
	m_selected(false) ,
	m_activate(false)
{
	std::cout << "construction component" << std::endl;
}

bool Component::isSelected() const
{
	return m_selected;
}

void Component::select()
{
	if (isSelectable())
		m_selected = true;
}

void Component::deselect()
{
	m_selected = false;
}

bool Component::isActive() const
{
	return m_activate;
}

void Component::activate()
{
	m_activate = true;
}

void Component::deactivate()
{
	m_activate = false;
}

///////////////
// Container //
///////////////

Container::Container() :
	m_children()
	, m_selectedChild(-1)
{
	std::cout << "construction container" << std::endl;
}

Container::~Container()
{
	for (Component* child : m_children)
		delete child;
}

bool Container::isSelectable() const
{
	return false;
}

void Container::handleEvent(sf::Event const& event)
{
	if (hasSelection() && m_children[m_selectedChild]->isActive())
	{
		//Propriété #1 : Si un enfant est actif, il récupère alors la gestion des évènements
		m_children[m_selectedChild]->handleEvent(event);
	}
	else if (event.type == sf::Event::MouseMoved)
	{
		bool found = false;
		sf::FloatRect childBox;
		for (unsigned int i(0); i < m_children.size(); ++i)
		{
			childBox.left = m_children[i]->getPosition().x;
			childBox.top = m_children[i]->getPosition().y;
			childBox.width = m_children[i]->getSize().x;
			childBox.height = m_children[i]->getSize().y;
			if (childBox.contains((float)event.mouseMove.x, (float)event.mouseMove.y))
			{
				//La souris est dans ce child
				selectChild(i);
				found = true;
			}

			if (found == false && hasSelection())
				m_children[m_selectedChild]->deselect();
		}
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (hasSelection())
		{
			activateSelectedChild();
		}
	}
}

void Container::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	for (Component* child : m_children)
	{
		target.draw(*child, states);
	}
}

sf::Vector2f Container::getSize() const
{
	if (m_children.size() > 0)
	{
		sf::FloatRect box;
		box.left = m_children[0]->getPosition().x;
		box.top = m_children[0]->getPosition().y;
		box.width = m_children[0]->getSize().x;
		box.height = m_children[0]->getSize().y;
		for (Component* child : m_children)
		{
			if (child->getPosition().x < box.left)
				box.left = child->getPosition().x;
			if (child->getPosition().y < box.top)
				box.top = child->getPosition().y;
			if (child->getPosition().x + child->getSize().x > box.left + box.width)
				box.width = child->getPosition().x + child->getSize().x - box.left;
			if (child->getPosition().y + child->getSize().y > box.left + box.height)
				box.height = child->getPosition().y + child->getSize().y - box.top;
		}
		return sf::Vector2f(box.width, box.height);
	}
	
	return sf::Vector2f(0.f, 0.f);
}

void Container::pack(Component* child)
{
	m_children.push_back(child);
}

bool Container::hasSelection() const
{
	return m_selectedChild >= 0;
}

Component const& Container::getSelection()
{
	std::cout << "get selection" << std::endl;
	if (hasSelection())
		return *m_children[m_selectedChild];
	else
		throw NoChildSelectedException();
}

void Container::deselectAll()
{
	for (Component* child : m_children)
	{
		child->deselect();
		m_selectedChild = -1;
	}
}

void Container::selectChild(int childId)
{
	if (m_children[childId]->isSelectable())
	{
		if (hasSelection())
			m_children[m_selectedChild]->deselect();
		m_children[childId]->select();
		m_selectedChild = childId;
	}
}

void Container::activateSelectedChild()
{
	m_children[m_selectedChild]->activate();
}

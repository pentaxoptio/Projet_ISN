#include "Textures.h"

TextureHolder::TextureHolder() :
    m_textures()
{

}

TextureHolder::~TextureHolder()
{
    for (std::pair<TextureId, sf::Texture*> pair : m_textures)
        delete pair.second;
}

void TextureHolder::registerTexture(TextureId id, std::string filename)
{
    sf::Texture* newTexture = new sf::Texture;
    newTexture->loadFromFile(filename);
    m_textures.insert(std::make_pair(id, newTexture));
}

sf::Texture const& TextureHolder::getTexture(TextureId id) const
{
    return *m_textures.at(id);
}

void TextureHolder::registerRect(RectId id, sf::IntRect rect)
{
    m_rects.insert(std::make_pair(id, rect));
}

sf::IntRect TextureHolder::getRect(RectId id) const
{
    return m_rects.at(id);
}


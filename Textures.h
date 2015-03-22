#ifndef TEXTURES_H
#define TEXTURES_H

#include <string>
#include <SFML/Graphics.hpp>

enum TextureId
{
    Tiles,
    Player,
    Effects
};

enum RectId
{
    Wall,
    Air,
    Stairs,
    RedEffect,
    BlueEffect
};

class TextureHolder
{
    public :
        TextureHolder();
        ~TextureHolder();
        void registerTexture(TextureId id, std::string filename);
        sf::Texture const& getTexture(TextureId id);
        void registerRect(RectId id, sf::IntRect rect);
        sf::IntRect getRect(RectId id);

    private :
        std::map<TextureId, sf::Texture*> m_textures;
        std::map<RectId, sf::IntRect> m_rects;
};

#endif

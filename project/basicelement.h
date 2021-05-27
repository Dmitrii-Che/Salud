#ifndef BASICELEMENT_H
#define BASICELEMENT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class BasicElement
{
public:
    BasicElement();
    explicit BasicElement(
        const Texture &texture, float x = 0.f, float y = 0.f, float w = 1.f, float h = 1.f);
    BasicElement(const BasicElement &Other);
    virtual ~BasicElement();
    void setTexture(const Texture &texture, float w, float h);
    void setTexture(const std::string &filename, float w, float h);
    void setSize(float w, float h);
    void setSprite(const Sprite &sprite);
    void setRect(float x = 0.f, float y = 0.f, float w = 1.f, float h = 1.f);
    void setRect(const FloatRect &rect);
    void setRectSize(float w, float h);
    void setPosition(float x, float y);
    void setColor(const Color &color);

    Color &getColor();

    FloatRect &getRect();

    virtual void update();
    virtual void update(const float &time);
    virtual void draw(RenderWindow *pWindow) const;

protected:
    FloatRect _rect;
    Texture _texture;
    Sprite _sprite;
    Color _color;
    float _textureSizeX, _textureSizeY;
};

#endif // BASICELEMENT_H

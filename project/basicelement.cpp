#include "basicelement.h"
#include <qdebug.h>

BasicElement::BasicElement()
{
    _textureSizeX = 1;
    _textureSizeY = 1;
}

BasicElement::BasicElement(const Texture &texture, float x, float y, float w, float h)
{
    _textureSizeX = 1;
    _textureSizeY = 1;
    _sprite.setTexture(texture);
    setRect(x, y, w, h);
}

BasicElement::~BasicElement() {}

void BasicElement::setTexture(const Texture &texture, float w, float h)
{
    _texture = texture;
    Vector2u size = _texture.getSize();
    float scaleX = w / size.x;
    float scaleY = h / size.y;
    _sprite.setTexture(_texture);
    _sprite.scale(scaleX, scaleY);
    setRectSize(w, h);
}

void BasicElement::setTexture(const std::string &filename, float w, float h)
{
    _texture.loadFromFile(filename);
    _textureSizeX = _texture.getSize().x;
    _textureSizeY = _texture.getSize().y;
    setSize(w, h);
}

void BasicElement::setSize(float w, float h)
{
    float scaleX = (w / _textureSizeX) / _sprite.getScale().x;
    float scaleY = (h / _textureSizeY) / _sprite.getScale().y;

    _sprite.setTexture(_texture);
    _sprite.scale(scaleX, scaleY);
    setRectSize(w, h);
}

void BasicElement::setSprite(const Sprite &sprite)
{
    _sprite = sprite;
}

void BasicElement::setRect(float x, float y, float w, float h)
{
    setRectSize(w, h);
    setPosition(x, y);
}

void BasicElement::setRect(const FloatRect &rect)
{
    setPosition(rect.left, rect.top);
    setRectSize(rect.width, rect.height);
}

void BasicElement::setRectSize(float w, float h)
{
    _rect.width = w;
    _rect.height = h;
}

void BasicElement::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
    _rect.left = x;
    _rect.top = y;
}

void BasicElement::setColor(const Color &color)
{
    _color = color;
    _sprite.setColor(_color);
}

Color &BasicElement::getColor()
{
    return _color;
}

FloatRect &BasicElement::getRect()
{
    return _rect;
}

void BasicElement::update() {}

void BasicElement::update(const float &time) {}

BasicElement::BasicElement(const BasicElement &Other)
    : _texture(Other._texture), _sprite(Other._sprite), _color(Other._color)
{
    _textureSizeX = Other._textureSizeX;
    _textureSizeY = Other._textureSizeY;
}

void BasicElement::draw(RenderWindow *pWindow) const
{
    pWindow->draw(_sprite);
}

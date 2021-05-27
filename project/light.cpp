#include "light.h"

Light::Light()
{
    _vX = 0.1f;
    _vY = 0.1f;
    _aX = 0.1f;
    _aY = 0.1f;
    _lifeTime = 200;
    _alfa = 255;
}

Light::~Light() {}

Light::Light(float vX, float vY, float aX, float aY, unsigned lifeTime)
{
    if (vX == 0.f) {
        vX = 0.1f;
    }

    if (vY == 0.f) {
        vY = 0.1f;
    }
    _vX = vX;
    _vY = vY;
    _aX = aX;
    _aY = aY;
    _lifeTime = lifeTime;
    _alfa = 255;
}

void Light::setVelocity(float vX, float vY)
{
    _vX = vX;
    _vY = vY;
}

Vector2<float> Light::getVelocity() const
{
    return Vector2<float>(_vX, _vY);
}

void Light::setAcceleration(float aX, float aY)
{
    _aX = aX;
    _aY = aY;
}

Vector2<float> Light::getAcceleration() const
{
    return Vector2<float>(_aX, _aY);
}

void Light::setLifeTime(unsigned lifeTime)
{
    _lifeTime = lifeTime;
}

unsigned Light::getLifeTime() const
{
    return _lifeTime;
}

bool Light::setAlfa(unsigned alfa)
{
    bool mark = false;
    if (alfa <= 255) {
        _alfa = alfa;
        _color.a = _alfa;
        setColor(_color);
        mark = true;
    }
    return mark;
}

unsigned Light::getAlfa() const
{
    return _alfa;
}

bool Light::modifyAlfa(int value)
{
    bool mark = false;
    _alfa += value;
    if (_alfa <= 255) {
        _color.a = _alfa;
        mark = true;
        setColor(_color);
    } else {
        _alfa -= value;
    }
    return mark;
}

Light::Light(const Light &Other) : BasicElement(Other)
{
    _vX = Other._vX;
    _vY = Other._vY;
    _aX = Other._aX;
    _aY = Other._aY;
    _lifeTime = Other._lifeTime;
    _alfa = Other._alfa;
}

void Light::update(const float &time)
{
    float x = getRect().left;
    float y = getRect().top;
    float vX = getVelocity().x;
    float vY = getVelocity().y;
    float aY = getAcceleration().y;

    setPosition(x + vX * time, y + vY * time);
    setVelocity(vX, vY + aY);
    modifyAlfa(-1);
}

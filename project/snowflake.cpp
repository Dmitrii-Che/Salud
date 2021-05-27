#include "snowflake.h"

Snowflake::Snowflake()
{
    _vX = 1.f;
    _vY = 1.f;
    _timer = 0.f;
    _startX = 1.f;
}

Snowflake::~Snowflake() {}

void Snowflake::update(const float &time)
{
    float x = getRect().left;
    float y = getRect().top;
    float vX = _vX;
    float vY = _vY;

    setPosition(x + vX * time, y + vY * time);

    _timer += time;
    if (_timer > 500.f) {
        _vX *= -1;
        _timer = 0.f;
    }
}

void Snowflake::setVelocity(float vX, float vY)
{
    _vX = vX;
    _vY = vY;
}

bool Snowflake::checkForheight(float H)
{
    return getRect().top > H;
}

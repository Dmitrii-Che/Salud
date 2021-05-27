#ifndef LIGHT_H
#define LIGHT_H

#include "basicelement.h"

class Light : public BasicElement
{
public:
    Light();
    explicit Light(float vX, float vY, float aX, float aY, unsigned lifeTime);
    ~Light();
    void setVelocity(float vX, float vY);
    Vector2<float> getVelocity() const;
    void setAcceleration(float aX, float aY);
    Vector2<float> getAcceleration() const;
    void setLifeTime(unsigned lifeTime);
    unsigned getLifeTime() const;
    bool setAlfa(unsigned alfa);
    unsigned getAlfa() const;
    bool modifyAlfa(int value);

    Light(const Light &Other);

protected:
    float _vX;
    float _vY;
    float _aX;
    float _aY;
    unsigned _lifeTime;
    unsigned _alfa;

    // BasicElement interface
public:
    void update(const float &time);
};

#endif // LIGHT_H

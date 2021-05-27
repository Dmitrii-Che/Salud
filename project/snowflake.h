#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include "basicelement.h"
#include <chrono>

class Snowflake : public BasicElement
{
public:
    Snowflake();
    ~Snowflake();
    void update(const float &time) override;
    void setVelocity(float vX, float vY);
    bool checkForheight(float H);

protected:
    time_t *_ptt = nullptr;
    float _vX;
    float _vY;
    float _timer;
    float _startX;
};

#endif // SNOWFLAKE_H

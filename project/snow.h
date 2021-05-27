#ifndef SNOW_H
#define SNOW_H

#include "snowflake.h"
#include <QSharedPointer>

class Snow
{
public:
    Snow();
    explicit Snow(const std::string &filename);
    ~Snow();
    void setTexture(const std::string &filename);
    void makeSnow(int Number);
    void updateSnow(const float &time);
    void drawSnow(RenderWindow *pWindow) const;
    void setBorders(unsigned windW, unsigned windH);
    void clearAll();

protected:
    unsigned _windW;
    unsigned _windH;
    QVector<QSharedPointer<Snowflake>> _vpSnowflakes;
    Texture _texture;
};

#endif // SNOW_H

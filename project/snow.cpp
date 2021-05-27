#include "snow.h"

Snow::Snow()
{
    _windW = 100;
    _windH = 100;
}

Snow::Snow(const std::string &filename)
{
    _windW = 100;
    _windH = 100;
    setTexture(filename);
}

Snow::~Snow()
{
    clearAll();
}

void Snow::setTexture(const std::string &filename)
{
    _texture.loadFromFile(filename);
}

void Snow::makeSnow(int Number)
{
    _vpSnowflakes.clear();

    for (int i = 0; i < Number; i++) {
        QSharedPointer<Snowflake> snowflake(new Snowflake());
        _vpSnowflakes.append(snowflake);
    }

    for (const auto &snowflake : _vpSnowflakes) {
        int tempXPosition = (rand() % _windW);
        int tempYPosition = -(rand() % _windH);
        float vX = ((rand() % 100) - 50) * 0.0001;
        float vY = ((rand() % 100) + 10) * 0.0002;
        snowflake->setVelocity(vX, vY);
        snowflake->setPosition(tempXPosition, tempYPosition);
        snowflake->setTexture(_texture, 10, 10);
    }
}

void Snow::updateSnow(const float &time)
{
    for (const auto &snowflake : _vpSnowflakes) {
        snowflake->update(time);
        if (snowflake->checkForheight(_windH)) {
            int tempXPosition = (rand() % _windW);
            float vX = ((rand() % 100) - 50) * 0.0001;
            float vY = ((rand() % 100) + 10) * 0.0002;
            snowflake->setVelocity(vX, vY);
            snowflake->setPosition(tempXPosition, 0);
        }
    }
}

void Snow::drawSnow(RenderWindow *pWindow) const
{
    for (const auto &snowflake : _vpSnowflakes) {
        snowflake->draw(pWindow);
    }
}

void Snow::setBorders(unsigned windW, unsigned windH)
{
    _windW = windW;
    _windH = windH;
}

void Snow::clearAll()
{
    _vpSnowflakes.clear();
    _vpSnowflakes.shrink_to_fit();
}

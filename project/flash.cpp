#include "flash.h"
#include <cmath>
#include <qdebug.h>

Flash::Flash(const QMap<std::string, Color> &map_Colors)
    : _map_Colors(map_Colors), _color({Color::White}), _lColors(map_Colors.keys()),
      _lightSize({10, 10})
{
    _mapColorsSize = 0;
    _flashLifeTimeMs = 200;
    _vXcoef = 0;
    _vYcoef = 0;
    _aYcoef = 0;
    _mapColorsSize = _lColors.size();
    _ptt = new time_t(std::chrono::system_clock::now().time_since_epoch().count());
    srand(time(_ptt));
}

Flash::Flash(const Flash &Other)
{
    if (_ptt != nullptr) {
        delete _ptt;
    }

    _ptt = new time_t(std::chrono::system_clock::now().time_since_epoch().count());
    srand(time(_ptt));
    _map_Colors = Other._map_Colors;
    _texture = Other._texture;
    _color = Other._color;
    _vLights = Other._vLights;
    _mapColorsSize = Other._mapColorsSize;
    _flashLifeTimeMs = Other._flashLifeTimeMs;
    _vXcoef = Other._vXcoef;
    _vYcoef = Other._vYcoef;
    _aYcoef = Other._aYcoef;
    _lColors = Other._lColors;
    _lightSize = Other._lightSize;
    _autoNumber = Other._autoNumber;
    _autoColor = Other._autoColor;
}

Flash &Flash::operator=(const Flash &Other)
{
    if (&Other != this) {
        if (_ptt != nullptr) {
            delete _ptt;
        }
        _ptt = new time_t(std::chrono::system_clock::now().time_since_epoch().count());
        srand(time(_ptt));
        _map_Colors = Other._map_Colors;
        _texture = Other._texture;
        _color = Other._color;
        _vLights = Other._vLights;
        _mapColorsSize = Other._mapColorsSize;
        _flashLifeTimeMs = Other._flashLifeTimeMs;
        _vXcoef = Other._vXcoef;
        _vYcoef = Other._vYcoef;
        _aYcoef = Other._aYcoef;
        _lColors = Other._lColors;
        _lightSize = Other._lightSize;
        _autoNumber = Other._autoNumber;
        _autoColor = Other._autoColor;
    }

    return *this;
}

Flash::~Flash()
{
    clearAll();
    delete _ptt;
}

void Flash::setTexture(const std::string &filename)
{
    _texture.loadFromFile(filename);
}

void Flash::setMoveCoefs(unsigned vXcoef, unsigned vYcoef, unsigned aYcoef)
{
    _vXcoef = vXcoef;
    _vYcoef = vYcoef;
    _aYcoef = aYcoef;
}

int Flash::makeFlash(int x, int y, int maxN, int minN)
{
    int lightNumber = maxN;
    if ((maxN > minN) && _autoNumber) {
        lightNumber = (rand() % (maxN - minN)) + minN;
    }

    int temp = rand() % _mapColorsSize;

    for (int i = 0; i < lightNumber; i++) {
        int alfa = rand() % 360;
        float tempV = 0.01 * ((rand() % 3) - 3);
        QSharedPointer<Light> light(new Light(static_cast<float>(sin(alfa)) * _vXcoef * tempV,
                                              static_cast<float>(cos(alfa)) * _vYcoef * tempV,
                                              0,
                                              0.0001 * _aYcoef,
                                              _flashLifeTimeMs));
        light->setTexture(_texture, _lightSize.x, _lightSize.y);

        if (_autoColor && _mapColorsSize > 0) {
            light->setColor(_map_Colors[_lColors[temp]]);
        } else {
            light->setColor(_color);
        }
        light->setPosition(x, y);
        _vLights.append(light);
    }
    return lightNumber;
}

void Flash::updateFlash(const float &time)
{
    for (auto &light : _vLights) {
        if (light->getAlfa() < 5) {
            _vLights.removeOne(light);
        }
    }

    for (auto &light : _vLights) {
        light->update(time);
    }
}

void Flash::drawFlash(RenderWindow *pWindow) const
{
    for (const auto &light : _vLights) {
        light->draw(pWindow);
    }
}

void Flash::clearAll()
{
    _vLights.clear();
    _vLights.shrink_to_fit();
}

void Flash::setAutoNumber(bool value)
{
    _autoNumber = value;
}

void Flash::setAutoColor(bool value)
{
    _autoColor = value;
}

void Flash::setColor(Color color)
{
    _color = color;
}

bool Flash::getAutoNumber() const
{
    return _autoNumber;
}

bool Flash::getAutoColor() const
{
    return _autoColor;
}

int Flash::getNumberOfLights() const
{
    return _vLights.size();
}

QMap<std::string, Color> &Flash::getMapColors()
{
    return _map_Colors;
}

QList<std::string> &Flash::getMapColorKeys()
{
    return _lColors;
}

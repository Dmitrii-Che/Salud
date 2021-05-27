#ifndef FLASH_H
#define FLASH_H

#include <QMap>
#include <QSharedPointer>

#include "light.h"

class Flash
{
public:
    explicit Flash(const QMap<std::string, Color> &map_Colors);
    Flash(const Flash &Other);
    Flash &operator=(const Flash &Other);
    ~Flash();
    void setTexture(const std::string &filename);
    void setMoveCoefs(unsigned vXcoef = 1, unsigned vYcoef = 1, unsigned aYcoef = 1);
    int makeFlash(int x, int y, int maxN = 50, int minN = 20);
    void updateFlash(const float &time);
    void drawFlash(RenderWindow *pWindow) const;
    void clearAll();

    void setAutoNumber(bool value = true);
    void setAutoColor(bool value);
    void setColor(Color color = Color::White);

    bool getAutoNumber() const;
    bool getAutoColor() const;

    int getNumberOfLights() const;

    QMap<std::string, Color> &getMapColors();
    QList<std::string> &getMapColorKeys();

protected:
    time_t *_ptt = nullptr;

    QMap<std::string, Color> _map_Colors;
    Texture _texture;
    Color _color{Color::White};
    QVector<QSharedPointer<Light>> _vLights;

    unsigned _mapColorsSize = 0;
    unsigned _flashLifeTimeMs = 200;
    unsigned _vXcoef = 0;
    unsigned _vYcoef = 0;
    unsigned _aYcoef = 0;

    QList<std::string> _lColors;

    Vector2f _lightSize = {10, 10};

    bool _autoNumber = true;
    bool _autoColor = true;
};

#endif // FLASH_H

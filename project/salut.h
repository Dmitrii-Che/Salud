#ifndef SALUT_H
#define SALUT_H

#include "button.h"
#include "flash.h"
#include "message.h"
#include "snow.h"
#include <math.h>
#include <QMainWindow>
#include <QTimer>

using namespace sf;

class Salut : public QMainWindow
{
    Q_OBJECT

public:
    explicit Salut(QWidget *parent = nullptr);
    void setBackGround(const std::string &filename);
    void setFront(const std::string &filename);
    ~Salut();

private:
    void init();
    void initTexts();
    void initBackGround();
    void initButtons();
    void arrangeButtons();
    void drawAll() const;
    void drawBackGround() const;
    void drawInfo() const;
    void drawUI() const;
    void drawLights() const;
    void drawSnow() const;
    void showExitMsg();
    void autoscale();
    void mainLoop();
    void keyReaction();
    void mouseReaction(const Event &e);
    void eventReaction();
    void resizeReaction();
    void buttonReaction();
    void makeSnow(int Number);
    void updateLights(const float &time);
    void updateSnow(const float &time);

protected:
    Texture _textureBbackGround;
    Texture _textureFront;
    Sprite _spriteBackGround;
    Sprite _spriteFront;
    unsigned _windW;
    unsigned _windH;
    unsigned _modeWidth;
    unsigned _modeHeight;
    float _btnSizeCoefX;
    float _btnSizeCoefY;
    float _time;

    int _maxNumbOfLight, _minNumbOfLight, _totalAmountOfLights, _lastFlashlAmountOfLights,
        _totalFlashSum;

    const Vector2f _fpsPosition{20.f, 20.f};
    const unsigned _fpsLimit = 60;
    const unsigned _fleshMoveCoef = 2;
    const float _cnstBorder = 100.f;
    const float _flashWorkTime = 1000.f;
    const float _msgSizeCoef = 100.f;
    const int _maxNumbOfLightBasic = 50;
    const int _minNumbOfLightBasic = 20;
    const int _fontSize = 16;

    RenderWindow *_pWindow = nullptr;
    time_t *_ptt = nullptr;
    QList<std::string> _lLightNumberKeyNames;
    Text _textFPS, _textLight;
    Font _font;
    Button _btnStart, _btnStop, _btnExit;
    Message _msgExit;
    QVector<QSharedPointer<Button>> _vpColorBtns;
    QVector<QSharedPointer<Button>> _vpLightNumberBtns;

    QSharedPointer<Button> _pBtnAutoColor = nullptr;
    QSharedPointer<Button> _pBtnAutoNumber = nullptr;

    Flash _flash;
    Snow _snow;

    bool _isAutoFlashOn = false;
    bool _isMsgExitVisible = false;
};
#endif // SALUT_H

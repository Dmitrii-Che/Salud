#include "button.h"
#include <QDebug>
#include <QTimer>

Button::Button()
    : _moveOverColor({136, 255, 200, 255}) /*Turquoise*/,
      _releaseColor({255, 255, 255, 255}) /*Wite*/, _fixColor({0, 00, 255, 255})
{
    _isButtonWithLock = false;
    _isButtonLocked = false;
}
Button::~Button() {}

bool Button::checkForPressed(const Window &relativeTo)
{
    bool mark = false;
    if (Mouse::isButtonPressed(Mouse::Left)) {
        int x0 = _rect.left;
        int y0 = _rect.top;
        int x1 = x0 + _rect.width;
        int y1 = y0 + _rect.height;

        int mX = Mouse::getPosition(relativeTo).x;
        int mY = Mouse::getPosition(relativeTo).y;

        if ((x0 < mX && mX < x1) && (y0 < mY && mY < y1)) {
            mark = true;
            if (!_isButtonWithLock) {
                pressButton();
            } else {
                lockButton();
            }
        }
    }
    return mark;
}

bool Button::checkForMoveOver(const Window &relativeTo)
{
    bool mark = false;

    int x0 = _rect.left;
    int y0 = _rect.top;
    int x1 = x0 + _rect.width;
    int y1 = y0 + _rect.height;

    int mX = Mouse::getPosition(relativeTo).x;
    int mY = Mouse::getPosition(relativeTo).y;

    if ((x0 < mX && mX < x1) && (y0 < mY && mY < y1)) {
        setColor(_moveOverColor);
        mark = true;
    } else {
        setColor(_releaseColor);
    }

    return mark;
}

bool Button::isButtonLocked()
{
    return _isButtonLocked;
}

void Button::pressButton()
{
    setColor(_pushColor);
    QTimer::singleShot(_clickViewTimeMS, [&] { setColor(_releaseColor); });
}
bool Button::lockButton()
{
    Uint8 tempR = static_cast<Uint8>(_releaseColor.r * 0.4);
    Uint8 tempG = static_cast<Uint8>(_releaseColor.g * 0.4);
    Uint8 tempB = static_cast<Uint8>(_releaseColor.b * 0.4);
    setColor({tempR, tempG, tempB});
    return _isButtonLocked = true;
}

bool Button::releaseButton()
{
    setColor(_releaseColor);
    return _isButtonLocked = false;
}

void Button::setLockingParameters(bool value)
{
    _isButtonWithLock = value;
}

void Button::setReleaseColor(const Color &color)
{
    _releaseColor = {color};
    setColor(color);
}

void Button::setMoveOverColor(const Color &color)
{
    _moveOverColor = color;
}

void Button::setText(const std::string &str, const Font &font)
{
    _text.setString(str);
    _text.setFont(font);
    _text.setPosition(_rect.left, _rect.top);
}

void Button::setTextPosition(float x, float y)
{
    _text.setPosition(x, y);
}

void Button::setTextColor(const Color &color)
{
    _releaseColor = color;
    _text.setColor(_releaseColor);
}

void Button::setTextSize(int size)
{
    _text.setCharacterSize(size);
}

void Button::draw(RenderWindow *pWindow) const
{
    BasicElement::draw(pWindow);
    pWindow->draw(_text);
}

Color &Button::getReleaseColor()
{
    return _releaseColor;
}

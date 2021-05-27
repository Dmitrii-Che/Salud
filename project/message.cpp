#include "message.h"

Message::Message(const QMap<std::string, std::string> &map_Files)
    : _map_Files(map_Files), _exitStr("    Exit"), _continueStr("Continue"),
      _standardTextColor(Color::White), _actionTextColor({136, 255, 200, 255})
{
    _BtnSizeCoef = 100;
    initButtons();
}

Message::~Message() {}

void Message::initButtons()
{
    _btnExit.setRect(_rect.left + _rect.width * .1f,
                     _rect.top + _rect.height * .6f,
                     _BtnSizeCoef,
                     _BtnSizeCoef);

    _btnExit.setText(_exitStr, _font);

    _btnContinue.setRect(_rect.left + _rect.width * .1f + _rect.width * .5f,
                         _rect.top + _rect.height * .6f,
                         _BtnSizeCoef,
                         _BtnSizeCoef);

    _btnContinue.setText(_continueStr, _font);

    _text.setPosition(_rect.left + _rect.width * .1f, _rect.top + _rect.height * .3f);
}

void Message::setText(const std::string &str, const Font &font, int charSize)
{
    _font = font;
    _text.setFont(_font);
    _text.setCharacterSize(charSize);
    _text.setColor(_standardTextColor);
    _text.setString(str);
    _text.setPosition(_rect.left + _rect.width * .1f, _rect.top + _rect.height * .3f);
}

void Message::setFont(const Font &font)
{
    _font = font;
    _text.setFont(_font);
}

void Message::setActionColor(const Color &color)
{
    _actionTextColor = color;
}

void Message::setDrawable(bool isDrawable)
{
    _isDrawable = isDrawable;
}

void Message::buttonReaction(RenderWindow *pWindow)
{
    if (_btnExit.checkForPressed(*pWindow)) {
        if (_isDrawable) {
            pWindow->close();
        }
    }

    if (_btnContinue.checkForPressed(*pWindow)) {
        _isDrawable = false;
    }

    if (_btnExit.checkForMoveOver(*pWindow)) {
        _btnExit.setTextColor(_actionTextColor);
    } else {
        _btnExit.setTextColor(_standardTextColor);
    }

    if (_btnContinue.checkForMoveOver(*pWindow)) {
        _btnContinue.setTextColor(_actionTextColor);
    } else {
        _btnContinue.setTextColor(_standardTextColor);
    }
}

bool Message::getDrawable() const
{
    return _isDrawable;
}

void Message::setPosition(float x, float y)
{
    BasicElement::setPosition(x, y);
    update();
}

void Message::draw(RenderWindow *pWindow) const
{
    if (_isDrawable) {
        BasicElement::draw(pWindow);
        pWindow->draw(_text);

        _btnExit.draw(pWindow);
        _btnContinue.draw(pWindow);
    }
}

void Message::update()
{
    _rect.left = _sprite.getPosition().x;
    _rect.top = _sprite.getPosition().y;
    initButtons();
}

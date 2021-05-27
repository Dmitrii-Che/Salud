#ifndef BUTTON_H
#define BUTTON_H

#include "basicelement.h"

class Button : public BasicElement
{
public:
    Button();
    ~Button();
    bool checkForPressed(const Window &relativeTo);
    bool checkForMoveOver(const Window &relativeTo);
    bool isButtonLocked();
    void pressButton();
    bool lockButton();
    bool releaseButton();
    void setLockingParameters(bool value = true);
    void setReleaseColor(const Color &color);
    void setMoveOverColor(const Color &color);
    void setText(const std::string &str, const Font &font);
    void setTextPosition(float x, float y);
    void setTextColor(const Color &color);
    void setTextSize(int size);

    void draw(RenderWindow *pWindow) const override;

    Color &getReleaseColor();

protected:
    const Color _pushColor = {133, 133, 133, 255}; /*Grey*/
    Color _moveOverColor;                          /*Turquoise*/
    Color _releaseColor;
    Color _fixColor;
    const int _clickViewTimeMS = 100;
    Text _text;
    bool _isButtonWithLock;
    bool _isButtonLocked;
};

#endif // BUTTON_H

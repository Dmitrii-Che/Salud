#ifndef MESSAGE_H
#define MESSAGE_H

#include "basicelement.h"
#include "button.h"
#include <QMap>

class Message : public BasicElement
{
public:
    explicit Message(const QMap<std::string, std::string> &map_Files);
    ~Message();
    void initButtons();
    void setText(const std::string &str, const Font &font, int charSize = 20);
    void setFont(const Font &font);
    void setStandartColor(const Color &color);
    void setActionColor(const Color &color);
    void setDrawable(bool isDrawable = true);
    void buttonReaction(RenderWindow *pWindow);
    bool getDrawable() const;
    void setPosition(float x, float y);

protected:
    Font _font;
    Text _text;
    int _BtnSizeCoef;

    Button _btnExit, _btnContinue;
    QMap<std::string, std::string> _map_Files;
    bool _isDrawable = false;

    std::string _exitStr, _continueStr;

    Color _standardTextColor;
    Color _actionTextColor;

public:
    void draw(RenderWindow *pWindow) const override;

private:
    void update() override;
};

#endif // MESSAGE_H

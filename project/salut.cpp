#include "salut.h"

QMap<std::string, std::pair<Keyboard::Key, Keyboard::Key>> map_KeysCombinations{
    {"Exit", std::pair<Keyboard::Key, Keyboard::Key>{Keyboard::LAlt, Keyboard::Q}},
    {"Continue", std::pair<Keyboard::Key, Keyboard::Key>{Keyboard::LAlt, Keyboard::C}},
    {"MakeSnow", std::pair<Keyboard::Key, Keyboard::Key>{Keyboard::LAlt, Keyboard::S}}};

QMap<std::string, Color> map_Colors{{"green", {50, 255, 50, 255}},
                                    {"yellow", {255, 255, 0, 255}},
                                    {"white", {255, 255, 255, 255}},
                                    {"blue", {0, 238, 255, 255}},
                                    {"blue2", {0, 85, 255, 255}},
                                    {"fiolet", {255, 0, 247, 255}},
                                    {"orange", {255, 150, 0, 255}},
                                    {"red", {255, 47, 0, 255}}};

QMap<std::string, unsigned> map_LightNumbers{{" low", 10},
                                             {"medium", 50},
                                             {" norm", 100},
                                             {" high", 150}};

QMap<std::string, std::string> map_Files{{"background", "src/1111.png"},
                                         {"front", "src/33333.png"},
                                         {"message", "src/msg2.png"},
                                         {"light", "src/spark.png"},
                                         {"snowflake", "src/snowflakes2.png"},
                                         {"start", "src/on.png"},
                                         {"stop", "src/off.png"},
                                         {"exit", "src/exit3.png"},
                                         {"colorBtn", "src/btn2.png"},
                                         {"fontFps", "fonts/calibri.ttf"}};

Salut::Salut(QWidget *parent) : _msgExit(Message(map_Files)), _flash(Flash(map_Colors))
{
    _windW = 100;
    _windH = 100;
    _modeWidth = 1500;
    _modeHeight = 1000;
    _btnSizeCoefX = 100.f;
    _btnSizeCoefY = 100.f;
    _time = 0.f;
    _maxNumbOfLight = 50;
    _minNumbOfLight = 20;
    _totalAmountOfLights = 0;
    _lastFlashlAmountOfLights = 0;
    _totalFlashSum = 0;

    _pWindow = new RenderWindow(VideoMode(_modeWidth, _modeHeight), "SALUT");
    //    _pWindow->setVerticalSyncEnabled(true);
    _pWindow->setFramerateLimit(_fpsLimit);
    _pWindow->setPosition({0, 0});

    init();
    mainLoop();
}

Salut::~Salut()
{
    delete _ptt;
    delete _pWindow;
}

void Salut::init()
{
    _ptt = new time_t(std::chrono::system_clock::now().time_since_epoch().count());
    srand(time(_ptt));

    _font.loadFromFile(map_Files["fontFps"]);

    _windW = _pWindow->getSize().x;
    _windH = _pWindow->getSize().y;
    _btnSizeCoefX = _windW * 0.1f;
    _btnSizeCoefY = _windH * 0.1f;

    _flash.setTexture(map_Files["light"]);
    _flash.setMoveCoefs(_fleshMoveCoef, _fleshMoveCoef, _fleshMoveCoef);
    _snow.setTexture(map_Files["snowflake"]);
    _snow.setBorders(_windW, _windH);

    _msgExit.setTexture(map_Files["message"], _msgSizeCoef * 4.f, _msgSizeCoef * 2.f);
    _msgExit.setPosition(_windW / 2.f - _msgSizeCoef * 2.f, _windH / 3.f - _msgSizeCoef);
    _msgExit.setText("  Are You Sure for Exit?", _font, _fontSize * 2);

    _lLightNumberKeyNames = map_LightNumbers.keys();

    initBackGround();
    initTexts();
    initButtons();
    autoscale();
}

void Salut::initTexts()
{
    _textFPS.setFont(_font);
    _textFPS.setCharacterSize(_fontSize);
    _textFPS.setColor(Color::White);
    _textFPS.setPosition(_fpsPosition);

    _textLight.setFont(_font);
    _textLight.setCharacterSize(_fontSize);
    _textLight.setColor(Color::White);
    _textLight.setPosition(_fpsPosition.x, _fpsPosition.y + _fontSize * 2.f);
}

void Salut::initBackGround()
{
    setBackGround(map_Files["background"]);
    setFront(map_Files["front"]);
}

void Salut::initButtons()
{
    _btnStart.setTexture(map_Files["start"], _btnSizeCoefX, _btnSizeCoefY);

    _btnStop.setTexture(map_Files["stop"], _btnSizeCoefX, _btnSizeCoefY);

    _btnExit.setTexture(map_Files["exit"], _btnSizeCoefX * 0.5f, _btnSizeCoefY);

    for (const auto &clrKey : _flash.getMapColorKeys()) {
        QSharedPointer<Button> btn(new Button());
        btn->setTexture(map_Files["colorBtn"], _btnSizeCoefX * 0.5f, _btnSizeCoefY * 0.5f);
        btn->setReleaseColor(map_Colors[clrKey]);
        btn->setLockingParameters(true);
        _vpColorBtns.append(btn);
    }

    QSharedPointer<Button> pAutoColorBtn(new Button());
    pAutoColorBtn->setTexture(map_Files["colorBtn"], _btnSizeCoefX * 0.5f, _btnSizeCoefY * 0.5f);
    pAutoColorBtn->setReleaseColor({100, 100, 100, 255});
    _pBtnAutoColor = pAutoColorBtn;

    for (int i = 0; i < map_LightNumbers.size(); i++) {
        QSharedPointer<Button> btn(new Button());
        btn->setText(_lLightNumberKeyNames[i], _font);
        btn->setTextSize(50);
        btn->setTextColor(map_Colors["yellow"]);
        _vpLightNumberBtns.append(btn);
    }

    QSharedPointer<Button> numberOffbtn(new Button());
    numberOffbtn->setText("auto", _font);
    numberOffbtn->setTextColor(map_Colors["green"]);
    _pBtnAutoNumber = numberOffbtn;

    arrangeButtons();
}

void Salut::arrangeButtons()
{
    float y0 = _windH * .8f;
    _btnStart.setRect(_btnSizeCoefX * 1.3f, y0 + _btnSizeCoefY * .83f, _btnSizeCoefX, _btnSizeCoefY);
    _btnStart.setSize(_btnSizeCoefX, _btnSizeCoefY);
    _btnStart.setReleaseColor(map_Colors["green"]);

    _btnStop.setRect(_windW - _btnSizeCoefX * 2.3f,
                     y0 + _btnSizeCoefY * .83f,
                     _btnSizeCoefX,
                     _btnSizeCoefY);
    _btnStop.setSize(_btnSizeCoefX, _btnSizeCoefY);
    _btnStop.setReleaseColor(map_Colors["red"]);

    _btnExit.setRect(_windW - _btnSizeCoefX * .5f,
                     _btnSizeCoefY * .5f,
                     _btnSizeCoefX,
                     _btnSizeCoefY);
    _btnExit.setSize(_btnSizeCoefX * .4f, _btnSizeCoefY * .8f);

    float tempDistanseParam = ((_btnStop.getRect().left - _btnStart.getRect().left + _btnSizeCoefX)
                               * .5f);
    float x0 = _windW * 0.5 - tempDistanseParam * .5f;
    float tempDistanseCoef = (tempDistanseParam / (_vpColorBtns.size() + 1));

    /*********************************************************/

    FloatRect tempRect{x0, y0 + _btnSizeCoefY, tempDistanseCoef * .5f, tempDistanseCoef * .5f};

    for (const auto &btn : _vpColorBtns) {
        btn->setRect(tempRect);
        btn->setSize(tempDistanseCoef, tempDistanseCoef);
        tempRect.left += tempDistanseCoef;
    }

    _pBtnAutoColor->setRect(tempRect);
    _pBtnAutoColor->setSize(tempDistanseCoef, tempDistanseCoef);

    tempRect.left = x0;
    tempRect.top = y0 + _btnSizeCoefY * .5f;
    tempRect.width = _btnSizeCoefX * .5f;
    for (const auto &btn : _vpLightNumberBtns) {
        btn->setRect(tempRect);
        btn->setTextPosition(tempRect.left, tempRect.top);
        btn->setTextSize(_btnSizeCoefX * .2f);
        tempRect.left += _btnSizeCoefX * .9f;
    }

    _pBtnAutoNumber->setRect(tempRect);
    _pBtnAutoNumber->setTextPosition(tempRect.left, tempRect.top);
}

void Salut::setBackGround(const std::string &filename)
{
    _textureBbackGround.loadFromFile(filename);
    _spriteBackGround.setTexture(_textureBbackGround);
    int tempW = _textureBbackGround.getSize().x;
    int tempH = _textureBbackGround.getSize().y;
    int tempVideoW = VideoMode::getDesktopMode().width;
    int tempVideoH = VideoMode::getDesktopMode().height;

    if (tempW > tempVideoW) {
        _modeWidth = tempVideoW;
    } else {
        _modeWidth = tempW;
    }

    if (tempH > tempVideoH) {
        _modeHeight = tempVideoH;
    } else {
        _modeHeight = tempH;
    }
}

void Salut::setFront(const std::string &filename)
{
    _textureFront.loadFromFile(filename);
    _spriteFront.setTexture(_textureFront);
    _spriteFront.setPosition(0.f, _windH * .8f);
}

void Salut::drawAll() const
{
    _pWindow->clear(Color::Blue);
    drawBackGround();
    drawLights();
    drawInfo();
    drawUI();
    drawSnow();
    _pWindow->display();
}

void Salut::drawBackGround() const
{
    _pWindow->draw(_spriteBackGround);
}

void Salut::drawInfo() const
{
    _pWindow->draw(_textFPS);
    _pWindow->draw(_textLight);
}

void Salut::drawUI() const
{
    _pWindow->draw(_spriteFront);
    _btnStart.draw(_pWindow);
    _btnStop.draw(_pWindow);

    for (const auto &btn : _vpColorBtns) {
        btn->draw(_pWindow);
    }

    if (_pBtnAutoColor != nullptr) {
        _pBtnAutoColor->draw(_pWindow);
    }
    for (const auto &btn : _vpLightNumberBtns) {
        btn->draw(_pWindow);
    }
    if (_pBtnAutoNumber != nullptr) {
        _pBtnAutoNumber->draw(_pWindow);
    }
    _btnExit.draw(_pWindow);

    _msgExit.draw(_pWindow);
}

void Salut::drawLights() const
{
    _flash.drawFlash(_pWindow);
}

void Salut::drawSnow() const
{
    _snow.drawSnow(_pWindow);
}

void Salut::showExitMsg()
{
    _msgExit.setPosition(_windW / 2.f - _msgSizeCoef * 2, _windH / 3.f - _msgSizeCoef);
    _msgExit.setDrawable();
    _isMsgExitVisible = true;
}

void Salut::autoscale()
{
    float w = static_cast<float>(_windW);
    float h = static_cast<float>(_windH);
    float w0 = static_cast<float>(_modeWidth);
    float h0 = static_cast<float>(_modeHeight);
    float scaleX = w / w0;
    float scaleY = h / h0;
    _spriteBackGround.setScale(scaleX, scaleY);

    float x = _textureFront.getSize().x;
    float y = _textureFront.getSize().y;
    float scaleX2 = w / x;
    float scaleY2 = h / y * 0.2;
    _spriteFront.setScale(scaleX2, scaleY2);
    _spriteFront.setPosition(0.f, h * .8f);

    _msgExit.setPosition(_windW / 2.f - _msgSizeCoef * 2.f, _windH / 3.f - _msgSizeCoef);

    arrangeButtons();
}

void Salut::mainLoop()
{
    Clock fpsClock, clock;
    Time previousTime = fpsClock.getElapsedTime();
    Time currentTime;
    float flashWorkTimeout = 0.f;

    while (_pWindow->isOpen()) {
        flashWorkTimeout += _time;
        _time = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        buttonReaction();
        eventReaction();

        /*FPS*/
        currentTime = fpsClock.getElapsedTime();
        float fps = 1.f / (currentTime.asSeconds() - previousTime.asSeconds());
        _textFPS.setString(QString("FPS: %1").arg(floor(fps)).toStdString());
        previousTime = currentTime;
        /*END FPS*/

        /*AUTOFLASH*/
        if (_isAutoFlashOn && flashWorkTimeout > _flashWorkTime) {
            int x = (_pWindow->getSize().x - _cnstBorder * 2);
            int y = (_pWindow->getSize().y - _cnstBorder * 5);

            _lastFlashlAmountOfLights = _flash.makeFlash((rand() % x) + _cnstBorder,
                                                         (rand() % y) + _cnstBorder,
                                                         _maxNumbOfLight,
                                                         _minNumbOfLight);
            _totalFlashSum++;
            flashWorkTimeout = 0.f;
        }
        /*END AUTOFLASH*/

        /*INFO*/
        _totalAmountOfLights = _flash.getNumberOfLights();
        _textLight.setString(QString("\nThe Last Flash: %1\nActual Lights: %2\nSalutes/Session: "
                                     "%3\n\nAlt+S For Snow\nAlt+Q For Exit\nMouseR For Clear")
                                 .arg(_lastFlashlAmountOfLights)
                                 .arg(_totalAmountOfLights)
                                 .arg(_totalFlashSum)
                                 .toStdString());
        /*END INFO*/

        updateLights(_time);
        updateSnow(_time);

        drawAll();
    }
}

void Salut::keyReaction()
{
    if (Keyboard::isKeyPressed(map_KeysCombinations["Exit"].first)
        && Keyboard::isKeyPressed(map_KeysCombinations["Exit"].second)) {
        _pWindow->close();
        //        _msgExit.setDrawable(true);
    }

    if (Keyboard::isKeyPressed(map_KeysCombinations["Continue"].first)
        && Keyboard::isKeyPressed(map_KeysCombinations["Continue"].second)) {
        _msgExit.setDrawable(false);
    }

    if (Keyboard::isKeyPressed(map_KeysCombinations["MakeSnow"].first)
        && Keyboard::isKeyPressed(map_KeysCombinations["MakeSnow"].second)) {
        makeSnow(100);
    }
}

void Salut::mouseReaction(const Event &e)
{
    if (e.mouseButton.button == Mouse::Button::Left) {
        unsigned x = e.mouseButton.x;
        unsigned y = e.mouseButton.y;
        if (y < _windH / 2 && !_isMsgExitVisible) {
            _lastFlashlAmountOfLights = _flash.makeFlash(x, y, _maxNumbOfLight, _minNumbOfLight);
            _totalFlashSum++;
        }
    } else {
        _flash.clearAll();
        _snow.clearAll();
    }
    _isMsgExitVisible = _msgExit.getDrawable();
}

void Salut::eventReaction()
{
    Event event;
    while (_pWindow->pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            _pWindow->close();
            break;

        case Event::KeyPressed:
            keyReaction();
            break;

        case Event::MouseButtonPressed:
            mouseReaction(event);
            break;

        case Event::Resized:
            _windW = event.size.width;
            _windH = event.size.height;
            resizeReaction();

            break;
        }
    }
}

void Salut::resizeReaction()
{
    float w = static_cast<float>(_windW);
    float h = static_cast<float>(_windH);

    _btnSizeCoefX = w * .1f;
    _btnSizeCoefY = h * .1f;
    _pWindow->setView(View(Vector2f(w * .5f, h * .5f), Vector2f(w, h)));

    if (_windW >= _modeWidth) {
        _pWindow->setSize({_modeWidth, _windH});
    }

    if (_windH >= _modeHeight) {
        _pWindow->setSize({_windW, _modeHeight});
    }

    autoscale();
}

void Salut::buttonReaction()
{
    auto releaseColorButtons = [&] {
        for (const auto &clrBtn : _vpColorBtns) {
            clrBtn->releaseButton();
        }
    };
    if (_btnStart.checkForPressed(*_pWindow)) {
        _isAutoFlashOn = true;
    }
    if (_btnStop.checkForPressed(*_pWindow)) {
        _isAutoFlashOn = false;
    }
    if (_btnExit.checkForPressed(*_pWindow)) {
        showExitMsg();
    }

    for (const auto &clrBtn : _vpColorBtns) {
        if (clrBtn->checkForPressed(*_pWindow)) {
            releaseColorButtons();
            clrBtn->lockButton();
            _flash.setAutoColor(false);
            _flash.setColor(clrBtn->getReleaseColor());
        }
    }

    if (_pBtnAutoColor != nullptr) {
        if (_pBtnAutoColor->checkForPressed(*_pWindow)) {
            _flash.setAutoColor(true);
            releaseColorButtons();
        }
    }

    for (int i = 0; i < _vpLightNumberBtns.size(); i++) {
        if (_vpLightNumberBtns[i]->checkForPressed(*_pWindow)) {
            for (const auto &btn : _vpLightNumberBtns) {
                btn->setTextColor(map_Colors["yellow"]);
            }
            if (_pBtnAutoNumber != nullptr) {
                _pBtnAutoNumber->setTextColor(map_Colors["yellow"]);
            }
            _vpLightNumberBtns[i]->setTextColor(map_Colors["green"]);
            _flash.setAutoNumber(false);
            _maxNumbOfLight = map_LightNumbers[_lLightNumberKeyNames[i]];
        }
    }

    if (_pBtnAutoNumber != nullptr) {
        if (_pBtnAutoNumber->checkForPressed(*_pWindow)) {
            for (const auto &btn : _vpLightNumberBtns) {
                btn->setTextColor(map_Colors["yellow"]);
            }
            _pBtnAutoNumber->setTextColor(map_Colors["green"]);
            _flash.setAutoNumber(true);
            _maxNumbOfLight = _maxNumbOfLightBasic;
            _minNumbOfLight = _minNumbOfLightBasic;
        }
    }

    _msgExit.buttonReaction(_pWindow);
}

void Salut::makeSnow(int Number)
{
    _snow.makeSnow(Number);
}

void Salut::updateLights(const float &time)
{
    _flash.updateFlash(time);
}

void Salut::updateSnow(const float &time)
{
    _snow.updateSnow(time);
}

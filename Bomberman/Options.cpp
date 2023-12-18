#include "Options.h"

//конструктор
Options::Options(Game* game) : Menu(game) {
    title.setString("Options");
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);

    //подпись
    check.setFont(g->getFont());
    check.setFillColor(sf::Color::White);
    check.setString("Sound (ON / OFF)");
    check.setCharacterSize(30);
    check.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2 + 25, 270);

    //музыка на фоне
    if (!ambient.openFromFile("music/ambient.mp3")) {
        cout << "Ошибка загрузки музыки: music/ambient.mp3" << endl;
    }
    ambient.setVolume(10);
    ambient.setLoop(true);
    ambient.play();
    sound = true;

    firstState = OPTIONS;
}

//запуск цикла
GameState Options::start() {

    //цикл игры
    Gui gui{ g->getRenderWindow() };
    setButtons(gui);
    state = firstState;
    while (g->isOpen())
    {
        //пул событий
        sf::Event event;
        while (g->pollEvent(event))
        {
            //обработка событий
            gui.handleEvent(event);

            //событие закрытия формы
            if (event.type == sf::Event::Closed) {
                g->close();
            }
        }

        //переход в другое состояние
        if (state != firstState) {
            clear();
            return state;
        }

        //отрисовка
        paint(gui);
    }
    clear();
    return EXIT;
}

//включаем или отключаем звук
void Options::checkSounds(bool flag) {
    if (flag) {
        cout << "Звук включен" << endl;
        ambient.play();
        sound = true;
    }
    else {
        cout << "Звук выключен" << endl;
        ambient.stop();
        sound = false;
    }
}

//получаем значение булевой переменной
bool Options::checkSound() {
    return sound;
}

//установка кнопок
void Options::setButtons(Gui& gui) {

    //размеры кнопок
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //вкл / выкл звук в игре
    box = CheckBox::create();
    box->setChecked(true);
    box->setSize({ btnSize.width - 70, btnSize.height - 15 });
    box->setPosition({ (w - btnSize.width) / 2 - 70, (h - btnSize.height) / 2 });
    box->onChange([&]() {checkSounds(box->isChecked()); });
    gui.add(box);

    //Назад
    Button::Ptr back = Button::create();
    back->setSize({ btnSize.width,btnSize.height });
    back->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 180 });
    back->setText("Back");
    back->onPress([&] {state = MENU; });
    gui.add(back);
}

//отрисовка
void Options::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    g->getRenderWindow().draw(check);
    gui.draw();
    g->getRenderWindow().display();
}

//очистка интерфейса
void Options::clear() {
    box.reset();
}
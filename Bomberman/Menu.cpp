#include "Menu.h"

//конструктор
Menu::Menu(Game* game) {
    g = game; //копируем указатель

    //текстура фона
    backgroundTexture = g->loadTexture("images/back.png");
    backgroundSprite.setTexture(backgroundTexture);

    //заголовок
    title.setFont(g->getFont());
    title.setFillColor(sf::Color::White);
    title.setString("BOMBER MAN");
    title.setCharacterSize(60);
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);

    //начальное состояние
    firstState = MENU;
}

//запуск цикла
GameState Menu::start() {

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
            if (event.type == sf::Event::Closed)
                g->close();
        }

        //переход в другое состояние
        if (state != firstState) {
            return state;
        }

        //отрисовка
        paint(gui);
    }
    return EXIT;
}

//установка кнопок
void Menu::setButtons(Gui& gui) {

    //размеры кнопок
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //Игра
    Button::Ptr game = Button::create();
    game->setSize({ btnSize.width,btnSize.height });
    game->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 120 });
    game->setText("Play");
    game->onPress([&] {state = GAME; });
    gui.add(game);

    //Рекорды
    Button::Ptr rating = Button::create();
    rating->setSize({ btnSize.width,btnSize.height });
    rating->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 60 });
    rating->setText("Rating");
    rating->onPress([&] {state = RATING; });
    gui.add(rating);

    //Настройки
    Button::Ptr options = Button::create();
    options->setSize({ btnSize.width,btnSize.height });
    options->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 });
    options->setText("Options");
    options->onPress([&] {state = OPTIONS; });
    gui.add(options);

    //Выход
    Button::Ptr exit = Button::create();
    exit->setSize({ btnSize.width,btnSize.height });
    exit->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 60 });
    exit->setText("Exit");
    exit->onPress([&] {state = LOGIN; });
    gui.add(exit);
}

//отрисовка
void Menu::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    gui.draw();
    g->getRenderWindow().display();
}
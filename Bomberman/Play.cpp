#include "Play.h"

//конструктор
Play::Play(Game* game) : Menu(game) {
    title.setString("");
    firstState = GAME;
}

//запуск цикла
GameState Play::start(Player& player) {

    //цикл игры
    Gui gui{ g->getRenderWindow() };
    Logic lg{ g, 544, 448, 32, &player };
    Clock clock;
    state = firstState;
    while (g->isOpen())
    {
        //сколько прошло секунд с последнего обновления
        auto dt = clock.restart().asSeconds();

        //пул событий
        sf::Event event;
        while (g->pollEvent(event))
        {
            //обработка событий
            gui.handleEvent(event);

            //событие закрытия формы
            if (event.type == sf::Event::Closed)
                g->close();

            //нажали и отпустили
            if (event.type == sf::Event::KeyReleased) {
                
                //выход в меню
                if (event.key.code == sf::Keyboard::Escape) {
                    state = MENU;
                }

                //движение бомбермена по карте
                if (event.key.code == sf::Keyboard::Right) {
                    cout << "Право" << endl;
                    lg.move(1, 0);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    cout << "Лево" << endl;
                    lg.move(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    cout << "Вверх" << endl;
                    lg.move(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    cout << "Вниз" << endl;
                    lg.move(0, 1);
                }

                //рестарт уровня
                if (event.key.code == sf::Keyboard::R) {
                    lg.reset();
                }

                //установка бомбы
                if (event.key.code == sf::Keyboard::Space) {
                    cout << "Установка бомбы" << endl;
                    lg.setBomb();
                }
            }
        }

        //переход в другое состояние
        if (state != firstState) {
            player.setScore(0);
            return state;
        }

        //обновление врагов
        lg.update(dt);

        //отрисовка
        paint(gui, lg);
    }
    return EXIT;
}

//отрисовка
void Play::paint(Gui& gui, Logic& lg) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);

    //отрисовка игрового поля
    lg.paint();

    //интерфейс
    gui.draw();
    g->getRenderWindow().display();
}

//деструктор
Play::~Play() {}
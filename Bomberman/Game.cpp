#include "Game.h"
#include "Menu.h"
#include "Rating.h"
#include "Options.h"
#include "Login.h"
#include "Player.h"
#include "Play.h"

//конструктор
Game::Game(Size size, string title) {
    win.create(VideoMode(size.width, size.height), title);
    //win.setFramerateLimit(144); //vsync
    this->size = size;

    //шрифт текста
    if (!font.loadFromFile("fonts/arial.ttf")) {
        cout << "Ошибка загрузки текста: fonts/arial.ttf" << endl;
    }
}

//запуск приложения
void Game::start() {
    Menu menu(this);
    Rating rating(this);
    Options options(this);
    Login login(this);
    Player player(this);
    Play play(this);
    GameState state = LOGIN;

    //в зависимости от текущего состояния игры
    while (state != EXIT) {
        switch (state) {
        case LOGIN: {
            cout << "Форма авторизации" << endl;
            state = login.start();
            player.loadData(login.getLogin()); //подгрузка информации о пользователе из файла
            break;
        }
        case GAME: {
            cout << "Игра" << endl;
            state = play.start(player);
            break;
        }
        case MENU: {
            cout << "Меню" << endl;
            state = menu.start();
            break;
        }
        case RATING: {
            cout << "Рейтинг" << endl;
            state = rating.start();
            break;
        }
        case OPTIONS: {
            cout << "Настройки" << endl;
            state = options.start();
            break;
        }
        }
    }
    cout << "Выход из игры" << endl;
}

//получаем текущее окно рендера
RenderWindow& Game::getRenderWindow()
{
    return win;
}

//проверка, что окно активно
bool Game::isOpen()
{
    return win.isOpen();
}

//добавление события
bool Game::pollEvent(sf::Event& e)
{
    return win.pollEvent(e);
}

//закрытие окна
void Game::close()
{
    win.close();
}

//получаем шрифт
sf::Font& Game::getFont() {
    return font;
}

//получаем файл
string Game::getFile() {
    return file;
}

//загрузка текстуры
sf::Texture Game::loadTexture(string textureFile)
{
    sf::Texture t;
    if (!t.loadFromFile(textureFile)) {
        cout << "Ошибка загрузки текстуры: " << textureFile << endl;
    }
    return t;
}

//размеры окна
const Size& Game::getSize() const
{
    return size;
}
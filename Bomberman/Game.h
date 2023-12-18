#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace sf;
using namespace tgui;
using namespace std;

//возможные состояния
enum GameState
{
    NONE, //пустое состояние
    LOGIN, //авторизация
    MENU, //главное меню
    GAME, //игра
    RATING, //таблица рекордов
    OPTIONS, //настройки
    WIN_LEVEL, //прошли уровень
    GAME_OVER, //проиграли
    EXIT //вышли из игры
};

//размеры игры
struct Size
{
    size_t width;
    size_t height;
};

//главное окно игры включающее все объекты
class Game {
private:
    RenderWindow win; //главное окно
    Gui gui; //интерфейс пользователя
    sf::Font font; //шрифт
    Size size; //размеры окна
    string file = "data.txt"; //файл с данными игроков

public:

    //конструктор
    Game(Size size, string title);

    //получаем текущее окно рендера
    RenderWindow& getRenderWindow();

    //проверка, что окно активно
    bool isOpen();

    //добавление события
    bool pollEvent(sf::Event& e);

    //закрытие окна
    void close();

    //получаем шрифт
    sf::Font& getFont();

    //получаем файл
    string getFile();

    //загрузка текстуры
    sf::Texture loadTexture(string textureFile);

    //размеры окна
    const Size& getSize() const;

    //запуск приложения
    void start();
};
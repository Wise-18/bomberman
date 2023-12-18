#pragma once
#include "Menu.h"

//авторизация нового пользователя
class Login : public Menu
{
private:
    sf::Text log; //подпись логина
    EditBox::Ptr input; //поле ввода
    string login; //текущий логин

public:

    //конструктор
    Login(Game* game);

    //запуск цикла
    GameState start();

    //установка кнопок
    void setButtons(Gui& gui);

    //отрисовка
    void paint(Gui& gui);

    //проверка логина в файле
    bool checkLogin();

    //получение логина
    string getLogin();

    //очистка интерфейса
    void clear();
};
#pragma once
#include "Menu.h"
#include <SFML/Audio/Music.hpp>

//опции - настройка звука
class Options : public Menu
{
private:
    sf::Text check; //надпись для checkbox
    CheckBox::Ptr box; //сам checkbox

    //музыка на фоне
    sf::Music ambient;
    bool sound; //остальные звуки в игре

public:

    //конструктор
    Options(Game* game);

    //запуск цикла
    GameState start();

    //установка кнопок
    void setButtons(Gui& gui);

    //включаем или отключаем звук
    void checkSounds(bool flag);

    //отрисовка
    void paint(Gui& gui);

    //очистка интерфейса
    void clear();

    //получаем значение булевой переменной
    bool checkSound();
};
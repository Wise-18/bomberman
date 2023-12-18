#pragma once
#include "Game.h"

//меню
class Menu {
protected:
    Game* g; //главное приложение
    GameState state; //текущее состояние
    GameState firstState; //начальное

    //текстура фона
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text title; //заголовок

public:

    //конструктор
    Menu(Game* game);

    //запуск цикла
    GameState start();

    //установка кнопок
    void setButtons(Gui& gui);

    //отрисовка
    void paint(Gui& gui);
};
#pragma once
#include "Player.h"
#include "Menu.h"
#include "Logic.h"

//класс игрового процесса
class Play : public Menu
{
public:

    //конструктор
    Play(Game* game);

    //запуск цикла
    GameState start(Player& player);

    //отрисовка
    void paint(Gui& gui, Logic& lg);

    //деструктор
    ~Play();
};
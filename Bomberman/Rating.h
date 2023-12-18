#pragma once
#include "Menu.h"

//рейтинговая таблица
class Rating : public Menu
{
private:
    vector<sf::Text> rating; //топ 5 игроков (логин - счет)

public:

    //конструктор
    Rating(Game* game);

    //загрузка рейтинга из файла
    void loadRating();

    //запуск цикла
    GameState start();

    //установка кнопок
    void setButtons(Gui& gui);

    //отрисовка
    void paint(Gui& gui);
};
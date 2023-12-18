#include "Game.h"

//главная функция
int main()
{
    system("chcp 1251");
    system("cls");
    srand(time(nullptr));
    Game gm{ {800, 600}, "Bomberman" };
    gm.start();
}
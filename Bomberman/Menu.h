#pragma once
#include "Game.h"

//����
class Menu {
protected:
    Game* g; //������� ����������
    GameState state; //������� ���������
    GameState firstState; //���������

    //�������� ����
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Text title; //���������

public:

    //�����������
    Menu(Game* game);

    //������ �����
    GameState start();

    //��������� ������
    void setButtons(Gui& gui);

    //���������
    void paint(Gui& gui);
};
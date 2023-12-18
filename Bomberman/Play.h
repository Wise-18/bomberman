#pragma once
#include "Player.h"
#include "Menu.h"
#include "Logic.h"

//����� �������� ��������
class Play : public Menu
{
public:

    //�����������
    Play(Game* game);

    //������ �����
    GameState start(Player& player);

    //���������
    void paint(Gui& gui, Logic& lg);

    //����������
    ~Play();
};
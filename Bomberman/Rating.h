#pragma once
#include "Menu.h"

//����������� �������
class Rating : public Menu
{
private:
    vector<sf::Text> rating; //��� 5 ������� (����� - ����)

public:

    //�����������
    Rating(Game* game);

    //�������� �������� �� �����
    void loadRating();

    //������ �����
    GameState start();

    //��������� ������
    void setButtons(Gui& gui);

    //���������
    void paint(Gui& gui);
};
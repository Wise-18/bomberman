#pragma once
#include "Menu.h"
#include <SFML/Audio/Music.hpp>

//����� - ��������� �����
class Options : public Menu
{
private:
    sf::Text check; //������� ��� checkbox
    CheckBox::Ptr box; //��� checkbox

    //������ �� ����
    sf::Music ambient;
    bool sound; //��������� ����� � ����

public:

    //�����������
    Options(Game* game);

    //������ �����
    GameState start();

    //��������� ������
    void setButtons(Gui& gui);

    //�������� ��� ��������� ����
    void checkSounds(bool flag);

    //���������
    void paint(Gui& gui);

    //������� ����������
    void clear();

    //�������� �������� ������� ����������
    bool checkSound();
};
#pragma once
#include "Menu.h"

//����������� ������ ������������
class Login : public Menu
{
private:
    sf::Text log; //������� ������
    EditBox::Ptr input; //���� �����
    string login; //������� �����

public:

    //�����������
    Login(Game* game);

    //������ �����
    GameState start();

    //��������� ������
    void setButtons(Gui& gui);

    //���������
    void paint(Gui& gui);

    //�������� ������ � �����
    bool checkLogin();

    //��������� ������
    string getLogin();

    //������� ����������
    void clear();
};
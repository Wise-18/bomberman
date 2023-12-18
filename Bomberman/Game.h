#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace sf;
using namespace tgui;
using namespace std;

//��������� ���������
enum GameState
{
    NONE, //������ ���������
    LOGIN, //�����������
    MENU, //������� ����
    GAME, //����
    RATING, //������� ��������
    OPTIONS, //���������
    WIN_LEVEL, //������ �������
    GAME_OVER, //���������
    EXIT //����� �� ����
};

//������� ����
struct Size
{
    size_t width;
    size_t height;
};

//������� ���� ���� ���������� ��� �������
class Game {
private:
    RenderWindow win; //������� ����
    Gui gui; //��������� ������������
    sf::Font font; //�����
    Size size; //������� ����
    string file = "data.txt"; //���� � ������� �������

public:

    //�����������
    Game(Size size, string title);

    //�������� ������� ���� �������
    RenderWindow& getRenderWindow();

    //��������, ��� ���� �������
    bool isOpen();

    //���������� �������
    bool pollEvent(sf::Event& e);

    //�������� ����
    void close();

    //�������� �����
    sf::Font& getFont();

    //�������� ����
    string getFile();

    //�������� ��������
    sf::Texture loadTexture(string textureFile);

    //������� ����
    const Size& getSize() const;

    //������ ����������
    void start();
};
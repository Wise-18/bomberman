#include "Game.h"
#include "Menu.h"
#include "Rating.h"
#include "Options.h"
#include "Login.h"
#include "Player.h"
#include "Play.h"

//�����������
Game::Game(Size size, string title) {
    win.create(VideoMode(size.width, size.height), title);
    //win.setFramerateLimit(144); //vsync
    this->size = size;

    //����� ������
    if (!font.loadFromFile("fonts/arial.ttf")) {
        cout << "������ �������� ������: fonts/arial.ttf" << endl;
    }
}

//������ ����������
void Game::start() {
    Menu menu(this);
    Rating rating(this);
    Options options(this);
    Login login(this);
    Player player(this);
    Play play(this);
    GameState state = LOGIN;

    //� ����������� �� �������� ��������� ����
    while (state != EXIT) {
        switch (state) {
        case LOGIN: {
            cout << "����� �����������" << endl;
            state = login.start();
            player.loadData(login.getLogin()); //��������� ���������� � ������������ �� �����
            break;
        }
        case GAME: {
            cout << "����" << endl;
            state = play.start(player);
            break;
        }
        case MENU: {
            cout << "����" << endl;
            state = menu.start();
            break;
        }
        case RATING: {
            cout << "�������" << endl;
            state = rating.start();
            break;
        }
        case OPTIONS: {
            cout << "���������" << endl;
            state = options.start();
            break;
        }
        }
    }
    cout << "����� �� ����" << endl;
}

//�������� ������� ���� �������
RenderWindow& Game::getRenderWindow()
{
    return win;
}

//��������, ��� ���� �������
bool Game::isOpen()
{
    return win.isOpen();
}

//���������� �������
bool Game::pollEvent(sf::Event& e)
{
    return win.pollEvent(e);
}

//�������� ����
void Game::close()
{
    win.close();
}

//�������� �����
sf::Font& Game::getFont() {
    return font;
}

//�������� ����
string Game::getFile() {
    return file;
}

//�������� ��������
sf::Texture Game::loadTexture(string textureFile)
{
    sf::Texture t;
    if (!t.loadFromFile(textureFile)) {
        cout << "������ �������� ��������: " << textureFile << endl;
    }
    return t;
}

//������� ����
const Size& Game::getSize() const
{
    return size;
}
#include "Play.h"

//�����������
Play::Play(Game* game) : Menu(game) {
    title.setString("");
    firstState = GAME;
}

//������ �����
GameState Play::start(Player& player) {

    //���� ����
    Gui gui{ g->getRenderWindow() };
    Logic lg{ g, 544, 448, 32, &player };
    Clock clock;
    state = firstState;
    while (g->isOpen())
    {
        //������� ������ ������ � ���������� ����������
        auto dt = clock.restart().asSeconds();

        //��� �������
        sf::Event event;
        while (g->pollEvent(event))
        {
            //��������� �������
            gui.handleEvent(event);

            //������� �������� �����
            if (event.type == sf::Event::Closed)
                g->close();

            //������ � ���������
            if (event.type == sf::Event::KeyReleased) {
                
                //����� � ����
                if (event.key.code == sf::Keyboard::Escape) {
                    state = MENU;
                }

                //�������� ���������� �� �����
                if (event.key.code == sf::Keyboard::Right) {
                    cout << "�����" << endl;
                    lg.move(1, 0);
                }
                if (event.key.code == sf::Keyboard::Left) {
                    cout << "����" << endl;
                    lg.move(-1, 0);
                }
                if (event.key.code == sf::Keyboard::Up) {
                    cout << "�����" << endl;
                    lg.move(0, -1);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    cout << "����" << endl;
                    lg.move(0, 1);
                }

                //������� ������
                if (event.key.code == sf::Keyboard::R) {
                    lg.reset();
                }

                //��������� �����
                if (event.key.code == sf::Keyboard::Space) {
                    cout << "��������� �����" << endl;
                    lg.setBomb();
                }
            }
        }

        //������� � ������ ���������
        if (state != firstState) {
            player.setScore(0);
            return state;
        }

        //���������� ������
        lg.update(dt);

        //���������
        paint(gui, lg);
    }
    return EXIT;
}

//���������
void Play::paint(Gui& gui, Logic& lg) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);

    //��������� �������� ����
    lg.paint();

    //���������
    gui.draw();
    g->getRenderWindow().display();
}

//����������
Play::~Play() {}
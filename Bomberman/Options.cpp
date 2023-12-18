#include "Options.h"

//�����������
Options::Options(Game* game) : Menu(game) {
    title.setString("Options");
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);

    //�������
    check.setFont(g->getFont());
    check.setFillColor(sf::Color::White);
    check.setString("Sound (ON / OFF)");
    check.setCharacterSize(30);
    check.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2 + 25, 270);

    //������ �� ����
    if (!ambient.openFromFile("music/ambient.mp3")) {
        cout << "������ �������� ������: music/ambient.mp3" << endl;
    }
    ambient.setVolume(10);
    ambient.setLoop(true);
    ambient.play();
    sound = true;

    firstState = OPTIONS;
}

//������ �����
GameState Options::start() {

    //���� ����
    Gui gui{ g->getRenderWindow() };
    setButtons(gui);
    state = firstState;
    while (g->isOpen())
    {
        //��� �������
        sf::Event event;
        while (g->pollEvent(event))
        {
            //��������� �������
            gui.handleEvent(event);

            //������� �������� �����
            if (event.type == sf::Event::Closed) {
                g->close();
            }
        }

        //������� � ������ ���������
        if (state != firstState) {
            clear();
            return state;
        }

        //���������
        paint(gui);
    }
    clear();
    return EXIT;
}

//�������� ��� ��������� ����
void Options::checkSounds(bool flag) {
    if (flag) {
        cout << "���� �������" << endl;
        ambient.play();
        sound = true;
    }
    else {
        cout << "���� ��������" << endl;
        ambient.stop();
        sound = false;
    }
}

//�������� �������� ������� ����������
bool Options::checkSound() {
    return sound;
}

//��������� ������
void Options::setButtons(Gui& gui) {

    //������� ������
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //��� / ���� ���� � ����
    box = CheckBox::create();
    box->setChecked(true);
    box->setSize({ btnSize.width - 70, btnSize.height - 15 });
    box->setPosition({ (w - btnSize.width) / 2 - 70, (h - btnSize.height) / 2 });
    box->onChange([&]() {checkSounds(box->isChecked()); });
    gui.add(box);

    //�����
    Button::Ptr back = Button::create();
    back->setSize({ btnSize.width,btnSize.height });
    back->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 180 });
    back->setText("Back");
    back->onPress([&] {state = MENU; });
    gui.add(back);
}

//���������
void Options::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    g->getRenderWindow().draw(check);
    gui.draw();
    g->getRenderWindow().display();
}

//������� ����������
void Options::clear() {
    box.reset();
}
#include "Login.h"

//�����������
Login::Login(Game* game) : Menu(game) {

    //�������
    log.setFont(g->getFont());
    log.setFillColor(sf::Color::White);
    log.setString("Login:");
    log.setCharacterSize(30);
    log.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 215);

    firstState = LOGIN;
}

//������ �����
GameState Login::start() {

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

//��������� ������
void Login::setButtons(Gui& gui) {

    //������� ������
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //���� ��� ����� ������
    input = EditBox::create();
    input->setSize({ btnSize.width * 1.5,btnSize.height * 0.8 });
    input->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 60 });
    input->onTextChange([&] {login = input->getText().toStdString(); cout << login << endl; });
    gui.add(input);

    //����
    Button::Ptr sign = Button::create();
    sign->setSize({ btnSize.width,btnSize.height });
    sign->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 });
    sign->setText("Sign");
    sign->onPress([&] {if (checkLogin()) state = MENU; });
    gui.add(sign);

    //�����
    Button::Ptr reset = Button::create();
    reset->setSize({ btnSize.width,btnSize.height });
    reset->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 60 });
    reset->setText("Reset");
    reset->onPress([&] {input->setText(""); });
    gui.add(reset);

    //�����
    Button::Ptr exit = Button::create();
    exit->setSize({ btnSize.width,btnSize.height });
    exit->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 120 });
    exit->setText("Exit");
    exit->onPress([&] {state = EXIT; });
    gui.add(exit);
}

//���������
void Login::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    g->getRenderWindow().draw(log);
    gui.draw();
    g->getRenderWindow().display();
}

//�������� ������ � �����
bool Login::checkLogin() {

    //������� �� 3 � ����� ��������
    if (login.length() >= 3 && login.find(' ') == string::npos) {

        //������� � �����
        ifstream reader{ g->getFile() };
        if (reader.is_open()) {

            //������ ������ ���� �� ������ ����������
            string line;
            bool flag = false; //���� ����� ����� ��� ���

            //������ ��������� �� �����
            while (!flag && getline(reader, line)) {
                stringstream stream{ line };
                string log;
                string score;
                stream >> log >> score;
                if (login == log) {
                    flag = true;
                }
            }
            reader.close();

            //��������� � ����� ���� ����� ����� � ����� ������
            if (!flag) {
                ofstream app{ g->getFile(), fstream::app };
                app << login << " " << 0 << endl;
                app.close();
                cout << "���� " << g->getFile() << " ������� ��������!" << endl;
            }
            else {
                cout << "��������� ����� ��� ����������" << endl;
            }
        }
        else {
            cout << "���� " << g->getFile() << " ������� ������!" << endl;
            ofstream writer{ g->getFile() };
            writer << login << " " << 0 << endl;
            writer.close();
        }
        return true;
    }
    else {
        cout << "����� ������� �� ����� ��� 3 �������� ��� �������� ������" << endl;
    }
    return false;
}

//��������� ������
string Login::getLogin() {
    return login;
}

//������� ����������
void Login::clear() {
    input.reset();
}
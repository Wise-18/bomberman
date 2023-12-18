#include "Login.h"

//конструктор
Login::Login(Game* game) : Menu(game) {

    //подпись
    log.setFont(g->getFont());
    log.setFillColor(sf::Color::White);
    log.setString("Login:");
    log.setCharacterSize(30);
    log.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 215);

    firstState = LOGIN;
}

//запуск цикла
GameState Login::start() {

    //цикл игры
    Gui gui{ g->getRenderWindow() };
    setButtons(gui);
    state = firstState;
    while (g->isOpen())
    {
        //пул событий
        sf::Event event;
        while (g->pollEvent(event))
        {
            //обработка событий
            gui.handleEvent(event);

            //событие закрытия формы
            if (event.type == sf::Event::Closed) {
                g->close();
            }
        }

        //переход в другое состояние
        if (state != firstState) {
            clear();
            return state;
        }

        //отрисовка
        paint(gui);
    }
    clear();
    return EXIT;
}

//установка кнопок
void Login::setButtons(Gui& gui) {

    //размеры кнопок
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //Поле для ввода логина
    input = EditBox::create();
    input->setSize({ btnSize.width * 1.5,btnSize.height * 0.8 });
    input->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 60 });
    input->onTextChange([&] {login = input->getText().toStdString(); cout << login << endl; });
    gui.add(input);

    //Вход
    Button::Ptr sign = Button::create();
    sign->setSize({ btnSize.width,btnSize.height });
    sign->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 });
    sign->setText("Sign");
    sign->onPress([&] {if (checkLogin()) state = MENU; });
    gui.add(sign);

    //Сброс
    Button::Ptr reset = Button::create();
    reset->setSize({ btnSize.width,btnSize.height });
    reset->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 60 });
    reset->setText("Reset");
    reset->onPress([&] {input->setText(""); });
    gui.add(reset);

    //Выход
    Button::Ptr exit = Button::create();
    exit->setSize({ btnSize.width,btnSize.height });
    exit->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 120 });
    exit->setText("Exit");
    exit->onPress([&] {state = EXIT; });
    gui.add(exit);
}

//отрисовка
void Login::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    g->getRenderWindow().draw(log);
    gui.draw();
    g->getRenderWindow().display();
}

//проверка логина в файле
bool Login::checkLogin() {

    //состоит из 3 и более символов
    if (login.length() >= 3 && login.find(' ') == string::npos) {

        //сверяем с базой
        ifstream reader{ g->getFile() };
        if (reader.is_open()) {

            //читаем данные пока не найдем совпадение
            string line;
            bool flag = false; //есть такой логин или нет

            //читаем построчно из файла
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

            //добавляем в конец файл новый логин в таком случае
            if (!flag) {
                ofstream app{ g->getFile(), fstream::app };
                app << login << " " << 0 << endl;
                app.close();
                cout << "Файл " << g->getFile() << " успешно дополнен!" << endl;
            }
            else {
                cout << "Указанный логин уже существует" << endl;
            }
        }
        else {
            cout << "Файл " << g->getFile() << " успешно создан!" << endl;
            ofstream writer{ g->getFile() };
            writer << login << " " << 0 << endl;
            writer.close();
        }
        return true;
    }
    else {
        cout << "Логин состоит из менее чем 3 символов или содержит пробел" << endl;
    }
    return false;
}

//получение логина
string Login::getLogin() {
    return login;
}

//очистка интерфейса
void Login::clear() {
    input.reset();
}
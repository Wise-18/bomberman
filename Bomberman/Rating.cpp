#include "Rating.h"

//конструктор
Rating::Rating(Game* game) : Menu(game) {
    title.setString("Rating");
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);
    firstState = RATING;
}

//загрузка рейтинга из файла
void Rating::loadRating() {
    rating.clear();
    ifstream reader{ g->getFile() };
    vector<pair<string, size_t>> top5;
    if (reader.is_open()) {
        string line;

        //читаем построчно из файла
        while (getline(reader, line)) {
            stringstream stream{ line };
            string login;
            string score;
            stream >> login >> score;
            top5.push_back({ login, stoi(score) });
        }
        reader.close();

        //упорядочиваем по убыванию счета
        for (int i = 0; i < top5.size(); i++) {
            for (int j = top5.size() - 1; j > i; j--) {
                if (top5[j].second > top5[j - 1].second) {
                    swap(top5[j], top5[j - 1]);
                }
            }
        }

        //получаем топ 5
        while (top5.size() > 5) {
            top5.pop_back();
        }

        //заполняем вектор
        for (int i = 0; i < top5.size(); i++) {
            sf::Text txt;
            txt.setFont(g->getFont());
            txt.setFillColor(sf::Color::White);
            txt.setString(to_string(i + 1) + ") " + top5[i].first + " - " + to_string(top5[i].second));
            txt.setCharacterSize(30);
            txt.setPosition((g->getSize().width - txt.getGlobalBounds().width) / 2, 60 * (i + 1) + 60);
            rating.push_back(txt);
        }
    }
    else {
        cout << "Ошибка открытия файла " << g->getFile() << endl;
    }
}

//запуск цикла
GameState Rating::start() {

    //цикл игры
    Gui gui{ g->getRenderWindow() };
    setButtons(gui);
    loadRating();
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
            if (event.type == sf::Event::Closed)
                g->close();
        }

        //переход в другое состояние
        if (state != firstState) {
            return state;
        }

        //отрисовка
        paint(gui);
    }
    return EXIT;
}

//установка кнопок
void Rating::setButtons(Gui& gui) {

    //размеры кнопок
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //Назад
    Button::Ptr back = Button::create();
    back->setSize({ btnSize.width,btnSize.height });
    back->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 180 });
    back->setText("Back");
    back->onPress([&] {state = MENU; });
    gui.add(back);
}

//отрисовка
void Rating::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);

    //вывод таблицы лидеров
    for (int i = 0; i < rating.size(); i++) {
        g->getRenderWindow().draw(rating[i]);
    }

    gui.draw();
    g->getRenderWindow().display();
}
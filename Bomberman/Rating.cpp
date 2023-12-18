#include "Rating.h"

//�����������
Rating::Rating(Game* game) : Menu(game) {
    title.setString("Rating");
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);
    firstState = RATING;
}

//�������� �������� �� �����
void Rating::loadRating() {
    rating.clear();
    ifstream reader{ g->getFile() };
    vector<pair<string, size_t>> top5;
    if (reader.is_open()) {
        string line;

        //������ ��������� �� �����
        while (getline(reader, line)) {
            stringstream stream{ line };
            string login;
            string score;
            stream >> login >> score;
            top5.push_back({ login, stoi(score) });
        }
        reader.close();

        //������������� �� �������� �����
        for (int i = 0; i < top5.size(); i++) {
            for (int j = top5.size() - 1; j > i; j--) {
                if (top5[j].second > top5[j - 1].second) {
                    swap(top5[j], top5[j - 1]);
                }
            }
        }

        //�������� ��� 5
        while (top5.size() > 5) {
            top5.pop_back();
        }

        //��������� ������
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
        cout << "������ �������� ����� " << g->getFile() << endl;
    }
}

//������ �����
GameState Rating::start() {

    //���� ����
    Gui gui{ g->getRenderWindow() };
    setButtons(gui);
    loadRating();
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
            if (event.type == sf::Event::Closed)
                g->close();
        }

        //������� � ������ ���������
        if (state != firstState) {
            return state;
        }

        //���������
        paint(gui);
    }
    return EXIT;
}

//��������� ������
void Rating::setButtons(Gui& gui) {

    //������� ������
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //�����
    Button::Ptr back = Button::create();
    back->setSize({ btnSize.width,btnSize.height });
    back->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 180 });
    back->setText("Back");
    back->onPress([&] {state = MENU; });
    gui.add(back);
}

//���������
void Rating::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);

    //����� ������� �������
    for (int i = 0; i < rating.size(); i++) {
        g->getRenderWindow().draw(rating[i]);
    }

    gui.draw();
    g->getRenderWindow().display();
}
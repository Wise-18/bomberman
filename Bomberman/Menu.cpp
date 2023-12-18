#include "Menu.h"

//�����������
Menu::Menu(Game* game) {
    g = game; //�������� ���������

    //�������� ����
    backgroundTexture = g->loadTexture("images/back.png");
    backgroundSprite.setTexture(backgroundTexture);

    //���������
    title.setFont(g->getFont());
    title.setFillColor(sf::Color::White);
    title.setString("BOMBER MAN");
    title.setCharacterSize(60);
    title.setPosition((g->getSize().width - title.getGlobalBounds().width) / 2, 20.0f);

    //��������� ���������
    firstState = MENU;
}

//������ �����
GameState Menu::start() {

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
void Menu::setButtons(Gui& gui) {

    //������� ������
    Size btnSize = { 100, 50 };
    int w = g->getSize().width;
    int h = g->getSize().height;

    //����
    Button::Ptr game = Button::create();
    game->setSize({ btnSize.width,btnSize.height });
    game->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 120 });
    game->setText("Play");
    game->onPress([&] {state = GAME; });
    gui.add(game);

    //�������
    Button::Ptr rating = Button::create();
    rating->setSize({ btnSize.width,btnSize.height });
    rating->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 - 60 });
    rating->setText("Rating");
    rating->onPress([&] {state = RATING; });
    gui.add(rating);

    //���������
    Button::Ptr options = Button::create();
    options->setSize({ btnSize.width,btnSize.height });
    options->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 });
    options->setText("Options");
    options->onPress([&] {state = OPTIONS; });
    gui.add(options);

    //�����
    Button::Ptr exit = Button::create();
    exit->setSize({ btnSize.width,btnSize.height });
    exit->setPosition({ (w - btnSize.width) / 2, (h - btnSize.height) / 2 + 60 });
    exit->setText("Exit");
    exit->onPress([&] {state = LOGIN; });
    gui.add(exit);
}

//���������
void Menu::paint(Gui& gui) {
    g->getRenderWindow().clear();
    g->getRenderWindow().draw(backgroundSprite);
    g->getRenderWindow().draw(title);
    gui.draw();
    g->getRenderWindow().display();
}
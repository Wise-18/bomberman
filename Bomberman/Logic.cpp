#include "Logic.h"

//конструктор
Logic::Logic(Game* game, int width, int height, int blockSize, Player* player) {
	
	//установка текущей игры и подгрузка текстуры
	g = game;
	p = player;
	gameTexture = new sf::Texture(g->loadTexture("images/game.png"));

	//счет
	score = 0;
	scoreText.setFont(g->getFont());
	scoreText.setString("Score: " + to_string(score));
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(
		130,
		scoreText.getGlobalBounds().height);
	
	//информация о текущем состоянии игры
	info.setFont(g->getFont());
	info.setString("");
	info.setCharacterSize(30);
	info.setFillColor(sf::Color::White);
	info.setPosition(
		((g->getSize().width - info.getGlobalBounds().width) / 2),
		(info.getGlobalBounds().height));

	//инициализируем карту
	size = 16;
	w = width / blockSize;
	h = height / blockSize;
	this->blockSize = blockSize;
	field = vector<vector<int>>(h, vector<int>(w, 0));

	//трава
	sf::Sprite grass;
	grass.setTexture(*gameTexture);
	grass.setTextureRect({ 0 * size, 4 * size, size, size });
	grass.setScale({ (float)blockSize / size * (w - 2), (float)blockSize / size * (h - 2) });
	grass.setPosition(
		{
			(float)blockSize + (g->getSize().width - w * blockSize) / 2,
			(float)blockSize + (g->getSize().height - h * blockSize) / 2
		});
	sprites.push_back(grass);

	//установка стен
	//вертикали
	for (int i = 0; i < h; i++) {
		sf::Sprite wall;
		wall.setTexture(*gameTexture);
		wall.setTextureRect({ 3 * size, 3 * size, size, size });
		wall.setScale({ (float)blockSize / size, (float)blockSize / size });
		wall.setPosition(
			{
					(float)(g->getSize().width - w * blockSize) / 2,
					(float)i * blockSize + (g->getSize().height - h * blockSize) / 2
			});
		sprites.push_back(wall);
		field[i][0] = 1;
		wall.setPosition(
			{
					(float)(w - 1) * blockSize + (g->getSize().width - w * blockSize) / 2,
					(float)i * blockSize + (g->getSize().height - h * blockSize) / 2
			});
		sprites.push_back(wall);
		field[i][w - 1] = 1;
	}

	//горизонтали
	for (int i = 1; i < w - 1; i++) {
		sf::Sprite wall;
		wall.setTexture(*gameTexture);
		wall.setTextureRect({ 3 * size, 3 * size, size, size });
		wall.setScale({ (float)blockSize / size, (float)blockSize / size });
		wall.setPosition(
			{
					(float)i * blockSize + (g->getSize().width - w * blockSize) / 2,
					(float)(g->getSize().height - h * blockSize) / 2
			});
		sprites.push_back(wall);
		field[0][i] = 1;
		wall.setPosition(
			{
					(float)i * blockSize + (g->getSize().width - w * blockSize) / 2,
					(float)(h - 1) * blockSize + (g->getSize().height - h * blockSize) / 2
			});
		sprites.push_back(wall);
		field[h - 1][i] = 1;
	}
	reset();
}

//сброс игры
void Logic::reset() {
	clear();
	status = 0; //игра идет

	//подписи
	score = 0;
	scoreText.setString("Score: " + to_string(score));
	info.setString("");

	//установка бомбера
	bomber = new Bomber(g, gameTexture, w, h, blockSize, size, 0, 4, { w / 2 - 6, h / 2 });

	//отдельные стены
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 3,3 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 6,3 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 9,3 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 12,3 }));

	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 4,7 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 7,7 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 10,7 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 13,7 }));

	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 3,11 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 6,11 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 9,11 }));
	walls.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 3, { 12,11 }));

	//разрушаемые стены
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 4,4 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 4,6 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 4,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 5,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 6,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 7,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 8,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 8,6 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 8,4 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 9,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 10,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 11,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 12,5 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 12,4 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 12,6 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 5,10 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 6,11 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 7,10 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 8,9 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 9,8 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 10,9 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 11,10 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 14,10 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 14,12 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 15,11 }));
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 13,11 }));

	//враги на уровне
	enemies.push_back(new Enemy(g, gameTexture, w, h, blockSize, size, 15, 0, { 7,6 }));
	enemies.push_back(new Enemy(g, gameTexture, w, h, blockSize, size, 15, 0, { 5,12 }));
	enemies.push_back(new Enemy(g, gameTexture, w, h, blockSize, size, 15, 0, { 9,2 }));

	//выход из уровня
	exit = new GameObject(g, gameTexture, w, h, blockSize, size, 3, 11, { 14,11 });
	bricks.push_back(new GameObject(g, gameTexture, w, h, blockSize, size, 3, 4, { 14,11 }));

	//отмечаем объекты на карте
	field[bomber->getPos().y][bomber->getPos().x] = 3;
	for (int i = 0; i < walls.size(); i++) {
		field[walls[i]->getPos().y][walls[i]->getPos().x] = 1;
	}
	for (int i = 0; i < bricks.size(); i++) {
		field[bricks[i]->getPos().y][bricks[i]->getPos().x] = 2;
	}
	for (int i = 0; i < enemies.size(); i++) {
		field[enemies[i]->getPos().y][enemies[i]->getPos().x] = 4;
	}
}

//очистка динамических переменных
void Logic::clear() {
	if (bomber)
		delete bomber;
	for (int i = 0; i < walls.size(); i++) {
		delete walls[i];
	}
	for (int i = 0; i < bricks.size(); i++) {
		delete bricks[i];
	}
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
	for (int i = 0; i < bombs.size(); i++) {
		delete bombs[i];
	}
	walls.clear();
	bricks.clear();
	enemies.clear();
	bombs.clear();
	if (exit)
		delete exit;
}

//изменяем положение бомбера
void Logic::move(int vx, int vy) {
	if (status == 0) {
		int result = bomber->move(field, vx, vy);
		if (result == 2) {
			over(1, "Game over!");
		}
		else if (result == 3) {
			over(2, "Win game!");
		}
	}
}

//обновление состояний остальных объектов
void Logic::update(float dt) {

	//по всем врагам
	for (int i = 0; status == 0 && i < enemies.size(); i++) {
		int result = enemies[i]->move(field, dt);

		//встретили игрока
		if (result == 2) {
			over(1, "Game over!");
		}
	}

	//по всем бомбам
	for (int i = 0; i < bombs.size(); i++) {
		int result = bombs[i]->ticks(field, dt);
		if (result == 1) {

			//убираем взрыв
			bombs.erase(bombs.begin() + i);
			break;
		}
		if (result == 2) {

			//обработка клеток, которые зацепило взрывом
			auto vec = bombs[i]->getBoomPos();
			for (int j = 0; j < vec.size(); j++) {

				//игрок
				//координаты совпали
				if (bomber->getPos().x == vec[j].x && bomber->getPos().y == vec[j].y) {
					over(1, "Game over!");
				}

				//враги
				for (int k = 0; k < enemies.size(); k++) {
					if (enemies[k]->getPos().x == vec[j].x && enemies[k]->getPos().y == vec[j].y) {
						enemies.erase(enemies.begin() + k);
						score += 100;
						scoreText.setString("Score: " + to_string(score));
						break;
					}
				}

				//кирпичи
				for (int k = 0; k < bricks.size(); k++) {
					if (bricks[k]->getPos().x == vec[j].x && bricks[k]->getPos().y == vec[j].y) {

						//если открыли выход
						if (exit->getPos().x == vec[j].x && exit->getPos().y == vec[j].y) {
							field[exit->getPos().y][exit->getPos().x] = 6;
						}
						bricks.erase(bricks.begin() + k);
						break;
					}
				}
			}
		}
	}
}

//установка бомбы
void Logic::setBomb() {

	//если ещё не установлено бомб
	if (bombs.size() == 0) {
		Bomb* bomb = new Bomb(g, gameTexture, w, h, blockSize, size, 3, 0, 
			{ bomber->getPos().x, bomber->getPos().y });
		bombs.push_back(bomb);
	}
}

//конец игры
void Logic::over(int newStatus, string title) {
	status = newStatus;
	info.setString(title);
	info.setPosition(
		((g->getSize().width - info.getGlobalBounds().width) / 2),
		(info.getGlobalBounds().height));
	p->setScore(score);
	p->updateScore();
}

//отрисовка
void Logic::paint() {

	//отрисовка игрового поля
	for (int i = 0; i < sprites.size(); i++) {
		g->getRenderWindow().draw(sprites[i]);
	}

	//отдельная отрисовка объектов
	if(bomber && status == 0)
		bomber->paint();
	if (exit) {
		exit->paint();
	}

	//стены
	for (int i = 0; i < walls.size(); i++) {
		walls[i]->paint();
	}

	//разрушаемые стены
	for (int i = 0; i < bricks.size(); i++) {
		bricks[i]->paint();
	}

	//враги
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->paint();
	}

	//бомбы
	for (int i = 0; i < bombs.size(); i++) {
		bombs[i]->paint();
	}

	//gui
	g->getRenderWindow().draw(scoreText);
	g->getRenderWindow().draw(info);
}

//деструктор
Logic::~Logic() {
	delete gameTexture;
	clear();
}
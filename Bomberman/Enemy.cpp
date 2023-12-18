#include "Enemy.h"

//конструктор
Enemy::Enemy(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos)
	: GameObject(game, tex, w, h, blockSize, size, i, j, pos) {
	timeOut = 0;
	if (rand() % 2) {
		dir = { rand() % 3 - 1,0 };
	}
	else {
		dir = { 0, rand() % 3 - 1 };
	}
}

//автоматически делает шаг через заданный промежуток времени
int Enemy::move(vector<vector<int>>& field, float dt) {
	timeOut += dt;

	//вышло время
	if (timeOut >= 1.0f) {
		timeOut = 0.0f;
		int dx = pos.x + dir.x;
		int dy = pos.y + dir.y;

		//валидные клетки
		if (dx >= 1 && dx < w - 1 && dy >= 1 && dy < h - 1 && (dir.x != 0 || dir.y != 0)) {

			//делаем шаг
			int step = field[dy][dx];
			if (step == 3 || step == 0) {
				sprite.setPosition(
					{
							(float)dx * blockSize + (g->getSize().width - w * blockSize) / 2,
							(float)dy * blockSize + (g->getSize().height - h * blockSize) / 2
					});
				field[pos.y][pos.x] = 0;
				setPos({ pos.x + dir.x, pos.y + dir.y });
				field[pos.y][pos.x] = 4;
			}

			//если это игрок
			if (step == 3) {
				return 2; //проиграли
			}

			//если пусто
			else if (step == 0) {
				return 1; //обычный ход
			}
			else {

				//меняем направление движения
				if (rand() % 2) {
					dir = { rand() % 3 - 1,0 };
				}
				else {
					dir = { 0, rand() % 3 - 1 };
				}
			}
		}
		else {

			//меняем направление движения
			if (rand() % 2) {
				dir = { rand() % 3 - 1,0 };
			}
			else {
				dir = { 0, rand() % 3 - 1 };
			}
		}
	}
	return 0;
}
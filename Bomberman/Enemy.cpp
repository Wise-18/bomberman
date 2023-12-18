#include "Enemy.h"

//�����������
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

//������������� ������ ��� ����� �������� ���������� �������
int Enemy::move(vector<vector<int>>& field, float dt) {
	timeOut += dt;

	//����� �����
	if (timeOut >= 1.0f) {
		timeOut = 0.0f;
		int dx = pos.x + dir.x;
		int dy = pos.y + dir.y;

		//�������� ������
		if (dx >= 1 && dx < w - 1 && dy >= 1 && dy < h - 1 && (dir.x != 0 || dir.y != 0)) {

			//������ ���
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

			//���� ��� �����
			if (step == 3) {
				return 2; //���������
			}

			//���� �����
			else if (step == 0) {
				return 1; //������� ���
			}
			else {

				//������ ����������� ��������
				if (rand() % 2) {
					dir = { rand() % 3 - 1,0 };
				}
				else {
					dir = { 0, rand() % 3 - 1 };
				}
			}
		}
		else {

			//������ ����������� ��������
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
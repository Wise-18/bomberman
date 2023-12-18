#include "Bomber.h"

//�����������
Bomber::Bomber(Game* game, sf::Texture* tex, int width, int height, int blockSize, int size, int i, int j, sf::Vector2i pos)
	: GameObject(game, tex, width, height, blockSize, size, i, j, pos) {}

//�������� � ������ �������
int Bomber::move(vector<vector<int>>& field, int vx, int vy) {
	int dx = pos.x + vx;
	int dy = pos.y + vy;

	//���� ���������� �������
	if (dx >= 1 && dx < w - 1 && dy >= 1 && dy < h - 1) {
		
		//� ����������� �� ������
		switch (field[dy][dx]) {
		case 0: {
			//�����
			sprite.setPosition(
				{
						(float)dx * blockSize + (g->getSize().width - w * blockSize) / 2,
						(float)dy * blockSize + (g->getSize().height - h * blockSize) / 2
				});
			field[pos.y][pos.x] = 0;
			setPos({ pos.x + vx, pos.y + vy });
			field[pos.y][pos.x] = 3;
			return 1; //��������
			break;
		}
		case 1: case 2: {
			//����� ��� ������
			break;
		}
		case 4: case 5: {
			//���� ��� �����
			field[pos.y][pos.x] = 0;
			sprite.setPosition(
				{
						-100,
						-100
				});
			return 2;
			break;
		}
		case 6: {
			//�����
			field[pos.y][pos.x] = 0;
			sprite.setPosition(
				{
						-100,
						-100
				});
			return 3;
			break;
		}
		}
	}
	return 0;
}

//��������� �����
void Bomber::setBomb() {

}
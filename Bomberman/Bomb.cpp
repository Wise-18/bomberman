#include "Bomb.h"

//�����������
Bomb::Bomb(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos)
	: GameObject(game, tex, w, h, blockSize, size, i, j, pos) {
	timeOut = 0;
	showTime = 0.5f;
	sf::Sprite boom;
	this->tex = tex;
	boom.setTexture(*tex);
	boom.setTextureRect({ 2 * size, 11 * size, size, size });
	boom.setScale({ (float)blockSize / size, (float)blockSize / size });
	boom.setPosition(
		{
				(float)pos.x * blockSize + (g->getSize().width - w * blockSize) / 2,
				(float)pos.y * blockSize + (g->getSize().height - h * blockSize) / 2
		});
	this->boom.push_back(boom);
	boomPos.push_back({ pos.x, pos.y });
}

//�������� ����� �� ������
int Bomb::ticks(vector<vector<int>>& field, float dt) {
	timeOut += dt;
	if (timeOut > 2.0f) {

		//����������� �����
		if (showTime == 0.5f) {

			//��������� �������� ������
			//�� ������� ����� �������������� �����
			vector<sf::Vector2i> dirs = {
				{-1, 0},
				{1, 0},
				{0, -1},
				{0, 1}
			};
			for (int i = 0; i < dirs.size(); i++) {
				int dx = pos.x + dirs[i].x;
				int dy = pos.y + dirs[i].y;

				//���� ���������� ��������
				if (dx >= 1 && dx < w - 1 && dy >= 1 && dy < h - 1) {

					//��� �� �����
					if (field[dy][dx] != 1) {
						field[dy][dx] = 0; //����������� ������
						sf::Sprite boom;
						boom.setTexture(*tex);
						int size = 16;
						if (dirs[i].x == -1) {
							boom.setTextureRect({ 1 * size, 11 * size, size, size });
						}
						else if (dirs[i].x == 1) {
							boom.setTextureRect({ 3 * size, 11 * size, size, size });
						}
						else if(dirs[i].y == -1){
							boom.setTextureRect({ 2 * size, 9 * size, size, size });
						}
						else if(dirs[i].y == 1){
							boom.setTextureRect({ 2 * size, 13 * size, size, size });
						}
						boom.setScale({ (float)blockSize / size, (float)blockSize / size });
						boom.setPosition(
							{
									(float)dx * blockSize + (g->getSize().width - w * blockSize) / 2,
									(float)dy * blockSize + (g->getSize().height - h * blockSize) / 2
							});
						this->boom.push_back(boom);
						boomPos.push_back({ dx, dy });
					}
				}
			}
			field[pos.y][pos.x] = 0;
			showTime -= dt;
			return 2;
		}
		if (showTime <= 0) {
			cout << "�����" << endl;
			return 1; //������� �����
		}
		showTime -= dt;
	}
	return 0;
}

//���������
void Bomb::paint() {
	
	//�� ������
	if (showTime == 0.5f) {
		g->getRenderWindow().draw(sprite);
	}
	else {
		//�����
		for (int i = 0; i < boom.size(); i++) {
			g->getRenderWindow().draw(boom[i]);
		}
	}
}

//�������� ������
vector<sf::Vector2i> Bomb::getBoomPos() {
	return boomPos;
}
#pragma once
#include "GameObject.h"

//����� ����������
class Bomber : public GameObject
{
public:

	//�����������
	Bomber(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//�������� � ������ �������
	int move(vector<vector<int>>& field, int vx, int vy);

	//��������� �����
	void setBomb();
};
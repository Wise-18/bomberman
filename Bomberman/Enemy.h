#pragma once
#include "GameObject.h"

//���� �� ������� ����
class Enemy : public GameObject
{
private:
	float timeOut; //�������� ����
	sf::Vector2i dir; //����������� ��������

public:

	//�����������
	Enemy(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//������������� ������ ��� ����� �������� ���������� �������
	int move(vector<vector<int>>& field, float dt);
};
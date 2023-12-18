#pragma once
#include "Game.h"

//������� ������
class GameObject
{
protected:
	Game* g; //������� ����
	int w, h; //������� ����
	int blockSize; //������ ����� ������
	sf::Vector2i pos; //��������� �� ������� ����
	sf::Sprite sprite; //������� ������

public:

	//�����������
	GameObject(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//���������
	void paint();

	//�������� ����������
	sf::Vector2i getPos();

	//�������������
	void setPos(sf::Vector2i pos);
};
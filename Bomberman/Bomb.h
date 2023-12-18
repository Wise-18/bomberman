#pragma once
#include "GameObject.h"

//������������ �����
class Bomb : public GameObject
{
private:
	float timeOut; //������� ������� �� ������
	float showTime; //������� ������� ���������� �����
	vector<sf::Sprite> boom; //������� ������
	vector<sf::Vector2i> boomPos; //������ �� ������� ��������� �����
	sf::Texture* tex; //�������� ����

public:

	//�����������
	Bomb(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//�������� ����� �� ������
	int ticks(vector<vector<int>>& field, float dt);

	//���������
	void paint();

	//�������� ������
	vector<sf::Vector2i> getBoomPos();
};
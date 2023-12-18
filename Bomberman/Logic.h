#pragma once
#include "Game.h"
#include "Bomber.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Player.h"

//������� ������ ��� ������� ���� � ��� ��������� �������
//��������� �� ��������������
class Logic
{
private:
	vector<vector<int>> field; //������� ����
	//(0 - �����, 1 - �����, 2 - ������, 3 - ������, 4 - ����, 5 - �����, 6 - ����� / �����)

	Game* g; //������� ����
	Player* p; //������� �����
	int size; //���� ������ �������

	//�������� ��� ���� ��������
	sf::Texture* gameTexture = nullptr;
	vector<sf::Sprite> sprites; //��������� ������� ���������� �� ��������
	int w, h; //������� ����
	int blockSize; //������ ����� ������ ����

	//���������
	Bomber* bomber = nullptr; //�����

	//�����
	vector<GameObject*> walls;

	//����������� �����
	vector<GameObject*> bricks;

	//�����
	vector<Enemy*> enemies;

	//�����
	GameObject* exit = nullptr;

	//�����
	vector<Bomb*> bombs;

	//����
	int score;
	sf::Text scoreText;

	//����������
	sf::Text info;

	int status; //������ ����

public:

	//�����������
	Logic(Game* game, int width, int height, int blockSize, Player* player);

	//����� ����
	void reset();

	//������� ������������ ����������
	void clear();

	//���������� ��������� ��������� ��������
	void update(float dt);

	//�������� ����������
	void move(int vx, int vy);

	//��������� �����
	void setBomb();

	//���������
	void paint();

	//����� ����
	void over(int newStatus, string title);

	//����������
	~Logic();
};
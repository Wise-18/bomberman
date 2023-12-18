#pragma once
#include "Game.h"

//��� ����������� ������
class Player
{
private:
	Game* g; //������� ����
	string login; //�����
	size_t score; //���� ����

public:

	//�����������
	Player(Game* game);

	//��������� ������
	string getLogin();

	//��������� �����
	size_t getScore();

	//��������� ������
	void setLogin(string login);

	//��������� �����
	void setScore(size_t score);

	//��������� ������ �� �����
	void loadData(string log);

	//��������� ���� � ����� ��� �������� ������������
	void updateScore();
};
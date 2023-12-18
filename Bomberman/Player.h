#pragma once
#include "Game.h"

//для менеджмента данных
class Player
{
private:
	Game* g; //текущая игра
	string login; //логин
	size_t score; //счет игры

public:

	//конструктор
	Player(Game* game);

	//получение логина
	string getLogin();

	//получение счета
	size_t getScore();

	//установка логина
	void setLogin(string login);

	//установка счета
	void setScore(size_t score);

	//получение данных из файла
	void loadData(string log);

	//обновляем счет в файле для текущего пользователя
	void updateScore();
};
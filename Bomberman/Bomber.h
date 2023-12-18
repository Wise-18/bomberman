#pragma once
#include "GameObject.h"

//класс бомбермена
class Bomber : public GameObject
{
public:

	//конструктор
	Bomber(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//движение в разные стороны
	int move(vector<vector<int>>& field, int vx, int vy);

	//установка бомбы
	void setBomb();
};
#pragma once
#include "GameObject.h"

//враг на игровом поле
class Enemy : public GameObject
{
private:
	float timeOut; //ожидание хода
	sf::Vector2i dir; //направление движения

public:

	//конструктор
	Enemy(Game* game, sf::Texture* tex, int w, int h, int blockSize, int size, int i, int j, sf::Vector2i pos);

	//автоматически делает шаг через заданный промежуток времени
	int move(vector<vector<int>>& field, float dt);
};